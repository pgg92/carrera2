#include "tlistacom.h"
#include "tcomplejo.h"
#include <iostream>

using namespace std;

// TLISTANODO
TListaNodo::
TListaNodo()
{
	anterior = siguiente = NULL;
}

TListaNodo::
TListaNodo(const TListaNodo &n)
{
	anterior = n.anterior;
	siguiente = n.siguiente;
	e = n.e;
}
TListaNodo::
~TListaNodo()
{
	anterior = siguiente = NULL;
}
TListaNodo &TListaNodo::
operator=(const TListaNodo &n)
{
	if( this != &n )
	{
		e = n.e;
		siguiente = n.siguiente;
		anterior = n.anterior;	
	}
	
	return *this;
}

// TLISTAPOS
TListaPos::
TListaPos()
{
	pos = NULL;
}
TListaPos::
~TListaPos()
{
	pos = NULL;
}
TListaPos::
TListaPos(const TListaPos &p)
{
	pos = p.pos;
}
TListaPos TListaPos::
operator=(const TListaPos &p)
{
	pos = p.pos;
	return *this;
}
bool TListaPos::
operator==(const TListaPos &p) const
{	
	bool equals = false;
	if( pos == p.pos )
		equals = true;
	
	return equals;
}
bool TListaPos::
operator!=(const TListaPos &p) const
{
	bool distinc = false;
	if( pos != p.pos )
		distinc = true;
		
	return distinc;
}
TListaPos TListaPos:: 
Anterior() const
{
	TListaPos aux;
	
	if(pos != NULL)
		aux.pos = pos->anterior;

	return aux;
}

TListaPos TListaPos::
Siguiente() const
{
	TListaPos aux;
	
	if(pos != NULL)
		aux.pos = pos->siguiente;
	
	return aux;
}
bool TListaPos::
EsVacia() const
{
	return pos == NULL;
}

TListaCom::
TListaCom()
{
	primero = ultimo = NULL;
}

TListaCom::
TListaCom(const TListaCom &l)
{
	primero = ultimo = NULL;
        *this = l;
}

TListaCom::
~TListaCom()
{
	TListaNodo *aux;
	
	aux = primero;
	while(primero != NULL)
	{
		primero = primero->siguiente;
		delete aux;
		aux = primero;
	}
	primero = ultimo = NULL;
}
TListaCom &TListaCom::
operator=(const TListaCom &l)
{
	TListaNodo *aux;
	if(this != &l)
	{
		if( EsVacia() == false )
		{
			(*this).~TListaCom();
		}	
		aux = l.ultimo;
		while(aux != NULL)
		{
			InsCabeza(aux->e);
			aux = aux->anterior;
		}		
	}
	return *this;
}
bool TListaCom::
operator==(const TListaCom &l) const
{
	bool equals = true;
	TListaNodo *aux, *laux;
	
	
	if( l.Longitud() == (*this).Longitud() )
	{
		aux = primero;
		laux = l.primero;
		while( aux != NULL && laux != NULL && equals == true )
		{
			if( aux->e != laux->e )
				equals = false;
			else
			{
				aux = aux->siguiente;
				laux = laux->siguiente;
			}
		}	
	}
	else
		equals = false;
	
	return equals;
}
bool TListaCom::
operator!=(const TListaCom &l) const
{
	return !(*this == l);
}

TListaCom TListaCom::
operator+(const TListaCom &l) const
{
	TListaNodo *daux;
	TListaCom nueva(l);
	
	daux = ultimo;
	while( daux != NULL )
	{
		nueva.InsCabeza( daux->e );
		daux = daux->anterior;
	}
	
	return nueva;
}
TListaCom TListaCom:: 
operator-(const TListaCom &l) const
{
	TListaNodo *aux;
	TListaCom nueva;
	
	aux = ultimo;
	while( aux != NULL )
	{
		if( l.Buscar(aux->e) == false )
			nueva.InsCabeza( aux->e );
		aux = aux->anterior;
	}
	
	return nueva;
}
bool TListaCom::
EsVacia() const
{
	bool enc = false;
	if(primero == NULL){
		enc = true;
	}
	return enc;
}
bool TListaCom::
InsCabeza(const TComplejo &c)
{
	bool insertar;
	TListaNodo *nuevo;
	
	insertar = false;
	nuevo = new TListaNodo();
	if( nuevo != NULL )
	{
		insertar = true;
		nuevo->e = c;
		
		if( primero != NULL )
		{
			nuevo->siguiente = primero;
			primero->anterior = nuevo;
			primero = nuevo;
		}	
		else
		{
			primero = nuevo;
			ultimo = nuevo;
		}
	}
	
	return insertar;
}
bool TListaCom::
InsertarI(const TComplejo &c, const TListaPos &p)
{
	bool insertar, encontrado;
	TListaNodo *nuevo, *buscado;
	
	encontrado = false;
	nuevo = new TListaNodo();
	if(nuevo != NULL && p.pos != NULL)
	{
		buscado = primero;
		while( encontrado == false && buscado != NULL)
		{
			if( p.pos == buscado )
				encontrado = true;
			else
				buscado = buscado->siguiente;
		}

		if( encontrado == true )
		{
			insertar = true;
			nuevo->e = c;
			if( p.pos == primero )
			{
				p.pos->anterior = nuevo;
				nuevo->siguiente = p.pos;
				primero = nuevo;
			}
			else
			{
				p.pos->anterior = primero;
				nuevo->siguiente = p.pos;
				p.pos->anterior->siguiente = nuevo;
				nuevo->anterior = p.pos->anterior;
			}
	}
}
	
	return insertar;
}

