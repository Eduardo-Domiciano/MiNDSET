# Norma ISO/IEC 27001

A ISO/IEC 27001 é uma norma de segurança da informação reconhecida internacionalmente, desenvolvida pelo orgão de certificação [International Organization for Standardization](https://www.iso.org/home.html) (ISO) e a [International Eletrotechnical Commission](https://www.iec.ch/homepage) (IEC). A norma ISO/IEC 27001 foi publicada pela primeira vez em 2005, sendo o resultado da evolução de uma norma britânica anterior, a BS 7799-2, publicada originalmente em 1999. A ISO juntamente com a IEC trabalharam juntas para desenvolver a ISO/IEC 27001 como um padrão internacional para sistemas de gestão de segurança da informação (SGSI).

## O que é a ISO/IEC 27001?

A norma internacional ISO/IEC 27001 estabelece os requisitos para criação, implementação, manutenção e melhorias continua de um **Sistema de Gestão de Segurança da Informação (SGSI)**, em ingles **Information Security Management System (ISMS)**. Ela é como um manual de melhores práticas que orienta uma organização a proteger suas informações de forma sistemática e estruturada. Ela não especifica quais tipos de ferramentas devem ser usadas, mas sim, como uma empresa deve gerenciar a segurança de forma completa.

![3 pilares](./img/ISO-IEC-27001-3-pilares.png)

O principal objetivo da norma é proteger os 3 pilares essenciais da informação:

- 1. **Confidencialidade**: Garantir que a informação seja acesivel apenas por pessoas autorizadas.
- 2. **Integridade**: Assegurar que as informações e seus metodos de processamento sejam precisos e completos, protegendo contra alterações não autorizadas.
- 3. **Disponibilidade**: Garantir que os usuarios autorizados tenham acesso a informação e aos ativos relacionados sempre que nescessário.

## Como funciona a ISO/IEC 27001?

![PDCA image](./img/ISO-IEC-27001-PDCA.png)

A implementação da norma 27001 não é um projeto com inicio, meio e fim, mas sim um ciclo continuo de gestão. Ela funciona com base no modelo **PDCA (Plan-Do-Check-Act)**, um ciclo de melhoria continua:

- 1. **Plan - Planejamento**: Essa é a fase em que é definido o escopo do SGSI, onde se estabelece a pilitica de segurança da informação, define a metodologia de avaliação de riscos e, o mais importante, identifica e avalia os riscos de segurança. Com base nessa avaliação, a empresa define os controles (medidas de segurança) nescessários para mitigar esses riscos. A norma possui uma lista de controle de referencia em seu Anexo A, que abordam áreas como controle de acesso, criptografia, segurança fisica, etc.

![Anexo A](./img/ISO-IEC-27001-ANEXO-A.png)
Creditos: https://www.27001.pt/

- 2. **Do - Fazer**: Essa é a fase onde se implementa o que foi planejado:
    - Implementação de controles de segurança definidos.
    - Realiza treinamentos de concientização para os funcionários.
    - Gerencia a operação diária de segurança da informação.
    - Cria Cria e mantem a documentação nescessária (politicas, procedimentos, registros).

- 3. **Check - Checar**: Nesse ponto, a organização monitora e revisa a eficácia do SGSI para garantir que ele está funcionando como esperado. Isso inclui:
    - Auditorias Internas: Verificações periódicas para garantir que os processos estão em conformidade com a norma.
    - Analise Critica pela Direção: A gestão da empresa revisa o desempenho do SGSI, analisando resultados das auditorias, incidentes ocorridos e decidir sobre as proximas ações.
    - Monitoramento de métrica: Acompanhar indicadores de desempenho para medir a eficácia dos controles.

- 4. **Act - Agir**: Com base nos resultados da fase de verificação, a organização toma ações corretivas e preventivaspara resolver problemas e melhorar o SGSI. Se a auditoria encpontrou uma falha, ela é corrigida nessa fase, ou se um risco surgiu, ele é tratado. Este passo garante que o sistema de gestao nao fique estagnado e evolua constantemente para lidar com novas ameaças.

![Anexo A](./img/ISO-IEC-27001-ANEXO-A-2.png)

Após passar por este ciclo e amadurecer seus processos, a empresa pode contratar um organismo certificador independente e credenciado para realizar uma auditoria externa. Se a empresa demonstrar que seu SGSI está em conformidade com todos os requisitos da norma, ela recebe a certificação ISO/IEC 27001, que geralmente é validada por três anos, mantendo auditorias e manutenções anuais.

## Escopo

A ISO/IEC 27001 especifica requisitos pra estabelecer, implementar, manter e melhorar continuamente o sistema de gestão da segurança da informação dentro do contexto da organização, tratando também da avaliação e tratamento de riscos da segurança da informação.

## Contexto da organização

A organização deve determinar as questões externas e internas que são relevantes ao propositos da organização e que afetam sua capacidade de alcançar os resultados definidos com a SGSI.

### Nessecidades e expectativas das partes interessadas

A organização deve determinar as partes interessadas que são relevantes para o sistema SGSI, bem como os requisitos relevantes dessas partes.

### Escopo SGSI

A organização deve definir limites e aplicabilidade da SGSI a fim de estabeler seu escopo. Considerando interfaces de comunicação e dependencias entre as atividades da organização, bem como as organizações de terceiros.

### Objetivo

A organização deve estabelecer, implementar, manter e melhorar continuamente  um sistema de gestão da segurança da informação, incluindo os processos necessários e suas interações, de acordo com os requisitos da norma.

## Liderança

A liderança deve se comprometer em relação a SGSI pelo seguintes meios:


- 1. Assegurando que a política de segurança da informação e os objetivos de segurança da informação 
estejam estabelecidos e sejam compatíveis com a direção estratégica da organização;
- 2. Assegurando a integração dos requisitos do sistema de gestão da segurança da informação nos 
processos da organização;
- 3. Assegurando que os recursos necessários para o sistema de gestão da segurança da informação 
estejam disponíveis;
- 4. Comunicando a importância de uma gestão eficaz da segurança da informação e da conformidade 
com os requisitos do sistema de gestão da segurança da informação;
- 5. assegurando que o sistema de gestão da segurança da informação alcance seus resultados 
pretendidos;
- 6. orientando e apoiando pessoas a contribuir para a eficácia do sistema de gestão da segurança 
da informação;
- 7. promovendo a melhoria contínua; e
- 8. apoiando outros papéis relevantes da gestão para demonstrar como sua liderança se aplica  
às áreas sob sua responsabilidade;

### Politica

A Organização da SGSI deve estabelecer politicas de segurança, fazendo com que sejam apropriadas ao proposito da organização, inclua os objetivos e fornecendo estrutura estabelece-los, que estajam comprometidos a satisfazer os requisitos aplicaveis, comprometida com as melhorias continua do sistema, ter o processo disponivel e documentado, ser acessivel e comunicada dentro da organização e estar disponivel para as partes conforme nescessário.

