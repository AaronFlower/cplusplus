#include <cstdlib>
#include <iostream>

void test()
{

    char i = -128;
    std::cout << (int)i << " " <<  (int) (i >> 1) <<  " div " << (i/2) << std::endl;

    i = -127;
    std::cout << (int)i << " " <<  (int) (i >> 1) << " div " << (i/2) << std::endl;

}

int main(void)
{
    test();
    srand(time(NULL)); // use current time as seed for random generator
    int n = rand() % 1000;
    std::cout << n << " " << (n / 2) << std::endl; 
    n = -(rand() % 1000);
    std::cout << n << " " << (n / 2) << std::endl; 
    return 0;
}
