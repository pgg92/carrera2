/* Prueba:
     metodos de TListaPos
*/
#include <iostream>

using namespace std;

#include "tlistacom.h"

int
main(void)
{

	
	TComplejo a(1,-7), b;
	TListaCom lc1, lc2;
	
	for (int i = 0; i < 5 ; i++)
	{
		b = double(i);
		cout << "B: " << b << " y A: " << a << endl;
		a = a + b;
		lc1.InsCabeza(a);
		cout << lc1 << endl; 
	}
	
  return 0;
}
