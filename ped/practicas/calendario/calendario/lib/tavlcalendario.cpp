//Raimundo Fenoll Albaladejo

#include "tavlcalendario.h"
#include <stdlib.h>
#include "string.h"

//--------------	TNODOAVL    -----------------------

//Constructor por defecto
TNodoAVL::TNodoAVL() {

	//Factor de equilibrio a 0
	fe = 0;
}

//Constructor De Copia
TNodoAVL::TNodoAVL(TNodoAVL &avl) {

	//Si no es lo mismo
	if(this != &avl) {

		item=avl.item;
		iz=avl.iz;
		de=avl.de;
		fe=avl.fe;	
	}
}

//Destructor
TNodoAVL::~TNodoAVL() {

	//El destructor libera toda la memoria y pone a null

	item.~TCalendario();
	iz.~TAVLCalendario();
	de.~TAVLCalendario();

	fe = 0;
}

//Sobrecarga del operador de asignacion
TNodoAVL & TNodoAVL::operator=(TNodoAVL &avl) {

	//Si no es lo mismo
	if(this != &avl) {

		item=avl.item;
		iz=avl.iz;
		de=avl.de;
		fe=avl.fe;
	}

	return *this;
}

//------------------	tavlcalendario    --------------

//Private:

void TAVLCalendario::InordenAux(TVectorCalendario &v, int &posicion) {


	//Recorrido: Izquierda - Raiz - Derecha

	if(raiz != NULL) {

		raiz->iz.InordenAux(v, posicion);
		v[posicion++] = raiz->item;
		raiz->de.InordenAux(v, posicion);
	}
}

void TAVLCalendario::PreordenAux(TVectorCalendario &v, int &posicion) {

	//Recorrido: Raiz - Izquierda - Derecha

	if(raiz != NULL) {

		v[posicion++] = raiz->item;				//Raiz
		raiz->iz.PreordenAux(v, posicion);		//Izquierda
		raiz->de.PreordenAux(v, posicion);		//Derecha

	}
}

void TAVLCalendario::PostordenAux(TVectorCalendario &v, int &posicion) {

	//Recorrido: Izquierda - Derecha - Raíz
	if(raiz != NULL) {

		raiz->iz.PostordenAux(v, posicion);
		raiz->de.PostordenAux(v, posicion);
		v[posicion++] = raiz->item;
	}
}

//Forma Canónica de la clase

//Constructor por defecto
TAVLCalendario::TAVLCalendario() {

	raiz = NULL;
}

//Constructor de copia
TAVLCalendario::TAVLCalendario(TAVLCalendario &avl) {

	//Si no es lo mismo
	if(this != &avl) {

		copiar_arbol(avl);

	}
}

//Copiamos un árbol avl entero
void TAVLCalendario::copiar_arbol(TAVLCalendario &avl) {

	if(EsVacio()) {

		raiz = new TNodoAVL();
	}

	if(avl.raiz != NULL) {

		TNodoAVL *aux = new TNodoAVL();	//Nos creamos un nodo
		aux->item = avl.raiz->item;

		raiz = aux;

		(raiz->iz).copiar_arbol(avl.raiz->iz);
		(raiz->de).copiar_arbol(avl.raiz->de);

	}

	else {

		if(raiz != NULL) {

			(*this).~TAVLCalendario();
		}

		raiz = NULL;
	}
}

//Destructor
TAVLCalendario::~TAVLCalendario() {

	if(raiz != NULL) {

		if(raiz->iz.raiz != NULL) {
			raiz->iz.~TAVLCalendario();
		}

		if(raiz->de.raiz != NULL) {

			raiz->de.~TAVLCalendario();
		}

		delete raiz;
		raiz= NULL;
	}
}

//Sobrecarga del operador asignacion
TAVLCalendario & TAVLCalendario::operator=(TAVLCalendario &avl) {

	//Llamamos al destructor para que libere toda la memoria
	(*this).~TAVLCalendario();

	if(this != &avl) {

		copiar_arbol(avl);
	}

	return *this;
}

bool TAVLCalendario::operator==(TAVLCalendario &avl) {

		if(avl.Nodos() == this->Nodos()) {

		int aux = Nodos();

		TVectorCalendario vector1(Preorden());
		TVectorCalendario vector2(avl.Preorden());

		return vector1 == vector2;
		}
}

//Dos arboles avl no son iguales
bool TAVLCalendario::operator!=(TAVLCalendario &avl) {

	if(operator==(avl)) {
		return false;
	}

	return true;
}

//Comprueba si el arbol esta vacio
bool TAVLCalendario::EsVacio() {

	if(raiz==NULL) {
		return true;
	}

	return false;
}

//Inserta un calenadario en el arbol. Llama a InsertarAux
bool TAVLCalendario::Insertar(TCalendario &c) {

	bool ok = false;

	//No puede haber elementos repetidos en el arbol

	//No puede haber elementos repetidos en el arbol
	if(!Buscar(c)) {

		//Si ya ha llegado a un nodo hoja
		if(raiz == NULL) {

			raiz = new TNodoAVL;

			raiz->item = c;

			ok=true;

		}

		else {

			if(c < (raiz->item) ) {

				ok = (raiz->iz).Insertar(c);

			}

			else if(c > (raiz->item) ) {

				ok = (raiz->de).Insertar(c);
			}

			else {

				ok=false;
			}
		}
	}

	Equilibrar();

	return ok;
}

