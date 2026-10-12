#include <iostream>
using namespace std;

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Verifica  se o elemento TA   no meio
        if (arr[mid] == target)
            return mid;

        // Se o elemeto alvo for  maior, ignora a metade  esquerda
        if (arr[mid] < target)
            left = mid + 1;

        // Se o elemento alvo for menor, ignora a metade direita
        else
            right = mid - 1;
    }

    // Se o elemento não estiver presente no array, retorna -1
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 10;
    int result = binarySearch(arr, size, target);

    if (result != -1)
        cout << "Elemento encontrado no índice: " << result << endl;
    else
        cout << "Elemento não encontrado." << endl;

    return 0;
}
