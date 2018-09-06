#include "tcomplejo.h"


// forma canonica
TComplejo &
TComplejo::operator= (const TComplejo &c)
{
	re = c.re;
	im = c.im;

	return *this;
}

// Metodos
TComplejo 
TComplejo::operator+ (const TComplejo &c) const
{
	TComplejo aux;

	aux.re = re + c.re;
	aux.im = im + c.im;

	if(aux.re == -0)
		aux.re = 0;
	if(aux.im == -0)
		aux.im = 0;

	return aux;
}
TComplejo 
TComplejo::operator- (const TComplejo &c) const
{
	TComplejo aux;

	aux.re = re - c.re;
	aux.im = im - c.im;

	if(aux.re == -0)
		aux.re = 0;
	if(aux.im == -0)
		aux.im = 0;

	return aux;
}
TComplejo 
TComplejo::operator* (const TComplejo &c) const
{
	TComplejo aux;

	aux.re = re * c.re;
	aux.im = im * c.im;

	return aux;
}
TComplejo 
TComplejo::operator+ (double r) const
{
	TComplejo aux;	
	
	aux.re = re + r;
	aux.im += im;	

	return aux;
}
TComplejo 
TComplejo::operator- (double r) const{

	TComplejo aux;	
	
	aux.re = re - r; 
	aux.im = im;	

	return aux;
}
TComplejo 
TComplejo::operator* (double r) const{

	TComplejo aux;	
	
	aux.re = r * re;
	aux.im *= im;

	return aux;
}
		
bool 
TComplejo::operator== (const TComplejo &c) const
{	
	bool equals = false;

	if (re == c.re && im == c.im)
		equals = true;

	return equals;

}
bool 
TComplejo::operator!= (const TComplejo &c) const
{
	bool distinct = false;

	if (re != c.re or im != c.im)
		distinct = true;

	return distinct;
}
	
double 
TComplejo::Arg(void) const
{
	double arc;
	if(re==0 && im==0)
		arc=0;
	else
		arc = atan2(im, re);

return arc;
}
double 
TComplejo::Mod(void) const
{
	double a;
	a = sqrt(pow(re,2) + pow(im,2));
	return a;
}

// Funciones amigas
ostream 
&operator<<(ostream &os, const TComplejo &c)
{

	os << "(" << c.re << " " << c.im << ")";
	return os;
}
TComplejo 
operator+(const double d, const TComplejo &c)
{

	TComplejo aux;

	aux.re = c.re + d;
	aux.im = c.im;

	return aux;
}
TComplejo 
operator-(const double d, const TComplejo &c)
{

	TComplejo aux;

	aux.re = d - c.re;
	aux.im = 0 - c.im;

	return aux;
}
TComplejo 
operator*(const double d, const TComplejo &c)
{
	TComplejo aux;

	aux.re = c.re * d;
	aux.im = c.im * d;

	return aux;
}
