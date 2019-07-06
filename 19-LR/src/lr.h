#ifndef Logistic_Regression_H__
#define Logistic_Regression_H__

#include <armadillo>
#include <string>

class LR {
public:
    LR(size_t num_features);
    ~LR() = default;

    void train(arma::mat X,
            arma::colvec Y,
            double alpha,
            double lambda,
            size_t batch_size,
            size_t num_iter);

    arma::mat predict(arma::mat X);

    arma::colvec getTheta();

    double getBias();

    void saveWeights(std::string filename);
    void loadWeigths(std::string filename);

private:
    size_t num_features;
    arma::colvec theta; // LR weights
    double bias;        // LR bias term
};

#endif /* ifndef Logistic_Regression_H__ */
