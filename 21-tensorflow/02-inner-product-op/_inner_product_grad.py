"""
将 FP 操作与梯度操作进行绑定。
"""

import tensorflow as tf
from tensorflow.python.framework import ops

inner_product_grad_module = tf.load_op_library(
    './build/libinner_product_grad.dylib')


@ops.RegisterGradient("InnerProduct")
def _inner_product_grad_cc(op, grad):
    """
    The gradient for `inner_product` using the operation implement in C++.
    - op: `inner_product` operation that we are differentiating, which we can
        use to find the inputs and outputs of the original op.
    - grad: gradient with respect to the output of the `inner_product` op.

    Return: gradients with respect to the output of `inner_product`
    """
    return inner_product_grad_module.inner_product_grad(grad, op.inputs[0],
                                                        op.inputs[1])
