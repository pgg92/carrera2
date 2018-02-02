// ALIAGA HYDER ALEJANDRO JESÚS DNI: 48765284V 

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;



// abstracción de una coordenada
struct Coord
{
	int x, y;
};

// constructor coordenada
void
nuevaCoordenada( int x, 
				 int y,
				 std::vector<Coord> &coords )
{
	Coord caux;

	caux.x = x;
	caux.y = y;
	coords.push_back(caux);
}

// mostrar matriz 2d
void
dibujarm2d( int f,
			int c,
			std::vector<Coord> &coords )
{
	int posicion;
	
	posicion = 0;
	for(int i = 0; i < f; i++ )
	{
		for(int j = 0; j < c; j++ )
		{
			if( coords[posicion].x == i &&
				coords[posicion].y == j )
			{
				std::cout << "X";
				posicion++;
			}
			else
				std::cout << ".";
				
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// dibujar el camino obtenido
void
dibujarCamino(	int f,
				int c, 
				std::vector<Coord> &coords )
{

	for( int i = 0; i < coords.size(); i++ )
	{
		std::cout 
		<< "("<< coords[i].x << ","
		<< coords[i].y << ")";
	}
}


// coste(m, x, k); , std::vector< Coord > &sol, int k
int
coste( std::vector<std::vector<int> > &m,
		std::vector< Coord > &sol,
		int k )
{
	int total;
	
	total = 0;
	for( int i = 0; i < k; i++)
	{
		total += m[sol[i].x][sol[i].y];
	}

	return total;
}


void
backTracking( std::vector<std::vector<int> > &m,
			  int kf,
			  int kc,
			  std::vector< Coord > &x,
			  int k,
			  int f,
			  int c,
			  std::vector< Coord > &solMejor,
			  int &vMejor )
{

	int vActual;

	Coord aux;
	aux.x = kf;
	aux.y = kc;
	x[k] = aux;
	k++;

	if( kf == f - 1 && kc == c - 1)
	{
		vActual = coste(m, x, k);
		if( vActual < vMejor )
		{
			vMejor = vActual;
			solMejor = x;
		}
	}
	else
	{
		if( kc == c - 1 )
		{
			backTracking(m, kf + 1, kc, x, k, f, c, solMejor, vMejor);
		}
		else if( kf == f - 1 )
		{
			backTracking(m, kf, kc + 1, x, k, f, c, solMejor, vMejor);
		}
		else
		{
			backTracking(m, kf + 1, kc, x, k, f, c, solMejor, vMejor);
			backTracking(m, kf, kc+1, x, k, f, c, solMejor, vMejor);
			backTracking(m, kf + 1, kc+1, x, k, f, c, solMejor, vMejor);
		}
	}
}

// leer fichero
bool
leerFichero( std::string nf, 
			 std::vector<std::vector<int> > &m,
			 int &fila,
			 int &col )
{
	int i,
		j;
	bool leido;
	std::ifstream fe;
		
	fe.open(nf);
	leido = false;
	
	if( fe.is_open() )
	{
		// 		n       m 
		fe >> fila >> col;
		std::vector< std::vector<int> >	maux(fila, std::vector<int>(col));
		
		for(i = 0; i < fila; i++)
			for(j = 0; j < col; j++)
				fe >> maux[i][j];
		
		leido = true;
		m = maux;
		fe.close();
	}
	
	return leido;
}

// control de los argumentos
bool
comprobarArgumentos( int argc, char *argv[], 
					 std::string &nf, 
					 std::vector<bool> &flag )
{
	int i;
	bool ok = true;
	
	flag[0] = flag[1] = flag[2] = flag[3] = false;
	 
	 for( i = 1; i < argc; i++ )
	 {
	 	if( (strcmp(argv[i], "-f") == 0 && !flag[2]) ||
	 		(strcmp(argv[i], "-p") == 0 && !flag[0]) )
	 	{
	 		if( (strcmp(argv[i], "-f")) == 0 )
	 		{
	 			nf = argv[i+1];
	 			flag[2] = true;
	 			i++;
	 		}
	 		if( (strcmp(argv[i], "-p")) == 0 )
				flag[0] = true;
	 	}
	 	else
	 		ok = false;
	 }
	 
	
	return ok;
}

int main( int argc, char *argv[] )
{
	int fila,
		columna,
		peso,
		costeMenor;
		
	bool argumentosOK,
		 leidoOK,
		 p,
		 t,
		 ig,
		 f;

	float vmejor;
		 
	std::string nombFich;
	
	std::vector< std::vector<int> > matriz;
	std::vector< Coord > solMejor;
	std::vector< Coord > x;
	std::vector< bool  > flags = { p,
								   t,
								   f,
								   ig };

	argumentosOK = comprobarArgumentos(argc, argv, nombFich, flags);
	leidoOK = leerFichero(nombFich, matriz, fila, columna);

	if( argumentosOK == false )
	{
		std::cout
		<< "ERROR. argumentos incorrectos "
		<< std::endl;
	}
	else
	{
		if( leidoOK == true )
		{
			costeMenor = INT_MAX;
			auto begin = high_resolution_clock::now();
			backTracking(matriz, 0, 0, x, 0, fila, columna, solMejor, costeMenor);
			auto end = high_resolution_clock::now();
		
			std::cout 
			<< "Backtracking: "
			<< costeMenor
			<< std::endl
			<< "CPU elapsed time: "
			<< duration_cast<milliseconds>(end-begin).count()
			<< "ms"
			<< std::endl;
		
			if( flags[0] == true )
			{
				std::cout << "A possible path: ";
				dibujarCamino(fila, columna, solMejor);
				std::cout  << std::endl;
				dibujarm2d( fila,columna, solMejor );
			}
		}
		else
		{
			std::cout 
			<< "ERROR. al abrir fichero"
			<< std::endl;
		}
	}
	return 0;
}






