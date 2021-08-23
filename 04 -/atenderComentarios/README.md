
 # Maquina de Estados
 a) Descripcion maquina de estados en lenguaje DOT	
 
 Grafico resultante: 	
 
 ![atenderComentarios en dot](https://user-images.githubusercontent.com/82005945/130470691-b8ed82a5-8ed9-408c-97ba-54d84bb6d5db.png)

 
 b) Formalizacion máquina de estados como una n-upla
    
  	M = {Q, E, T, qo, F}
  
 	Q = {OUT,COMMENT1, COMMENT2}
	
	E = {putchar(prevC) | prevC = c, prevc = '\n' |putchar(' ')| putchar(prevC),prevC = '*' | c = '/' | putchar(' '), prevC = '/' | c = '/', prevC = '/' | c = '*', prevC = c, 	  prevC = c }
	
	T = {OUT => putchar(prevC) | prevC = c => OUT, OUT => prevC = '/' | c = '/' => COMMENT1,OUT =>  prevC = '/' | c = '*' => COMMENT2, COMMENT1 => prevC = c => COMMENT1, 		COMMENT1 => prevc = '\n' | putchar(' ')| putchar(prevC) => OUT, COMMENT2 => prevC = c => COMMENT2, COMMENT2 => prevC = '*' | c = '/' | putchar(' ') => OUT  }
	
	qo = OUT
	
	F = {OUT,COMMENT1, COMMENT2}
	

Tabla de transiciones

![image](https://user-images.githubusercontent.com/82044738/130380418-8849f5ab-ad31-4ebd-b67e-a9e169b66572.png)



