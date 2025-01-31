# NETSTAT (NETWORK STATISTICS) 
Netstat é uma ferramenta ultilizada para monitorar e diagnosticar as conexoes de rede em um computador. Ela exibe informações detalhadas sobre conexoes de rede, portas de escuta, tabelas de roteamento e esztatistica de rede.

- Exibe todas as conexões de redes ativas, tanto entrada quanto saida.
- Mostra quais portas estão abertas e a espera de conexão.
- Exibe a tabela de roteamento, que mostra como os pacotes são encaminhados pelo sistema.
- Fornece estatisticas detalhadas sobre o uso de protocolos, como TCP, UDP, ICMP e IP.
- Mostra quais processos estao associais a cada conexao de rede, permite identificar programas especificos que estao usando a rede.

### Observar todas as conexões de uma porta especifica:
`$ watch -n 5 'netstat -an | grep ":22"'`
 A resposta seria algo assim:
 ```
tcp6       0      0 :::22                   :::*                    LISTEN
tcp6       0      0 192.0.0.2:22         192.0.0.3:50358      ESTABLISHED
tcp6       0      0 192.0.0.8:22         192.0.0.3:50968      ESTABLISHED
udp6       0      0 fe80::2289:84ff:fe0:546 :::*

 ```