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
		
		
		"*COMIENZO_DE_LINEA" -> POSIBLE_INCLUDE_DEFINE_UNDEF [label = " c = '#'"];	
		"*COMIENZO_DE_LINEA" -> POSIBLE_COMENTARIO [label = " c = '/'"];	
		"*COMIENZO_DE_LINEA" -> CARACTER_COMUN [label = "EOC"];	
		"*COMIENZO_DE_LINEA" -> "*COMIENZO_DE_LINEA" [style = "invis"];	 
		"*COMIENZO_DE_LINEA" -> "*COMIENZO_DE_LINEA" [style = "invis"]; 	
		"*COMIENZO_DE_LINEA" -> "*COMIENZO_DE_LINEA" [label = " c = '/n'"]; 	
		CARACTER_COMUN -> CARACTER_COMUN [style ="invis"];		
		CARACTER_COMUN -> CARACTER_COMUN [label = "EOC"];		
		CARACTER_COMUN -> POSIBLE_COMENTARIO [label = " c = '/'"];		
		CARACTER_COMUN -> "*COMIENZO_DE_LINEA" [label = " c = '/n'"];		
	
		POSIBLE_INCLUDE_DEFINE_UNDEF -> DEFINE;		
		POSIBLE_INCLUDE_DEFINE_UNDEF -> UNDEF;		
		POSIBLE_INCLUDE_DEFINE_UNDEF -> INCLUDE;		
		DEFINE -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		
		UNDEF -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		
		INCLUDE -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		
		DEFINE -> CARACTER_COMUN [label= "EOC"];		
		UNDEF -> CARACTER_COMUN [label= "EOC"];		
		INCLUDE -> CARACTER_COMUN [label= "EOC"];		
		DEFINE -> ATENDER_DEFINE [label = "c = '/n \n ????"];		
		UNDEF -> ATENDER_UNDEF [label = "c = '/n \n ????"];		
		INCLUDE -> ATENDER_INCLUDE [label = "c = '/n \n ????"];		
	
		POSIBLE_COMENTARIO -> COMENTARIOS;		
		POSIBLE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = "c = '/n'"];		
		POSIBLE_COMENTARIO -> CARACTER_COMUN [label = "EOC"];		
		COMENTARIOS -> FIN_DE_COMENTARIO;
		FIN_DE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = " c = '/n'"];
		FIN_DE_COMENTARIO -> CARACTER_COMUN [label = "EOC"];
	
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "*COMIENZO_DE_LINEA" [label = "c = '/n'"];		
		POSIBLE_INCLUDE_DEFINE_UNDEF -> CARACTER_COMUN [label="EOC"];		
	
	
	}	


