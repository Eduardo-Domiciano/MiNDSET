# Guia Completo e Definitivo: Fail2ban

O **Fail2ban** é uma das ferramentas de segurança mais populares e eficazes para servidores Linux. Ele atua como um sistema leve de prevenção e mitigação de intrusões (IPS - *Intrusion Prevention System*), protegendo serviços contra ataques automatizados de força bruta (*brute force*), varreduras maliciosas e negação de serviço básica.

---

## 1. O que é e Como Funciona

### 1.1 O Conceito
Em servidores conectados à internet, serviços expostos (como SSH, FTP, servidores web e painéis administrativos) sofrem milhares de tentativas de autenticação inválida todos os dias. 

O Fail2ban opera analisando continuamente os arquivos de log do sistema ou do *systemd journal*. Quando identifica múltiplos comportamentos suspeitos originados de um mesmo endereço IP dentro de um período pré-determinado, ele adiciona automaticamente uma regra ao firewall da máquina para bloquear temporariamente (ou permanentemente) aquele invasor.


### 1.2 Principais Casos de Uso
* **Proteção contra Força Bruta em SSH:** Bloqueio de bots tentando senhas aleatórias para contas como `root` e `admin`.
* **Proteção de Servidores Web (Nginx / Apache):** Bloqueio de scanners de vulnerabilidades buscando arquivos sensíveis (`.env`, `wp-config.php`, `phpmyadmin`).
* **Proteção de Aplicações Web (WordPress, Nextcloud, etc.):** Bloqueio de requisições excessivas a endpoints de autenticação como `wp-login.php` ou `xmlrpc.php`.
* **Servidores de E-mail (Postfix / Dovecot) e FTP:** Bloqueio de invasores tentando abusar de autenticação SMTP/IMAP/POP3.

---

## 2. Arquitetura e Conceitos Fundamentais

O funcionamento do Fail2ban baseia-se em quatro pilares fundamentais:

| Conceito | Descrição |
| :--- | :--- |
| **Jail (Cadeia)** | É a unidade de configuração que conecta um **filtro**, uma **ação** e um **alvo de log**, aplicando os limites de tolerância estabelecidos. |
| **Filter (Filtro)** | Conjunto de regras baseadas em Expressões Regulares (`failregex`) responsáveis por casar as linhas de log que representam falhas de acesso. |
| **Action (Ação)** | A ação executada quando o limite de falhas é atingido (ex: adicionar regra no `nftables`/`iptables`, enviar notificação por e-mail ou disparar um script). |
| **Logpath** | Caminho do arquivo de log monitorado pela jail ou instrução para leitura via *systemd journal*. |

### 2.1 Parâmetros Essenciais de Configuração

* `bantime`: Duração do banimento do IP (ex: `10m`, `1h`, `1d`, `1w` ou `-1` para permanente).
* `findtime`: Janela de tempo de observação na qual as falhas acumuladas serão contabilizadas.
* `maxretry`: Número máximo de tentativas de falha permitidas dentro do intervalo `findtime` antes do banimento.
* `ignoreip`: Lista de endereços IP, máscaras CIDR ou hostnames confiáveis que **jamais** serão banidos (whitelist).

> **Exemplo Prático:**  
> Com `findtime = 10m`, `maxretry = 5` e `bantime = 1h`, se um mesmo IP falhar 5 vezes dentro de uma janela de 10 minutos, ele será banido por 1 hora.

{.is-info}


## 3. Instalação e Inicialização

### 3.1 Pré-requisitos
* Acesso com privilégios administrativos (`sudo` ou `root`).
* Um firewall em funcionamento no sistema (`nftables`, `iptables`, `ufw` ou `firewalld`).

### 3.2 Instalação por Distribuição

#### Debian / Ubuntu e Derivados
```bash
sudo apt update
sudo apt install fail2ban -y
```

#### RHEL / CentOS / Rocky Linux / AlmaLinux
```bash
sudo dnf install epel-release -y
sudo dnf install fail2ban fail2ban-firewalld -y
```

