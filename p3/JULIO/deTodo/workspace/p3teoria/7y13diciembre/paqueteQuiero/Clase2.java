package paqueteQuiero;

public class Clase2 {
	
	public void f(){
		
		Clase1 c = new Clase1();
		
		// accediendo a un protected, desde el mismo paquete.
		c.protegido = 30;
		
		c.publico = 30;
		
		// c.privado = 30;
		
		c.paquete = 30;
		
	}
}
