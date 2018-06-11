package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;
import compute.RMI_Interface;


public class ClientMain {

	private static String GREETING_MESSAGE = "\n\n" + 
			"As disciplinas disponiveis sao: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\n\n" + 
			"As opcoes disponiveis sao:\n\n" + 
			"  1 - lista todos os codigos de disciplinas com seus respectivos titulos\n\n" + 
			"  2 - dado o codigo de uma disciplina retorna a ementa\n\n" + 
			"  3 - dado o codigo de uma disciplina, retorna todas as informacoes desta disciplina\n\n" + 
			"  4 - lista todas as informacoes de todas as disciplinas\n\n" + 
			"  5 - escreve um comentario sobre a proxima aula de uma disciplina\n\n" + 
			"  6 - dado o codigo de uma disciplina retorna o comentario sobre a ultima aula da disciplina\n\n" + 
			"  7 - sair do sistema\n\n" + 
			"  Para acessar, digite o codigo do comando - a disciplina logo depois caso seja\n\n" + 
			"  necessario(comandos 2, 3 e 6) - usuario senha e depois o comentario para o\n\n" + 
			"  comando 5 -  e somente entao pressione \'enter\':\n\n" + 
			"  exemplo: \n \"1\"\n \"2 MC102\"\n \"5 MC102 usuario senha comentario\"\n ";
	
	private static String ERROR_MESSAGE = "A mensagem enviada possui um comando invalido";
	
	public static void main(String args[]) {
		
        String input = new String();
        Scanner sc = new Scanner(System.in);
        char option;
        String disc_id = null, user_name = null, psswd = null;
        
		
		if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            String name = "Message";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            RMI_Interface message = (RMI_Interface) registry.lookup(name);
            

            do {

            	System.out.print(GREETING_MESSAGE);

            	
            	input = sc.next();
            	option = input.charAt(0);
            	
            	if (option != '7') {
            		if(option != '1' && option != '4') {
                		disc_id = sc.next();
                		if(option == '6'){
                			user_name = sc.next();
                			psswd = sc.next();
                		}
                	}
                	
            		String server_output;
            		
                	switch(option) {
        			case '1':
        				server_output = message.listAllDisciplines();
        			case '2':
        				server_output = message.disciplineMenu(disc_id);
        			case '3':
        				server_output = message.disciplineInfo(disc_id);
        			case '4':
        				server_output = message.listAllDisciplinesInfo();
        			case '5':
        				server_output = message.writeComment(disc_id, user_name, psswd);
        			case '6':
        				server_output = message.getComment(disc_id);
        			default:
        				server_output = ERROR_MESSAGE;
                	}
                	
                	
                	System.out.println(server_output);
            	}
            } while (option != '7');

            
        } catch (Exception e) {
            System.err.println("Client exception:");
            e.printStackTrace();
        }
        
        sc.close();
	}
}
