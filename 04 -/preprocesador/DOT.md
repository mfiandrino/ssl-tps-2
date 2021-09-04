Estamos utilizando un gráfico general y 3 separados para mostrar los estados de DEFINE, UNDEF e INCLUDE		

GRAFICO GENERAL:	

	digraph G {	

		"*COMIENZO_DE_LINEA" [shape=box];	
		rankdir = LR;	
	
		subgraph cluster_0 {	
			style=filled;	
			color=lightgrey;	
			DEFINE;	
		}	
		
	  	subgraph cluster_1 {	
			style=filled;	
			color=lightgrey;	
			UNDEF;	
  		}	
		
	    	subgraph cluster_2 {	
    		style=filled;	
			color=lightgrey;	
    		INCLUDE;	
		}	
		
	    	subgraph cluster_3 {	
    		style=filled;	
			color=lightgrey;	
    		COMENTARIOS;	
		}	
		
		subgraph cluster_4 {
		        style = filled;
		        color=lightgrey;
		        COMILLAS_SIMPLES;
		}

		subgraph cluster_5 {
		        style = filled;
		        color=lightgrey;
		        COMILLAS_DOBLES;
		}
		
		"*COMIENZO_DE_LINEA" -> POSIBLE_INCLUDE_DEFINE_UNDEF [label = " c == '#'"];
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	POSIBLE_INCLUDE_DEFINE_UNDEF -> CARACTER_COMUN [label = " EOC "];
	    	CARACTER_COMUN -> POSIBLE_COMENTARIO [label = " c == '/'"];
	    	CARACTER_COMUN -> CARACTER_COMUN [style = "invis"];
	    	CARACTER_COMUN -> CARACTER_COMUN [label = " EOC "];
	    	CARACTER_COMUN -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	"*COMIENZO_DE_LINEA" -> CARACTER_COMUN [label = " EOC "];
	    	"*COMIENZO_DE_LINEA" -> "*COMIENZO_DE_LINEA" [style = "invis"];
	    	"*COMIENZO_DE_LINEA" -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    
		//DEFINE
	    	POSIBLE_INCLUDE_DEFINE_UNDEF -> DEFINE [label = " c == 'd' "];
		DEFINE -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	DEFINE -> CARACTER_COMUN;
		
	    	//UNDEF
	    	POSIBLE_INCLUDE_DEFINE_UNDEF -> UNDEF [label = " c == 'u' "];
		UNDEF -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	UNDEF -> CARACTER_COMUN;
	    
	    	//INCLUDE
	    	POSIBLE_INCLUDE_DEFINE_UNDEF -> INCLUDE [label = " c == 'i' "];
	    	INCLUDE -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	INCLUDE -> CARACTER_COMUN;
	    	INCLUDE -> COMILLAS_SIMPLES [label = "c == '"];
	    	INCLUDE -> COMILLAS_DOBLES [label = " c == \" "];
	    
	    	//COMENTARIOS
	    	"*COMIENZO_DE_LINEA" -> POSIBLE_COMENTARIO [label = " c == '/'"];
	    	POSIBLE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	POSIBLE_COMENTARIO -> CARACTER_COMUN [label = " EOC "];
	    	POSIBLE_COMENTARIO -> COMENTARIOS [label = " c == '/' or c == '*'"];
	    	COMENTARIOS -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
	    	COMENTARIOS -> CARACTER_COMUN [label = " EOC "];
	    	COMENTARIOS -> POSIBLE_COMENTARIO [label = " c == '/' "];
	    	COMENTARIOS -> COMILLAS [label = " c == \" or c == ' "];
	    
	    
	    	//COMILLAS_SIMPLES
		"*COMIENZO_DE_LINEA" -> COMILLAS_SIMPLES [label = "c == '"];
	    	CARACTER_COMUN -> COMILLAS_SIMPLES [label = "  c == '"];
	    	COMILLAS_SIMPLES -> "*COMIENZO_DE_LINEA" [label = " c == '\\n' "];
	    	COMILLAS_SIMPLES -> CARACTER_COMUN [label = " EOC "];
	    	COMILLAS_SIMPLES -> COMILLAS_SIMPLES [label = " c == ' "];
	    	COMILLAS_SIMPLES -> COMILLAS_DOBLES [label = " c == \" "];
	    	COMILLAS_SIMPLES -> POSIBLE_COMENTARIO [label = " c == '/' "];
	    
	    	//COMILLAS_DOBLES
		"*COMIENZO_DE_LINEA" -> COMILLAS_DOBLES [label = " c == \" "];
	    	CARACTER_COMUN -> COMILLAS_DOBLES [label = " c == \" "];
	    	COMILLAS_DOBLES -> "*COMIENZO_DE_LINEA" [label = " c == '\\n' "];
	    	COMILLAS_DOBLES -> CARACTER_COMUN [label = " EOC "];
	    	COMILLAS_DOBLES -> COMILLAS_DOBLES [label = " c == \" "];
	    	COMILLAS_DOBLES -> COMILLAS_SIMPLES [label = " c == ' "];
	    	COMILLAS_DOBLES -> POSIBLE_COMENTARIO [label = " c == '/' "];
	    
	}