//Equilibramos por la izquierda
void TAVLCalendario::Equilibrar() {

	TNodoAVL *nodo;

	if( raiz != NULL )
	{
		raiz->fe = raiz->de.Altura() - raiz->iz.Altura();

		if (raiz->fe > 1)
		{
			if (raiz->de.raiz->fe >= 0) {
				nodo = raiz->de.raiz;
				raiz->de.raiz = raiz->de.raiz->iz.raiz;
				nodo->iz.raiz = raiz;
				raiz = nodo;                     
			}

			else {
				nodo = raiz->de.raiz;
				raiz->de.raiz = nodo->iz.raiz->iz.raiz;
				nodo->iz.raiz->iz.raiz = raiz;
				raiz = nodo->iz.raiz;
				nodo->iz.raiz = raiz->de.raiz;
				raiz->de.raiz = nodo;
			}

			raiz->fe = raiz->de.Altura() - raiz->iz.Altura();

			if (raiz->iz.raiz != NULL) {
				raiz->iz.raiz->fe = raiz->iz.raiz->de.Altura() - raiz->iz.raiz->iz.Altura();                    
			}

			if (raiz->de.raiz != NULL) {
				raiz->de.raiz->fe = raiz->de.raiz->de.Altura() - raiz->de.raiz->iz.Altura();
			}

		}

		else if (raiz->fe < -1) {

			if (raiz->iz.raiz->fe <= 0) {
				nodo = raiz->iz.raiz;
				raiz->iz.raiz = raiz->iz.raiz->de.raiz;
				nodo->de.raiz = raiz;
				raiz = nodo;
			}

			else {

				nodo = raiz->iz.raiz;
				raiz->iz.raiz = nodo->de.raiz->de.raiz;
				nodo->de.raiz->de.raiz = raiz;
				raiz = nodo->de.raiz;
				nodo->de.raiz = raiz->iz.raiz;
				raiz->iz.raiz = nodo;                                                    
				
			}

			raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
			raiz->iz.raiz->fe = raiz->iz.raiz->de.Altura() - raiz->iz.raiz->iz.Altura();
			raiz->de.raiz->fe = raiz->de.raiz->de.Altura() - raiz->de.raiz->iz.Altura();
		}
	}
}

//Crea un nuevo nodo
TNodoAVL * TAVLCalendario::Nuevo_Nodo(TCalendario &c) {

	TNodoAVL *node = new TNodoAVL();

	node->item = c;

	return node;
}

//Busca un calendario en el arbol
bool TAVLCalendario::Buscar(TCalendario &c) {

	bool ok = false;

	if(raiz!=NULL) {

		if(raiz->item == c) {

			ok = true;
		}

		else {

			if(c < (raiz->item)) {

				ok = (raiz->iz).Buscar(c);
			}

			else {

				ok = (raiz->de).Buscar(c);
			}
		}
	}

	return ok;
}

//Altura del arbol
int TAVLCalendario::Altura() {

	int iz = 0;
	int de = 0;

	if(raiz != NULL) {

		iz = (raiz->iz).Altura();
		de = (raiz->de).Altura();

		if(iz < de) {

			return 1 + de;
		}

		else {
			return 1 + iz;
		}
	}

	return 0;
}

//Devuelve el numero de nodos del arbol
int TAVLCalendario::Nodos() {

	int nodos=0;
	int first = 1;		//Hay que contar tambien el nodo de la raiz

	if(raiz != NULL) {

		nodos = first + raiz->iz.Nodos() + raiz->de.Nodos();
	}

	return nodos;
}

//Devuelve el numero de nodos hoja del arbol
int TAVLCalendario::NodosHoja() {

	int nodos_hoja = 0;

	if(raiz != NULL) {

		//Es nodo hoja cuando cumple estas condiciones (cuando encuentre el ultimo nodo hoja, raiz si que sera entonces NULL)
		if(raiz->iz.raiz == NULL && raiz->de.raiz == NULL) {

			nodos_hoja=1;
		}

		//Seguimos buscando.
		else {

			nodos_hoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();

		}
	}

	return nodos_hoja;
}

//Devuelve el recorrido en inorden
TVectorCalendario TAVLCalendario::Inorden() {

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCalendario v(Nodos());
	InordenAux(v, posicion);

	return v;
}

//Devuelve el recorrido en preorden
TVectorCalendario TAVLCalendario::Preorden() {

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCalendario v(Nodos());
	PreordenAux(v, posicion);

	return v;
}

//Devuelve el recorrido en postorden
TVectorCalendario TAVLCalendario::Postorden() {

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los datos
	TVectorCalendario v(Nodos());
	PostordenAux(v, posicion);

	return v;
}

//Borra un calendario
bool TAVLCalendario::Borrar(TCalendario &c) {
}

//Devuelve la raiz del arbol
TCalendario TAVLCalendario::Raiz() {

	//Si el arbol está vacío, que devuelva un calendario vacío

	if(raiz == NULL) {

		TCalendario c;

		return c;
	}

	else {

		return raiz->item;
	}
}

//Sobrecarga del operador salida
ostream & operator<<(ostream &o, TCalendario &c) {
}


