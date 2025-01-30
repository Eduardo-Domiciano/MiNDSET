# COMANDOS BASICOS DE NETSTAT

# 1. Mostrar todas as conexões de rede ativas e suas estatisticas:
$ netstat -a

# 2. Listar todas as conexões de rede e portas de escuta:
$ netstat -an

# 3. Exibir conexões de rede juntamente com PID (identificador de processo):
$ netstat -ano

# 4. Mostrar estatisticas detalhadas das interfaces de rede:
$ netstat -e

# 5. Exibir tabela de roteamento:
$ netstat -r

# 6. Mostrar estatisticas de conexoes TCP:
$ netstat -s

# 7. Exibir conexões TCP apenas:
$ netstat -p tcp

# 8. Mostra a tabela de interfaces, listando todas todas as interfaces de rede e suas estatisticas:
$ netstat -i

# 9. Exibe as associações de griupos multicast
$ netstat -g

# 10. Exibe conexoes mascaradas, úteis em configurações de NAT (Network Address Translations):
$ netstat -M

# 11. Verbosidade. Fornesse informações adicionais:
$ netstat -v

# 12. Não trunca endereços IP exibindo-os completamente:
$ netstat -W

# 13. Não resolve nomes, exibindo informações em formato numerico:
$ netstat -n

# 14. Não resolve nomes de hardware, exibindo-os como numeros.
$ netstat -N

# 15. Exibe temporizadores, mostrando tempo relacionado as conexoes.
$ netstat -o

# 16. Continuo, analizando a saida constantemente:
$ netstat -c

# 17. Exibe sockets do servidor em escuta:
$ netstat -l

# 18. Exibe a FIB ( Base de Informações de encaminhamento), que é a tela de encaminhamento padrão:
$ netstat -F

# 19. Exibe o cache de roteamento em vez da FIB:
$ netstat -C

# 20. Exibe o contexto de segurança SELinux para sockets:
$ netstat -Z