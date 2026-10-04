# Bind9 DNS

O BIND 9 (Berkeley Internet Name Domain version 9) é o software servidor de DNS (Domain Name System) mais utilizado no mundo. Ele é um projeto open-source mantido pelo Internet Systems Consortium (ISC) e atua como a "lista de contatos" da internet, traduzindo nomes de domínio legíveis por humanos (como exemplo.com) em endereços IP legíveis por máquinas (como 192.0.2.1).

O daemon do serviço se chama **named**. No Debian/Ubuntu, o unit do systemd costuma ser `named` ou `bind9` (ex.: `systemctl status bind9`).

## Visão da arquitetura

Em muitos provedores e redes corporativas o mesmo BIND concentra vários papéis. Visualmente:

```text
                      +-----------------------------+
                      |   Clientes / Roteadores     |
                      +--------------+--------------+
                                     |
                          Consultas DNS (UDP/TCP 53)
                                     v
                 +---------------------------------------+
                 |            Servidor BIND9             |
                 +-------------------+-------------------+
                                     |
         +---------------------------+---------------------------+
         |                           |                           |
         v                           v                           v
+-------------------+       +-------------------+       +-------------------+
|  DNS Autoritativo |       |  Recursão / Cache |       |   Zonas Reversas  |
| - Zonas diretas   |       | - Validação DNSSEC|       | - Blocos públicos |
| - Resposta "AA"   |       | - Filtragem RPZ   |       | - RFC 1918 / CGNAT|
+-------------------+       +-------------------+       +-------------------+
```

- **AA** (*Authoritative Answer*): flag na resposta quando o servidor é autoritativo pela zona.
- Recursão e RPZ costumam atender à **rede autorizada**; zonas reversas públicas atendem quem consulta PTR na Internet.

## Principais formas de usar o BIND 9

O BIND 9 pode desempenhar diferentes papéis em uma rede, dependendo de como é configurado. Em resumo: o **recursivo** busca respostas na internet para os clientes; o **autoritativo** é a fonte oficial dos registros de um domínio; o **híbrido** faz os dois no mesmo servidor.

### Servidor Recursivo (Resolver)

**O que é:** um DNS que recebe a pergunta do cliente (PC, notebook, servidor, navegador, etc.) e, se não tiver a resposta na cache, percorre a hierarquia DNS (root → TLD → autoritativo) até obter o IP (ou outro registro) e devolvê-lo ao cliente.

**Finalidade:** ser o “DNS que a rede usa” no dia a dia — o endereço configurado em `/etc/resolv.conf`, DHCP ou firewall. Exemplos práticos: DNS interno da empresa, DNS do provedor, ou um resolver só para uma LAN.

**Características típicas:**

- Clientes apontam para ele (`nameserver 10.0.0.10`)
- Mantém **cache** para acelerar consultas repetidas
- Precisa de saída para a internet (ou de *forwarders*) para resolver nomes públicos
- Em geral **não** é a fonte oficial dos seus domínios (isso é papel do autoritativo)
- Deve restringir quem pode usar recursão (`allow-recursion`) — abrir para a internet inteira é risco (abuso / amplificação)

### Servidor Autoritativo

**O que é:** um DNS que guarda e responde **oficialmente** pelas zonas de um ou mais domínios. Quando alguém pergunta “qual o IP de `www.exemplo.com`?”, se este servidor for o NS publicado no registro do domínio, a resposta dele é a referência.

**Finalidade:** publicar e manter os registros do seu domínio (A, AAAA, MX, TXT, CNAME, NS, etc.) — site, e-mail, SPF, API internas mapeadas por nome, etc. É o papel de “servidor de nomes do domínio” na hospedagem ou no datacenter.

**Características típicas:**

- Contém os arquivos de zona (`db.exemplo.com`) ou, se for secundário (slave), os recebe de um primary
- Responde só o que está nas **suas** zonas (ou devolve NXDOMAIN / referral conforme o caso)
- Em modo autoritativo puro, **não** resolve o restante da internet para os clientes
- Costuma aparecer nos registros **NS** do domínio nos registrars
- Primary edita a zona; secondary replica via transferência (AXFR/IXFR)

### Servidor Híbrido

**O que é:** o mesmo processo BIND configurado para ser **ao mesmo tempo** recursivo (resolver para clientes) e autoritativo (zonas locais). Muitos setups pequenos começam assim: um único servidor com `recursion yes` e zonas em `named.conf.local`.

**Finalidade:** simplificar a operação quando há poucos hosts e uma equipe pequena — um único IP de DNS atende à LAN e também publica os domínios internos/externos.

**Cuidados:**

- Mistura dois papéis com riscos e cargas diferentes (cache/recursão vs. zonas oficiais)
- Um problema de recursão (loop, sobrecarga, abuso) pode afetar também as zonas autoritativas, e o contrário
- A recomendação de segurança e boas práticas é **separar**: um (ou mais) resolvers para a rede e outro(s) servidor(es) só autoritativos, com recursão desligada para o público
- Se for híbrido, limite bem `allow-query` / `allow-recursion` e monitore carga e logs

| Papel | Pergunta que responde | Objetivo principal |
|-------|------------------------|--------------------|
| Recursivo | “Qual o IP de qualquer nome?” | Resolver e cachear para os clientes |
| Autoritativo | “O que está publicado em *meu* domínio?” | Ser a fonte oficial da zona |
| Híbrido | Os dois no mesmo host | Conveniência; separar em produção quando possível |

## Funções que costumam complementar o serviço

Além dos três modos acima, o mesmo servidor (híbrido) frequentemente entrega:

### Resolução reversa (rDNS / PTR)

**O que é:** traduz IP → nome (`in-addr.arpa` no IPv4, `ip6.arpa` no IPv6), o inverso do registro A/AAAA.

