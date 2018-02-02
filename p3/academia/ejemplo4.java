// folio

Class A
{
    private int x = 10;      //variable de instancia
    private static int z = 0;// variable de clase
    private final int v;     // variable de instancia constate
    public A(int vv)
    {
	v = vv;
	z = z + vv;
    }

    public int getX(){ return x; }
    public int getZ(){ return z; }
    public static int getZ2(){ return z; }
    public int getS(){ return z+y+v; } // desde uno de instancia accedo a todo
    //    public static int getSS(){ return y + z + v; } // no podemos acceder a los variables
                                                   // de isntacia desde un metodo static

    public static void incS(){ z++; };    
}

public Class Ejemplo4
{
    public static void main(Stirng[] args){
	// System.out.println(A.x); // x es de instancia, necesito una isntancia
	// System.out.println(A.z); // z es privada
	System.out.println(A.getZ2());
	A a new = A(12);
	System.out.println(a.getX() + "" + a.getZ()); // a.getX() == 10, a.getZ() == 12
	// System.out.println(A.getZ()); // getz es de isntancia necesito un objeto para invocalo
	System.out.println(A.getZ2()); //A.getz2() == 12
	a.incS(); // aunque se ignore a podemos usar para invocar un metodo static
	A b = new(14);
	System.out.println(b.getS() + b.getZ()); // b.getS() == 50, b.getZ() == 6
    }
}
