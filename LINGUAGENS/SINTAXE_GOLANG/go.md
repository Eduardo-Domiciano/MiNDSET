# Anotações sobre sintaxe Go

Go é uma linguagem compilada de propósito geral. O arquivo `.go` vira um executável: o compilador lê o texto e gera o programa. Todo arquivo começa com `package`. O programa que se executa sozinho usa `package main` e a função `main`: é ali que a execução começa.

No terminal, `go run arquivo.go` compila e roda na hora. `go build -o programa arquivo.go` gera o executável `programa`. Vários arquivos do mesmo projeto pedem um módulo: na pasta, `go mod init exemplo` cria o `go.mod`.

A chave `{` fica na mesma linha do `if`, do `for` e da função. O compilador recusa a chave na linha de baixo. `gofmt` arruma recuo e espaços; o comando é `gofmt -w arquivo.go`.

## Módulo 1: Introdução

### Primeiro programa

Este exemplo é o menor programa que produz um resultado visível. Ele serve para conferir se o Go está instalado. `import "fmt"` traz o pacote de formatação e impressão. `fmt.Println` escreve a frase e pula a linha. Salve como `.go` e rode com `go run`.

```go
package main

import "fmt"

func main() {
	fmt.Println("hello, world!")
}
```

### Comentários

Comentário é texto que o compilador ignora. Serve para anotar o motivo de um trecho. `//` vale até o fim da linha. `/*` e `*/` fecham um bloco de várias linhas.

```go
package main

import "fmt"

func main() {
	// uma linha
	fmt.Println("o comentário não aparece na saída")
}
```

## Módulo 2: Variáveis e tipos de dados

Uma variável é um nome para um valor. O tipo diz o que cabe ali e quais operações fazem sentido. Fora de função, `var` declara. Dentro de função, `:=` declara e atribui de uma vez, e o tipo sai do valor da direita.

`int` guarda inteiro. `float64` guarda número com parte decimal. `string` guarda texto. `bool` guarda verdadeiro ou falso. `rune` guarda um caractere Unicode e se escreve entre aspas simples; texto vai entre aspas duplas. `fmt.Println` mostra a rune como número. `string(letra)` entrega o caractere.

O decimal usa ponto. Uma variável declarada e não usada é erro de compilação. O mesmo vale para um `import` que o arquivo não usa.

```go
package main

import "fmt"

func main() {
	var idade int = 35
	altura := 1.75
	nome := "João"
	letra := 'A'
	isProgramador := true

	fmt.Println(idade, altura, nome, string(letra), isProgramador)
}
```

Cada tipo tem um valor zero, o conteúdo de uma variável declarada sem atribuição: `0` para número, `""` para texto, `false` para `bool`. `const` cria um nome fixo. O valor de uma constante não recebe outra atribuição.

```go
package main

import "fmt"

func main() {
	var contador int
	const pi = 3.14

	fmt.Println(contador, pi)
}
```

| Valor | Tipo | Para que serve |
| --- | --- | --- |
| `35` | `int` | Contagem, idade, índice |
| `1.75` | `float64` | Medida, média |
| `"João"` | `string` | Texto |
| `'A'` | `rune` | Um caractere |
| `true`, `false` | `bool` | Uma condição |

## Módulo 3: Operações

Os operadores aritméticos calculam. Servem para qualquer conta direta, sem função. Com dois `int`, `/` devolve o quociente inteiro: `9 / 2` vale `4`. Com `float64`, `/` conserva a parte decimal. `%` devolve o resto, útil para saber se um número é par (`n % 2 == 0`).

```go
package main

import "fmt"

func main() {
	fmt.Println("Soma:", 2+3)
	fmt.Println("Subtração:", 10-4)
	fmt.Println("Multiplicação:", 7*5)
	fmt.Println("Divisão inteira:", 9/2)
	fmt.Println("Divisão:", 9.0/2)
	fmt.Println("Resto:", 9%2)
}
```

Comparação devolve `bool`: `==`, `!=`, `>`, `<`, `>=`, `<=`. `&&`, `||` e `!` juntam condições.

```go
package main

import "fmt"

func main() {
	idade := 19
	fmt.Println(idade >= 18 && idade < 60)
}
```

## Módulo 4: Strings

String é texto, entre aspas duplas. Serve para nome, mensagem e qualquer frase que o programa mostre ou compare. O texto, depois de criado, não se altera no lugar: uma mudança produz outra string.

`+` junta textos. `fmt.Printf` monta a frase com verbos de formato: `%s` é texto, `%d` é inteiro, `\n` pula a linha. `fmt.Sprintf` devolve a frase pronta, em vez de imprimir.

`len` conta bytes. Num texto com acento, a quantidade de letras e a quantidade de bytes divergem. O `for` com `range` percorre cada caractere.

