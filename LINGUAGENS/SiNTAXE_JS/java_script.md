# Anotações sobre sintaxe JavaScript

JavaScript roda no navegador e também no terminal, com o Node. Um arquivo `.js` não precisa de `main`: o interpretador executa o arquivo de cima para baixo. No terminal, `node arquivo.js`. No navegador, o mesmo código pode ir numa tag `script` ou no console das ferramentas de desenvolvedor. `console.log` escreve na saída, no papel do `std::cout` do C++.

## Módulo 1: Introdução

### Primeiro programa

Este exemplo é o menor script que produz um resultado visível. Ele serve para conferir se o Node está instalado e para ver como um texto chega à tela. Use-o como primeiro arquivo de qualquer exercício: salve como `.js` e rode com `node`.

```js
console.log("hello, world!");
```

### Comentários

Comentário é texto que o interpretador ignora. Serve para anotar o motivo de um trecho, não para repetir o que a linha já diz. `//` vale até o fim da linha. `/* */` cobre várias linhas.

```js
// uma linha
/* várias
   linhas */
console.log("o comentário não aparece na saída");
```

## Módulo 2: Variáveis e tipos de dados

Uma variável é um nome para um valor. `let` cria um nome cujo valor pode mudar. `const` cria um nome que não pode passar a apontar para outro valor. Use `const` por padrão e `let` quando o valor precisa ser trocado, como o contador de um laço. `var` é a forma antiga: vaza para fora do bloco e embaralha o código. Estes exemplos não usam `var`.

JavaScript não exige que você escreva o tipo. O valor é que tem tipo: número, texto, booleano, objeto, ou a ausência de valor.

```js
let idade = 35;
idade = 36;

const altura = 1.75;
const letra = "A";
const nome = "João";
const isProgramador = true;
```

| Valor | Tipo | Para que serve |
| --- | --- | --- |
| `35`, `1.75` | número | Conta, medida, índice. Não há `int` e `float` separados. |
| `"João"` | string | Texto. Aspas simples ou duplas dão no mesmo. |
| `true`, `false` | booleano | Uma condição: sim ou não. |
| `null` | ausência escolhida | “Aqui não há valor”, de propósito. |
| `undefined` | ainda sem valor | Variável declarada e não preenchida, ou propriedade que não existe. |

Texto longo ou com variável no meio usa crase. É um template: `${nome}` entra no texto já convertido para string.

```js
const nome = "João";
const idade = 35;
console.log(`${nome} tem ${idade} anos.`);
```

Comparação de valor usa `===` e `!==`. Os dois lados precisam ser do mesmo tipo e do mesmo conteúdo. `==` converte tipos antes de comparar (`"1" == 1` é verdadeiro) e esconde erro. Estes exemplos usam `===`.

```js
console.log(1 === 1);       // true
console.log(1 === "1");     // false
console.log(1 !== "1");     // true
```

## Módulo 3: Estrutura de controle

O script segue as linhas de cima para baixo, a menos que uma condicional escolha outro bloco ou um laço repita um bloco.

### Condicionais (if, else if, else)

O `if` executa o bloco quando a condição é verdadeira. O `else if` testa outra condição só se as anteriores falharam. O `else` é o caminho restante. Serve para regras do tipo “se a idade permite, faça isto; senão, faça aquilo”. A condição fica entre parênteses e o bloco, entre chaves.

```js
const idade = 18;

if (idade >= 18) {
    console.log("Você é maior de idade.");
} else if (idade >= 12) {
    console.log("Você é adolescente.");
} else {
    console.log("Você é criança.");
}
```

Uma função pode receber o valor e decidir dentro dela. Aqui o parâmetro já é booleano, então a condição é o próprio `valor`. Chame `condicionaisIf(true)`, `condicionaisIf(false)` ou outro valor para ver os três caminhos.

```js
function condicionaisIf(valor) {
    if (valor === true) {
        console.log("O valor é verdadeiro =>", valor);
    } else if (valor === false) {
        console.log("O valor é falso =>", valor);
    } else {
        console.log("valor não encontrado!");
    }
}

condicionaisIf(false);
```

### switch

O `switch` compara um único valor com várias alternativas. Serve quando há muitas opções do mesmo dado, como um item de menu, e uma cadeia de `else if` ficaria longa. Cada `case` termina com `break`. Sem `break`, a execução continua no caso seguinte. `default` roda quando nenhum `case` combina.

```js
function condicionalSwitch(opcao) {
    switch (opcao) {
        case "Sim":
            console.log("opção sim ativada");
            break;
        case "Nao":
            console.log("Opção Nao ativada");
            break;
        default:
            console.log("Uma opção para quando nenhum caso anterior combina");
    }
}

condicionalSwitch("Sim");
```

### Operador ternário

O ternário é uma expressão com dois resultados: um se a condição for verdadeira, outro se for falsa. Serve para escolher um valor em uma linha, como o texto de uma mensagem. Não serve para um bloco com várias ações: nesse caso o `if` continua mais claro. A forma é `condição ? valorSeVerdadeiro : valorSeFalso`.

