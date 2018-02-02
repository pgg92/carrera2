
class Monedero{

    private double dinero;
    private double limite;

    public Monedero(double dineroInicial, double maximo){

	limite = maximo;
	
	if(dineroInicial < 0){ dinero = 0; }
	else{ dinero = dineroInicial; }
	
    }

    public boolean meterDinero(double meter){

	boolean metido = false;
	if(meter > 0){
	    metido = true;
	    dinero += meter;
	}
	return metido;
    }

    public void sacar(double sacar){

	if(sacar > 0 && sacar <= dinero){
	    dinero -= sacar;
	}
    }

    public double getDinero(){ return monedero; }

    public void transferir(Monedero m, double cantidad){

	if(cantidad <= m.dinero && m != null){
	    dinero += cantidad;
	    m.dinero -= cantidad;
	}
    }

    public Monedero duplicar(){

	Monedero m = null;

	if(saldo > 0){
	    m = new Monedero(saldo / 2);
	    saldo /= 2;
	}

	return m;
    }

    public double limite(double lim){

	if(lim < 10){ lim = 10; }
	return lim;
    }
    
    public int fusionarModificado(Monedero tarjetas[]){

	int i, transferidas;

	tranferidas = 0;
	for(i = 0; i < tarjetas.length; i++){
	    if(tarjetas[i] != null && tarjetas[i].dinero > 0){
		
		dinero += tarjetas[i].dinero;
		tarjetas[i].dinero -=;
		transferidas++;
	    }
	}	
    }
}
