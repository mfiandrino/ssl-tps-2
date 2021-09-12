	digraph CARACTER_COMUN { 
		rankdir=LR;
		labelloc=t;	
		decorate=true;	
		labelfloat=false;	
		fontname=Helvetica;	
		ranksep=equally;	
		subgraph cluster_0 {		
			style=filled;		
			color=lightgrey;		
		    "*comienzoDeLinea" [shape=box,fontsize=40, height=5, width=5]; 
		    enPalabra [shape=box, height=1, width=1]; 
		    espacio [shape=box, height=1, width=1];
		    caracterEspecial [shape=box, height=1, width=1];
		    posibleIncludeDefineUndef [shape=box, height=1, width=1];
			label = "INICIO";		
		}	
	

		subgraph cluster_0 {		
			style=filled;		
			color=lightgrey;		
			comentarioFinDeLinea [shape=box, height=1, width=1];
			comentarioMultilinea [shape=box, height=1, width=1];
			posibleFinDeComentarioMultilinea [shape=box, height=1, width=1];
			FinDeComentarioMultilinea [shape=box, height=1, width=1];
			posibleComentario [shape=box, height=1, width=1];
			label = "COMENTARIOS";		
		}		

		subgraph cluster_1 {		
			style=filled;		
			color=lightgrey;
			aperturaComillasSimples [shape=box, height=1, width=1];
			entreComillasSimples [shape=box, height=1, width=1];
			cierreComillasSimples [shape=box, height=1, width=1];
			label = "COMILLAS_SIMPLES";		
		}

		subgraph cluster_2 {		
			style=filled;		
			color=lightgrey;		
			aperturaComillasDobles [shape=box, height=1, width=1];
			cierreComillasDobles [shape=box, height=1, width=1];
			entreComillasDobles [shape=box, height=1, width=1];
			label = "COMILLAS_DOBLES";		
		}

		subgraph cluster_3 {		
			style=filled;		
			color=lightgrey;		
			d [shape=box, height=1, width=1];
			de [shape=box, height=1, width=1];
			def [shape=box, height=1, width=1];
			defi [shape=box, height=1, width=1];
			defin [shape=box, height=1, width=1];
			define [shape=box, height=1, width=1];
			defineEspacio [shape=box, height=1, width=1];
			defineIdentificador [shape=box, height=1, width=1];
			identificadorInvalido [shape=box, height=1, width=1];
			numeralIncorrecto [shape=box, height=1, width=1];
			defineIdentificadorEspacio [shape=box, height=1, width=1];
			textoDefineInvalido [shape=box, height=1, width=1];
			defineTexto [shape=box, height=1, width=1];
			label = "DEFINE";		
		}

		subgraph cluster_4 {		
			style=filled;		
			color=lightgrey;		
			u [shape=box, height=1, width=1];
			un [shape=box, height=1, width=1];
			und [shape=box, height=1, width=1];
			unde [shape=box, height=1, width=1];
			esUndef [shape=box, height=1, width=1];
			undefEspacio [shape=box, height=1, width=1];
			undefIdentificador [shape=box, height=1, width=1];
			label = "UNDEF";		
		}

	    comentarioFinDeLinea -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(' '), putchar(c)"];
	    comentarioFinDeLinea -> comentarioFinDeLinea [label = " EOC "];

	    comentarioMultilinea -> posibleFinDeComentarioMultilinea [label = " c == '*' "];
	    comentarioMultilinea -> comentarioMultilinea [label = " EOC "];

	    posibleFinDeComentarioMultilinea -> posibleFinDeComentarioMultilinea [label = " c == '*' "];
	    posibleFinDeComentarioMultilinea -> FinDeComentarioMultilinea [label = " c == '/' \n putchar(' ')"];
	    posibleFinDeComentarioMultilinea -> comentarioMultilinea [label = " EOC "];

	    FinDeComentarioMultilinea -> posibleComentario [label = " c == '/' "];
	    FinDeComentarioMultilinea -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    FinDeComentarioMultilinea -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    FinDeComentarioMultilinea -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c) "];
	    FinDeComentarioMultilinea -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c) "];
	    FinDeComentarioMultilinea -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c) "];
	    FinDeComentarioMultilinea -> caracterEspecial [label = " EOC \n putchar(c)"];

	    posibleComentario -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(/), putchar(c)"];
	    posibleComentario -> comentarioFinDeLinea [label = " c == '/' "];
	    posibleComentario -> aperturaComillasSimples [label = " c == ' \n putchar(/), putchar(c)"];
	    posibleComentario -> aperturaComillasDobles [label = " c == \" \n putchar(/), putchar(c) "];
	    posibleComentario -> comentarioMultilinea [label = " c == '*' "];
	    posibleComentario -> espacio [label = " c == ' ' or c == '\\t' \n putchar(/), putchar(c) "];
	    posibleComentario -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n putchar(/), nuevaPalabra(c)"];
	    posibleComentario -> caracterEspecial [label = " EOC \n putchar(/), putchar(c)"];

	    enPalabra -> "*comienzoDeLinea" [label = " c == '\\n' \n verificaEnTabla(), putchar(c) "];
	    enPalabra -> aperturaComillasSimples [label = " c == ' \n verificaEnTabla(), putchar(c) "];
	    enPalabra -> aperturaComillasDobles [label = " c == \" \n verificaEnTabla(), putchar(c)  "];
	    enPalabra -> posibleComentario [label = " c == '/' \n verificaEnTabla() "];
	    enPalabra -> espacio [label = " c == ' ' or c == '\\t' \n verificaEnTabla(), putchar(c)"];
	    enPalabra -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevoCaracterEnPalabra() "];
	    enPalabra -> caracterEspecial [label = " EOC \n verificaEnTabla(), putchar(c) "];

	    espacio -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c)"];
	    espacio -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    espacio -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    espacio -> posibleComentario [label = " c == '/' "];
	    espacio -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c)"];
	    espacio -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c)"];
	    espacio -> caracterEspecial [label = " EOC \n putchar(c) "];

	    caracterEspecial -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c)"];
	    caracterEspecial -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    caracterEspecial -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    caracterEspecial -> posibleComentario [label = " c == '/' "];
	    caracterEspecial -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c)"];
	    caracterEspecial -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c)"];
	    caracterEspecial -> caracterEspecial [label = " EOC \n putchar(c)"];

	    "*comienzoDeLinea" -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c) "];
	    "*comienzoDeLinea" -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    "*comienzoDeLinea" -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    "*comienzoDeLinea" -> posibleComentario [label = " c == '/' "];
	    "*comienzoDeLinea" -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c)"];
	    "*comienzoDeLinea" -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c)"];
	    "*comienzoDeLinea" -> posibleIncludeDefineUndef [label = " c == '#' "];
	    "*comienzoDeLinea" -> caracterEspecial [label = " EOC \n putchar(c)"];

	    aperturaComillasSimples -> cierreComillasSimples [label = " c == ' \n putchar(c)"];
	    aperturaComillasSimples -> entreComillasSimples [label = " EOC \n putchar(c)"];

	    entreComillasSimples -> cierreComillasSimples [label = " c == ' \n putchar(c)"];
	    entreComillasSimples -> entreComillasSimples [label = " EOC \n putchar(c)"];

	    cierreComillasSimples -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c)"];
	    cierreComillasSimples -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    cierreComillasSimples -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    cierreComillasSimples -> posibleComentario [label = " c == '/' "];
	    cierreComillasSimples -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c)"];
	    cierreComillasSimples -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c)"];
	    cierreComillasSimples -> caracterEspecial [label = " EOC \n putchar(c)"];

	    aperturaComillasDobles -> cierreComillasDobles [label = " c == \" \n putchar(c) "];
	    aperturaComillasDobles -> entreComillasDobles [label = " EOC \n putchar(c)"];

	    entreComillasDobles -> cierreComillasDobles [label = " c == \" \n putchar(c)"];
	    entreComillasDobles -> entreComillasDobles [label = " EOC \n putchar(c)"];

	    cierreComillasDobles -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar(c)"];
	    cierreComillasDobles -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    cierreComillasDobles -> aperturaComillasDobles [label = " c == \" \n putchar(c)"];
	    cierreComillasDobles -> posibleComentario [label = " c == '/' "];
	    cierreComillasDobles -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c)"];
	    cierreComillasDobles -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c)"];
	    cierreComillasDobles -> caracterEspecial [label = " EOC \n putchar(c)"];

	    posibleIncludeDefineUndef -> d [label = " c == 'd' "];
	    posibleIncludeDefineUndef -> u [label = " c == 'u' "];
	    posibleIncludeDefineUndef -> i [label = " c == 'i' "];
	    posibleIncludeDefineUndef -> numeralIncorrecto [label = " EOC \n putchar('#'), putchar(c)"];

	    d -> de [label = "c == 'e' " ];
	    d -> numeralIncorrecto [label = "c == EOC" ];

	    de -> def [label = "c == 'f'" ];
	    de -> numeralIncorrecto [label = "c == EOC " ];

	    def -> defi [label = "c == 'i' " ];
	    def -> numeralIncorrecto [label = "c == EOC " ];

	    defi -> defin [label = "c == 'n' " ];
	    defi -> numeralIncorrecto [label = "c == EOC " ];

	    defin -> define [label = "c == 'e' " ];
	    defin -> numeralIncorrecto [label = "c == EOC " ];

	    define -> defineEspacio [label = "c == ' '  or c == '\\t' "];
	    define -> numeralIncorrecto [label = "c == EOC " ];

	    defineEspacio -> defineIdentificador [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
	    defineEspacio -> defineEspacio [label = " c == ' ' or c == '\\t' "];
	    defineEspacio -> identificadorInvalido [label = " EOC "];

	    defineIdentificador -> defineIdentificador [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'z' or c == '0'...'9' \n nuevoIdentificador(c)" ];
	    defineIdentificador -> defineIdentificadorEspacio [label = "c == ' ' or c == '\\t' " ];
	    defineIdentificador -> identificadorInvalido [label = " EOC " ];

	    defineIdentificadorEspacio -> defineIdentificadorEspacio [label = "c == ' ' or c == '\\t' " ];
	    defineIdentificadorEspacio -> textoDefineInvalido [label = "c == '\\n' " ];
	    defineIdentificadorEspacio -> defineTexto [label = " EOC " ];

	    defineTexto -> "*comienzoDeLinea" [label = "c == '\\n' " ];
	    defineTexto -> defineTexto [label = " EOC " ];

	    u -> un [label = "c == 'n' " ];
	    u -> numeralIncorrecto [label = "c == EOC " ];

	    un -> und [label = "c == 'd' " ];
	    un -> numeralIncorrecto [label = "c == EOC " ];

	    und -> unde [label = "c == 'e' " ];
	    und -> numeralIncorrecto [label = "c == EOC " ];

	    unde -> esUndef [label = "c == 'f' " ];
	    unde -> numeralIncorrecto [label = "c == EOC " ];

	    esUndef -> undefEspacio [label = "c == ' ' or c == '\\t' " ];
	    esUndef -> numeralIncorrecto [label = "c == EOC " ];

	    undefEspacio -> undefIdentificador [label = "c == '_' or c =='A'...'Z' or c =='a'...'z' \n nuevoIdentificador(c)" ];
	    undefEspacio -> undefEspacio [label = "c == ' ' or c == '\\t' " ];
	    undefEspacio -> identificadorInvalido [label = " EOC " ];

	    undefIdentificador -> undefIdentificador [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'z' or '0'...'9' \n nuevoCaracterIdentificador(c)" ];
	    undefIdentificador -> "*comienzoDeLinea" [label = "c == '\\n \n undef(identificador) " ];
	    undefIdentificador -> identificadorInvalido [label = " EOC " ];

	}
	
![DOT - Preprocesador](https://user-images.githubusercontent.com/82002194/133004996-f765dc2e-ab79-445a-9220-409dbf865ce3.png)

