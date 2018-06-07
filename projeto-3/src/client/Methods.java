package client;

import java.io.Serializable;
import server.Task;

public class Methods implements Task<String>, Serializable {

	private char option;
	
	
	public String execute() {
		
		switch(option) {
			case '1':
				return listAllDisciplines();
				break;
			case '2':
				return disciplineMenu(disc_id);
				break;
			case '3':
				return listAllDisciplines();
				break;
			case '4':
				return listAllDisciplines();
				break;
			case '5':
				return listAllDisciplines();
				break;
			case '6':
				return listAllDisciplines();
				break;
			case '7':
				return listAllDisciplines();
				break;
		}
	}
	
	public static String listAllDisciplines() {
		
	}
	
	public static String disciplineMenu(String disc_id) {
		
	}
	
	public static String discplineInfo(String disc_id) {
		
	}
	
	public static String listAllDiscplinesInfo() {
		
	}
	
	public static String writeComment(String disc_id, String user_name, String user_psswd) {
		
	}
	
	public static String getComment(String disc_id) {
		
	}
}
