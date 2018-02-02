#ifndef _tcom
#define _tcom

#include <iostream>
#include <cmath>


// paco cojo

using namespace std;

class TComplejo{

	private:
		double 
			re, im;

	public:
		// Forma canonica
		TComplejo  ()
			{re = 0; im = 0;}
		TComplejo  (double r)
			{re = r; im = 0;}
		TComplejo  (double r, double i)
			{re = r; im = i;}
		~TComplejo ()
			{im = 0; re = 0;}
		TComplejo(const TComplejo &c)
			{re = c.re; im = c.im;}
			
		TComplejo &operator= (const TComplejo &c);

		// Metodos
		TComplejo operator+ (const TComplejo &c) const; 
		TComplejo operator- (const TComplejo &c) const;
		TComplejo operator* (const TComplejo &c) const;
		TComplejo operator+ (const double d) const;
		TComplejo operator- (const double d) const;
		TComplejo operator* (const double d) const;
		
		bool operator==	(const TComplejo &c) const;
		bool operator!=	(const TComplejo &c) const;

		double Re() const{return re;}
		double Im() const{return im;}

		void Re(const double r) {re = r;}
		void Im(const double i) {im = i;}
	
		double Arg(void);
		double Mod(void);

	// Funciones amigas
	friend ostream & operator<<(ostream &os, const TComplejo &c);
	friend TComplejo operator+(double d, const TComplejo &c);
	friend TComplejo operator-(double d, const TComplejo &c);
	friend TComplejo operator*(double d, const TComplejo &c);
};
#endif
