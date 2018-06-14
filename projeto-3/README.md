# Compilando

considerando que você tá na pasta src:

mkdir ../class

javac -d ../class server/RMI_Server.java server/Discipline.java interface_rmi/RMI_Interface.java client/ClientMain.java

jar cvf ../class/server/RMI_Server.jar ../class/server/RMI_Server.class

# Executando o servidor
rmiregistry &

java -cp /home/nathyharumi/mc833/projeto-3/class/ -Djava.rmi.server.hostname=localhost -Djava.rmi.server.codebase=/home/nathyharumi/mc833/projeto-3/class/server/RMI_Server.jar -Djava.security.policy=server.policy server.RMI_Server
 
