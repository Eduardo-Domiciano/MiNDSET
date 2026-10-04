# Estrutura de dados

Estrutura de dados é uma maneira de organizar, gerenciar e armazenar dados para que possam ser usados de forma adequada. Elas são fundamentais na ciência da computação, pois determinam como os dados são armazenados, manipulados e acessados. Estruturas diferentes resolvem tipos diferentes de problemas. Alguns exemplos: arrays, listas ligadas, pilhas, filas, árvores e grafos.

## Listas

Listas permitem armazenar e manipular coleções de elementos de forma dinâmica: o tamanho pode aumentar ou diminuir conforme necessário. Os elementos podem ser inseridos em qualquer posição. Quando seguem um critério de ordem (por exemplo, crescente), a lista é chamada de lista ordenada.

### Lista linear com vetores

Uma lista linear é uma coleção de elementos em sequência, em que cada um ocupa uma posição específica. Implementada com um vetor (array), os elementos ficam em posições contíguas na memória. O acesso por índice é direto. Inserir ou remover no meio exige deslocar os elementos seguintes.

A capacidade máxima é definida na criação. O número de elementos ocupados (o tamanho) cresce até esse limite.

### Exemplo de lista linear com vetor em C++

```cpp
#include <iostream>
using namespace std;

class ListaLinear {
private:
    int* vetor;
    int capacidade;
    int tamanho;

public:
    // Construtor: inicializa a lista com uma capacidade e tamanho zero.
    ListaLinear(int cap) {
        capacidade = cap;
        tamanho = 0;
        vetor = new int[capacidade];
    }

    // Destrutor: libera a memória alocada para o vetor.
    ~ListaLinear() {
        delete[] vetor;
    }

    // Insere no final, se ainda houver capacidade.
    void inserir(int elemento) {
        if (tamanho < capacidade) {
            vetor[tamanho] = elemento;
            tamanho++;
        } else {
            cout << "A lista está cheia!" << endl;
        }
    }

    // Remove o elemento de um índice e desloca os seguintes para a esquerda.
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

    // Retorna o valor de um índice, se ele for válido.
    int acessar(int indice) {
        if (indice >= 0 && indice < tamanho) {
            return vetor[indice];
        } else {
            cout << "Índice inválido!" << endl;
            return -1; // valor de erro
        }
    }

    // Exibe os elementos da lista.
    void exibir() {
        for (int i = 0; i < tamanho; i++) {
            cout << vetor[i] << " ";
        }
        cout << endl;
    }

    // Retorna quantos elementos a lista tem agora.
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

    lista.remover(2); // remove o elemento no índice 2 (30)
    cout << "Lista após remoção: ";
    lista.exibir();

    int elemento = lista.acessar(1); // acessa o elemento no índice 1 (20)
    cout << "Elemento no índice 1: " << elemento << endl;

    return 0;
}
```

### Vantagens

- Implementação simples.
- Acesso direto a qualquer posição pelo índice.

### Desvantagens

- Inserir ou remover no meio custa caro, porque os elementos seguintes precisam ser deslocados.
- A capacidade máxima precisa ser conhecida na inicialização. Se encher, é preciso realocar o vetor.

### Lista de alocação dinâmica

Uma lista de alocação dinâmica, em geral uma lista ligada, é formada por nós. Cada nó guarda um dado e uma referência (ponteiro) para outro nó. A memória de cada nó é alocada e liberada conforme a lista cresce ou encolhe, então o tamanho não precisa ser fixado na criação.

### Tipos de listas ligadas

- **Lista simplesmente ligada:** cada nó contém um valor e uma referência para o próximo. A cabeça é um ponteiro para o primeiro nó. O último nó aponta para nulo, o que marca o fim da lista.
- **Lista duplamente ligada:** cada nó contém um valor, uma referência para o próximo e outra para o anterior. Dá para percorrer a lista nos dois sentidos. O anterior do primeiro nó e o próximo do último são nulos.
- **Lista circular:** o próximo do último nó aponta de volta para o primeiro, formando um círculo.

### Exemplo de lista simplesmente ligada em C++

