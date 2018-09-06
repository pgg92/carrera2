#include "tvectorcom.h"

//Forma canonica
TVectorCom::~TVectorCom()
{
	if(c != NULL)
		delete [] c;
		
	c = NULL;
	tamano = 0;
}

TVectorCom::
TVectorCom (const int ta)
{
	if(ta <= 0) 
		{tamano = 0; c = NULL;}
	
	else
	{
		tamano = ta; 
		c = new TComplejo[ta];
	}
}

TVectorCom::
TVectorCom (const TVectorCom &v)
{
	if(v.tamano != 0 && v.c != NULL){
	
		tamano = v.tamano;
		c = new TComplejo [v.tamano];
		
		for(int i = 0; i < v.tamano; i++)
			c[i] = v.c[i];
	}
	
	else
		{ c = NULL; tamano = 0;}
	
}

TVectorCom &
TVectorCom::operator= (const TVectorCom &v)
{
	int i;

	if(this != &v)
	{
		this->~TVectorCom();

		if(v.tamano != 0)
		{
			tamano = v.tamano;
			c = new TComplejo[v.tamano];
			
			for(i = 0; i < tamano; i++)
				c[i] = v.c[i];
		}
	}
	return *this;
}


//metodos
bool 
TVectorCom::operator== (const TVectorCom &v) const
{
	bool equals = true;
	int i;

	if(tamano == v.tamano)
	{		
		for(i = 0; i < tamano && equals == true; i++)
		{
			if(c[i] != v.c[i])
				equals = false;
		}
	}
	else
		equals = false;
			
	return equals;
}
bool 
TVectorCom::operator!= (const TVectorCom &v) const
{
	bool distinct = true;
	int i;
	
		if(tamano == v.tamano)
		{
			for(i = 0; i < tamano && distinct; i++)
			{
				if(c[i] == v.c[i])
					distinct = false;
			}
		}
	
	return distinct;
}

bool 
TVectorCom::ExisteCom(const TComplejo &c)
{
	bool equals = false;
	int i;
	
	for(i = 0; i < tamano && !equals; i++)
		if(this->c[i] == c)
			equals = true;
	
	return equals;
}

bool 
TVectorCom::Redimensionar(int t)
{
	bool resize = false;
	TComplejo *nv = NULL;
	int i;
	
		if(t > 0 && t != tamano)
		{
			nv = new TComplejo[t];
			
			for(i = 0; i < tamano; i++)
				nv[i] = c[i];
			for(i = tamano; i < t; i++)
				nv[i] = TComplejo();
				
			c = nv;
			tamano = t;
			resize = true;
		}
		
		if(t > 0 && t < tamano)
		{
			nv = new TComplejo[t];
			
			for(i = 0; i < t; i++)
				nv[i] = c[i];
				
			c = nv;
			resize = true;
		}
	
	return resize;
}

TComplejo &
TVectorCom::operator[](int e)
{
	if(e >= 1 && e <= tamano && c != NULL)	
		return c[e - 1];
	else
		return error;
}


TComplejo 
TVectorCom::operator[](int e) const
{
	if(e <= tamano && c != NULL && e >= 1)
		return c[e - 1];
	else
		return error;
}


int 
TVectorCom::Ocupadas()
{
	TComplejo aux = TComplejo();
	int ocupadas = 0;
	int i;
	
	
	for(i = 0; i < tamano; i++)
	{
		if(c[i]!=aux)
			ocupadas++;
	}
	
	return ocupadas;
}

void 
TVectorCom::MostrarComplejos(double real) const
{
	int i;
	bool primero = true;
	
	cout << "[";
	
	for(i = 0; i < tamano; i++)
	{
		if(c[i].Re() >= real)
		{
			if(primero)
			{
				cout << c[i];
				primero = false;
			}
			else
			{
				cout << ", " << c[i];
			}
		}
	}
	cout << "]";
}


//funciones amigas

ostream
&operator<<(ostream &os, const TVectorCom &v)
{
	int i;
	
	os << "[";
	
	for(i = 0; i < v.tamano; i++)
	{
		os << "(" << i+1 << ") ";
		os << v.c[i];
		
		if(i < v.tamano - 1)
			os <<", ";
	}

	os << "]";
	
	return os;
}

















