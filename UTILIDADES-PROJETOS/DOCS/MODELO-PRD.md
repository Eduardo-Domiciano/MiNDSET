# PRD — Documento de Requisitos de Projeto

Modelo para copiar no início de um projeto. Troque os textos entre colchetes. Apague a seção que não se aplicar. O PRD diz **o que** o projeto precisa entregar e **como saber** que entregou. Detalhe de implementação fica fora daqui.

| Campo | Valor |
| --- | --- |
| Projeto | [nome] |
| Versão | [0.1] |
| Status | [rascunho / em revisão / aprovado] |
| Autor | [nome] |
| Data | [AAAA-MM-DD] |
| Responsável pela decisão | [quem aprova o escopo] |

## 1. Resumo

[Em um parágrafo: o que será feito, para quem e por que agora.]

## 2. Problema

[Qual situação existe hoje. Quem sente o problema. O que acontece se nada mudar.]

## 3. Objetivo

[O resultado que este projeto precisa produzir. Uma ou duas frases, no infinitivo ou no presente: "o usuário consegue…".]

### Como o sucesso será medido

| Métrica | Situação atual | Meta | Como medir |
| --- | --- | --- | --- |
| [ex.: tempo para concluir o cadastro] | [ex.: não medido] | [ex.: menos de 2 minutos] | [ex.: log do formulário] |

## 4. Quem usa

| Pessoa | O que precisa fazer | O que já sabe |
| --- | --- | --- |
| [ex.: operador do caixa] | [ex.: registrar uma venda sem sair da tela] | [ex.: usa o sistema atual todo dia] |

## 5. Escopo

**Entra nesta entrega**

- [capacidade 1]
- [capacidade 2]

**Não entra nesta entrega**

- [o que fica para depois, ou o que outro sistema continua fazendo]

## 6. Requisitos funcionais

Cada requisito é uma capacidade observável. O identificador não muda: se o requisito cair, o código fica vago no histórico, não é reaproveitado.

| ID | Requisito | Prioridade |
| --- | --- | --- |
| RF-01 | [O sistema deve…] | [alta / média / baixa] |
| RF-02 | [O usuário deve conseguir…] | [alta / média / baixa] |

Prioridade alta entra nesta entrega. Média entra se couber sem atrasar as altas. Baixa fica registrada e só entra com decisão explícita.

## 7. Requisitos não funcionais

Limites de qualidade: desempenho, segurança, disponibilidade, privacidade, acessibilidade, idioma, volume de dados.

| ID | Requisito | Prioridade |
| --- | --- | --- |
| RNF-01 | [ex.: a tela principal abre em até 2 segundos na rede interna] | [alta] |
| RNF-02 | [ex.: dados pessoais seguem a LGPD; acesso só com login] | [alta] |

## 8. Fluxo principal

Passos do caminho feliz, na ordem em que a pessoa age.

1. [A pessoa abre…]
2. [Informa…]
3. [O sistema confirma…]

### Outros caminhos

- [ex.: dado inválido — o sistema aponta o campo e não grava]
- [ex.: sessão expirada — volta ao login e não perde o que ainda não foi enviado, se isso estiver no escopo]

## 9. Regras

Condições que o sistema precisa obedecer e que não cabem numa frase de requisito.

- [ex.: um pedido só pode ser cancelado enquanto o status for "aberto"]
- [ex.: o mesmo e-mail não pode cadastrar duas contas]

## 10. Critérios de aceite

Lista verificável. Cada item começa de um requisito e diz o que precisa ser verdade para considerá-lo pronto.

- [ ] RF-01: [dado de entrada] produz [resultado observável]
- [ ] RF-02: [condição de erro] produz [mensagem ou estado]
- [ ] RNF-01: [medição] fica dentro de [limite]

## 11. Premissas, restrições e dependências

**Premissas** — o que se assume verdadeiro e, se falhar, muda o plano.

- [ex.: o cadastro de clientes já existe e expõe consulta por documento]

**Restrições** — limites que não estão em negociação.

- [ex.: prazo, orçamento, stack obrigatória, ambiente sem internet]

**Dependências** — o que este projeto precisa receber de fora.

| Dependência | De quem | Para qual requisito |
| --- | --- | --- |
| [ex.: API de pagamento] | [equipe ou fornecedor] | [RF-0X] |

## 12. Riscos

| Risco | Efeito se ocorrer | O que reduz o efeito |
| --- | --- | --- |
| [ex.: a API externa muda o contrato] | [ex.: o pagamento não conclui] | [ex.: contrato versionado e teste de contrato] |

## 13. Perguntas abertas

| Pergunta | Quem responde | Até quando |
| --- | --- | --- |
| [o que ainda impede fechar um requisito] | [nome] | [data] |

## 14. Glossário

| Termo | Significado neste projeto |
| --- | --- |
| [termo] | [definição única, para o time não usar a palavra em dois sentidos] |

## Histórico

| Versão | Data | O que mudou |
| --- | --- | --- |
| 0.1 | [AAAA-MM-DD] | Versão inicial |
