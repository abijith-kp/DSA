(defun mirror (x)
    (if (null x) 
        () 
        (if (listp (car x))
            (append (mirror (cdr x)) (list (mirror (car x))))
            (append (mirror (cdr x)) (list (car x))))))

(setq l1 '(a b c (d e) f (g h)))
(setq l2 (mirror l1))