```cpp
#include <iostream>
using namespace std;

// Nó: guarda o valor e o ponteiro para o próximo.
struct Nodo {
    int valor;
    Nodo* proximo;
};

class ListaLigada {
private:
    Nodo* cabeca;

public:
    // Construtor: lista vazia.
    ListaLigada() {
        cabeca = nullptr;
    }

    // Destrutor: libera todos os nós.
    ~ListaLigada() {
        Nodo* atual = cabeca;
        Nodo* proximo;
        while (atual != nullptr) {
            proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }

    // Insere no início: o novo nó passa a ser a cabeça.
    void inserirInicio(int valor) {
        Nodo* novoNodo = new Nodo();
        novoNodo->valor = valor;
        novoNodo->proximo = cabeca;
        cabeca = novoNodo;
    }

    // Remove o primeiro nó e atualiza a cabeça.
    void removerInicio() {
        if (cabeca != nullptr) {
            Nodo* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }

    // Percorre a lista a partir da cabeça e exibe os valores.
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
```

### Vantagens

- Inserir e remover no início (ou numa posição cujo ponteiro já se conhece) é barato: basta ajustar referências.
- O tamanho cresce nó a nó, sem reservar a capacidade inteira de antemão.

### Desvantagens

- Não há acesso direto por índice. Para chegar a um elemento, a lista é percorrida desde o primeiro nó.

## Pilhas

Pilha (stack, em inglês) é uma estrutura que segue o princípio LIFO (Last In, First Out): o último elemento a entrar é o primeiro a sair.

### Conceito

Uma pilha permite inserção (push) e remoção (pop) apenas no topo. A imagem é uma pilha de pratos: o prato novo entra no topo, e o prato que se retira também é o do topo.

### Implementação com `std::vector`

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Pilha {
private:
    vector<int> vetor;

public:
    Pilha() {}

    // Adiciona um elemento ao topo.
    void push(int elemento) {
        vetor.push_back(elemento);
    }

    // Remove e devolve o elemento do topo.
    int pop() {
        if (!vetor.empty()) {
            int topo = vetor.back();
            vetor.pop_back();
            return topo;
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // valor de erro
        }
    }

    // Devolve o topo sem removê-lo.
    int top() {
        if (!vetor.empty()) {
            return vetor.back();
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // valor de erro
        }
    }

    bool isEmpty() {
        return vetor.empty();
    }

    int size() {
        return vetor.size();
    }
};

int main() {
    Pilha pilha;

    pilha.push(10);
    pilha.push(20);
    pilha.push(30);

    cout << "Topo da pilha: " << pilha.top() << endl;
    cout << "Tamanho da pilha: " << pilha.size() << endl;

    cout << "Removendo elemento do topo: " << pilha.pop() << endl;
    cout << "Topo da pilha após remoção: " << pilha.top() << endl;
    cout << "Tamanho da pilha após remoção: " << pilha.size() << endl;

    return 0;
}
```

### Vantagens

- Simples de implementar.
- Útil para avaliar expressões aritméticas e para o controle de chamadas de função (a pilha de execução).

### Desvantagens

- Só o topo é acessível. Os demais elementos ficam escondidos até serem desempilhados.

O `std::vector` cresce sozinho quando o bloco contíguo enche: a biblioteca realoca um vetor maior e copia os elementos.

### Pilha com ponteiros

Nesta versão, cada elemento é um nó alocado separadamente. A pilha cresce e encolhe um nó por vez, sem realocar um bloco inteiro.

### Implementação com ponteiros

```cpp
#include <iostream>
using namespace std;

// Cada nó guarda um valor e o ponteiro para o nó abaixo.
struct Nodo {
    int valor;
    Nodo* proximo;
};

class Pilha {
private:
    Nodo* topo;

public:
    // Pilha vazia: o topo não aponta para ninguém.
    Pilha() {
        topo = nullptr;
    }

    // Libera todos os nós.
    ~Pilha() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Cria um nó e o coloca como novo topo.
    void push(int elemento) {
        Nodo* novoNodo = new Nodo();
        novoNodo->valor = elemento;
        novoNodo->proximo = topo;
        topo = novoNodo;
    }

    // Remove o topo, avança o ponteiro e devolve o valor removido.
    int pop() {
        if (!isEmpty()) {
            Nodo* temp = topo;
            int valor = topo->valor;
            topo = topo->proximo;
            delete temp;
            return valor;
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // valor de erro
        }
    }

    // Devolve o valor do topo sem removê-lo.
    int top() {
        if (!isEmpty()) {
            return topo->valor;
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // valor de erro
        }
    }

    bool isEmpty() {
        return topo == nullptr;
    }
};

