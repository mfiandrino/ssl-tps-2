# Maquina de Estados

 a) Descripcion maquina de estados en lenguaje DOT
 
![includes](https://user-images.githubusercontent.com/82002194/130468334-85518479-1804-4140-8a98-4ef0e3824358.png)

b) Formalización máquina de estados como una n-upla

	M = {Q, E, T, qo, F}
	Q = {OUT, IN}
	E = {c != '#' | inc != 'include' | c = getchar(), c == '#' | inc == 'include' | c = getchar(), c == '<' | c == "" | c = getchar(), c = getchar()}
	T = {OUT => c != '#' | inc != 'include' | c = getchar() => OUT, OUT => c == '#' | inc == 'include' | c = getchar() => IN, IN => c == '<' | c == "" | c = getchar() => IN, IN => c = getchar() => OUT}
	qo = OUT
	F = {OUT, IN}	
	
Tabla de transiciones

![atenderIncludes como n-upla](https://user-images.githubusercontent.com/82005945/130468997-ebea30a9-b488-4654-916d-a8f2748dccc6.png)
