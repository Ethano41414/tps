Exercice 0

(define carre (lambda (x) (* x x)))
(carre 5)

(define quad (lambda (x pow)
    (letrec ((puiss (lambda (value count)
        (if (< count pow) (
            puiss (* x value) (+ count 1)
        )
            value
        )
    )))
    (puiss 1 0)
    )
))
(quad 3 3)
(define puiss64(lambda (x)
    (letrec ((puiss2 (lambda (value curr_pow)
        (if (< curr_pow 64) (
            puiss2 (* value value) (* curr_pow 2)
        )
            value
        )
    )))
    (puiss2 x 1)
    )
))

(puiss64 2)


Exercice 1

(define cercle(lambda(r) (
    list (* 6.28 r) (* 3.14 (* r r))
)
))

(cercle 1)


Exercice 2


(define fac(lambda (n)
    (letrec ((facto (lambda (value max count)
        (if (<= count max) (
            facto (* value count) max (+ 1 count)
        )
            value
        )
    )))
    (if (or (< n 0) (not (integer? n))) (
        error "ERROR: negative or real number in factorial function"
    ) (
       facto 1 n 1
    ))
    )
))

(fac 5)
(fac 0)
(fac 1)
(fac -1)




Exercice 3

(define som_int(lambda (n)
    (letrec ((sum (lambda (S max i)
        (if (<= i max) (
            sum (+ S i) max (+ i 1)
        )
            S
        )
    )))
    (sum 0 n 0)
    )
))

(som_int 0)
(som_int 4)


(define somme_carre(lambda (start end)
    (letrec ((sum2 (lambda (S i)
        (if (<= i end) (
            sum2 (+ S i) (+ i 1)
        )
            S
        )
    )))
    (if (< start end) (
        sum2 0 start
    ) (
        if (= start end)
           0
           (error "ERROR: end is superior to start in somme carre")
        
    ))
    )
))

(somme_carre 0 4)
(somme_carre 8 8)
(somme_carre 4 6)
(somme_carre 6 2)



Exercice 4

(define long(lambda (L)
    (letrec ((len (lambda (pointer curr_len)
        (if (null? pointer)
            curr_len
        (
            len (cdr pointer) (+ curr_len 1)
        )
        )
    )))
    (len L 0)
    )
))

(long '())
(long '(5 2))
(long '(4 8 9 7 3 1 5 4))


(define minimum(lambda (L)
    (letrec ((minim (lambda (pointer min)
        (if (null? pointer)
            min
        (if (< (car pointer) min)
            (minim (cdr pointer) (car pointer))
            (minim (cdr pointer) min)
        ))
    )))
    (if (null? L)
        (error "ERROR void list")
        (minim L (car L))
    )
    )
))

(minimum '())
(minimum '(5 2))
(minimum '(4 8 9 7 3 1 5 4))


fonction foldleft

(define foldleft(lambda (f l init)
    (letrec ((flr (lambda (f l last)
        (if (null? l)
            last
        (
            flr f (cdr l) (f (car l) last)
        )
        )
    )))
    (if (null? l) init
    (flr f l init)
    )
    )
))


(define somme(lambda (L)
    (foldleft + L 0)
))

(equal?
  (map somme (list '(4 5 6 8) '(5 8) '(-5 5 4)))
  '(23 13 4)
)


(define produit(lambda (L)
    (if (null? L)
      0
      (foldleft * L 1)
    )
))

(equal?
  (map produit (list '() '(4 0 6 8) '(5 8) '(-5 5 4)))
  '(0 0 40 -100)
)


(define nbpos(lambda (L)
    (letrec ((rpc (lambda (pointer count)
        (if (null? pointer)
            count
            (if (< 0 (car pointer))
                (rpc (cdr pointer) (+ count 1))
                (rpc (cdr pointer) count)
            )
        )
    )))
    (rpc L 0)
    )
))

(equal?
  (map nbpos (list '(4 0 6 8) '(-8 -1 0) '(6 0 4 -5 5 4)))
  '(3 0 4)
)






Exercice 5
(define last(lambda (L)
    (letrec ((find (lambda (pointer)
        (if (null? (cdr pointer))
            (car pointer)
            (find (cdr pointer))
        )
    )))
    (if (null? L)
        (error "ERROR: void list, no last element")
        (find L)
    )
    )
))

(equal?
  (map last (list '(4 0 6 8) '(-8 -1 0) '(6 0 4 -5 5 4)))
  '(8 0 4)
)


Exercice 6

(define insere_pos(lambda (pos x l)
    (if (null? l)
        (if (zero? pos)
            (cons x l)
            (if (> pos 0)
                (error "ERROR: too long index")
                l
            )
        )
    (cons (if (zero? pos) x (car l)) (if(zero? pos) l (insere_pos (- pos 1) x (cdr l))))
    )
))

(insere_pos 7 5 '(4 4 4 4 4 4 4))
(insere_pos 0 5 '())




Exercice 7

(define miroir(lambda (l)
    (if (null? l)
        l
        (append (miroir (cdr l)) (list (car l)))
    )
))

(miroir '(4 8 7 6 5 4 8 7 5))
(miroir '())



Exercice 8
(define membre(lambda (x l)
    (if (null? l)
        (error "ERROR: unfined value")
        (if (= (car l) x) #t (membre x (cdr l)))
    )
))

(membre 0 '(0 4 587 6 3))
(membre 2 '(0 4 587 6 3))
(membre 6 '(0 4 587 6 3))
(membre 3 '(0 4 587 6 3))


(define membre2(lambda (x l)
    (if (null? l)
        #f
        (if (= (car l) x) #t (membre2 x (cdr l)))
    )
))

(membre2 0 '(0 4 587 6 3))
(membre2 2 '(0 4 587 6 3))
(membre2 6 '(0 4 587 6 3))
(membre2 3 '(0 4 587 6 3))



Exercice 9

(define epure(lambda (l)
    (letrec((repur (lambda (l lacc)
        (if (null? l)
            lacc
            (if (membre2 (car l) lacc)
                (repur (cdr l) lacc)
                (repur (cdr l) (append lacc ((car l))))
            )
        )
    )))
    (repur l ())
    )
))









































