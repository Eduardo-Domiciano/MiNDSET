# HTTP, HTTPS, SSL e TLS

HTTP é o protocolo com que o navegador pede uma página e o servidor responde. HTTPS é esse mesmo protocolo dentro de um túnel cifrado. O túnel se chama TLS. SSL é o antecessor do TLS: a sigla ainda aparece em “certificado SSL”, mas o protocolo SSL não deve mais ser usado. TSL não é um protocolo; é a sigla TLS escrita fora de ordem.

## HTTP

**HTTP** (*Hypertext Transfer Protocol*) é o protocolo de aplicação que leva o pedido do cliente até o servidor e traz a resposta de volta. Ele não é a página, nem o HTML, nem o DNS. Ele é o formato da conversa: método, caminho, cabeçalhos e corpo.

A conversa é **pedido e resposta**. O cliente abre a conexão (na Web clássica, TCP na porta **80**) e envia uma mensagem. O servidor devolve outra mensagem e, no HTTP/1.0, a conexão podia acabar ali. No HTTP/1.1 a conexão costuma ser reaproveitada. HTTP/2 e HTTP/3 mudam o transporte e o empacotamento; o modelo pedido/resposta continua.

O HTTP é **sem estado**. Cada pedido se explica sozinho. O servidor não guarda, pelo protocolo, que o pedido anterior foi da mesma pessoa. Sessão, login e carrinho entram por cima, em cookie, token ou outro mecanismo da aplicação.

```text
 Cliente                         Servidor
    |                                |
    |  GET /index.html HTTP/1.1      |
    |  Host: www.exemplo.com         |
    |------------------------------->|
    |                                |
    |  HTTP/1.1 200 OK               |
    |  Content-Type: text/html       |
    |                                |
    |  <html>...</html>              |
    |<-------------------------------|
```

Um pedido tem três partes:

1. **Linha inicial:** método, caminho e versão. Exemplo: `GET /index.html HTTP/1.1`.
2. **Cabeçalhos:** metadados, um por linha. `Host` diz qual site, no mesmo IP, está sendo pedido. `User-Agent`, `Accept` e `Cookie` também vão aqui.
3. **Corpo:** opcional. Um `GET` em geral não tem corpo. Um `POST` leva o formulário ou o JSON.

A resposta repete a ideia: linha de status (`HTTP/1.1 200 OK`), cabeçalhos e corpo (HTML, JSON, imagem, arquivo).

Métodos mais usados:

| Método | O que pede |
|--------|------------|
| `GET` | Ler um recurso. Não deve alterar o servidor. |
| `HEAD` | O mesmo que `GET`, sem o corpo. Serve para ver cabeçalhos. |
| `POST` | Enviar dados para processamento (formulário, criação). |
| `PUT` | Guardar ou substituir o recurso naquele caminho. |
| `PATCH` | Alterar parte do recurso. |
| `DELETE` | Remover o recurso. |
| `OPTIONS` | Perguntar quais métodos aquele caminho aceita. |

O status da resposta se lê pelo primeiro dígito:

| Faixa | Sentido |
|-------|---------|
| `1xx` | Informação provisória |
| `2xx` | Sucesso (`200 OK`, `201 Created`) |
| `3xx` | Redirecionamento (`301`, `302`, `304`) |
| `4xx` | Erro do cliente (`400`, `401`, `403`, `404`) |
| `5xx` | Erro do servidor (`500`, `502`, `503`) |

Pelo HTTP puro, quem estiver no caminho lê o pedido e a resposta. Senha, cookie e o HTML viajam em texto claro. É por isso que site público na internet usa HTTPS.

## HTTPS

**HTTPS** é HTTP sobre TLS. O nome expande para *Hypertext Transfer Protocol Secure*. A porta padrão é **443**.

A ordem importa. Primeiro o cliente e o servidor concluem o TLS. Só depois o HTTP começa, já cifrado. Quem observa a rede vê o IP, a porta e o tamanho aproximado dos pacotes. Não vê a URL completa, os cabeçalhos nem o corpo.

```text
 Cliente                                      Servidor
    |                                             |
    |  1. Handshake TLS (porta 443)               |
    |     certificado, chaves, cifra              |
    |<------------------------------------------->|
    |                                             |
    |  2. HTTP dentro do túnel                    |
    |     GET /conta HTTP/1.1                     |
    |     Cookie: sessao=...                      |
    |============================================>|
    |     HTTP/1.1 200 OK                         |
    |     (cifrado)                               |
    |<============================================|
```

O HTTPS entrega três propriedades, vindas do TLS:

- **Confidencialidade.** O conteúdo não é legível no meio do caminho.
- **Integridade.** Alterar um byte no caminho invalida a mensagem.
- **Autenticação do servidor.** O certificado diz que aquele servidor é o dono do nome pedido, se uma autoridade confiável assinou o certificado e se o nome confere.