![general](https://user-images.githubusercontent.com/82005945/131566055-6da5baa2-ecb1-454f-9122-5a1650264b1b.png)


DEFINE:		

	digraph DEFINE {	
  
		subgraph cluster_0 {	
    		style=filled;	
		    	color=lightgrey;	
    		node [style=filled,color=white];	
    		"#d" -> "#de" [label= "c = 'e' "];	
		    	"#de"-> "#def"  [label= "c = 'f'"];
			"#def" -> "#defi" [label= "c = 'i'"];	
		    	"#defi" -> "#defin" [label= "c = 'n'"];	
			"#defin" -> "#define" [label= "c = 'e'"];	
		    	"#define" -> "#define_" [label= "c = ' '"];	
			"#define_" -> "#define_identificador" [label= "c = '???'"];		
			"#define_identificador" -> "#define_identificador_" [label= "c = ' '"];		
			"#define_identificador_"-> "#define_identificador_texto" [label= "c = '???'"];		
    		label = "DEFINE";		
		}		

		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#d" [label = " c = 'd'"];		
	
		"#d" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#de" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#def" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#defi" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#defin" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#define" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#define_" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#define_identificador" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#define_identificador_" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#define_identificador_texto" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		// {"#d","#de","#def","#defi","#defin","#define","#define_","#define_identificador","#define_identificador_","#define_identificador_texto"} -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		

		"#d" -> CARACTER_COMUN [label= " EOC"];		
		"#de" -> CARACTER_COMUN [label= " EOC"];		
		"#def" -> CARACTER_COMUN [label= " EOC"];		
		"#defi" -> CARACTER_COMUN [label= " EOC"];		
		"#defin" -> CARACTER_COMUN [label= " EOC"];		
		"#define" -> CARACTER_COMUN [label= " EOC"];		
		"#define_" -> CARACTER_COMUN [label= " EOC"];		
		"#define_identificador" -> CARACTER_COMUN [label= " EOC"];		
		"#define_identificador_" -> CARACTER_COMUN [label= " EOC"];		
		"#define_identificador_texto" -> CARACTER_COMUN [label= " EOC"];		

		//{"#d","#de","#def","#defi","#defin","#define","#define_","#define_identificador","#define_identificador_","#define_identificador_texto"} -> CARACTER_COMUN [label= " EOC"];		

		"#define_identificador_texto" -> ATENDER_DEFINE [label = "c = '/n' \n ????"]; 		

	}	
		
![DEFINE](https://user-images.githubusercontent.com/82005945/131562228-b512a26c-828c-438e-a88d-4c3bd76d4214.png)
		
	
UNDEF:	
	
	digraph UNDEF {		
		rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
		    	style=filled;		
	    		color=lightgrey;		
    		node [style=filled,color=white];		
  			"#u" -> "#un" [label= "c = 'n'"];		
			"#un"-> "#und"  [label= "c = 'd'"];		
    		"#und" -> "#unde" [label= "c = 'e'"];		
			"#unde" -> "#undef" [label= "c = 'f'"];		
    		"#undef" -> "#undef_" [label= "c = ' '"];		
			"#undef_" -> "#undef_identificador" [label= "c = '???'"];		
    		"#undef_identificador" -> "#undef_identificador_" [label= "c = ' '"];		
			"#undef_identificador_" -> "#undef_identificador_?" [label= "c = '???'"];		
    		label = "UNDEF";		
  		}		
		
		
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#u" [label = " c = 'u'"];		
		
		"#u" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#un" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#und" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#unde" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#undef" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];	
		"#undef_" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#undef_identificador" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#undef_identificador_" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#undef_identificador_?" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		//{"#u","#un","#und","#unde","#undef","#undef_","#undef_identificador","#undef_identificador_","#undefine_identificador_?"} -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		
		
		"#u" -> CARACTER_COMUN [label= " EOC"];		
		"#un" -> CARACTER_COMUN [label= " EOC"];		
		"#und" -> CARACTER_COMUN [label= " EOC"];		
		"#unde" -> CARACTER_COMUN [label= " EOC"];		
		"#undef" -> CARACTER_COMUN [label= " EOC"];		
		"#undef_" -> CARACTER_COMUN [label= " EOC"];		
		"#undef_identificador" -> CARACTER_COMUN [label= " EOC"];		
		"#undef_identificador_" -> CARACTER_COMUN [label= " EOC"];		
		"#undef_identificador_?" -> CARACTER_COMUN [label= " EOC"];		
		//{"#u","#un","#und","#unde","#undef","#undef_","#undef_identificador","#undef_identificador_","#undefine_identificador_?"} -> CARACTER_COMUN [label= " EOC"];			
	
		"#undef_identificador_?" -> ATENDER_UNDEF [label = "c = '/n' \n ????"]; 	
	
	}		
	
![UNDEF](https://user-images.githubusercontent.com/82005945/131562327-78630dd0-02ad-4ab2-8eb9-8b8c58bd3378.png)
	
	
INCLUDE:			  
	
	digraph INCLUDE {		
		rankdir = LR;		
		//concentrate=true;		
	
		subgraph cluster_0 {		
    		style=filled;		
        		color=lightgrey;		
	        	node [style=filled,color=white];		
	    		"#i" -> "#in" [label= " c = 'n'"];		
		        "#in"-> "#inc"  [label= " c = 'c'"];		
			"#inc" -> "#incl" [label= " c = 'l'"];		
	        	"#incl" -> "#inclu" [label= " c = 'u'"];		
		        "#inclu" -> "#includ" [label= " c = 'd'"];			
			"#includ" -> "#include" [label= " c = 'e'"];		
        		"#include" -> "#include_" [label= " c = ' '"];		
    		label = "INCLUDE";		
    	}		
	
	
		POSIBLE_INCLUDE_DEFINE_UNDEF -> "#i" [label = " c = 'i'"];		
	
		"#i" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
    	"#in" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#inc" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#incl" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
	    	"#inclu" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#includ" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
    	"#include" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
		"#include_" -> "*COMIENZO_DE_LINEA" [label="c = '/n'"];		
    	//  {"#i","#in","#inc","#incl","#inclu","#includ","#include","#include_"} -> "*COMIENZO_DE_LINEA" [label= "c = '/n' "];		
	
		"#i" -> CARACTER_COMUN [label= " EOC"];		
	    	"#in" -> CARACTER_COMUN [label= " EOC"];		
		"#inc" -> CARACTER_COMUN [label= " EOC"];		
	    	"#incl" -> CARACTER_COMUN [label= " EOC"];		
		"#inclu" -> CARACTER_COMUN [label= " EOC"];		
	    	"#includ" -> CARACTER_COMUN [label= " EOC"];		
		"#include" -> CARACTER_COMUN [label= " EOC"];		
	    	"#include_" -> CARACTER_COMUN [label= " EOC"];		
   		// {"#i","#in","#inc","#incl","#inclu","#includ","#include","#include_"} -> CARACTER_COMUN [label= " EOC"];		
	
		"#include_" -> ATENDER_INCLUDE [label = "c = '/n' \n ????"]; 		
	
	}		
		
![INCLUDE](https://user-images.githubusercontent.com/82005945/131562351-b6ed93ad-a95b-4bd9-b72c-aa8a5d2cffc6.png)	
		
COMENTARIOS:	
	
	digraph COMENTARIOS {
		rankdir = LR;
    	
	
		subgraph cluster_0 {
			style=filled;
    		color=lightgrey;
	    		node [style=filled,color=white];
    		COMENTARIO_MULTILINEA -> POSIBLE_FIN_DE_COMENTARIO [label = " c = '*'"];
    		COMENTARIO_FIN_DE_LINEA;
    		label = "COMENTARIOS";
  		}
		
  		POSIBLE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = " c = '/n'"];
  		POSIBLE_COMENTARIO -> CARACTER_COMUN [label = "EOC"];
  		POSIBLE_COMENTARIO -> COMENTARIO_MULTILINEA [label = " c = '*'"];
  		POSIBLE_COMENTARIO -> COMENTARIO_FIN_DE_LINEA [label = " c = '/'"];
  		COMENTARIO_FIN_DE_LINEA -> FIN_DE_COMENTARIO [label = " c = '/n' \n putchar(' '); \n putchar(c);"];
  		POSIBLE_FIN_DE_COMENTARIO -> FIN_DE_COMENTARIO [label = " c = '/' \n putchar(' ');"];
  		POSIBLE_FIN_DE_COMENTARIO -> COMENTARIO_MULTILINEA [label = " EOC "];
		
  		FIN_DE_COMENTARIO -> "*COMIENZO_DE_LINEA" [label = " c = '/n'"];
  		FIN_DE_COMENTARIO -> POSIBLE_COMENTARIO [label = " c = '/'"];
  		FIN_DE_COMENTARIO -> CARACTER_COMUN [label = "EOC"];
  		
  		
  		COMENTARIO_MULTILINEA -> COMENTARIO_MULTILINEA [style = "invis"];
  		COMENTARIO_MULTILINEA -> COMENTARIO_MULTILINEA [label = "EOC"];
  		COMENTARIO_FIN_DE_LINEA -> COMENTARIO_FIN_DE_LINEA [style = "invis"];
  		COMENTARIO_FIN_DE_LINEA -> COMENTARIO_FIN_DE_LINEA [label = "EOC"];
  	  
	}
	
![COMENTARIOS](https://user-images.githubusercontent.com/82005945/131565367-96812e50-d0c2-42f1-a90c-13f0713c2d66.png)
	
	