```js
function condicionalTernario(operador) {
    return operador
        ? "O operador é true!"
        : "O operador é false!";
}

console.log(condicionalTernario(true));
```

### Loops (for, while, do-while)

Um laço repete um bloco enquanto a condição for verdadeira. Cada volta é uma iteração. A condição de parada precisa mudar dentro do laço; senão a repetição não acaba.

O `for` junta num só lugar o valor inicial, a condição e o passo. Serve quando se sabe quantas voltas dar, como imprimir de 0 a 4. `let i = 0` cria o contador, `i < 5` autoriza a volta, `i++` soma 1 ao fim de cada volta.

```js
function loopFor() {
    for (let i = 0; i < 5; i++) {
        console.log("teste de loop", i);
    }
}

loopFor();
```

O `while` testa antes de entrar. Se a condição já for falsa, o bloco não roda. O contador nasce fora do laço e o incremento fica dentro. Serve quando a quantidade de voltas depende de algo que muda durante a repetição, como ler linhas até o arquivo acabar.

```js
function loopWhile() {
    let i = 0;
    while (i < 5) {
        console.log("teste loop", i);
        i++;
    }
}

loopWhile();
```

O `do-while` executa o bloco e só depois testa. A primeira volta acontece mesmo que a condição seja falsa. Serve quando a ação precisa ocorrer pelo menos uma vez, como pedir um dado antes de saber se ele é válido.

```js
function loopDo() {
    let i = 0;
    do {
        console.log("teste loop", i);
        i++;
    } while (i < 5);
}

loopDo();
```

O `for...of` percorre os valores de uma lista, sem índice. Use-o para visitar cada item de um array. O `for` clássico continua útil quando a posição importa.

```js
const numeros = [10, 20, 30];

for (const numero of numeros) {
    console.log(numero);
}
```

## Módulo 4: Funções

Uma função é um bloco com nome, ou com um nome guardado numa variável. Ela serve para escrever uma tarefa uma vez e chamá-la de vários pontos. Parênteses recebem os parâmetros. Chaves delimitam o corpo. `return` entrega um valor a quem chamou e encerra a função. Sem `return`, a função devolve `undefined`.

### Função declarada

A forma começa com a palavra `function`, o nome e os parâmetros. Pode ser chamada em qualquer ponto do arquivo, mesmo numa linha anterior à definição. Use-a para uma ação nomeada do programa: calcular, validar, imprimir um relatório.

```js
function declarada(parametro) {
    return parametro;
}

console.log(declarada("Função declarada: function, nome e parâmetros."));
```

### Função expressa

A função vira o valor de uma variável. A chamada só funciona depois dessa linha, porque a variável ainda não existia. Serve para passar a função adiante ou para guardá-la com `const` e impedir que outro valor ocupe o mesmo nome. O nome entre `function` e `(` é opcional; sem ele, a função é anônima.

```js
const expressa = function (texto) {
    console.log(texto);
};

expressa("Função expressa: a função está guardada numa variável.");
```

### Arrow function

A arrow function é uma forma curta da função expressa. Não se escreve a palavra `function`. Depois dos parâmetros vem `=>` e o corpo. Serve para funções pequenas, sobretudo as que são passadas a outra função. Com uma expressão só, o `return` é implícito. Com várias linhas, usam-se chaves e `return`.

```js
const dobrar = (numero) => numero * 2;

const avisar = () => {
    console.log("Arrow function: função curta guardada numa variável.");
};

console.log(dobrar(10));
avisar();
```

### Retorno e parâmetros

O parâmetro é a entrada. O retorno é a saída. `soma` recebe dois números e devolve a adição. Quem chama guarda o resultado ou usa direto. Um parâmetro a mais é ignorado. Um a menos chega como `undefined`. Dá para declarar um valor padrão, usado quando o argumento não vem.

```js
function soma(a, b = 0) {
    return a + b;
}

const resultado = soma(5, 3);
console.log("A soma é:", resultado);
console.log("Sem o segundo argumento:", soma(5));
```

### Função autoinvocada (IIFE)

Uma IIFE (*Immediately Invoked Function Expression*) é uma função expressa chamada no mesmo instante em que é escrita. Os parênteses em volta transformam a função numa expressão. Os parênteses do fim fazem a chamada. Serve para rodar um preparo uma vez sem deixar nomes soltos no restante do arquivo.

```js
(function () {
    console.log("IIFE: estes parênteses finais chamam a função agora.");
})();
```

### Callback

Callback é uma função entregue a outra função como argumento. Quem recebe decide o momento de chamá-la. Serve para completar uma rotina com um comportamento que muda: ordenar com uma regra, avisar quando um cálculo terminar, percorrer uma lista e fazer algo com cada item.

```js
function executar(funcao) {
    funcao();
}

function mensagem() {
    console.log("Callback: esta função foi passada e chamada lá dentro.");
}

executar(mensagem);
```

### Função recursiva

