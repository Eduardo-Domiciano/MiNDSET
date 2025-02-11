# Segue aqui, anotações sobre comandos comuns no ambiente Linux

### Comandos
1. List. Checar arquivos e pastas do diretorio:

`ls`
`ls --help`: Ls documentation
`ls -l`: Diretorios e arquivos em listas
`ls -la`: Mostra os arquivos em lista, mostrando também os arquivos ocultos.

2. Print Work Diretory:
`pwd`: Mostra o caminho completop do territorio em que vc se encontra.

3. Change Diretory
`cd nome_do_diretorio`: Esse comando é usado para mudar de diretorio, mas ser seguido de uma pasta dentro do diretorio atual, ou do caminho completo a partir do diretorio usr. Por Exemplo: `usr/share/wordlist`
`cd --help`: Documentação do comando ls
`cd ..`: Esse comando é usado para sair de uma pasta.
`cd ~`: Esse comando te leva automaticamente para a pasta padrao do usuario. Se seu usuario for kali sua pasta padrao será: `./usr/home/kali`

4. Making Diretory:
`mkdir <nome_do_diretorio>`: Usado para criar diretorios.
`mkdir --help`: Documentação do mkdir

5. Concatenate:
`cat nome_do_arquivo.txt`: Exibir o conteudo de um arquivo.
`cat arquivo01.txt arquivo02.txt`: Permite concatenar dois arquivos em uma unica exibição.
`cat > novo_arquivo.txt`: Cria um arquivo de leitura.
`cat >> arquivo existente.txt`: Adiciona conteudo em um arquivo selecionado.
`cat arquivo01.txt > arquivo02.txt`: adicionar o conteudo de um arquivo para o outro.
`cat -n nome_do_arquivo.txt`: enumera as lianhas de um arquivo.

6. Sort:
`sort arquivo.txt`: Ordena as linhas de um arquivo de texto em ordem alfabetica.
`sort -n arquivo.txt`: Ordena as linhas do arquivo em ordem numérica.
`sort -r arquivo.txt`: Ordena em ordem reversa.
`sort -k 2 arquivo.txt`: Ordena com base em uma coluna especifica.

7. uniq:
`uniq arquivo.txt`: Remove linhas duplicadas consecutivas. Melhor usado em conjunto com o comando `sort`.
`uniq -d arquivo.txt`: Exibe apenas as linhas duplicadas.
`uniq -u arquivo.txt`: Exibe apenas as linhas unicas.
`uniq -c arquivo.txt`: Conta a frequencia de linhas.
`uniq -i arquivo.txt`: Ignora a diferença entre maiusculas e minusculas.


wget Ip-ou-dominio/arquivo-a-ser-baixado
:"Esse comando é usado para fazer donload de arquivos"

grep "nome_a_ser_buscado"
:" è uma ferramenta de linha que busca padrões em arquivo de texto, como palavras chave
ou expressoes regulares."

w
:"Exibe todos os usuarios logados no sistema, além de informações de data e hora do log"