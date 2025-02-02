#!/bin/bash

# Função para exibir ajuda
mostrar_ajuda() {
  echo "CONNECTIONS STATISTICS (cs) é um script de monitoramento de conexões de rede em tempo real"
  echo "Salve esse arquivo na pasta '~/bin' e usar o comando '$ chmod +x cs' para criar o comando"
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