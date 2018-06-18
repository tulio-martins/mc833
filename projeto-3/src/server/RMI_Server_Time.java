package server;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;


import interface_rmi.RMI_Interface;


public class RMI_Server_Time implements RMI_Interface {

	private static ArrayList<Discipline> disc;
	
	public RMI_Server_Time() {
		super();
	}
	
	public String listAllDisciplines() throws RemoteException {
		long start = System.nanoTime();
		long finish;
		String output = new String();
		PrintWriter writer;
		
		output = "";
		
		for(int i =0; i < 10; i++)
				output += "Discplina "+ disc.get(i).getId() + ": " + disc.get(i).getTitulo() + "\n";
		
		finish = System.nanoTime();
		double microseconds;
		
		try {
			writer  = new PrintWriter(new FileWriter("LIST_DISCIPLINES.csv", true));
			
			
			microseconds = (finish - start) / 1000;
			
			writer.print(microseconds+",");
			writer.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return output;
	}
	
	public String disciplineMenu(String disc_id) throws RemoteException {
		long start = System.nanoTime();
		long finish;
		double microseconds;
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				
				finish  = System.nanoTime();
				
				try {
					PrintWriter writer;
					writer  = new PrintWriter(new FileWriter("DISCIPLINE_MENU.csv", true));
					
					
					microseconds = (finish - start) / 1000;
					
					writer.print(microseconds+",");
					writer.close();
					
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				return "Disciplina: "+disc.get(i).getId() + ".\n Ementa :" + disc.get(i).getEmenta() + "\n";
			}
		}
		
		finish  = System.nanoTime();
		
		try {
			PrintWriter writer;
			writer  = new PrintWriter(new FileWriter("DISCIPLINE_MENU.csv", true));
			
			
			microseconds = (finish - start) / 1000;
			
			writer.print(microseconds+",");
			writer.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String disciplineInfo(String disc_id) throws RemoteException {
		FileReader f;
		String comment = new String();
		String line;
		
		long start = System.nanoTime();
		long finish;
		
		
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
				
				
				finish  = System.nanoTime();
				double microseconds;
				

				finish  = System.nanoTime();
				
				try {
					PrintWriter writer;
					writer  = new PrintWriter(new FileWriter("DISCIPLINE_INFO.csv", true));
					
					
					microseconds = (finish - start) / 1000;
					
					writer.print(microseconds+",");
					writer.close();
					
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				return " Disciplina: "+disc.get(i).getId() + ".\n Titulo : " + disc.get(i).getTitulo() +
						".\n Ementa :" + disc.get(i).getEmenta() + ".\n Sala :" + disc.get(i).getSala_de_aula() +
						".\n Horario :" + disc.get(i).getHorario() + ".\n Comentario da ultima aula :" + comment + "\n";
			}
		}
		

		double microseconds;
		

		finish  = System.nanoTime();
		
		try {
			PrintWriter writer;
			writer  = new PrintWriter(new FileWriter("DISCIPLINE_INFO.csv", true));
			
			
			microseconds = (finish - start) / 1000;
			
			writer.print(microseconds+",");
			writer.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String listAllDisciplinesInfo() throws RemoteException {
		String output = new String();
		
		FileReader f;
		String comment = new String();
		String line;
		
		long start = System.nanoTime();
		long finish;
		double microseconds;
		
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
		
		finish = System.nanoTime();
		
		try {
			PrintWriter writer;
			writer  = new PrintWriter(new FileWriter("ALL_DISCIPLINES.csv", true));
			
			
			microseconds = (finish - start) / 1000;
			
			writer.print(microseconds+",");
			writer.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return output;
	}

	public String writeComment(String disc_id, String user_name, String psswd, String comment)
			throws RemoteException {
		PrintWriter writer;
		
		long start = System.nanoTime();
		long finish;
		
		
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				if(user_name.equals(disc.get(i).getUsuario())) {
					if(psswd.equals(disc.get(i).getSenha())) {
						try {
							writer  = new PrintWriter(disc.get(i).getId()+".txt");
							
							
							writer.println(comment);
							writer.close();
							
							finish  = System.nanoTime();
							double microseconds;
							
							try {
								PrintWriter time_writer;
								time_writer  = new PrintWriter(new FileWriter("WRITE_COMMENT.csv", true));
								
								
								microseconds = (finish - start) / 1000;
								
								time_writer.print(microseconds+",");
								time_writer.close();
								
							} catch (FileNotFoundException e) {
								e.printStackTrace();
							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							
							
							
							
							return "Comentario escrito com sucesso";
						} catch (FileNotFoundException e) {
							e.printStackTrace();
							
							finish = System.nanoTime();
							double microseconds;
							
							try {
								PrintWriter time_writer;
								time_writer  = new PrintWriter(new FileWriter("WRITE_COMMENT.csv", true));
								
								
								microseconds = (finish - start) / 1000;
								
								time_writer.print(microseconds+",");
								time_writer.close();
								
							} catch (FileNotFoundException e1) {
								e1.printStackTrace();
							} catch (IOException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
							
							return "Erro inesperado e intratatavel";
						}

						
					} else {
						
						finish = System.nanoTime();
						double microseconds;
						
						try {
							PrintWriter time_writer;
							time_writer  = new PrintWriter(new FileWriter("WRITE_COMMENT.csv", true));
							
							
							microseconds = (finish - start) / 1000;
							
							time_writer.print(microseconds+",");
							time_writer.close();
							
						} catch (FileNotFoundException e) {
							e.printStackTrace();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
						return "Senha incorreta para disciplina "+disc_id;
					}
				} else {
					
					finish = System.nanoTime();
					double microseconds;
					
					try {
						PrintWriter time_writer;
						time_writer  = new PrintWriter(new FileWriter("WRITE_COMMENT.csv", true));
						
						
						microseconds = (finish - start) / 1000;
						
						time_writer.print(microseconds+",");
						time_writer.close();
						
					} catch (FileNotFoundException e) {
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
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
		
		long start = System.nanoTime();
		long finish;
		
		
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
				
				finish = System.nanoTime();
				double microseconds;
				
				try {
					PrintWriter time_writer;
					time_writer  = new PrintWriter(new FileWriter("GET_COMMENT.csv", true));
					
					
					microseconds = (finish - start) / 1000;
					
					time_writer.print(microseconds+",");
					time_writer.close();
					
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				return " Disciplina: "+disc.get(i).getId() + ".\n Comentario da ultima aula :" + comment + "\n";
			}
		}
		
		finish = System.nanoTime();
		double microseconds;
		
		try {
			PrintWriter time_writer;
			time_writer  = new PrintWriter(new FileWriter("GET_COMMENT.csv", true));
			
			
			microseconds = (finish - start) / 1000;
			
			time_writer.print(microseconds+",");
			time_writer.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "Id da disciplina incorreto\n";
	}
	
	public static void main(String args[]) {
		
		disc = Discipline.generate();
		
		
		
		try {
			String name = "Message";
			RMI_Interface engine = new RMI_Server_Time();
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
