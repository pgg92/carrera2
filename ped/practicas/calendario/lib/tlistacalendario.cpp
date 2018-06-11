//Raimundo Fenoll Albaladejo

#include "tlistacalendario.h"

#include <stdlib.h>
#include "string.h"

//------------------------TLISTACALENDARIO------------------

//Constructor por Defecto
TListaCalendario::TListaCalendario() {

	//Creamos una Lista Vacía cuando el puntero que accede a la lista (el primero) vale null
	primero=NULL;
}

//Constructor de Copia
TListaCalendario::TListaCalendario(const TListaCalendario &l) {

	TListaPos actual;
	TListaPos anterior;

	if(this!=&l) {

		primero=new TNodoCalendario(*l.primero);
		anterior=l.Primera();
		actual=l.Primera();
		actual=actual.Siguiente();

		if(actual.pos!=NULL) {

			while(actual.pos!=NULL) {

				anterior.Siguiente();
				anterior.pos=new TNodoCalendario(*actual.pos);
				anterior=actual;
				actual=actual.Siguiente();
			}
		}
	}
}

//Destructor
TListaCalendario::~TListaCalendario() {

	//Puntero a Nodo Auxiliar (apunta a null)
	TNodoCalendario *auxiliar=NULL;

	while(!EsVacia()) {

		auxiliar=primero;
		primero=primero->siguiente;
		delete auxiliar;

	}
}

//Sobrecarga del Operador Asignación
TListaCalendario & TListaCalendario::operator=(const TListaCalendario &l) {

	TListaPos anterior;

	if(this!=&l) {

		//(*this).~TListaCalendario();
		anterior=l.Primera();

		while(!anterior.EsVacia()) {

			//Vamos insertando en this todos los nodos
			//Obtener(anterior) nos devuelve un nodo
			this->Insertar(Obtener(anterior));
			anterior=anterior.Siguiente();
		}
	}

	return *this;
}

//Sobrecarga del Operador Igualdad
bool TListaCalendario::operator==(const TListaCalendario &l) {

	bool ok=true;
	TListaPos list=l.Primera();
	TListaPos mylist=Primera();
	int length=l.Longitud();
	int my_length=Longitud();

	//Basta con que no tengan la misma longitud para que no sean iguales
	if(length!=my_length) {
		ok=false;
	}

	else {

		while(ok && !list.EsVacia() && !mylist.EsVacia()) {

			if(Obtener(list)!=Obtener(mylist)) {

				ok=false;

			}

			else {
				list=list.Siguiente();
				mylist=mylist.Siguiente();
			}
		}

	}
}

//Sobrecarga del Operador Suma
TListaCalendario TListaCalendario::operator+(const TListaCalendario &l) {

	TListaCalendario list;
	TListaPos position;

	if(!l.EsVacia()) {

		list=*this; //Copiamos en list en contenido de esta clase
		position=l.Primera();

		while(!list.EsVacia()) {

			//Sobre nuestra lista (list), vamos insertando los calendarios de l
			list.Insertar(Obtener(position));
			position=position.Siguiente();

		}

	}

	else {
		list=l;
	}

	return list;
}

//Sobrecarga del Operador Resta
TListaCalendario TListaCalendario::operator-(const TListaCalendario &l) {
	
	TListaCalendario list;
	TListaPos position;

	list=*this;

	while(!position.EsVacia()) {

		list.Borrar(Obtener(position));
		position=position.Siguiente();
	}

	return list;
}

//Inserta un Calendario en la Lista
bool TListaCalendario::Insertar(const TCalendario &c) {

	bool ok=false;
	TListaPos actual;
	TListaPos anterior;

	if(EsVacia()) {

		TNodoCalendario *nodo=new TNodoCalendario(); //Nos Creamos Un puntero a un Nodo
		nodo->c=c; //Su Calendario será el qe se pasa por parámetro
		primero=nodo; //Primero apuntará a ese nodo
		ok=true; //Modificamos
	}

	else if(!Buscar(c)){

			//Comprobemos en que posicion debe quedarse el calendario
			actual=Primera();

			while(!ok && !actual.EsVacia()) {

				//Si entra en la Primera iteracion, el caledario se inserta al principio de la lista
				if(Obtener(actual)>c) {
					ok=true;
				}

				//Incrementamos el puntero (Actualizamos)
				else {
					anterior=actual;
					actual=actual.Siguiente();
				}

			}

			if(ok||anterior==Ultima()) {

				//Insertando al Principio de la lista
				if(anterior.EsVacia()) {
					TNodoCalendario *nodo=new TNodoCalendario();
					nodo->c=c;
					nodo->siguiente=actual.pos;
					primero=nodo;
				}

				//Insertando al Final de la lista
				else if(anterior==Ultima()) {
					TNodoCalendario *nodo=new TNodoCalendario();
					nodo->c=c;
					nodo->siguiente=NULL;
					anterior.pos->siguiente=nodo;
				}

				//Insertando por en medio
				else {
					
					TNodoCalendario *nodo=new TNodoCalendario();
					nodo->c=c;
					nodo->siguiente=actual.pos;
					anterior.pos->siguiente=nodo;
				}

			}
			

		}

	return ok;
}