**Para que serve na prática:**

- Conformidade com RIR / Registro.br / LACNIC em blocos públicos (ASN)
- **Entregabilidade de e-mail** — muitos provedores (Gmail, Microsoft, etc.) esperam PTR coerente com o hostname do MTA
- Diagnóstico (`traceroute`, inventário) e monitoramento (Zabbix, Grafana, etc.)

### Filtragem RPZ (Response Policy Zone)

**O que é:** uma zona de política usada como *DNS firewall*. Antes (ou no lugar) da resolução normal, o BIND aplica regras a nomes consultados.

**Finalidade:** bloquear malware, phishing, domínios indesejados, etc., respondendo NXDOMAIN ou redirecionando (ex.: `CNAME localhost`), conforme a política.

### DNSSEC

**O que é:** extensões que assinam criptograficamente dados DNS.

**Finalidade:**

- No **resolver**: `dnssec-validation` verifica se a resposta da Internet é autêntica (mitiga *cache poisoning* / sequestro)
- No **autoritativo**: assinam-se as zonas próprias (`inline-signing`, `key-directory`, etc.) para quem valida DNSSEC confiar nos seus registros

## O que é um domínio (anatomia do nome)

Um **nome de domínio** é um endereço hierárquico lido **da direita para a esquerda**. Cada pedaço entre pontos é um **rótulo** (*label*). O conjunto completo, incluindo o host, chama-se **FQDN** (*Fully Qualified Domain Name*) quando termina com o ponto da raiz (ex.: `www.exemplo.com.br.`).

Exemplo: `www.exemplo.com.br`

```text
  www  .  exemplo  .  com  .  br  .
   |         |         |      |   |
   |         |         |      |   +── Raiz DNS (root) — implícita; o ponto final do FQDN
   |         |         |      +────── ccTLD (país): Brasil
   |         |         +───────────── categoria sob .br (com, org, net, ...)
   |         +─────────────────────── domínio registrado (o que você compra no Registro.br)
   +───────────────────────────────── host / subdomínio (www, mail, api, ...)
```

| Parte | Exemplo | O que representa |
|-------|---------|------------------|
| Host / subdomínio | `www` | Máquina ou serviço dentro do domínio (`mail`, `ns1`, `app`…) |
| Nome registrado | `exemplo` | Organização / marca — zona que o autoritativo publica |
| Nível sob o TLD | `com` | Em `.br`: categoria (`com.br`, `org.br`…). Em `exemplo.com`: o próprio gTLD é `com` |
| TLD | `br` ou `com` | *Top-Level Domain* — país (ccTLD) ou genérico (gTLD: `.com`, `.net`, `.org`) |
| Raiz | `.` | Topo da árvore DNS; todos os TLDs “penduram” nela |

**Observações úteis:**

- `exemplo.com.br` (sem `www`) já é um FQDN válido — muitos sites têm registro **A** no apex (`@`) e `www` como **CNAME** ou outro **A**.
- `www` **não** faz parte obrigatória do domínio; é só um subdomínio convencional para o site web.
- No DNS a busca sobe a hierarquia pelo lado direito: primeiro sabe-se quem cuida de `.br`, depois de `com.br`, depois de `exemplo.com.br`, e por fim resolve-se `www`.

Comparando formatos comuns:

```text
www.exemplo.com.br     →  host + domínio.br (Registro.br)
mail.empresa.com       →  host + domínio sob gTLD .com
api.interno.lan        →  host + zona interna (não precisa ser pública)
```

## Como Funciona a Resolução no BIND 9

Quando um computador solicita o IP de um site usando um servidor BIND 9 **recursivo**, o processo ocorre em etapas. A busca segue a **árvore** do DNS, do topo (raiz) até o autoritativo do domínio.

### Níveis da hierarquia (exemplo: `www.exemplo.com.br`)

```text
                         (raiz)  .
                          / | \
                         /  |  \
                       com br  org   ...     ← TLDs (servidores raiz apontam para cá)
                            |
                          com.br              ← categoria sob .br
                            |
                       exemplo.com.br         ← domínio registrado (zona autoritativa)
                      /     |      \
                   www    mail    ns1         ← hosts / subdomínios (registros A, MX, ...)
                    |
                 203.0.113.10                 ← IP (resposta final)
```

Ordem típica das consultas (quando não há cache):

```text
  1º  Resolver → Root (.)           "Quem é responsável por .br?"
  2º  Resolver → TLD .br            "Quem cuida de com.br / exemplo.com.br?"
  3º  Resolver → (nível com.br)     "Quais NS de exemplo.com.br?"
  4º  Resolver → Autoritativo       "Qual o A de www.exemplo.com.br?"
  5º  Resolver → Cliente            devolve o IP e guarda na cache (TTL)
```

Diagrama em sequência (cliente ↔ BIND ↔ hierarquia):

```text
 Cliente                BIND (recursivo)           Hierarquia DNS
    |                         |                          |
    |--- consulta nome ------>|                          |
    |                         |-- cache hit? ------------|
    |                         |     sim → responde       |
    |                         |     não ↓                |
    |                         |------ root hints ------->| Root (.)
    |                         |<----- NS do TLD ---------|
    |                         |------ consulta TLD ----->| TLD (.br / .com)
    |                         |<----- NS autoritativo ---|
    |                         |------ consulta zona ---->| Autoritativo (exemplo.com.br)
    |                         |<----- resposta + TTL ----|
    |                         |-- grava cache            |
    |<-- IP / registro -------|                          |
```

