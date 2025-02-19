#include <iostream>
#define TAMANHO_MAXIMO 5 // Tamanho máximo da fila

using namespace std;

class FilaCircular {
private:
    int vetor[TAMANHO_MAXIMO];
    int frente;
    int traseira;
    int tamanho;

public:
    // Construtor
    FilaCircular() {
        frente = -1;
        traseira = -1;
        tamanho = 0;
    }

    // Enqueue: Adicionar elemento ao final da fila
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

    // Dequeue: Remover e retornar elemento do início da fila
    int dequeue() {
        if (frente == -1) {
            cout << "Fila vazia!" << endl;
            return -1; // Valor de erro
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

    // Front: Retornar elemento do início sem remover
    int front() {
        if (frente != -1) {
            return vetor[frente];
        } else {
            cout << "Fila vazia!" << endl;
            return -1; // Valor de erro
        }
    }

    // IsEmpty: Verificar se a fila está vazia
    bool isEmpty() {
        return (frente == -1);
    }

    // Size: Retornar o número de elementos na fila
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
