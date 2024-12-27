# UM POUCO SOBRE A FERRAMENTA DE TRANSFERENCIA SCP (SECURE COPY PROTOCOL)
#É uma ferramenta de transferencia de arquivos entre computadores em uma rede.
# Ele usa SSH para criptografar e proteger durante a tranferencia.
# O comando basico para usar a ferramenta é:
scp arquivo.txt usuario@ip:/caminho/pasta_de_destino

#Para copiar uma pasta com todas as sub pastas pode se usar o -r:
scp -r arquivo.txt usuario@ip:/caminho/pasta_de_destino

# Para comprimir os arquivos antes da transferencia use o -C:
scp -C arquivo.txt usuario@ip:/caminho/pasta_de_destino

# Se for nescessário definir uma porta diferente da padrão "22", deve-se usar -P:
# Lembrando que deve ser maiuscula, a minuscula vou falar mais a frente.
scp -P 35 arquivo.txt usuario@ip:/caminho/pasta_de_destino

# Para um modo Verbose, que tyras mais informação, use -v:
scp -v arquivo.txt usuario@ip:/caminho/pasta_de_destino

# Para que a copia dos arquivos mantenham a data de modificação do original, use -p:
# Lembrando que o "p" aqui é minusculo.
scp -p arquivo.txt usuario@ip:/caminho/pasta_de_destino