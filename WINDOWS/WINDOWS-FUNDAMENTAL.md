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