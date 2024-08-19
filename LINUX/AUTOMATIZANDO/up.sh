:'AUTOMATIZANDO COMANDOS COM SCRIPT SHELL
    Esse arquivo mostra os passos pra criar um automação com
    Shell script'

:"A primeira coisa é criar um arquivo do formato shell. Esse se chama up.sh
    e serve pra atualizar o sistema"

:"Esse arquivo tem que estar na pasta ~/bin para ser chamado como comando.
     Ainda nao tenho certeza se funcuiona como comando apenas nessa pasta"

:"Como o arquivo vai estar na pasta /bin, precisamos adicionar esse caminho."

#!/bin/bash

:"Agora adicionamos o comendo que sera rodado quando o arquivo for executado"

apt-get update && apt-get upgrade -y

:" Assim, toda vez que chamar o arquivo ele executará o comando. Agora, para 
    em vez de chamar o arquivo, executa-lo como um comando do terminal, é nescessário
    autorizar que seja executado usando o comando a baixo no terminal."

:"sudo chmod +x up
    Aqui no caso, up é o nome do arquivo que ser´pa autorizado. o nome do arquivo
    passa a ser o comando a ser chamado."  