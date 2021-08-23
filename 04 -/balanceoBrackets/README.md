# Maquina de Estados

 a) Descripcion maquina de estados en lenguaje DOT
 
 
 b) Formalizacion máquina de estados como una 7-upla
 
M = {E, A, A', T, e0, p0, F}

E = {CARACTER_COMUN, APERTURA_BRACKET, CLAUSURA_BRACKET, COMILLAS} 

A = { {, [, (, }, ], ), ", ' }

A' = { {, [, (, }, ], ), ", ' }

e0 = {CARACTER_COMUN}

P0 = $

F = {CARACTER_COMUN, APERTURA_BRACKET, CLAUSURA_BRACKET, COMILLAS}