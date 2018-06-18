package server;

import java.util.ArrayList;

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
		this.titulo = titulo;
		this.sala_de_aula = sala_de_aula;
		this.horario = horario;
		this.comentario = comentario;
		this.usuario = usuario;
		this.senha = senha;
		
	}

	public static ArrayList<Discipline> generate() {
		// TODO Instancia uma ArrayList de Disciplinas
		
		ArrayList<Discipline> disc = new ArrayList<Discipline>();
		
		disc.add(new Discipline("MC833", "Programacao de Redes de Computadores",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.",
				"CC03", "Quinta 10:00 a 12:00", "MC833.txt", "edmundo", "edmundo123"));
		
		disc.add(new Discipline("MC102", "Algoritmos e Programacao de Computadores",
				"Conceitos basicos de organizacao de computadores. Construcao de algoritmos e sua representacao em pseudocodigo e" +
				" linguagens de alto nivel. Desenvolvimento sistematico e implementacao de programas. Estruturacao, depuracao, testes" +
				" e documentacao de programas. Resolucao de problemas.",
				"CC02", "Sexta 14:00 a 16:00", "MC102.txt", "zanoni", "zanoni123"));
		
		
		disc.add(new Discipline("MC536\0", "Bancos de Dados: Teoria e Pratica\0",
				"Arquiteturas de sistemas de gerenciamento de bancos de dados. Modelagem de dados: modelos conceituais e logicos," +
				" incluindo o modelo relacional e normalizacao. algebra relacional. Linguagens de definicao e de manipulacao de dados." +
				" Otimizacao de consultas. Mecanismos de protecao, recuperacao e seguranca. Controle de concorrência. Bancos de dados nao relacionais." +
				" Projeto e desenvolvimento de ferramentas e tecnicas utilizadas na solucao de problemas de sistemas de informacao, utilizando bancos de dados." +
				" Modelagem, especificacao, projeto e implementacao de aplicacoes em sistemas de informacao.",
				"CB02", "Segunda 10:00 a 12:00; Quarta 10:00 a 12:00", "MC536.txt", "breno", "breno123"));
		

		disc.add(new Discipline("MC358", "Fundamentos Matematicos da Computacao",
				"Conceitos basicos de matematica strcpy(discreta e de logica para computacao.Tecnicas de provas, inducao matematica." +
				" Relacoes e conceitos de teoria de grafos. Modelagem de problemas usando grafos.",
				"CB02\0", "Terca 19:00 a 21:00; Quarta 19:00 a 21:00", "MC358.txt", "arnaldo", "arnaldo123"));
		

		
		disc.add(new Discipline("MC346\0", "Paradigmas da Computacao",
				"Programacao utilizando diferentes tecnologias de comunicacao: sockets, TCP e UDP, e chamada de metodo remoto.\0",
				"CB12", "Segunda 16:00 a 18:00; Quarta 16:00 a 18:00", "MC346.txt", "wainer", "wainer123"));
		

		
		
		disc.add(new Discipline("MC750", "Construcao de Interfaces Homem-Computador",
				"Introducao a Interfaces Humano-Computador (IHC). Aspectos humanos. Aspectos tecnologicos. Processos," +
				" metodos e tecnicas de pesquisa, design e avaliacao. Ferramentas de suporte. Concepcao, modelagem e" +
				" prototipacao de solucoes em interfaces de usuario.0",
				"CB06\0", "Terca 16:00 a 18:00; Quinta 16:00 a 18:00", "MC750.txt", "baranauskas", "baranauskas123"));
		
	
		
		disc.add(new Discipline("MC458", "Projeto e Analise de Algoritmos I",
				"Tecnicas de projeto e analise de algoritmos. Ferramental Matematico para Analise de Algoritmos." +
				" Projeto de algoritmos por inducao. Busca, ordenacao e estatisticas de ordem. Programacao Dinâmica. Algoritmos Gulosos.",
				"PB18\0", "Terca 10:00 a 12:00; Quinta 10:00 a 12:00", "MC458.txt", "lehilton", "lehilton123"));
		
		
		disc.add(new Discipline("MC558", "Projeto e Analise de Algoritmos II",
				"Tratamento de Problemas NP-dificeis: algoritmos exatos, algoritmos aproximados e algoritmos heuristicos.",
				"CB17", "Terca 16:00 a 18:00; Quinta 16:00 a 18:00", "MC558.txt", "christiane\0", "christiane123"));	

		
		disc.add(new Discipline("MC658", "Projeto e Analise de Algoritmos III",
				"Tratamento de Problemas NP-dificeis: algoritmos exatos, algoritmos aproximados e algoritmos heuristicos.",
				"CB13", "Segunda 19:00 a 21:00; Quarta 21:00 a 23:00", "MC658.txt", "flavio", "flavio123"));
		
		disc.add(new Discipline("MC886\0", "Aprendizado de Maquina",
				"Tecnicas de aprendizado de maquina estatistico para classificacao, agrupamento e deteccao de outliers.",
				"CB01", "Segunda 19:00 a 21:00; Quarta 21:00 a 23:00", "MC886.txt", "rocha", "rocha123"));
		
		
		return disc;
	}

	public String getId() {
		return id;
	}
	
	public String getTitulo() {
		return titulo;
	}
	
	public String getEmenta() {
		return ementa;
	}

	public String getSala_de_aula() {
		return sala_de_aula;
	}

	public String getHorario() {
		return horario;
	}

	public String getComentario() {
		return comentario;
	}

	public String getUsuario() {
		return usuario;
	}

	public String getSenha() {
		return senha;
	}
	
	
}
