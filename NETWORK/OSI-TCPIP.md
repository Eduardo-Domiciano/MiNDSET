# Modelo OSI e pilha TCP/IP

Dois modelos descrevem a mesma ideia: uma mensagem desce camadas no remetente, atravessa a rede e sobe as camadas no destinatário. Cada camada cumpre um trabalho e acrescenta (ou retira) um pedaço da mensagem.

O **modelo OSI** é um modelo de referência, publicado pela ISO (ISO/IEC 7498). Ele tem sete camadas e serve para nomear funções, comparar protocolos e localizar uma falha. Não é o desenho que o sistema operacional implementa linha por linha.

A **pilha TCP/IP** é o que a Internet usa. O nome junta os dois protocolos centrais: o **TCP**, que organiza o fluxo de dados entre processos, e o **IP**, que endereça e encaminha pacotes entre redes. No modelo clássico há quatro camadas. Elas cobrem as mesmas funções das sete do OSI, com as três de cima fundidas numa só e as duas de baixo fundidas em outra.

Um aparelho não fala com outro “porque ambos implementam o OSI”. Eles se falam porque usam os **mesmos protocolos** (Ethernet, IP, TCP, HTTP, e assim por diante). O OSI é o mapa. O TCP/IP é a estrada.

## As sete camadas

A numeração oficial começa embaixo. A camada 1 é a física. A camada 7 é a aplicação. Um mnemônico de cima para baixo, da aplicação até a física: *Anxious Pale Shakespeare Treated Nervous Drunk Patiently* (Application, Presentation, Session, Transport, Network, Data Link, Physical).

| Camada | Nome | Função em uma frase | PDU | Exemplos |
|--------|------|---------------------|-----|----------|
| 7 | Aplicação | O programa usa a rede | Dados | HTTP, DNS, SMTP, SSH |
| 6 | Apresentação | Formato comum dos dados | Dados | Codificação, compressão, cifra no modelo |
| 5 | Sessão | Diálogo entre as partes | Dados | Abertura, sincronismo, encerramento no modelo |
| 4 | Transporte | Processo fala com processo | Segmento (TCP) ou datagrama (UDP) | TCP, UDP |
| 3 | Rede | Host fala com host, entre redes | Pacote | IPv4, IPv6, ICMP |
| 2 | Enlace | Entrega no mesmo enlace físico | Quadro (*frame*) | Ethernet, Wi-Fi, PPP |
| 1 | Física | O sinal no meio | Bits | Cabo, fibra, rádio |

**PDU** (*Protocol Data Unit*) é o nome da unidade naquela camada. Nas camadas 7, 6 e 5 o nome continua **dados**. Daí para baixo o nome muda.

```text
 7  Aplicação        dados
 6  Apresentação     dados
 5  Sessão           dados
 4  Transporte       segmento TCP  |  datagrama UDP
 3  Rede             pacote IP
 2  Enlace           quadro  +  trailer
 1  Física           bits
```

Quem costuma agir em cada altura:

| Altura | Equipamento típico | O que ele olha |
|--------|--------------------|----------------|
| 7 a 5 | O próprio host (programas) | Conteúdo e sessão da aplicação |
| 4 | Sistema operacional do host | Porta, TCP ou UDP |
| 3 | Roteador | Endereço IP e rota |
| 2 | Switch | Endereço MAC |
| 1 | Cabo, fibra, rádio, hub | Sinal |

Um switch de verdade às vezes olha IP, e um roteador doméstico também faz NAT e Wi-Fi. O mapa acima é o lugar **principal** de cada função, não uma lei do gabinete.

## Camada 7 — Aplicação

A camada de aplicação oferece à programa a possibilidade de usar a rede. O navegador, o cliente de e-mail, o SSH e o servidor web não inventam sozinhos como pedir um recurso: eles usam um protocolo desta camada.

Não é a janela gráfica. Um servidor sem tela também tem camada de aplicação. A interface é o protocolo: HTTP para a Web, SMTP para enviar e-mail, IMAP para ler, DNS para traduzir nome em IP, SSH para administrar, FTP e SFTP para arquivos. O detalhe de HTTP e HTTPS está em `HTTP.md`. O DNS está em `BIND9-DNS.md`.

Quando o programa entrega os dados, eles descem para a apresentação.

## Camada 6 — Apresentação

No modelo OSI, esta camada é a tradutora. Programas diferentes podem representar o mesmo conteúdo de formas diferentes. A apresentação converte para um formato que o outro lado entende. Também é aqui que o modelo coloca compressão e criptografia.