![GENERAL](https://user-images.githubusercontent.com/82005945/131953050-2d5a71a6-c45d-4c32-a68f-ed918e325293.png)


DEFINE:		

	digraph DEFINE {	
        	//rankdir = LR;
        	//concentrate=true;
        
		subgraph cluster_0 {	
    		style=filled;	
		    	color=lightgrey;	
    		node [style=filled,color=white];	
    		"#d" -> "#de" [label= "c == 'e' "];	
		    	"#de"-> "#def"  [label= "c == 'f'"];
			"#def" -> "#defi" [label= "c == 'i'"];	
		    	"#defi" -> "#defin" [label= "c == 'n'"];	
			"#defin" -> "#define" [label= "c == 'e'"];	
		    	"#define" -> "#define_" [label= "c == ' '"];	
			"#define_" -> "#define_identificador" [label= "c == '_' or c == letra"];
			"#define_identificador" -> "#define_identificador" [label= " c == '_' or c == letra or c == numero "];
			"#define_identificador" -> "#define_identificador_" [label= "c == ' '"];		
			"#define_identificador_"-> "#define_identificador_texto" [label= " EOC "];
			"#define_identificador_texto"-> "#define_identificador_texto" [label= " EOC "];
    		label = "DEFINE";		
		}		

		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#d" [label = " c == 'd'"];		
	
		"#d" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#de" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#def" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#defi" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#defin" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#define" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		//{"#d","#de","#def","#defi","#defin","#define","#define_identificador_texto"} -> "*COMIENZO_DE_LINEA" [label= "c == '/n' "];		

		"#d" -> CARACTER_COMUN [label= " EOC"];		
		"#de" -> CARACTER_COMUN [label= " EOC"];		
		"#def" -> CARACTER_COMUN [label= " EOC"];		
		"#defi" -> CARACTER_COMUN [label= " EOC"];		
		"#defin" -> CARACTER_COMUN [label= " EOC"];		
		"#define" -> CARACTER_COMUN [label= " EOC"];		
		
		//{"#d","#de","#def","#defi","#defin","#define"} -> CARACTER_COMUN [label= " EOC"];		

    	"#define_" -> IDENTIFICADOR_INVÁLIDO [label= " EOC "];
    	"#define_identificador" -> IDENTIFICADOR_INVÁLIDO [label= " EOC "];
    	"#define_identificador_" -> TEXTO_DEFINE_INVÁLIDO [label= " c == '\\n' "];
    
    	"#define_identificador_texto" -> "*COMIENZO_DE_LINEA" [label="c == '\\n' \n ATENDER DEFINE"];

	}	

![DEFINE](https://user-images.githubusercontent.com/82005945/131953084-aa1d6eb6-bd15-4913-92d4-5e4780b76828.png)

		
UNDEF:	
	
	digraph UNDEF {		
		//rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
		    	style=filled;		
	    		color=lightgrey;		
    		node [style=filled,color=white];		
  			"#u" -> "#un" [label= "c == 'n'"];		
			"#un"-> "#und"  [label= "c == 'd'"];		
    		"#und" -> "#unde" [label= "c == 'e'"];		
			"#unde" -> "#undef" [label= "c == 'f'"];		
    		"#undef" -> "#undef_" [label= "c == ' '"];		
			"#undef_" -> "#undef_identificador" [label= "c == '_' or c == letra"];
			"#undef_identificador" -> "#undef_identificador" [label= " c == '_' or c == letra or c == numero "];
    		label = "UNDEF";		
  		}		
  		
		
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#u" [label = " c == 'u'"];		
		
		"#u" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#un" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#und" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#unde" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#undef" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];			
		//{"#u","#un","#und","#unde","#undef"} -> "*COMIENZO_DE_LINEA" [label= "c == '/n' "];		
		
		"#u" -> CARACTER_COMUN [label= " EOC"];		
		"#un" -> CARACTER_COMUN [label= " EOC"];		
		"#und" -> CARACTER_COMUN [label= " EOC"];		
		"#unde" -> CARACTER_COMUN [label= " EOC"];		
		"#undef" -> CARACTER_COMUN [label= " EOC"];		
		//{"#u","#un","#und","#unde","#undef"} -> CARACTER_COMUN [label= " EOC"];			
	
	    	"#undef_" -> IDENTIFICADOR_INVÁLIDO [label= " EOC "];
        	"#undef_identificador" -> IDENTIFICADOR_INVÁLIDO [label= " EOC "];
	
		"#undef_identificador" -> "*COMIENZO_DE_LINEA" [label="c == '\\n' \n ATENDER UNDEF"];
	}	

![UNDEF](https://user-images.githubusercontent.com/82005945/131953106-b440b5e0-c465-4c0a-b9f2-e83ff61d1a98.png)


INCLUDE:			  
	
	digraph INCLUDE {		
		//rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
    		style=filled;		
        		color=lightgrey;		
	        	node [style=filled,color=white];		
	    		"#i" -> "#in" [label= " c == 'n'"];		
		        "#in"-> "#inc"  [label= " c == 'c'"];		
			"#inc" -> "#incl" [label= " c == 'l'"];		
	        	"#incl" -> "#inclu" [label= " c == 'u'"];		
		        "#inclu" -> "#includ" [label= " c == 'd'"];			
			"#includ" -> "#include" [label= " c == 'e'"];		
        		"#include" -> "#include_" [label= " c == ' '"];	
        		"#include_" -> "#include_''" [label= " c == ''"];
        		"#include_''" -> "#include_''texto" [label= " EOC "];
        		"#include_''texto" -> "#include_''texto" [label= " EOC "];
        		"#include_''texto" -> "#include_''texto''" [label= " c == ''"];
    		label = "INCLUDE";		
    	}		
	
	
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#i" [label = " c == 'i'"];		
	
		"#i" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
    	"#in" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#inc" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#incl" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
	    	"#inclu" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
		"#includ" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
    	"#include" -> "*COMIENZO_DE_LINEA" [label="c == '\\n'"];		
    	//  {"#i","#in","#inc","#incl","#inclu","#includ","#include","#include_"} -> "*COMIENZO_DE_LINEA" [label= "c == '\\n' "];		
	
		"#i" -> CARACTER_COMUN [label= " EOC"];		
	    	"#in" -> CARACTER_COMUN [label= " EOC"];		
		"#inc" -> CARACTER_COMUN [label= " EOC"];		
	    	"#incl" -> CARACTER_COMUN [label= " EOC"];		
		"#inclu" -> CARACTER_COMUN [label= " EOC"];		
	    	"#includ" -> CARACTER_COMUN [label= " EOC"];		
		"#include" -> CARACTER_COMUN [label= " EOC"];		
   		// {"#i","#in","#inc","#incl","#inclu","#includ","#include","#include_"} -> CARACTER_COMUN [label= " EOC"];		
   		
   		"#include_" -> PATH_INVÁLIDO [label= " EOC "];
   		"#include_''" -> PATH_INVÁLIDO [label= " c == \\n or c == '' "];
   		"#include_''texto" -> PATH_INVÁLIDO [label= " c == \\n "];
	
	    	"#include_''texto''" -> "*COMIENZO_DE_LINEA" [label="c == '\\n' \n ATENDER INCLUDE"];
	    	"#include_''texto''" -> COMILLAS [label= " c == '' or c == ' \n ATENDER INCLUDE"];
	    	"#include_''texto''" -> POSIBLE_COMENTARIO [label= " c == '/' \n ATENDER INCLUDE"];
	    	"#include_''texto''" -> CARACTER_COMUN [label= " EOC \n ATENDER INCLUDE"];
	}	

![INCLUDE](https://user-images.githubusercontent.com/82005945/131953123-cd4293cc-60c4-4e73-ba40-6a09265fd45b.png)


COMENTARIOS:	
	
	digraph COMENTARIOS {
		//rankdir = LR;
    	
	
		subgraph cluster_0 {
			style=filled;
    		color=lightgrey;
	    		node [style=filled,color=white];
    		COMENTARIO_MULTILINEA -> POSIBLE_FIN_DE_COMENTARIO_MULTILINEA [label = " c == '*'"];
    		COMENTARIO_FIN_DE_LINEA;
    		POSIBLE_FIN_DE_COMENTARIO_MULTILINEA -> FIN_DE_COMENTARIO_MULTILINEA [label = " c == '/' \n putchar(' ');"];
  		    	POSIBLE_FIN_DE_COMENTARIO_MULTILINEA -> COMENTARIO_MULTILINEA [label = " EOC "];
  		    	POSIBLE_FIN_DE_COMENTARIO_MULTILINEA -> POSIBLE_FIN_DE_COMENTARIO_MULTILINEA [style = "invis"];
  		    	POSIBLE_FIN_DE_COMENTARIO_MULTILINEA -> POSIBLE_FIN_DE_COMENTARIO_MULTILINEA [label = " c == '*' "];
    		label = "COMENTARIOS";
  		}
		
		POSIBLE_COMENTARIO -> CARACTER_COMUN [label = "EOC"];
  		POSIBLE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
  		POSIBLE_COMENTARIO -> COMENTARIO_MULTILINEA [label = " c == '*'"];
  		POSIBLE_COMENTARIO -> COMENTARIO_FIN_DE_LINEA [label = " c == '/'"];
		POSIBLE_COMENTARIO -> APERTURA_COMILLAS_SIMPLES [label = " c == '\'' " ];
  		COMENTARIO_FIN_DE_LINEA -> "*COMIENZO_DE_LINEA" [label = " c == '\\n' \n putchar(' '); \n putchar(c);"];
  		
		
  		FIN_DE_COMENTARIO_MULTILINEA -> "*COMIENZO_DE_LINEA" [label = " c == '\\n'"];
  		FIN_DE_COMENTARIO_MULTILINEA -> POSIBLE_COMENTARIO [label = " c == '/'"];
		FIN_DE_COMENTARIO_MULTILINEA -> APERTURA_COMILLA_SIMPLE [label = " c == '\'' "]; 
  		FIN_DE_COMENTARIO_MULTILINEA -> CARACTER_COMUN [label = "EOC"];
  		
  		
  		COMENTARIO_MULTILINEA -> COMENTARIO_MULTILINEA [style = "invis"];
  		COMENTARIO_MULTILINEA -> COMENTARIO_MULTILINEA [label = "EOC"];
  		COMENTARIO_FIN_DE_LINEA -> COMENTARIO_FIN_DE_LINEA [style = "invis"];
  		COMENTARIO_FIN_DE_LINEA -> COMENTARIO_FIN_DE_LINEA [label = "EOC"];
  	  
	}

![COMENTARIOS](https://user-images.githubusercontent.com/82005945/131953144-015f2008-c8cf-43f6-97a4-9800268467a2.png)


COMILLAS SIMPLES:

	digraph COMILLAS_SIMPLES {		
		//rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
    		style=filled;		
        		color=lightgrey;		
	        	node [style=filled,color=white];		
	        	APERTURA_COMILLAS_SIMPLES -> CIERRE_COMILLAS_SIMPLES [label= " c == ' "];		
		        APERTURA_COMILLAS_SIMPLES -> ENTRE_COMILLAS_SIMPLES  [label= " EOC "];		
			ENTRE_COMILLAS_SIMPLES -> CIERRE_COMILLAS_SIMPLES [label= " c == ' "];
			ENTRE_COMILLAS_SIMPLES -> ENTRE_COMILLAS_SIMPLES [style = "invis"];
			ENTRE_COMILLAS_SIMPLES -> ENTRE_COMILLAS_SIMPLES [label = " EOC "];
	        	CIERRE_COMILLAS_SIMPLES -> APERTURA_COMILLAS_SIMPLES [label= "  c == ' "];
    		label = "COMILLAS_SIMPLES";		
    	}		

	    
	    "*COMIENZO_DE_LINEA" -> APERTURA_COMILLAS_SIMPLES [label = " c == ' "];
	    CARACTER_COMUN -> APERTURA_COMILLAS_SIMPLES [label = " c == ' "];
	    INCLUDE -> APERTURA_COMILLAS_SIMPLES [label = " c == ' "];
	    CIERRE_COMILLAS_DOBLES -> APERTURA_COMILLAS_SIMPLES [label = " c == ' "];
	    CIERRE_COMILLAS_SIMPLES -> "*COMIENZO_DE_LINEA" [label = " c == '/n' "];
	    CIERRE_COMILLAS_SIMPLES -> CARACTER_COMUN [label = " EOC "];
	    CIERRE_COMILLAS_SIMPLES -> POSIBLE_COMENTARIO [label = " c == '/' "];
	    CIERRE_COMILLAS_SIMPLES -> APERTURA_COMILLAS_DOBLES [label= " c == \" "];
	
	}

![COMILLAS_SIMPLES](https://user-images.githubusercontent.com/82005945/131953172-6bb7c37c-0618-4a14-9507-8c887bc6b8cd.png)


COMILLAS DOBLES:

	digraph COMILLAS_DOBLES {		
		//rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
    		style=filled;		
        		color=lightgrey;		
	        	node [style=filled,color=white];		
	        	APERTURA_COMILLAS_DOBLES -> CIERRE_COMILLAS_DOBLES [label= " c == \" "];		
		        APERTURA_COMILLAS_DOBLES -> ENTRE_COMILLAS_DOBLES  [label= " EOC "];		
			ENTRE_COMILLAS_DOBLES -> CIERRE_COMILLAS_DOBLES [label= " c == \" "];
			ENTRE_COMILLAS_DOBLES -> ENTRE_COMILLAS_DOBLES [style = "invis"];
			ENTRE_COMILLAS_DOBLES -> ENTRE_COMILLAS_DOBLES [label = " EOC "];
	        	CIERRE_COMILLAS_DOBLES -> APERTURA_COMILLAS_DOBLES [label= "  c == \" "];
    		label = "COMILLAS_DOBLES";		
    	}		

	    
	    "*COMIENZO_DE_LINEA" -> APERTURA_COMILLAS_DOBLES [label = " c == \" "];
	    CARACTER_COMUN -> APERTURA_COMILLAS_DOBLES [label = " c == \" "];
	    INCLUDE -> APERTURA_COMILLAS_DOBLES [label = " c == \" "];
	    CIERRE_COMILLAS_SIMPLES -> APERTURA_COMILLAS_DOBLES [label = " c == \" "];
	    CIERRE_COMILLAS_DOBLES -> "*COMIENZO_DE_LINEA" [label = " c == '/n' "];
	    CIERRE_COMILLAS_DOBLES -> CARACTER_COMUN [label = " EOC "];
	    CIERRE_COMILLAS_DOBLES -> POSIBLE_COMENTARIO [label = " c == '/' "];
	    CIERRE_COMILLAS_DOBLES -> APERTURA_COMILLAS_SIMPLES [label= " c == ' "];
	
	}

![COMILLAS_DOBLES](https://user-images.githubusercontent.com/82005945/131953200-d1f6891f-0f2a-4d14-9741-f35151321424.png)

