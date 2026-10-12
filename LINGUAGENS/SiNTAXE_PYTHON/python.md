# Anotações sobre sintaxe Python

Python é uma linguagem de propósito geral. O arquivo `.py` é executado de cima para baixo. Não há função `main` obrigatória: a primeira linha já vale. No terminal, `python3 arquivo.py`. `print` escreve na tela.

A indentação faz parte da sintaxe. O bloco de um `if`, de um `for` ou de uma função é o que está recuado debaixo dele, em geral quatro espaços. Um recuo errado é erro de programa, não só de estilo.

## Módulo 1: Introdução

### Primeiro programa

Este exemplo é o menor script que produz um resultado visível. Ele serve para conferir se o Python está instalado. Salve como `.py` e rode com `python3`.

```python
print("hello, world!")
```

### Comentários

Comentário é texto que o interpretador ignora. Serve para anotar o motivo de um trecho. `#` vale até o fim da linha. Três aspas fecham um texto longo, útil em explicação de classe. Esse texto longo, se ficar sozinho no começo de uma função ou classe, vira a documentação dela.

```python
# uma linha
print("o comentário não aparece na saída")
```

## Módulo 2: Variáveis e tipos de dados

Uma variável é um nome para um valor. Não se escreve o tipo na frente: o valor é que tem tipo. O nome passa a apontar para outro valor quando recebe uma atribuição nova.

`type` mostra o tipo. Use-o quando a conta der um resultado estranho: muitas vezes o valor não é do tipo que o nome sugere.

```python
x = 10            # int, inteiro
y = 3.14          # float, número com parte decimal
nome = "Ana"      # str, texto
vivo = True       # bool, verdadeiro ou falso

print(type(x), type(y), type(nome), type(vivo))
```

O decimal usa ponto, não vírgula. `3,14` não é um float: a vírgula monta uma tupla `(3, 14)`, dois inteiros empacotados. `True` e `False` começam com maiúscula e não vão entre aspas. `"True"` é texto, e texto não entra numa condição do jeito que um booleano entra.

| Valor | Tipo | Para que serve |
| --- | --- | --- |
| `10` | `int` | Contagem, idade, índice |
| `3.14` | `float` | Medida, média, dinheiro em cálculo simples |
| `"Ana"` | `str` | Texto |
| `True`, `False` | `bool` | Uma condição |
| `None` | ausência | “Aqui não há valor”, de propósito |

## Módulo 3: Operações

Os operadores aritméticos calculam. Servem para qualquer conta direta, sem função. A divisão `/` sempre devolve `float`. `//` devolve o quociente inteiro. `%` devolve o resto, útil para saber se um número é par (`n % 2 == 0`). `**` é potência.

```python
print("Soma:", 2 + 3)
print("Subtração:", 10 - 4)
print("Multiplicação:", 7 * 5)
print("Divisão:", 8 / 2)
print("Divisão inteira:", 9 // 2)
print("Resto:", 9 % 2)
print("Potência:", 2 ** 3)
```

Comparação devolve `True` ou `False`: `==`, `!=`, `>`, `<`, `>=`, `<=`. `and`, `or` e `not` juntam condições.

```python
idade = 19
print(idade >= 18 and idade < 60)
```

## Módulo 4: Strings

String é texto, entre aspas simples ou duplas. Serve para nome, mensagem e qualquer frase que o programa mostre ou compare.

`+` junta textos. Não junta texto com número: converta o número com `str` ou, melhor, use uma f-string. `*` repete o texto. A f-string começa com `f` antes das aspas e coloca variáveis dentro de `{}`.

```python
nome = "Maria"
sobrenome = "Silva"
idade = 35

print(nome + " " + sobrenome)
print("Olá " * 3)
print(f"{nome} tem {idade} anos.")
```

## Módulo 5: Estrutura de controle

### Condicionais (if, elif, else)

O `if` executa o bloco recuado quando a condição é verdadeira. O `elif` testa outra condição só se as anteriores falharam. O `else` é o caminho restante. Serve para regras do tipo “se a idade permite, faça isto; senão, faça aquilo”. Não há chaves: o recuo marca o bloco.

```python
idade = 18

if idade >= 18:
    print("Você é maior de idade.")
elif idade >= 12:
    print("Você é adolescente.")
else:
    print("Você é criança.")
```