1. **Consulta à Cache:** o BIND 9 verifica se o IP do domínio já está armazenado em sua memória cache local. Se estiver dentro do tempo de vida (TTL), ele responde imediatamente.
2. **Consulta aos Root Servers:** caso não esteja na cache, o BIND 9 consulta um dos Root Servers (raiz `.`). Ele já os conhece pelo arquivo de *root hints*; a resposta indica quem cuida do TLD (ex.: `.br`, `.com`).
3. **Consulta ao TLD (e níveis intermediários):** o resolver pergunta aos NS do TLD. Em nomes como `exemplo.com.br`, pode haver um passo a mais sob `.br` (ex.: `com.br`) até obter os NS do domínio registrado.
4. **Consulta ao Servidor Autoritativo:** o BIND faz a requisição final aos NS de `exemplo.com.br` (ou equivalente), que devolvem o registro pedido (ex.: **A** de `www`).
5. **Resposta e Caching:** o BIND envia o resultado ao cliente e guarda na cache local pelo TTL.

O BIND 9 não possui uma interface gráfica (GUI) nativa. Ele é gerenciado e configurado essencialmente através de arquivos de texto plano e utilitários de linha de comando.

## Como é feita a gestão nativa

- **Arquivos de configuração:** o arquivo principal é o `named.conf` (opções gerais, permissões e declarações de zonas). No Debian/Ubuntu ele costuma apenas incluir outros arquivos, por exemplo:
  - `/etc/bind/named.conf.options`
  - `/etc/bind/named.conf.local`
  - `/etc/bind/named.conf.default-zones`
- **Arquivos de zona:** arquivos onde ficam mapeados os registros DNS propriamente ditos (A, AAAA, CNAME, MX, TXT, etc.).
- **Utilitário rndc:** ferramenta de linha de comando para controlar o daemon do BIND 9 em tempo de execução (recarregar zonas, limpar cache, verificar status) sem precisar reiniciar o serviço.

## Modelos dos arquivos de configuração (Debian/Ubuntu)

Caminhos típicos em `/etc/bind/`. Os exemplos abaixo são **modelos didáticos** — ajuste IPs, redes e nomes ao seu ambiente.

### 1. `named.conf` — ponto de entrada

**Para que serve:** arquivo principal lido pelo `named`. No Debian/Ubuntu ele quase só faz `include` dos outros arquivos.

**Como funciona:** na subida do serviço, o BIND carrega este arquivo e, em cascata, tudo o que for incluído.

```
// /etc/bind/named.conf
include "/etc/bind/named.conf.options";
include "/etc/bind/named.conf.local";
include "/etc/bind/named.conf.default-zones";
```

| Diretiva | O que faz |
|----------|-----------|
| `include "..."` | Incorpora o conteúdo de outro arquivo de configuração |

---

### 2. `named.conf.options` — opções globais

**Para que serve:** comportamento geral do servidor (recursão, quem pode consultar, forwarders, portas, diretórios).

**Como funciona:** o bloco `options { ... };` vale para todo o daemon, salvo se uma zona ou view sobrescrever algo.

```
// /etc/bind/named.conf.options
options {
    directory "/var/cache/bind";

    // Quem pode fazer consultas (clientes)
    allow-query { localhost; 10.0.0.0/8; };

    // Quem pode usar este servidor como recursivo
    allow-recursion { localhost; 10.0.0.0/8; };
    recursion yes;

    // Encaminhar consultas a outros resolvers (opcional)
    // forwarders {
    //     1.1.1.1;
    //     8.8.8.8;
    // };
    // forward only;   // só usa forwarders; sem isso, tenta a hierarquia DNS

    dnssec-validation auto;

    listen-on port 53 { 127.0.0.1; 10.0.0.10; };
    listen-on-v6 { none; };

    // Evita vazamento de versão
    version "not currently available";
};
```

| Configuração | O que é / para que serve |
|--------------|--------------------------|
| `directory` | Pasta de trabalho do `named` (cache, arquivos temporários de zona) |
| `allow-query` | ACLs de quem pode fazer consultas DNS neste servidor |
| `allow-recursion` | ACLs de quem pode pedir resolução recursiva (não deve ser “qualquer um” na internet) |
| `recursion` | Liga/desliga resolução recursiva |
| `forwarders` | Lista de DNS externos para os quais o BIND pode encaminhar consultas |
| `forward only` | Se definido, só usa os forwarders (não sobe a hierarquia root→TLD) |
| `dnssec-validation` | Validação DNSSEC das respostas (`auto`, `yes`, `no`) |
| `listen-on` | Endereços IPv4 e porta em que o BIND escuta |
| `listen-on-v6` | Idem para IPv6 (`none` desliga) |
| `version` | Texto devolvido em consultas CHAOS `version.bind` (hardening) |

ACLs comuns: `localhost`, `any`, `none`, ou redes CIDR (`10.0.0.0/8`). Dá para criar ACLs nomeadas com `acl "rede-interna" { ... };`.

> **Open Resolver — perigo:** `allow-recursion` **nunca** deve ser `any` em servidor exposto à Internet. Recursão aberta é abusada para amplificação de DDoS. Restrinja a redes internas / clientes autorizados (`acl`). `allow-query { any; }` pode ser aceitável para **consultar zonas autoritativas** públicas; a recursão é que precisa ficar fechada.

---

### 3. `named.conf.local` — zonas locais (suas)

**Para que serve:** declarar as zonas que **você** administra (autoritativo) ou zonas de stub/forward específicas do ambiente.

**Como funciona:** cada bloco `zone "nome" { ... };` associa um domínio a um arquivo de zona (master) ou a servidores mestres (slave).

