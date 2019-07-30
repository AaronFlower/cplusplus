"""
Tests for the inner product Tensorflow operation
"""

import unittest
import numpy as np
import tensorflow as tf


inner_product_module = tf.load_op_library('./build/libinner_product.dylib')


class InnerProductOpTest(unittest.TestCase):

    def test_innerProductHardCoded(self):
        res = inner_product_module.inner_product([[1], [2]], [[1, 2], [3, 4]])
        print(res)

res = inner_product_module.inner_product([[1], [2]], [[1, 2], [3, 4]])
print(res)
