# AQUI UM BREVE TUTORIAL DE COMANDOS E CONFIGURAÇÕES PARA UMA CONEXAO SSH


# 1. Verificar se o servidor ssh esta em execução:
sudo service ssh status
#ou
sudo systemctl status ssh


# 2. Comando que permite que a porta ssh fique aberta no firewall:
sudo ufw allow 22/tcp
# e para verificar
sudo ufw status

# 3. iniciar uma conexão ssh com um computador ou server:
sudo ssh nome_usuario@ip_server
# Depois disso, ele vai pedir a senha.

# 4. Pra encerrar a conexao:
exit