### 3.3 Habilitação e Inicialização do Serviço
```bash
# Habilita o serviço para iniciar no boot do sistema
sudo systemctl enable fail2ban

# Inicia o serviço
sudo systemctl start fail2ban

# Confirma se o serviço está ativo e rodando
sudo systemctl status fail2ban
```

---

## 4. Estrutura de Diretórios e Boas Práticas

Os arquivos de configuração do Fail2ban residem no diretório `/etc/fail2ban/`:

```
/etc/fail2ban/
├── fail2ban.conf          # Configurações globais do daemon (logs, socket)
├── fail2ban.local         # Sobrescrita local para fail2ban.conf
├── jail.conf              # Jails padrão fornecidas pelo pacote
├── jail.local             # Sobrescrita global de jails
├── jail.d/                # Diretório recomendado para configurações modulares
│   ├── 00-whitelist.local # Configurações globais de IPs ignorados
│   ├── sshd.local         # Jail específica do SSH
│   └── nginx.local        # Jails para aplicações web
├── filter.d/              # Filtros com regras de Regex pré-definidas
└── action.d/              # Ações e comandos de bloqueio (iptables, nftables, etc.)
```

> [!IMPORTANT]
> **Regra de Ouro:** **NUNCA** edite diretamente os arquivos `.conf` originais (`jail.conf`, `fail2ban.conf`).  
> Atualizações do sistema operacional substituem esses arquivos. Toda e qualquer configuração customizada deve ser feita em arquivos `.local` ou dentro do diretório `/etc/fail2ban/jail.d/*.local`.

{.is-warning}

---

## 5. Configuração Passo a Passo

### 5.1 Configurando a Whitelist Global (`ignoreip`)
Para evitar que administradores fiquem bloqueados fora do próprio servidor, configure a lista de IPs ignorados.

Crie o arquivo `/etc/fail2ban/jail.d/00-whitelist.local`:
```ini
[DEFAULT]
# Adicione localhost, a rede interna e seu IP público fixo de administração
ignoreip = 127.0.0.1/8 ::1 192.168.1.0/24 203.0.113.50

# Tempo padrão de banimento e janela de detecção
bantime  = 1h
findtime = 10m
maxretry = 5
```

---

### 5.2 Protegendo o Acesso SSH (`sshd`)
O SSH costuma ser o principal alvo de ataques automatizados.

Crie o arquivo `/etc/fail2ban/jail.d/sshd.local`:

#### Para distribuições modernas que utilizam Systemd (Ubuntu 22.04+, Debian 12+, Rocky/AlmaLinux):
```ini
[sshd]
enabled  = true
port     = ssh
backend  = systemd
maxretry = 3
findtime = 10m
bantime  = 2h
```

#### Para sistemas baseados em arquivos de log tradicionais:
```ini
[sshd]
enabled  = true
port     = 22
logpath  = /var/log/auth.log
maxretry = 3
findtime = 10m
bantime  = 2h
```

---

### 5.3 Protegendo Servidores Web Nginx / Apache

#### 1. Bloqueio de Scanners e Erros HTTP Excessivos (404/403/401)
Crie o arquivo `/etc/fail2ban/jail.d/nginx-botsearch.local`:
```ini
[nginx-botsearch]
enabled  = true
port     = http,https
logpath  = /var/log/nginx/access.log
maxretry = 5
findtime = 5m
bantime  = 6h
```

#### 2. Proteção de Login do WordPress (`wp-login.php`)
Crie primeiro o filtro `/etc/fail2ban/filter.d/wordpress-auth.conf`:
```ini
[Definition]
failregex = ^<HOST> .* "POST /wp-login.php HTTP/.*" 200
            ^<HOST> .* "POST /xmlrpc.php HTTP/.*" 200
ignoreregex =
```

Em seguida, ative a jail em `/etc/fail2ban/jail.d/wordpress.local`:
```ini
[wordpress-auth]
enabled  = true
port     = http,https
filter   = wordpress-auth
logpath  = /var/log/nginx/access.log
maxretry = 4
findtime = 5m
bantime  = 24h
```

---

## 6. Referência Rápida de Comandos (`fail2ban-client`)

O utilitário `fail2ban-client` é a ferramenta de linha de comando oficial para gerenciar e inspecionar o estado do serviço:

