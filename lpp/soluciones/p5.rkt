;;
;; Solución práctica 5
;;

#lang r6rs
(import (rnrs)
        (schemeunit)
        (graphics turtles))

;---------------------------------------------
; Ejercicio 1: (cuadrado-lista lista)
;              (max-lista lista)
;----------------------------------------------

; cuadrado-lista

(define (cuadrado x)
  (* x x))

(define (cuadrado-lista lista)
  (cuadrado-lista-iter lista '()))

(define (cuadrado-lista-iter lista res)
  (if (null? lista)
      res
      (cuadrado-lista-iter (cdr lista)
                           (append res (list (cuadrado (car lista)))))))


;; Pruebas
(display "Probando 'cuadrado-lista'\n")
(check-equal? (cuadrado-lista '(2 3 4 5)) '(4 9 16 25))


; max-lista


(define (max-lista lista)
  (max-lista-iter (cdr lista) (car lista)))

(define (max-lista-iter lista res)
  (if (null? lista)
      res
      (max-lista-iter (cdr lista) (max res (car lista)))))

;; Pruebas
(display "Probando 'max-lista'\n")
(check-equal? (max-lista '(2 5 9 12 5 0 4)) 12)


;---------------------------------------------
; Ejercicio 2: (expande-pareja pareja)
;              (expande lista-parejas)
;------------------------------------

; expande-pareja

(define (expande-pareja pareja)
  (expande-pareja-iter pareja '()))

(define (expande-pareja-iter pareja res)
  (if (= 0 (cdr pareja))
      res
      (expande-pareja-iter (cons (car pareja)
                                 (- (cdr pareja) 1))
                           (cons (car pareja) res))))

;; Pruebas
(display "Probando 'expande-pareja'\n")
(check-equal? (expande-pareja (cons 'a 4)) '(a a a a))

; expande

(define (expande lista-parejas)
  (expande-iter lista-parejas '()))

(define (expande-iter lista-parejas res)
  (if (null? lista-parejas)
      res
      (expande-iter (cdr lista-parejas)
                    (append res (expande-pareja (car lista-parejas))))))

;; Pruebas
(display "Probando 'expande'\n")
(check-equal? (expande '((#t . 3) ("LPP" . 2) (b . 4))) '(#t #t #t "LPP" "LPP" b b b b))


;----------------------------------------------
; Ejercicio 3: (aplica-funciones lista-parejas)
;----------------------------------------------

(define (aplica-funciones lista)
  (aplica-funciones-iter lista '()))

(define (aplica-funciones-iter lista res)
  (if (null? lista)
      res
      (aplica-funciones-iter (cdr lista) (append res
                                                 (list ((caar lista) (cdar lista)))))))

   
;; Pruebas
(display "Probando 'aplica-funciones'\n")
(check-equal? (aplica-funciones (list (cons sqrt 16) (cons list 2) (cons even? 5) (cons not #f))) '(4 (2) #f #t))



;-----------------------------------------
; Ejercicio 4: (binario-a-decimal str)
;              (decimal-a-hexadecimal str)
;-----------------------------------------

; binario-a-decimal

;;
;; Definimos las funciones 'car-string' y 'cdr-string'
;; para poder trabajar con las cadenas como con las listas.
;;
;; Otra forma de hacerlo, también correcta, es convertir el
;; string con el número binario en una lista de caracteres
;; con la función 'string->list' y trabajar con esa lista de
;; caracteres.
;;

(define (cdr-string cadena)
  (substring cadena 1 (string-length cadena)))

(define (car-string cadena)
  (string-ref cadena 0))

(define (caracter-a-num caracter)
  (- (char->integer caracter)
     (char->integer #\0)))


;; Función principal

(define (binario-a-decimal binario)
  (binario-a-decimal-iter binario 0))

(define (binario-a-decimal-iter binario result)
  (if (equal? binario "")
      result
      (binario-a-decimal-iter (cdr-string binario)
                              (+ (* (caracter-a-num (car-string binario))
                                    (expt 2 (string-length (cdr-string binario))))
                                 result))))

;; Pruebas
(display "Probando 'binario-a-decimal'\n")
(check-equal? (binario-a-decimal "101") 5)
(check-equal? (binario-a-decimal "101101") 45)


; decimal-a-hexadecimal


(define (num-a-hexadecimal decimal)
  (if (< decimal 10)
      (integer->char (+ (char->integer #\0)
                        decimal))
      (integer->char (+ (char->integer #\A)
                        (- decimal 10)))))

(define (caracter-a-string caracter)
  (make-string 1 caracter))

(define (decimal-a-hexadecimal decimal)
  (decimal-a-hexadecimal-iter decimal ""))

(define (decimal-a-hexadecimal-iter decimal result)
  (if (< decimal 16)
      (string-append (caracter-a-string (num-a-hexadecimal decimal))
                     result)
      (decimal-a-hexadecimal-iter (div decimal 16)
                                  (string-append (caracter-a-string (num-a-hexadecimal (mod decimal 16)))
                                                 result))))
      
;; Pruebas
(display "Probando 'decimal-a-hexadecimal'\n")
(check-equal? (decimal-a-hexadecimal 200) "C8")
(check-equal? (decimal-a-hexadecimal 999) "3E7")


;--------------------------------------------------
; Ejercicio 5: (piramide-hexagonal lado decremento)
;              (alfombra-sierpinski tam min)
;--------------------------------------------------


; piramide-hexagonal

(turtles #t)

(define (hexagono lado)
   (begin
      (draw lado)
      (turn 60)
      (draw lado)
      (turn 60)
      (draw lado)
      (turn 60)
      (draw lado)
      (turn 60)
      (draw lado)
      (turn 60)
      (draw lado)
      (turn 60)))
      
(define (piramide-hexagonal lado decremento)
   (if (> lado 10)
      (begin
         (hexagono lado)
         (turn 60)
         (move decremento)
         (turn -60)
         (piramide-hexagonal (- lado decremento) decremento))))


;; Pruebas
(piramide-hexagonal 150 10)

; Apartado b)
(define (dibuja-cuadrado w)
  (begin
    (draw w)
    (turn 90)
    (draw w)
    (turn 90)
    (draw w)
    (turn 90)
    (draw w)
    (turn 90)))

(define (alfombra-sierpinski w min)
    (if (> w min)
        (begin
          (alfombra-sierpinski (/ w 3) min)
          (move (/ w 3))
          (alfombra-sierpinski (/ w 3) min)
          (move (/ w 3))
          (alfombra-sierpinski (/ w 3) min)
          (turn 90)(move (/ w 3))(turn -90)
          (alfombra-sierpinski (/ w 3) min)
          (turn 90)(move (/ w 3))(turn -90)
          (alfombra-sierpinski (/ w 3) min)
          (turn 180)(move(/ w 3))(turn -180)
          (alfombra-sierpinski (/ w 3) min)
          (turn 180)(move(/ w 3))(turn -180)
          (alfombra-sierpinski (/ w 3) min)
          (turn -90) (move (/ w 3)) (turn 90)
          (alfombra-sierpinski (/ w 3) min)
          (turn -90) (move (/ w 3)) (turn 90)) ;; volvemos a la posición original
        (dibuja-cuadrado w)))

;; Pruebas
(turn -90)
(move 500)
(turn 90)
(alfombra-sierpinski 300 6)