bool TListaCom::
InsertarD(const TComplejo &c, const TListaPos &p)
{
	bool insertado;
	TListaNodo *nuevo;
	TListaNodo *buscado;
	bool encontrado;
	
	nuevo = new TListaNodo;
	encontrado = false;
	if( nuevo != NULL && p.pos != NULL )
	{
		buscado = primero;
		while( encontrado == false && buscado != NULL)
		{
			if( p.pos == buscado )
				encontrado = true;
			else
				buscado = buscado->siguiente;
		}
		
		if( encontrado == true )
		{
			nuevo = new TListaNodo;	
			insertado = true;
			
			nuevo->e = c;
			nuevo->siguiente = p.pos->siguiente;
			nuevo->anterior = p.pos;
			if( p.pos->siguiente == NULL )
				ultimo = nuevo;
			else
				p.pos->siguiente->anterior = nuevo;
			p.pos->siguiente = nuevo;
		}
	}
	
	return insertado;
}
bool TListaCom::
Borrar(const TComplejo &c)
{
	bool encontrado;
	TListaNodo  *aux,	// al sitio
				*ant,	// al anterior
				*sig;	// al siguiente
				
	aux = primero;
	encontrado = false;
	while(aux != NULL && encontrado == false)
	{
		if(aux->e == c)
			encontrado = true;
		else
			aux = aux->siguiente;
	}
	
	if(encontrado)
	{
		ant = aux->anterior;
		sig = aux->siguiente;

		if(ant != NULL)
			ant->siguiente = sig;
		else
			primero = sig;
		if(sig != NULL)
			sig->anterior = ant;
		else
			ultimo = ant;
		delete aux;
	}
	return encontrado;	
}
bool TListaCom::
BorrarTodos(const TComplejo &c)
{
	bool borrado;
	int borrados;
	
	borrados = 0;
	borrado = false;
	
	while( Borrar(c) == true)
		borrados++;	
	
	if(borrado > 0)
		borrado = true;
		
	return borrado;
	
}

bool TListaCom::
Borrar(TListaPos &p)
{
	bool encontrada = false;
	TListaNodo *ptL, *ptA, *ptS;

	if(!p.EsVacia())
	{
		encontrada = false;
		ptL = primero;
		while(ptL && !encontrada)
		{
			if(ptL == p.pos)
				encontrada = true;
			else
				ptL = ptL->siguiente;
		}
		if(encontrada)
		{
			ptA = ptL->anterior;
			ptS = ptL->siguiente;
			if(ptA)
				ptA->siguiente = ptS;
			else
				primero = ptS;
			if(ptS)
				ptS->anterior = ptA;
			else
				ultimo = ptA;
			delete ptL;
			p.pos = NULL;
		}
	}
	return encontrada;
}

TComplejo TListaCom::
Obtener(const TListaPos &p) const
{
	bool encontrado;
	TComplejo caux;
	TListaNodo *naux;

	encontrado = false;
	naux = primero;
	while( naux != NULL && encontrado == false )
	{
		if( naux == p.pos )
			encontrado = true;
		else
			naux = naux->siguiente;
	}
	if( encontrado == true )
		caux = naux->e;
	
	return caux;
}
bool TListaCom::
Buscar(const TComplejo &c) const
{
	bool find = false;
	TListaNodo *aux;
	
	aux = primero;
	while( aux != NULL && find == false )
	{
		if( aux->e == c )
			find = true;
		aux = aux->siguiente;
	}
	
	return find;
}
int TListaCom:: 
Longitud() const
{
	int nodos = 0;
	TListaNodo *aux;
	
	aux = primero;
	while(aux != NULL)
	{
		aux = aux->siguiente;
		nodos++;
	}
	
	return nodos;
}
TListaPos TListaCom::
Primera() const
{
	TListaPos aux;
	aux.pos = primero;
	return aux;
}
TListaPos TListaCom::
Ultima() const
{
	TListaPos aux;
	aux.pos = ultimo;
	return aux;
}
ostream 
&operator<<(ostream &os, const TListaCom &l)
{
	TListaNodo *aux;

	if( l.primero != NULL )
	{
		os << "{";
		
		aux = l.primero;
		while( aux != NULL )
		{
			os << aux->e;
			if( aux->siguiente )
				os << ' ';
			aux = aux->siguiente;
		}
		os << "}";
	}
	else
		os << "{}";
	
	return os;
}
