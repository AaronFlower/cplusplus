#include <iostream>
#include <bitset>
#include <string>

using std::cout;
using std::endl;
using std::bitset;
using std::string;

int main(void)
{
    bitset<8> bs1(108);
    bitset<8> bs2("11101101");
    bitset<8> bs3;

    cout << "bs1: " << bs1 << endl;
    cout << "bs2: " << bs2 << endl;
    cout << "bs3: " << bs3 << endl;

    bs1.reset();
    bs1.set(2);
    bs1.set(3);
    bs1.set(3);
    cout << "bs1: " << bs1 << endl;

    bs2.set();
    bs2.reset(2);
    bs2.reset(3);
    bs2.reset(3);
    cout << "bs2: " << bs2 << endl;

    if (bs2[1] == 1) {
        cout << "bs1: bit 1 is set" << endl;
    } else {
        cout << "bs1: bit 1 is unset" << endl;
    }


    //Constuct 01: 8 bits initialized to zero
    bitset<8> bitset1;
    cout << "Construction without any parameter. Content of bitset1 :"
        << bitset1 << endl;

    //Construct 02: Construct it from a integer number
    bitset<8> bitset2(177);
    cout << "Constructor with int as parameter. Content of bitset2: "
        << bitset2 << endl;

    //Construct 03: Construct it from string
    bitset<8> bitset3(string("11111100"));
    cout << "Constructor with string parameter.Content of bitset3: "
        << bitset3 << endl;

    //Usage 01: Set and Reset a bit in the bitset
    bitset2.reset(); cout << bitset2 << endl;
    bitset2.set(4); cout << bitset2 << endl;
    bitset2.set(7); cout << bitset2 << endl;

    bitset3.set();  cout << bitset3 << endl;
    bitset3.reset(1); cout << bitset3 << endl;
    bitset3.reset(2); cout << bitset3 << endl;

    //Usage 02: Testing a perticular Bit
    cout << "Bitset3: " << bitset3 << endl;
    for (size_t i=0; i<bitset3.size(); i++)
    {
        if (bitset3.test(i))
            cout << "Bit " << i << " is Set" << endl;
        else
            cout << "Bit " << i << " is Not Set" << endl;
    }

    //Usage 03: Number of bits set
    bitset3.reset();
    bitset3.set(2);
    bitset3.set(4);
    bitset3.set(5);
    cout << bitset3.count() << " Bit(s) set" << endl;

    return 0;
}
