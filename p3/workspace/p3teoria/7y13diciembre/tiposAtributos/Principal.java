package tiposAtributos;

public class Principal {
	public static void main(String [] args){
		// podemos acceder a la variable estatica sin estar vinculado a ningun objeto.
		System.out.println(Clase1.y);
		
		Clase1 c1 = new Clase1();
		Clase1 c2 = new Clase1();
		
		c1.x = 2;
		c2.x = 4;
		System.out.println(c1.x + ", " + c2.x); // 2, 4 (cada objeto tiene la suya)
		// System.out.println(Clase1.x); es de instancia, neceisto saber de que objeto es.
		
		c1.y = 2;
		c2.y = 4;
		// almacenan caracteristicas comunes a todos los objetos de la clase.
		System.out.println(c1.y + " " + c2.y); // 4, 4 (es la misma variable), se queda el ultimo valor que le asigne.
		System.out.println(Clase1.y); // al ser de clase, no esta vinculada a ningun objeto.
	}
}
