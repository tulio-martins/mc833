package compute;

public class ServerMain {

	private char option;
	private String disc_id;
	private String user_name;
	private String psswd;
	
	private static String ERROR_MESSAGE = "A mensagem enviada possui um comando invalido";
	
	public String Result() {
		
		switch(option) {
			case '1':
				return listAllDisciplines();
			case '2':
				return disciplineMenu();
			case '3':
				return disciplineInfo();
			case '4':
				return listAllDisciplinesInfo();
			case '5':
				return writeComment();
			case '6':
				return getComment();
			default:
				return ERROR_MESSAGE;
		}
	}
	
	public static String listAllDisciplines() {
		
	}
	
	public static String disciplineMenu() {
		
	}
	
	public static String disciplineInfo() {
		
	}
	
	public static String listAllDisciplinesInfo() {
		
	}
	
	public static String writeComment() {
		
	}
	
	public static String getComment() {
		
	}
	
}
