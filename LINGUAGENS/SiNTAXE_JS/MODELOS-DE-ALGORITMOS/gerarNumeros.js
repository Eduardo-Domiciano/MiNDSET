/// Pra gerar numeros aleatórios, você pode usar Math.random
/// O parseInt aqui faz o trabalho de arredondar para um numero inteiro, uma vez que por padrao
// o Math.random, gera numeros decimnais

/// Aqui eu usei um loop para gerar 6 numeros pq eu vou usar esse algoritmo pra jogar na mega sena.
/// Nao é zuera!

function numeros(min, max)
{
    for(let i=0; i<6; i++)
    {
        let valor = parseInt(Math.random() * (max - min) + min)
        console.log(valor)
    }
}

numeros(1, 60)