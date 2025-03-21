// Importa o módulo readline para entrada de dados no terminal
const readline = require('readline');

// Configura a interface de leitura
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Função para calcular a média de um array de números
function calcularMedia(valores) {
    if (valores.length === 0) {
        return 0; // Retorna 0 se não houver valores
    }
    const soma = valores.reduce((acumulador, valor) => acumulador + valor, 0);
    return soma / valores.length;
}

// Função para coletar valores do usuário
function coletarValores(callback) {
    let valores = [];

    function perguntar() {
        rl.question("Digite um número real (ex.: 10.5) ou 'sair' para finalizar: ", (entrada) => {
            if (entrada.toLowerCase() === 'sair') {
                rl.close(); // Fecha a interface de leitura
                callback(valores); // Chama o callback com os valores coletados
            } else {
                // Converte a entrada para número real
                let numero = parseFloat(entrada);

                // Verifica se é um número válido (inclui reais)
                if (!isNaN(numero)) {
                    valores.push(numero);
                    console.log(`Valor ${numero} adicionado.`);
                } else {
                    console.log("Entrada inválida! Por favor, digite um número real (ex.: 3.14).");
                }
                perguntar(); // Continua pedindo mais valores
            }
        });
    }

    perguntar(); // Inicia o processo de coleta
}

// Função principal
function main() {
    console.log("Digite números reais para calcular a média.");
    coletarValores((valores) => {
        if (valores.length === 0) {
            console.log("Nenhum valor foi inserido para calcular a média.");
        } else {
            const media = calcularMedia(valores);
            console.log(`Valores inseridos: ${valores}`);
            console.log(`Média: ${media.toFixed(2)}`); // Formata com 2 casas decimais
        }
    });
}

// Executa o programa
main();