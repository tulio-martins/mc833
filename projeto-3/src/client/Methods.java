package client;

import java.io.Serializable;
import compute.Task;

public class Methods implements Task<String>, Serializable {

	private char option;
	private String disc_id;
	private String user_name;
	private String psswd;
	
	private static String ERROR_MESSAGE = "A mensagem enviada possui um comando invalido";
	
	public Methods(char option, String disc_id, String user_name, String psswd) {
		this.option = option;
		this.disc_id = disc_id;
		this.user_name = user_name;
		this.psswd = psswd;
	}

	public String execute() {
		// TODO Auto-generated method stub
		return null;
	}
	
	
	
}