Na pilha real, boa parte disso mora dentro da aplicação ou numa biblioteca entre a aplicação e o transporte. O HTTPS é HTTP sobre TLS. O TLS cifra e autentica, mas no sistema operacional ele não aparece como uma “camada 6” separada do navegador. Para o estudo do OSI, o lugar pedagógico da cifra é a apresentação. Para o diagnóstico de um site, TLS se observa entre o HTTP e o TCP.

## Camada 5 — Sessão

No modelo, a sessão abre, mantém e encerra o diálogo entre as duas partes. Ela separa conversas para que os dados não se misturem, sincroniza a troca e pode retomar de um ponto combinado se a comunicação cair. Duas abas do navegador pedindo páginas ao mesmo tempo são o exemplo clássico de sala de aula: duas sessões, dois fluxos, sem embaralhar a resposta.

Na pilha TCP/IP esse trabalho se divide. A conexão estável é o TCP, na camada de transporte. A “sessão” que o usuário percebe (estar logado, manter várias abas) é a aplicação, com cookie, token ou várias conexões TCP ao mesmo tempo. Cada conexão TCP é um soquete: endereço IP local, porta local, IP remoto e porta remota.

## Camada 4 — Transporte

Aqui a conversa deixa de ser “este computador com aquele” e passa a ser “este processo com aquele processo”. O número que distingue os processos é a **porta**. O HTTP padrão usa a 80, o HTTPS a 443, o DNS a 53, o SSH a 22.

A camada escolhe o protocolo de transporte e corta a mensagem em pedaços. No TCP o pedaço se chama **segmento**. No UDP se chama **datagrama**.

### TCP

O **TCP** (*Transmission Control Protocol*) cria uma conexão antes de enviar dados úteis e trata o fluxo como um canal confiável:

- os segmentos saem numerados e são remontados na ordem;
- o destinatário confirma o que chegou;
- o que se perde é retransmitido;
- o emissor segura o ritmo para não afogar o receptor (controle de fluxo) nem a rede (controle de congestionamento).

Serve para arquivo, página web, e-mail e qualquer troca em que faltar um pedaço estrague o resultado.

Isso é confiabilidade, não sigilo. O TCP não cifra. Quem cifra o HTTPS é o TLS, por cima do TCP.

#### Aperto de mão em três passos

Antes dos dados, o TCP faz o *three-way handshake*. SYN e ACK são **flags** do cabeçalho TCP, não um “bit solto” fora do segmento. Cada lado também escolhe um número de sequência.

```text
 Cliente                         Servidor
    |                                |
    |  SYN        "quero conectar"   |
    |------------------------------->|
    |                                |
    |  SYN/ACK    "pode, e eu também"|
    |<-------------------------------|
    |                                |
    |  ACK        "combinado"        |
    |------------------------------->|
    |                                |
    |  daqui em diante, dados        |
```

1. O cliente envia **SYN** (*synchronize*).
2. O servidor responde **SYN/ACK**: aceita o SYN do cliente e manda o seu.
3. O cliente devolve **ACK** (*acknowledgement*). A conexão está estabelecida.

O encerramento educado usa a flag **FIN**, em geral em quatro passos (cada lado avisa que não tem mais nada para enviar e confirma o aviso do outro). Uma ruptura abrupta usa **RST**.

### UDP

O **UDP** (*User Datagram Protocol*) não abre conexão, não numera para remontar uma conversa e não pede retransmissão. Ele entrega o datagrama à porta de destino e segue. Há uma soma de verificação para detectar corrupção; se falhar, o datagrama é descartado, não repetido.

Chamada de voz, vídeo ao vivo, jogos e consultas DNS usam UDP quando chegar atrasado é pior do que perder um pedaço. “Se não chegou, o problema é de quem recebe” descreve a falta de garantia. Não descreve segurança: UDP também não cifra.

| | TCP | UDP |
|---|-----|-----|
| Conexão antes dos dados | Sim, handshake | Não |
| Ordem e retransmissão | Sim | Não |
| Unidade | Segmento | Datagrama |
| Cabeçalho típico | 20 bytes, sem opções | 8 bytes |
| Uso comum | Web, e-mail, arquivo, SSH | DNS, voz, vídeo, DHCP |

## Camada 3 — Rede

A camada de rede leva o pacote de um host a outro, atravessando redes. O endereço desta camada é lógico: **IPv4** ou **IPv6**. Ele é configurado (ou obtido por DHCP) e pode mudar. Não vem gravado de fábrica como identidade permanente da placa.

O protocolo que carrega o pacote é o **IP**. Roteadores leem o IP de destino, consultam a tabela de rotas e encaminham o pacote ao próximo salto. Protocolos de roteamento, como **OSPF**, **RIP** e **BGP**, servem para os roteadores **montarem** essa tabela. Eles não substituem o IP. ICMP, o protocolo do `ping`, também mora nesta camada.

