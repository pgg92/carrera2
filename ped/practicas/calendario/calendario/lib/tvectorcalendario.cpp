//Raimundo Fenoll Albaladejo

#include "tvectorcalendario.h"
#include <iostream>
#include "string.h"

//Constructor Por Defecto
TVectorCalendario::TVectorCalendario() {
	
	//Debemos inicializarb tanto el vector de Calendarios como tamano
	
	c=NULL; //Vector de Dimensión cero.
	tamano=0;
}

//Constructor A Partir De Un Tamaño
TVectorCalendario::TVectorCalendario(const int t) {
	
	//Debemos inicializarb tanto el vector de Calendarios como tamano
	
	if(t<0) { 
		c=NULL;
		tamano=0;
	}
	else {
		c=new TCalendario[t];
		tamano=t;
	}
}

//Constructor De Copia
TVectorCalendario::TVectorCalendario(const TVectorCalendario &v) {

	if(this!=&v) {
		c=NULL;
		Copiar_Datos(v);
	}
}

//Destructor
TVectorCalendario::~TVectorCalendario() {
	
	if(c!=NULL) {
		delete [] c;
		c=NULL;
	}

	//tamano=0; // Si inicializa a 0 por defecto.	
}

//Sobrecarga Del Operador Asignación
TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &v) {
	
	if(this != &v) {
		
		(*this).~TVectorCalendario();
		Copiar_Datos(v);
	}
	
	return *this;
}

//Sobrecarga Del Operador Igualdad
bool TVectorCalendario::operator==(const TVectorCalendario &tv) {
	
	bool ok=true;
	
	if(tamano==tv.tamano && c!=NULL && tv.c!=NULL) {
		for(int i=0;i<tamano && ok==true;i++) {
			if(c[i]==tv.c[i]) {
				ok=true;
			}
			else {
				ok=false;
			}
		}
	}
	
	return ok;
}

//Sobrecarga Del Operador Desigual
bool TVectorCalendario::operator!=(const TVectorCalendario &tv) {
	
	bool ok=false;
	
	if(tamano!=tv.tamano) { //Basta con que no tengan el mismo tamano					//Para que ya no sean iguales.
		ok=true;
	}
	else {
		for(int i=0;i<tamano;i++) {
			if(c[i]!=tv.c[i]) {
				ok=true;
			}
		}
	}
	
	return ok;
}

//Sobrecarga Del Operador Corchete (Parte Izquierda)
TCalendario &TVectorCalendario::operator[](const int index) {

	//Si está comprendido en el rango, entonces tiene que devolver
	//esa posición.
	if(Comprueba_Rango(index)) {
		return c[index-1];
	}
	//Si existe a una posición que no existe, tiene que devolver
	//un calendario vacío.
	else {
		error = TCalendario();
	}

	return error;
}

//Sobrecarga Del Operador Corchete (Parte Derecha)
TCalendario TVectorCalendario::operator[] (int index) const {

	TCalendario paux;

	//Esttá dentro de los límites.
	if(Comprueba_Rango(index)) {
		return c[index-1];
	}
	//Esta fuera de los límites. Tiene que devolver el calendario vacío.
	else {
		return paux;
	}
}

//Tamaño Del Vector (Posiciones Totales)
int TVectorCalendario::Tamano() {
	return tamano;	
}

//Cantidad De Posiciones Ocupadas (No Vacías) En El Vector
int TVectorCalendario::Ocupadas() {
	
	int vacio=0;
	
	for(int i=0;i<tamano;i++) {
		if(c[i].EsVacio()) {
			vacio++;
		}
	}
	return tamano-vacio;
}

//Devuelve True Si Existe El Calendario En El Vector
bool TVectorCalendario::ExisteCal(const TCalendario &cal) {
	
	bool ok=false;

	for(int i=0;i<tamano;i++) {
		if(c[i]==cal) {
			ok=true;
		}
	}

	return ok;
}

