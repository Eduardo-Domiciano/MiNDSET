# NETSTAT (NETWORK STATISTICS) 
Netstat é uma ferramenta ultilizada para monitorar e diagnosticar as conexoes de rede em um computador. Ela exibe informações detalhadas sobre conexoes de rede, portas de escuta, tabelas de roteamento e esztatistica de rede.

- Exibe todas as conexões de redes ativas, tanto entrada quanto saida.
- Mostra quais portas estão abertas e a espera de conexão.
- Exibe a tabela de roteamento, que mostra como os pacotes são encaminhados pelo sistema.
- Fornece estatisticas detalhadas sobre o uso de protocolos, como TCP, UDP, ICMP e IP.
- Mostra quais processos estao associais a cada conexao de rede, permite identificar programas especificos que estao usando a rede.

### Observar todas as conexões de uma porta especifica:
`$ watch -n 5 'netstat -an | grep ":22"'`

Explicação do comando:
- `watch -n 5`: Esse comando executa uma ação repetidamente a cada 5 segundos.
- `netstat -an`: Esse comando exibe todas as conexões de rede e as portas que estão sendo ouvidas pelo seu sistema. Opção `-a` mostra as conexões, enquanto a `-n` exibe endereços e portas no formato numerico.
- `grep ":22"`: Esse comando procura por linhas que contem a string `:22` no output do netstat.
- Lembrando que `|` é um caracter usado para executar mais de um comando na mesma saida.



 A resposta seria algo assim:
 ```
tcp6       0      0 :::22                   :::*                    LISTEN
tcp6       0      0 192.0.0.2:22         192.0.0.3:50358      ESTABLISHED
tcp6       0      0 192.0.0.8:22         192.0.0.3:50968      ESTABLISHED
udp6       0      0 fe80::2289:84ff:fe0:546 :::*

 ```

Explicação da saida:
Linha 1
- `tcp6`: indica que é uma conexaoTCP sobre ipv6, ou seja, exibe o tipo de protocolo de conexao.
- `0 0`: Numero de bites enviado e recebidos, respectivamente, mas nada ainda foi transmitido.
- `:::22`: Esta ouvindo na porta 22, para qualquer endereço ipv6.
- `:::*`: Endereço remoto, indicando que esta ouvindo de qualquer endereço.
- `LISTEN`: O estado da conexão da porta é `LISTEN`, ou seja, esta aguardadno conexao de entrada.

Linha 2
- `tcp6`: Mesma coisa, indicando qual protocolo esta sendo usado.
- `0 0`: Mesma coisa, numero de bites enviados e recebidos.
- `192.0.0.2:22`: Endereço local da maquina, ouvindo na porta 22 (porta padrao para SSH).
- `192.0.0.3:50358`: Endereço do cliente que esta se conectando a maquina local. Ele está se conectando através da porta 50358.

As demais linhas seguem o mesmo padrão.


## CONECTIONS STATISTICS (CS)

Com o objetivo de facilitar o processo, busquei umas ferramentas, consegui um script que faz essa analise de conexões, filtrando por alguns parametros.

```
#!/bin/bash

# Função para exibir ajuda
mostrar_ajuda() {
  echo "CONNECTIONS STATISTICS (cs) é um script de monitoramento de conexões de rede em tempo real"
  echo "Uso: $0 [-p porta] [-i ip] [-t intervalo_em_segundos] [-h]"
  echo
  echo "  -p porta                 Porta a ser monitorada"
  echo "  -i ip                    Endereço IP a ser monitorado"
  echo "  -t intervalo_em_segundos Intervalo de tempo entre as verificações (padrão: 5 segundos)"
  echo "  -h                       Exibe esta mensagem de ajuda"
}

PORT=""
IP=""
DEFAULT_INTERVAL=5

# Processa os argumentos
while getopts "p:i:t:h" opt; do
  case ${opt} in
    p )
      PORT=$OPTARG
      ;;
    i )
      IP=$OPTARG
      ;;
    t )
      INTERVAL=$OPTARG
      ;;
    h )
      mostrar_ajuda
      exit 0
      ;;
    \? )
      mostrar_ajuda
      exit 1
      ;;
  esac
done

# Se o intervalo não foi fornecido, usa o valor padrão
if [ -z "$INTERVAL" ]; then
  INTERVAL=$DEFAULT_INTERVAL
fi

while true; do
    echo "$(date):"
    if [ -n "$PORT" ] && [ -n "$IP" ]; then
        # Filtra por porta e IP
        netstat -an | grep ":$PORT" | grep "$IP"
    elif [ -n "$PORT" ]; then
        # Filtra apenas por porta
        netstat -an | grep ":$PORT"
    elif [ -n "$IP" ]; then
        # Filtra apenas por IP
        netstat -an | grep "$IP"
    else
        # Mostra todas as conexões
        netstat -an
    fi
    sleep $INTERVAL
done

```

Esse aquivo consta na pasta de AUTOMATIZANDO da pasta LINUX desse repozitorio.