A escolha do caminho considera, entre outros fatores, o tamanho da rota, o custo configurado, se o enlace está no ar e a política da rede. “O caminho com menos aparelhos”, “o que perde menos pacote” e “o enlace mais rápido” são intuições úteis. O critério real é o que o protocolo de roteamento e o administrador definiram, não uma medição mágica feita pelo pacote.

Forma dos endereços:

- IPv4: 32 bits, escritos em quatro números decimais. Exemplo de documentação: `192.0.2.1`.
- IPv6: 128 bits, escritos em hexadecimal separado por dois-pontos. Exemplo de documentação: `2001:db8::1`.

O IPv6 não é uma camada nova. É outro protocolo da mesma camada de rede.

## Camada 2 — Enlace

O enlace entrega o quadro no **mesmo** segmento de rede: um cabo, uma VLAN, uma célula Wi-Fi. O endereço é o **MAC** (*Media Access Control*), da placa de rede (NIC).

Um MAC tem 48 bits, em geral escritos como seis pares hexadecimais: `00:1a:2b:3c:4d:5e`. O fabricante grava um endereço na placa. O sistema pode **apresentar outro** no lugar dele. Isso é falsificação (*spoofing*) e é comum em virtualização e em teste. “Gravado de fábrica” e “impossível de trocar na transmissão” não são a mesma frase.

O quadro Ethernet leva, entre outros campos, MAC de destino, MAC de origem e o pacote IP como carga. No **final** vai o trailer **FCS** (*Frame Check Sequence*), uma soma que detecta corrupção acidental. Se o FCS não fecha, o quadro é descartado. Quem intercepta o quadro no caminho pode alterá-lo e **recalcular** o FCS. O trailer não é assinatura criptográfica e não impede adulteração proposital.

Para enviar um IP nesta rede local, o remetente precisa do MAC correspondente. No IPv4 isso se resolve com **ARP**. No IPv6, com **NDP**. Fora da rede local, o quadro é endereçado ao MAC do gateway (o roteador), e o IP de destino continua sendo o do host final.

A camada de enlace também se descreve em duas subcamadas: **LLC**, que faz a ponte com a rede, e **MAC**, que trata do acesso ao meio e do endereçamento físico.

## Camada 1 — Física

A camada física é o sinal. Bits viram pulso elétrico no cabo de par trançado, luz na fibra ou onda no rádio, e o processo inverso na recepção. Também entram conector, pinagem, taxa de transmissão e codificação da linha.

Cabo Ethernet é o exemplo mais visível, não o único. A placa de rede participa das duas primeiras camadas: o conector e o sinal são físicos; o MAC e o quadro são enlace.

## Encapsulamento

Descer as camadas é **encapsular**. Cada camada acrescenta um cabeçalho na frente daquilo que recebeu. A de enlace acrescenta também o trailer no fim.

```text
Aplicação / apresentação / sessão
        |  dados
        v
Transporte     [ cabeçalho TCP ou UDP | dados ]           segmento ou datagrama
        v
Rede           [ cabeçalho IP | segmento ]                pacote
        v
Enlace         [ cabeçalho MAC | pacote | FCS ]           quadro
        v
Física         bits no meio
```

O cabeçalho de transporte leva portas e, no TCP, números de sequência e flags. O de rede leva IP de origem e de destino. O de enlace leva os MAC deste salto.

Na chegada ocorre o **desencapsulamento**. A física entrega bits, o enlace confere o quadro e tira o cabeçalho MAC, a rede lê o IP, o transporte lê a porta e entrega os dados ao processo certo. Cada aparelho no caminho não sobe até a aplicação. Um switch para na camada 2. Um roteador abre até a camada 3, escolhe a rota e monta um **quadro novo** para o próximo enlace. O pacote IP segue; o MAC muda a cada salto.

## OSI ao lado do TCP/IP

| OSI | TCP/IP (4 camadas) | O que concentra |
|-----|--------------------|-----------------|
| 7 Aplicação | Aplicação | Protocolos que o programa usa |
| 6 Apresentação | Aplicação | |
| 5 Sessão | Aplicação | |
| 4 Transporte | Transporte | TCP e UDP |
| 3 Rede | Internet | IP, ICMP, roteamento |
| 2 Enlace | Interface de rede (acesso à rede) | Ethernet, Wi-Fi e o meio |
| 1 Física | Interface de rede | |

Há quem desenhe o TCP/IP com cinco camadas, separando enlace e física. O conjunto de protocolos é o mesmo. O que muda é o desenho didático.

