// ALIAGA HYDER ALEJANDRO JESÚS DNI: 48765284V 

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>

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
	int posicion = 0;
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

void
dibujarCamino(	int f,
				int c, 
				std::vector<Coord> &coords )
{
	//dibujar las coordenadas
	std::cout  << std::endl;
	for( int i = 0; i < coords.size(); i++ )
	{
		std::cout << "("<< coords[i].x << ",";
		std::cout << coords[i].y << ")";
	}
}


// fila-1, columna-1, flags[0], matriz, coordenadas, m2d );

void
caminanteVoraz( int f,
				int c,
				bool flag,
				std::vector<std::vector<int> > &m,
				std::vector< Coord> &coords )
{
	Coord caux;
	int peso,
		i, j;
		
	peso = m[0][0];
	i = j = 0;
	
	while( i != f || j != c )
	{	
		// ultima fila -> j++
		// ultima columna -> i++
		if( i == f )
		{
			nuevaCoordenada(i,j,coords);
			j++;
		}
		else if( j == c )
		{
			nuevaCoordenada(i,j,coords);
			i++;
		}
		// si la diagonal es el menor...
		else if( m[i+1][j+1] <= m[i+1][j] &&
				 m[i+1][j+1] <= m[i][j+1])
		{
			nuevaCoordenada(i,j,coords);
			i++;
			j++;	 
		}
		// si la derecha es el menor...
		else if( m[i][j+1] <= m[i+1][j] &&
				 m[i][j+1] <= m[i+1][j+1])
		{
			nuevaCoordenada(i,j,coords);
			i++;
			j++;
		}
		// entonces abajo es la menor...
		else if( m[i+1][j] <= m[i+1][j+1] &&
				 m[i+1][j] <= m[i][j+1])
		{
			nuevaCoordenada(i,j,coords);
			i++;
		}
		
		peso += m[i][j];
	}
	nuevaCoordenada(i,j,coords);
	
	
	std::cout << peso;

}
/* LEER FICHERO Y PROCESAR ARGUMENTOS */

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

int main(int argc, char *argv[])
{
	int fila,
		columna;
		
	bool argumentosOK,
		 leidoOK,
		 p, t, ig, f;
		 
	std::string nombFich;
	
	
	std::vector< std::vector<int> > matriz;
	std::vector<Coord> coordenadas;
	std::vector<bool> flags = { p,
								t,
								f,
								ig};


	argumentosOK = comprobarArgumentos(argc, argv, nombFich, flags);
	leidoOK = leerFichero(nombFich, matriz, fila, columna);
	
	
	if( argumentosOK == false )
	{
		std::cout << "ERROR. argumentos incorrectos " << std::endl;
	}
	else
	{
		if( leidoOK == true )
		{	
			std::cout << "Greedy: ";
			caminanteVoraz( fila-1, columna-1, flags[0], matriz, coordenadas);
			std::cout  << std::endl << std::endl;
		
			if( flags[0] == true )
			{
				std::cout << "A greedy path: ";
				dibujarCamino(fila-1, columna-1, coordenadas);
				std::cout  << std::endl;
				dibujarm2d( fila,columna, coordenadas );
			}
		}
		else
		{
			std::cout << "ERROR. al abrir fichero" << std::endl;
		}
	}
	return 0;
}






