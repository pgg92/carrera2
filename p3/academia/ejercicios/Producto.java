
class Producto{

    private String nombre;
    private double pvp;
    private int stock;

    private static final int INITIALSTOCK = 0;
    
    public Producto(String n, double p){

	if(p > 0){ pvp = p; }
	else{ pvp = 1; }

	nombre = n;
	stock = INITIALSTOCK;
    }

    public int incrementar(int incremento){

	int incrementado = 0;
	
	if(incremento >= 0){
	    stock += incremento;
	    incrementado = incremento;
	}

	return incrementado;
    }

    public double incrementar(int demanda){

	double coste = 0;

	if(demanda <= stock){
	    
	    if(demanda <= 3){ coste = pvp * demanda; }
	    else{ coste = pvp * demanda * 100 / 10; }
	    
	    stock -= demanda;
	}
	
	return coste;
    }

    public int getUnidades(){ return stock; }
    public double getPrecio(){ return pvp; }
    public String getNombre(){ return nombre; }
    
}
