;; (m c)  (m c) (m c)
;;   l1     b     l2

(boat '(3 3) '(0 0) '(0 0))

(defun check (x)
    (if (> (first x) (second x))
        nil
        T))

(defun boat (x y z)
    (if (check (list (- (first x) 1) (- (second x) 1)))))
