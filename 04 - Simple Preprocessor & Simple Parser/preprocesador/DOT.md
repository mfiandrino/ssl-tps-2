	digraph CARACTER_COMUN { 
		
		labelloc=t;	
		decorate=true;	
		labelfloat=false;	
		fontname=Helvetica;	
		ranksep=equally;	
		
		"*comienzoDeLinea" [shape=box]; 
		enPalabra;
		espacio;
		caracterEspecial;
		posibleIncludeDefineUndef;

		subgraph cluster_0 {		
			style=filled;		
			color=lightgrey;		
			comentarioFinDeLinea;
			comentarioMultilinea;
			posibleFinDeComentarioMultilinea;
			FinDeComentarioMultilinea;
			posibleComentario;
			label = "COMENTARIOS";		
		}		

		subgraph cluster_1 {		
			style=filled;		
			color=lightgrey;		
			aperturaComillasSimples;
			entreComillasSimples;
			cierreComillasSimples;
			label = "COMILLAS_SIMPLES";		
		}

		subgraph cluster_2 {		
			style=filled;		
			color=lightgrey;		
			aperturaComillasDobles;
			cierreComillasDobles;
			entreComillasDobles;
			label = "COMILLAS_DOBLES";		
		}

		subgraph cluster_3 {		
			style=filled;		
			color=lightgrey;		
			d;
			de;
			def;
			defi;
			defin;
			define;
			defineEspacio;
			defineIdentificador;
			identificadorInvalido;
			defineIdentificadorEspacio;
			textoDefineInvalido;
			defineTexto;
			label = "DEFINE";		
		}

		subgraph cluster_4 {		
			style=filled;		
			color=lightgrey;		
			u;
			un;
			und;
			unde;
			esUndef;
			undefEspacio;
			undefIdentificador;
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
	    posibleIncludeDefineUndef -> aperturaComillasSimples [label = " c == ' \n putchar('#'), putchar(c)"];
	    posibleIncludeDefineUndef -> aperturaComillasDobles [label = " c == \" \n putchar('#'), putchar(c)"];
	    posibleIncludeDefineUndef -> "*comienzoDeLinea" [label = " c == '\\n' \n putchar('#'), putchar(c)"];
	    posibleIncludeDefineUndef -> posibleComentario [label = " c == '/' \n putchar('#')"];
	    posibleIncludeDefineUndef -> espacio [label = " c == ' ' or c == '\\t' \n putchar('#'), putchar(c)"];
	    posibleIncludeDefineUndef -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n putchar('#'), putchar(c)"];
	    posibleIncludeDefineUndef -> caracterEspecial [label = " EOC \n putchar('#'), putchar(c)"];

	    d -> de [label = "c == 'e' " ];
	    d -> aperturaComillasSimples [label = "c == ' \n printf(#d), putchar(c)" ];
	    d -> aperturaComillasDobles [label = "c == '' \n printf(#d), putchar(c)" ];
	    d -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#d), putchar(c)" ];
	    d -> posibleComentario [label = "c == / \n printf(#d), putchar(c)" ];
	    d -> espacio [label = "c == ' ' or c == '\\t'  \n printf(#d), putchar(c)" ];
	    d -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'d' or c == 'f'...'z'  \n printf(#d), nuevaPalabra(c)" ];
	    d -> caracterEspecial [label = " EOC \n printf(#d), putchar(c)" ];

	    de -> def [label = "c == 'f'" ];
	    de -> aperturaComillasSimples [label = "c == ' \n printf(#de), putchar(c)" ];
	    de -> aperturaComillasDobles [label = "c == \" \n printf(#de), putchar(c)" ];
	    de -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#de), putchar(c)" ];
	    de -> posibleComentario [label = "c == / \n printf(#de), putchar(c)" ];
	    de -> espacio [label = "c == ' ' or c == '\t' \n printf(#de), putchar(c)" ];
	    de -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'e' or c == 'g'...'z' \n printf(#de), nuevaPalabra(c)" ];
	    de -> caracterEspecial [label = " EOC \n printf(#de), putchar(c)" ];

	    def -> defi [label = "c == 'i' " ];
	    def -> aperturaComillasSimples [label = "c == ' \n printf(#def), putchar(c)" ];
	    def -> aperturaComillasDobles [label = "c == \" \n printf(#def), putchar(c)" ];
	    def -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#def), putchar(c)" ];
	    def -> posibleComentario [label = "c == / \n printf(#def), putchar(c)" ];
	    def -> espacio [label = "c == ' '  or c == '\t' \n printf(#def), putchar(c)" ];
	    def -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'h' or c == 'j'...'z' \n printf(#def), nuevaPalabra(c)" ];
	    def -> caracterEspecial [label = " EOC \n printf(#def), putchar(c)" ];

	    defi -> defin [label = "c == 'n' " ];
	    defi -> aperturaComillasSimples [label = "c == ' \n printf(#defi), putchar(c)" ];
	    defi -> aperturaComillasDobles [label = "c == \" \n printf(#defi), putchar(c)" ];
	    defi -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#defi), putchar(c)" ];
	    defi -> posibleComentario [label = "c == / \n printf(#defi), putchar(c)" ];
	    defi -> espacio [label = "c == ' '  or c == '\t' \n printf(#defi), putchar(c)" ];
	    defi -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'m' or c == 'o'...'z' \n printf(#defi), nuevaPalabra(c)" ];
	    defi -> caracterEspecial [label = " EOC \n printf(#defi), putchar(c)" ];

	    defin -> define [label = "c == 'e' " ];
	    defin -> aperturaComillasSimples [label = "c == ' \n printf(#defin), putchar(c)" ];
	    defin -> aperturaComillasDobles [label = "c == \" \n printf(#defin), putchar(c)" ];
	    defin -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#defin), putchar(c)" ];
	    defin -> posibleComentario [label = "c == / \n printf(#defin), putchar(c)" ];
	    defin -> espacio [label = "c == ' '  or c == '\t' \n printf(#defin), putchar(c)" ];
	    defin -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'d' or c == 'f'...'z' \n printf(#defin), nuevaPalabra(c)" ];
	    defin -> caracterEspecial [label = " EOC \n printf(#defin), putchar(c)" ];

	    define -> defineEspacio [label = "c == ' '  or c == '\\t' "];
	    define -> aperturaComillasSimples [label = "c == ' \n printf(#define), putchar(c)" ];
	    define -> aperturaComillasDobles [label = "c == \" \n printf(#define), putchar(c)" ];
	    define -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#define), putchar(c)" ];
	    define -> posibleComentario [label = "c == / \n printf(#define), putchar(c)" ];
	    define -> enPalabra [label = "c == '_' or  c == 'A'...'Z' or c == 'a'...'d' or c == 'f'...'z' \n printf(#define), nuevaPalabra(c)" ];
	    define -> caracterEspecial [label = " EOC \n printf(#define), putchar(c)" ];

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
	    u -> aperturaComillasSimples [label = "c == \' \n printf(#u), putchar(c)" ];
	    u -> aperturaComillasDobles [label = "c == \" \n printf(#u), putchar(c)" ];
	    u -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#u), putchar(c)" ];
	    u -> posibleComentario [label = "c == / \n printf(#u), putchar(c)" ];
	    u -> espacio [label = "c == ' ' or c == '\\t' \n printf(#u), putchar(c)" ];
	    u -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'m' or 'o'...'z' \n printf(#u), nuevaPalabra(c)" ];
	    u -> caracterEspecial [label = " EOC \n printf(#u), putchar(c)" ];

	    un -> und [label = "c == 'd' " ];
	    un -> aperturaComillasSimples [label = "c == \' \n printf(#un), putchar(c)" ];
	    un -> aperturaComillasDobles [label = "c == \" \n printf(#un), putchar(c)" ];
	    un -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#un), putchar(c)" ];
	    un -> posibleComentario [label = "c == / \n printf(#un), putchar(c)" ];
	    un -> espacio [label = "c == ' ' or c == '\\t' \n printf(#un), putchar(c)" ];
	    un -> enPalabra [label = "c == '_' c == or 'A'...'Z' or c == 'a'...'c' or 'e'...'z' \n printf(#un), nuevaPalabra(c)" ];
	    un -> caracterEspecial [label = " EOC \n printf(#un), putchar(c)" ];

	    und -> unde [label = "c == 'e' " ];
	    und -> aperturaComillasSimples [label = "c == \' \n printf(#und), putchar(c)" ];
	    und -> aperturaComillasDobles [label = "c == \" \n printf(#und), putchar(c)" ];
	    und -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#und), putchar(c)" ];
	    und -> posibleComentario [label = "c == / \n printf(#und), putchar(c)" ];
	    und -> espacio [label = "c == ' ' or c == '\\t' \n printf(#und), putchar(c)" ];
	    und -> enPalabra [label = "c == '_' c == or 'A'...'Z' or c == 'a'...'d' or 'f'...'z' \n printf(#und), nuevaPalabra(c)" ];
	    und -> caracterEspecial [label = " EOC \n printf(#und), putchar(c)" ];

	    unde -> esUndef [label = "c == 'f' " ];
	    unde -> aperturaComillasSimples [label = "c == \' \n printf(#unde), putchar(c)" ];
	    unde -> aperturaComillasDobles [label = "c == \" \n printf(#unde), putchar(c)" ];
	    unde -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#unde), putchar(c)" ];
	    unde -> posibleComentario [label = "c == / \n printf(#unde), putchar(c)" ];
	    unde -> espacio [label = "c == ' ' or c == '\\t' \n printf(#unde), putchar(c)" ];
	    unde -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'e' or 'g'...'z' \n printf(#unde), nuevaPalabra(c)" ];
	    unde -> caracterEspecial [label = " EOC \n printf(#unde), putchar(c)" ];

	    esUndef -> undefEspacio [label = "c == ' ' or c == '\\t' " ];
	    esUndef -> aperturaComillasSimples [label = "c == \' \n printf(#undef), putchar(c)" ];
	    esUndef -> aperturaComillasDobles [label = "c == \" \n printf(#undef), putchar(c)" ];
	    esUndef -> "*comienzoDeLinea" [label = "c == '\\n' \n printf(#undef), putchar(c)" ];
	    esUndef -> posibleComentario [label = "c == / \n printf(#undef), putchar(c)" ];
	    esUndef -> enPalabra [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n printf(#undef), nuevaPalabra(c)" ];
	    esUndef -> caracterEspecial [label = " EOC  \n printf(#undef), putchar(c)" ];

	    undefEspacio -> undefIdentificador [label = "c == '_' or c =='A'...'Z' or c =='a'...'z' \n nuevoIdentificador(c)" ];
	    undefEspacio -> undefEspacio [label = "c == ' ' or c == '\\t' " ];
	    undefEspacio -> identificadorInvalido [label = " EOC " ];

	    undefIdentificador -> undefIdentificador [label = "c == '_' or c == 'A'...'Z' or c == 'a'...'z' or '0'...'9' \n nuevoCaracterIdentificador(c)" ];
	    undefIdentificador -> "*comienzoDeLinea" [label = "c == '\\n \n undef(identificador) " ];
	    undefIdentificador -> identificadorInvalido [label = " EOC " ];

	}
		

![Preprocesador - DOT](https://user-images.githubusercontent.com/82005945/132162623-ee7bf7d0-869b-4789-a261-a07a6fa0f9af.png)