//Borra un Calendario de la lista
bool TListaCalendario::Borrar(const TCalendario &c) {

	bool ok=false;
	TListaPos anterior=Primera();
	TListaPos actual=Primera();

	//Si la lista no está vacia
	if(!EsVacia()) {

		//Obviamente borra algo que encuentres
		if(Buscar(c)) {

			//Encuentra el calendario en primer lugar
			if(Obtener(actual)==c) {

				ok=true;

				primero=primero->siguiente;
				delete actual.pos;

			}

			//Lo va encontrando a medio recorrido
			else {

				//Incrementa de Posicion
				actual=actual.Siguiente();

				while(actual.pos!=NULL && ok==false) {

					if(Obtener(actual)==c) {

						ok=true;

						anterior.pos->siguiente=actual.pos->siguiente;
						delete actual.pos;
					}

					else {

						anterior=actual;
						actual=actual.Siguiente();

					}

				}

			}

		}

	}

	return ok;
}

//Borra una posicion de la lista
bool TListaCalendario::Borrar(const TListaPos &p) {

	bool ok=false;

	TListaPos anterior=Primera();
	TListaPos actual=Primera();

	//Si la lista no está vacía
	if(!EsVacia()) {

		//Si coincide con la primera posicion
		if(p==actual) {

			primero=primero->siguiente;
			delete actual.pos;
		}

		//Si no lo encontrará por enmedio
		else {

			anterior=actual;
			actual=actual.Siguiente();

			while(!actual.EsVacia() && !ok) {

				//Por fin lo ha encontrado
				if(p==actual) {

					ok=true;

					actual.pos->siguiente=actual.pos->siguiente;
					delete actual.pos;
				}

				//Sigue Buscando
				else {

					anterior=actual;
					actual.pos=actual.pos->siguiente;
				}

			}
		}
	}

	return ok;
}

//Borra todos los calendarios con fecha anterior a la pasada
bool TListaCalendario::Borrar(const int d, const int m, const int a) {

	//Nos declaramos un nuevo calendario
	TCalendario cal(d,m,a,"");

	TListaPos actual;
	TListaPos anterior;
	actual.pos=primero;

	bool ok=false;
	bool aux=false;

	//Debe haber al menos algo en la Lista
	if(!EsVacia()) {

		//Ya es mayor el calendario en la primera posicion de la lista
		if(cal>primero->c) {

			ok=true;

			primero=primero->siguiente;
			delete actual.pos;

		}

		else {

			anterior=actual;
			actual=actual.Siguiente();

			while(actual.pos!=NULL) {

				if(cal>actual.pos->c && !aux) {

					ok = true;

					anterior.pos->siguiente=actual.pos->siguiente;
					delete actual.pos;
					anterior=actual;
					actual.pos=actual.pos->siguiente;

					ok=true;
				}

				else {
					aux=true;
				}

			}

		}
	}

	return ok;
}

//EsVacia devuelve true cuando el primer puntero es NULL
bool TListaCalendario::EsVacia() const{

	bool ok=false;

	if(primero==NULL) {
		ok=true;
	}

	return ok;
}

//Obtiene el elemento que ocupa la posición indicada
TCalendario TListaCalendario::Obtener(const TListaPos &p) const {

	if(!p.EsVacia()) {

		return p.pos->c;
	}
}

//Busca un Calendario en la Lista
bool TListaCalendario::Buscar(const TCalendario &cal) const{

	bool ok=false;

	if(!EsVacia()) {

		TListaPos pointer;

		for(pointer.pos = primero; pointer.pos!=NULL && ok==false; pointer.pos=pointer.pos->siguiente) {

			//Si encuentra el calendario del parámetro en la Lista
			if(pointer.pos->c==cal) {
				ok=true;
			}
		}
	}

	return ok;
}