Uma função recursiva chama a si mesma com um problema menor, até uma condição de parada. Sem essa condição, a chamada não acaba. Serve para estruturas que se repetem, como percorrer uma árvore ou calcular um fatorial. O exemplo abaixo conta de `n` até 0 e para quando chega em 0.

```js
function regressiva(n) {
    if (n === 0) {
        console.log("parou em 0");
        return;
    }
    console.log(n);
    regressiva(n - 1);
}

regressiva(3);
```

### Função de ordem superior

Função de ordem superior recebe uma função, ou devolve uma função. O callback é um caso disso. Serve para separar o dado da operação: a mesma função aplica a conta que você passar. No exemplo, `aplicar` não sabe se vai dobrar ou somar. Quem chama é que entrega a operação.

```js
function aplicar(numero, operacao) {
    return operacao(numero);
}

console.log(aplicar(10, (n) => n * 2));
console.log(aplicar(10, (n) => n + 1));
```

## Módulo 5: Arrays e strings

### Arrays

Um array guarda vários valores em posições numeradas a partir de zero. O tamanho muda: `push` acrescenta no fim, `pop` remove o último. Serve para lista de notas, nomes ou qualquer sequência que precise ser percorrida. O acesso é `numeros[i]`. `length` diz quantos itens existem. Passar de `length - 1` lê `undefined`.

```js
const numeros = [1, 2, 3, 4, 5];

for (let i = 0; i < numeros.length; i++) {
    console.log(numeros[i]);
}

numeros.push(6);
console.log(numeros);
```

### Strings

String é texto. Aspas criam o valor. `length` conta caracteres. Colchetes leem um caractere, também a partir de zero. Template com crase monta frase com variáveis. Serve para nome, mensagem, caminho e qualquer texto que o programa mostre ou compare.

```js
const texto = "Hello, World!";
console.log(texto);
console.log(texto.length);
console.log(texto[0]);

const nome = "Ana";
console.log(`Olá, ${nome}`);
```

## Módulo 6: Objetos

Um objeto agrupa dados com nome. Cada nome é uma propriedade. Serve para um registro: pessoa, produto, ponto na tela. O acesso usa ponto (`pessoa.nome`) ou colchetes (`pessoa["nome"]`). Os colchetes servem quando o nome da propriedade está numa variável. Um método é uma função guardada numa propriedade: `pessoa.saudacao()` usa os dados do próprio objeto.

```js
const pessoa = {
    nome: "João",
    idade: 30,
    saudacao() {
        console.log(`Nome: ${this.nome}`);
        console.log(`Idade: ${this.idade}`);
    }
};

pessoa.saudacao();
```

## Módulo 7: Função construtora e classe

### Função construtora

Uma função construtora fabrica objetos com os mesmos campos. Chama-se com `new`. Dentro dela, `this` é o objeto que está nascendo. Por convenção o nome começa com maiúscula, para não confundir com uma função comum. Serve quando vários objetos compartilham a mesma forma: várias pessoas, cada uma com nome e idade próprios. `new Pessoa(...)` devolve o objeto. As propriedades aparecem na ordem em que foram atribuídas a `this`.

```js
function Pessoa(nome, idade) {
    this.nome = nome;
    this.idade = idade;
    this.saudacao = function () {
        console.log(`Oi, meu nome é ${this.nome} e tenho ${this.idade} anos.`);
    };
}

const eu = new Pessoa("Ana", 25);
eu.saudacao();
```

### Classe

`class` é a forma atual do mesmo molde. O `constructor` recebe os dados iniciais e grava em `this`. Os métodos ficam no corpo da classe, sem a palavra `function`. Serve para o mesmo papel da construtora, com uma leitura mais próxima de outras linguagens. `new Pessoa(...)` cria o objeto. Herança usa `extends`: `Cachorro` é um `Animal` e substitui `som`.

```js
class Animal {
    som() {
        console.log("O animal faz um som.");
    }
}

class Cachorro extends Animal {
    som() {
        console.log("O cachorro late.");
    }
}

const c = new Cachorro();
c.som();
```

## Módulo 8: Objetos prontos da linguagem

JavaScript já traz funções para conta e para listas. Não é preciso escrever raiz quadrada nem ordenação.

### Math

`Math` reúne operações numéricas. `Math.sqrt` devolve a raiz quadrada. `Math.floor` arredonda para baixo, `Math.max` devolve o maior entre os argumentos. Use-as para não reescrever fórmula que a linguagem já entrega.

```js
const resultado = Math.sqrt(16);
console.log("Raiz quadrada de 16 é:", resultado);
```

### Ordenar um array

`sort` ordena o próprio array. Sem uma função de comparação, ele converte os itens para texto e ordena como palavras: `10` pode ficar antes de `2`. Com números, passe `(a, b) => a - b` para ordem crescente. Serve para ranking, busca depois da ordenação e qualquer lista que precise de ordem.

```js
const numeros = [5, 3, 1, 4, 2];
numeros.sort((a, b) => a - b);

for (const num of numeros) {
    console.log(num);
}
```
