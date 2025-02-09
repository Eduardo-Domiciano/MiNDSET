# Uma conexão SSH (Secure Shell) é um protocolo de rede que permite a comunicação segura entre dois computadores. Ele fornece uma maneira de acessar remotamente e gerenciar servidores e dispositivos de rede.

Quando você se conecta a um servidor remoto usando SSH, todo trafego de rede é criptografado, o que garante que a comunicação seja segura e nao porssa ser interceptada por terceiros.

## Comandos mais comuns:

### 1. Estabelecer uma conexão SSH:
`ssh usuario@ip_ou_dominio`
Esse é o comando padrão para acessar um servidor remoto. Depois disso, apenas informe a senha do usuario.

### 2. Conectar a um servidor em uma porta especifica:
`ssh -p porta usuario@servidor_remoto`

### 3. Copiar arquivo para servidor remoto:
`scp arquivo_local usuario@servidor_remoto:/caminho/destino`

### 4. Copiar arquivo do servidor remoto para computador local:
`scp usuario@servidor_remoto:/caminho/arquivo remoto caminho local`

### 5. Encaminhamento de porta local(Port Forwarding):
Local Forwarding: Redireciona uma porta local, para uma remota:
    `ssh -L porta_local:localhost:porta_remota usuario@servidor_remoto`
Remote Fowarding: Redireciona uma porta remota para uma porta local:
    `ssh -R porta_remota:localhost:porta_local usuario@servidor_remoto`

### 6. Execução de comandos remotos:
`ssh usuarios@servidor_remoto 'comando' `

### 7. Gerar um par de chaves SSH:
`ssh-keygen -t -b 2048 -C 'seu_email@exemplo.com'`

### 8. copiar chave publica para um servidor remoto:
`ssh-sopy-id -i ~/.ssh/id_rsa.pub usuario@servidor_remoto`

### 9. Para copiar uma com todas as subpastas:
`scp -r pasta usuario@servidor_remoto:/caminho/pasta_de_destino`

### 10. Para comprimir um arquivo antes da transferencia use -C:
`scp -C arquivo.txt usuarior@ip:/caminho/pasta_de_destino`

### 11. Para definir uma porta diferente da padrao (:22):
`scp -P 35 arquivo.txt usuario@ip:/caminho/pasta_de_destino`

### 12. Para o modo verbosidade:
`scp -v arquivo.txt usuario@ip:/caminho/pasta_de_destino`

### 13. Para que a copia dos arquivos mantenham a data de modificação original:
`scp -p arquivo.txt usuario@ip:/caminho/pasta_de_destino`