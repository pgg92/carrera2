
class Coche{

    private double consumo;
    private double disponibilidad;
    private double capacidad;

    private static final double MINCONSUMO = 0,5;
    private static final double MINCAPACIDAD = 0;

    
    public Coche(double con, double cap){

	if(con <= 0){ consumo == MINCONSUMO; }
	else{ consumo = con; }

	if(cap < 0){ capacidad = MINCAPACIDAD; }
	else{ capacidad = cap; }
    }

    public double repostar(double añadir){

	double cantidad, repostado = 0;
       
	if(añadir >= 0 ){
	    
	    if(añadir > capacidad - disponibilidad){

		cantidad = capacidad - disponibilidad;
		disponibilida += añadir;
	    }

	    disponibilidad += añadir;
	    repostado = cantidad;
	}

	else{ repostado = 0;}
	
	return repostado;
    }

    public double getDisponibilidad(){ return disponibilidad; }
    public double getCapacidad(){ return getCapacidad; }

    public boolean recorre(double distancia){

	boolean recorrer = false;
	
	if(distancia => 0){
	    if(CALCULARSIPUEDE){

		disponibilidad -= ;
		recorrer = true;
	    }
	}
    }

}
