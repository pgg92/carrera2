;;
;; Solución práctica 7
;;

#lang r6rs
(import (rnrs)
        (schemeunit))

;;
;; Barrera de abstracción arbol
;;

(define (dato-arbol arbol) 
    (car arbol))

(define (hijos-arbol arbol) 
    (cdr arbol))

(define (hoja-arbol? arbol) 
   (null? (hijos-arbol arbol)))


;;
;; Barrera de abstracción arbol binario
;;

(define (dato-arbolb arbol)
   (car arbol))
   
(define (hijo-izq-arbolb arbol)
   (cadr arbol))

(define (hijo-der-arbolb arbol)
   (caddr arbol))

(define (hoja-arbolb? arbol)
  (and (vacio-arbolb? (hijo-izq-arbolb arbol))
       (vacio-arbolb? (hijo-der-arbolb arbol))))
   
(define (vacio-arbolb? x)
   (null? x))

(define arbolb-vacio '())


;------------
; Ejercicio 1
;------------

;; a.1)

(display "Probando ejercicio a.1)\n")
(define arbol '(15 (4 (2) (3))
                   (8 (6))
                   (12 (9) (10) (11))))

(check-equal? (dato-arbol (cadr (hijos-arbol (caddr (hijos-arbol arbol))))) 10)

;;
;; a.2)
;;
;; 1 - (suma-datos-arbol (car bosque)) devuelve 9
;; 2 - La primera llamada recursiva a suma-datos-bosque devuelve 56
;;

;; Prueba:

(define (suma-datos-arbol arbol)
    (+ (dato-arbol arbol)
       (suma-datos-bosque (hijos-arbol arbol))))

(define (suma-datos-bosque bosque)
    (if (null? bosque)
        0
        (+ (suma-datos-arbol (car bosque)) 
           (suma-datos-bosque (cdr bosque)))))

(define bosque (hijos-arbol arbol))

(check-equal? (suma-datos-arbol (car bosque)) 9)
(check-equal? (suma-datos-bosque (cdr bosque)) 56)


;; a.3)
;;
;; 1 - La invocación a map devuelve la lista '(9 14 42)
;; 2 - Las invocaciones a + en la ejecución de fold-right son:
;;
;;       (+ 42 15) => 57
;;       (+ 14 57) => 71
;;       (+ 9 71) => 80
;;

;; b.1)

(display "Probando ejercicio b.1)\n")
(define arbolb '(40 (23 (5 () ())
                        (32 (29 () ())
                            ()))
                    (45 ()
                        (56 () ()))))

(check-equal? (dato-arbolb (hijo-izq-arbolb (hijo-der-arbolb (hijo-izq-arbolb arbolb)))) 29)


;---------------------------------------------
; Ejercicio 2: (to-string-arbol arbol)
;------------------------------------

; to-string-arbol

(define (to-string-arbol arbol)
   (string-append (symbol->string (dato-arbol arbol))
                  (to-string-bosque (hijos-arbol arbol))))

(define (to-string-bosque bosque)
   (if (null? bosque)
       ""
       (string-append (to-string-arbol (car bosque))
                      (to-string-bosque (cdr bosque)))))
                              