```
// /etc/bind/named.conf.local

// Zona direta (nome → IP)
zone "exemplo.com" {
    type primary;                    // master (BIND moderno); em configs antigas: master
    file "/etc/bind/db.exemplo.com";  // arquivo com os registros
    allow-transfer { 10.0.0.11; };   // quem pode fazer AXFR (secundários)
};

// Zona reversa (IP → nome) — exemplo rede 10.0.0.0/24
zone "0.0.10.in-addr.arpa" {
    type primary;
    file "/etc/bind/db.10.0.0";
};

// Exemplo de secundário (slave) — recebe cópia do primary
// zone "exemplo.com" {
//     type secondary;               // slave em sintaxe antiga
//     file "db.exemplo.com";
//     masters { 10.0.0.10; };
// };
```

| Configuração | O que é / para que serve |
|--------------|--------------------------|
| `zone "nome"` | Nome da zona (domínio ou zona reversa `in-addr.arpa`) |
| `type primary` | Este servidor é autoritativo e edita o arquivo da zona |
| `type secondary` | Este servidor espelha a zona a partir de um `masters` |
| `file` | Caminho do arquivo de zona no disco |
| `allow-transfer` | Quem pode transferir a zona inteira (AXFR/IXFR) — restringir aos slaves |
| `masters` | IPs do servidor primary (só em `secondary`) |

---

### 4. `named.conf.default-zones` — zonas padrão do sistema

**Para que serve:** zonas “de fábrica” do pacote Debian/Ubuntu: localhost, broadcast, root hints, etc.

**Como funciona:** o BIND já sobe com zonas locais essenciais e com a dica dos root servers, sem você declarar tudo na mão.

```
// /etc/bind/named.conf.default-zones  (resumo típico)

zone "." {
    type hint;
    file "/usr/share/dns/root.hints";   // ou /etc/bind/db.root
};

zone "localhost" {
    type primary;
    file "/etc/bind/db.local";
};

zone "127.in-addr.arpa" {
    type primary;
    file "/etc/bind/db.127";
};

zone "0.in-addr.arpa" {
    type primary;
    file "/etc/bind/db.0";
};

zone "255.in-addr.arpa" {
    type primary;
    file "/etc/bind/db.255";
};
```

| Zona / tipo | Para que serve |
|-------------|----------------|
| `"."` + `type hint` | Lista dos root servers (*root hints*) usada na resolução recursiva |
| `localhost` / `127.in-addr.arpa` | Resolução local de `localhost` ↔ `127.0.0.1` |
| `0` / `255.in-addr.arpa` | Zonas especiais de rede (broadcast / “this network”) |

Em geral **não se edita** esse arquivo; atualizações vêm do pacote.

---

### 5. Arquivo de zona — registros DNS

**Para que serve:** mapa concreto nome ↔ dados (IP, mail, alias, texto…). Referenciado pelo `file` em `named.conf.local`.

**Como funciona:** o BIND carrega o arquivo, valida o SOA/serial e responde de forma autoritativa pelos nomes da zona. Após editar, aumente o **serial** e recarregue (`rndc reload` ou `systemctl reload bind9`).

```
; /etc/bind/db.exemplo.com
; Comentários começam com ;

$TTL 3600
@   IN  SOA ns1.exemplo.com. admin.exemplo.com. (
        2026092201  ; serial  (YYYYMMDDnn — aumente a cada alteração)
        3600        ; refresh (slave tenta atualizar)
        900         ; retry   (se refresh falhar)
        604800      ; expire  (slave desiste se não alcançar o master)
        300         ; negative cache / minimum TTL
)

@       IN  NS      ns1.exemplo.com.
@       IN  NS      ns2.exemplo.com.
@       IN  MX  10  mail.exemplo.com.
@       IN  A       10.0.0.20
@       IN  TXT     "v=spf1 mx -all"

ns1     IN  A       10.0.0.10
ns2     IN  A       10.0.0.11
www     IN  A       10.0.0.20
mail    IN  A       10.0.0.21
app     IN  CNAME   www.exemplo.com.
```

| Elemento / registro | O que é |
|---------------------|---------|
| `$TTL` | Tempo de vida padrão (segundos) das respostas em cache |
| `@` | Atalho para o nome da zona (ex.: `exemplo.com.`) |
| `SOA` | Start of Authority — metadados da zona (serial, tempos de sync) |
| `NS` | Nameserver autoritativo da zona |
| `A` | Nome → IPv4 |
| `AAAA` | Nome → IPv6 |
| `CNAME` | Alias de um nome para outro |
| `MX` | Servidor de e-mail (prioridade + hostname) |
| `TXT` | Texto livre (SPF, DKIM, verificações, etc.) |
| `PTR` | Em zona reversa: IP → nome (inverso do A) |

#### Como montar o nome da zona reversa (IPv4)

A consulta inverte os octetos do IP e anexa `.in-addr.arpa`:

```text
IP:      10.0.0.20
         |  |  |  |
         v  v  v  v
Zona /24 →  0.0.10.in-addr.arpa     (rede 10.0.0.0/24)
Registro →  20  IN  PTR  www.exemplo.com.
Consulta →  20.0.0.10.in-addr.arpa
```

Exemplo: `172.16.204.246` → consulta `246.204.16.172.in-addr.arpa` (zona típica `/24`: `204.16.172.in-addr.arpa`).

#### Ponto final em FQDN

Em arquivos de zona, nome completo **deve terminar com ponto** (`.`).

- Correto: `ns1.exemplo.com.`
- Errado: `ns1.exemplo.com` — o BIND concatena o nome da zona, virando algo como `ns1.exemplo.com.0.0.10.in-addr.arpa.`

Zona reversa (exemplo mínimo):

```
; /etc/bind/db.10.0.0
$TTL 3600
@   IN  SOA ns1.exemplo.com. admin.exemplo.com. (
        2026092201 3600 900 604800 300
)
@       IN  NS  ns1.exemplo.com.
10      IN  PTR ns1.exemplo.com.    ; 10.0.0.10
20      IN  PTR www.exemplo.com.    ; 10.0.0.20
```

---

### 6. `rndc` — controle em tempo de execução

