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
