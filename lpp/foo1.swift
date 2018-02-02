let a = 3 // constante, infiere el tipo en el momento de la inicializacion.
var b = 4 // variable
print(a, b)
print("a: \(a) b: \(b + b)")
print("a: " + String(a)  + " b: " + String(b))

let c:Int = 30
print(c)

print(a, b, c, separator:" *** ", terminator: "<>\n")

print(a, terminator: " ")
print(b, terminator: " ")
print(" ")

let x:Int // si no inicializamos la constante hay que indicarle el tipo, porque el tipo
            // se infiere en la inicializacion.

x = 3       // podemos cambiarle solo una vez el valor a la constante (valor inicial)
// a = 6
print(x)

func saluda(){
    print("hola")
}
saluda()

func incrementa(x:Int) -> Int{
    // x = x + 1; los parametros se consideran constantes.
    return x + 1
}

print(incrementa(3))

func inc(inout x:Int){
    x = x + 1
}
var val : Int = 9
inc(&val)
print(val)

func mayor2(x:Int, y:Int) -> Int{
    var mayor:Int
    if(x > y){
        mayor = x
    }
    else {
        mayor = y
    }
    return mayor
}
print( mayor2(3, y:93) )

func mayor3(valor1 x:Int, valor2 y:Int, valor3 z:Int) -> Int{
    return mayor2(x, y : mayor2(y, y: z))
}
print(mayor3(valor1: 3, valor2: 3, valor3: 40))

// el primero no tiene nombre externo, el resto el nombre externo coincide con
// el nombre interno.
//func suma3(_ v1:Int, v2 v2:Int, v3 v3:Int) -> Int

func suma3(_ v1:Int, _ v2:Int, _ v3:Int) -> Int{
    return v1 + v2 + v3
}

print(suma3(3, 4, 5))

func prod(x:Int = 3, y:Int = 6) -> Int{
    return x * y
}
print(prod())
print(prod(3))
print(prod(y:9))
print(prod(3, y:10))

func mir(x x:Int, y y:Int) -> Int{
    return x - y
}
// print(mir(y:34, x:3))

// funcion recursiva que imprime de 1 a n.
func impN(n:Int){
    if n == 1{
        print(n)
    }
    else{
        print(n)
        impN(n-1)
    }
}
print("-----")
impN(5)
print("-----")
for i in 1...10{
    print(i, terminator: " ")
}
print( " ")

for i in 1..<10{
    print(i, terminator: " ")
}
print(" ")
// esta al reves... se desborda :()
//for i in 10...1{
//   print("adiooooo")
//}
for i in (1...10).reverse(){
    print(i)
}
//let rango = (10...1) // al intentar crear el rango, no cumple que inicio sea menor que fin.

var i:Int
i = 1
while(i < 10){
    print(i)
    i = i + 2
}

for i in 1.stride(to: 10, by: 2){
    print(i)
}
var ab:Int = 5
for i in ab.stride(to: 100, by: 10){
    print(i)
}

var inicio:Int = 10

for i in inicio.stride(to:100, by: 1) where i % 2 == 0{
    print(i)
}

// funcion que suma los numeros desde 1 hasta n.
func sumatots(n:Int)->Int{
    if(n == 1){
        return 1
    }
    else{
        return n + sumatots(n-1)
    }
}
// funcion que suma los numeros entre a y b.
func sumaEnts(a:Int, b:Int) ->Int{
    if(a > b){
        return 0
    }
    else{
        return a + sumaEnts(a+1, b:b);
    }
}
// funcon que suma los numeros f(a) + f(a+1) + f(a+2) .. + f(b)
func sumatorio(desde a:Int, hasta b:Int, fun f: (Int) ->Int) ->Int{
    if(a > b){
        return 0
    }
    else{
        return f(a) + sumatorio(desde : a + 1, hasta : b, fun : f)
    }
}
func cuadrado(x:Int) -> Int{
    return x * x
}
print(sumatorio(desde:3, hasta: 10, fun:cuadrado))

// funcion que recibe 3 parametros y devuelve el menor y mayor de los 3.
func maxmin(x:Int, y:Int, z:Int) -> (minimo:Int, maximo:Int){
    return (min(x, y, z), max(x, y, z))
}

let tupla = maxmin(3, y: 4, z: 10)

print(tupla.minimo, tupla.maximo)

var v = [3, 3, 1, 2]

print(v)

for x in v{
    print(x)
}


// funcion que recibe un vector de enteros y devuelve la suma de los enteros
// entre inicio y fin.
func sumarVector(v:[Int], inicio:Int, fin:Int) -> Int{
    var suma:Int
    suma = 0
    for i in inicio...fin{
        suma = suma + v[i]
    }
    return suma
}

func sumarVectorRecursivo(v:[Int], inicio:Int, fin:Int) -> Int{
    if(inicio > fin){
        return 0
    }
    else{
        return sumarVectorRecursivo(v, inicio: inicio+1, fin: fin) + v[inicio]
    }
}