### for

O `for` percorre cada item de uma sequência. Serve para visitar uma lista, um texto ou uma faixa de números, sem controlar o índice na mão. `range(5)` produz `0, 1, 2, 3, 4`. `range` não inclui o número final.

```python
numeros = [1, 2, 3, 4]

for numero in numeros:
    print("item da lista:", numero)

for i in range(5):
    print("volta", i)
```

### while

O `while` repete enquanto a condição for verdadeira. O contador nasce fora e muda dentro do bloco. Serve quando a quantidade de voltas depende de algo que muda durante a repetição. Se a condição nunca ficar falsa, o laço não acaba.

```python
contador = 0

while contador < 3:
    print("Oi")
    contador += 1
```

`+= 1` é o mesmo que `contador = contador + 1`.

## Módulo 6: Funções

Uma função é um bloco com nome. Ela serve para escrever uma tarefa uma vez e chamá-la de vários pontos. `def` define. Os parâmetros ficam entre parênteses. `return` entrega o resultado e encerra a função. Sem `return`, a função devolve `None`.

A chamada usa o nome e os argumentos. Quem chama guarda o retorno numa variável ou usa direto.

```python
def soma(a, b):
    return a + b

resultado = soma(10, 5)
print(resultado)
```

Um parâmetro pode ter valor padrão, usado quando o argumento não vem.

```python
def soma(a, b=0):
    return a + b

print(soma(5))
```

## Módulo 7: Listas

Uma lista guarda vários valores em posições numeradas a partir de zero. O tamanho muda. Serve para notas, nomes ou qualquer sequência que precise crescer. `append` acrescenta no fim. `len` diz quantos itens existem. Índice negativo conta do fim: `-1` é o último. Passar de um índice que não existe é erro.

```python
numeros = [1, 2, 3, 4]
print(numeros)
print(numeros[0])
print(numeros[2])

numeros.append(5)
print("último:", numeros[-1])
print("quantidade:", len(numeros))
```

## Módulo 8: Dicionário e tupla

O dicionário guarda pares de chave e valor. Serve para um registro com campos nomeados, como uma pessoa, quando ainda não faz sentido criar uma classe. O acesso usa a chave entre colchetes.

```python
pessoa = {"nome": "João", "idade": 30}
print(pessoa["nome"])
pessoa["idade"] = 31
```

A tupla também é uma sequência, mas não muda depois de criada. Serve para um grupo fixo, como coordenadas. A vírgula é o que a forma, não os parênteses.

```python
ponto = (10, 20)
print(ponto[0])
```

## Módulo 9: Classes e objetos

Uma classe é o molde. Um objeto é um exemplar desse molde, criado ao chamar a classe como se fosse uma função. Serve quando vários dados e as ações que os usam devem andar juntos: um carro tem marca e também liga.

`__init__` é o inicializador. Ele roda sozinho na criação e grava os dados no objeto. `self` é o próprio objeto. Todo método recebe `self` como primeiro parâmetro. Na chamada, esse argumento não se escreve: `objeto.mostrar_info()` já entrega o objeto como `self`.

O acesso aos campos e métodos usa ponto.

```python
class ClasseDeTeste:
    def __init__(self, parametro1, parametro2):
        self.parametro1 = parametro1
        self.parametro2 = parametro2

    def mostrar_info(self):
        print(f"parâmetro 1: {self.parametro1}, parâmetro 2: {self.parametro2}")

objeto = ClasseDeTeste("primeiro", "segundo")
objeto.mostrar_info()
```

O exemplo do carro guarda um estado (`ligado`) e oferece ações que mudam esse estado. Crie o objeto com a marca, o modelo e o ano. Chame `info` para ler, `ligar` e `desligar` para mudar.

```python
class Carro:
    def __init__(self, marca, modelo, ano):
        self.marca = marca
        self.modelo = modelo
        self.ano = ano
        self.ligado = False

    def ligar(self):
        self.ligado = True
        print(f"{self.modelo} está ligado.")

    def desligar(self):
        self.ligado = False
        print(f"{self.modelo} está desligado.")

    def info(self):
        print(f"{self.ano} {self.marca} {self.modelo} - Ligado: {self.ligado}")

meu_carro = Carro("Toyota", "Corolla", 2020)
meu_carro.info()
meu_carro.ligar()
meu_carro.info()
meu_carro.desligar()
```

