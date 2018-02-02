Conceptos:

-friend : método que permite a un objeto acceder a mi parte privada
- Puntero this : direccion de memoria del objeto de nuestra clase que invoca al método

		  TCalendario a.
		  
		  a.metodo(int b) {
		    return this; //Devuelve el puntero del objeto a
		    return *this //Devuelve el contenido del objeto a
		  }
		    
- Puntero const:






-----------------------------------------------------------OPERADORES DE SOBRECARGA----------------------------------------------------------------------

--------------------------------------------------------------------
//Si se modifica el operando de la izquierda (Ejemplo Igual a=b).

1. Almacenar todos los cambios en el propio objeto
2. Devolver el propio objeto // return *this;
3. Lo devolvemos por referncia para que el constructor por defecto no trabaje (que es lo que pasaría si lo devolviéramos por valor).

TCalendario &TCalendario::operator=(const TCalendario &c) { //Devuelto por referencia.
  
  if(this != &c) {
    
    (*this).~Tcaledario(); //Borramos el contenido de nuestro objeto TCalendario.
    
    dia=c.dia; //Almacenar todos los cambios en el propio objeto.
    mes=c.mes;
    anyo=c.anyo;
    
    //Mensaje ya está a NULL porque hemos llamado al destructor
    
    if(c.mensaje!=null) { //Comprobemos si c.mensaje no es nulo
      mensaje = new char[strlen(c.mensaje)+1]; //Asigno la misma capacidad de memoria a mens que a mensaje
      strcpy(mensaje, c.mensaje); // Copio el mensaje
    }
    
  }
  
  return *this; //Devolver el propio objeto.
}

----------------------------------------------------------------------
//Si no se modifica el operando de la izquierda (Ejemplo suma a+b).

1. Crear objeto temporal para almacenar el resultado
2. Devolvemos el objeto temporal.
3. Lo devolvemos por valor porque si lo hiciesemos por referencia se destruiría ya que es un objeto local (solo permanece un tiempo) y se destruiría antes de llegar al {.





