# Compilando
javac src/interface_rmi/RMI_Interface.java

jar cvf interface_rmi.jar src/interface_rmi/*.class

javac -classpath interface_rmi.jar src/server/RMI_Server.java src/server/Discipline.java

javac src/client/ClientMain.java

# Executando o Servidor

/*Lembrando que o rmiregistry tem que ser logo depois da compilacao e logo antes da execução*/

rmiregistry &

java -cp $PWD/src:/$PWD/interface_rmi.jar -Djava.rmi.server.hostname={IP DO SERVIDOR} -Djava.rmi.server.codebase=$PWD/interface_rmi.jar  server.RMI_Server

# Executando o Cliente

java -cp $PWD:$PWD/interface_rmi.jar -Djava.rmi.server.codebase=http://localhost/~{CAMINHO NO SERVIDOR D PASTA PÓS HOME ATE SRC}/src/interface_rmi.jar  client.ClientMain {IP DO SERVIDOR}
