
 # Maquina de Estados
 a) Descripcion maquina de estados en lenguaje DOT
 
 
 b) Formalizar la máquina de estados como una n-upla, basarse en el Capítulo #1 del Volumen #3 de [MUCH2012]  
    
  M = {Q, E, T, qo, F}
  
 	Q = {OUT, IN}
	
	E = {c==('\n'||'\t'||' '), ++contadores[nc] nc=0, ++nc, c!=('\n'||'\t'||' ') }
	
	T = {OUT => c==('\n'||'\t'||' ') => OUT, OUT => ++nc => IN, IN => c!=('\n'||'\t'||' ') => IN, IN => ++contadores[nc] nc=0 => OUT }
	
	qo = OUT
	
	F = {OUT, IN}
	

Tabla de transiciones

