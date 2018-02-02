// Aliaga Hyder Alejandro Jes�s 48765284V
#include <iostream>
#include "tabbcom.h"
#include <queue>

// TNodoABB
// constructor por defecto
TNodoABB::
TNodoABB(){}

// constructor copia
TNodoABB::
TNodoABB(const TNodoABB& n)
{
	this->item = n.item;
	this->iz = n.iz;
	this->de = n.de;
}

// desctructor
TNodoABB::
~TNodoABB(){}

// sobrecargar operador asignacion
TNodoABB&
TNodoABB:: operator=(const TNodoABB& n)
{
	return *this;
}



// TABBCom

//constructor por defecto
TABBCom::
TABBCom()
{
	this->nodo = NULL;
}

// constructro copia
TABBCom::
TABBCom(const TABBCom& com)
{
	if (com.nodo != NULL)
		this->nodo = new TNodoABB(*com.nodo);
	else
		this->nodo = NULL;
}

// Destructor
TABBCom::
~TABBCom()
{
}

// sobrecargar operador asignacion
TABBCom &
TABBCom:: operator=(const TABBCom& rp)
{
	nodo = NULL;

	if (rp.nodo)
	{
		this->~TABBCom();
		this->nodo = new TNodoABB(*rp.nodo);
	}

	return *this;
}
// Sobrecarga del operador igualdad
bool
TABBCom:: operator==(const TABBCom& a) const
{
	bool iguales;

	iguales = false;

	if (this->Inorden() == a.Inorden())
		iguales = true;

	return iguales;
}

// Devuelve TRUE si el �rbol est� vac�o, FALSE en caso contrario
bool
TABBCom::EsVacio() const
{
	return nodo == NULL;
}

// Inserta el elemento en el �rbol
bool
TABBCom::Insertar(const TComplejo& c) {
	bool insertado;

	insertado = false;

	if (nodo == NULL)
	{
		this->nodo = new TNodoABB();
		this->nodo->item = c;
		insertado = true;
	}
	else if (!(c == nodo->item))
	{
		if (c.Mod() > nodo->item.Mod() ||
			c.Mod() == nodo->item.Mod() && c.Re() > nodo->item.Re() ||
			c.Mod() == nodo->item.Mod() && c.Re() == nodo->item.Re() ||
			c.Im() > nodo->item.Im())
		{
			insertado = nodo->de.Insertar(c);
		}
		else
			insertado = nodo->iz.Insertar(c);
	}
	return insertado;
}

bool TABBCom::Borrar(const TComplejo &e){
	bool exito;
	TNodoABB *aux;
	TComplejo mayorIzq;

	if(nodo == NULL){
		exito = false;
	}
	else{
		if(e == nodo->item){	
			exito = true;
			if(nodo->iz.EsVacio() && nodo->de.EsVacio()){
				delete nodo;
				nodo = NULL;
			}
			else{
				if(nodo->iz.EsVacio())
				{
					aux = nodo;
					nodo = nodo->de.nodo;
					aux->de.nodo = NULL;						
					delete aux;
					aux = NULL;

				}
				else{
					if(nodo->de.EsVacio())
					{
						aux = nodo;
						nodo = nodo->iz.nodo;
						aux->iz.nodo =NULL;							
						delete aux;
						aux = NULL;
					}
					else
					{
						// arbol con dos hijos.
						// mayor en la izquierda.
						mayorIzq = nodo->iz.BuscarMayor();
						nodo->iz.Borrar(mayorIzq);
						nodo->item = mayorIzq;
					}
				}
			}
		}
		else{		
			if(e.Mod() > nodo->item.Mod() || 
				e.Mod() == nodo->item.Mod() && e.Re() > nodo->item.Re() || 
				e.Mod() == nodo->item.Mod() && e.Re() == nodo->item.Re() && e.Im() > nodo->item.Im())
					exito = nodo->de.Borrar(e);
			else
				exito = nodo->iz.Borrar(e);
		}
	}
	return exito;
}


