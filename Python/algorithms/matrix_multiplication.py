#!/usr/bin/python
import sys
import multiprocessing as mp
import random
import time

matrix = []
n = 0

def row_multiply(row):#, output_row):
    result_row = []

    for x in xrange(n):
        t_sum = 0
        for y in xrange(n):
            t_sum = t_sum + (matrix[row][y] * matrix[y][x])
        result_row.append(t_sum)

    return result_row

def matrix_multiply_parallel():
    product_matrix = []

    pool = mp.Pool(4)
    product_matrix = pool.map(row_multiply, range(n))

    return product_matrix

def matrix_multiply_serial():
    product_matrix = []

    for row in xrange(n):
        product_matrix.append(row_multiply(row))

    return product_matrix


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print "ERROR"
        sys.exit(1)

    methods = [matrix_multiply_serial, matrix_multiply_parallel]
    i_n = int(sys.argv[1])
    method_opt = int(sys.argv[2])

    for n in map((lambda x: 2**x), range(1, i_n+1)):
        matrix = [[random.randint(1,10)    for i in xrange(n)]
                                           for j in xrange(n)]

        print "matrix created    n:", n
        t1 = time.time()
        methods[method_opt]()
        print "complete!!    time:", time.time() - t1
