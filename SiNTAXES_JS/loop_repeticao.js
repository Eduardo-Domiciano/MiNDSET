///Loop é um algoritmo capaz de gerar um laço de repetição continuo
/// em um bloco de codigo, até que um condição seja atinjida.
/// Em linguagem de programação isso é chamado iteração.


/// O "for" declara um iterador "i" e compara com o valor escolhido "5"
/// enquanto "i" for menor quer 5, ele soma o valor de i+1 em "i++".
/// quando "i" for igual a 5, o loop é encerrado.
function loop_for()
{
    for(i=0; i<5; i++)
    {
        console.log("teste de loop ", i);
    }
}

/// O while apesar de ser declarado de forma diferente, ele faz o mesmo processo.
/// Lembrando que o "i" iterador deve ser declarado antes do loop, e o
/// incrementador "i++" deve ser adicionado dentro do bloco de codigo do while.
function loop_while()
{
    let i=0;
    while(i<5)
    {
        console.log("teste loop ", i);
        i++;
    };
    
}

/// O do é quase igual o while, mas a diferença é que ele é sempre capaz
/// de executar uma vez o bloco de codigo, ja que a condicional "while",
/// é declarada apenas no final.
function loop_do()
{
    let i=0;
    do
    {
        console.log("teste loop ", i);
        i++;
    }while(i<5);
}

/// Lembrando que as condicionais "i<5" que decidem se devem parar ou nao o loop,
/// elas retornam um valor boleano "True" ou "False".