```go
package main

import "fmt"

func main() {
	nome := "Maria"
	sobrenome := "Silva"
	idade := 35

	fmt.Println(nome + " " + sobrenome)
	fmt.Printf("%s tem %d anos.\n", nome, idade)

	frase := fmt.Sprintf("%s %s", nome, sobrenome)
	fmt.Println(frase)
}
```

## Módulo 5: Estrutura de controle

O programa segue as linhas de cima para baixo, a menos que uma estrutura de controle mude o caminho. Condicionais escolhem um bloco. O `for` repete um bloco.

### Condicionais (if, else if, else)

O `if` executa o bloco quando a condição é verdadeira. O `else if` testa outra condição só se as anteriores falharam. O `else` é o caminho restante. Serve para regras do tipo “se a idade permite, faça isto; senão, faça aquilo”. A condição fica sem parênteses. A chave abre na mesma linha.

```go
package main

import "fmt"

func main() {
	idade := 18

	if idade >= 18 {
		fmt.Println("Você é maior de idade.")
	} else if idade >= 12 {
		fmt.Println("Você é adolescente.")
	} else {
		fmt.Println("Você é criança.")
	}
}
```

O `if` pode declarar uma variável que só existe nesse `if` e no `else` ligado a ele. O ponto e vírgula separa a declaração da condição.

```go
package main

import "fmt"

func main() {
	if idade := 18; idade >= 18 {
		fmt.Println("maior de idade, idade local:", idade)
	}
}
```

### for

Go tem um laço: o `for`. As três formas cobrem contagem, repetição enquanto uma condição vale e percurso de uma coleção.

A forma com três partes serve quando se sabe quantas voltas dar. `i := 0` cria o contador, `i < 5` é a condição, `i++` avança no fim de cada volta. A volta com `i` igual a `5` não acontece.

A forma só com condição repete enquanto ela for verdadeira. O contador nasce fora e muda dentro do bloco. Se a condição nunca ficar falsa, o laço não acaba.

`range` percorre cada item. No slice, a volta entrega o índice e o valor. O índice que não entra na conta se descarta com `_`.

```go
package main

import "fmt"

func main() {
	for i := 0; i < 5; i++ {
		fmt.Println("volta", i)
	}

	contador := 0
	for contador < 3 {
		fmt.Println("Oi")
		contador++
	}

	numeros := []int{1, 2, 3, 4}
	for _, numero := range numeros {
		fmt.Println("item:", numero)
	}
}
```

`++` soma um. `contador += 1` faz a mesma conta.

### switch

O `switch` escolhe um caminho entre vários valores. Serve quando um `if` com muitas ramificações compara a mesma variável. Cada `case` termina sozinho: o fluxo sai do `switch` ao fim do caso escolhido. `default` é o caminho restante. Vários valores no mesmo `case` se separam por vírgula.

```go
package main

import "fmt"

func main() {
	dia := 3

	switch dia {
	case 1:
		fmt.Println("segunda")
	case 2, 3:
		fmt.Println("meio da semana")
	default:
		fmt.Println("outro dia")
	}
}
```

## Módulo 6: Funções

Uma função é um bloco com nome. Ela serve para escrever uma tarefa uma vez e chamá-la de vários pontos. `func` define. Os parâmetros declaram o tipo. O tipo depois dos parênteses é o retorno. `return` entrega o resultado e encerra a função. Parâmetros do mesmo tipo podem compartilhar uma escrita só: `a, b int`.

A função fica fora de `main`, no mesmo pacote. A chamada usa o nome e os argumentos.

```go
package main

import "fmt"

func soma(a, b int) int {
	return a + b
}

func main() {
	resultado := soma(10, 5)
	fmt.Println(resultado)
}
```

Uma função pode devolver mais de um valor. O par usual é o resultado e um `error`. `nil` no erro significa que a conta deu certo. Quem chama testa `err != nil` antes de usar o resultado. `fmt.Errorf` monta o erro com uma mensagem.

```go
package main

import "fmt"

func dividir(a, b float64) (float64, error) {
	if b == 0 {
		return 0, fmt.Errorf("divisão por zero")
	}
	return a / b, nil
}

func main() {
	resultado, err := dividir(10, 2)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(resultado)
}
```

## Módulo 7: Arrays e slices

O array guarda vários valores do mesmo tipo. O tamanho faz parte do tipo: `[3]int` e `[4]int` são tipos diferentes. O tamanho é fixo. O índice começa em zero. Serve para uma coleção pequena e de tamanho conhecido.

```go
package main

import "fmt"

func main() {
	numeros := [3]int{1, 2, 3}
	fmt.Println(numeros[0])
	fmt.Println(len(numeros))
}
```

