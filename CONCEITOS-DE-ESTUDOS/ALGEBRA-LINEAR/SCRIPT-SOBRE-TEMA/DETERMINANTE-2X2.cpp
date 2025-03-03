#include <iostream>

using namespace std;

// Função que calcula matriz 2x2
float determinante2x2(float a, float b, float c, float d)
{
    return (a * d) - (b * c);
};

int main()
{
    float a, b, c, d;

    cout << "Digite os elementos da matriz 2x2:" << endl;

    cout << "Elemento A: ";
    cin >> a;

    cout << "Elemento B: ";
    cin >> b;

    cout << "Elemento C: ";
    cin >> c;

    cout << "Elemento D: ";
    cin >> d;

    cout << "Determinante da matriz 2x2: " << determinante2x2(a, b, c, d) << endl;

    return 0;
}