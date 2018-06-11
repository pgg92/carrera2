;;
;; Solución práctica 4
;;

#lang r6rs
(import (rnrs)
        (schemeunit))

;---------------------------------------------
; Ejercicio 1: (longitud-impar lista-simbolos)
;              (suma-longitudes lista-simbolos)
;              (mayusculas lista-simbolos)
;----------------------------------------------

; longitud-impar

(define (longitud-impar lista-simbolos)
    (filter (lambda (x)
              (odd? (string-length (symbol->string x)))) lista-simbolos))

;; Pruebas
(display "Probando 'longitud-impar'\n")
(check-equal? (longitud-impar '(me gusta LPP porque aprendo nuevos paradigmas de programación)) '(gusta LPP aprendo))
(check-equal? (longitud-impar '(hola que tal estás)) '(que tal estás))


; suma-longitudes

(define (suma-longitudes lista-simbolos)
  (fold-right (lambda (dato result)
                (+ result (string-length (symbol->string dato)))) 0 lista-simbolos))

;; Pruebas
(display "Probando 'suma-longitudes'\n")
(check-equal? (suma-longitudes '(me gusta LPP porque aprendo nuevos paradigmas de programación)) 53)
(check-equal? (suma-longitudes '(hola como estás)) 13)

; mayusculas

(define (mayusculas lista-simbolos)
  (map (lambda (x)
         (string->symbol (string-upcase (symbol->string x)))) lista-simbolos))

;; Pruebas
(display "Probando 'mayusculas'\n")
(check-equal? (mayusculas '(me gusta LPP porque aprendo nuevos paradigmas de programación))
             '(ME GUSTA LPP PORQUE APRENDO NUEVOS PARADIGMAS DE PROGRAMACIÓN))


;---------------------------------------------
; Ejercicio 2: (resultados‐quiniela lista‐parejas)
;              (cuenta-resultados resultado lista-resultados)
;              (cuenta-resultados-lista lista-resultados)
;------------------------------------

; resultado-partido

(define (resultado-partido partido)
  (cond
    ((> (car partido) (cdr partido))  1)
    ((= (car partido) (cdr partido))  'X)
    (else 2)))

;; Pruebas
(display "Probando 'resultado-partido'\n")
(check-equal? (resultado-partido (cons 3 1)) 1)
(check-equal? (resultado-partido (cons 0 0)) 'X)
(check-equal? (resultado-partido (cons 1 3)) 2)

; resultados-quinielas

(define (resultados-quiniela lista-parejas)
  (map resultado-partido lista-parejas))

;; Pruebas
(display "Probando 'resultados-quiniela'\n")
(check-equal? (resultados-quiniela '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) '(2 X 2 1 X))
(check-equal? (resultados-quiniela '((2 . 2))) '(X))
(check-equal? (resultados-quiniela '((3 . 2) (4 . 3) (3 . 5))) '(1 1 2))


; cuenta-resultados

(define (cuenta-resultados resultado lista-parejas)
  (length (filter (lambda (partido)
                    (equal? (resultado-partido partido) resultado))
                  lista-parejas)))

;; Pruebas
(display "Probando 'cuenta-resultados'\n")
(check-equal? (cuenta-resultados 'X '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 2)
(check-equal? (cuenta-resultados 1 '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 1)
(check-equal? (cuenta-resultados 2 '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 2)


(define (inc-pos n lista)
  (if (= n 0)
      (cons (+ 1 (car lista)) (cdr lista))
      (cons (car lista) (inc-pos (- n 1) (cdr lista)))))

;; Pruebas
(display "Probando 'inc-pos'\n")
(check-equal? (inc-pos 3 '(2 7 9 10)) '(2 7 9 11))
(check-equal? (inc-pos 1 '(2 7 9 10)) '(2 8 9 10))

(define (cuenta-resultados-lista lista-parejas)
  (fold-right (lambda (partido lista-resultado)
                (cond
                  ((equal? (resultado-partido partido) 1)
                   (inc-pos 0 lista-resultado))
                  ((equal? (resultado-partido partido) 'X)
                   (inc-pos 1 lista-resultado))
                  ((equal? (resultado-partido partido) 2)
                   (inc-pos 2 lista-resultado)))) (list 0 0 0) lista-parejas))

;; Pruebas
(display "Probando 'cuenta-resultados-lista'\n")
(check-equal? (cuenta-resultados-lista '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) '(1 2 2))
(check-equal? (cuenta-resultados-lista '((2 . 2))) '(0 1 0))
(check-equal? (cuenta-resultados-lista '((3 . 2) (4 . 3) (3 . 5))) '(2 0 1))

;--------------------
; Ejercicio 3: Huecos
;--------------------

(display "Probando ejercicio huecos\n")

; a)

(check-equal? (fold-right list 0 '(1 2 3)) '(1 (2 (3 0))))

; b)

(check-equal? (fold-left list "hola" '("como" "estas" "adios")) '((("hola" "como") "estas") "adios"))

; c)

(define lista '((2 . 7) (3 . 5) (10 . 4) (5 . 5)))

(check-equal? (filter even?
                      (map (lambda (x) (+ (car x)
                                               (cdr x)))
                                lista))
              '(8 14 10))

; d)

(check-equal? (filter (lambda (pareja)
                        (> (car pareja)
                           (cdr pareja)))
                      (map (lambda (pareja)
                             (cons (cdr pareja)
                                   (car pareja))) lista))
              '((7 . 2) (5 . 3)))


; e)

(check-equal? (fold-right (lambda (pareja resultado)
                            (cons (car pareja) resultado))
                          '()
                          (filter (lambda (x) (even? (+ (car x) (cdr x)))) lista))
              '(3 10 5))




;--------------------
; Ejercicio 4: (make-multiplicador k)
;              (make-exponenciador k)
;              (fija-segundo-arg f k)
;--------------------


(define (make-multiplicador k)
  (lambda (x)
    (* x k)))

;; Pruebas
(display "Probando 'make-multiplicador'\n")
(check-equal? ((make-multiplicador 10) 3) 30)
(check-equal? ((make-multiplicador 5) 3) 15)



(define (make-exponenciador k)
  (lambda (x)
    (expt k x)))

;; Pruebas
(display "Probando 'make-exponenciador'\n")
(check-equal? ((make-exponenciador 2) 3) 8)
(check-equal? ((make-exponenciador 5) 3) 125)


(define (fija-arg f i k)
  (if (= i 1)
      (lambda (x)
        (f k x))
      (lambda (x)
        (f x k))))

;; Pruebas
(display "Probando 'fija-arg'\n")
(check-equal? ((fija-arg + 2 10) 8) 18)
(check-equal? ((fija-arg expt 1 2) 4) 16)
(check-equal? ((fija-arg string-append 2 "****") "Hola") "Hola****")

;--------------------
; Ejercicio 5: (suma-n-izq n lista-parejas)
;              (aplica-2 func lista-parejas)
;--------------------


; suma-n-izq

(define (suma-n-izq n lista-parejas)
  (map (lambda (pareja)
         (cons (+ n (car pareja))
               (cdr pareja))) lista-parejas))

;; Pruebas

(display "Probando 'suma-n-izq' \n")
(equal? (suma-n-izq 10 '((1 . 3) (0 . 9) (5 . 8) (4 . 1))) '((11 . 3) (10 . 9) (15 . 8) (14 . 1)))
(equal? (suma-n-izq 5 '((2 . 1) (3 . 2) (4 . 3))) '((7 . 1) (8 . 2) (9 . 3)))


; aplica-2

(define (aplica-2 func lista-parejas)
  (map (lambda (pareja)
         (func (car pareja) (cdr pareja))) lista-parejas))


;; Pruebas

(display "Probando 'aplica-2'\n")
(check-equal? (aplica-2 + '((2 . 3) (1 . -1) (5 . 4))) '(5 0 9))
(check-equal? (aplica-2 (lambda (x y)
                          (if (even? x)
                              y
                              (* y -1))) '((2 . 3) (1 . 3) (5 . 4) (8 . 10))) '(3 -3 -4 10))



;--------------------------------------------------------
; Ejercicio 6: (cadena-mayor lista)
;              (filtra-simbolos lista-simbolos lista-num)
;--------------------------------------------------------

; cadena-mayor

(define (pareja-mayor pareja1 pareja2)
  (if (> (cdr pareja1)
         (cdr pareja2))
      pareja1
      pareja2))

(display "Probando 'pareja-mayor'\n")
(check-equal? (pareja-mayor (cons "hola" 4) (cons "un" 2)) (cons "hola" 4))
(check-equal? (pareja-mayor (cons "un" 2) (cons "hola" 4)) (cons "hola" 4))


(define (cadena-mayor lista)
  (fold-right pareja-mayor
             '("" . 0)
              (map (lambda (cadena)
                     (cons cadena (string-length cadena))) lista)))

;; Pruebas

(display "Probando 'cadena-mayor'\n")
(check-equal? (cadena-mayor '("vamos" "a" "obtener" "la" "cadena" "mayor")) (cons "obtener" 7))
(check-equal? (cadena-mayor '("prueba" "con" "maximo" "igual")) (cons "maximo" 6))
(check-equal? (cadena-mayor '("hola")) (cons "hola" 4))

; filtra-simbolos

(define (filtra-simbolos lista-simbolos lista-longitudes)
  (filter (lambda (pareja)
            (= (string-length (symbol->string (car pareja)))
               (cdr pareja))) (map cons lista-simbolos lista-longitudes)))

;; Pruebas

(display "Probando 'filtra-simbolos'\n")
(check-equal? (filtra-simbolos '(este es un ejercicio de examen) '(2 1 2 9 1 6)) '((un . 2) (ejercicio . 9) (examen . 6)))
(check-equal? (filtra-simbolos '(en un lugar de La Mancha) '(2 3 4 2 2 2)) '((en . 2) (de . 2) (La . 2)))