O cadeado do navegador significa que o TLS fechou com um certificado aceito para aquele nome. Não significa que o site seja honesto, nem que o conteúdo seja verdadeiro.

## SSL e TLS

**SSL** (*Secure Sockets Layer*) é o protocolo antigo de túnel cifrado, criado pela Netscape nos anos 1990. Houve SSL 2.0 e SSL 3.0. Os dois estão aposentados: têm falhas conhecidas e os clientes atuais recusam negociá-los.

**TLS** (*Transport Layer Security*) é o sucessor. O TLS 1.0 saiu em 1999 a partir do SSL 3.0, com outro nome para não ficar preso à Netscape. TLS 1.0 e 1.1 também estão obsoletos. O que se usa hoje é **TLS 1.2** e **TLS 1.3**.

```text
  SSL 2.0  →  SSL 3.0  →  TLS 1.0  →  TLS 1.1  →  TLS 1.2  →  TLS 1.3
  aposentado   aposentado   obsoleto    obsoleto    em uso      em uso
```

Na prática, “certificado SSL” e “certificado TLS” são o mesmo objeto: um certificado **X.509**, com a chave pública do servidor e a assinatura de uma autoridade certificadora (CA). O certificado não escolhe SSL ou TLS. Quem escolhe a versão é a negociação entre cliente e servidor. Um certificado novo, num servidor atual, fala TLS.

O aperto de mão do TLS, em linhas gerais:

1. O cliente diz quais versões e cifras aceita.
2. O servidor escolhe uma combinação e envia o certificado.
3. O cliente confere a cadeia até uma CA em que confia, o prazo e se o nome do certificado é o nome do site.
4. Os dois combinam a chave da sessão. A chave privada do servidor não viaja na rede.
5. A partir daí, o HTTP (ou outro protocolo) segue cifrado com essa chave de sessão.

TLS protege o transporte. Ele não substitui login, autorização nem cuidado com o que a aplicação faz depois de decifrar o pedido.

## Esquema de uma URL

**URL** (*Uniform Resource Locator*) é o endereço de um recurso e a indicação de **como** buscá-lo. A forma geral:

```text
esquema://usuario:senha@host:porta/caminho?consulta#fragmento
```

Exemplo completo, com todas as peças:

```text
https://ana:segredo@www.exemplo.com:443/conta/pedidos?status=aberto#resumo
|___|   |__________| |______________| |_||______________||____________| |____|
  |          |              |           |        |              |          |
esquema   usuário        host        porta    caminho       consulta   fragmento
```

| Peça | No exemplo | Função |
|------|------------|--------|
| Esquema | `https` | Protocolo. Decide o modo de conexão e a porta padrão. |
| Usuário e senha | `ana:segredo` | Credencial embutida na autoridade. Evite: fica em histórico, log e referenciador. |
| Host | `www.exemplo.com` | Nome ou IP do servidor. O DNS transforma o nome em IP. |
| Porta | `443` | Porta TCP (ou UDP, no HTTP/3). Omitida, vale a padrão do esquema. |
| Caminho | `/conta/pedidos` | Recurso dentro daquele host. |
| Consulta | `status=aberto` | Parâmetros para o servidor. Começa em `?`. Vários pares se separam com `&`. |
| Fragmento | `resumo` | Ponto dentro da página. Começa em `#`. O navegador usa; **não** envia ao servidor. |

O **esquema** é o trecho anterior a `://`. Ele não é decoração: o cliente escolhe o programa de acesso por causa dele.

| Esquema | O que o cliente faz | Porta padrão |
|---------|---------------------|--------------|
| `http` | Abre TCP e fala HTTP em claro | 80 |
| `https` | Abre TCP, conclui TLS e só então fala HTTP | 443 |
| `ftp` | Usa o protocolo de transferência de arquivos | 21 |

`http://www.exemplo.com/conta` e `https://www.exemplo.com/conta` apontam para o mesmo caminho no mesmo host e são recursos diferentes para o cliente: um vai à porta 80 sem cifra, o outro à porta 443 com TLS. Se a porta padrão vale, ela pode sumir da barra de endereço. `https://www.exemplo.com/conta` é o mesmo que `https://www.exemplo.com:443/conta`.

Ordem em que o navegador usa essas peças num `https`:

```text
 URL
  |
  |  1. Lê o esquema → https
  |  2. DNS do host → endereço IP
  |  3. TCP no IP, porta 443
  |  4. TLS: certificado precisa cobrir o host
  |  5. HTTP: método + caminho + ?consulta
  |     Host: www.exemplo.com
  |  6. #fragmento fica no navegador
  v
 Página
```

Dois detalhes que mudam o diagnóstico:

- O caminho e a consulta vão no pedido HTTP, depois do TLS. O esquema e a porta não se repetem nessa linha inicial; o `Host` leva o nome.
- Um certificado emitido para `exemplo.com` não cobre, sozinho, `outro.com`. O nome que o TLS valida é o host da URL, não o caminho.