;; Pruebas
(display "Probando 'to-string-arbol'\n")
(define arbol2 '(a (b (c (d)) (e)) (f)))
(check-equal? (to-string-arbol arbol2) "abcdef")

; to-string-arbol-fos

(define (to-string-arbol-fos arbol)
    (fold-left string-append
               (symbol->string (dato-arbol arbol))
               (map to-string-arbol-fos (hijos-arbol arbol))))

;; Pruebas
(display "Probando 'to-string-arbol-fos'\n")
(check-equal? (to-string-arbol-fos arbol2) "abcdef")


;----------------------------------------------
; Ejercicio 3: (ordenado-arbol? arbol)
;----------------------------------------------


; ordenado-arbol

; funciones auxiliares
(define (ordenada-lista lista)
  (if (null? (cdr lista))
      #t
      (and (< (car lista) (cadr lista))
           (ordenada-lista (cdr lista)))))

(define (raices bosque)
  (if (null? bosque)
      '()
      (cons (dato-arbol (car bosque))
            (raices (cdr bosque)))))

; funciones recursión mutua

(define (ordenado-arbol? arbol)
  (and (ordenada-lista (append (raices (hijos-arbol arbol))
                               (list (dato-arbol arbol))))
       (ordenado-bosque? (hijos-arbol arbol))))

(define (ordenado-bosque? bosque)
  (if (null? bosque)
      #t
      (and (ordenado-arbol? (car bosque))
           (ordenado-bosque? (cdr bosque)))))

;; Pruebas
(display "Probando 'ordenado-arbol'\n")

(check-true (ordenado-arbol? '(10 (5) (7))))
(check-true (ordenado-arbol? '(50 (10 (4) (6) (8)) (25 (15)))))
(check-false (ordenado-arbol? '(10 (8) (7))))
(check-false (ordenado-arbol? '(6 (5) (7))))
(check-false (ordenado-arbol? '(50 (10 (4) (6) (11)) (25) (15))))

; ordenado-arbol-fos

; función auxiliar
(define (and-lista lista)
  (fold-right (lambda(x y) (and x y)) #t lista))

(define (ordenado-arbol-fos? arbol)
  (and (ordenada-lista (append (map dato-arbol (hijos-arbol arbol))
                               (list (dato-arbol arbol))))
       (and-lista (map ordenado-arbol-fos? (hijos-arbol arbol)))))


;; Pruebas
(display "Probando 'ordenado-arbol-fos'\n")
(check-true (ordenado-arbol-fos? '(10 (5) (7))))
(check-true (ordenado-arbol-fos? '(50 (10 (4) (6) (8)) (25 (15)))))
(check-false (ordenado-arbol-fos? '(10 (8) (7))))
(check-false (ordenado-arbol-fos? '(6 (5) (7))))
(check-false (ordenado-arbol-fos? '(50 (10 (4) (6) (11)) (25) (15))))


;----------------------------------------------
; Ejercicio 4: (veces a b arbol)
;              (es-camino? lista arbol)
;----------------------------------------------

;; a

(define (suma-pareja p1 p2)
  (cons (+ (car p1) (car p2))
        (+ (cdr p1) (cdr p2))))

(define (comprueba-raiz a b arbol)
  (if (= a (dato-arbol arbol))
      (cons 1 0)
      (if (= b (dato-arbol arbol))
          (cons 0 1)
          (cons 0 0))))

;; recursión mutua

(define (veces a b arbol)
  (suma-pareja (comprueba-raiz a b arbol)
               (veces-bosque a b (hijos-arbol arbol))))

(define (veces-bosque a b bosque)
  (if (null? bosque)
      (cons 0 0)
      (suma-pareja (veces a b (car bosque))
                   (veces-bosque a b (cdr bosque)))))


;; fos
(define (veces-fos a b arbol)
  (fold-right suma-pareja
              (comprueba-raiz a b arbol)
              (map (lambda (subarbol)
                     (veces-fos a b subarbol)) (hijos-arbol arbol))))


;; Pruebas
(display "Probando 'veces'\n")
(define arbol3 '(1 (1 (1)) (2 (3) (2)) (1 (2) (3))))
(check-equal? (veces 1 2 arbol3) (cons 4 3))
(check-equal? (veces 4 3 arbol3) (cons 0 2))
(check-equal? (veces 4 5 arbol3) (cons 0 0))

(display "Probando 'veces-fos'\n")
(check-equal? (veces-fos 1 2 arbol3) (cons 4 3))
(check-equal? (veces-fos 4 3 arbol3) (cons 0 2))
(check-equal? (veces-fos 4 5 arbol3) (cons 0 0))

;; es-camino

(define (es-camino? lista arbol)
  (and (equal? (car lista) (dato-arbol arbol))
       (es-camino-bosque? (cdr lista) (hijos-arbol arbol))))

(define (es-camino-bosque? lista bosque)
  (cond
    ((and (null? bosque) (null? lista)) #t)
    ((or (null? bosque) (null? lista)) #f)
    (else (or (es-camino? lista (car bosque))
              (es-camino-bosque? lista (cdr bosque))))))


;; Pruebas
(display "Probando 'es-camino?'\n")
(define arbol4 '(a (a (a) (b)) (b (a) (c)) (c)))
(check-true (es-camino? '(a b a) arbol4))
(check-false (es-camino? '(a b) arbol4))
(check-false (es-camino? '(a b a b) arbol4))


;; nodos-nivel


(define (nodos-nivel n arbol)
  (if (= n 0)
      (list (dato-arbol arbol))
      (nodos-nivel-bosque (- n 1) (hijos-arbol arbol))))

(define (nodos-nivel-bosque n bosque)
  (if (null? bosque) '()
      (append (nodos-nivel n (car bosque))
              (nodos-nivel-bosque n (cdr bosque)))))


;; Pruebas
(display "Probando 'nodos-nivel'\n")
(define arbol5 '(1 (2 (3 (4) (2)) (5)) (6 (7))))
(check-equal? (nodos-nivel 0 arbol5) '(1))
(check-equal? (nodos-nivel 1 arbol5) '(2 6))
(check-equal? (nodos-nivel 2 arbol5) '(3 5 7))
(check-equal? (nodos-nivel 3 arbol5) '(4 2))


;----------------------------------------------
; Ejercicio 5: (pertenece? dato arbolb)
;              (ordenado? arbolb)
;              (camino-arbolb arbolb)
;----------------------------------------------

;; pertenece

(define (pertenece? dato arbolb)
  (cond
    ((vacio-arbolb? arbolb) #f)
    ((= (dato-arbolb arbolb) dato) #t)
    ((> (dato-arbolb arbolb) dato)
     (pertenece? dato (hijo-izq-arbolb arbolb)))
    (else (pertenece? dato (hijo-der-arbolb arbolb)))))

;; Pruebas
(display "Probando 'pertenece?'\n")
(define arbolb2 '(40 (18 (3 () ())
                        (23 ()
                            (29 () ())))
                    (52 (47 () ())
                        ())))
(check-true (pertenece? 29 arbolb2))
(check-false (pertenece? 42 arbolb2))


;; ordenado-arbolb?


(define (comprueba-menor dato arbolb)
  (cond
    ((vacio-arbolb? arbolb) #t)
    ((hoja-arbolb? arbolb)
     (< (dato-arbolb arbolb) dato))
    (else
     (comprueba-menor dato (hijo-der-arbolb arbolb)))))

(define (comprueba-mayor dato arbolb)
  (cond
    ((vacio-arbolb? arbolb) #t)
    ((hoja-arbolb? arbolb)
     (> (dato-arbolb arbolb) dato))
    (else
     (comprueba-mayor dato (hijo-izq-arbolb arbolb)))))

(define (ordenado-arbolb? arbolb)
  (if (or (vacio-arbolb? arbolb)
          (hoja-arbolb? arbolb))
      #t
      (and (comprueba-menor (dato-arbolb arbolb) (hijo-izq-arbolb arbolb))
           (comprueba-mayor (dato-arbolb arbolb) (hijo-der-arbolb arbolb))
           (ordenado-arbolb? (hijo-izq-arbolb arbolb))
           (ordenado-arbolb? (hijo-der-arbolb arbolb)))))



;; Pruebas
(display "Probando 'ordenado-arbolb?'\n")
(define arbolb3 '(6 (3 (1 () ())
                       (5 () ()))
                    (8 (7 () ())
                       (9 () ()))))
(define arbolb4 '(6 (3 (1 () ())
                       (5 () ()))
                    (7 (8 () ())
                       (9 () ()))))
(check-true (ordenado-arbolb? arbolb3))
(check-false (ordenado-arbolb? arbolb4))

;; camino-arbolb

 (define (camino-arbolb arbolb lista)
    (cond
      ((null? lista) '())
      ((equal? (car lista) '=)
           (cons (dato-arbolb arbolb) (camino-arbolb arbolb (cdr lista))))
      ((equal? (car lista) '<)
           (camino-arbolb (hijo-izq-arbolb arbolb) (cdr lista) ))
      ((equal? (car lista) '>)
           (camino-arbolb (hijo-der-arbolb arbolb) (cdr lista) ))))


;; Pruebas
(display "Probando 'camino-arbolb'\n")
(define arbolb5 '(9 (5 (3 (1 () ())
                          (4 () ()))
                       (7 () ()))
                    (15 (13 (10 () ())
                            (14 () ()))
                        (20 ()
                            (23 () ())))))
               
(check-equal? (camino-arbolb arbolb5 '(= < < = > =)) '(9 3 4))
(check-equal? (camino-arbolb arbolb5 '(> = < < =)) '(15 10))
