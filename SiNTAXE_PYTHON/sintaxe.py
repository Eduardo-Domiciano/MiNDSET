# Anotações sobre a linguagem Python

# Calculos matemáticos

print("Calculo matemáticos com Python ######################")

print("Soma: 2 + 3 = ", 2 + 3)

print("Subtração: 10 - 4 = ", 10 - 4)

print("Multiplicação: 7 * 5 = ", 7 * 5)

print("Divisão: 8 / 2 = ", 8 / 2)

print("Divisão inteira: 9 // 2 = ", 9 // 2)

print("Resto da divisão - Modulo: 9 % 2 = ", 9 % 2)

print("Potencia: 2 ** 3 = ", 2 ** 3)

print("")
print("")

# Strings
print("Strings ##########################################")

nomeMaria = "Maria"
sobrenomeSilva = "Silva"

print("Concatenar (Juntar textos)")
print(nomeMaria + " " + sobrenomeSilva)

print("Repetir String")
print("Olá " * 3)

print("F-Strings (Interpolação de variaveis)")
idade = 35
print(f"{nomeMaria} tem {idade} anos.")

print("")
print("")

# Variaveis e Tipos
print("Variaveis e tipos #############################")

# O python é capaz de perceber o tipo de variavel
x = 10          # inteiro (int)
y = 3,14        # decimal (Float)
nomeAna = "Ana"    # texto (String)
vivo = "True"   # Boleano (True ou False)

print(f" Tipo de x: {type(x)}, Tipo de y: {type(y)}, Tipo de nomeAna: {type(nomeAna)}, Tipo de vivo: {type(vivo)}")

print("")
print("")

# Lista (Coleções)
print("Lista (Coleções) ###############################")

numeros = [1, 2, 3, 4]
print("numeros da lista = ", numeros)
print(numeros[0])
print(numeros[2])
numeros.append(5)
print("numero adicionado", numeros[-1])

print(f"quantidade de numeros da lista", len(numeros))

print("")
print("")

# Estruturas de repetição
print("Estruturas de repetição ##########################")

for numero in numeros:
    print(f"Enumerando uma lista com for: ", numero)

contador = 0
while contador < 3:
    print("Oi")
    contador += 1

print("")
print("")

# Condições If e Else

print("Condições (if/else) #################################")

idade = 19

if idade >= 18:
    print("Maior de idade")
else:
    print("Menor de idade")

# Funções

def soma(a, b):
    return a + b

resultado = soma(10, 5)
print(resultado)

print("")
print("")

