TCP Connection Test

Teste Echo de Conexão - quando cliente é conectado ao servidor qualquer 
mensagem enviad pelo cliente e lida e repetida pelo servidor.

Os arquivos "client.c" e "server.c" fazem parte do processo. Apenas compile
com gcc e ao executr o cliente o faca com o parametro do localhost:
    "./client 127.0.0.1"
    
Ainda não é um servidor concorrente, apenas aceita um cliente.
