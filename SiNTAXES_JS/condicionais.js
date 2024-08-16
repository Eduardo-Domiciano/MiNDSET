///Condcionais são uma forma de permitir o software de tomar decisões

/// O if é uma condicional que executa uma tarefa a partir de uma validação de verdade3iro ou falso
/// Aqui, criei uma função que testa esse processo. Quando a função é chamada,
///ele valida o parametro "valor", se for verdadeiro, ele imprimi o bloco do if.
///Se for falso, ele imprimi o bloco do else if, e se nao encontrar nenhum valor, ele imprimi o else.
function condicionais_if(valor)
{
    if(valor == true)
    {
        console.log("O valor é verdadeiro =>", valor)
    }else if(valor == false)
    {
        console.log("O valor é falso =>", valor)
    }else{console.log("valor nao encontrado!")}
}
//condicionais_if(false)


// O Switch é uma melhor opção quando você tem uma quantidade maior de alternativas nescessárias
// para serem executadas, ela ainda pode ter uma opção padrão caso nenhuma das 
//alternativas sejam alcaçadas.
function condicional_switch(opcao) {
        
    switch(opcao)
    {
        case "Sim":
            console.log("opção sim ativada")
            break
        
        case "Nao":
            console.log("Opção Nao ativada")
            break
        
        default:
            console.log("Uma opção pra caso nenhum dos casos anteriores ativarem")

    }
}

//condicional_switch("5")

// Uma ultima opção é o operador ternário. Ele basicamente tem duas opções, uma se a
// condição for true e outra se a condição for false. É uma boa opção para economizar com 
//linhas de codigo.

function condicionais_ternario(operador)
{
    return operador
        ? "O operador é true!"
        : "O operador é false!"
}

console.log(condicionais_ternario(true))
