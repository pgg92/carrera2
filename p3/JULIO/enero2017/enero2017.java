// ENERO 2017 (las que se han podido sacar de las 40)

// NO HAY FOTO DEL UML
// PREGUNTAS FOTO
1. En java, si un metodo publico no abstracto f() definido en una superclase se sobreescribe
en una de su subclases, se puede invocar desde la subclase a meotodo de la superclase mediante la **no se ve casi esta parte** la instruccion super.f()
-F

2. ** ni idea que pone **
-

3. Todas las relaciones entre objetos que aparecen en el diagrama UML son binarias
-

4. Si un metodo lanza excepciones declaradas (checked exceptions) directa o indirectamente y no las captura debe indicarlos en su especificaion de excepciones (clausula throw, en java)
-F: throws es para indicar las que puedes lanzar independientemente de si las capturas o no hay que ponerlo para las que lo requieran

5. la clase Color del diagrama UML es una unterface de java
-

6. La metafora de los dos sombreros nos enseña que debemos aprovechar el momento en que estamos introduciendo una nueva funcionalidad en nuestro codigo para refactorizarlo al mismo tiempo
-F: lo contrario hacer cada cosa por separado

7. Una clase generica se puede utilizar mediante conversion de tipos implicita
-?¿

8. EL downcasting se puede realizar mediante conversion de tipos implicita
-V: ademas el downcasting si no me equivoco siempre en implicito

9. EL upcasting se puede realizar mediante conversion de tipos implicita
-V: si puede realizar tanto de forma implicita como explicita, (implicita: objeto base referencia a derivada sin poner el cast)

10. En java, una clase puede implementar varias interfaces, per solo puede heredar implementaciones de una unica superclase
-V: herencia de interfaz puede ser multiple y de implementación solo es simple en java

11. Sabemos que los lenguajes de programacion soportan el reemplazo o refinamiento como una forma de implementar metodos sobrecargados, pero no hay ningun lenguaje que proporciones ambas tecnicas (por ejemplo. Java solo soportar reemplazo y C++ solo refinamiento)
-F: en java hay sobrecarga(cambiar implementacion) y refinamiento(usar super)

12. La genericada es una forma de polimorfismo
-V

13. En ajva solo las clases pueden ser genericas, no asi los metodos
-F

14. En el paradigma orientados a objetos, un objetos siempre es una instancia de alguna clase
-V

// PREGUNTAS OTRA FOTO
15. Los metodos definidos en una subclase nunca pueden acceder directamente a las propiedades
privadas de la superclase 
-V: nunca se accede a lo privado da igual el caso

16. No tiene sentido definir constructuores en una clase abstracta, ya que nunca serán invoca-
dos
-F: si tiene constructuores

17. La siguiente definicion: interface s{ public Object obj; } constituye una definicion de 
interfaz correcta en java
-F

18. Desde un metodo de una subclase siempre puede invocarse un metodo implementado con el mis-
mo nombree identica sigantura de tipo en su superclase
-¿?

19. Un metodo tiene poliformismo puro cuando tiene como argumentos al menos una variable polimorifca 
-V: es la definicion de polimorfismo puro

20. Si en una clase no se declara, implicita o explicitamente, un constructor por defecto no se pueden crear instanscia de esa clase
-F: hay constructor de oficio

21. Los constructores siempre deben tener visibilidad publica
-F: puedes hacer los constructores que quieras y distinta visibilidad

22. Una interfaz en java obliga a que las clases no abstractas que la implementan deban implementar todos los metodos que la interfaz declara
-V

23. Para usar reflexion en Java debemos conocer en tiempo de compilacion el nombre de las
clases que queremos manipular
-F

24. El principio abierto-cerrado indica que un componente software debe estar abierto a su extenseion, pero cerrado a su modificacion
-V

25. La inversio de control en los frameworks es posible, entre otras cosas, al enlace dinamico de metodos
-V

26. Decimos que un metodos en una subclase sobrescribe un metodo de su superclase si los metodos tienen el mismo nombre, la misma signatura de tipos (excluyendo el tipo devuelto) y enlace dinamico
-¿?

27. this es un ejemplo de variable polimorfica en java
-V: aunque no pueda cambiar a donde apunta no deja de ser polimorfica

28. Segun el principio de sustitucion de Liskov, los metodos que usan references a superclases deben ser capaces de utilizar objetos de sus subclases sin saberlo
-

29. La forma canonica de una clase varia dependiendo del lenguaje que se utilice
-V

30. En java, al implementar una composicion, la copia defensiva nos ayuda a prevenir que existan  referencias a los objetos 'parte' que sean externas al objeto 'todo'
-V

31. Un lenguaje de programacion puede combinar tipado estatico en algunas instrucciones del languaje y tipado dinamico en otras
-V

32. En el diagrama UML, el motodo escalar()... de la clase Figura2D tien enlace estatico
-

33. Supongamos que la clase FactoryFiguras del diagrama UML tiene como contenido crear objetos de tipo IDibujable. Esta clase tiene una relacion de dependencia con Circulo y Rectangulo porque usa 
instacias de esas clases
-

34. Dado el diagrama UML, els siguiente constructor de copia de Lienzo, sin errores de compilacion, realiza una copia profunda de una objeto Lienzo. (suponemos que figuras esta imple,entado como List<IDibujable>):

public Lienzo(Lienzo otro)
{
	ancho = otro.ancho;
	alto = otro.alto;
	
	titulo = new String(otro.titulo);
	figuras = new ArrayList<IDibujable>();
	
	for (IDibujable figura : otro.figuras) 
	{
		figuras.add(figura);
	}
}
-F: diria que falso, porque solo estas copiando referencias a los objetos del ArrayList y no añadiendo uno
identido a cada uno de la lista

// PREGUNTAS OTRA FOTO (sin repetir)
35. La clase ExcepcionJuegoTablero en el diagrama UML tiene una relacion de dependencia con AbstractPartida porque usa informacion proporcionada por esa ultima
-

36. Dado el diagrama UML, el siguiente constructor de copia de AbstractTablero realiza una copia profunda de una objeto AbstractTablero (supones que casillas esta implementado como un List<Casilla>)

public AbstractTablero(AbstractTabler otro)
{
	super otro;
}

dimx = otro.dimx;
dimy = otro.dimy;

casillas = new ArrayList<Casillas>();
for (Casilla casilla : otro.casillas)
{
	casillas.add(casilla);
}
-

37. Esta implementacion del metodo AbstractTablero.inicializa() del diagrama UML no compilará
public static void inicializa()
{
	dimx = 0;
	dimy = 0;
	casillas = null;
	** puede que falte algo de codigo**
}
-F: en caso de ser los atributos de clase
-V: en caso de no ser de clase




