package server;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;


import interface_rmi.RMI_Interface;


public class RMI_Server implements RMI_Interface {

	private static ArrayList<Discipline> disc;
	
	public RMI_Server() {
		super();
	}
	
	public String listAllDisciplines() throws RemoteException {
		
		String output = new String();
		
		output = "";
		
		for(int i =0; i < 10; i++)
				output += "Discplina "+ disc.get(i).getId() + ": " + disc.get(i).getTitulo() + "\n";
		
		return output;
	}
	
	public String disciplineMenu(String disc_id) throws RemoteException {
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				return "Disciplina: "+disc.get(i).getId() + ".\n Ementa :" + disc.get(i).getEmenta() + "\n";
			}
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String disciplineInfo(String disc_id) throws RemoteException {
		FileReader f;
		String comment = new String();
		String line;
		
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				try {
					f = new FileReader(disc.get(i).getId() + ".txt");
					BufferedReader bf = new BufferedReader(f);
					
					comment = "";
					
					while((line = bf.readLine()) != null) {
		                comment += line;
		            }   
					
					bf.close();
					f.close();
				} catch (FileNotFoundException e) {
					comment = "N/A";
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				
				
				return " Disciplina: "+disc.get(i).getId() + ".\n Titulo : " + disc.get(i).getTitulo() +
						".\n Ementa :" + disc.get(i).getEmenta() + ".\n Sala :" + disc.get(i).getSala_de_aula() +
						".\n Horario :" + disc.get(i).getHorario() + ".\n Comentario da ultima aula :" + comment + "\n";
			}
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String listAllDisciplinesInfo() throws RemoteException {
		String output = new String();
		
		FileReader f;
		String comment = new String();
		String line;
		
		output = "";
		
		for(int i =0; i < 10; i++) {
			
			comment = "";
			
			try {
				f = new FileReader(disc.get(i).getId() + ".txt");
				BufferedReader bf = new BufferedReader(f);

				while((line = bf.readLine()) != null) {
					comment += line;
				}   

				bf.close();
				f.close();
			} catch (FileNotFoundException e) {
				comment = "N/A";
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			
			output += " Disciplina: "+disc.get(i).getId() + ".\n Titulo : " + disc.get(i).getTitulo() +
						".\n Ementa :" + disc.get(i).getEmenta() + ".\n Sala :" + disc.get(i).getSala_de_aula() +
						".\n Horario :" + disc.get(i).getHorario() + ".\n Comentario da ultima aula :" + comment + "\n";
		}
		
		return output;
	}

	public String writeComment(String disc_id, String user_name, String psswd, String comment)
			throws RemoteException {
		PrintWriter writer;
		
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				if(user_name.equals(disc.get(i).getUsuario())) {
					if(psswd.equals(disc.get(i).getSenha())) {
						try {
							writer  = new PrintWriter(disc.get(i).getId()+".txt");
							
							
							writer.println(comment);
							writer.close();
							
							return "Comentario escrito com sucesso";
						} catch (FileNotFoundException e) {
							e.printStackTrace();
							return "Erro inesperado e intratatavel";
						}

						
					} else {
						return "Senha incorreta para disciplina "+disc_id;
					}
				} else {
					return "Usuario para disciplina "+disc_id+" incorreto";
				}
			}
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String getComment(String disc_id) throws RemoteException {
		FileReader f;
		String comment = new String();
		String line;
		
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				try {
					f = new FileReader(disc.get(i).getId() + ".txt");
					BufferedReader bf = new BufferedReader(f);
					
					while((line = bf.readLine()) != null) {
		                comment += line;
		            }   
					
					bf.close();
					f.close();
				} catch (FileNotFoundException e) {
					comment = "N/A";
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				
				
				return " Disciplina: "+disc.get(i).getId() + ".\n Comentario da ultima aula :" + comment + "\n";
			}
		}
		
		return "Id da disciplina incorreto\n";
	}
	
	public static void main(String args[]) {
		
		disc = Discipline.generate();
		
		
		
		try {
			String name = "Message";
			RMI_Interface engine = new RMI_Server();
			RMI_Interface stub =
					(RMI_Interface) UnicastRemoteObject.exportObject(engine, 0);
			Registry registry = LocateRegistry.getRegistry();
			registry.rebind(name, stub);
			System.out.println("RMI_Server bound");
		} catch (Exception e) {
			System.err.println("RMI_Server exception:");
			e.printStackTrace();
		}
	}

}
