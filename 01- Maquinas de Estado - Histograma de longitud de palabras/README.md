## 1. Arboles de expresión
Utilizamos notación infija para ambos árboles de expresion.  
	b)  
  				![image](https://user-images.githubusercontent.com/82005945/125212785-0dcd8580-e286-11eb-98e9-8f2d3f7706f2.png)  
	c)  
				![image](https://user-images.githubusercontent.com/82005945/125212800-2d64ae00-e286-11eb-99ab-6afb62bc17eb.png)

## 2. Máquina de Estado

  a)  

  b) M = {Q, E, T, qo, F}
  
 	Q = {OUT, IN}
	
	E = {c==('\n'||'\t'||' '), ++contadores[nc] nc=0, ++nc, c!=('\n'||'\t'||' ') }
	
	T = {OUT => c==('\n'||'\t'||' ') => OUT, OUT => ++nc => IN, IN => c!=('\n'||'\t'||' ') => IN, IN => ++contadores[nc] nc=0 => OUT }
	
	qo = OUT
	
	F = {OUT, IN}
	

Tabla de transiciones

![image](https://user-images.githubusercontent.com/82044738/125221765-21391a80-e29f-11eb-8215-c5031120a52b.png)



## 3. Implementaciones de Máquinas de Estado

a)  
Indicar ventajas y desventajas de la versión de [KR1988] y de esta implementción
- La implementación con switch tiene como ventaja la modularización, ya que el graficador no conoce nada de contar caracteres, y el histograma no sabe nada de graficar o mostrar resultados.
- La implementación con switch es mas mantenible debido a que si requiere algún cambio de alguna acción en una transición de estados, simplemente se agrega la acción en el case correspondiente, en cambio, en la version de [KR1988] no está separado cada caso, por lo tanto, habría que hacer ingeniería inversa para distinguir cada caso para luego agregar dicha acción.
- La implemetación del switch puede ser mecanizada. Se puede usar un programa en el cual al dibujar la máquina de estados devuelva el código de la misma.
- La version de [KR1988] está optimizada para ser mas eficiente, ya que no evalúa los casos o acciones redundantes, a costa de tener menor mantenibilidad.

b)  
¿Tiene alguna aplicacion goto hoy en dia?

- Los goto se utilizan en lenguaje de bajo nivel para hacer saltos de linea, en C se pueden utilizar para errores o para salir de ciclos multiples. 
	
¿Algun lenguaje moderno lo utiliza?

- Muchos lenguajes tienen GOTO o similares, pero en todos, utilizarlos discriminadamente esta visto como una mala practica de programacion.

c)  
¿Es necesario que las funciones accedan a contadores? Si es así, ¿cómo hacerlo?
-	Es necesario en este caso que las funciones accedan a contadores, ya que utilizamos y modificamos sus valores dentro de las funciones recursivas. Para
que las funciones recursivas accedan a los contadores debemos declararlas y pasarlas por parametro. 

			
	
