package constructores;

class A{
	
}

class B{
	public B(int x){}
	
}

public class Constructor {
	private int x;
	
	public static void main(String [] args){
		A a = new A(); // constructor  por defecto de oficio.
		
		// B b = new B(); // se cancela el constructor por defecto
		// porque java asume que debes usar uno de los que existen.
	}
}
