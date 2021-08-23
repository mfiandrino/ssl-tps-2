
 # Maquina de Estados
 a) Descripcion maquina de estados en lenguaje DOT
 
 
 b) Formalizacion máquina de estados como una n-upla
    
  M = {Q, E, T, qo, F}
  
 	Q = {OUT,COMMENT1, COMMENT2}
	
	E = {putchar(prevC) | prevC = c, prevc = '\n' |putchar(' ')| putchar(prevC),prevC = '*' | c = '/' | putchar(' '),prevC = '/' | c = '/', prevC = '/' | c = '*', prevC = c, 	  prevC = c }
	
	T = {OUT => putchar(prevC) | prevC = c => OUT, OUT => prevC = '/' | c = '/' => COMMENT1,OUT =>  prevC = '/' | c = '*' => COMMENT2, COMMENT1 => prevC = c => COMMENT1, 		COMMENT1 => prevc = '\n' | putchar(' ')| putchar(prevC) => OUT, COMMENT2 => prevC = c => COMMENT2, COMMENT2 => prevC = '*' | c = '/' | putchar(' ') => OUT  }
	
	qo = OUT
	
	F = {OUT,COMMENT1, COMMENT2}
	

Tabla de transiciones




