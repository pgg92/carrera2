package paquete1;

public class Clase2 extends paqueteQuiero.Clase1{
	
	public void f(){
		//privado = 3;
		publico = 3;
		//paquete = 3;
		protegido = 3;	// estoy fuera del paquete, como es herencia si que me deja acceder a lo protegido
	}
	public void g(Clase2 r){
		r.publico = 3;
		//r.privado = 5;
		r.protegido = 10;
		//r.paquete = 30;
	}
}
