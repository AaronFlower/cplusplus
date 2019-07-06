#ifndef LR_UTILS_H__
#define LR_UTILS_H__

#include <armadillo>

using arma::mat;
using arma::colvec;


class Utils {
public:
    static inline mat sigmoid(arma::mat logits);

    static inline double accuracy(colvec y, colvec yHat);

    static inline colvec cross_entropy_loss(colvec y, colvec yHat);
};

mat Utils::sigmoid(mat logits) {
    return 1.0 / (1 + exp(-logits));
}

double Utils::accuracy(colvec y, colvec yHat) {
    size_t n = y.n_rows;
    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        if ((y(i) >= 0.5 && yHat(i) >= 0.5) || (y(i) < 0.5 && yHat(i) < 0.5)) {
            ++count;
        }
    }

    return count * 1.0 / n;
}

colvec Utils::cross_entropy_loss(colvec y, colvec yHat) {
    // In armadillo `%` is elementwise multiplication.
    return -y % log(yHat) - (1 - y) % log(1 - yHat);
}

#endif /* ifndef LR_UTILS_H__ */
