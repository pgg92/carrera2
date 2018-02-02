// ALIGA HYDER ALEJANDRO JESÚS 48765284V

#pragma once
#include "tvectorcom.h"
#include "tcomplejo.h"

// forward declaration
class TNodoAVL;

class TAVLCom
{
	// friend declaration
	friend class TNodoAVL;

	// Sobrecarga del operador salida
	friend ostream & operator<<(ostream &, const TAVLCom &);

	private:
		// Puntero al nodo
		TNodoAVL *raiz;
		// AUXILIAR : Devuelve el recorrido en inorden
		void InordenAux(TVectorCom &, int &) const;
		// AUXILIAR : Devuelve el recorrido en preorden
		void PreordenAux(TVectorCom &, int &) const;
		// AUXILIAR : Devuelve el recorrido en postorden
		void PostordenAux(TVectorCom &, int &) const;
		
		// funciones auxiliares a las dadas
		#pragma region aux functions
		#pragma region insertar
		// insertar II
		void II();
		// insertar DD
		void DD();
		// insertar DI
		void DI();
		// insertar ID
		void ID();
		// realizar inserciom, devuelve un booleano
		bool insertaraux(const TComplejo&, bool&);
		#pragma endregion
		// borrar aux
		bool BorrarAux(const TComplejo&, bool&);
		// determina si un nodo es hoja
		bool esHoja() const;
		// comprueba si solo tien hijo izquierdo
		bool soloIzquierdo() const;
		// determina si tiene dos hijos
		bool estafull() const;

		#pragma endregion


	public:
		// Constructor por defecto
		TAVLCom();
		// Constructor de copia
		TAVLCom(const TAVLCom &);
		// Destructor
		~TAVLCom();
		// Sobrecarga del operador asignación
		TAVLCom & operator=(const TAVLCom &);

		// Sobrecarga del operador igualdad
		bool operator==(const TAVLCom &) const;
		// Sobrecarga del operador desigualdad
		bool operator!=(const TAVLCom &) const;
		// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
		bool EsVacio() const;
		// Inserta el elemento en el árbol
		bool Insertar(const TComplejo &);
		// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
		bool Buscar(const TComplejo &);

		// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
		int Altura() const;
		// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
		int Nodos() const;
		// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
		int NodosHoja() const;

		// Devuelve el recorrido en inorden sobre un vector
		TVectorCom Inorden() const;
		// Devuelve el recorrido en preorden sobre un vector
		TVectorCom Preorden() const;
		// Devuelve el recorrido en postorden sobre un vector
		TVectorCom Postorden() const;
		// Devuelve el elemento TComplejo raíz del árbol AVL
		TComplejo Raiz() const;	
		// buscar mayor nodo de un arbol
		TComplejo BuscarMayor() const;

		// comprueba y arregla los fe tras borrar
		bool Reestructuracion(bool& ,
													bool& ,
													bool& ,
													bool& );
		// Borra un TComplejo del árbol AVL
		bool Borrar(const TComplejo &);
};

class TNodoAVL
{
	// friend declaration
	friend class TAVLCom;

private:
	// El elemento del nodo
	TComplejo item;
	// Subárbol izquierdo y derecho
	TAVLCom iz;
	TAVLCom de;
	// Factor de equilibrio
	int fe;

public:
	// Constructor por defecto
	TNodoAVL();
	// Constructor de copia
	TNodoAVL(const TNodoAVL &);
	// Destructor
	~TNodoAVL();
	// Sobrecarga del operador asignación
	TNodoAVL & operator=(const TNodoAVL &);
};
