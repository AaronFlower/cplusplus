#include <iostream>
#include <string>

using namespace std;

int main(void) {
	string str{"Hello World"};
	for(auto c: str) cout << "[" << c << "]" ;
	cout << endl;

	return 0;
}
