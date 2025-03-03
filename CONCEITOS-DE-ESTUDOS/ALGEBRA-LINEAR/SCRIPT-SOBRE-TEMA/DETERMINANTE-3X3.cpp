
#include <iostream>
using namespace std; 

//caucula a determinante
double determinante3x3(double a, double  b, double c, double d,  double e, double f, double g, double h, double i ) {
    double determinante  = a * (e * i -  f * h) - b * (d *  i - f * g) +  c * (d * h - e * g);
    return determinante;  
}

int main() {
    double a, b, c, d, e, f, g, h, i;


    cout << "Insira os elementos da matriz 3x3:" << endl;
    cout << "Elemento (a): "; cin >> a;
    cout << "Elemento (b): "; cin >> b;
    cout << "Elemento (c): "; cin >> c; 
    cout << "Elemento (d): "; cin >> d;
    cout << "Elemento (e): "; cin >> e;
    cout << "Elemento (f): "; cin >> f; 
    cout << "Elemento (g): "; cin >> g;
    cout << "Elemento (h): "; cin >> h;
    cout << "Elemento (i): "; cin >> i;

    double determinante = determinante3x3(a, b, c, d, e, f, g, h, i); 

    cout << "Determinante da matriz:  "  << determinante << endl;
    return 0;
}