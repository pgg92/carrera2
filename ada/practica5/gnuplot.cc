// poner titulo arriba de la grafica
set title "complejidad temporal funciones..."

//guardar datos de pantalla
// 1 -> x, 2 -> y //  para indicar que columna es la x y
plot "datos.dat" using 1:2 with lines, "datos.dat" using 1:3 with lines, ...

// si ponemos el nombre en 1 sobra
plot "datos.dat" using 1:2 with lines, "" using 1:3 with lines, ...

// limitar eje a cuanto llega
// indica la x[0:500] indica la y[0:2000]
plot "datos.dat" [0:500] [0:2000] using 1:2 with lines, "" using 1:3 with lines, \retorno de carro
"" using ....., \retorno de carro 
""using .......

// poniendo el titulo

plot "datos.dat" [0:500] [0:2000] using 1:2 with lines title "titulo", "" using 1:3 with lines title "titulo", \retorno de carro
"" using ....., \retorno de carro 
""using .......

// etiqueta debajo de la grafica
set xlabel "n"
set ylabel "llamadas recursivas"


/*
	fichero .cc 
	fichero gnu plot que al ejecutarlo salga la grafica
	captura de lo que sale en la grafica (desde plot se puede exportar)
	justificar la complejidad para cada grafica
*/
