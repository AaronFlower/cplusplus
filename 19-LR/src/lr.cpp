#include <cassert>

#include "lr.h"
#include "utils.h"

using arma::mat;
using arma::uvec;       // uvec = ucolvec = Col<uword>, uword = unsigned int
using arma::randi;      // random integer
using arma::distr_param;
using std::cout;
using std::endl;

LR::LR(size_t num_features):num_features(num_features) {

    // randomly initialize the weight vector.
    theta.set_size(num_features);
    theta.randn();  // normal , zero-mean unit-variance
    bias = 0;       // initilaize bias to be zero.
}

void LR::train(arma::mat X,
        arma::colvec Y,
        double alpha,
        double lambda,
        size_t batch_size,
        size_t num_iter
        ) {
    assert(X.n_cols == num_features);

    size_t m = X.n_rows;
    assert(Y.n_rows == m);

    cout << "[+] start training with learning rate: " << alpha
        << ", lambda: " << lambda << ", batch size: " << batch_size << endl;

    for (size_t i = 0; i < num_iter; ++i) {
        // randomly smaple `batch_size` rows from X
        // uvec = ucolvec = Col<uword> , uword = unsigned int for indices
        uvec index = randi<uvec>(batch_size, distr_param(0, m - 1));

        mat X_sample = X.rows(index);
        colvec y_sample = Y.elem(index);

        // inference
        colvec y_hat = Utils::sigmoid(X_sample * theta + bias);
        colvec y_diff = y_hat - y_sample;

        colvec gradient = X_sample.t() * y_diff;


        // with bias there's a messy update formula.
        theta = theta - (lambda / m) * theta -  (alpha / m) * gradient;
        bias = bias - alpha * mean(y_diff);

        if ((i + 1) % 5 == 0 || (i + 1) == num_iter) {
            double loss = mean(Utils::cross_entropy_loss(
                        Y,
                        Utils::sigmoid(X * theta + bias)
                        )
                    );
            double accuracy = Utils::accuracy(Y, predict(X));
            cout << "After iteration " << i << " : " << " loss " << loss
                << ", accuracy " << accuracy << endl;
        }
    }
}

colvec LR::predict(mat X) {
    colvec Y = arma::trunc(Utils::sigmoid(X * theta + bias) + 0.5);
    return Y;
}

colvec LR::getTheta() {
    return theta;
}

double LR::getBias() {
    return bias;
}