A slice é a sequência de tamanho variável. Serve para notas, nomes ou qualquer lista que precise crescer. Escreve-se `[]int`, sem número entre os colchetes. `append` devolve a slice com o item novo no fim; o resultado volta para a mesma variável. `len` diz quantos itens existem. Passar de um índice que não existe é erro e encerra o programa.

```go
package main

import "fmt"

func main() {
	numeros := []int{1, 2, 3, 4}
	fmt.Println(numeros[0])
	fmt.Println(numeros[2])

	numeros = append(numeros, 5)
	fmt.Println("último:", numeros[len(numeros)-1])
	fmt.Println("quantidade:", len(numeros))
}
```

## Módulo 8: Mapas

O mapa guarda pares de chave e valor. Serve para achar um dado pelo nome, como a nota de uma pessoa. Todas as chaves têm o mesmo tipo, e todos os valores também. `make` cria o mapa vazio. A chave entre colchetes lê e grava.

A leitura devolve dois resultados: o valor e um `bool`. O `bool` diz se a chave existia. Sem esse segundo resultado, uma chave ausente devolve o valor zero do tipo, e o programa não distingue “zero gravado” de “chave que não está no mapa”.

A ordem das chaves numa volta com `range` muda de execução para execução.

```go
package main

import "fmt"

func main() {
	notas := map[string]float64{
		"Ana": 8.5,
	}
	notas["Bruno"] = 7

	nota, ok := notas["Ana"]
	if ok {
		fmt.Println("Ana:", nota)
	}
	fmt.Println("quantidade:", len(notas))
}
```

## Módulo 9: Structs e métodos

Go agrupa dados numa `struct` e pendura funções nesse tipo. Essas funções se chamam métodos. O conjunto faz o papel do molde: vários dados e as ações que os usam andam juntos.

O trecho `(p Pessoa)` antes do nome é o receptor. Dentro do método, `p` é o valor daquela pessoa. A chamada usa ponto: `p1.saudacao()`.

```go
package main

import "fmt"

type Pessoa struct {
	Nome  string
	Idade int
}

func (p Pessoa) saudacao() {
	fmt.Printf("Oi, meu nome é %s e tenho %d anos.\n", p.Nome, p.Idade)
}

func main() {
	p1 := Pessoa{Nome: "Ana", Idade: 25}
	p1.saudacao()
}
```

O exemplo do carro guarda um estado (`ligado`) e oferece ações que mudam esse estado. O receptor `*Carro` é um ponteiro: o método recebe o endereço do carro e altera o próprio objeto. Com receptor sem `*`, o método receberia uma cópia, e `ligado = true` morreria ao fim da função. Na chamada, `meuCarro.ligar()` continua igual; o compilador usa o endereço da variável.

```go
package main

import "fmt"

type Carro struct {
	Marca  string
	Modelo string
	Ano    int
	ligado bool
}

func (c *Carro) ligar() {
	c.ligado = true
	fmt.Printf("%s está ligado.\n", c.Modelo)
}

func (c *Carro) desligar() {
	c.ligado = false
	fmt.Printf("%s está desligado.\n", c.Modelo)
}

func (c Carro) info() {
	fmt.Printf("%d %s %s - Ligado: %t\n", c.Ano, c.Marca, c.Modelo, c.ligado)
}

func main() {
	meuCarro := Carro{Marca: "Toyota", Modelo: "Corolla", Ano: 2020}
	meuCarro.info()
	meuCarro.ligar()
	meuCarro.info()
	meuCarro.desligar()
}
```

## Módulo 10: Visibilidade, composição e interfaces

Esses três mecanismos organizam o programa quando os dados e os métodos crescem. A inicial maiúscula decide quem enxerga o nome. A composição junta structs. A interface descreve um conjunto de métodos, e qualquer tipo que tenha esses métodos entra no lugar dela.

### Visibilidade

O nome com inicial maiúscula é exportado: outro pacote pode usá-lo. O nome com inicial minúscula fica no pacote. Serve para esconder um detalhe e expor só a ação. O saldo muda por `depositar` e `sacar`. Uma atribuição de fora do pacote não alcança `saldo`.

No mesmo arquivo, o método enxerga o campo minúsculo, porque arquivo e tipo estão no mesmo pacote.

```go
package main

import "fmt"

type ContaBancaria struct {
	Titular string
	saldo   float64
}

func (c *ContaBancaria) depositar(valor float64) {
	c.saldo += valor
}

func (c *ContaBancaria) sacar(valor float64) {
	if valor <= c.saldo {
		c.saldo -= valor
		return
	}
	fmt.Println("Saldo insuficiente.")
}

func (c ContaBancaria) mostrarSaldo() {
	fmt.Printf("Saldo de %s: R$ %.2f\n", c.Titular, c.saldo)
}

func main() {
	banco := ContaBancaria{Titular: "Ana", saldo: 2000}
	banco.depositar(200)
	banco.sacar(50)
	banco.mostrarSaldo()
}
```

