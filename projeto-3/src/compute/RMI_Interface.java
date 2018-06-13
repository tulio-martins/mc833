package compute;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI_Interface extends Remote {

	public String listAllDisciplines() throws RemoteException;
	public String disciplineMenu(String disc_id) throws RemoteException;
	public String disciplineInfo(String disc_id) throws RemoteException;
	public String listAllDisciplinesInfo() throws RemoteException;
	public String writeComment(String disc_id, String user_name, String psswd, String comment) throws RemoteException;
	public String getComment(String disc_id) throws RemoteException;
	
}
