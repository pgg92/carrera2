#ifndef _tvcom
#define _tvcom

#include "tcomplejo.h"

using namespace std;

class TVectorCom
{
	private:
		TComplejo error;
		TComplejo *c;
		int tamano;

	public:
		//Forma canonica
		TVectorCom ()
			{tamano = 0; c = NULL;}
		~TVectorCom ();
		TVectorCom (int ta);
		TVectorCom (const TVectorCom &v);
		
		TVectorCom &operator= (const TVectorCom &v);

		
		// sobre carga operadores
		bool operator== (const TVectorCom &v) const;
		bool operator!= (const TVectorCom &v) const;
		bool ExisteCom(const TComplejo &c);
		bool Redimensionar(int t);
		
		TComplejo &operator[](int e);
		TComplejo operator[] (int e) const;
		
		int Tamano()
			{return tamano;}
		int Ocupadas();
		void MostrarComplejos(const double real) const;
		
		//funciones amigas
		friend ostream & operator<<(ostream &os, const TVectorCom &v); 
		
};
#endif
