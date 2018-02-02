#include "tabbcalendario.h"

//----------------------- CLASE TABBCALENDARIO -------------------

//------------- FORMA CANÓNICA --------------

//Consructor Por Defecto
TABBCalendario::TABBCalendario() {

	raiz=NULL;
}

//Constructor De Copia
TABBCalendario::TABBCalendario(const TABBCalendario &c) {

	//Puede ser que *c.raiz y raiz no sea lo mismo
	if(this!=&c) {

		Copiar_arbol(c);

	}
}

//Método para copiar un árbol entero
void TABBCalendario::Copiar_arbol(const TABBCalendario &c) {

	if(EsVacio()) {

		raiz = new TNodoABB();
	}

	if(c.raiz != NULL) {

		TNodoABB *aux = new TNodoABB();
		aux->item = c.raiz->item;

		raiz=aux;

		(raiz->iz).Copiar_arbol(c.raiz->iz);
		(raiz->de).Copiar_arbol(c.raiz->de);

	}

	else {

		raiz=NULL;
	}
}

//Destructor
TABBCalendario::~TABBCalendario() {

	if(raiz != NULL) {

		if(raiz->iz.raiz != NULL) {
			raiz->iz.~TABBCalendario();
		}

		if(raiz->de.raiz != NULL) {

			raiz->de.~TABBCalendario();
		}

		delete raiz;
		raiz= NULL;
	}
}

//Sobrecarga del Operador asignacion
TABBCalendario & TABBCalendario::operator=(const TABBCalendario &c) {

	//Puede ser que *c.raiz y raiz no sea lo mismo
	if(this!=&c) {

		this->~TABBCalendario();
		Copiar_arbol(c);
	}

	return *this;
}

//---------------------- PARTE PÚBLICA -----------------------

//Sobrecarga del operador igualdad
bool TABBCalendario::operator==(const TABBCalendario &c) const{

	//Dos árboles son iguales si poseen los mismos elementos,independientemente de la estructura interna del árbol

	bool ok=true;
	bool equal=true;

	TVectorCalendario v1(Nodos());
	TVectorCalendario v2(c.Nodos());

	//No son iguales si no tienen la misma cantidad de nodos
	if(v1.Tamano() != v2.Tamano()) {
		ok=false;
	}

	else {

		//Compara que en ambos arboles esten los mismos calendarios
		for(int i=0; i<v1.Tamano() && ok; i++) {

			for(int j=0; j<v2.Tamano(); j++) {

				if(v1[i] == v2[j]) {
					
					equal = true;
				}
			}

			if(equal) {

				ok=true;
			}

			else {
				ok=false;
			}
		}

	}
	return ok;
}

//Suma de dos ABB
TABBCalendario TABBCalendario::operator+(const TABBCalendario &arbol) const{

	//Sacamos una copia del operando de la izquierda:
	TABBCalendario mi_arbol;
	mi_arbol=(*this);

	TVectorCalendario v2 = arbol.Inorden();

	for(int x=1; x<=v2.Tamano(); x++) {

		mi_arbol.Insertar(v2[x]);
	}

	return mi_arbol;
}

//Resta de dos ABB
TABBCalendario TABBCalendario::operator-(const TABBCalendario &arbol) const{

	//Creamos un árbol vacío
	TABBCalendario aux;

	TVectorCalendario v1=Inorden(); //Se recorre el operando de la izquierda en inorden

	for(int i=1; i<=v1.Tamano(); i++) {

		if(!arbol.Buscar(v1[i])) {

			aux.Insertar(v1[i]);

		}
	}

	return aux;
}

//Comprueba si el arbol está vacío
bool TABBCalendario::EsVacio() const{

	bool ok=false;

	//El arbol se supondra que esta vacio cuando la raiz dea null
	if(raiz == NULL) {

		ok=true;
	}

	return ok;
}

