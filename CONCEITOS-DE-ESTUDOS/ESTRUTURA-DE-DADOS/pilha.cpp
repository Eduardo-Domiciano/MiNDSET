#include <iostream>
#include <vector>
using namespace std;

class Pilha {
private:
    vector<int> vetor; // Vetor para armazenar os elementos

public:
    // Construtor: Inicializa a pilha.
    Pilha() {}

    // Push: Adicionar elemento ao topo
    void push(int elemento) {
        vetor.push_back(elemento);
    }

    // Pop: Remover e retornar elemento do topo, verificando se a pilha ta vazia.
    int pop() {
        if (!vetor.empty()) {
            int topo = vetor.back();
            vetor.pop_back();
            return topo;
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // Valor de erro
        }
    }

    // Peek/Top: Retornar elemento do topo sem remove-lo, verificando se a pilha ta vazia.
    int top() {
        if (!vetor.empty()) {
            return vetor.back();
        } else {
            cout << "Pilha vazia!" << endl;
            return -1; // Valor de erro
        }
    }

    // IsEmpty: Verificar se a pilha está vazia
    bool isEmpty() {
        return vetor.empty();
    }

    // Size: Retornar o número de elementos na pilha
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
