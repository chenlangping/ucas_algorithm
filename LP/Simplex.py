import numpy as np
 
class Simplex(object):
    def __init__(self, obj):
        self.matrix = np.array([[0] + obj])
 
    def add_constraint(self, a, b):
        self.matrix = np.vstack([self.matrix, [b] + a])
 
    def solve(self):
        m, n = self.matrix.shape
        temp, B = np.vstack([np.zeros((1, m - 1)), np.eye(m - 1)]), list(range(n - 1, n + m - 1))
        matrix = self.matrix = np.hstack([self.matrix, temp])
        while matrix[0, 1:].min() < 0:
            print(matrix)
            print("\n")
            col = np.where(matrix[0, 1:] < 0)[0][0] + 1
            row = np.array([matrix[i][0] / matrix[i][col] if matrix[i][col] > 0 else 0x7fffffff for i in
                range(1, matrix.shape[0])]).argmin() + 1
            if matrix[row][col] <= 0:
                return None
            print(row)
            print(col)

            matrix[row] /= matrix[row][col]
            ids = np.arange(matrix.shape[0]) != row
            matrix[ids] -= matrix[row] * matrix[ids, col:col + 1]  
            B[row] = col
        return matrix[0][0]

#t = Simplex([-7, 7, -2,-1,-6,0])
#t.add_constraint([3, -1, 1,-2,0,0], -3)
#t.add_constraint([2, 1, 0,1,1,0], 4)
#t.add_constraint([-1, 3, 0,-3,0,1], 12)

t = Simplex([-1,-14,-6])
t.add_constraint([1,1,1],4)
t.add_constraint([1,0,0],2)
t.add_constraint([0,0,1],3)
t.add_constraint([0,3,1],6)

print(t.solve())
print(t.matrix)
