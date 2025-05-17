#   Anotações sobre os fundamentos do windows.

## New Technology File System (NTFS)

O sistema de arquivos usado nas versoes mais modernas do windows é o New Technology File System. Antes do NTFS existinha o FAT16/FAT32 (File Allocation Table) e o HPFS (High Performance File System). Ainda é possivel ver o modelo FAT implantado em dispositivos USBs e MicroSDs, mas nao mais em windows OS. O NTFS é conhecido como um sistema de registros de arquivos diarios. Em caso de falha, o sistema pode reparar automaticamente as pastas ou arquivos do disco usando as informações armazenadas em um arquivo de log. Isso nao é possivel no FAT.

### Permissões NTFS

É possivel conceder ou negar permissoes de acesso a pastas e arquivos. As permissoes são:

- Full Control
- Modify
- Read & Execute
- List Folder Content
- Read
- Write

credito imagem: microsoft
![Permissões NTFS 1](../WINDOWS/img/ntfs-permissions1.png)

Se quiser ver as permissões:

- Clicar com o  botao direito do mause na pasta
- Propriedades
- Segurança
- Em grupos e nomes de usuarios, você visualisa o grupo ou nome de usuario que tem a permissao.
- Em permissões de usuario, você ve qual permissão o grupo e o usuario tem para essa pasta.

![Permissões NTFS 2](../WINDOWS/img/ntfs-permissions2.png)

Outro recurso do NTFS é o Alternative Data Streams (ADS). O ADS é um atributo esécifico do windows NTFS. Cada arquivo tem pelo meno um fluxo de dados (`$DATA`), e o ADS permite que os arquivos contenham mais de um fluxo de dados. Nativamente o windows explorer não exibe ADS para o usuario. Existem executraveis de terceiro que podem visualizar esses dados, mas o power shell tem a capacidade de visualizar esses dados. Hacker criadores de malware usam ADS para ocultar dados. Você pode saber mais sobre malware com ADS [aqui](https://www.malwarebytes.com/blog/101/2015/07/introduction-to-alternate-data-streams).

## Usuarios

Existem dois tipos de contas no windows, Usuario padrão e Administrador. Cada tipo determina o que o usuario poderá executar no sistema.

- Um administrador pode fazer alterações no sistema: Adicionar ususarios, excluir, modificar grupos, configuraçõesdo sistemas e etc.
- Um usuario padrao só poderá fazer alterações em pastas/arquivos atribuidos ao usuario e nao pode fazer alterações no sistema, como instalar programas por exemplo.

No menu de contas do windows, apenas o administrador poderá ver as opções de alterar tipo de conta, exluir, adicionar conta e etc. Cada usuario criado tera uma lista de pastas exclusivo para esse usuario especifico.
- Área de trabalho
- Documentos
- Downloads
- Musica
- Fotos

Outra forma de gerenciar ususarios é usar o "Gerenciamento de Usuarios e Grupos Locais". para acessar use Win + R e aparecerá a caixa de menu executar. Insira o comando `lusrmgr.msc`

![Gerenciador-usuarios](../WINDOWS/img/GERENCIADOR-USUARIOS.png)

Aqui há 2 pastas, Usuários e Grupos. Clicando em grupos, verá todos os grupos locais, juntamente com as descrições. Cada grupo tem permissões especificas definidas para eles, e os usuários são atribuidos a cada grupo pelo administrador. Quando um usuario é atribuido a um grupo, ele herda as pemissões desse grupo.

## UAC (User Account Control)

A maioria dos usuarios domesticos do windows, usam o sistema como administradores locais. Como dito antes qualquer administrador local pode fazer alterações no sistema. Um usuario comum nao precisa ter o nivel de privilégio de um administrador, capaz de alterar o sistema ou fazer instalações de softwares duvidosos.

### Executando como usuario

Quando um usuario faz uma ação, essa ação é feita a partir dos privilégios desse usuario, ou seja, se ele nao tiver o privilégio de instalar um programa duvidoso ou nao, ele nao conseguirá fazer isso sem a autenticação de um usuario que tem esse privilégio.

### UAC

Para proteger o usuario local usando dessa limitação de privilegios, a microsoft introduziu o UAC (User Account Control). Introduzindo inicialmente no Windows Vista, se manteve nas versoes posteriores. O UAC obviamente nao se aplica ao Administrador, mas a todos os demais usuarios. 
- Quando um usuario como administrador loga no sistema, ele nao loga com os privilegios de execução, se um software for instalado, um prompt aparece pedindo autorização para executar essas ações que requerem privilegios mais altos.

- Quando um usuario padrão loga no sistema, sempre que algum software for instalado, um prompt vai aparecer pedindo uma senha para essa ação ser executada. Quando vc também nao esta lgado como usuario padrão, os icones que precisam ser executados como administrador tem o simbolo do escudo de segurança para alerta-lo da nescessidade desse priovilegio para executar essa ação.

![icone com simbolo de segurança](../WINDOWS/img/exemplo-seguranca-administrador.png)

O icone do escudo amarelo e azul indica a nescessidade de uma autorização de administrador para executar o arquivo.