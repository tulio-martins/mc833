# TCP Connection Test

Teste Echo de Conexão - quando cliente é conectado ao servidor qualquer
mensagem enviado pelo cliente é lida e repetida pelo servidor.

Os arquivos "client.c", "server.c" e "conc_server.c" fazem parte do processo. Apenas compile
com gcc e ao executr o cliente o faca com o parametro do localhost:

    "./client 127.0.0.1"

O server.c é um servidor iterativo, apenas aceita um cliente por vez. Caso haja dois clientes, ele esperará o primeiro terminar a conexão para receber as informações do segundo cliente.

O conc_server.c é um servidor concorrente que recebe até 10 clientes por vez.