**O que é:** o `rndc` (*Remote Name Daemon Controller*) é o **cliente** de linha de comando que envia ordens ao daemon `named` pelo canal de controle (porta **953**, em geral só em `127.0.0.1`). **Não** é o servidor DNS — o servidor é o `named`.

**Para que serve:** recarregar configuração e zonas, limpar cache e ver status **sem** parar o processo (consultas na porta 53 continuam). No Docker isso evita `docker compose restart` só para aplicar uma zona.

**Como funciona:** o cliente autentica-se com a mesma chave que o `named` carregou (`rndc.key`). Sem `include` da chave e sem bloco `controls` no `named.conf` (nível raiz), o `rndc` falha mesmo com o arquivo no disco.

#### O que precisa existir

1. Arquivo de chave (não publique o `secret` no Git/docs):
   - No container: `/etc/bind/rndc.key`
   - No host deste ambiente: **`/opt/docker/bind9/config/rndc.key`** (volume `config` → `/etc/bind`)
2. No `named.conf` do **mesmo volume**, no **nível raiz** — **depois** do `};` que fecha o `logging`, nunca dentro dele:

```
include "/etc/bind/rndc.key";

controls {
    inet 127.0.0.1 port 953
        allow { 127.0.0.1; }
        keys { "rndc-key"; };
};
```

O nome em `keys { "rndc-key"; }` deve ser **igual** ao `key "..."` do `rndc.key`. Se o arquivo tiver outro nome, use esse no `controls`.

**Onde editar (Docker deste servidor):** `/opt/docker/bind9/config/named.conf` e `/opt/docker/bind9/config/rndc.key`. O `named` e o `docker exec bind9 rndc` leem `/etc/bind` **do container**, que é essa pasta do host — não o `/etc/bind` do Debian (a menos que o compose monte exatamente isso).

No pacote BIND nativo (sem Docker), o Debian/Ubuntu costuma já trazer `rndc.key` + `controls` em `/etc/bind`.

Comandos úteis (no host nativo; no Docker prefixe com `docker exec bind9`):

```
rndc status
rndc reload
rndc reload exemplo.com
rndc flush
rndc flushname exemplo.com
```

| Comando | Efeito |
|---------|--------|
| `rndc status` | Estado do servidor (`server is up and running` = ok) |
| `rndc reload` | Recarrega configuração e zonas |
| `rndc reload zona` | Recarrega só uma zona |
| `rndc flush` | Limpa toda a cache de resolução |
| `rndc flushname nome` | Limpa a cache só daquele nome |

---

### Ordem mental de edição

1. Opções globais → `named.conf.options`
2. Declarar zona → `named.conf.local`
3. Criar/editar registros → `db.*`
4. Validar → `named-checkconf` e `named-checkzone exemplo.com /etc/bind/db.exemplo.com`
5. Aplicar → `rndc reload` (ou `systemctl reload bind9`)

## Instalar o BIND 9 com Docker

Neste repositório, o modelo de instalação em container fica em `DNS/DNS-files/` (imagem `ubuntu/bind9`). Os arquivos de configuração ficam no **host**; o BIND só enxerga os caminhos **dentro do container**.

Pré-requisito: Docker Engine + plugin Compose.

### Ideia do setup

| No host | No container | Função |
|---------|--------------|--------|
| `/opt/docker/bind9/config` (compose em produção) ou `/etc/bind` (modelo `DNS-files`) | `/etc/bind` | `named.conf*`, `rndc.key`, zonas padrão (`db.local`, etc.) |
| `/opt/docker/bind9/cache` | `/var/cache/bind` | Working directory, zonas autoritativas, RPZ, chaves DNSSEC |
| `/opt/docker/bind9/records` | `/var/lib/bind` | Reserva no estilo Debian (este modelo não a usa nos `file` das zonas) |
| `/opt/docker/bind9/logs` ou `./logs` | `/var/log/named` | `bind.log`, `security.log`, `dnssec.log` |

No servidor atual o inspect típico é `/opt/docker/bind9/config -> /etc/bind`. O `rndc.key` e o `named.conf` devem ficar em **`config/`**, não no `/etc/bind` do host (esse path **não** entra no container). Confira com `docker inspect bind9` se o compose divergir.

O BIND **não cria pastas**. Se o diretório não existir no container (via volume), aparece `file not found` mesmo com o arquivo no host.

### 1. Criar pastas no host

```bash
mkdir -p /etc/bind
mkdir -p /opt/docker/bind9/cache /opt/docker/bind9/records
mkdir -p /opt/docker/bind9/logs   # ou logs/ ao lado do compose
chmod 755 /etc/bind
chmod 777 /opt/docker/bind9/cache /opt/docker/bind9/records
# pasta de logs precisa ser gravável pelo named
chmod 777 /opt/docker/bind9/logs
```

### 2. Copiar a configuração de referência

Os `named.conf*` de exemplo estão em `DNS/DNS-files/`. No servidor, o BIND lê **`/etc/bind`**, não a pasta do Git:

```bash
# Exemplo: a partir da pasta do repositório
cp DNS/DNS-files/named.conf \
   DNS/DNS-files/named.conf.options \
   DNS/DNS-files/named.conf.local \
   DNS/DNS-files/named.conf.default-zones \
   /etc/bind/

# Zonas padrão (localhost / 127 / 0 / 255) — use as de DNS-files/bind/ ou as do pacote
cp DNS/DNS-files/bind/db.local \
   DNS/DNS-files/bind/db.127 \
   DNS/DNS-files/bind/db.0 \
   DNS/DNS-files/bind/db.255 \
   /etc/bind/

chmod 644 /etc/bind/*.conf /etc/bind/db.*
```