//Isertar un calendario en el arbol
bool TABBCalendario::Insertar(TCalendario &c) {

	bool ok = false;

	//No puede haber elementos repetidos en el arbol
	if(!Buscar(c)) {

		//Si ya ha llegado a un nodo hoja
		if(raiz == NULL) {

			raiz = new TNodoABB;

			raiz->item = c;

			ok=true;

			//raiz = Nuevo_Nodo(c);
			//ok=true;

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

	return ok;
}

//Devuelve un nodo
TNodoABB * TABBCalendario::Nuevo_Nodo(TCalendario &c) {

	TNodoABB *node = new TNodoABB();

	node->item = c;

	return node;
}

TNodoABB * TABBCalendario::obtenerNodo(const TCalendario &c) {

	TNodoABB * nodo = raiz;

	while(nodo != NULL && nodo->item != c) {

		if(nodo->item < c) {
			nodo = nodo->de.raiz;
		}

		else {
			nodo = nodo->iz.raiz;
		}
	}

	return nodo;
}

TNodoABB * TABBCalendario::obtenerNodoaux(const TNodoABB * nodo) {

	TNodoABB * result = NULL;
	TNodoABB * aux = raiz;

	while(aux != NULL && aux->item!=nodo->item) {
		result = aux;

		if(aux->item < nodo->item) {
			aux = aux->de.raiz;
		}

		else {
			aux = aux->iz.raiz;
		}
	}

	return result;
}

//Borra un calendario del arbol
bool TABBCalendario::Borrar(const TCalendario &c) {

	bool ok = false;

	TNodoABB *nodo = obtenerNodo(c);

	if(nodo != NULL) {
		ok = true;
	}

	if(ok) {
		eliminarNodo(nodo);
	}

	return ok;
}

//Proceso de eliminar un nodo
void TABBCalendario::eliminarNodo(TNodoABB *nodo) {

	if( (nodo->iz).EsVacio() && (nodo->de).EsVacio() ) {

		TNodoABB *first = obtenerNodoaux(nodo);
		if((first->iz).raiz == nodo) {
			(first->iz).raiz = NULL;
		}

		else {
			(first->de).raiz = NULL;
		}

		delete nodo;
		nodo = NULL;
	}

	//Izquierda
	else if ( (nodo->iz).EsVacio() ) {
		TNodoABB *aux = nodo;
		swap(nodo->item, (aux->de).raiz->item);
		aux = (nodo->de).raiz;
		(nodo->de).raiz = NULL;

		delete aux;
		aux = NULL;
	}

	//Derecha
	else if( (nodo->de).EsVacio() ) {
		TNodoABB *second = nodo;
		swap(nodo->item, (second->iz).raiz->item);
		second = (nodo->iz).raiz;
		(nodo->iz).raiz = NULL;

		delete second;
		second = NULL;
	}

	//Ultima oportunidad
	else {

		TNodoABB *aux = (nodo->iz).raiz;

		while( (aux->de).EsVacio() == false ) {

			aux = (aux->de).raiz;
		}

		TCalendario c = aux->item;
		eliminarNodo(aux);
		nodo->item = c;
	}
}

//Encuentra un calendario en el árbol
bool TABBCalendario::Buscar(TCalendario &c) const{

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

//Devuelve la raíz del arbol
TCalendario TABBCalendario::Raiz() const{

	//Si el árbol está vacío, se devuelve un calendario vacío
	if(raiz == NULL) {

		TCalendario c;

		return c;
	}

	else {

		return raiz->item;

	}
}

//Devuelve la altura del árbol
int TABBCalendario::Altura() const{

	int altura=0;
	int sub_iz=0;
	int sub_de=0;

	if(raiz != NULL) {

		sub_iz = raiz->iz.Altura();
		sub_de = raiz->de.Altura();

		if(sub_iz > sub_de) {

			altura = sub_iz;
		}

		else {

			altura = sub_de;
		}

		altura++;
	}

	return altura;
}

//Devuelve la cantidad de nodos del arbol
int TABBCalendario::Nodos() const{

	int nodos=0;
	int first = 1;		//Hay que contar tambien el nodo de la raiz

	if(raiz != NULL) {

		nodos = first + raiz->iz.Nodos() + raiz->de.Nodos();
	}

	return nodos;
}

//Devuelve la cantidad de nodos_hoja del arbol
int TABBCalendario::NodosHoja() const{

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
TVectorCalendario TABBCalendario::Inorden() const{

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCalendario v(Nodos());
	InordenAux(v, posicion);

	return v;
}

//Devuelve el recorrido en Preorden
TVectorCalendario TABBCalendario::Preorden() const{

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCalendario v(Nodos());
	PreordenAux(v, posicion);

	return v;
}

//Devuelve el recorrido en Postorden
TVectorCalendario TABBCalendario::Postorden() const{

	int posicion=1;

	//Vector del tamaño adecuado para almacenar todos los datos
	TVectorCalendario v(Nodos());
	PostordenAux(v, posicion);

	return v;
}

//Devuelve el recorrido en niveles
TVectorCalendario TABBCalendario::Niveles() {
}

int* TABBCalendario::lista_hijos(const TListaCalendario &lista) {

	int *entero = new int[lista.Longitud()];

	//Si el arbol esta vacio se devuelve un vector lleno de 0
	if(EsVacio()) {

		for(int i=0; i<lista.Longitud(); i++) {

			entero[i] = 0;
		}

	}

	//Si la lista está vacía se devuelve null
	if(lista.EsVacia()) {

		entero = NULL;

	}

	else {

		//Primera posicion de la lista
		TListaPos aux = lista.Primera();

		for(int i=0; i<lista.Longitud(); i++) {

			int hijos=0;

			//Deveulve el calendario de esa posicion de la lista
			TCalendario c = lista.Obtener(aux);

			//Si está el elemento
			if(Buscar(c)) {

				TNodoABB *nodo = obtenerNodo(c);

				//2 hijos
				if(nodo->iz.EsVacio() ==false && nodo->de.EsVacio() ==false) {
					
					hijos = 2;
				}

				//1 hijo
				else if(nodo->de.EsVacio() == false || nodo->iz.EsVacio()== false) {

					hijos = 1;
				}

				else {

					hijos = 0;
				}
			}

			entero[i] = hijos;

			aux = aux.Siguiente();
		}
	}

	return entero;
}

// ------------------- PARTE PRIVADA ---------------------

void TABBCalendario::InordenAux(TVectorCalendario &v, int &posicion) const{

	//Recorrido: Izquierda - Raiz - Derecha

	if(raiz != NULL) {

		raiz->iz.InordenAux(v, posicion);
		v[posicion++] = raiz->item;
		raiz->de.InordenAux(v, posicion);
	}
}

void TABBCalendario::PreordenAux(TVectorCalendario &v, int &posicion) const{

	//Recorrido: Raiz - Izquierda - Derecha

	if(raiz != NULL) {

		v[posicion++] = raiz->item;				//Raiz
		raiz->iz.PreordenAux(v, posicion);		//Izquierda
		raiz->de.PreordenAux(v, posicion);		//Derecha

	}
}

void TABBCalendario::PostordenAux(TVectorCalendario &v, int &posicion) const{

	//Recorrido: Izquierda - Derecha - Raíz
	if(raiz != NULL) {

		raiz->iz.PostordenAux(v, posicion);
		raiz->de.PostordenAux(v, posicion);
		v[posicion++] = raiz->item;
	}
}

//Sobrecarga del operador salida
ostream & operator<< (ostream &o,const TABBCalendario &arbol) {

	o<<arbol.Inorden();

	return o;
}

//------------------ CLASE TNODOABB --------------------

//Constructor Por Defecto
TNodoABB::TNodoABB() {
}

//Constructor De Copia
TNodoABB::TNodoABB(const TNodoABB &n) {

	//Si no es lo mismo
	if(this!=&n) {

		item=n.item;
		iz=n.iz;
		de=n.de;

	}
}

//Destructor
TNodoABB::~TNodoABB() {

	//El Destructor libera toda la memoria y pone a NULL

	item.~TCalendario();
	iz.~TABBCalendario();
	de.~TABBCalendario();
}

//Sobrecarga del Operador Asignacion
TNodoABB & TNodoABB::operator=(const TNodoABB &n) {

	//Si no es lo mismo
	if(this!=&n) {

		item=n.item;
		iz=n.iz;
		de=n.de;

	}

	return *this;
}





