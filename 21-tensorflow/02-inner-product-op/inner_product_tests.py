"""
Tests for the inner product Tensorflow operation
"""

import unittest
import numpy as np
import tensorflow as tf
import _inner_product_grad


inner_product_module = tf.load_op_library('./build/libinner_product.dylib')


class InnerProductOpTest(unittest.TestCase):

    # def test_raiseExceptionWithIncompatibleDimensions(self):
    #     with self.assertRaises(ValueError):
    #         inner_product_module.inner_product([1, 2], [[1, 2], [3, 4]])

    def test_innerProductHardCoded(self):
        res = inner_product_module.inner_product([[1], [2]], [[1, 2], [3, 4]])
        self.assertEqual(res.shape, (2, 1))
        data = res.numpy()
        self.assertEqual(data[0][0], 5)
        self.assertEqual(data[1][0], 11)

    def test_innerProductGradient(self):
        # TF 的 matmul 和梯度
        x = tf.Variable([[-1], [0], [2]], name="inputs", dtype="float")
        W = tf.Variable(np.arange(1, 10).reshape(3, 3), name="weights",
                        dtype="float")
        with tf.GradientTape() as tape:
            z = tf.matmul(W, x)
        dz_dw, dz_dx = tape.gradient(z, [W, x])
        print(z)
        print(dz_dw, dz_dx)

        # 自定义操作的梯度
        with tf.GradientTape() as tape:
            z_inner = inner_product_module.inner_product(x, W)
        dz_dw_inner, dz_dx_inner = tape.gradient(z_inner, [x, W])
        print(z_inner)
        print(dz_dw_inner, dz_dx_inner)


if __name__ == "__main__":
    unittest.main()
