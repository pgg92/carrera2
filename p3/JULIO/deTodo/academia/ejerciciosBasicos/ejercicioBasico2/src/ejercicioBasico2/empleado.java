package ejercicioBasico2;

public class empleado {
	
	private char dni;
	private double salarioBase;
	private final static double salarioMinimo=8;
	
	public empleado(char dni, double s)
	{
		this.dni=dni;
		setSalario(s);
		salarioBase=s;
	}
	
	public double setSalario(double s)
	{
		if(s<salarioMinimo){ salarioBase = salarioMinimo; }
		return s;
	}
	
	public double getSalario(){return salarioBase;}


	/**
	 * añadir el metodo calcularSalario que devuelve
	 * el salario trancurrido en n meses (n para como parametro)	
	 */
	public double calcularSalario(int n)
	{
		return salarioBase * n;
	}
	
	/**
	 * añadir el metedod, incremetarSalario
	 * que incrementa en salario en un porcentaje pasado
	 * como parametro (solo si este es positivo) y devuelve
	 * la cantidad incrementada
	 */
	public double incrementarSalario(double porcentaje)
	{
		double incrementa = 0;
		
		if(porcentaje > 0)
		{
			incrementada = salarioBase*porcentaje/100;
			salarioBase += incrementada;
			return incrementada;
		}
		
		
	}
	
}

ArrayList -> //array dinamico
			// va creciendo conforme le vamos metiendo nuevos valores





