TComplejo TABBCom::BuscarMayor() const
{
	TComplejo aux;
	if(nodo->de.EsVacio())
		aux = nodo->item;
	else
		aux = nodo->de.BuscarMayor();
	return aux;
}


// Devuelve TRUE si el elemento est� en el �rbol, FALSE en caso contrario
bool
TABBCom::Buscar(const TComplejo& c) const
{
	bool encontrado;

	encontrado = false;

	if (nodo)
	{
		if (c == nodo->item)
			encontrado = true;
		else
			encontrado = nodo->iz.Buscar(c) || nodo->de.Buscar(c);
	}

	return encontrado;
}

// Devuelve el elemento en la ra�z del �rbol
TComplejo
TABBCom::Raiz() const
{
	TComplejo aux;

	if (this->nodo)
		aux = this->nodo->item;

	return aux;
}

// Devuelve la altura del �rbol (la altura de un �rbol vac�o es 0)
int
TABBCom::Altura() const
{
	int altiz;
	int altde;
	int altura;

	if (nodo)
	{
		altde = nodo->de.Altura();
		altiz = nodo->iz.Altura();

		if (altde > altiz)
			altura = altde + 1;
		else
			altura = altiz + 1;
	}
	else
		altura = 0;

	return altura;
}

// Devuelve el n�mero de nodos del �rbol (un �rbol vac�o posee 0 nodos)
int
TABBCom::Nodos() const
{
	int nodos;

	if (nodo)
		nodos = nodo->iz.Nodos() + nodo->de.Nodos() + 1;
	else
		nodos = 0;

	return nodos;
}

// Devuelve el n�mero de nodos hoja en el �rbol (la ra�z puede ser nodo hoja)


