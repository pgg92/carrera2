var vector = [3, 3, 2]

func imprimir(v:[Int]){
	for x in v{
		print(x, terminator: ", ")
	}
}

imprimir(v:vector)

func sumarElementosRS(v:ArraySlice<Int>) -> Int{
    if(v.count == 0){
        return 0
    }
    else{
        let pos = v.startIndex // indice de la primera posicion.
        print("comienzo en llamada: ", pos)
        let primero = v[pos]
        return primero + sumarElementosRS(v:v[pos + 1..<v.endIndex])
    }
}
print(sumarElementosRS(v:[2, 3, 2, 3]))

// funcion que devuelve la suma de aplicar la funcion f a cada elemento del vector
func cuadrado(x:Int)->Int{
    return x*x
}
// print(sumarFR([3, 3, 1]), f:cuadrado) ) // imrpime 19 (9 + 9 + 1)
func sumarFR(_ v:ArraySlice<Int>, _ f:(Int) ->Int) -> Int{
    if(v.count == 0){
		return 0
	}
	else{
		let posicion = v.startIndex
		return f(v[posicion]) + sumarFR(v[posicion+1..<v.endIndex], f)
	}
}
 print(sumarFR([3, 3, 1], cuadrado)) // imprime 19 (9 + 9 + 1)

print([3, 3, 3, 2, 1].reduce(0, -)) // foldLeft

print([3, 3, 3, 2, 1].map(cuadrado))

print([3, 1, 1, 2, 2].map(cuadrado).reduce(0, +))

print([3, 1, 2, 2, 1].map( {$0 * $0} ).reduce(0, {$0 + $1} ) )

print([3, 1, 2, 2, 1].map( 
		{
			(x:Int) -> Int in return x * x
		} 
	).reduce(0, +) )

// TUPLA 
// AGRUPACION DE ELEMENTOS DE DISTINTO TIPO NAZI.
var t = (3, 4, "jose")
print(t.0, t.1, t.2)

var t2:(Int, Int, String) = (3, 3, "poya")
print(t2)

var t3:(first:Int, second:Int, third:String) = (3, 1, "domingo")
print(t3.first, t3.second, t3.third)
print(t3.0)

// funcion que recibe un vector de tuplas e imprime por pantalla
// para cada tupla la suma de sus elementos.

func sumaTuplas(_ v:ArraySlice<(Int, Int)>){
	if(v.count != 0){
		let posicion = v.startIndex
		print(v[posicion], terminator: ", ")
		sumaTuplas(v[posicion+1..<v.endIndex])
	}
}

sumaTuplas([(3, 2), (3, 1), (3, 5), (3, 1)])

// EJERCICIOS PROPUESTOS
// 1. Funcion que devuelve la cantidad de elementos pares que hay en
// un Array pasado como parametro
// 2. Repetir el anterior suponiendo que el parametro es un ArraySlice
// 3. Repetir el anterior utilizando orden superior
// 4. Repetir los anteriores haciendolos iterativos o recursivos

// 5. Funcon que recibe un vector y dos predicados, devuleve
// una tupla formada por dos elemenot, una con las que cumplen el primer
// predicado y otra con las que cumplen el segundo predicado.

// 6. Funcion que devuelve cierto si un ArraySlice<Int> que recibe esta
// ordenado de menor a mayor

// 7. amaros los unos a los otros como yo os he amado.




