| Ação | Comando |
| :--- | :--- |
| **Ver status geral e jails ativas** | `sudo fail2ban-client status` |
| **Ver status e IPs banidos de uma jail** | `sudo fail2ban-client status sshd` |
| **Banir um IP manualmente** | `sudo fail2ban-client set sshd banip 198.51.100.25` |
| **Desbanir (unban) um IP de uma jail** | `sudo fail2ban-client set sshd unbanip 198.51.100.25` |
| **Desbanir um IP em todas as jails ativas** | `sudo fail2ban-client unban 198.51.100.25` |
| **Recarregar configurações sem reiniciar** | `sudo fail2ban-client reload` |
| **Testar regex contra arquivo de log** | `sudo fail2ban-regex /var/log/auth.log /etc/fail2ban/filter.d/sshd.conf` |

---

## 7. Recursos Avançados

### 7.1 Banimento Progressivo para Reincidentes (`recidive`)
A jail `recidive` monitora o próprio log do Fail2ban (`/var/log/fail2ban.log`) e pune atacantes reincidentes com bloqueios longos (ex: 1 semana).

Crie o arquivo `/etc/fail2ban/jail.d/recidive.local`:
```ini
[recidive]
enabled   = true
logpath   = /var/log/fail2ban.log
banaction = %(banaction_allports)s
bantime   = 1w
findtime  = 1d
maxretry  = 3
```

### 7.2 Banimento com Crescimento Exponencial (*Exponential Backoff*)
A partir das versões mais recentes do Fail2ban, é possível configurar o tempo de banimento incremental dinâmico:
```ini
[DEFAULT]
bantime.increment = true
bantime.rndtime = 15m
bantime.maxtime = 4w
bantime.factor = 2
```

---

## 8. Diagnóstico e Solução de Problemas (Troubleshooting)

### 8.1 Inspecionando os Logs do Fail2ban
Para diagnosticar por que uma regra não está disparando ou conferir histórico de bloqueios:
```bash
sudo tail -f /var/log/fail2ban.log
```

### 8.2 Incompatibilidade de Fuso Horário (Timezone)
O Fail2ban depende estritamente dos timestamps nos logs. Se a aplicação (como PHP, Nginx ou MySQL) gravar logs em um fuso horário diferente do relógio do sistema operacional, os eventos podem ser considerados "antigos demais" e descartados.
* **Verifique o relógio do sistema:** `timedatectl status`
* Garanta sincronização NTP ativa e coerência de timezone entre servidor e aplicações.

### 8.3 Uso com Cloudflare ou Proxies Reversos
Se seu tráfego passa por CDN ou proxy reverso (Cloudflare, AWS ALB, Nginx Proxy), o log do servidor conterá o IP do proxy, e não o IP real do cliente.
* **Solução:** Configure o módulo `http_realip_module` (no Nginx) ou `mod_remoteip` (no Apache) para restaurar o cabeçalho `X-Forwarded-For` como o endereço IP do cliente.
* **Nunca** bloqueie no nível de firewall local o IP de um proxy reverso, pois isso indisponibilizará o site para todos os usuários legítimos.

### 8.4 O que Fazer se Você For Banido Acidentalmente
1. Acesse o servidor por uma rota alternativa (console web da nuvem, VPN ou outro IP).
2. Execute o comando de liberação:
   ```bash
   sudo fail2ban-client unban <SEU_IP>
   ```
3. Inclua imediatamente seu IP na diretiva `ignoreip` em `/etc/fail2ban/jail.d/00-whitelist.local` e recarregue com `sudo fail2ban-client reload`.

---

## 9. Checklist de Validação para Produção

- [x] Fail2ban instalado e habilitado na inicialização do sistema (`systemctl enable fail2ban`).
- [x] Arquivo de Whitelist criado com IPs confiáveis em `jail.d/00-whitelist.local`.
- [x] Configurações criadas exclusivamente em extensões `.local`.
- [x] Jail de proteção SSH configurada e ativa.
- [x] Teste de regex validado com `fail2ban-regex`.
- [x] Logs verificados sem erros em `/var/log/fail2ban.log`.

![fail2ban_logo.png](/fail2ban_logo.png){.align-abstopright}