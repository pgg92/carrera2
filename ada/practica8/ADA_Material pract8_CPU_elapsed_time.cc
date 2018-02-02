// Código de ejemplo para mostrar el tiempo de proceso de un fragmento del programa.

// Este código es válido para el estándar C++11 y siguientes.
// Si se compila con una versión del lenguaje anterior probar la opción "-std=c++0x" del compilador g++

#include <iostream>

#include <chrono>
#include <thread>


using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


double my_function(){

	// do something ...

	// .. and remove next line :)
	sleep_until(system_clock::now() + seconds(5));

	return 0;
}


int main(){
    auto begin = high_resolution_clock::now();
    auto r = my_function();
    auto end = high_resolution_clock::now();
    cout 
      << "Backtracking: " 
      << r
	  << endl
      << "CPU elapsed time: " 
      << duration_cast<milliseconds>(end-begin).count() << " ms" << endl;
  }

