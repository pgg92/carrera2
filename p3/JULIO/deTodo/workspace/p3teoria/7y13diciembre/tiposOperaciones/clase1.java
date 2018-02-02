package tiposOperaciones;

public class clase1 {
	public int x;
	public static int y;
	
	// operacion de instancia
	public void f(){
		// existe this. siempre hay objeto implicito.
		x = 3;
		y = 3;
	}
	
	// operacion de clase
	public static void g(){
		// no existe this, no hay objeto implicito
		// x = 3; // no tengo this, no es this.x, x es de instancia necesito una instancia.
		y = 3;
	}
	
	public static void main(String [] args){
		// estamos invocando a g sin ningun objeto, es una operacion de clase
		// no tiene objeto impleicigo.
		clase1.g();
		
		// f es de instancia necesita que lo invoque un objeto.
		// clase1.f(); 
		
		clase1 c = new clase1();
		
		c.f();
		c.g(); // se ignora el objeto que lo invocaaaa!
		
	}
}
