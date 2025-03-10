#include <iostream>
using namespace std;

// nó da árvore binária
struct Node {
        int data;           // armazenando no nó
        Node* left;         // filho esquerdo
        Node* right;        // ilho direito

        Node(int value) {   // Construtor
            data = value;
            left = nullptr;
            right = nullptr;
        }
};


 // Classe para a árvore binária de busca
class BST {
private:
    Node* root;     // Raiz da árvore

        // Função auxiliar para inserir um nó (recursiva)
    Node* insertHelper(Node* node, int value) 
    {
        if (node == nullptr) {
             return new  Node(value);  //    Cria nov nó se o local estiver vazio
        }
        if  (value < node->data) {
             node->left = insertHelper(node->left, value);  //esquerda
        } else if (value > node->data) {
             node->right  = insertHelper(node->right, value); // direita
        }
         return node;  // Retorna o nó
    }

    // buscar um valor - recursiva
    Node* searchHelper(Node* node, int value) {
        if (node == nullptr || node->data == value) 
        {
             return node;  // Retorna nullptr  se não encontrado ou o nó seencontrado
        }
        if (value <  node->data) {
            return searchHelper(node->left, value);  // Busca  esquerda
        }
        return  searchHelper(node->right, value);  // Busca direita
    }

    // Funçao para encontrar o menor valor 
    Node*  findMin(Node*  node) {
        while (node->left != nullptr)  
        {
             node = node->left;
        }
         return node;
    }

    // Funçao para remover um nó 
    Node* removeHelper(Node* node, int value) 
    {
        if (node == nullptr) {
            return nullptr;  // Nó não encontrado
        }
        if (value < node->data) {
            node->left = removeHelper(node->left, value);  // Remove à esquerda
        } else if (value > node->data) {
            node->right = removeHelper(node->right, value); // Remove à direita
        } else {  // Nó encontrado
         // Caso 1: Nó  sem filhos ou com apenas um fiho
            if (node->left == nullptr) {
                 Node* temp = node->right;
                delete  node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left; 
                delete node;
                return temp;
            }
        // Caso 2: Nó com dois filhos
                Node* temp = findMin(node->right);  
                node->data = temp->data;            
                node->right = removeHelper(node->right, temp->data); // Remove  o duplicado
        }
        return node;
    }
    void  inorderHelper(Node* node) 
    {
        if (node != nullptr) {
             inorderHelper(node->left);    // vai subárvore esquerda
             cout << node->data << " ";    // vai nó atual
             inorderHelper(node->right);   // vai subárvore direita
        }
    }

      // liberar memória
    void destroyHelper(Node* node) 
    {
        if (node !=  nullptr) {
            destroyHelper(node->left);
            destroyHelper(node->right);
            delete node;
        }
    }

public:
    BST() { root = nullptr; }  // Construtor

    ~BST() { destroyHelper(root); }  // liberar memória

    
    void insert(int value) {
        root = insertHelper(root,  value);
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

// principal para testar a árvore
int main() 
{
    BST tree;

    // Inserir valores
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);

    
    cout << "Percurso em-ordem: ";
    tree.inorder();

    // Buscando valores
    cout << "Busca 7: " << (tree.search(7) ? "Encontrado" : "Nao encontrado") << endl;
    cout << "Busca 8: " << (tree.search(8) ? "Encontrado" : "Nao encontrado") << endl;

    // Removendo um valor
    cout << "Removendo 5..." << endl;
    tree.remove(5);
    cout << "Novo percurso em ordem: ";
    tree.inorder(); 

    return 0;
}