package server;

import java.util.ArrayList;
import java.util.List;

public class Discipline {

	private String id;
	private String titulo;
	private String ementa;
	private String sala_de_aula;
	private String horario;
	private String comentario;
	private String usuario;
	private String senha;
	
	
	private Discipline(String id, String titulo, String ementa, String sala_de_aula,
					  String horario, String comentario, String usuario, String senha) {
		this.id = id;
		this.ementa = ementa;
		this.sala_de_aula = sala_de_aula;
		this.horario = horario;
		this.comentario = comentario;
		this.usuario = usuario;
		this.senha = senha;
		
	}

	public static ArrayList<Discipline> generate() {
		// TODO Instancia uma ArrayList de Disciplinas
		
		ArrayList<Discipline> disc = new ArrayList<Discipline>();
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC102\0", "Algoritmos e Programacao de Computadores\0",
				"Conceitos basicos de organizacao de computadores. Construcao de algoritmos e sua representacao em pseudocodigo e" +
				" linguagens de alto nivel. Desenvolvimento sistematico e implementacao de programas. Estruturacao, depuracao, testes" +
				" e documentacao de programas. Resolucao de problemas.\0",
				"CC02\0", "Sexta 14:00 a 16:00\0", "mc102.txt\0", "zanoni\0", "zanoni123\0"));
		
		
		/*<================== Falta mexer daqui para baixo ================>*/
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		disc.add(new Discipline("MC833\0", "Programacao de Redes de Computadores\0",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CC03\0", "Quinta 10:00 a 12:00\0", "mc833.txt\0", "edmundo\0", "edmundo123\0"));
		
		
		return disc;
	}

	public void setId(String id) {
		this.id = id;
	}
	
	
}
