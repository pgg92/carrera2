// ALIAGA HYDER ALEJANDRO JESÚS 48765284V
#ifndef _tabb
#define _tabb

#include "tvectorcom.h"
#include "tlistacom.h"

// Forward declaration
class TABBCom;
class TNodoABB;

class TABBCom
{
	friend class TNodoABB;

private:
	// puntero al nodo
	TNodoABB *nodo;
	// aux: recorrido inorden
	void InordenAux(TVectorCom &, int &) const;
	// aux: recorrido preorden
	void PreordenAux(TVectorCom &, int &) const;
	// aux: recorrido postorden
	void PostordenAux(TVectorCom &, int &) const;

public:
	// constructor por defecto
	TABBCom();
	// constructro copia
	TABBCom(const TABBCom &);
	// Destructor
	~TABBCom();
	// sobrecargar operador asignacion
	TABBCom &operator=(const TABBCom &);

	// Sobrecarga del operador igualdad
	bool operator==(const TABBCom &) const;
	// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
	bool EsVacio() const;
	// Inserta el elemento en el árbol
	bool Insertar(const TComplejo &);
	// Borra el elemento en el árbol bool
	bool Borrar(const TComplejo &);
	// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
	bool Buscar(const TComplejo &) const;
	// Devuelve el elemento en la raíz del árbol
	TComplejo Raiz() const;

	// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
	int Altura() const;
	// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
	int Nodos() const;
	// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
	int NodosHoja() const;

	// Devuelve el recorrido en inorden
	TVectorCom Inorden() const;
	// Devuelve el recorrido en preorden
	TVectorCom Preorden() const;
	// Devuelve el recorrido en postorden
	TVectorCom Postorden() const;
	// Devuelve el recorrido en niveles
	TVectorCom Niveles() const;

	TComplejo BuscarMayor() const;

	// EXAMEN JUNIO 2017
	int examen(const TABBCom& tree);
	bool estructura(const TABBCom& tree);
	bool tope(const TABBCom& tree);
	bool ceaux(const TABBCom& tree);

	// Sobrecarga del operador salida
	friend ostream & operator<<(ostream &, const TABBCom &);
	
	int* examen2(const TListaCom& lp) const;
	int encontrarCaso(const TComplejo& p) const;
	
};

class TNodoABB
{
	friend class TABBCom;

private:
	// Elemento del nodo
	TComplejo item;
	// subarboles izquierdo / derecho
	TABBCom iz;
	TABBCom de;

public:
	// constructor por defecto
	TNodoABB();
	// constructor parametrizado
	TNodoABB(const TNodoABB &);
	// destructor
	~TNodoABB();
	// sobrecargar operador asignacion
	TNodoABB &operator=(const TNodoABB &);
};

#endif
