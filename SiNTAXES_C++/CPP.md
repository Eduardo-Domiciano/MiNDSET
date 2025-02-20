# Anotações sobre sintaxe C++

## Modulo 1: Introdução ao C++

### 1.1 O que é C++?
C++ é uma linguagem de programação de propósito geral que é usado para desenvolver software de sis6temas, aplicações desktop, jogos, motores de jogos, drivers, entre outros.

### 1.2 Primeiro programa em C++
````
#include <iostream>

int main()
{
    std::cout << "hello, word! << std::endl;
    return 0;
}
````

## Modulo 2: Variaveis e Tipos de dados

- Declarações de variaveis
````
inst idade = 35;
float altura = 1.75;
char letra = 'A';
std::string nome = 'João';
bool isProgramador = true;
````

## Modulo 3: Estrutura de controle

- Condicionais (if, elseif, else)
````
inst idade = 18;
if (idade >= 18)
{
    std::cout << "Você é maior de idade." << std::endl;
} else {
    std::cout << "Você é menor de idade." << std::endl;
}
````

- Loops (for, while, do-while)
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
    k++
}while (k < 5>);
````

## Modulo 4: Funções

- Declaração e Definição de funções
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

- Funções com retorno e Paramentros
````
# include <iostream>
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
- Arrays
````
int numeros[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++)
{
    std::cout << numeros[i] << std::endl;
}

````
- Strings
````
std::string texto = "Hello, World!";
std::cout << texto << std::endl;

````

## Modulo 6: Estrutura de dados

- Estruturas
````
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
    std::cout << "Idade: " << P1.idade << std::endl;

    return 0;
};

````
- Vetores (std::vector)

````
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numeros = {1, 2, 3, 4, 5};
    for (int num : numeros) {
        std::cout << num << std::endl;
    };
    return 0;
}

````

## Modulo 7: Programação orientada a objetos

- Classes e Objetos
````
class Pessoa {
    public:
        std::string nome;
        int idade;

        void saudacao() {
            std::cout << "Oi, meu nome é " << nome << " e tenho " << idade << " anos." << std::endl;>
        }
};

int main(){
    Pessoa P1;
    p1.nome = "Ana";
    p1.idade = 25;
    p1.saudacao();

    return 0;
}

````

- Herança
````
class Animal {
    public:
        void som() {
            std::cout << "O animal faz um som." << std::endl;>>
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

- Leitura e escrita de arquivos

````
#include <iostream>
#include <fstream>

int main() {
    // escrita em arquivo
    std::ofstream arquivoSaida("exemplo.txt");
    arquivoSaida << "Escrevendo no arquivo." << std::endl;
    arquivoSaida.close();

    //Leitura de arquivo
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

- Biblioteca `cmatch`

````
#include <iostream>
#include <cmath>

int main() {
    double resultado = std::sqrt(16.0);
    std::cout << "Raiz quadrada de 16 é: " << resultado << std::endl;

    return 0;
}

````

- Biblioteca `algorithm`

````
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numeros = {5, 3, 1, 4, 2};
    std::sort(numeros.begin(), numeros.end());
    for (int num: numeros) {
        std::cout << num << std:: endl;
    }

    return 0;
}

````