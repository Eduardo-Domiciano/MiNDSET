/// Funções são blocos de contrução de codigo, executando todo o codigo dentro de seu escopo
/// Eles podem receber quantos parametros forem nescessários.

///Vou começar explicando alguns tipos de funções depois vamos expandindo aos poucos esse
/// intendimento.



/// #1. FUNÇÕES DECLARADAS:  Funções declaradas são as que sao definjidas por pela palavra chave "function", seguida
///pelo nome da função e parenteses com ou sem parametros. Como padrao java script todo
///o bloco de codigo executavel deve estar entre "{}".
function declaradas(paramentro)
{
    return paramentro
}
console.log(declaradas("1. Funções declaradas são a forma padrao de declarar funções."))



/// #2. FUNÇÕES EXPRESSAS: Funções Expressas podem ser declaradas como variaveis, sendo essas funções
/// nomeadas ou anonimas.
const expressas = function(textoExpresso)
{
    return console.log(textoExpresso);
}
expressas("2. As funções expressa pode ser nomeada colocando o nome entre a palavra chave function e o ().")



/// #3. ARROW FUNCTIONS: Arrow Functions são funções de uma forma mais simples, onde a palavra chave
/// function nao é nescessária.
const arrow = () => 
    {
        console.log("3. Parece bobeira uma função simples em um variavel, mas será muito usada no dia a dia.");
    };
arrow();



/// #4. FUNÇÕES AUTO-INVOCADAS: Funções Auto-Invocadas ou IIFE (Immediately Invocked Function Expression), são funções
/// que se envocam quando sao declaradas.
(function()
{
    console.log("4. Algumas dessas funções são ótimas para encapsulamento de codigo. Isso ajuda muito na leitura.")
})(); /// Na verdade ela é chamada por esse parenteses no final da expressão.



/// #5. FUNÇÕES CONSTRUTORAS: Funções são objetos em js, e o que a função contrutora faz é declarar uma classe.
/// Lembrando que como classe a primeira letra deve ser maiuscula.
/// Classes são objetos em js, mas eu vou criar um topico especifico para esse assunto.
function Pessoa(nome, idade, textoDoObj)
{
    this.textoDoObj = textoDoObj;
    this.nome = nome;
    this.idade = idade;
};
const eu = new Pessoa("Eduardo", 34, "5. Repare que a classe retorna um objeto.");
console.log(eu) /// Pra agora é o suficiente, mas vou falar melhor sobre isso no topico apropriado.
/// Um pequeno detalhe que se deve reparar é que apesar de o "textoDoObj" ter sido declarado por ultimo,
/// ele é retornado primeiro, isso acontece porque a função sempre retorna na ordem que o contrutor foi
/// escrito, mas eu mostro melhor no topico classes como buscar informações especificas e sobre metodos tbm.



/// #6. CALLBACK: Uma função Callback é um função passada a outra função como parametro, que é então invocado dentro da função
/// para completar alguma rotina  ou ação. É realmente mais dificil explicar do que fazer.
const callback = function(){console.log("6. Essa função auto-executavel recebe a função calback como parametro.")}; /// função msg

(function(funcao)
{
    return funcao()
})(callback); /// Como eu disse antes, esse ultimo parenteses chama a função auto-invocada, por isso o parametro deve ser
/// inserida nela.



/// #7. FUNÇÕES RECURSIVAS: Funções recursivas são usadas muitos para resolver problemas em subproblemas similares.
/// Basicamente são funções que se invocam dentro de si mesma, obviamente mantendo uma condição de parada.
function recursiva(n)
{
    if(n == 0)
    {console.log(`7. Se o parametro for igual a 0, ele imprimi essa msg, mas no caso de nao, ele se executa de novo, 
    com o novo parametro e recomeça a validação, continuando em um loop infinito, até a condição alcançada.`);
    }else{ recursiva(n - 1)};
    
}
recursiva(1)

/// #8. ORDEM SUPERIOR: Funções de Ordem Superior são funções que recebem funções ou abstraem a logica.
function ordemSuperior(num, operacao)
{
    return console.log(`8. A ideia aqui é que você possa passar um script como parametro a ser executado pela função.`, operacao(num));
}
ordemSuperior(10, num => num * 2)


console.log(`
    ===>  Lembrando que eu nao conheço tao bem todos esses modelos ainda, o que temos aqui são modelos que podem ser usados e
    que eu possa catalogar aqui para o meu proprio uso e nescessidade. Sigo estudando mais sobre elas e adquirindo aos poucos
    o conhecimento nescessário pra evoluir na linguagem.`)