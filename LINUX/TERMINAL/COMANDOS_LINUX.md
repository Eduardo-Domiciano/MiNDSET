# Segue aqui, anotações sobre comandos comuns no ambiente Linux

### Comandos
1. List. Checar arquivos e pastas do diretorio:
- `ls`
- `ls --help`: Ls documentation
- `ls -l`: Diretorios e arquivos em listas
- `ls -la`: Mostra os arquivos em lista, mostrando também os arquivos ocultos.

2. Print Work Diretory:
- `pwd`: Mostra o caminho completop do territorio em que vc se encontra.

3. Change Diretory
- `cd nome_do_diretorio`: Esse comando é usado para mudar de diretorio, mas ser seguido de uma pasta dentro do diretorio atual, ou do caminho completo a partir do diretorio usr. Por Exemplo: `usr/share/wordlist`
- `cd --help`: Documentação do comando ls
- `cd ..`: Esse comando é usado para sair de uma pasta.
- `cd ~`: Esse comando te leva automaticamente para a pasta padrao do usuario. Se seu usuario for kali sua pasta padrao será: `./usr/home/kali`

4. Making Diretory:
- `mkdir <nome_do_diretorio>`: Usado para criar diretorios.
- `mkdir --help`: Documentação do mkdir

5. Concatenate:
- `cat nome_do_arquivo.txt`: Exibir o conteudo de um arquivo.
- `cat arquivo01.txt arquivo02.txt`: Permite concatenar dois arquivos em uma unica exibição.
- `cat > novo_arquivo.txt`: Cria um arquivo de leitura.
- `cat >> arquivo existente.txt`: Adiciona conteudo em um arquivo selecionado.
- `cat arquivo01.txt > arquivo02.txt`: adicionar o conteudo de um arquivo para o outro.
- `cat -n nome_do_arquivo.txt`: enumera as lianhas de um arquivo.

6. Sort:
- `sort arquivo.txt`: Ordena as linhas de um arquivo de texto em ordem alfabetica.
- `sort -n arquivo.txt`: Ordena as linhas do arquivo em ordem numérica.
- `sort -r arquivo.txt`: Ordena em ordem reversa.
- `sort -k 2 arquivo.txt`: Ordena com base em uma coluna especifica.

7. Uniq:
- `uniq arquivo.txt`: Remove linhas duplicadas consecutivas. Melhor usado em conjunto com o comando `sort`.
- `uniq -d arquivo.txt`: Exibe apenas as linhas duplicadas.
- `uniq -u arquivo.txt`: Exibe apenas as linhas unicas.
- `uniq -c arquivo.txt`: Conta a frequencia de linhas.
- `uniq -i arquivo.txt`: Ignora a diferença entre maiusculas e minusculas.

8. GNU wget (world Wide web Get):
- `wget http://exemplo.com/arquivo.zip`: Baixa um arquivo de uma pagina web.
- `wget -r http://exemplo.com/diretorio/`: Baixa um diretorio inteiro.
- `wget -c http://exemplo.com/arquivo.zip`: Continua um download interrompido.

9. Global Regular Expression Print:
- `grep "palavra-buscada" arquivo.txt`: Busca uma palavra em um arquivo.
- `grep "palavra-buscada" arquivo01.txt arquivo02.txt`: Busca uma palabra em ambos arquivos.
- `grep -i "palavra-buscada" arquivo.txt`: Ignora diferença entre maiuscula e minuscula durante a busca.
- `grep -n "palavra-buscada" arquivo.txt`: Mostra o numero da linha.
- `grep -r "palavra-buscada" /caminho/do/diretorio`: Busca recursiva em diretorios.
- `grep -v "palavra-buscada" arquivo.txt`: Mostrar linhas que nao contem o padrao buscado.
- `grep -c "palavra-buscada" arquivo.txt`: Mostrar contagem de linhas que nao ontem o padrao buscado.

10. w (who):
- `w`: Esse comando basicamente mostra todos os usuarios ativos no sistema operacional. 
###### As informações mostradas são:
- [x] Nome do usuario: Nomes dos usuarios conectados.
- [x] TTY: Terminal que o usuario esta usando.
- [x] From: O ip e porta da conexao remota.
- [x] LOGIN@: hora que o usuario fez o login.
- [x] IDLE: Tempo de inatividade do usuario.
- [x] JCPU: Tempo total de CPU ultilizado pelos processos do usuario, incluindo os processos de segundo plano.
- [x] PCPU: Tempo de CPU utilizado pelo processo atual.
- [x] what: o comando ou o processo que o usuario esta executando.

###### Exemplo de saida de comando:
```
 16:10:07 up 2 days,  3:44,  3 users,  load average: 0.09, 0.03, 0.01
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
alice    pts/0    192.168.1.2       09:23    1:23m  0.23s  0.09s bash
bob      pts/1    :0                10:15    5:01   1:01   0.00s vi
carol    pts/2    192.168.1.3       14:30    0.00s  0.45s  0.10s top

```

- `w -h`: Exibe a saida limitando informações. Pode ser util se houver muitos usuario.
- `w -s`: Exibir informações simplificadas.