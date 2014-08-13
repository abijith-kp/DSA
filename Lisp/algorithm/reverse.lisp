(defun rl (x)
    (if (null x) 
        () 
        (append (rl (cdr x)) (list (car x)))))

(setq l1 '(a b c d e f g h))
(setq l2 (rl '(a b c d e f g h)))
