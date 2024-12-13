# PERMITINDO ACESSO REMOTO AO MYSQL EM UM SERVIDOR UBUNTO 24.04.1 LTS

# 1. Editar o arquivo de configuração do MySql:
sudo nano /etc/mysql/mysql.conf.d/mysql.cnf


# 2. Localize a linha:
bind-address = 127.0.0.1
# Você pode alterar essa linha de duas maneiras, colocando "#" para comentar a linha, ou
# alterar o valor para 0.0.0.0
bind-address = 0.0.0.0
# Salve o arquivo e saia.


# 3. Reinicie o serviço MySql para aplicar as mudanças:
sudo service mysql restart

# 4. configure as permissões do usuario logando como root:
sudo mysql -u root -q


# 5. Crie um usuario com acesso remoto e defina a senha:
CREATE USER 'usuario_remoto'@'%' IDENTIFIED BY 'senha';

#Conseda privilégio ao novo usuario:
GRANT ALL PRIVILEGES ON *.* TO 'usuario_remoto'@'%' WITH GRANT OPTION;

#Atualize as permissoes:
FLUSH PRIVILEGES;

#Configure o firewall:
sudo ufw allow 3306/tcp