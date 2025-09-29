# Programação Orientado Objeto

# A primeira anotaçao é sobre Classes
# Classes sao forma de criar "Modelo" de coisa do mundo real (ou abstrata), com atributos (caracteristicas) e métodos (ações)

# Estrutura Basica de uma classe
class ClasseDeTeste:
    def __init__(self, parametro1, parametro2):
        # O metodo __init__ é contrutor
        # Ele roda automaticamente quando crianmos o objeto
        self.parametro1 = parametro1
        self.parametro2 = parametro2

    def mostrar_info(self):
        # Métodos sempre recenbem "self" como 1º parametros
        print(f"Imprimindo os parametros da classe: {self.parametro1}, param2: {self.parametro2}")

# Criando objetos (instancias)
# Criar um objeto e nada mais que instaciar puxando tosos as informações e métodos dela deixando pronta pra usar.

objeto = ClasseDeTeste("Teste de paramentro 01", "Teste de paramentro 02")

# Quando vc usa uma variavel para instaciar uma classe, usando ponto, você pode chamar os metodos da classe.

objeto.mostrar_info()

print(" ")
print(" ")

# Um modelo de classe pra ser usado ##############################################################################
print("###################################################################################")

class Carro:
    def __init__(self, marca, modelo, ano):
        self.marca = marca
        self.modelo = modelo
        self.ano = ano
        self.ligado = False

    def ligar(self):
        self.ligado = True
        print(f"{self.modelo} esta ligado.")

    def desligar(self):
        self.ligado = False
        print(f"{self.modelo} esta desligado")
    
    def info(self):
        print(f"{self.ano} {self.marca} {self.modelo} - Ligado: {self.ligado}")

meu_carro = Carro("Toyota", "Corola", 2020)

meu_carro.info()
meu_carro.ligar()
meu_carro.info()
meu_carro.desligar()




print(" ")
print(" ")


# ####################################################################################################
print("###################################################################################")

'''
    PROGRAMAÇÃO ORIENTADA A OBJETOS
    POO é um paradigma que organiza o codigo em torno de objetos.
    Um objeto é como uma entidade que combina dados (atributos) e ações (métodos).

    4 PILARES DO POO

    - Encapsulamento
    - Herança
    - Polimorfismo
    - Abstração
'''

# Encapsulamento

'''
    O encapsulamento permite esconder detalhes internos de uma classe e expor apenas o nescessário.

    Em Python, nao existe "privado" de verdade, mas por convenção:
        - atributos >> público.
        - _atributo >> protegido (uso interno)
        - __atributo >> privado (name mangling)

'''

class contaBancaria:
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

banco = contaBancaria("Eu", 2000)
banco.depositar(200)
banco.sacar(50)
banco.mostrar_saldo()



# Herança

'''
- Permite criar classes filhas que herdam atributos e metodos de uma classe pai.
'''

class Animal:
    def __init__(self, nome):
        self.nome = nome

    def falar(self):
        print("O animal faz som.")

class Cachorro(Animal):
    def falar(self):
        print(f"{self.nome} diz: au au!")

class Gato(Animal):
    def falar(self):
        print(f"{self.nome} diz: Miau!")

dog = Cachorro("Rex")
cat = Gato("kat")

dog.falar()
cat.falar()


# Polimorfismo
'''
- Permite que metodo com o mesmo nome se comportem de forma diferente dependendo da classe.
- No exemplo acima, falar() é Polimorfico (funciona diferente e cachorro e gato)
'''



# Abstração
'''
- Cria classes abstrata que definem o que devem ser feitos, mas nao como.
- Em Python usamos o modulo abc para isso.
'''

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