Ajuste ACLs, IPs e zonas em `/etc/bind/named.conf.options` e `named.conf.local` antes de subir. O mapeamento **deste ambiente** (IPs, domínios, tabelas host ↔ container) continua em `DNS/DNS-files/README.md`.

### Layout das zonas em `/var/cache/bind`

No modelo deste repositório, os `file` em `named.conf.local` apontam para caminhos **dentro do container** (`/var/cache/bind/...`). No host isso é `/opt/docker/bind9/cache/...`.

Padrão de pastas (genérico):

```text
/opt/docker/bind9/cache/                    →  /var/cache/bind
├── master-rev/
│   └── <zona-reversa>/
│       ├── <arquivo>.rev                   # registros PTR
│       └── keys/                           # chaves DNSSEC da zona (se houver)
├── master-aut/
│   └── <dominio>/
│       ├── <dominio>.hosts                 # zona direta (A, MX, TXT, ...)
│       └── keys/
└── block/
    └── db.blacklist.zone                   # RPZ (blacklist)
```

| Pasta | Uso |
|-------|-----|
| `master-rev/` | Zonas reversas (`in-addr.arpa` / `ip6.arpa`) |
| `master-aut/` | Zonas diretas (nome → IP) |
| `block/` | Zona RPZ usada pelo `response-policy` |
| `.../keys/` | Chaves DNSSEC daquela zona (`key-directory` no `.local`) |

**Importante:** o BIND sobe mesmo se um arquivo de zona faltar, mas a zona correspondente **não carrega** (`file not found` no log). Zona comentada no `.local` não é lida — o arquivo pode existir no disco e ainda assim não vale até descomentar o bloco.

#### RPZ (Response Policy Zone)

A blacklist costuma ter **duas** peças:

1. Declaração da zona em `named.conf.local` (`zone "blacklist.zone" { ... file "..."; }`)
2. Ativação em `named.conf.options` com `response-policy { zone "blacklist.zone" ...; }`

Sem o arquivo apontado no `file`, o daemon sobe, mas a política RPZ falha ao carregar essa zona.

### Permissões no host

O container sobe o `named` como `root` (`BIND9_USER: root`) e com `apparmor:unconfined`. Mesmo assim os bind-mounts precisam ser legíveis/graváveis conforme o uso:

```bash
# Config e zonas padrão — leitura
chmod 644 /etc/bind/*.conf /etc/bind/db.*

# Arquivos de zona sob cache — leitura (ajuste o glob às suas pastas)
chmod 644 /opt/docker/bind9/cache/master-rev/*/*.rev 2>/dev/null || true
chmod 644 /opt/docker/bind9/cache/block/db.blacklist.zone 2>/dev/null || true

# Diretórios de trabalho — escrita (journals, DNSSEC, logs)
chmod 777 /opt/docker/bind9/cache /opt/docker/bind9/records
chmod 777 logs   # pasta montada em /var/log/named (ao lado do compose)
```

- `/etc/bind` pode ficar com arquivos `644`
- `cache` precisa de escrita (working directory, journals, DNSSEC)
- `logs` precisa de escrita; **não** é necessário criar os `.log` na mão — monte a pasta vazia e gravável

### 3. Modelo do `docker-compose.yml`

Baseado em `DNS/DNS-files/docker-compose.yml`. Coloque o arquivo em `/opt/docker/bind9/` (ou outra pasta de compose) e alinhe o volume de logs:

```yaml
services:
  bind9:
    image: ubuntu/bind9:latest
    container_name: bind9
    restart: always
    environment:
      TZ: America/Sao_Paulo
      BIND9_USER: root
    command: ["-4", "-g"]
    ports:
      - "53:53/tcp"
      - "53:53/udp"
    volumes:
      - /etc/bind:/etc/bind
      - /opt/docker/bind9/cache:/var/cache/bind
      - /opt/docker/bind9/records:/var/lib/bind
      - ./logs:/var/log/named
    security_opt:
      - apparmor:unconfined
```

No ambiente em produção o compose costuma montar **`/opt/docker/bind9/config:/etc/bind`** (e volumes extras `master-rev`, `block`). Nesse caso `named.conf` e `rndc.key` ficam em `config/`, não em `/etc/bind` do host.

| Item do compose | Para que serve |
|-----------------|----------------|
| `image: ubuntu/bind9:latest` | Imagem oficial Ubuntu com BIND 9 |
| `container_name: bind9` | Nome fixo do container (útil para `docker logs` / watchdog) |
| `restart: always` | Sobe de novo se o host reiniciar ou o container cair |
| `TZ` | Fuso horário dos logs |
| `BIND9_USER: root` | Evita `permission denied` nos `.conf` montados do host |
| `command: ["-4", "-g"]` | `-g` = foreground (obrigatório no Docker) + log no stderr; `-4` = **só IPv4** (ver nota abaixo) |
| `ports` `53/tcp` e `53/udp` | Porta DNS no host |
| volume `/etc/bind` | Configuração e zonas padrão |
| volume `cache` | `directory` do named + arquivos de zona (`file "/var/cache/bind/..."`) |
| volume `records` | `/var/lib/bind` (reserva) |
| volume `./logs` | Destino dos `file` do bloco `logging` no `named.conf` |
| `apparmor:unconfined` | Evita bloqueio do AppArmor em mounts/escrita neste setup |

> **IPv4 vs IPv6 no `command`:**  
> - `command: ["-4", "-g"]` — desliga sockets IPv6. Use só se o DNS for **IPv4-only**.  
> - `command: ["-g"]` — IPv4 e IPv6. Necessário se houver `listen-on-v6`, zona `ip6.arpa` ou clientes consultando o DNS por IPv6.  
> O `docker-compose.yml` em `DNS-files` hoje usa `-4`. Se o ambiente atender o bloco IPv6, troque para só `-g` e mantenha `listen-on-v6` coerente no `.options`.