//Mostrar Por Pantalla Mensajes de TCalendario
void TVectorCalendario::MostrarMensajes(const int d, const int m, const int a) {

	int index=0;

	TCalendario cal;

	//Si se pasa una fecha inválida como parámetro, la salida es [].
	if(cal.esCorrecto(d,m,a)==true) {
		cout<<"[]";
	}

	else {

		//Cual es la última posición en donde c[i].dia>=cal?
		for(int i=1;i<tamano;i++) {

			if(c[i]>cal || c[i]==cal) {
				index=i;
			}
		}

		cout<<"[";

		//Imprimamos los Calendarios
		for(int j=1;j<tamano;j++) {

			if(c[j]>cal || c[j]==cal) {

				if(j==index) {
					cout<<c[j];
				}

				else {
					cout<<c[j]<<" ,";

				}
			}
		}

		cout<<"]"; //Cerrado entre Corchetes la salida
	}

}

//Redimensionar El Vector de TCalendario
bool TVectorCalendario::Redimensionar(const int t) {
	
	bool ok=true;
	TCalendario *vector_calendario = NULL; //Puntero auxiliar que apunta a NULL
	
	if(t<=0 || t==tamano) {
		return false;
	}

	else if(t>0 && t>tamano) {
		
		vector_calendario=new TCalendario[t]; //Nos creamos un vector de Calendario de t posiciones.

		if(vector_calendario!=NULL) { //vector_calendario debe de tener almenos algo..

			if(c!=NULL) {

				for(int i=0;i<t;i++) {

					//Las posiciones nuevas serán vacías
					if(i>=tamano) {
						TCalendario cal;
						vector_calendario[i]=cal;
					}

					//Si no Copiamos directamente el calendario.
					else {
						vector_calendario[i]=c[i];
					}
				}

				delete [] c;
			}

			//Redimensionamos:
			tamano=t;
			c=vector_calendario;
			ok=true;
		}	
	}

	else if(t>0 && t<tamano) {

		vector_calendario=new TCalendario[t]; //Nos creamos un vector de Calendario de t posiciones.

		if(vector_calendario!=NULL) { //vector_calendario debe de tener almenos algo..

			if(c!=NULL) {

				//Simplemente copiamos hasta el tamaño del nuevo vector
				for(int i=0;i<t;i++) {

					vector_calendario[i]=c[i];
				}

				delete [] c;
			}

			//Redimensionamos:
			tamano=t;
			c=vector_calendario;
			ok=true;
		}
	}
	return ok;
}

//Sobrecarga Del Operador Salida
ostream & operator<<(ostream &o, const TVectorCalendario &v) {

	//Si el vector es de dimensión cero,
	if(v.tamano==0) {
		o<<"[]";
	}
	else {

		o<<"[";

		for(int i=1;i<=v.tamano;i++) {

			//Si es el último Calendario, que no haga la coma y separación al final.
			if(i==v.tamano) {
				o<<"("<<i<<")"<<" "<<v.c[i-1];
			}

			else {
				o<<"("<<i<<")"<<" "<<v.c[i-1]<<", ";
			}
			
		}

		o<<"]";
	}

	return o;
}

//Comprueba_Rango del Vector de Calendarios
bool TVectorCalendario::Comprueba_Rango(const int index) const {
	bool ok=false;
	
	if(index>=1 && index<=tamano) {
		ok=true;
	}
	return ok;
}

//Copia los Datos.
void TVectorCalendario::Copiar_Datos(const TVectorCalendario &v) {

	tamano=v.tamano;
	error=v.error;

	if(v.c!=NULL) { //Si hay datos en v.c
		c=new TCalendario[tamano]; //Un Vector de Calendarios

		if(c!=NULL) {//Si tamano>1
			for(int i=0;i<tamano;i++) {
				c[i]=v.c[i];
			}
		}

	}
	else { //Si no c=NULL;
		c=NULL;
	}
}





