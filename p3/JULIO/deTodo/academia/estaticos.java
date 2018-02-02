/*
los atributos de instancia constantes los podemos inicializar en el momento
de la declaración o en constructor, cada objeto tendra su porpia constate.
asi cada objeto tendra su propio valor para esa constante
 */

class Clase
{
    public static int x;         // atributo de la calse
    public int y;                // atributo de instancia
    public final static int z=0; // atributo de clase constante
    public final int v=10;       // atributo de instancia constante
}

public Class Estaticos
{
    public static void main(String[] args)
    {
	System.out.println(Clase.z); // para acceder a una variable de clase
	                             // podemos utilizar el nombre de la clase,
	                             // no  necesita estar  vinculada a ningun objeto
	Clase.x++;
	Clase c1=new Clase(), c2=new Clase();
	c1.y++;
	c2.y+=4;
	c2.x=c2.x + 20;
	System.out.println(c1.y + "" + c1.z);
	System.out.println(c2.y + "" + c2.x + "" + c1.x);
    }
}