Encapsular e desencapsular funcionam nos dois mapas. No TCP/IP simplesmente não existem cabeçalhos separados de “apresentação” e de “sessão” no meio do pacote: esse trabalho, quando existe, já vai dentro dos dados da aplicação.

## Uma ida ao site, camada por camada

O navegador pede `https://www.exemplo.com/`.

1. **Aplicação.** O navegador monta um `GET /` HTTP com o cabeçalho `Host`.
2. **Apresentação e sessão, na prática.** O TLS negocia a cifra e autentica o certificado. A “sessão” segura é essa negociação mais a conexão TCP.
3. **Transporte.** O sistema abre TCP com a porta de destino 443. Handshake SYN, SYN/ACK, ACK. Os bytes do TLS e do HTTP seguem em segmentos.
4. **Rede.** O destino lógico é o IP que o DNS devolveu para `www.exemplo.com`. Se esse IP não está na rede local, o próximo salto é o gateway.
5. **Enlace.** ARP (ou a cache ARP) fornece o MAC do gateway. O quadro sai com esse MAC e com o IP final ainda dentro.
6. **Física.** A placa põe os bits no cabo ou no rádio.

No servidor o caminho sobe até o processo que escuta a porta 443. Na volta, as camadas se repetem no sentido inverso.

## Ferramentas

As ferramentas abaixo perguntam a camadas diferentes. Saber qual camada responde evita cobrar de um comando uma informação que ele não busca.

### ping

O `ping` testa se há caminho até um IP, ou até o IP em que um nome resolve, e se esse host responde. Ele usa **ICMP Echo Request** e espera **Echo Reply**. ICMP é da camada de rede, ao lado do IP, não “dentro do TCP”.

```bash
ping -c 4 exemplo.com
man ping
```

`-c 4` limita a quatro sondas. Sem isso, no Linux o `ping` segue até `Ctrl+C`.

Cada linha de resposta mostra o endereço que respondeu, o tamanho, o tempo de ida e volta e o **TTL** que restou. TTL é um contador do cabeçalho IP: cada roteador diminui 1. Chegou a zero, o pacote é descartado. Isso impede um pacote de circular para sempre e é a base do traceroute.

Silêncio não significa, sozinho, que o host está desligado. Firewall pode descartar ICMP e ainda assim aceitar TCP na porta 443.

### traceroute

O `traceroute` lista os roteadores pelos quais o pacote passa até o destino. A sintaxe no Linux é `traceroute`, com **e** no fim.

```bash
traceroute exemplo.com
traceroute -I exemplo.com
man traceroute
```

O comando manda sondas com TTL 1, depois 2, depois 3. O roteador que zerar o TTL devolve ICMP *Time Exceeded*, e assim o caminho aparece salto a salto. No Linux, a sonda padrão do `traceroute` é **UDP** para portas altas, não ICMP. A opção `-I` pede ICMP, parecido com o `tracert` do Windows. Um `* * *` num salto significa que aquela máquina não respondeu a tempo, não que a Internet acabou ali.

### whois

O `whois` consulta o registro do domínio ou do bloco de IP: quem registrou, quais são os servidores de nome publicados, datas e o escritório de registro. Ele **não** é a ferramenta que descobre o IP de um site. Nome para IP é DNS.

```bash
whois exemplo.com
man whois
```

### dig

O **DNS** traduz nome em endereço (e o contrário, no reverso). O computador de casa, em geral, não é um servidor DNS autoritativo. Ele tem um *resolver* que pergunta a um recursivo: o do provedor, o da rede interna, ou um público como os da Cloudflare, do Google ou do OpenDNS. Esse recursivo é que percorre a hierarquia e guarda cache. O funcionamento do servidor está em `BIND9-DNS.md`.

O `dig` faz a pergunta na mão, ao servidor que você indicar.

```bash
dig exemplo.com
dig @1.1.1.1 exemplo.com
dig exemplo.com AAAA
man dig
```

A resposta útil está na seção `ANSWER`: o tipo (A para IPv4, AAAA para IPv6), o TTL e o endereço. `status: NOERROR` com essa seção preenchida é nome encontrado. `NXDOMAIN` é nome inexistente. Tempo esgotado é falha de alcançar o servidor DNS, não falta do nome.

| Ferramenta | Camada que ela exercita | Pergunta |
|------------|-------------------------|----------|
| `ping` | Rede (ICMP) | Este IP responde? |
| `traceroute` | Rede, salto a salto | Por quais roteadores o pacote passa? |
| `dig` | Aplicação (DNS), sobre UDP/53 ou TCP/53 | Qual é o registro deste nome? |
| `whois` | Consulta a um registro, fora da entrega do pacote | Quem publicou este domínio ou este bloco? |
