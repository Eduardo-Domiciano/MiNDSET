# CONFIGURAR SSH NO LINUX

#O SSH POR PADRAO RODA NA PORTA 22, GERALMENTE VEM HABILITADO,
#MAS NO CASO DE NÃO, SEGUE AS INSTRUÇÕES:

# 1. Primeiro para ver se o openssh-server esta instalado:
$ apt list openssh-server
# Se estiver instalado, a resposta vai ser algo assim:
Listing... Pronto
openssh-server/noble-updates,now 1:9.6p1-3ubuntu13.5 amd64 [installed]

# 2. No caso de não estar instaldo, segue o comando de instalação:
$ apt install openssh-server

# beckup das chaves atuais
mkdir /etc/ssh/default_keys
mv /etc/ssh/ssh_host_* /etc/ssh/default_keys/

# 3. No caso de precisar gerar novas chaves ssh
$ dpkg-reconfigure openssh-server

# 4. Ativar temporariamente o serviço:
$ systemctl start ssh.socket

# 5. Parar o serviço
$ systemctl stop ssh.socket

# 6. Para manter o serviço sempre ativo:
$ systemctl enable ssh.service

# 7. Para desativar o serviço permanentemente:
$ systemctl 

#8. Para verificar o status do serviço:
$ systemctl status ssh.service
# A resposta deve ser algo assim:
ssh.service - OpenBSD Secure Shell server
     Loaded: loaded (/usr/lib/systemd/system/ssh.service; disabled; preset: enabled)
     Active: active (running) since Fri 2024-12-27 23:49:09 UTC; 1 month 0 days ago
     #OBS: activo significa que esta sendo usado no momento
TriggeredBy: ● ssh.socket
       Docs: man:sshd(8)
             man:sshd_config(5)
   Main PID: 19787 (sshd)
      Tasks: 1 (limit: 6808)
     Memory: 2.2M (peak: 3.4M)
        CPU: 201ms
     CGroup: /system.slice/ssh.service
             └─19787 "sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups"