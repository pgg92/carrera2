package ejercicioBasico1;

public class coche
{
	private int conMax=12;
	private String matricula;
	private Double deposito;
	private double capacidad;
	private static final double cmin = 40;
	private int numCoches=0; // si no lo ponemos static todos los coches tendrán el mismo valor
							// asi tenemos 1 valor para todos;
	private final int consumo;
	
	public coche(String m)
	{
		this.matricula=m;
		numCoches++;
		if(deposito<cmin){this.deposito=cmin;}
		consumo=4;
	}
	
	public double repostar(Double rep)
	{
		double salida=rep;
		if(rep<0){salida=0;}
		else{deposito+=rep;}
		return salida;
	}
	
	public int GetNumc(){return numCoches;}

	public String getMatricula() {
		return matricula;
	}

	public Double getDeposito() {
		return deposito;
	}


	public double getCapacidad() {
		return capacidad;
	}

	public int getNumCoches() {
		return numCoches;
	}

	public static double getCmin() {
		return cmin;
	}
	
	public coche(Double rep, int con, String m)
	{
		if(con>conMaximo){con=12;}
		
		if(con<4){con=consumo;}
	}
	
	/**
	 * Añadir un atributo constante, consumo, que es el consumo en litros cada 100 km
	 * 
	 * El consumo por defecto sera 4 litros
	 * 
	 * Añadir otro constructor que reciba ademas como paramtero el consumo del coche
	 * si el consumo es inferior a 4 se fiajra a 4, y si el consumo es superior a 12 se fijara
	 * a 12 (añadir constante para dichos valores)
	 * 
	 * Añadir el mettodo recorrer, que recive una distancia y devuelve cierto si se ha podido
	 * recorrer la dsitancia, en funcion del consumo y de la cantidad a recorrer
	 * 
	 */
	
	public int recorrer(double distancia)
	{
		boolean sepuede = false;
		
		if(distancia>0)
		{
			if(distancia / 100 * consumo <= deposito)
			{
				sepuede = true;
				deposito-= distancia / 100 * consumo;
			}
		}
		
		return sepuede;
	}
	
}





