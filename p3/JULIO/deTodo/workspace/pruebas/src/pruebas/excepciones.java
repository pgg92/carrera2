package pruebas;

public class excepciones {

	excepciones(){}
	
	public void f(int valor) throws Exception{
		
		if(valor == 1)
			throw new Exception("cuando valor es 1");
		
		if(valor == 2)
			throw new Exception("cuando valor es 2");
	}
	
	
}
