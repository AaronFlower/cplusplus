#include <iostream>
#include <string>

using namespace std;

string concatenate(const string & a, const string & b, const string & glue = "") {
	return a + glue + b;
}

int factorial(int n) {
	if (n == 1 || n == 0) {
		return 1;
	}
	return n * factorial(n - 1);
}

int main(void) {
	string a{"Hello"};
	string b{"Functions"};

	cout << concatenate(a, b, "-->") << ".\n";
	cout << "Factorial recursive function" << ".\n";
	cout << factorial(3) << endl;

	return 0;
}
