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
