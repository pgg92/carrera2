;;
;; Solución práctica 6
;;

#lang r6rs
(import (rnrs)
        (schemeunit))

;;
;; Definimos la función hoja?
;;

(define (hoja? x)
  (not (list? x)))

;------------
; Ejercicio 1
;------------

(display "Probando ejercicio 1 a)\n")
(define lista-a '((a b) d (c (e) (f g) h)))
(check-equal? (cadddr (caddr lista-a)) 'h)


(display "Probando ejercicio 1 b)\n")
(define lista-b '(1 (6 (3) 10) (2) 8))
(check-equal? (caddr (cadr lista-b)) 10)

;---------------------------------------------
; Ejercicio 2: (cuenta-pares lista)
;              (cuenta-pares-fos lista)
;------------------------------------

; cuenta-pares

(define (cuenta-pares x)
  (cond
    ((null? x) 0)
    ((hoja? x) (if (even? x) 1 0))
    (else (+ (cuenta-pares (car x))
             (cuenta-pares (cdr x))))))


;; Pruebas
(display "Probando 'cuenta-pares'\n")
(check-equal? (cuenta-pares '(1 (2 3) 4 (5 6))) 3)
(check-equal? (cuenta-pares '(((1 2) 3 (4) 5) ((((6)))))) 3)

; cuenta-pares-fos

(define (cuenta-pares-fos lista)
  (fold-right + 0
              (map (lambda (x)
                     (if (hoja? x)
                         (if (even? x) 1 0)
                         (cuenta-pares-fos x))) lista)))

;; Pruebas
(display "Probando 'cuenta-pares-fos'\n")
(check-equal? (cuenta-pares-fos '(1 (2 3) 4 (5 6))) 3)
(check-equal? (cuenta-pares-fos '(((1 2) 3 (4) 5) ((((6)))))) 3)


;----------------------------------------------
; Ejercicio 3: (cumplen-predicado pred lista)
;              (cumplen-predicado-fos pred lista)
;----------------------------------------------

;; cumplen-predicado

(define (cumplen-predicado pred x)
  (cond
    ((null? x) '())
    ((hoja? x) (if (pred x) (list x) '()))
    (else (append (cumplen-predicado pred (car x))
                  (cumplen-predicado pred (cdr x))))))


;; Pruebas
(display "Probando 'cumplen-predicado'\n")
(check-equal? (cumplen-predicado even? '(1 (2 (3 (4))) (5 6))) '(2 4 6))
(check-equal? (cumplen-predicado pair? '(((1 . 2) 3 (4 . 3) 5) 6)) '((1 . 2) (4 . 3)))


;; cumplen-predicado-fos

(define (cumplen-predicado-fos pred lista)
  (fold-right append '()
              (map (lambda (x)
                     (if (hoja? x)
                         (if (pred x) (list x) '())
                         (cumplen-predicado-fos pred x))) lista)))

;; Pruebas
(display "Probando 'cumplen-predicado-fos'\n")
(check-equal? (cumplen-predicado-fos even? '(1 (2 (3 (4))) (5 6))) '(2 4 6))
(check-equal? (cumplen-predicado-fos pair? '(((1 . 2) 3 (4 . 3) 5) 6)) '((1 . 2) (4 . 3)))


;-----------------------------------------
; Ejercicio 4: (sustituye-elem lista elem-old elem-new)
;-----------------------------------------

(define (sustituye-elem x elem-old elem-new)
  (cond
    ((null? x) '())
    ((hoja? x) (if (equal? x elem-old) elem-new x))
    (else
     (cons (sustituye-elem (car x) elem-old elem-new)
           (sustituye-elem (cdr x) elem-old elem-new)))))
  
;; Pruebas
(display "Probando 'sustituye-elem'\n")
(check-equal? (sustituye-elem  '(a b (c d (e c)) c (f (c) g)) 'c 'h) '(a b (h d (e h)) h (f (h) g)))


;---------------------------------
; Ejercicio 5: (diff-listas l1 l2)
;---------------------------------

(define (diff-listas x1 x2)
  (cond
    ((null? x1) '())
    ((hoja? x1) (if (equal? x1 x2) '() (list (cons x1 x2))))
    (else (append (diff-listas (car x1) (car x2))
                  (diff-listas (cdr x1) (cdr x2))))))

;; Pruebas
(display "Probando 'diff-listas'\n")
(check-equal? (diff-listas '(a (b ((c)) d e) f) '(1 (b ((2)) 3 4) f)) '((a . 1) (c . 2) (d . 3) (e . 4)))
(check-equal? (diff-listas '((a b) c) '((a b) c)) '())

;-------------------------------------------------
; Ejercicio 6: (cuenta-hojas-debajo-nivel lista n)
;              (nivel-elemento lista)
;-------------------------------------------------


; cuenta-hojas-debajo-nivel

(define (cuenta-hojas-debajo-nivel x n)
  (cond
    ((null? x) 0)
    ((hoja? x) (if (< n 0) 1 0))
    (else
     (+ (cuenta-hojas-debajo-nivel (car x) (- n 1))
        (cuenta-hojas-debajo-nivel (cdr x) n)))))

;; Pruebas
(display "Probando 'cuenta-hojas-debajo-nivel'\n")
(check-equal? (cuenta-hojas-debajo-nivel '(10 2 (4 6 (9 3) (8 7) 12) 1) 2) 4)
(check-equal? (cuenta-hojas-debajo-nivel '(10 2 (4 6 (9 3) (8 7) 12) 1) 3) 0)

; nivel-elemento

(define (max-cdr pareja1 pareja2)
  (if (> (cdr pareja1)
         (cdr pareja2))
         pareja1
         pareja2))

(define (sumo1-nivel-pareja pareja)
  (cons (car pareja)
        (+ 1 (cdr pareja))))

(define (nivel-elemento lista)
  (cond ((null? lista) (cons 0 0))
        ((hoja? lista) (cons lista 0))
        (else (max-cdr (sumo1-nivel-pareja (nivel-elemento (car lista)))
                       (nivel-elemento (cdr lista))))))

;; Pruebas
(display "Probando 'nivel-elemento'\n")
(check-equal? (nivel-elemento '(2 (3))) '(3 . 2))
(check-equal? (nivel-elemento '((2) (3 (4)((((((5))) 6)) 7)) 8)) '(5 . 8))