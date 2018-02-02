/* SALIDA:
4
1
2
4
*/

#include <iostream>
#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

int
main(void)
{
  
  TABBCom a1;
  TABBCom a2;
  int val;

  TComplejo c1(1, 0);
  TComplejo c2(2, 0);
  TComplejo c3(3, 0);
  TComplejo c4(4, 0);

  a2.Insertar(c1);
  a2.Insertar(c2);

  a1.Insertar(c1);
  a1.Insertar(c2);  
  val = a1.examen(a2);
  cout << val << endl;

  a2.Borrar(c2);
  val = a1.examen(a2);
  cout << val << endl;

  a1.Borrar(c2);
  a1.Borrar(c1);
  val = a1.examen(a2);
  cout << val << endl;

  a2.Borrar(c1);
  val = a1.examen(a2);
  cout << val << endl;

  return 1;
}

