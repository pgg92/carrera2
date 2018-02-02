f(x) = a*x + b
fit f(x) "burbuja.dat" via a,b
plot "burbuja.dat" with lines, f(x)
pause -1 "pulsar para continuar"


f(n) = a*(n*log(n)) + b
fit f(x) "quicksort.dat" via a,b
plot "quicksort.dat" with lines, f(x)
pause -1 "pulsar para continuar"