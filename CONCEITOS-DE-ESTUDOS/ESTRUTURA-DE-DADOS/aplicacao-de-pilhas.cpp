#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Funçao para iverte uma palavra.
string inverte_palavra(string palavra) {
    stack<char> pilha;
// Empilha cada letra da palavra
    for (char letra :  palavra) {
         pilha.push(letra);
    }
    // desempilha as letras e forma a palavra invertida
    string palavra_invertida = "";
    while (!pilha.empty()) {
        palavra_invertida +=pilha.top();
        pilha.pop();
    }

    return palavra_invertida;
}


int main() {
    string palavras[] = {"pilha", "carro", "Ana"};// pslsvras pra inverter

    for (string palavra : palavras) { // roda a lista e executa o inverte palavra e exibe
        cout << "Entrada: "  << palavra << "\tSaída: " <<  inverte_palavra(palavra) << endl;
    }
    return 0;
}