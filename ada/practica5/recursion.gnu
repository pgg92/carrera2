set title "complejidad temporal funciones..."
set xlabel "n"
set ylabel "llamadas recursivas"

plot [:] [0:2000] "datos.dat" using 1:2 with line title "pow2_1",\
"" using 1:3 with line title "pow2_2",\
"" using 1:4 with line title "pow2_3",\
"" using 1:5 with line title "pow2_4"

pause -1 "Pulsa retorno"
