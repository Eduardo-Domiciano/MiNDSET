#include <iostream>
#include <string>
#include <list>
#include <limits>

class Fila {
private:
    std::list<std::string> fila; // declara uma lista encadeada fila
public:
    void push(const std::string& nome) { // adiciona no final da fila
        fila.push_back(nome);
    }
    
    void pop() { // remove o primeiro nome da fila
        if (!fila.empty()) {
            std::cout << "Removendo: " << fila.front() << std::endl;
            fila.pop_front();
        } else {
            std::cout << "A fila está vazia!" << std::endl;
        }
    }
    
    void consulta(const std::string& nome) { // consulta o nome desejado
        int pos = 1;
        for (const auto& pessoa : fila) {
            if (pessoa == nome) {
                std::cout << nome << " está na posição " << pos << " na fila." << std::endl;
                return;
            }
            pos++;
        }
        std::cout << nome << " não está na fila." << std::endl;
    }
    
    bool isEmpty() { // caso a fila esteja vazia
        return fila.empty();
    }
};

void mostrarMenu() {
    std::cout << "Escolha uma opção:\n";
    std::cout << "1. Inclusão (push)\n";
    std::cout << "2. Remoção (pop)\n";
    std::cout << "3. Consulta\n";
    std::cout << "4. Sair\n";
}

int main() {
    Fila fila; // instacia fia
    int opcao; // variavel da opção do menu
    std::string nome;
    
    do {
        mostrarMenu();
        std::cout << "Opção: ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ve a opção e apaga depois
        
        switch (opcao) { // executa uma ação comparando as opções
        case 1:
            std::cout << "Digite o nome: ";
            std::getline(std::cin, nome);
            fila.push(nome);
            break;
        case 2:
            fila.pop();
            break;
        case 3:
            std::cout << "Digite o nome para consulta: ";
            std::getline(std::cin, nome);
            fila.consulta(nome);
            break;
        case 4:
            std::cout << "Encerrando o programa.\n";
            break;
        default:
            std::cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 4);
    
    return 0;
}