{.is-warning}

Se o `systemd-resolved` no host já ocupar a porta 53, publique só no IP do servidor, por exemplo:

```yaml
ports:
  - "203.0.113.10:53:53/tcp"
  - "203.0.113.10:53:53/udp"
```

### 4. Subir e validar

```bash
cd /opt/docker/bind9
docker compose up -d --force-recreate
docker logs -f bind9
```

Sinais de sucesso no log: `all zones loaded` e `running` (sem `exiting (due to fatal error)`).

Testes:

```bash
dig @127.0.0.1 google.com
dig @IP_DO_SERVIDOR google.com

docker exec bind9 ls -la /etc/bind
docker exec bind9 ls -la /var/cache/bind
docker exec bind9 ls -ld /var/log/named
```

### 5. Operação no Docker (runbook)

Comandos abaixo assumem `container_name: bind9`.

#### Habilitar e usar o `rndc` no Docker

O cliente roda **dentro** do container (`docker exec`). A chave e o `named.conf` estão no volume de config do host.

```bash
# A chave precisa existir no volume montado em /etc/bind (não no /etc/bind do host)
ls -la /opt/docker/bind9/config/rndc.key
docker exec bind9 ls -la /etc/bind/rndc.key

# Gerar chave no volume, se ainda não houver (depois: include + controls no named.conf)
docker exec bind9 rndc-confgen -a

# Validar sintaxe (include/controls no nível raiz)
docker exec bind9 named-checkconf /etc/bind/named.conf

# O named só lê a chave nova após restart
cd /opt/docker/bind9
docker compose restart

docker exec bind9 rndc status
```

Acerto: o `rndc status` termina com `server is up and running`. Depois disso, `reload` / `flush` (abaixo) bastam; não precisa reiniciar o container para cada zona.

| Erro | Causa típica |
|------|----------------|
| `neither .../rndc.conf nor .../rndc.key was found` | Arquivo no `/etc/bind` do host; o volume é `/opt/docker/bind9/config` |
| `connection to remote host closed` | Chave diferente da que o `named` carregou, ou falta `controls` — reinicie após alinhar |
| `unknown option 'key'` / `'controls'` | `include`/`controls` colocados **dentro** do `logging { }` |
| `loading configuration: failure` | `named-checkconf` no host (`config/named.conf`) e corrija antes de subir |

Não grave o `secret` do `rndc.key` na documentação.

#### Validar sintaxe (antes de aplicar)

```bash
docker exec bind9 named-checkconf /etc/bind/named.conf

docker exec bind9 named-checkzone 0.0.10.in-addr.arpa \
  /var/cache/bind/master-rev/0.0.10.in-addr.arpa/10.0.0.rev
```

#### Recarregar e limpar cache

```bash
docker exec bind9 rndc status
docker exec bind9 rndc reload
docker exec bind9 rndc reload 0.0.10.in-addr.arpa

# Cache: tudo ou só um nome
docker exec bind9 rndc flush
docker exec bind9 rndc flushname exemplo.com
```

Reinício do container (só quando mudar portas/volumes/compose):

```bash
cd /opt/docker/bind9
docker compose restart
# ou
docker compose down && docker compose up -d
```

Logs:

```bash
docker logs -f --tail 100 bind9
```

#### Procedimento: adicionar um PTR

1. Edite o `.rev` da zona em `/opt/docker/bind9/cache/master-rev/<zona>/`.
2. **Incremente o serial** no SOA (ex.: `YYYYMMDDnn`).
3. Adicione o registro (último octeto → FQDN **com ponto**):

```bind
50      IN  PTR host50.exemplo.com.
```

4. Valide e recarregue:

```bash
docker exec bind9 named-checkzone 0.0.10.in-addr.arpa \
  /var/cache/bind/master-rev/0.0.10.in-addr.arpa/10.0.0.rev
docker exec bind9 rndc reload 0.0.10.in-addr.arpa
```

5. Teste:

```bash
dig @127.0.0.1 -x 10.0.0.50 +short
```

#### Procedimento: bloquear domínio na RPZ

1. Edite `/opt/docker/bind9/cache/block/db.blacklist.zone`.
2. Incremente o **serial**.
3. Adicione o domínio (e wildcards, se quiser) — exemplo que força NXDOMAIN:

```bind
site-falso.com          CNAME .
*.site-falso.com        CNAME .
```

(Se a política no `.options` for `policy CNAME localhost`, o efeito pode ser redirecionar em vez de NXDOMAIN — alinhe o arquivo à política.)

4. Recarregue e teste:

```bash
docker exec bind9 rndc reload blacklist.zone
dig @127.0.0.1 site-falso.com
```

#### Testes de diagnóstico (`dig` e `nslookup`)

Forma geral — troque o IP pelo DNS que está testando:

```bash
dig @192.168.1.150 google.com
dig @172.16.204.246 google.com

nslookup google.com 192.168.1.150
nslookup tryhackme.com 172.16.204.246

# Reverso
dig @172.16.204.246 -x 172.16.204.246

# Trace / sem recursão
dig @172.16.204.246 google.com +trace
dig @172.16.204.246 google.com +norecurse
```

Use **apenas o nome DNS** (`tryhackme.com`), nunca a URL completa (`https://...`).

---

##### Acerto — servidor alcançável e nome encontrado (`NOERROR`)

`dig` — pontos de atenção: `status: NOERROR`, flag `ra` (recursion available), seção `ANSWER` com o IP:

```text
$ dig @172.16.204.246 google.com

; <<>> DiG ... <<>> @172.16.204.246 google.com
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 48264
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 1

;; QUESTION SECTION:
;google.com.			IN	A

;; ANSWER SECTION:
google.com.		294	IN	A	142.250.78.142

;; Query time: 1 msec
;; SERVER: 172.16.204.246#53(172.16.204.246) (UDP)
```

