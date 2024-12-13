#Criando uma porta de conexão remota no ubunto server 24.4.1 LTS

# >>>>>> O objetivo de quando eu fui tentar criar essa porta, era poder criar uma conexão
#com o mysql. Para isso também é nescessário configurar o mysql, mas vou explicar
# isso em outro arquivo. <<<<<<<<<<

# 1. A primeira coisa é verificar o status do firewall:
sudo ufw status
# a resposta deve ser: Status: active ou Status: inactive

# 2. Habilitar o firewall(se ja não estiver habilitado):
sudo ufw enable

# 3. Adicionar uma regra de entrada para uma porta desejada:
sudo ufw allow porta/protocolo
# Ex: sudo ufw allow 3306/tcp no caso de uma porta para conecção com o mysql.
# Ficar atento porque alguns serviços tem uma porta padrão como 80 para HTTP, 443 para HTTPS,
# 21 para FTP, 22 para SSH, 25 para SMTP, 110 para POP3, 143 para IMAP, 43 para DNS,
# ou 3389 para RDP.

# 4. Se nescessário, adicione regras, como por exemplo permissao apenas de trafego de saida.
sudo ufw allow out 80/tcp
# Aqui por exemplo permite que o seu servidor envie dados para outro servidor, pela
# porta 80. Quando vc nao usa "out" vc permite entrada e saida, o "out" no caso especifica
# a direção permitida de trafego.

# 5. Entao para verificar se deu certo, vc usa o passo 1. de novo
sudo ufw status
# a resposta deve ser algo como:
Status: active

To                         Action      From
--                         ------      ----
3306/tcp                   ALLOW       Anywhere
3306/tcp (v6)              ALLOW       Anywhere (v6)
# Mostrando as regras de firewall que foram implantadas.


# AQUI ALGUMAS DICAS ADICIONAIS PARA PODER USAR O UFW (UNCOMPLICATED FIREWALL)

# >>> Permitir tráfego de uma determninada faixa de portas:
sudo ufw allow 1000:2000/tcp
# Permite conexão na faixa de portas de 1000 a 2000 usando o protocolo tcp.


# >>> Permitindo tráfego de um endereço IP especifico:
sudo ufw allow from 192.168.1.100


# >>> Permitir trafego de uma faixa de endereço IP:
sudo ufw allow from 192.168.1.0/24


# >>> Bloquear tráfego de uma porta especifica:
sudo ufw deny 25/tcp


# >>> Bloquear tráfego de saida em uma porta especifica:
sudo ufw deny out 25/tcp


# >>> Desabilitar firewall:
sudo ufw disable

