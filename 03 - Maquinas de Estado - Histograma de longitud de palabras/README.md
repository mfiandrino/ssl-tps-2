# TP 03 - Maquinas de Estado - Histograma de longitud de palabras

## Numero de Equipo: 3

## Integrantes:

✒️ **Apellido y Nombre:** Argüeso, Matias Emanuel  **Legajo:** 166690-3 | **Usuario:** MatiasArgueso

✒️ **Apellido y Nombre:** Fiandrino, Maximiliano | **Legajo:** 152277-2 | **Usuario:** mfiandrino

✒️ **Apellido y Nombre:** Gomez, Tomas Leonel | **Legajo:** 175801-9 | **Usuario:** tgomez00

✒️ **Apellido y Nombre:** Lobianco, Agustín Francisco | **Legajo:** 147139-9 | **Usuario:** alobianco

✒️ **Apellido y Nombre:** Martínez Gross, Natalia | **Legajo:** 168861-3 | **Usuario:** nmartinezgross

✒️ **Apellido y Nombre:** Roldán, Iván Gabriel | **Legajo:** 167705-6 | **Usuario:** ivan3256   

## Enunciado
Este trabajo está basado en el ejercicio 1-13 de [KR1988] de la sección arreglos:  
~~~
Ejercicio 1-13. Escriba un programa que imprima el histograma de las longitudes de las palabras de su entrada. Es fácil dibujar el histograma con las barras horizontales; la orientación vertical es un reto más interesante.
~~~
Problema: Imprimir un histograma de las longitudes de las palabras de en la entrada estándar.  

### 12.1. Objetivos
- Aplicar los conceptos de modularización
- Utilizar las herramientas de compilación y construcción de ejecutables estudiadas
- Aplicar máquinas de estado para el procesamiento de texto.
- Implementar máquinas de estado con diferentes métodos.  

### 12.2. Temas
- Árboles de expresión.
- Representación de máquinas de estado.
- Implementación de máquinas de estado.
- Arreglos
- Flujos
- Modularización  

### 12.3. Tareas
1. Árboles de Expresión 

	a. Estudiar el programa del ejemplo las sección 1.5.4 Conteo de Palabras de [KR1988].  

	b. Dibujar el árbol de expresión para la inicialización de los contadores: nl = nw = nc = 0.  

	c. Dibujar el árbol de expresión para la expresión de control del segundo if: c == ' ' || c == '\n' || c == '\t'.  

2. Máquina de Estado:

	a. Describir en lenguaje dot ??? y dentro del archivo histograma.gv la máquina de estado que resuelve el problema planteado.  

	b. Formalizar la máquina de estados como una n-upla, basarse en el Capítulo #1 del Volumen #3 de [MUCH2012].  
	
3. Implementaciones de Máquinas de Estado:  
Las implementaciones varían en los conceptos que utilizan para representaar
los estados y las transiciones.  

	a. Implementación #1: Una variable para el estado actual.  

		i. Escribir el programa histograma-1-enum-switch.c que siga la Implementación #1, variante enum y switch. Esta implementación es la regularización de la implementación de la sección 1.5.4 de [KR1988]. Los estados son valores de una variable y las transiciones son la selección estructurada y la actualización de esa variable. Esta versión es menos eficiente que la versión de [KR1988], pero su regularidad permite la automatización de la construcción del programa que implementa la máquina de estados. Además de la regularidad, esta versión debe:
		- Utilizar typedef y enum en vez de define, de tal modo que la variable estado se pueda declarar de la siguiente manera: State s = Out;
		- Utilizar switch en vez de if.  

		ii. Responder en readme.md: Indicar ventajas y desventajas de la versión de [KR1988] y de esta implementción.  

	b. Implementación #2: Sentencias goto (sí, el infame goto)  

		i. Leer la sección 3.8 Goto and labels de [KR1988]  

		ii. Leer Go To Statement Considered Harmful de [DIJ1968].  

		iii. Leer "GOTO Considered Harmful" Considered Harmful de [RUB1987].  

		iv. Responder en readme.md: ¿Tiene alguna aplicación go to hoy en día? ¿Algún lenguaje moderno lo utiliza?  

		v. Escribir el programa histograma-2-goto.c que siga la Implementación #2.
		En esta implementación los estados son etiquetas y las transiciones son la selección estructurada y el salto incondicional con la sentencia goto.

	c. Implementación #3: Funciones Recursivas

		i. Leer la sección 4.10 Recursividad de [KR1988]. 

		ii. Responder en readme.md: ¿Es necesario que las funciones accedan a contadores? Si es así, ¿cómo hacerlo?.
		Leer la sección 1.10 Variables Externas y Alcance y 4.3 Variables Externas de [KR1988].  

		iii. Escribir el programa, histograma-3-rec.c que siga la implementación #3.
		En esta implementación los estados son funciones recursivas y las transiciones son la selección estructurada y la invocación recursiva.

	d. Implementación #X:  
	Es posible diseñar más implementaciones. Por ejemplo, una basada en una tabla que defina las transiciones de la máquina. En ese caso, el programa usaría la tabla para lograr el comportamiento deseado. El objetivo de este punto es diseñar una implementación diferente a las implementaciones #1, #2, y #3.

		i. Diseñar una nueva implementación e indicar en Readme.md cómo esa implementación representa los estados y cómo las transiciones.

		ii. Escribir el programa, histograma-x.c que siga la nueva implementación.

