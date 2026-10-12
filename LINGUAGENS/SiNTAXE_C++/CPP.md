# Anotações sobre sintaxe C++

## Modulo 1: Introdução ao C++

### 1.1 O que é C++?
C++ é uma linguagem de programação de propósito geral que é usado para desenvolver software de sis6temas, aplicações desktop, jogos, motores de jogos, drivers, entre outros.

### 1.2 Primeiro programa em C++

Este exemplo é um programa completo: o menor arquivo que o compilador transforma em um executável. Ele serve para conferir se o ambiente está instalado e para ver como uma mensagem chega ao terminal. Use-o como molde de todo programa daqui para a frente: a função `main` é o ponto de entrada, `std::cout` escreve na tela e `return 0` avisa ao sistema que o programa terminou sem erro. O arquivo precisa ser salvo como `.cpp` e compilado, por exemplo com `g++ arquivo.cpp -o programa`.

````
#include <iostream>

int main()
{
    std::cout << "hello, world!" << std::endl;
    return 0;
}
````

## Modulo 2: Variaveis e Tipos de dados

Uma variável é um nome para um valor guardado na memória. O tipo diz o que cabe ali e quais operações fazem sentido. `int` guarda inteiro, `float` guarda número com parte decimal, `char` guarda um caractere, `std::string` guarda um texto e `bool` guarda verdadeiro ou falso. Use o tipo mais estreito que descreve o dado: idade em `int`, altura em `float` ou `double`, uma resposta de sim ou não em `bool`. Texto em C++ vai entre aspas duplas e exige `#include <string>`.

````
#include <string>

int idade = 35;
float altura = 1.75;
char letra = 'A';
std::string nome = "João";
bool isProgramador = true;
````

## Modulo 3: Estrutura de controle

O programa segue as linhas de cima para baixo, a menos que uma estrutura de controle mude o caminho. Condicionais escolhem um bloco. Laços repetem um bloco enquanto uma condição for verdadeira.

### Condicionais (if, else if, else)

O `if` executa o bloco quando a condição é verdadeira. O `else` executa o outro caminho. O `else if` testa uma segunda condição só quando a primeira falhou. Serve para regras do tipo “se a idade permite, faça isto; senão, faça aquilo”. A condição fica entre parênteses e o bloco, entre chaves.

````
int idade = 18;
if (idade >= 18)
{
    std::cout << "Você é maior de idade." << std::endl;
}
else if (idade >= 12)
{
    std::cout << "Você é adolescente." << std::endl;
}
else
{
    std::cout << "Você é criança." << std::endl;
}
````

### Loops (for, while, do-while)

Os três repetem um trecho. O `for` serve quando se sabe quantas voltas dar, como percorrer posições de 0 a 4. O `while` testa a condição antes de entrar: se já for falsa, o bloco não roda. O `do-while` roda o bloco uma vez e só depois testa, útil quando a ação precisa acontecer pelo menos uma vez, como pedir uma senha. Nos dois últimos, alguém dentro do bloco precisa alterar a variável da condição; senão o laço não acaba.

````
for (int i = 0; i < 5; i++)
{
    std::cout << i << std::endl;
}

int j = 0;
while (j < 5)
{
    std::cout << j << std::endl;
    j++;
}

int k = 0;
do {
    std::cout << k << std::endl;
    k++;
} while (k < 5);
````

## Modulo 4: Funções

Uma função é um bloco com nome. Ela serve para escrever uma tarefa uma vez e chamá-la de vários pontos, em vez de copiar o mesmo código. A declaração avisa o compilador do nome e dos tipos. A definição traz o corpo. A chamada, dentro de `main` ou de outra função, é o uso.

### Declaração e definição de funções

`saudacao` não recebe dado e não devolve valor (`void`). O exemplo mostra a ordem usual: declarar antes de `main`, definir depois. Dá para definir a função inteira antes de `main` e dispensar a declaração separada. Use uma função assim para uma ação fechada: imprimir um menu, limpar um cálculo, abrir uma mensagem padrão.

````
#include <iostream>
void saudacao();

int main()
{
    saudacao();
    return 0;
}

void saudacao()
{
    std::cout << "Olá, Isso foi escrito em C++!" << std::endl;
}
````

### Funções com retorno e parâmetros

O parâmetro é o valor que entra. O retorno é o valor que sai para quem chamou. `soma` recebe dois `int` e devolve a adição. Quem chama guarda o resultado numa variável ou usa direto numa expressão. Use esse formato para cálculos e consultas: o nome diz a tarefa, os parâmetros dizem a entrada e o tipo antes do nome diz o que volta. `return` encerra a função e entrega o valor.

````
#include <iostream>
int soma(int a, int b);

int main()
{
    int resultado = soma(5, 3);
    std::cout << "A soma é: " << resultado << std::endl;
    return 0;
}

int soma(int a, int b)
{
    return a + b;
}
````

## Modulo 5: Arrays e Strings

### Arrays

Um array guarda vários valores do mesmo tipo em posições numeradas a partir de zero. O tamanho, entre colchetes, é fixo: este array tem cinco `int` e não cresce. Serve para uma coleção pequena e de tamanho conhecido, como as notas de uma prova ou os dias de uma semana. O acesso é `numeros[i]`. O laço abaixo visita cada posição. Ultrapassar o tamanho é erro: o C++ não avisa sozinho.

````
int numeros[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++)
{
    std::cout << numeros[i] << std::endl;
}
````

### Strings

`std::string` é o tipo da biblioteca padrão para texto de tamanho variável. Diferente de `char`, que guarda uma letra, a string guarda uma frase, um nome ou uma linha lida do teclado. Use-a sempre que o texto puder mudar de tamanho. É preciso `#include <string>`. Aspas duplas criam o texto. `std::cout` imprime o conteúdo.

