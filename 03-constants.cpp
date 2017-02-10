#include <iostream>
#include <string>

#define PI 3.1415926
#define NEWLINE '\n'


using namespace std;

int main(void) {
	// literals 
	bool isOk = true;
	int *iPtr = nullptr;
	string rawStr = R"(Never say \t \n escaped charachter!)";

	cout<<"bool"<<isOk<<endl;
	cout<<"nullptr:"<<iPtr<<endl;
	cout<<"rasStr:"<<rawStr<<endl;
	
	double r = 5.0;
	decltype(r) circle;

	circle = 2 * PI * r;

	cout << circle << NEWLINE;

	return 0;
}
	

