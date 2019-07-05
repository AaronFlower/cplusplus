#include <iostream>
#include <armadillo>

using namespace arma;

int main(void)
{
    mat A = randu<mat>(4, 5);
    mat B = randu<mat>(4, 5);

    std:: cout << A * B.t() << std::endl;
    return 0;
}
