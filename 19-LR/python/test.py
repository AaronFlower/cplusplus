'''
To test our LibLR
'''

import numpy as np
import matplotlib.pyplot as plt

import LibLR


def loadData():
    data = np.loadtxt('data.txt')
    X, y = data[:, 0:2], data[:, 2]
    return X, y


X, y = loadData()

X_train, y_train = X[:90], y[:90].reshape(90, 1)
X_test, y_test = X[90:], y[90:].reshape(10, 1)

lr = LibLR.LR(2)

X_train = X[:2]

# lr.train(X_train, [1, 0], 0.1, 0, 10, 10);
# lr.train(np.mat(X_train), np.mat([1, 0]), 0.1, 0, 10, 10);

print(lr.getBias())
theta = lr.getTheta()
print(theta)
