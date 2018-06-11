;;
;; Solución práctica 3
;; 

#lang r6rs
(import (rnrs)
        (schemeunit))


;------------------------------------
; Ejercicio 1: (multiplo-de n lista-nums)
;------------------------------------

(define (es-multiplo? x y)
  (= (mod x y) 0))

;; Pruebas

(display "Probando 'es-multiplo?' \n")
(check-true (es-multiplo? 10 2))
(check-true (es-multiplo? 21 7))

(define (multiplo-de n lista-num)
  (if (null? lista-num)
      '()
      (cons (es-multiplo? (car lista-num) n)
            (multiplo-de n  (cdr lista-num)))))
          

;; Pruebas
(display "Probando 'multiplo-de'\n")
(check-equal? (multiplo-de 10 '(100 23 10 300  48 7)) '(#t #f #t #t #f #f))
(check-equal? (multiplo-de 2 '(3 7 9)) '(#f #f #f))
(check-equal? (multiplo-de 2 '(2 8 6)) '(#t #t #t))


;------------------------------------
; Ejercicio 2: (calcular-lista lista)
;------------------------------------


(define (calcula-pareja op pareja)
  (cond ((equal? op '+) (+ (car pareja) (cdr pareja)))
        ((equal? op '-) (- (car pareja) (cdr pareja)))
        ((equal? op '/) (/ (car pareja) (cdr pareja)))
        ((equal? op '*) (* (car pareja) (cdr pareja)))))

;; Pruebas
(display "Probando 'calcula-pareja'\n")
(check-equal? (calcula-pareja '+ (cons 2 4)) 6)
(check-equal? (calcula-pareja '/ (cons -6 2)) -3)

(define (calcular-lista lista)
  (if (null? lista) '()
      (cons (calcula-pareja (car lista) (cadr lista))
            (calcular-lista (cddr lista)))))

;; Pruebas
(display "Probando 'calcular-lista'\n")
(check-equal? (calcular-lista '(+ (2 . 3) * (4 . 5))) '(5 20))
(check-equal? (calcular-lista '(/ (-6 . 2) - (4.5 . 0.5))) '(-3 4.0))


;------------------------------------
; Ejercicio 3: (expande lista-parejas)
;------------------------------------


(define (expande-pareja pareja)
  (if (= (cdr pareja) 0)
      '()
      (cons (car pareja)
            (expande-pareja (cons (car pareja) 
                                  (- (cdr pareja) 1))))))

;; Pruebas
(display "Probando 'expande-pareja'\n")
(check-equal? (expande-pareja (cons #t 4)) '(#t #t #t #t))
(check-equal? (expande-pareja (cons 'a 6)) '(a a a a a a))
(check-equal? (expande-pareja (cons 'a 0)) '())

(define (expande lista-parejas)
  (if (null?  lista-parejas)
      '()
      (append (expande-pareja (car lista-parejas))
              (expande (cdr lista-parejas)))))


;; Pruebas
(display "Probando 'expande'\n")
(check-equal? (expande '((#t . 3) ("LPP" . 2) (b . 4))) '(#t #t #t "LPP" "LPP" b b b b))
(check-equal? (expande '()) '())
(check-equal? (expande '((4 . 3))) '(4 4 4))


;------------------------------------
; Ejercicio 4: (resultados‐quiniela lista‐parejas)
;              (cuenta-resultados resultado lista-resultados)
;              (cuenta-resultados-lista lista-resultados)
;------------------------------------

; Apartado a)

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


(define (resultados-quiniela lista-resultados)
  (if (null? lista-resultados)
      '()
      (cons (resultado-partido (car lista-resultados))
            (resultados-quiniela (cdr lista-resultados)))))


;; Pruebas
(display "Probando 'resultados-quiniela'\n")
(check-equal? (resultados-quiniela '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) '(2 X 2 1 X))
(check-equal? (resultados-quiniela '((2 . 2))) '(X))
(check-equal? (resultados-quiniela '((3 . 2) (4 . 3) (3 . 5))) '(1 1 2))

; Apartado b)

(define (cuenta-resultados resultado lista-resultados)
  (cond
    ((null? lista-resultados) 0)
    ((equal? resultado (resultado-partido (car lista-resultados)))
     (+ 1 (cuenta-resultados resultado (cdr lista-resultados))))
    (else (cuenta-resultados resultado (cdr lista-resultados)))))
  
;; Pruebas
(display "Probando 'cuenta-resultados'\n")
(check-equal? (cuenta-resultados 'X '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 2)
(check-equal? (cuenta-resultados 1 '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 1)
(check-equal? (cuenta-resultados 2 '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) 2)

; Apartado c)

(define (inc-pos n lista)
  (if (= n 0)
      (cons (+ 1 (car lista)) (cdr lista))
      (cons (car lista) (inc-pos (- n 1) (cdr lista)))))

;; Pruebas
(display "Probando 'inc-pos'\n")
(check-equal? (inc-pos 3 '(2 7 9 10)) '(2 7 9 11))
(check-equal? (inc-pos 1 '(2 7 9 10)) '(2 8 9 10))

(define (cuenta-resultados-lista lista-resultados)
  (cond
    ((null? lista-resultados) (list 0 0 0))
    ((equal? 1 (resultado-partido (car lista-resultados)))
     (inc-pos 0 (cuenta-resultados-lista (cdr lista-resultados))))    
    ((equal? 'X (resultado-partido (car lista-resultados)))
     (inc-pos 1 (cuenta-resultados-lista (cdr lista-resultados))))
    (else (inc-pos 2 (cuenta-resultados-lista (cdr lista-resultados))))))


;; Pruebas
(display "Probando 'cuenta-resultados-lista'\n")
(check-equal? (cuenta-resultados-lista '((1 . 2) (4 . 4) (3 . 5) (6 . 2) (9 . 9))) '(1 2 2))
(check-equal? (cuenta-resultados-lista '((2 . 2))) '(0 1 0))
(check-equal? (cuenta-resultados-lista '((3 . 2) (4 . 3) (3 . 5))) '(2 0 1))


;------------------------------------
; Ejercicio 5: (filtra-simbolos lista-simbolos lista-num)
;------------------------------------

(define (filtra-simbolos lista-simbolos lista-num)
  (cond
    ((null? lista-simbolos) '())
    ((= (string-length  (symbol->string (car lista-simbolos))) (car lista-num)) 
     (cons (cons (car lista-simbolos)
                 (car lista-num))
           (filtra-simbolos (cdr lista-simbolos) (cdr lista-num))))
    (else
     (filtra-simbolos (cdr lista-simbolos) (cdr lista-num)))))

;; Pruebas
(display "Probando 'filtra-simbolos'\n")
(check-equal? (filtra-simbolos '(este es un ejercicio de examen) '(2 1 2 9 1 6)) '((un . 2) (ejercicio . 9) (examen . 6)))
(check-equal? (filtra-simbolos '( este es un ejercicio de examen) '(2 1 3 4 1 5)) '())
(check-equal? (filtra-simbolos '(ejercicio) '(9)) '((ejercicio . 9)))