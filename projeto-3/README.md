# Compilando

considerando que você tá na pasta src:

mkdir ../class

javac -d ../class server/RMI_Server.java server/Discipline.java interface_rmi/RMI_Interface.java client/ClientMain.java

jar cvf ../class/server/RMI_Server.jar ../class/server/RMI_Server.class

# Executando o servidor
rmiregistry &

java -cp /home/nathyharumi/mc833/projeto-3/class/ -Djava.rmi.server.hostname=localhost -Djava.rmi.server.codebase=/home/nathyharumi/mc833/projeto-3/class/server/RMI_Server.jar -Djava.security.policy=server.policy server.RMI_Server

# Tentativa 2

# Compilando 2.0
javac interface_rmi/RMI_Interface.java

jar cvf interface_rmi.jar interface_rmi/*.class

javac -classpath interface_rmi.jar server/RMI_Server.java server/Discipline.java

javac -classpath interface_rmi.jar server/RMI_Server.java server/Discipline.java

javac client/ClientMain.java

# Executando o Servidor 2.0

/*Lembrando que o rmiregistry tem que ser logo depois da compilacao e logo antes da execução, porque eu nao sei mas nao funciona quando nao é*/

rmiregistry &

java -cp /home/tuliomartins/mc833/projeto-3/src/:/home/tuliomartins/mc833/projeto-3/src/interface_rmi.jar -Djava.rmi.server.hostname=localhost -Djava.rmi.server.codebase=/home/tuliomartins/mc833/projeto-3/src/interface_rmi.jar  server.RMI_Server

#Executando o Cliente

java -cp /home/tuliomartins/mc833/projeto-3/src/:/home/tuliomartins/mc833/projeto-3/src/interface_rmi.jar -Djava.rmi.server.codebase=http://localhost/~tuliomartins/mc833/projeto-3/src/interface_rmi.jar  client.ClientMain localhost
