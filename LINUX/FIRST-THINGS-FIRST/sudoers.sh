:"PRIVILÉGIO SUDOERS"
:"Quando vc instala o OS com uma maquina virtual, o seu usuario nao vem com privilégio de
    root por padrao, por isso é nescessário configurar."

su root
:"A primeira coisa é alterar o usuario para root. Para isso é se usa o comando su.
    Digite su e em seguida o nome do usuario root, logo vai ser pedido a vc a senha
    que vc definiu na instalação."

sudo nano /etc/sudoers
:"Agora como root, você deve usar o comando a cima para editar o arquivo que define o
    privilégio dos usuários. Assim que abrir o editor, vá para a sessao onde esta escrito
    --user privilége especification-- e adicione o nome do seu usuario"

su usuario
:"Depois apenas troque de usuario mais uma vez agora para o seu nome de usuario
    e teste algum comando com sudo."