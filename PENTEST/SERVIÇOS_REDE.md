# SERVIÇOS DE REDE

## ESSAS SÃO ANOTAÇÕES SOBRE SERVIÇOS DE REDE, BASEADO NA SALA [NETWORK SERVICES](https://tryhackme.com/r/room/networkservices) DO THM.


## 1. Noções basicas sobre SMB:
SMB ou Server Message Block Protocol - é um protocolo de comunicação cliente-servidor usado para compartilhar arquivos, impressoras, portais seriais e outros recursos na rede.

Os servidores criam sistemas de arquivos e outros recursos, como impressoras, pipes nomeados e APIs, disponibilizando para os clientes. Os clientes tem seus proprios discos rigidos, mas também quertem acesso aos sistemas de arquivos compartilhados e impressoras nos servidores.

SBM é conhecido como um protocolo de solicitação de resposta, o que significa que ele transmite varias mensagens entre cliente e servidores para estabelecer uma conexao. Os clientes se conectam aos servidores usando TCP/IP(na verdade, NetBIOS sobre TCP/IP), NetBEUI ou IPX/SPX

Uma vez que a conexao estiver estabelecida, o cliente pode mandar comandos SMBs para o server, permitindo abrir, ler e escrever arquivos, geralmente fazendo tudo o que quiser com os arquivos do sistema. No caso do SMB, tudo é feito pela rede.

Todos os windows, a partir do 95 incluem suporte ao protocolo SMB. E o Samba é um open source server que suporta o SMBpara UNIX.

## 2. Enumeração SMB:
Enumeração: Enumeração é o processo de coleta de informação sobre um alvo para encontrar possiveis formas de atacart e ajudar na exploração. O processo é essencial pois evita desperdiçar tempo com exploits que nao funcionam. A enumeração pode ser usada para coleta de nomes, senhas, informações de rede, hosts, dados da aplicação, ou serviços que poissam ajudar na invasao.

SMB: Normalmente, há unidades de compartilhamento SMB em um servidor que podem ser conectados e usados para vuisualizar ou tranferir arquivos. O SMB pode ser om bom ponto de partida para reunir informações varias sobre o servidor, as aplicações e os usuarios.

O primeira etapa da enumeração é fazer uma varredura de portas, descobrir quantas portas abertas e quais serviços estão disponiveis.
Duas boas ferramentas para essa tarefa são `Nmap` e o `enum4linux`. Nmap, ja tem um arquivo de anotação exclusivo pra ela nem [aqui](https://github.com/Eduardo-Domiciano/MiNDSET/blob/master/PENTEST/Nmap-varredura-de-rede.md), e um mini tutorial de comandos basicos bem [aqui](https://github.com/Eduardo-Domiciano/MiNDSET/blob/master/PENTEST/FERRAMENTAS/NMAP.sh). Ja o enum4linux é uma ferramenta usada para enumerar compartilhamento em ambos os sistemas windows e Linux. Ate o momento dessas anotações, eu ainda não estudei sobre essa ferramenta, mas usei aqui pra essa sala e parece ser bem simples. 

## 3. Telnet

