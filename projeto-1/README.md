# TCP Connection Test

Teste Echo de Conexão - quando cliente é conectado ao servidor qualquer
mensagem enviado pelo cliente é lida e repetida pelo servidor.

Os arquivos "client.c", "server.c" e "conc_server.c" fazem parte do processo. Apenas compile
com gcc e ao executr o cliente o faca com o parametro do localhost:

    "./client 127.0.0.1"

O server.c é um servidor iterativo, apenas aceita um cliente por vez. Caso haja dois clientes, ele esperará o primeiro terminar a conexão para receber as informações do segundo cliente.

O conc_server.c é um servidor concorrente que recebe até 10 clientes por vez.

Adicionado menu-server-side. e menu-client-side.c que tratam respectivamente do lado do cliente e do lado do servdior do trabalho.
Menu server-side quase completo sem testes, entretanto há um erro pendenet a se resolver no caso de tratamento de erros. Ao detectar um erro na busca de uma disciplina o servidor envia um erro, porem em uma mensagem em um formato no esperado pelo cliente. É necessário também popular/inicializar os dados das disciplinas;

Menu client-side com implementações de funcoes de tratamento de mensagens faltantes mas com backbone criado, não testado.
