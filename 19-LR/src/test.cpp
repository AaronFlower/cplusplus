#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include "lr.h"
#include "utils.h"

using std::cout;
using std::endl;
using arma::sign;

TEST(arma, sign) {
    arma::colvec Y = { -1.5, -0.5, 0, 0.5, 1.5 };
    arma::colvec sY = sign(Y);

    EXPECT_THAT(sY, testing::ElementsAre(-1, -1, 0, 1, 1));
}

TEST(arma, Utils) {
    arma::colvec Y = { -1.5, -0.5, 0, 0.5, 1.5 };
    arma::colvec lY = arma::trunc(Utils::sigmoid(Y) + 0.5);
    EXPECT_THAT(lY, testing::ElementsAre(0, 0, 1, 1, 1));
}

TEST(test, LR) {
    LR model(2);
    // Oops, creates a new LR with 3 features.
    // with explicit constructor
    // model = 3;
    EXPECT_EQ(model.getTheta().n_rows, 2);
    EXPECT_EQ(model.getTheta().n_cols, 1);

    arma::mat X = {
        {3, 3},
        {4, 3},
        {1, 1}
    };

    arma::colvec y = {1, 1, 0};

    model.train(X, y, 1.0, 0, 3, 9);

    cout << model.getTheta();
    cout << model.getBias();

    colvec yH = model.predict(X);
    EXPECT_THAT(yH, testing::ElementsAre(1, 1, 0));
}
