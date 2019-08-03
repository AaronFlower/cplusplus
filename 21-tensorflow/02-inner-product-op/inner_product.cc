/**
 * 添加新的操作，一般分为三个步骤：
 * 1. 定义新操作的接口。(及定义输入，输入和属性等）
 * 2. 实现操作功能。(可能根据不同的设备实现不同的内核操作）
 * 3. 将实现与操作绑定。
 *
 * 因为 TF 使用的是 AD 自动微分，我们可能还需要实现对应的梯度计算。
 */

#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/platform/default/logging.h"
#include "tensorflow/core/framework/shape_inference.h"
#include "tensorflow/core/framework/op_kernel.h"

using namespace tensorflow;

// 1. 定义接口
REGISTER_OP("InnerProduct")
    .Input("input: float")   // a.shape = (nl_1, 1)
    .Input("weights: float") // w.shape = (nl, nl_1)
    .Output("inner_product: float") // z = (nl, 1)
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
        shape_inference::ShapeHandle input_shape;
        shape_inference::ShapeHandle weight_shape;

        // WithRank 如果 rank 配置，则将 shape 返回给第三个参数
        // 否则 return an error.
        // IF_RETURN_IF_ERROR 如果发生错误就返回.
        TF_RETURN_IF_ERROR(c->WithRank(c->input(0), 2, &input_shape));
        TF_RETURN_IF_ERROR(c->WithRank(c->input(1), 2, &weight_shape));

        auto nl = c->Dim(weight_shape, 0);
        auto nl_1 = c->Dim(weight_shape, 1);
        auto al_1 = c->Dim(input_shape, 0);

        // 保证权重矩阵和输入单元是可以相乘的. 即看下是否能够 merge
        shape_inference::DimensionHandle merged;
        TF_RETURN_IF_ERROR(c->Merge(al_1, nl_1, &merged));

        c->set_output(0, c->Matrix(nl, 1));
        return Status::OK();
    });

// Implementation of an inner product operation, Dense Layer without bias.
// 2. 实现 CPU 版本的内核
class InnerProductOp: public OpKernel {
public:
    explicit InnerProductOp(OpKernelConstruction* context):OpKernel(context) {
    }

    // Compute the inner product
    void Compute(OpKernelContext* context) override {
        // DCHECK_EQ Debug Check
        DCHECK_EQ(2, context->num_inputs());

        const Tensor& input = context->input(0);
        const Tensor& weights = context->input(1);

        const TensorShape& weights_shape = weights.shape();

        // create output_shape
        TensorShape output_shape;
        output_shape.AddDim(weights_shape.dim_size(0));
        output_shape.AddDim(1);

        // create output tensor
        Tensor* output = nullptr;
        OP_REQUIRES_OK(context, context->allocate_output(0, output_shape,
                    &output));

        // Get the responding Eigen tensors for data access.
        // TF 用的是 Eigen
        auto input_tensor = input.matrix<float>();
        auto weights_tensor = weights.matrix<float>();
        auto output_tensor = output->matrix<float>();

        for (size_t i = 0; i < output->shape().dim_size(0); ++i) {
            output_tensor(i, 0) = 0;
            for (size_t j = 0; j < weights.shape().dim_size(1); ++j) {
                output_tensor(i, 0) += weights_tensor(i, j) *
                    input_tensor(j, 0);
            }
        }
    }
};


// 3. 将 CPU 版的内核与操作绑定
REGISTER_KERNEL_BUILDER(Name("InnerProduct").Device(DEVICE_CPU),
        InnerProductOp);
