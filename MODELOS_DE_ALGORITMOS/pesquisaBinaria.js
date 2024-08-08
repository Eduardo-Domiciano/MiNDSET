// A pesquisa binaria é um algortitmo de busca em uma lista ordenada, onde
// em vez de comparar cada item de uma lista com o valor buscado, você
// elimina metade dos itens em cada comparação minimizando o trabalho, 
// ou melhor dizendo o processamento no processo de busca.

let lista1 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
console.log(binarySearch(lista1, 11))

function binarySearch(lista, numero) {
    let i = 0;
    let f = lista.length - 1;
    let m = Math.floor(i + (f - i) / 2);

    while(i <= f) {
        if(numero == lista[m]) {
            return m;
        }
        if(numero > lista[m]) {
            i = m + 1;
        }
        if(numero < lista[m]) {
            f = m -1;
        }
        m = Math.floor(i + (f - i) / 2)
    }
    
    return  lista[f];
}