| Campo | Significado |
|-------|-------------|
| `status: NOERROR` | Consulta ok; houve resposta útil |
| `flags: ... ra` | Servidor aceitou recursão (para clientes autorizados) |
| `ANSWER SECTION` | Registro encontrado (ex.: A → IP) |
| `SERVER: ...#53` | Qual DNS respondeu |

`nslookup` — resposta não autoritativa típica de resolver com cache/recursão:

```text
$ nslookup tryhackme.com 172.16.204.246
Server:		172.16.204.246
Address:	172.16.204.246#53

Non-authoritative answer:
Name:	tryhackme.com
Address: 64.239.123.129
Name:	tryhackme.com
Address: 64.239.109.129
```

`Non-authoritative answer` é **normal** em DNS recursivo: a resposta veio da cache ou da hierarquia, não porque este servidor seja o NS oficial do domínio.

---

##### Erro — DNS inacessível (timeout / sem servidor)

Serviço parado, IP errado, firewall bloqueando UDP/TCP 53, ou porta 53 não publicada no Docker:

```text
$ dig @192.168.1.150 google.com
;; communications error to 192.168.1.150#53: timed out
;; communications error to 192.168.1.150#53: timed out
;; communications error to 192.168.1.150#53: timed out

; <<>> DiG ... <<>> @192.168.1.150 google.com
;; no servers could be reached
```

| Sintoma | Interpretação |
|---------|----------------|
| `timed out` | Pacote não chegou ou não houve resposta a tempo |
| `no servers could be reached` | Nenhum DNS alvo respondeu |
| `connection refused` | Host alcançável, mas nada escuta na 53 |

Nesse caso o problema é **conectividade / serviço**, não o nome do domínio.

---

##### Erro — DNS ok, mas o nome não existe (`NXDOMAIN`)

Domínio inexistente **ou** nome malformado. Exemplo clássico: passar URL com `https://` e barra — isso **não** é um nome DNS válido:

```text
$ nslookup https://tryhackme.com/ 172.16.204.246
Server:		172.16.204.246
Address:	172.16.204.246#53

** server can't find https://tryhackme.com/: NXDOMAIN
```

Correto:

```bash
nslookup tryhackme.com 172.16.204.246
dig @172.16.204.246 tryhackme.com
```

No `dig`, o mesmo caso aparece como `status: NXDOMAIN` (sem `ANSWER SECTION` útil).

| Status / mensagem | Significado |
|-------------------|-------------|
| `NXDOMAIN` | O nome consultado **não existe** na hierarquia (ou foi bloqueado por RPZ com política NXDOMAIN) |
| `server can't find ...: NXDOMAIN` | Equivalente no `nslookup` |

---

##### Outros status úteis do `dig`

| `status` | O que indica |
|----------|----------------|
| `NOERROR` | Sucesso (pode ter resposta vazia em alguns tipos de query) |
| `NXDOMAIN` | Nome inexistente |
| `SERVFAIL` | Falha no servidor (zona quebrada, DNSSEC, timeout ao subir a hierarquia, misconfig) |
| `REFUSED` | Servidor recusou a query (ACL: recursão/consulta não permitidas para o seu IP) |
| `FORMERR` | Query malformada |

Exemplos de leitura rápida:

```bash
# Ver só o status
dig @172.16.204.246 google.com +noall +comments

# Ver só a resposta (IPs)
dig @172.16.204.246 google.com +short
```

---

##### Resumo rápido

| Resultado | Exemplo | Ação típica |
|-----------|---------|-------------|
| Acerto | `NOERROR` + `ANSWER` com IP | DNS e nome ok |
| Sem DNS | `timed out` / `no servers could be reached` | Checar container, IP, firewall, porta 53 |
| Nome errado / inexistente | `NXDOMAIN` | Corrigir o nome (sem `https://`); ou criar o registro / ver RPZ |
| Recursão negada | `REFUSED` | Seu IP fora de `allow-recursion` / ACL |
| Falha interna | `SERVFAIL` | Ver `docker logs bind9` e zonas |

Inventário de zonas/IPs **deste ambiente**: `DNS/DNS-files/README.md`.

### 6. Erros frequentes

| Log / sintoma | Causa provável |
|---------------|----------------|
| `connection refused` na porta 53 | Container parado ou porta 53 não publicada / ocupada |
| `named.conf.options: permission denied` | Arquivo `600` / usuário sem leitura nos `.conf` |
| `directory '/var/cache/bind' is not writable` | `/opt/docker/bind9/cache` sem permissão de escrita |
| `named.conf:...: file not found` (include) | Falta arquivo em `/etc/bind` (ex.: `named.conf.local`) |
| `checking logging configuration failed: file not found` | Falta `/var/log/named` **no container** (volume `./logs`) |
| `blacklist.zone ... file not found` | Falta o arquivo em `cache/block/` apontado no `.local` |
| zona `... file not found` | Falta o `file` sob `/opt/docker/bind9/cache/...` |
| `automatic empty zone: ...` | **Informativo** — não é erro; o BIND cria zonas vazias RFC automaticamente |

### Referência no repositório

| Caminho | Conteúdo |
|---------|----------|
| `DNS/DNS-files/docker-compose.yml` | Compose usado neste modelo |
| `DNS/DNS-files/named.conf*` | Config de referência (copiar para `/etc/bind`) |
| `DNS/DNS-files/bind/` | Cópia auxiliar (`db.*`, backups, `rndc.key`, etc.) |
| `DNS/DNS-files/README.md` | Mapeamento detalhado host ↔ container e zonas deste ambiente |
| `DNS/bind9-watchdog.sh` | Watchdog opcional (reinicia se o DNS no container parar de responder) |