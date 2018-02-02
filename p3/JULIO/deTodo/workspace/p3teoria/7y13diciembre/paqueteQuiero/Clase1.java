package paqueteQuiero;

// default => solo visible dentro del paquete.
// podemos tener todas las
// clase default que queramos.
class EnPaquete {
	public static void f() {
		
		Clase1 c1 = new Clase1();
		
		// es privado y solo accesible
		// desde aqui.
		// c1.privado = 3;

		c1.publico = 30;
		
		// es accesible por las clases que esten dentro del
		// mismo paquete.
		c1.protegido = 30;
	}
}

// publica => visible desde cualquier paquete.
// solo podemos poner una clase publica
// por fichero y su nombre debe coincidir
// con el nombre de la clase.
public class Clase1 {
	
	private int privado;
	public int publico;
	protected int protegido;
	// visibilidad default.
	int paquete;

	public void f() {
		privado = 3;
	}

}