````
#include <string>

std::string texto = "Hello, World!";
std::cout << texto << std::endl;
````

## Modulo 6: Estrutura de dados

### Estruturas

`struct` agrupa campos de tipos diferentes sob um único nome. `Pessoa` junta um nome e uma idade que andam juntos. Serve para representar um registro: pessoa, ponto na tela, produto. Cria-se uma variável do tipo da struct e preenchem-se os campos com ponto: `p1.nome`. Cada variável tem a própria cópia dos campos. O nome da variável e o nome do campo distinguem maiúsculas: `p1` e `P1` são nomes diferentes.

````
#include <iostream>
#include <string>

struct Pessoa
{
    std::string nome;
    int idade;
};

int main()
{
    Pessoa p1;
    p1.nome = "João";
    p1.idade = 30;

    std::cout << "Nome: " << p1.nome << std::endl;
    std::cout << "Idade: " << p1.idade << std::endl;

    return 0;
}
````

### Vetores (std::vector)

`std::vector` também guarda vários valores do mesmo tipo, mas o tamanho muda em tempo de execução: dá para acrescentar e remover elementos. Use-o no lugar do array quando a quantidade não é fixa, como uma lista de notas que ainda vai receber itens. É preciso `#include <vector>`. O `for` com `:` percorre cada elemento sem controlar o índice na mão. `numeros.push_back(6)` acrescenta um valor ao fim.

````
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numeros = {1, 2, 3, 4, 5};
    for (int num : numeros) {
        std::cout << num << std::endl;
    }
    return 0;
}
````

## Modulo 7: Programação orientada a objetos

### Classes e objetos

Uma classe é o molde. Um objeto é um exemplar desse molde. `Pessoa` descreve os dados (`nome`, `idade`) e um comportamento (`saudacao`). Serve quando dados e a ação que os usa devem ficar juntos: a saudação lê os campos da própria pessoa, sem receber nome e idade de fora. Cria-se o objeto (`Pessoa p1`), preenchem-se os campos e chama-se o método com ponto. `public` deixa campos e métodos acessíveis a quem tem o objeto.

````
#include <iostream>
#include <string>

class Pessoa {
    public:
        std::string nome;
        int idade;

        void saudacao() {
            std::cout << "Oi, meu nome é " << nome << " e tenho " << idade << " anos." << std::endl;
        }
};

int main(){
    Pessoa p1;
    p1.nome = "Ana";
    p1.idade = 25;
    p1.saudacao();

    return 0;
}
````

### Herança

Herança cria uma classe nova a partir de outra. `Cachorro` é um `Animal`: recebe o que `Animal` já tem e pode substituir o que for específico. `: public Animal` diz essa relação. Serve para tratar vários tipos pelo que têm em comum e especializar o comportamento. Aqui `Cachorro` redefine `som()`. No objeto `c`, a chamada usa a versão do cachorro. O mesmo desenho vale para gato, pássaro e outros, cada um com o próprio `som()`, sem copiar o restante da classe base.

````
#include <iostream>

class Animal {
    public:
        void som() {
            std::cout << "O animal faz um som." << std::endl;
        }
};

class Cachorro : public Animal {
    public:
        void som() {
            std::cout << "O cachorro late." << std::endl;
        }
};

int main() {
    Cachorro c;
    c.som();

    return 0;
}
````

## Modulo 8: Manipulação de arquivos

Arquivo em disco continua existindo depois que o programa termina. `std::ofstream` abre para escrita. `std::ifstream` abre para leitura. Serve para guardar configuração, registro ou qualquer texto que a próxima execução precise ler. O exemplo cria `exemplo.txt` na pasta em que o programa roda, escreve uma linha, fecha, abre de novo e imprime cada linha na tela. `close` devolve o arquivo ao sistema. Se a abertura falhar, o programa deve testar o fluxo antes de ler; este exemplo assume que o arquivo foi criado no passo anterior. É preciso `#include <fstream>`.

````
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ofstream arquivoSaida("exemplo.txt");
    arquivoSaida << "Escrevendo no arquivo." << std::endl;
    arquivoSaida.close();

    std::ifstream arquivoEntrada("exemplo.txt");
    std::string linha;
    while (std::getline(arquivoEntrada, linha)) {
        std::cout << linha << std::endl;
    }
    arquivoEntrada.close();

    return 0;
}
````

## Modulo 9 Bibliotecas Padrão

A biblioteca padrão é código pronto que acompanha o compilador. Cada cabeçalho (`#include`) libera um grupo de ferramentas. Inclua só o que o arquivo usa.

### Biblioteca `cmath`

`cmath` reúne funções matemáticas: raiz, potência, seno, valor absoluto e outras. `std::sqrt` devolve a raiz quadrada de um `double`. Use-a para não reescrever fórmula que a linguagem já entrega com precisão conhecida. O resultado pode ser guardado ou impresso direto.

````
#include <iostream>
#include <cmath>

int main() {
    double resultado = std::sqrt(16.0);
    std::cout << "Raiz quadrada de 16 é: " << resultado << std::endl;

    return 0;
}
````

### Biblioteca `algorithm`

`algorithm` traz algoritmos que operam sobre intervalos, não sobre um tipo só. `std::sort` ordena do primeiro elemento até o último, marcados por `begin()` e `end()`. Serve para ordenar um `vector`, e também outros contêineres, sem escrever o algoritmo de ordenação. Depois da chamada, `numeros` fica em ordem crescente. O `for` imprime o resultado para conferir.

````
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numeros = {5, 3, 1, 4, 2};
    std::sort(numeros.begin(), numeros.end());
    for (int num : numeros) {
        std::cout << num << std::endl;
    }

    return 0;
}
````
