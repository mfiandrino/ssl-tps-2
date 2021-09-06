Estamos utilizando un gráfico general y 3 separados para mostrar los estados de DEFINE, UNDEF e INCLUDE		

digraph CARACTER_COMUN {		
		//rankdir = LR;		
		//concentrate=true;		
	

comienzoDeLinea [shape=box];
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
            textoUndefInvalido;
    		label = "UNDEF";		
    	}
	
	    comentarioFinDeLinea -> comienzoDeLinea [label = " c == '\\n' \n putchar(' '), putchar(c)"];
	    comentarioFinDeLinea -> comentarioFinDeLinea [label = " EOC "];
	    
	    comentarioMultilinea -> posibleFinDeComentarioMultilinea [label = " c == '*' "];
	    comentarioMultilinea -> comentarioMultilinea [label = " EOC "];
	    
	    posibleFinDeComentarioMultilinea -> posibleFinDeComentarioMultilinea [label = " c == '*' "];
	    posibleFinDeComentarioMultilinea -> FinDeComentarioMultilinea [label = " c == '/' \n putchar(' ')"];
	    posibleFinDeComentarioMultilinea -> comentarioMultilinea [label = " EOC "];
	    
	    FinDeComentarioMultilinea -> posibleComentario [label = " c == '/' "];
	    FinDeComentarioMultilinea -> aperturaComillasSimples [label = " c == ' \n putchar(c)"];
	    FinDeComentarioMultilinea -> aperturaComillasDobles [label = " c == '' \n putchar(c)"];
	    FinDeComentarioMultilinea -> comienzoDeLinea [label = " c == '\\n' \n putchar(c) "];
	    FinDeComentarioMultilinea -> espacio [label = " c == ' ' or c == '\\t' \n putchar(c) "];
	    FinDeComentarioMultilinea -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n nuevaPalabra(c) "];
	    FinDeComentarioMultilinea -> caracterEspecial [label = " EOC \n putchar(c)"];
	    
	    posibleComentario -> comienzoDeLinea [label = " c == '\\n' \n putchar(/), putchar(c)"];
	    posibleComentario -> comentarioFinDeLinea [label = " c == '/' "];
	    posibleComentario -> aperturaComillasSimples [label = " c == ' \n putchar(/), putchar(c)"];
	    posibleComentario -> aperturaComillasDobles [label = " c == '' \n putchar(/), putchar(c) "];
	    posibleComentario -> comentarioMultilinea [label = " c == '*' "];
	    posibleComentario -> espacio [label = " c == ' ' or c == '\\t' \n putchar(/), putchar(c) "];
	    posibleComentario -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' \n putchar(/), nuevaPalabra(c)"];
	    posibleComentario -> caracterEspecial [label = " EOC \n putchar(/), putchar(c)"];
	    
	    enPalabra -> comienzoDeLinea [label = " c == '\\n' "];
	    enPalabra -> aperturaComillasSimples [label = " c == ' "];
        enPalabra -> aperturaComillasDobles [label = " c == \" "];
        enPalabra -> posibleComentario [label = " c == '/' "];
        enPalabra -> espacio [label = " c == ' ' or c == '\\t' "];
        enPalabra -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        enPalabra -> caracterEspecial [label = " EOC "];
        
        espacio -> comienzoDeLinea [label = " c == '\\n' "];
	    espacio -> aperturaComillasSimples [label = " c == ' "];
        espacio -> aperturaComillasDobles [label = " c == \" "];
        espacio -> posibleComentario [label = " c == '/' "];
        espacio -> espacio [label = " c == ' ' or c == '\\t' "];
        espacio -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        espacio -> caracterEspecial [label = " EOC "];
        
        caracterEspecial -> comienzoDeLinea [label = " c == '\\n' "];
	    caracterEspecial -> aperturaComillasSimples [label = " c == ' "];
        caracterEspecial -> aperturaComillasDobles [label = " c == \" "];
        caracterEspecial -> posibleComentario [label = " c == '/' "];
        caracterEspecial -> espacio [label = " c == ' ' or c == '\\t' "];
        caracterEspecial -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        caracterEspecial -> caracterEspecial [label = " EOC "];
        
        comienzoDeLinea -> comienzoDeLinea [label = " c == '\\n' "];
	    comienzoDeLinea -> aperturaComillasSimples [label = " c == ' "];
        comienzoDeLinea -> aperturaComillasDobles [label = " c == \" "];
        comienzoDeLinea -> posibleComentario [label = " c == '/' "];
        comienzoDeLinea -> espacio [label = " c == ' ' or c == '\\t' "];
        comienzoDeLinea -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        comienzoDeLinea -> posibleIncludeDefineUndef [label = " c == '#' "];
        comienzoDeLinea -> caracterEspecial [label = " EOC "];
        
        aperturaComillasSimples -> cierreComillasSimples [label = " c == ' "];
        aperturaComillasSimples -> entreComillasSimples [label = " EOC "];
        
        entreComillasSimples -> cierreComillasSimples [label = " c == ' "];
        entreComillasSimples -> entreComillasSimples [label = " EOC "];
        
        cierreComillasSimples -> comienzoDeLinea [label = " c == '\\n' "];
	    cierreComillasSimples -> aperturaComillasSimples [label = " c == ' "];
        cierreComillasSimples -> aperturaComillasDobles [label = " c == \" "];
        cierreComillasSimples -> posibleComentario [label = " c == '/' "];
        cierreComillasSimples -> espacio [label = " c == ' ' or c == '\\t' "];
        cierreComillasSimples -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        cierreComillasSimples -> caracterEspecial [label = " EOC "];
        
        aperturaComillasDobles -> cierreComillasDobles [label = " c == ' "];
        aperturaComillasDobles -> entreComillasDobles [label = " EOC "];
        
        entreComillasDobles -> cierreComillasDobles [label = " c == ' "];
        entreComillasDobles -> entreComillasDobles [label = " EOC "];
        
        cierreComillasDobles -> comienzoDeLinea [label = " c == '\\n' "];
	    cierreComillasDobles -> aperturaComillasSimples [label = " c == ' "];
        cierreComillasDobles -> aperturaComillasDobles [label = " c == \" "];
        cierreComillasDobles -> posibleComentario [label = " c == '/' "];
        cierreComillasDobles -> espacio [label = " c == ' ' or c == '\\t' "];
        cierreComillasDobles -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        cierreComillasDobles -> caracterEspecial [label = " EOC "];
        
        posibleIncludeDefineUndef -> d [label = " c == 'd' "];
	    posibleIncludeDefineUndef -> u [label = " c == 'u' "];
        posibleIncludeDefineUndef -> aperturaComillasSimples [label = " c == ' "];
        posibleIncludeDefineUndef -> aperturaComillasDobles [label = " c == \" "];
        posibleIncludeDefineUndef -> comienzoDeLinea [label = " c == '\\n' "];
        posibleIncludeDefineUndef -> posibleComentario [label = " c == '/' "];
        posibleIncludeDefineUndef -> espacio [label = " c == ' ' or c == '\\t' "];
        posibleIncludeDefineUndef -> enPalabra [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        posibleIncludeDefineUndef -> caracterEspecial [label = " EOC "];
        
        d -> de [label = "c == 'e' " ];
        d -> aperturaComillasSimples [label = "c == ' , printf(#d), putchar(c)" ];
        d -> aperturaComillasDobles [label = "c == '' , printf(#d), putchar(c)" ];
        d -> comienzoDeLinea [label = "c == '\n' , printf(#d), putchar(c)" ];
        d -> posibleComentario [label = "c == / , printf(#d), putchar(c)" ];
        d -> espacio [label = "c == ' ' or c == '\t' , printf(#d), putchar(c)" ];
        d -> enPalabra [label = "c =='' or 'A'...'Z' or 'a'...'d' or 'f'...'z' , printf(#d), nuevaPalabra(c)" ];
        d -> caracterEspecial [label = " EOC , printf(#d), putchar(c)" ];
        
        de -> def [label = "c == 'f'" ];
        de -> aperturaComillasSimples [label = "c == ' , printf(#de), putchar(c)" ];
        de -> aperturaComillasDobles [label = "c == '' , printf(#de), putchar(c)" ];
        de -> comienzoDeLinea [label = "c == '\n' , printf(#de), putchar(c)" ];
        de -> posibleComentario [label = "c == / , printf(#de), putchar(c)" ];
        de -> espacio [label = "c == ' ' or c == '\t' , printf(#de), putchar(c)" ];
        de -> enPalabra [label = "c =='' or  'A'...'Z' or  'a'...'e' or  'g'...'z' , printf(#de), nuevaPalabra(c)" ];
        de -> caracterEspecial [label = " EOC , printf(#de), putchar(c)" ];
        def -> defi [label = "c == 'i' " ];
        def -> aperturaComillasSimples [label = "c == ' , printf(#def), putchar(c)" ];
        def -> aperturaComillasDobles [label = "c == '' , printf(#def), putchar(c)" ];
        def -> comienzoDeLinea [label = "c == '\n' , printf(#def), putchar(c)" ];
        def -> posibleComentario [label = "c == / , printf(#def), putchar(c)" ];
        def -> espacio [label = "c == ' '  or c == '\t' , printf(#def), putchar(c)" ];
        def -> enPalabra [label = "c =='' or  'A'...'Z' or  'a'...'h' or  'j'...'z' , printf(#def), nuevaPalabra(c)" ];
        def -> caracterEspecial [label = " EOC , printf(#def), putchar(c)" ];
        
        defi -> defin [label = "c == 'n' " ];
        defi -> aperturaComillasSimples [label = "c == ' , printf(#defi), putchar(c)" ];
        defi -> aperturaComillasDobles [label = "c == '' , printf(#defi), putchar(c)" ];
        defi -> comienzoDeLinea [label = "c == '\n' , printf(#defi), putchar(c)" ];
        defi -> posibleComentario [label = "c == / , printf(#defi), putchar(c)" ];
        defi -> espacio [label = "c == ' '  or c == '\t' , printf(#defi), putchar(c)" ];
        defi -> enPalabra [label = "c =='' or  'A'...'Z' or  'a'...'m' or  'o'...'z' , printf(#defi), nuevaPalabra(c)" ];
        defi -> caracterEspecial [label = " EOC , printf(#defi), putchar(c)" ];
        defin -> define [label = "c == 'e' " ];
        defin -> aperturaComillasSimples [label = "c == ' , printf(#defin), putchar(c)" ];
        defin -> aperturaComillasDobles [label = "c == '' , printf(#defin), putchar(c)" ];
        defin -> comienzoDeLinea [label = "c == '\n' , printf(#defin), putchar(c)" ];
        defin -> posibleComentario [label = "c == / , printf(#defin), putchar(c)" ];
        defin -> espacio [label = "c == ' '  or c == '\t' , printf(#defin), putchar(c)" ];
        defin -> enPalabra [label = "c =='' or  'A'...'Z' or 'a'...'d' or  'f'...'z' , printf(#defin), nuevaPalabra(c)" ];
        defin -> caracterEspecial [label = " EOC , printf(#defin), putchar(c)" ];
        
        define -> defineEspacio [label = "c == ' '  or c == '\t' "];
        define -> aperturaComillasSimples [label = "c == ' , printf(#define), putchar(c)" ];
        define -> aperturaComillasDobles [label = "c == '' , printf(#define), putchar(c)" ];
        define -> comienzoDeLinea [label = "c == '\n' , printf(#define), putchar(c)" ];
        define -> posibleComentario [label = "c == / , printf(#define), putchar(c)" ];
        define -> enPalabra [label = "c =='' or  'A'...'Z' or  'a'...'d' or  'f'...'z' , printf(#define), nuevaPalabra(c)" ];
        define -> caracterEspecial [label = " EOC , printf(#define), putchar(c)" ];
                
        defineEspacio -> defineIdentificador [label = " c == '_' or c == 'A'...'Z' or c == 'a'...'z' "];
        defineEspacio -> defineEspacio [label = " c == ' ' or c == '\\t' "];
        defineEspacio -> identificadorInvalido [label = " EOC "];
        
        defineIdentificador -> defineIdentificador [label = "c =='_' or 'A'...'Z' or 'a'...'z' or '0'...'9', nuevoIdentificador(c)" ];
        defineIdentificador -> defineIdentificadorEspacio [label = "c == ' ' or c == '\t' " ];
        defineIdentificador -> identificadorInvalido [label = " EOC " ];

        defineIdentificadorEspacio -> defineIdentificadorEspacio [label = "c == ' ' or c == '\t' " ];
        defineIdentificadorEspacio -> textoDefineInvalido [label = "c == '\n' " ];
        defineIdentificadorEspacio -> defineTexto [label = " EOC " ];
        
        defineTexto -> comienzoDeLinea [label = "c == '\\n' " ];
        defineTexto -> defineTexto [label = " EOC " ];
	    
	}

	