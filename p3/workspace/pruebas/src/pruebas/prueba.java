package pruebas;

public class prueba {

	public static void main(String[] args) {
		
		int valor = 2;
		
		excepciones e = new excepciones();
		
		try 
		{
			e.f(valor);
		}
		catch (Exception e1) 
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		finally{}

	}

}
