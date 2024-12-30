# ESSE É UM RESUMO DA SALA DE AULA "WHAT IS NETWORKING?" DO TRY HACK ME. ESSA SALA FALA SOBRE SOBRE REDE, IP, ENDEREÇAMENTO MAC, Ping.
LINK: https://tryhackme.com/r/room/whatisnetworking



# 1. O que é a internet?

A internet é uma grande rede com varias redes menores dentro. Dispositivos conectados e trocando 
informações. A primeira iteração da internet foi dentro do projeto ARPANET no final dos anos 1960. 
Financiada pelo Departamento de defesa dos Estados Unidos, foi a primeira rede ativa documentada. 
Mas só em 1989 que a internet como a connhecemos foi inventada por Tim Berners-Lee com a crianção 
do World Wide Web (WWW). A partir dai, a internet passou a ser usada como repositorio e 
compartilhamento de informações.

Uma rede pode ser de 2 tipos, publica e privada. A publica é a internet como a conhecemos, sendo 
acessada por qualquer um, as redes privadas, são redes internas, como de organizações comerciais,
militares e governamentais entre outras. Um bom exemplo disso é uma empresa que precisa de uma rede
interna que conecte todos os setores para trocar informações. Empresas grandes precisam de servidores
para armazenar informações, que servem de fonta para toda a empresa, com diferentes niveis de acesso.


# 2. Identificando os dispositivos.

Se você tem vários dispositivos em uma rede, você precisa identifica-los. Para fazer você tem duas 
informações, o ip e as impressões digitais. Um ser humano por exemplo tem nome e impressões digitais,
ele pode mudar seu nome, mas não consegue mudar suas digitais. Cada ser humano tem um conjunto de 
impressoes digitais. No caso de um dispositivo, estamos falando de:

* Um endereço de IP (Internet Protocol)
* Endereço MAC (Media Access Control), esse é tipo um numero de serie.

    ## 2.2 Endereço de IP (Internet Protocol):
        Um endereço IP pode ser usado para identificar um dispositivo em uma rede por um certo periodo 
        de tempo, mas esse mesmo endereço IP pode ser associado a outro dispositivo, ja que o ip pode ser alterado.

        ![Modelo de endereçamento de IP](<img src='/REDES/img/IP-IMG-THM.png'>)

        Um endereço de IP é um conjunto de numeros divididos em 4 octetos. Esse numero é calculado por 
        meio de uma técnica conhecida como endereçamento de IP e sub-rede. Um endereço IP pode mudar de 
        dispositivo para dispositivo, mas não pode estar ativo simultaneamente na mesma rede.
        Um endereço IP é um conjunto de padrões conhecidos como protocolos. Esse protocolos são a espinha 
        dorsal da rede e forçam os dispositivos conectdos a se comunicarem na mesma linguagem. Importante 
        lembrar que um dispositivo pode ao mesmo tempo ter um IP em uma rede privada, por exemplo sua casa ele
        ou empresa e outro endereço IP publica, como a internet.

        Se você tem internet em casa, com vários dispositivos conectados, você tem uma rede privada, onde
        seu roteador gera um IP para cada dispositivo, a fim de identificar cada um deles. Mas quando você
        entrar na internet, você terá um IP publica que será fornecido pelo Internet Service Provider ou ISP, 
        mais conhecido como provedor de internet.

        A medida que mais dispositivos se conectam na internet, fica cada vez mais dificil obter endereços de 
        IP disponiveis. Até agora, falamos apenas de uma versao do sistema de endereçamento do protocolo de 
        internet conhecido como IPv4, que usa um sitema de numeração de 2^32 endereços IP (4,29 bilhões) - a
        Cisco, uma gigante da insdustria estimou que haveria 50 bilhões de dispositivos conectados até o final 
        de 2021.

        O IPv6 é uma nova iteração do esquema de endereçamento do protocolo de internet pra ajudar a resolver 
        esse problema. Esse novo modelo tem algumas vantagens:

            * Suporta até 2^128 endereços IP(mais de 340 trilhoes), resolvendo os problemas enfrentados com o IPV4.
            * Mais eficiente divido a novas tecnologias.

        Comparação entre um endereço IPv6 e um IPv4.

        ![Comparação do modelo IPv6 para o modelo IPv4](<img src='/REDES/img/IPv6-IPv4-COMPARACAO-THM.png'>)


    ## 2.3 Endereços MAC (Media Access Control):

        Todos os dispositivos em uma rede, terão uma interface de rede fisica, que é uma placa encontrada 
        na placa mae do dispositivo. Essa interface recebe um endereço exclusivo na fabrica em que foi 
        contruida, chamada de endereçamento MAC (Media Access Control). O endereço MAC é um Hexadecimal de 12 
        caracteres dividido em 2 e separado por ":". Por exemplo a4:c3:f0:85:ac:2d.
        Os primeiros 2 caracteres representam a empresa que fez a interface de rede e os ultimos seis sao um numero 
        exclusivo.

        ![Modelo de endereçamento MAC](<img src='/REDES/img/MAC-THM.png'>)

        No entanto até esse endereço pode ser falsificado, em um processo chamado spoofing. Quando isso acontece, um dispositivo pode fingir ser outro para garantir acesso em projetos com segurança mal implementada.

# 3.Ferrmaneta Ping: 
    O ping é uma ferramneta essencial no dia a dia, ela usa pacortes ICMP (Internet Control Message Protocol) para determinar o desenpenho de uma conexão entre dispositivos. O tempo nescessário para os pacotes viajarem entre os dispositivos é medido pelo ping

    ![Mostrando o ping no terminal](<img src='/REDES/img/MAC-THM.png'>)