### Composição

Uma struct pode incluir outra. Os campos e os métodos do tipo incluído passam a responder também no tipo de fora. `Cachorro` inclui `Animal`, então `dog.Nome` chega ao nome sem copiar o campo. O método `Falar` escrito em `Cachorro` é o que responde em `dog.Falar()`. O método de `Animal` continua em `dog.Animal.Falar()`.

```go
package main

import "fmt"

type Animal struct {
	Nome string
}

func (a Animal) Falar() {
	fmt.Println("O animal faz um som.")
}

type Cachorro struct {
	Animal
}

func (c Cachorro) Falar() {
	fmt.Printf("%s diz: au au!\n", c.Nome)
}

type Gato struct {
	Animal
}

func (g Gato) Falar() {
	fmt.Printf("%s diz: miau!\n", g.Nome)
}

func main() {
	dog := Cachorro{Animal: Animal{Nome: "Rex"}}
	cat := Gato{Animal: Animal{Nome: "Kat"}}
	dog.Falar()
	cat.Falar()
}
```

### Interfaces

A interface lista métodos, sem corpo. Um tipo a satisfaz quando tem esses métodos, com o mesmo nome e a mesma assinatura. Não há palavra para “implementar”: a correspondência é pelos métodos.

`apresentar` recebe um `Falante`. `Cachorro` e `Gato` servem, porque os dois têm `Falar()`. A função chama `Falar` e cada valor executa o próprio método. Esse é o ponto em que o mesmo nome produz efeitos diferentes conforme o tipo concreto.

```go
package main

import "fmt"

type Falante interface {
	Falar()
}

type Animal struct {
	Nome string
}

type Cachorro struct {
	Animal
}

func (c Cachorro) Falar() {
	fmt.Printf("%s diz: au au!\n", c.Nome)
}

type Gato struct {
	Animal
}

func (g Gato) Falar() {
	fmt.Printf("%s diz: miau!\n", g.Nome)
}

func apresentar(animal Falante) {
	animal.Falar()
}

func main() {
	dog := Cachorro{Animal: Animal{Nome: "Rex"}}
	cat := Gato{Animal: Animal{Nome: "Kat"}}
	apresentar(dog)
	apresentar(cat)
}
```

A interface também é o contrato de uma família de tipos. Toda forma que entra numa função de área precisa do método `Area() float64`. `Retangulo` entra porque tem esse método. Quem escreve a função depende do contrato, e cada forma traz o próprio cálculo.

```go
package main

import "fmt"

type Forma interface {
	Area() float64
}

type Retangulo struct {
	Largura float64
	Altura  float64
}

func (r Retangulo) Area() float64 {
	return r.Largura * r.Altura
}

func imprimirArea(f Forma) {
	fmt.Println(f.Area())
}

func main() {
	ret := Retangulo{Largura: 10, Altura: 5}
	imprimirArea(ret)
}
```

## Módulo 11: defer

`defer` agenda uma chamada para o momento em que a função atual terminar. Serve para fechar o que foi aberto: arquivo, conexão, trava. A chamada adiada fica junto da abertura, e o encerramento acontece em qualquer saída da função, inclusive no `return` do meio.

Vários `defer` rodam na ordem inversa: o último agendado é o primeiro a executar.

```go
package main

import "fmt"

func main() {
	defer fmt.Println("3. ao sair de main")
	fmt.Println("1. começo")
	fmt.Println("2. meio")
}
```

## Módulo 12: Pacotes da biblioteca padrão

A biblioteca padrão acompanha o compilador. Cada `import` traz um pacote. O nome antes do ponto é o nome do pacote: `math.Sqrt`, `sort.Ints`.

### math

O pacote `math` reúne contas que não cabem num operador: raiz, seno, arredondamento. `math.Sqrt` devolve a raiz quadrada como `float64`. O número `16` entra direto porque uma constante numérica se adapta ao tipo que a função espera.

```go
package main

import (
	"fmt"
	"math"
)

func main() {
	resultado := math.Sqrt(16)
	fmt.Println("Raiz quadrada de 16 é:", resultado)
}
```

### sort

O pacote `sort` ordena slices. `sort.Ints` coloca os inteiros em ordem crescente e altera a própria slice. Serve para ranking ou para percorrer valores em ordem. Quem precisa da lista original guarda uma cópia antes da chamada.

```go
package main

import (
	"fmt"
	"sort"
)

func main() {
	numeros := []int{5, 3, 1, 4, 2}
	sort.Ints(numeros)

	for _, numero := range numeros {
		fmt.Println(numero)
	}
}
```
