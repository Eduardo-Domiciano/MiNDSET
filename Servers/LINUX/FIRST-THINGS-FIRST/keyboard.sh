:"ALTERANDO TECLADO PARA ABNT2"

sudo nano /etc/default/keyboard
:"Existe um arquivo em /ect/default/keyboard onde o teclado esta configurado.
    Com a cjamada a cima, abrimos o nano, um editor de texto via terminal para
    editar  o  arquivo com as informações a baixo."

:'
    #Arquivo de configuração para teclado (ABNT2) #/etc/default/keyboard

    XKBMODEL="abnt2"

    XKBLAYOUT="br"

    XKBVARIANT="abnt2"

    XKBLAYOUT="br"

    XKBOPTIONS="lv3:alt_switch,compose:rctrl"

    BACKSPACE="guess"

    --> preste bem atenção em qual chave esta cada informação! <--
'
:'Depois de inserir as novas informações, aperte ctrl O para abrir a opção de salvar e
    confirme com ENTER. Depois Ctrl X para sair e entao reinicie o sistema.'