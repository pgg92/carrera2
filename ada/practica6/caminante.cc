

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>


int
recursiva( int i, int j, std::vector<std::vector<int> > &m )
{
	int s1, s2, s3;
	
	if(i == 0 && j == 0)
	{
		return m[i][j];
	}
	else
	{
		if(i > 0 && j > 0)
			s1 = recursiva(i-1, j-1, m) + m[i][j];
		else
			s1 = INT_MAX;	
		if(j > 0)
			s2 = recursiva(i, j-1, m) + m[i][j];
		else
			s2 = INT_MAX;  
		if(i > 0)
			s3 = recursiva(i-1, j, m) + m[i][j];
		else
			s3 = INT_MAX;
		return std::min(std::min(s1, s2), s3);	
	}
}

bool
leerFichero( std::string nf, std::vector<std::vector<int> > &m,  int &fila, int &col )
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
		{
			for(j = 0; j < col; j++)
			{
				fe >> maux[i][j];
			}
		}
		
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
//p, t, ig, f
	int i;
	bool ok = true;
	
	flag[0] = flag[1] = flag[2] = flag[3] = false;
	 
	 for( i = 1; i < argc; i++ )
	 {
	 	if( (strcmp(argv[i], "-f") == 0 && !flag[2]) ||
	 		(strcmp(argv[i], "-p") == 0 && !flag[0]) ||
	 		(strcmp(argv[i], "-t") == 0 && !flag[1]) ||
	 		(strcmp(argv[i], "-ignore--recursive") == 0 && !flag[3]) )
	 	{
	 		if( (strcmp(argv[i], "-f")) == 0 )
	 		{
	 			nf = argv[i+1];
	 			flag[2] = true;
	 			i++;
	 		}
	 		if( (strcmp(argv[i], "-p")) == 0 )
				flag[0] = true;
			if( (strcmp(argv[i], "-t")) == 0 )
				flag[1] = true;
			if( (strcmp(argv[i], "-ignore--recursive")) == 0 )
				flag[3] = true;
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
	std::vector<bool> flags = {p, t, f, ig};


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
			std::cout << "Recursive: " << recursiva(fila-1, columna-1, matriz);
			std::cout  << std::endl;
		}
		else
		{
			std::cout << "ERROR. al abrir fichero" << std::endl;
		}
	}
	return 0;
}