## Módulo 10: Os quatro pilares

Programação orientada a objetos organiza o código em objetos. Cada objeto junta dados (atributos) e ações (métodos). Os quatro pilares nomeiam quatro jeitos de organizar essa relação.

### Encapsulamento

Encapsulamento esconde um detalhe interno e expõe só o que o resto do programa deve usar. O saldo muda por `depositar` e `sacar`, não por uma atribuição solta que poderia deixar o valor negativo sem passar pela regra.

Python não impede o acesso de verdade. A convenção é:

- `atributo` — uso livre
- `_atributo` — detalhe interno; quem está de fora evita usar
- `__atributo` — o nome é reescrito pela linguagem (`name mangling`), para não bater com o mesmo nome numa classe filha

```python
class ContaBancaria:
    def __init__(self, titular, saldo):
        self.titular = titular
        self.__saldo = saldo

    def depositar(self, valor):
        self.__saldo += valor

    def sacar(self, valor):
        if valor <= self.__saldo:
            self.__saldo -= valor
        else:
            print("Saldo insuficiente.")

    def mostrar_saldo(self):
        print(f"Saldo de {self.titular}: R$ {self.__saldo}")

banco = ContaBancaria("Ana", 2000)
banco.depositar(200)
banco.sacar(50)
banco.mostrar_saldo()
```

### Herança

Herança cria uma classe a partir de outra. A filha recebe o que a pai já tem e substitui o que for específico. `class Cachorro(Animal)` diz essa relação. Serve para não copiar `nome` e o restante que todos os animais compartilham. `__init__` da filha, se existir, precisa chamar `super().__init__(...)` para o inicializador da classe pai também rodar. Neste exemplo a filha não define `__init__`, então usa o da classe pai.

```python
class Animal:
    def __init__(self, nome):
        self.nome = nome

    def falar(self):
        print("O animal faz um som.")

class Cachorro(Animal):
    def falar(self):
        print(f"{self.nome} diz: au au!")

class Gato(Animal):
    def falar(self):
        print(f"{self.nome} diz: miau!")

dog = Cachorro("Rex")
cat = Gato("Kat")
dog.falar()
cat.falar()
```

### Polimorfismo

Polimorfismo é o mesmo método com efeitos diferentes conforme a classe do objeto. `falar` existe em `Animal`, `Cachorro` e `Gato`. Quem chama não precisa saber qual dos três recebeu: chama `falar` e o objeto responde com a própria versão. A função abaixo aceita qualquer um deles.

```python
def apresentar(animal):
    animal.falar()

apresentar(dog)
apresentar(cat)
```

### Abstração

Uma classe abstrata define o que as filhas precisam saber fazer, sem implementar ela mesma. Serve de contrato: toda forma tem `area`, mas retângulo e círculo calculam de jeitos diferentes. O módulo `abc` faz isso. Classe com método abstrato não pode ser instanciada. A filha só vira objeto concreto quando implementa esse método.

```python
from abc import ABC, abstractmethod

class Forma(ABC):
    @abstractmethod
    def area(self):
        pass

class Retangulo(Forma):
    def __init__(self, largura, altura):
        self.largura = largura
        self.altura = altura

    def area(self):
        return self.largura * self.altura

ret = Retangulo(10, 5)
print(ret.area())
```

## Módulo 11: Funções prontas da linguagem

### math

O módulo `math` reúne contas que não cabem num operador: raiz, seno, arredondamento. `import math` traz o módulo. `math.sqrt` devolve a raiz quadrada. Use-o para não reescrever fórmula que a linguagem já entrega.

```python
import math

resultado = math.sqrt(16)
print("Raiz quadrada de 16 é:", resultado)
```

### sorted

`sorted` devolve uma lista nova em ordem, sem alterar a original. Serve para ranking ou para percorrer valores em ordem e manter a lista como entrou. `lista.sort()` ordena a própria lista, no lugar.

```python
numeros = [5, 3, 1, 4, 2]
ordenados = sorted(numeros)

for numero in ordenados:
    print(numero)
```