int main() {
    Pilha pilha;

    pilha.push(10);
    pilha.push(20);
    pilha.push(30);

    cout << "Topo da pilha: " << pilha.top() << endl;

    cout << "Removendo elemento do topo: " << pilha.pop() << endl;
    cout << "Topo da pilha após remoção: " << pilha.top() << endl;

    return 0;
}
```

### Vantagens

- O tamanho acompanha a quantidade de elementos, nó a nó.
- Inserção e remoção no topo são rápidas.

### Desvantagens

- Cada nó gasta memória extra com o ponteiro.
- Os nós ficam espalhados na memória, o que prejudica o aproveitamento da cache em relação a um vetor contíguo.

Nos exemplos de pilha e de fila, devolver `-1` quando a estrutura está vazia serve só como sinal de erro. Se `-1` for um valor válido da estrutura, esse sinal se confunde com um elemento de verdade.

## Filas

Uma fila (queue, em inglês) segue o princípio FIFO (First In, First Out): o primeiro elemento a entrar é o primeiro a sair. A imagem é uma fila de pessoas: quem chegou antes é atendido antes.

Enfileirar (`enqueue`) coloca o elemento no final. Desenfileirar (`dequeue`) retira o elemento da frente.

### Implementação com vetor

O exemplo trata o vetor como um anel: os índices de frente e traseira dão a volta com o operador módulo. É uma fila circular de capacidade fixa.

```cpp
#include <iostream>
#define TAMANHO_MAXIMO 100

using namespace std;

class Fila {
private:
    int vetor[TAMANHO_MAXIMO];
    int frente;
    int traseira;
    int tamanho;

public:
    // Frente e traseira em -1 indicam fila vazia.
    Fila() {
        frente = -1;
        traseira = -1;
        tamanho = 0;
    }

    // Insere no final. Se o próximo índice da traseira coincidir com a frente, a fila está cheia.
    void enqueue(int elemento) {
        if ((traseira + 1) % TAMANHO_MAXIMO == frente) {
            cout << "Fila cheia!" << endl;
        } else {
            if (frente == -1) frente = 0;
            traseira = (traseira + 1) % TAMANHO_MAXIMO;
            vetor[traseira] = elemento;
            tamanho++;
        }
    }

    // Remove e devolve o elemento da frente.
    int dequeue() {
        if (frente == -1) {
            cout << "Fila vazia!" << endl;
            return -1; // valor de erro
        } else {
            int elemento = vetor[frente];
            if (frente == traseira) {
                frente = -1;
                traseira = -1;
            } else {
                frente = (frente + 1) % TAMANHO_MAXIMO;
            }
            tamanho--;
            return elemento;
        }
    }

    // Devolve a frente sem removê-la.
    int front() {
        if (frente != -1) {
            return vetor[frente];
        } else {
            cout << "Fila vazia!" << endl;
            return -1; // valor de erro
        }
    }

    bool isEmpty() {
        return (frente == -1);
    }

    int size() {
        return tamanho;
    }
};

int main() {
    Fila fila;

    fila.enqueue(10);
    fila.enqueue(20);
    fila.enqueue(30);

    cout << "Elemento na frente da fila: " << fila.front() << endl;

    cout << "Removendo elemento da fila: " << fila.dequeue() << endl;
    cout << "Elemento na frente da fila após remoção: " << fila.front() << endl;

    return 0;
}
```

### Filas circulares

Numa fila linear com vetor, cada remoção “abandona” a posição da frente. Mesmo com espaço livre no início do vetor, a traseira pode bater no fim e a fila parecer cheia.

A fila circular devolve a traseira ao início quando ela chega ao fim do vetor. O último posto liga de volta ao primeiro, e o espaço liberado pelas remoções volta a ser usado. A condição de fila cheia, neste exemplo, é a traseira estar imediatamente antes da frente no anel: `(traseira + 1) % capacidade == frente`.

O código abaixo é o mesmo mecanismo, com capacidade 5, para o efeito da volta aparecer com poucos elementos.

### Implementação de fila circular em C++

```cpp
#include <iostream>
#define TAMANHO_MAXIMO 5

using namespace std;

class FilaCircular {
private:
    int vetor[TAMANHO_MAXIMO];
    int frente;
    int traseira;
    int tamanho;

public:
    FilaCircular() {
        frente = -1;
        traseira = -1;
        tamanho = 0;
    }

    void enqueue(int elemento) {
        if ((traseira + 1) % TAMANHO_MAXIMO == frente) {
            cout << "Fila cheia!" << endl;
        } else {
            if (frente == -1) frente = 0;
            traseira = (traseira + 1) % TAMANHO_MAXIMO;
            vetor[traseira] = elemento;
            tamanho++;
        }
    }