int
TABBCom::NodosHoja() const
{
	int hojas;

	if (!nodo)
		return 0;

	if (nodo->de.EsVacio() && nodo->iz.EsVacio())
		return 1;
	else
		return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

// Devuelve el recorrido en inorden
TVectorCom
TABBCom::Inorden() const
{
	int posicion;
	TVectorCom recorrido(Nodos());

	posicion = 1;
	InordenAux(recorrido, posicion);

	return recorrido;
}

// Devuelve el recorrido en preorden
TVectorCom
TABBCom::Preorden() const
{
	int posicion;
	TVectorCom recorrido(Nodos());

	posicion = 1;
	PreordenAux(recorrido, posicion);
	return recorrido;
}

// Devuelve el recorrido en postorden
TVectorCom
TABBCom::Postorden() const
{
	int posicion;
	TVectorCom recorrido(Nodos());

	posicion = 1;
	PostordenAux(recorrido, posicion);
	return recorrido;
}

// Devuelve el recorrido en niveles
TVectorCom
TABBCom::Niveles() const
{
	TVectorCom v(Nodos());
	queue<TNodoABB *> cola;
	
	TNodoABB *aux;
	int i = 1;
	
	if(nodo != NULL)
	{
		cola.push(nodo);
	}
	while(!cola.empty())
	{
		aux = cola.front();
		cola.pop();
		
		v[i] = aux->item;
		i++;
		
		if(aux->iz.nodo != NULL)
			cola.push(aux->iz.nodo);
			
		if(aux->de.nodo != NULL)
			cola.push(aux->de.nodo);
	}
	return v;
}

void TABBCom::InordenAux(TVectorCom& v, int& pos) const
{
	if (this->nodo)
	{
		this->nodo->iz.InordenAux(v, pos);
		v[pos] = nodo->item;
		pos++;
		this->nodo->de.InordenAux(v, pos);
	}
}

void TABBCom::PreordenAux(TVectorCom& v, int& pos) const
{
	if (this->nodo)
	{
		v[pos] = nodo->item;
		pos++;
		this->nodo->iz.PreordenAux(v, pos);
		this->nodo->de.PreordenAux(v, pos);
	}
}

void TABBCom::PostordenAux(TVectorCom& v, int& pos) const
{
	if (this->nodo)
	{
		this->nodo->iz.PostordenAux(v, pos);
		this->nodo->de.PostordenAux(v, pos);
		v[pos] = nodo->item;
		pos++;
	}
}

// Sobrecarga del operador salida
ostream & operator<<(ostream& os, const TABBCom &a)
{
	os << a.Niveles();

	return os;
}



// EXAMEN JUNIO 2017
// FUNCION examen DEVUELVE INT
int TABBCom::examen(const TABBCom& tree)
{
	if (EsVacio() && tree.EsVacio())
		return 4;
		
	else if (EsVacio() || tree.EsVacio())
		return 2;
	
	
	else if (estructura(tree))
	{
		if (tree == *this)
			return 4;
		else
			return 3;
	}
		
	else if (!estructura(tree))
	{
		if (Nodos() == tree.Nodos())
			return 0;
		if (Nodos() > tree.Nodos())
			return 1;
		if (Nodos() < tree.Nodos())
			return 2;
	}
}

bool TABBCom::estructura(const TABBCom& tree)
{
	
	bool rizq = false;
	bool rdrc = false;
	
	// caso base: ninguno tiene hijos
	if (tope(tree))
		return true;
	
	// si tienen misma estructua (mismos hijos)
	else if (ceaux(tree))
	{
		if (!nodo->iz.EsVacio())
			rizq = estructura(tree.nodo->iz);
		
		if (!nodo->de.EsVacio())
			rdrc = estructura(tree.nodo->de);
		
		return rizq and rdrc;
	}
	
	else
		return false;
}

bool TABBCom::tope(const TABBCom& tree)
{
	if (nodo->iz.EsVacio() &&
		nodo->de.EsVacio() &&
		tree.nodo->de.EsVacio() &&
		tree.nodo->iz.EsVacio())
	{
		return true;
	}
	else
		return false;
}

bool TABBCom::ceaux(const TABBCom& tree)
{
	if ( (nodo->iz.EsVacio() && nodo->de.EsVacio() &&
			tree.nodo->iz.EsVacio() && tree.nodo->de.EsVacio()) ||

		(nodo->iz.EsVacio() && !nodo->de.EsVacio() &&
			tree.nodo->iz.EsVacio() && !tree.nodo->de.EsVacio()) ||

		(!nodo->iz.EsVacio() && nodo->de.EsVacio() &&
			!tree.nodo->iz.EsVacio() && tree.nodo->de.EsVacio()) )
	{
		return true;
	}
	else
		return false;
}


int* TABBCom::examen2(const TListaCom& lp) const
{
	int* lista = new int [lp.Longitud()];
	
	int cont = 0;
	
	TListaPos auxpos;
	
	if (lp.Longitud() != 0)
	{
		auxpos = lp.Primera();
		
		while (!auxpos.EsVacia())
		{
			lista[cont] = encontrarCaso(lp.Obtener(auxpos));
	
			auxpos = auxpos.Siguiente();
			cont++;
		}
	}
}

int TABBCom::encontrarCaso(const TComplejo& p) const
{
	if (nodo)
	{
		if (nodo->item.Mod() == p.Mod())
		{
			if (nodo->iz.EsVacio() && nodo->de.EsVacio())
				return 0;
			else if (nodo->iz.EsVacio() && !nodo->de.EsVacio())
				return 1;
			else if (!nodo->iz.EsVacio() && !nodo->de.EsVacio())
				return 2;
		}
		else if (p.Mod() < nodo->item.Mod())
			return nodo->iz.encontrarCaso(p);
		else if (p.Mod() > nodo->item.Mod())
			return nodo->de.encontrarCaso(p);
	}
}





















































