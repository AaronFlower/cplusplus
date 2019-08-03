/**
 * inner_product 对应的梯度计算，我们也是要实现的。因为它也是一个操作。
 * 所以实现和操作一样。
 * 1. 定义操作接口。
 * 2. 实现梯度计算。
 * 3. 绑定实现。
 */

#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/shape_inference.h"

using namespace tensorflow;

// 1. 定义接口
REGISTER_OP("InnerProductGrad")
    .Input("grad: float32")
    .Input("input: float32")
    .Input("weights: float32")
    .Output("grad_inputs: float32")
    .Output("grad_weights: float32");

// 2. 实现计算
class InnerProductGradOp : public OpKernel {
public:
    explicit InnerProductGradOp(OpKernelConstruction* context):
        OpKernel(context) {}

    void Compute(OpKernelContext* context) override {
        DCHECK_EQ(3, context->num_inputs());

        const Tensor& grad = context->input(0);
        const Tensor& input = context->input(1);
        const Tensor& weights = context->input(2);

        TensorShape input_shape = input.shape();
        TensorShape weights_shape = weights.shape();

        DCHECK_EQ(input_shape.dim_size(0), weights_shape.dim_size(1));
        DCHECK_EQ(weights_shape.dim_size(0), grad.shape().dim_size(0));

        // create output tensors
        Tensor* grad_input = nullptr;
        Tensor* grad_weights = nullptr;

        OP_REQUIRES_OK(context, context->allocate_output(0, input_shape,
                    &grad_input));
        OP_REQUIRES_OK(context, context->allocate_output(1, weights_shape,
                    &grad_weights));

        // Get the Eigen tensors for data access
        auto grad_tensor = grad.matrix<float>();
        auto weights_tensor = weights.matrix<float>();
        auto input_tensor = input.matrix<float>();
        auto grad_input_tensor = grad_input->matrix<float>();
        auto grad_weights_tensor = grad_weights->matrix<float>();

        size_t m = weights_shape.dim_size(0);
        size_t n = weights_shape.dim_size(1);

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                grad_weights_tensor(i, j) = grad_tensor(i, 0) *
                    input_tensor(j, 0);
            }
        }

        for (size_t i = 0; i < n; ++i) {
            grad_input_tensor(i, 0) = 0;
            for (size_t j = 0; j < n; ++j) {
                grad_input_tensor(i, 0) += grad_tensor(j, 0) *
                    weights_tensor(j, i);
            }
        }
    }
};

// 3. 注册操作
REGISTER_KERNEL_BUILDER(Name("InnerProductGrad").Device(DEVICE_CPU),
        InnerProductGradOp);