    int dequeue() {
        if (frente == -1) {
            cout << "Fila vazia!" << endl;
            return -1; // valor de erro
        } else {
            int elemento = vetor[frente];
            if (frente == traseira) {
                frente = -1;
                traseira = -1;
            } else {
                frente = (frente + 1) % TAMANHO_MAXIMO;
            }
            tamanho--;
            return elemento;
        }
    }

    int front() {
        if (frente != -1) {
            return vetor[frente];
        } else {
            cout << "Fila vazia!" << endl;
            return -1; // valor de erro
        }
    }

    bool isEmpty() {
        return (frente == -1);
    }

    int size() {
        return tamanho;
    }
};

int main() {
    FilaCircular fila;

    fila.enqueue(10);
    fila.enqueue(20);
    fila.enqueue(30);

    cout << "Elemento na frente da fila: " << fila.front() << endl;

    cout << "Removendo elemento da fila: " << fila.dequeue() << endl;
    cout << "Elemento na frente da fila após remoção: " << fila.front() << endl;

    return 0;
}
```

## Árvore binária

Árvore binária é uma estrutura em que cada nó tem no máximo dois filhos, em geral chamados de esquerdo e direito.

### Estrutura

- **Raiz:** o nó do topo, sem pai.
- **Folhas:** nós sem filhos.
- **Nós internos:** nós com pelo menos um filho.
- **Altura:** o número máximo de arestas da raiz até uma folha.
- **Nível de um nó:** a distância desse nó até a raiz (a raiz está no nível 0).

### Tipos

- **Árvore binária completa:** todos os níveis, exceto talvez o último, estão cheios, e os nós do último nível ficam o mais à esquerda possível.
- **Árvore binária cheia:** todo nó tem zero ou dois filhos. Nenhuma folha interna fica com um filho só.
- **Árvore binária balanceada:** em qualquer nó, a altura da subárvore esquerda e a da direita diferem em no máximo um.

### Operações comuns

- **Inserção:** acrescentar um nó.
- **Busca:** localizar um nó.
- **Remoção:** retirar um nó.
- **Percursos:** visitar todos os nós numa ordem definida.
  - Pré-ordem: raiz, subárvore esquerda, subárvore direita.
  - Em-ordem: subárvore esquerda, raiz, subárvore direita.
  - Pós-ordem: subárvore esquerda, subárvore direita, raiz.

### Árvore binária de busca

O exemplo abaixo é uma árvore binária de busca (BST). Além do limite de dois filhos, ela mantém uma ordem: valores menores ficam à esquerda do nó e valores maiores, à direita. O percurso em-ordem lista os valores em ordem crescente.

Na remoção há três casos: nó sem filhos, nó com um filho e nó com dois filhos. No último caso, o valor do nó é trocado pelo menor valor da subárvore direita (o sucessor) e esse sucessor é removido.

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    Node* searchHelper(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return searchHelper(node->left, value);
        }
        return searchHelper(node->right, value);
    }

    // Menor valor de uma subárvore: desce sempre pela esquerda.
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* removeHelper(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->data) {
            node->left = removeHelper(node->left, value);
        } else if (value > node->data) {
            node->right = removeHelper(node->right, value);
        } else {
            // Sem filho esquerdo, ou sem nenhum filho: sobe o direito.
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Dois filhos: copia o sucessor e remove a cópia na subárvore direita.
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeHelper(node->right, temp->data);
        }
        return node;
    }

    void inorderHelper(Node* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

    void destroyHelper(Node* node) {
        if (node != nullptr) {
            destroyHelper(node->left);
            destroyHelper(node->right);
            delete node;
        }
    }

public:
    BST() { root = nullptr; }

    ~BST() { destroyHelper(root); }

    void insert(int value) {
        root = insertHelper(root, value);
    }

    bool search(int value) {
        return searchHelper(root, value) != nullptr;
    }

    void remove(int value) {
        root = removeHelper(root, value);
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);

    cout << "Percurso em-ordem: ";
    tree.inorder();

    cout << "Busca 7: " << (tree.search(7) ? "Encontrado" : "Nao encontrado") << endl;
    cout << "Busca 8: " << (tree.search(8) ? "Encontrado" : "Nao encontrado") << endl;

    cout << "Removendo 5..." << endl;
    tree.remove(5);
    cout << "Novo percurso em-ordem: ";
    tree.inorder();

    return 0;
}
```
