
#include "tavlcom.h"

// class TNodoAVL
#pragma region NODO

// Constructor por defecto
TNodoAVL::TNodoAVL() 
{
	fe = 0;
}

// Constructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL& nodo)
	:iz( nodo.iz ), de( nodo.de ), item( nodo.item ), fe( nodo.fe ) {}

// Destructor
TNodoAVL::~TNodoAVL() 
{
	item.~TComplejo();
	iz.~TAVLCom();
	de.~TAVLCom();
	fe = 0;
}

// Sobrecarga del operador asignación
TNodoAVL& TNodoAVL::operator=(const TNodoAVL &arbol)
{
	if (this != &arbol)
	{
		iz = arbol.iz;
		de = arbol.de;
		item = arbol.item;
		fe = arbol.fe;
	}
	return *this;
}

#pragma endregion

// class TAVLCom
#pragma region AVL

#pragma region canonica / asignacion

// Constructor por defecto
TAVLCom::TAVLCom()
{
	raiz = NULL;
}

// Constructor de copia
TAVLCom::TAVLCom(const TAVLCom& tree)
{
	if (tree.raiz)
		this->raiz = new TNodoAVL(*tree.raiz);

	else
		this->raiz = NULL;
}

// Destructor
TAVLCom::~TAVLCom()
{
	delete raiz;
	raiz = NULL;
}

// Sobrecarga del operador asignación
TAVLCom & TAVLCom::operator=(const TAVLCom& tree)
{
	if (this != &tree)
	{
		this->~TAVLCom();

		if (tree.raiz != NULL)
		{
			raiz = new TNodoAVL;
			*raiz = *(tree.raiz);
		}
	}

	return *this;
}
#pragma endregion

#pragma region sobrecargas

// Sobrecarga del operador igualdad
bool TAVLCom::operator==(const TAVLCom& tree) const
{
	bool equals;

	equals = this->Inorden() == tree.Inorden();

	return equals;
}
// Sobrecarga del operador desigualdad
bool TAVLCom::operator!=(const TAVLCom& tree) const
{
	return !(*this == tree);
}
#pragma endregion

// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCom::EsVacio() const
{
	return !raiz;
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TAVLCom::Buscar(const TComplejo &c)
{
	bool encontrado;

	if(raiz != NULL)
		encontrado = raiz->iz.Buscar(c) || raiz->de.Buscar(c) || raiz->item == c;
	else
		encontrado = false;
	
	return encontrado;
}

#pragma region obtenerCaracteristicas
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TAVLCom::Altura() const
{
	int altiz;
	int altde;
	int altura = 0;

	if (raiz)
	{
		altde = raiz->de.Altura();
		altiz = raiz->iz.Altura();

		if (altde > altiz)
			altura = altde + 1;
		else
			altura = altiz + 1;
	}

	return altura;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TAVLCom::Nodos() const
{
	int nodos;

	if (!raiz)
		nodos = 0;
	else
		nodos = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
	return nodos;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TAVLCom::NodosHoja() const
{
	int nodosHoja;
	
	if (!raiz)
		nodosHoja = 0;
	else if (raiz->de.EsVacio() && raiz->iz.EsVacio())
	{
		nodosHoja = 1;
	}
	else
		nodosHoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();

	return nodosHoja;
}
// Devuelve el elemento TComplejo raíz del árbol AVL
TComplejo TAVLCom::Raiz() const
{
	TComplejo aux;

	if (this->raiz)
		aux = this->raiz->item;

	return aux;
}

// funciones auxiliares para evitar espaguetis
bool TAVLCom::esHoja() const
{
	bool hoja = false;

	if (raiz->de.EsVacio() && raiz->iz.EsVacio())
		hoja = true;

	return hoja;
}
bool TAVLCom::soloIzquierdo() const
{
	bool soloizq = false;

	if (this->raiz->de.EsVacio() && !(this->raiz->iz.EsVacio()))
		soloizq = true;

	return soloizq;
}
bool TAVLCom::estafull() const
{
	bool soloizq = false;

	if (!(this->raiz->de.EsVacio()) && !(this->raiz->iz.EsVacio()))
		soloizq = true;

	return soloizq;
}
#pragma endregion

#pragma region borrar

bool TAVLCom::Reestructuracion(bool& borrado,
															 bool& decreceDe,
															 bool& decreceIz,
															 bool& decrece
															 )
{
	// si se ha borrado comprobamos factores de equilibrio
	if(borrado)
	{
		// si decrece por la izquierda
		if(decreceIz)
		{
			raiz->fe++;
			
			if(raiz->fe == 0)
				decrece = true;
				
			else if(raiz->fe == 1)
				decrece = false;
				
			else if(raiz->fe == 2)
			{
				if (raiz->de.raiz->fe == -1)
				{
					DI();
					decrece = true;
				}
				else if (raiz->de.raiz->fe == 0)
				{
					DD();
					decrece = false;
				}
				else if (raiz->de.raiz->fe == 1)
				{
					DD();
					decrece = true;
				}
			}

		}
		
		// si decrece por la derecha
		else if(decreceDe)
		{
			raiz->fe--;
			
			if(raiz->fe == 0)
				decrece = true;
				
			else if(raiz->fe == -1)
					decrece = false;
					
			else if(raiz->fe == -2)
			{
				if(raiz->iz.raiz->fe == -1)
				{
					II();
					decrece = true;
				}
				else if(raiz->iz.raiz->fe == 0)
				{
					II();
					decrece = false;
				}
				else if(raiz->iz.raiz->fe == 1)
				{
					ID();
					decrece = true;
				}
			}
		}
	}
}

bool TAVLCom::Borrar(const TComplejo& c)
{
	bool decrece = false;

	return BorrarAux(c, decrece);
}
bool TAVLCom::BorrarAux(const TComplejo& c, bool& decrece)
{
	TNodoAVL *nodoraiz;
	TNodoAVL *nodob;

	TComplejo mayorIz;
	
	bool borrado = false;
	bool decreceiz = false;
	bool decrecede = false;

	if(raiz)
	{
		// PROCESO1 : Borrado
		// SI no es el nodo buscado
		if (c.Mod() < raiz->item.Mod())
		{
			borrado = raiz->iz.BorrarAux(c, decreceiz);
		}
		else if (c.Mod() > raiz->item.Mod())
		{
			borrado = raiz->de.BorrarAux(c, decrecede);
		}
		// si es el nodo buscado
		else if (this->raiz->item == c)
		{
			// hoja: borrar
			if (this->esHoja())
			{
				delete raiz;
				raiz = NULL;
				decrece = true;
				borrado = true;
			}
			// solo hijo izquierdo:
			else if (this->soloIzquierdo())
			{
				raiz = raiz->iz.raiz;
				decrece = true;
				borrado = true;
			}
			// dos hijos: criterio mayor izquierda
			else if (this->estafull())
			{
				mayorIz = raiz->iz.BuscarMayor();
				nodoraiz = raiz;
				borrado = BorrarAux(mayorIz, decrece);
				nodoraiz->item = mayorIz;
			}
			// solo hijo derecho:
			else
			{
				raiz = raiz->de.raiz;
				decrece = true;
				borrado = true;
			}
		}
		
		// comprobar factor equilibrio una vez borrado
		Reestructuracion(borrado, 
										 decrecede,
										 decreceiz,
										 decrece);
	}
	return borrado;
}


TComplejo TAVLCom::BuscarMayor() const
{
	TComplejo mayor;
	if (raiz)
		if (raiz->de.raiz)
			mayor = raiz->de.BuscarMayor();
		else
			mayor = raiz->item;
	return mayor;

}


#pragma endregion

#pragma region recorridos
// Devuelve el recorrido en inorden sobre un vector
TVectorCom TAVLCom::Inorden() const
{
	// posicion en el vector que almacena el recorrido
	int posicion = 1;

	//vector del tamaño adecuado para almacenar todos los nodos
	TVectorCom v(Nodos());

	InordenAux(v, posicion);

	return v;
}

// Devuelve el recorrido en preorden sobre un vector
TVectorCom TAVLCom::Preorden() const
{
	int posicion = 1;

	TVectorCom v(Nodos());

	PreordenAux(v, posicion);

	return v;
}

// Devuelve el recorrido en postorden sobre un vector
TVectorCom TAVLCom::Postorden() const
{
	int posicion = 1;

	TVectorCom v(Nodos());

	PostordenAux(v, posicion);

	return v;
}

// AUXILIAR : Devuelve el recorrido en inorden
void TAVLCom::InordenAux(TVectorCom& v, int& pos) const
{
	if (this->raiz)
	{
		this->raiz->iz.InordenAux(v, pos);
		v[pos] = raiz->item;
		pos++;
		this->raiz->de.InordenAux(v, pos);
	}
}

// AUXILIAR : Devuelve el recorrido en preorden
void TAVLCom::PreordenAux(TVectorCom& v, int& pos) const
{
	if (this->raiz)
	{
		v[pos] = raiz->item;
		pos++;
		this->raiz->iz.PreordenAux(v, pos);
		this->raiz->de.PreordenAux(v, pos);
	}
}

// AUXILIAR : Devuelve el recorrido en postorden
void TAVLCom::PostordenAux(TVectorCom& v, int& pos) const
{
	if (this->raiz)
	{
		this->raiz->iz.PostordenAux(v, pos);
		this->raiz->de.PostordenAux(v, pos);
		v[pos] = raiz->item;
		pos++;
	}
}
#pragma endregion

#pragma region insertar

// Inserta el complejo en el árbol
bool TAVLCom::Insertar(const TComplejo& complejo)
{
	bool insertar;
	bool crece;

	insertar = insertaraux(complejo,crece);

	return insertar;
}

// realizar inserccion en el arbol, devuelve un booleano
bool TAVLCom::insertaraux(const TComplejo& c, bool &crece)
{
    bool insertado = false;
    bool creceiz = false;
    bool crecede = false;
 
    if (c.Re() != 0 || c.Im() != 0)
    // si el arbol esta vacio insertar c
    if (EsVacio())
    {
        raiz = new TNodoAVL;
        raiz->fe = 0;
        raiz->item = c;
        insertado = true;
        crece = true;
    }
    // si tienen distinta raiz
    else if (raiz->item.Mod() != c.Mod())
    {
        // si this es menor insertar derecha
        if (c.Mod() > raiz->item.Mod())
        {
            insertado = raiz->de.insertaraux(c, crecede);
        }
        // si this es mayor insertar izquierda
        else if (c.Mod() < raiz->item.Mod())
        {
            insertado = raiz->iz.insertaraux(c, creceiz);
        }
        if (creceiz)
        {
            raiz->fe--;
            if (raiz->fe == 0)
                crece = false;
            if (raiz->fe == -1)
                crece = true;
            if (raiz->fe == -2)
            {
                crece = false;
                if (raiz->iz.raiz->fe == -1)
                    II();
                if (raiz->iz.raiz->fe == 1)
                    ID();
            }
        }
        else
        {
            if (crecede)
            {
                raiz->fe++;
                if (raiz->fe == 0)
                    crece = false;
                if (raiz->fe == 1)
                    crece = true;
                if (raiz->fe == 2)
                {
                    crece = false;
                    if (raiz->de.raiz->fe == -1)
                        DI();
                    if (raiz->de.raiz->fe == 1)
                        DD();
                }
            }
        }
    }
    else
    {
        insertado = false;
        crece = false;
    }
 
    return insertado;
}

// insertar II
void TAVLCom::II()
{
	// TNodoAVL auxiliar
	TNodoAVL *nodoraiz;

	// reordenacíon
	nodoraiz = this->raiz;
	this->raiz = nodoraiz->iz.raiz;
	nodoraiz->iz.raiz = this->raiz->de.raiz;
	this->raiz->de.raiz = nodoraiz;

	// recalcular f.equilibrio
	if (raiz->fe == 0)
	{
		this->raiz->fe = 1;
		this->raiz->de.raiz->fe = -1;
	}
	else
	{
		this->raiz->fe = 0;
		this->raiz->de.raiz->fe = 0;
	}
}

void TAVLCom::ID()
{
	TNodoAVL *auxR, *auxIz, *auxDe;
	
	auxR = raiz;
	raiz = raiz->iz.raiz->de.raiz;
	auxIz = raiz->iz.raiz;
	auxDe = raiz->de.raiz;
	raiz->iz.raiz = auxR->iz.raiz;
	raiz->de.raiz = auxR;
	auxR->iz.raiz = auxDe;
	raiz->iz.raiz->de.raiz = auxIz;
	if(raiz->fe == 0)
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	else
		if(raiz->fe == -1)
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;	
			raiz->de.raiz->fe = 0;	
		}
}

void TAVLCom::DI()
{
	TNodoAVL *auxR, *auxIz, *auxDe;
	
	auxR = raiz;
	raiz = raiz->de.raiz->iz.raiz;
	auxIz = raiz->iz.raiz;
	auxDe = raiz->de.raiz;
	raiz->de.raiz = auxR->de.raiz;
	raiz->iz.raiz = auxR;
	auxR->de.raiz = auxIz;
	raiz->de.raiz->iz.raiz = auxDe;
	if(raiz->fe == 0)
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	else
		if(raiz->fe == -1)
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;
			raiz->de.raiz->fe = 0;	
		}
}

void TAVLCom::DD()
{
	// TNodoAVL auxiliar
	TNodoAVL *nodoraiz;

	// reordenacíon
	nodoraiz = raiz;
	raiz = nodoraiz->de.raiz;
	nodoraiz->de.raiz = raiz->iz.raiz;
	this->raiz->iz.raiz = nodoraiz;

	// recalcular f.equilibrio
	if (raiz->fe == 0)
	{
		raiz->fe = -1;
		raiz->iz.raiz->fe = 1;
	}
	else
	{
		raiz->fe = 0;
		raiz->iz.raiz->fe = 0;
	}
}

#pragma endregion
// operador salida recorrido inorden
ostream & operator<<(ostream& os, const TAVLCom& tree)
{
	os << tree.Inorden();
	return os;
}

#pragma endregion

