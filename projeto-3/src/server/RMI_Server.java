package server;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.List;


import compute.RMI_Interface;


public class RMI_Server implements RMI_Interface {

	private static List<Discipline> disc;
	
	public RMI_Server() {
		super();
	}
	
	public String listAllDisciplines() throws RemoteException {
		
		String output = new String();
		
		output = "";
		
		for(int i =0; i < 10; i++)
				output.concat("Discplina "+ disc.get(i).getId() + ": " + disc.get(i).getTitulo() + "\n");
		
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
		for(int i = 0 ;i < 10; i++) {
			if(disc_id.equals(disc.get(i).getId())) {
				return "Disciplina: "+disc.get(i).getId() + ".\n Ementa :" + disc.get(i).getEmenta() + "\n";
			}
		}
		
		return "Id da disciplina incorreto\n";
	}

	public String listAllDisciplinesInfo() throws RemoteException {
		String output = new String();
		
		output = "";
		
		for(int i =0; i < 10; i++)
				output.concat("Discplina "+ disc.get(i).getId() + ": " + disc.get(i).getTitulo() + "\n");
		
		return output;
	}

	public String writeComment(String disc_id, String user_name, String psswd)
			throws RemoteException {
		// TODO Auto-generated method stub
		return null;
	}

	public String getComment(String disc_id) throws RemoteException {
		
		return null;
	}
	
	public static void main(String args[]) {
		
		disc = Discipline.generate();
		
		
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}
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
