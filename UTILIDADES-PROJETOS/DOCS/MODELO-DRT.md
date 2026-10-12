# DRT — Documento de Requisitos Técnicos

Modelo para copiar junto com o PRD. Troque os textos entre colchetes. Apague a seção que não se aplicar. O PRD diz **o que** entregar. O DRT diz **como** o sistema precisa ser construído para cumprir esses requisitos: arquitetura, interfaces, dados, segurança e limites técnicos.

| Campo | Valor |
| --- | --- |
| Projeto | [nome] |
| Versão | [0.1] |
| Status | [rascunho / em revisão / aprovado] |
| Autor | [nome] |
| Data | [AAAA-MM-DD] |
| PRD de origem | [caminho ou versão do PRD] |
| Responsável técnico | [quem aprova as decisões daqui] |

## 1. Resumo técnico

[Em um parágrafo: que sistema é este, quais partes ele tem e com o que ele se integra.]

## 2. Contexto atual

[O que já existe: sistemas, bases, serviços e restrições herdadas. O que este projeto altera e o que permanece.]

## 3. Arquitetura

[Desenho das partes e da responsabilidade de cada uma. Uma parte faz um trabalho. Se duas partes fazem o mesmo, o desenho ainda não fechou.]

| Parte | Responsabilidade | Depende de |
| --- | --- | --- |
| [ex.: API de pedidos] | [ex.: gravar e consultar pedidos] | [ex.: banco de pedidos, fila de pagamento] |
| [ex.: interface web] | [ex.: fluxo descrito no PRD] | [ex.: API de pedidos] |

```text
[pessoa] → [interface] → [serviço] → [banco ou sistema externo]
```

## 4. Stack

Versões entram aqui para o time não misturar gerações no mesmo projeto.

| Camada | Escolha | Versão |
| --- | --- | --- |
| Linguagem | [ex.: TypeScript] | [ex.: 5.x] |
| Interface | [ex.: navegador moderno] | [ex.: últimas duas versões estáveis] |
| Servidor | [ex.: Node] | [ex.: 22 LTS] |
| Dados | [ex.: PostgreSQL] | [ex.: 16] |
| Fila / cache | [ex.: nenhum / Redis] | [versão] |

## 5. Interfaces

Cada contrato que cruza uma fronteira: API, evento, arquivo ou chamada a sistema externo.

| ID | Interface | Direção | Contrato |
| --- | --- | --- | --- |
| IF-01 | [ex.: criar pedido] | [esta parte chama / é chamada] | [método, caminho, payload mínimo e resposta] |
| IF-02 | [ex.: aviso de pagamento aprovado] | [recebe evento] | [nome do evento e campos obrigatórios] |

Erro de contrato também é requisito: o que a parte devolve quando a entrada é inválida, quando o sistema externo falha e quando a operação se repete.

| Situação | Comportamento |
| --- | --- |
| Entrada inválida | [ex.: recusa sem gravar e devolve o campo em falta] |
| Sistema externo indisponível | [ex.: não confirma o pedido; a pessoa pode tentar de novo] |
| Mesma operação enviada duas vezes | [ex.: a segunda chamada devolve o resultado da primeira, sem duplicar] |

## 6. Dados

| Dado | Onde vive | Quem grava | Quem lê | Por quanto tempo |
| --- | --- | --- | --- | --- |
| [ex.: pedido] | [ex.: tabela pedidos] | [serviço] | [serviço, relatório] | [ex.: 5 anos] |

- Identificador estável: [o que não muda depois de criado].
- O que não pode ser duplicado: [ex.: um pagamento externo gera um único pedido].
- Migração, se houver dado antigo: [origem, regra de transformação e como conferir que nada se perdeu].

## 7. Segurança e privacidade

| ID | Requisito técnico | Atende no PRD |
| --- | --- | --- |
| RS-01 | [ex.: toda chamada da API exige token válido] | [RNF-0X] |
| RS-02 | [ex.: senha não é gravada; guarda-se só o hash] | [RNF-0X] |
| RS-03 | [ex.: dado pessoal em trânsito só por canal cifrado] | [RNF-0X] |

- Quem autentica: [serviço próprio / provedor externo].
- Quem autoriza cada ação: [papel e o que esse papel pode fazer].
- Segredo (chave, senha de banco, token): [onde fica; não entra no repositório].

## 8. Ambientes

| Ambiente | Para que serve | O que aponta |
| --- | --- | --- |
| Local | [desenvolvimento na máquina] | [banco e serviços locais ou de teste] |
| Homologação | [ensaio com dado fictício] | [integrações de sandbox] |
| Produção | [uso real] | [integrações reais] |

Configuração que muda por ambiente fica fora do código: endereço, credencial e flag. O que é igual em todos os ambientes fica no repositório.

## 9. Operação

| Sinal | Onde olhar | O que indica problema |
| --- | --- | --- |
| [ex.: erro ao criar pedido] | [ex.: log do serviço, com id do pedido] | [ex.: taxa acima de X em 5 minutos] |
| [ex.: tempo da API] | [ex.: métrica da rota] | [ex.: acima do limite do RNF] |

- Como publicar uma versão: [comando ou pipeline, e se a versão anterior continua no ar durante a troca].
- Como voltar atrás: [o que reverte código e o que reverte banco].
- Cópia de segurança: [o que é copiado, com que frequência e como se testa a restauração].

## 10. Requisitos técnicos

Tradução dos requisitos do PRD para uma condição que dá para construir e verificar. O identificador não se reaproveita se o item for retirado.

| ID | Requisito técnico | Origem no PRD | Prioridade |
| --- | --- | --- | --- |
| RT-01 | [ex.: a criação do pedido responde em até 500 ms no percentil 95, sem contar o provedor de pagamento] | [RNF-01] | [alta] |
| RT-02 | [ex.: a operação de criar pedido aceita repetição sem gerar dois pedidos] | [RF-0X] | [alta] |

## 11. Decisões

Escolha já fechada, com o motivo. Decisão nova entra como linha nova; a antiga permanece, marcada como substituída.

| ID | Decisão | Motivo | Status |
| --- | --- | --- | --- |
| DT-01 | [ex.: PostgreSQL para os pedidos] | [ex.: o time precisa de transação e de consulta relacional] | [vigente] |

## 12. Como verificar

- [ ] RT-01: [teste, medição ou revisão que prova o requisito]
- [ ] RT-02: [repetir a mesma chamada e conferir que existe um único registro]
- [ ] RS-01: [chamada sem token é recusada]

## 13. Riscos técnicos

| Risco | Efeito | O que reduz o efeito |
| --- | --- | --- |
| [ex.: o sandbox do pagamento não reproduz o erro real] | [ex.: a falha só aparece em produção] | [ex.: teste de contrato e ensaio com resposta simulada] |

## 14. Perguntas abertas

| Pergunta | Quem responde | Até quando |
| --- | --- | --- |
| [o que ainda impede fechar uma decisão técnica] | [nome] | [data] |

## 15. Glossário

| Termo | Significado neste projeto |
| --- | --- |
| [termo] | [definição única] |

## Histórico

| Versão | Data | O que mudou |
| --- | --- | --- |
| 0.1 | [AAAA-MM-DD] | Versão inicial |
