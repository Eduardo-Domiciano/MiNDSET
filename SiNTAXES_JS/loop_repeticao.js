///Loop é um algoritmo capaz de gerar um laço de repetição continuo
/// em um bloco de codigo, até que um condição seja atinjida.
/// Em linguagem de programação isso é chamado iteração.


function loop_for()
{
    for(i=0; i<5; i++)
    {
        console.log("teste de loop ", i)
    }
}

function loop_while()
{
    let i=0;
    while(i<5)
    {
        console.log("teste loop ", i)
        i++
    }
    
}

loop_while()