

Exercice 1 (1)



universel
(define tous-egaux(lambda (l)
    (if (null? l)
        #t
        (if (null? (cdr l))
            #t
            (and (equal? (car l) (cadr l)) (tous-egaux (cdr l)))
        )
    )
))


existanciel
(define tous-egaux(lambda (l)
    (if (null? l)
        #t
        (if (null? (cdr l))
            #t
            (if (equal? (car l) (cadr l))
                (tous-egaux (cdr l))
                #f
            )
        )
    )
))

(tous-egaux '())
(tous-egaux '(5 5 5 5 5 5 5 5))
(tous-egaux '('(5 2) '(5 2) '(5 2) '(5 2) '(5 2) '(5 2)))
(tous-egaux '('(5 2) '(5 2) '(5 2) '(5 3) '(5 2) '(5 2)))
(tous-egaux '(1 0 1 1 1 1 1))
(tous-egaux '("art" "art"))
(tous-egaux '("art" "ert"))
(tous-egaux '(5))







Exercice 1 (2)

universel
(define tous-diff(lambda (l)
    (if (null? l)
        #t
        (if (null? (cdr l))
            #t
            (and (not (equal? (car l) (cadr l))) (tous-diff (cdr l)))
        )
    )
))


existenciel
(define tous-diff(lambda (l)
    (if (null? l)
        #t
        (if (null? (cdr l))
            #t
            (if (not (equal? (car l) (cadr l)))
                (tous-diff (cdr l))
                #f
            )
        )
    )
))

(tous-diff '())
(tous-diff '(1 2 3 4 5 6 7 8))
(tous-diff '('(1 2) '(5 2) '(1 2) '(5 2) '(1 2) '(5 2)))
(tous-diff '('(5 2) '(1 2) '(1 2) '(1 3) '(5 2) '(1 2)))
(tous-diff '(1 0 1 0 1 7 9))
(tous-diff '("art" "art"))
(tous-diff '("art" "ert"))
(tous-diff '(5))




Exercice 2 (1)

(define reflexive(lambda (R E)
    (if (null? E)
        #t
        (and (R (car E) (car E)) (reflexive R (cdr E)))
    )
))

(let (
    (E '(0 1 2 3 4 5 6))
    (R (lambda (x y) (= (modulo (- x y) 3) 0)))
)
(reflexive R E)
)


Exercice 2 (2)

(define syme(lambda (R E)
    (letrec((sym? (lambda (x l)
        (if (null? l)
            #t
            (if (equal? (R x (car l)) (R (car l) x))
                (sym? x (cdr l))
                #f
            )
        )
    )))
    (let((test (sym? (car E) (cdr E))))
        (if test
            test
            (syme R (cdr E))
        )
    )
    )
))
(define symetrique(lambda (R E)
    (if (null? E)
        #t
        (if (null? (cdr E))
            (R (car E) (car E))
            (syme R E)
        )
    )
))

(let (
    (E '(0 1 2 3 4 5 6))
    (A '(4))
    (V '())
    (R (lambda (x y) (= (modulo (- x y) 3) 0)))
)
(symetrique R E)
)



Exercice 2 (3)

(define transi?(lambda (R x y z)
    (or (not (and (R x y) (R y z))) (R x z))
))
(define all_tests(lambda (R orig l1 l2 l3)
    (if (null? l1)
        #t
        (if (null? l2)
            (all_tests R orig (cdr l1) orig orig)
            (if (null? l3)
                (all_tests R orig l1 (cdr l2) orig)
                (if (transi? R (car l1) (car l2) (car l3))
                    (all_tests R orig l1 l2 (cdr l3))
                    #f
                )
            )
        )
    )
))
(define transitive(lambda (R E)
    (if (null? E)
        #t
        (all_tests R E E E E)
    )
))                               quand tout se passe bien tu commences avec tout (E E E E) et tu finis avec rien, c'est bien pensé hein ? Comme dans la vraie vie                                 





Exercice 2  (4)

(define member?(lambda (value l) (if (null? l) #f (if (= value (car l)) #t (member? value (cdr l))))))

(define classe_equiv(lambda (R E curr_elm class)
    (if (null? E)
        class
        (if (R curr_elm (car E))
            (classe_equiv R (cdr E) curr_elm (append class (list (car E))))
            (classe_equiv R (cdr E) curr_elm class)
        )
    )
))

(define retirer_classe(lambda (E class new)
    (if (null? E)
        new
        (if (member? (car E) class)
            (retirer_classe (cdr E) class new)
            (retirer_classe (cdr E) class (append new (list (car E))))
        )
    )
))


(define quotient(lambda (R E)
    (letrec((quoti (lambda (e2 quotient_list)
        (if (null? e2)
            quotient_list
            (let ((classe (classe_equiv R e2 (car e2) '())))
                (quoti (retirer_classe e2 classe '()) (append quotient_list (list classe)))
            )
        )
    )))
    (quoti E '())
    )
))


(define relation(lambda (x y) (= (modulo (- x y) 3) 0)))

(quotient relation '(0 1 2 3 4 5 6 7 8 9))







Exercice 3

Exo 3 (1a)

(define sum_rs(lambda (n a)
    (if (= n 0)
        a
        (sum_rs (- n 1) (+ n a))
    )
))

(sum_rs 200 0)

(define sqr_sum_rs(lambda (n a)
    (if (= n 0)
        a
        (sqr_sum_rs (- n 1) (+ (* n n) a))
    )
))

(sqr_sum_rs 200 0)


Exo 3 (1b)
(define mul_rs(lambda (n a)
    (if (= n 0)
        a
        (mul_rs (- n 1) (* n a))
    )
))

(mul_rs 200 1)


Exo 3 (1c)

(define fibonacci_rs(lambda (n)
    (letrec((frec(lambda (n l)
        (if (zero? n)
            (cadr l)
            (frec (- n 1) (list (cadr l) (+ (car l) (cadr l))))
        )
    )))
    (if (zero? n)
        1
        (frec (- n 1) '(1 1))
    )
    )
))

(fibonacci_rs 10)




Exo 3 (2a)

(define sum_rd(lambda (k n)
    (cond
        ((zero? (- n k)) n) 
        ((zero? (- (- n k) 1)) (+ n k))
        (#t (+ (sum_rd k (inexact->exact (floor (/ (+ n k) 2)))) (sum_rd (inexact->exact (floor (+ (/ (+ k n) 2) 1))) n)))
    )
))

(sum_rd 1 200)


(define sqr_sum_rd(lambda (k n)
    (cond
        ((zero? (- n k)) (* n n)) 
        ((zero? (- (- n k) 1)) (+ (* n n) (* k k)))
        (#t (+ (sqr_sum_rd k (inexact->exact (floor (/ (+ n k) 2)))) (sqr_sum_rd (inexact->exact (floor (+ (/ (+ k n) 2) 1))) n)))
    )
))

(sqr_sum_rd 1 200)


Exo 3 (2b)

(define mul_rd(lambda (k n)
    (cond
        ((zero? (- n k)) n) 
        ((zero? (- (- n k) 1)) (* n k))
        (#t (* (mul_rd k (inexact->exact (floor (/ (+ n k) 2)))) (mul_rd (inexact->exact (floor (+ (/ (+ k n) 2) 1))) n)))
    )
))

(mul_rd 1 200)


Exo 3 (2c)

(define fibonacci_rd(lambda (n)
    (if (or (zero? n) (zero? (- n 1)))
        1
        (+ (fibonacci_rd (- n 1)) (fibonacci_rd (- n 2)))
    )
))

(fibonacci_rd 10)


Exo 3 (2d)

(define ordre2(lambda (n)
    (cond
        ((zero? n) 0)
        ((zero? (- n 1)) 1)
        (#t (+ n (+ (ordre2 (- n 1)) (ordre2 (- n 2)))))
    )
))

(ordre2 0)
(ordre2 1)
(ordre2 2)
(ordre2 3)




Exercice 4

(define puissance_cartesienne(lambda (E n)
    (if (zero? n)
        '()
        (letrec((ballade (lambda ()
        )))
        (if (null? E)
            '()
            (ballade())
        )
        )
    )
))




























































