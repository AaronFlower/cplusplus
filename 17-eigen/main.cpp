#include <iostream>
#include "Eigen/Dense"

using Eigen::MatrixXd;
using std::cout;
using std::endl;

int main(void)
{
    MatrixXd m(2, 2);

    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << m << endl;

    MatrixXd m2 = MatrixXd::Random(3, 3);
    cout << "m2 : \n" << m2 << endl;

    MatrixXd m3 = MatrixXd::Constant(3, 3, 1.2);
    cout << "m3 : \n" << m3 << endl;

    Eigen::VectorXd v(3);
    v << 1, 2, 3;


    cout << "m2 * v = \n" << m2 * v << endl;



    return 0;
}
