# Estrutura de dados.

Estrutura de dados é uma maneira de organizar, gerenciar e armazenar dados de maneira eficiente para que possam ser usados de forma adequada e eficaz. Elas são fundamentais na ciencia da ccomputação pois determinam a forma como dados são armazenados, manipulados e acessados. Diferentes estruturas de dados são usados para resolver diversos tipos de problemas. Alguens exemplos incluem: arrays, listas ligadas, pilhas, filas, arvores e grafos.

## Listas:

Listas nos permite armazenar e manipular coleções de elementos de forma dinamica, ou seja, tamanho da lista pode aumentar ou diminuir conforme nescessário. Os elementos em uma lista podem ser inseridos em qualquer posição. Quando os elementos estao ordenados a lista é chamada lista ordenada.

### Lista linear com vetores

Uma lista linear pe uma coleção ordenada de elementos, onde cada elemento ocupa uma posição especifica. Quando implementamos uma lista linear usanbdo um vetor (ou array), os elementos são armazenados em posições continuas na memoria.

### Aqui um exemplo de como implementar uma lista linear ultilizando um vetor em C++
````
#include <iostream>
using namespace std;

class ListaLinear {
private:
    int* vetor;
    int capacidade;
    int tamanho;

public:
    // Construtor: Inicializa a lista com uma capacidade especificada e define o tamanho como "0"
    ListaLinear(int cap) {
        capacidade = cap;
        tamanho = 0;
        vetor = new int[capacidade];
    }

    // Destrutor: Libera a memoria alocada para o vetor quando o objeto é destruido.
    ~ListaLinear() {
        delete[] vetor;
    }

    // Inserir elemento: Adiciona um elemento ao final da lista desde que a capacidade maxima não tenha sido atingida.
    void inserir(int elemento) {
        if (tamanho < capacidade) {
            vetor[tamanho] = elemento;
            tamanho++;
        } else {
            cout << "A lista está cheia!" << endl;
        }
    }

    // Remover elemento: Remove um elemento de uma posição especifica e ajusta os elementos subsequentes.
    void remover(int indice) {
        if (indice >= 0 && indice < tamanho) {
            for (int i = indice; i < tamanho - 1; i++) {
                vetor[i] = vetor[i + 1];
            }
            tamanho--;
        } else {
            cout << "Índice inválido!" << endl;
        }
    }

    // Acessar elemento: Retorna o valor do elemento em uma posição especifica, verificando se o indice é valido.
    int acessar(int indice) {
        if (indice >= 0 && indice < tamanho) {
            return vetor[indice];
        } else {
            cout << "Índice inválido!" << endl;
            return -1; // Valor de erro
        }
    }

    // Exibir os elementos da lista.
    void exibir() {
        for (int i = 0; i < tamanho; i++) {
            cout << vetor[i] << " ";
        }
        cout << endl;
    }

    // Obter tamanho: retorna o numero atual de elementos na lista.
    int obterTamanho() {
        return tamanho;
    }
};

int main() {
    ListaLinear lista(5);

    lista.inserir(10);
    lista.inserir(20);
    lista.inserir(30);
    lista.inserir(40);
    lista.inserir(50);

    cout << "Lista após inserções: ";
    lista.exibir();

    lista.remover(2); // Remover elemento no índice 2 (30)
    cout << "Lista após remoção: ";
    lista.exibir();

    int elemento = lista.acessar(1); // Acessar elemento no índice 1 (20)
    cout << "Elemento no índice 1: " << elemento << endl;

    return 0;
}

````
### Vantagens:

- Facilidade de implementação
- Apesar de simples, pode ser ultilizado para problemas mais complexos, dependendo do tamnho da lista.

### Desvantagens:

- Alto custo de remoção e inserção;
- Nescessidade de conhecer o tamanho da lista no momento da inicializaçao.

### Lista de alocação dinamica

Uma lista de alocação dinamica, frequentemente referida como lista ligada, é uma estrutura de dados que consiste em nós, onde cada nó contém dados e uma referencia (ou ponteiro) para o proximo nó na sequencia. Ao contrário de um vetor, que requer um tamanho fixo, uma lista ligada permite alocação e desalocação dinamica de memoria, o que torna  essa estrutura flexivel em termos de tamanho.

### Tipos de listas ligadas:

- Listas simplesmente liugada: Cada nó contem um valor e uma referencia para o proximo nó. A cabeça ou o inicio da lista é um ponteiro para o proximo nó. A ultima referencia do nó é null, indicando o fim da lista.

- Lista duplamente ligada: Cada nó contém um valor, uma referencia para o proximo nó e uma referencia para o nó anterior. Permite navegação bidirecional. A ultima referencia de nó é null.

- Lista circular: Semelhante a listas ligadas, mas a referencia do ultimo nó aponta de volta para o primeiro nó, formando um circulo.

### Exemplo de implementação de lista simplesmente ligada em C++

````
#include <iostream>
using namespace std;

// Definição do nó: Estrutura basica que contem o valor e o ponteiro para o proximo nó.
struct Nodo {
    int valor;
    Nodo* proximo;
};

class ListaLigada {
private:
    Nodo* cabeca;

public:
    // Construtor: Inicializa a lista com a cabeça como nullptr.
    ListaLigada() {
        cabeca = nullptr;
    }

    // Destrutor: Libera a memoria alocada para os nós da lista.
    ~ListaLigada() {
        Nodo* atual = cabeca;
        Nodo* proximo;
        while (atual != nullptr) {
            proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }

    // Inserir no início: Cria um novo nó e o adiciona no fim da lista.
    void inserirInicio(int valor) {
        Nodo* novoNodo = new Nodo();
        novoNodo->valor = valor;
        novoNodo->proximo = cabeca;
        cabeca = novoNodo;
    }

    // Remover do início: Remove o nó do inicio da lista e ajusta a cabeça.
    void removerInicio() {
        if (cabeca != nullptr) {
            Nodo* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }

    // Exibir lista: Percorre e exibe todos os valores da lista.
    void exibir() {
        Nodo* atual = cabeca;
        while (atual != nullptr) {
            cout << atual->valor << " -> ";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    ListaLigada lista;

    lista.inserirInicio(10);
    lista.inserirInicio(20);
    lista.inserirInicio(30);

    cout << "Lista após inserções: ";
    lista.exibir();

    lista.removerInicio();
    cout << "Lista após remoção: ";
    lista.exibir();

    return 0;
}

````