package paquete1;


public class Clase3 {
	
	// Atributo de instancia: existe una copia por cada objeto
	// de la clase. Cada objeto que cree de la Clase3 tiene
	// su propia valor.
	private int valor;
	
	
	// Atributo de clase: solo existe una copia para todos los 
	// objetos de la clase.
	
	private final int x;
	
	private final int y = 10;
	
	// private final int z;
	
	public static void f(){
		
		// la clase hay que usarla con el
		// nombre completo porque ya hay
		// una Clase1 dentro de este paquete.
		paqueteQuiero.Clase1 miClase = new paqueteQuiero.Clase1();
		
		//miClase.privado = 30;	// es privado y no accesible desde fuera de la clase.
		//miClase.protegido = 30; // no estoy en el mismo paquete y no hay relacion de herencia
		miClase.publico = 30;
		//miClase.paquete = 30; // no estoy en el mismo paquete
		
		// no puedo acceder desde otro paquete.
		// paqueteQuiero.EnPaquete mic;
		
	}
	public Clase3(int vx){
		
		// podra cambiar en funcion del objeto
		// no podra cambiar de valor dentro del objeto,
		// pero cada uno tendra un valor distinto.
		x = vx;
		//y = 10;
	}
	public void g(){
		
		final int x = 3;
		final int y;
		
		y = 33;
		// y = 12; no le puedo dar valor dos veces, es constante.
		
	}
}