4. Escribir un único programa de prueba para las cuatro implementaciones.  

	Construir una tabla comparativa a modo de benchmark que muestre el tiempo de procesamiento para cada una de las cuatro implementaciones, para tres archivos diferentes de tamaños diferentes, el primero en el orden de los kilobytes, el segundo en el orden de los megabytes, y el tercero en el orden de los gigabytes.  

	. (Opcional) Eficiencia del uso del Tiempo:
	La tabla tiene en las filas las cuatro implementación, en las columnas los tres archivos, y en la intersección la duración para una implementación para un archivo.

### 12.4. Restricciones
- La implementación de la máquina de estado debe ser "seleccionable".  
Algunas formas posibles de implementar la selección son:
	- En tiempo de traducción desde el makefile.
	- En de tiempo de ejecución mediante reemplazlo de dynamic link library.
	- En de tiempo de ejecución mediante argumentos de la línea de comandos.
- La solución debe estar modularizada: las máquinas de estado no deben conocer del graficador y viceversa.
- Desde main.c se coordina todo.

### Crédito extra
Parametrizar si el histograma se dibuja vertical u horizontalmente.

### 12.5. Productos
~~~
DD-histograma
|-- readme.md
| |-- Árboles de expresión.
| |-- Respuestas.
| `-- Benchmark.
|-- histograma.gv
|-- Makefile
|-- main.c
|-- Graficador.h
|-- Graficador.c
|-- Test.c
|-- histograma.h
|-- histograma-1-enum-switch.c
|-- histograma-2-goto.c
|-- histograma-3-rec.c
`-- histograma-x.c
~~~

## Resolución

### 1. Arboles de expresión
Utilizamos notación infija para ambos árboles de expresion.  
	b)  
  				![image](https://user-images.githubusercontent.com/82005945/125212785-0dcd8580-e286-11eb-98e9-8f2d3f7706f2.png)  
	c)  
				![image](https://user-images.githubusercontent.com/82005945/125212800-2d64ae00-e286-11eb-99ab-6afb62bc17eb.png)

### 2. Máquina de Estado

  a) Describir en lenguaje dot y dentro del archivo histograma.gv la máquina de estado que resuelve el problema planteado.  
  Grafico resultante:  
    
  ![image](https://user-images.githubusercontent.com/82005945/125221973-7d03a380-e29f-11eb-846d-7194a35257c5.png)

  
  b) Formalizar la máquina de estados como una n-upla, basarse en el Capítulo #1 del Volumen #3 de [MUCH2012]  
    
  M = {Q, E, T, qo, F}
  
 	Q = {OUT, IN}
	
	E = {c==('\n'||'\t'||' '), ++contadores[nc] nc=0, ++nc, c!=('\n'||'\t'||' ') }
	
	T = {OUT => c==('\n'||'\t'||' ') => OUT, OUT => ++nc => IN, IN => c!=('\n'||'\t'||' ') => IN, IN => ++contadores[nc] nc=0 => OUT }
	
	qo = OUT
	
	F = {OUT, IN}
	

Tabla de transiciones

![image](https://user-images.githubusercontent.com/82044738/125221765-21391a80-e29f-11eb-8215-c5031120a52b.png)



### 3. Implementaciones de Máquinas de Estado

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
  
d)  
Diseñar una nueva implementación e indicar en Readme.md cómo esa implementación representa los estados y cómo las transiciones.  
- Respresentación de estados: son realizadas mediante etiquetas
- Representación de transiciones: son realizadas mediante saltos de goto's tomando en consideración la condición del if que analiza el valor de "c".  
  