//Devuelve la longitud de la lista
int TListaCalendario::Longitud() const {

	int length=0;
	TListaPos lp;
	lp.pos=primero;

	//Hasta que no llegue al final
	while(lp.pos!=NULL) {

		length++;
		lp.pos=lp.pos->siguiente;

	}

	return length;
}

//Devuelve la Primera posición de la Lista
TListaPos TListaCalendario::Primera() const {

	TListaPos lp; //lp por defecto ya se pone a NULL

	//Si mi lista no esta vacia
	if(!EsVacia()) {

		//Primer puntero de la lista
		lp.pos=primero;

	}

	return lp;
}

//Devuelve la Ultima posicion de la Lista
TListaPos TListaCalendario::Ultima() const {

	TListaPos actual, anterior;
	actual.pos=primero; //actual pasa a ser primero

	if(!EsVacia()) {

		//Hacer Traza
		while(actual.pos!=NULL) {

			anterior=actual;
			actual.pos=actual.pos->siguiente;

		}

	}

	//La ultima Posicion de la lista es el puntero que hay entre
	//El penúltimo y el último nodo.
	return anterior;
}

TListaCalendario TListaCalendario::SumarSubl(const int I_L1, const int F_L1, const TListaCalendario &L2, const int I_L2, const int F_l2) {
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2) {
}

//Ostream. Sobrecarga de Salida
ostream & operator<<(ostream &o, const TListaCalendario &l) {

	TListaPos actual=l.Primera();

	//Si la Lista está vacia, que devuelva <>
	if(l.EsVacia()) {
		o<<"<>";
	}

	//Si la lista no está vacia, entonces que vaya
	//mostrando los mensajes
	else {

		o<<"<";

		while(!actual.EsVacia()) {

			o << l.Obtener(actual);
			actual=actual.Siguiente();

			if(!actual.EsVacia()) {
				
				o << " ";

			}
		}

		o<<">";
	}

	return o;
}

//----------------------TLISTAPOS-----------------------

//Constuctor por Defecto. HECHO
TListaPos::TListaPos(){

	pos=NULL;
}

//Constructor de Copia. HECHO
TListaPos::TListaPos(const TListaPos &l) {

	if(this!=&l) {

		if(pos!=NULL) {
			delete pos;
		}

		else {

			pos=l.pos;
		}

	}
}

//Destructor. HECHO
TListaPos::~TListaPos() {

	//Pos se inicializa a NULL
	pos=NULL;
}

//Sobrecarga del Operador Asignación. HECHO
TListaPos & TListaPos::operator=(const TListaPos &l) {

	//Si no es el mismo objeto, entra
	if(this!=&l) {

		if(this!=NULL) {
			pos=l.pos;
		}
		
	}

	return *this;
}

//Sobrecarga del Operador Igualdad. HECHO
bool TListaPos::operator==(const TListaPos &p) const{

	bool ok=false;

	if(pos==p.pos) {
		ok=true;
	}

	return ok;
}

//Sobrecarga del Operador Desigualdad. HECHO
bool TListaPos::operator!=(const TListaPos &p) const{

	bool ok=false;

	if(pos!=p.pos) {
		ok=true;
	}

	return ok;
}

//Devuelve La Posición Siguiente. HECHO
TListaPos TListaPos::Siguiente() const {

	TListaPos posicion; //Posicion Vacia

	//Si no es el ultimo de la lista
	if(pos!=NULL || pos==NULL) {
		posicion.pos=pos->siguiente;
	}

	return posicion;
}

//Posición Vacía. HECHO
bool TListaPos::EsVacia() const {

	bool ok=false;

	if(pos==NULL) {
		ok=true;
	}

	return ok;
}

//--------------------TNODOCALENDARIO----------------

//Constructor por Defecto. HECHO
TNodoCalendario::TNodoCalendario(){

	siguiente=NULL;
}

//Constructor De Copia. HECHO.
TNodoCalendario::TNodoCalendario(const TNodoCalendario &n) {

	if(this!=&n) { //Si no es el mismo objeto

		if(siguiente!=NULL) {

			delete siguiente; //elimina el puntero
		}

		c=n.c;
		siguiente=n.siguiente;
	}
}

//Destructor. HECHO
TNodoCalendario::~TNodoCalendario(){
	
	siguiente=NULL;
}

//Sobrecarga Del Operador Asignación. HECHO
TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &n) {

	if(this!=&n) {

		if(siguiente!=NULL) {

			delete siguiente; //elimina el puntero
		}

		if(this!=NULL) {
			c=n.c;
			siguiente=n.siguiente;

		}
	}

	return *this;
}








