package client;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Date;
import java.util.Scanner;
import interface_rmi.RMI_Interface;


public class ClientMain_Time {

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
        String disc_id = null, user_name = null, psswd = null, comment  = null;
        
        Date start;
		Date finish;
		double miliseconds;
		
		PrintWriter writer;
		
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
                		System.out.println(disc_id);
                		if(option == '5'){
                			user_name = sc.next();
                			psswd = sc.next();
                			comment = sc.nextLine();
                		}
                	}
                	
            		String server_output;
            		
                	switch(option) {
        			case '1':
        				start = new Date();
        				server_output = message.listAllDisciplines();
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_LIST_DISCIPLINES.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
        			case '2':
        				start = new Date();
        				server_output = message.disciplineMenu(disc_id);
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_DISCIPLINE_MENU.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				break;
        			case '3':
        				start = new Date();
        				server_output = message.disciplineInfo(disc_id);
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_DISCIPLINE_INFO.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
        			case '4':
        				start = new Date();
        				server_output = message.listAllDisciplinesInfo();
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_ALL_DISCIPL_INFO.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
        			case '5':
        				start = new Date();
        				server_output = message.writeComment(disc_id, user_name, psswd, comment);
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_WRITE_COMMENT.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
        			case '6':
        				start = new Date();
        				server_output = message.getComment(disc_id);
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_GET_COMMENT.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
        			default:
        				start = new Date();
        				server_output = ERROR_MESSAGE;
        				finish = new Date();
        				
        				writer  = new PrintWriter(new FileWriter("CLIENT_ERROR.csv", true));
        				
        				miliseconds = finish.getTime() - start.getTime();
        				
        				writer.println(miliseconds+",");
						writer.close();
        				
        				break;
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
