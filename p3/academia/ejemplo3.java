class Venga
{
    public int a; // atributo de instancia
    public static int b=a; // atributo de clase
    public venga(int x)
    {
	a = x;
	b++;
    }

    public int getA(){ return A; } // metodo de instancia, recibe this

    public static int get(){ return a + b }; // metodo clase, no tiene this
                                             // no existe this.a, solo se puede acceder a atributos static
   
    public static int getB(){ return b; } // b no necesita this
   
    public int getS(){ return a+b; } // es de this y a sera la global
}

public Class operaciones3
{
    public static void main(String[] args)
    {
	Venga va1 = new Venga[2];
	Venga va2 = new Venga[3];
	Venga va3 = new venga (venga.getB()); // venga.getB() -> al ser de clase puedes llamar sin método
	System.out.print(va1.getS() + va1.getB() + va2.getA());
    }
}
