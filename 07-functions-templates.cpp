#include <iostream>
#include <string>

using namespace std;

// Function overloading
int doubleValue(int a ) {
	return a * 2;
}
string doubleValue(const string &str) {
	return str + str;
}

// Template 
template <class T>
T sum(T a, T b) {
	T result;
	result = a + b;
	return result;
}

// Template two classes
template <class T, class U>
bool areEqual(T a, U b) {
	return a == b;
}

template <class T, int N>
T fixedMultiply(T val) {
	return val * N;
}

int main(void) {
	int a = 2;
	float f = 3.14;
	cout << "Double integer: " << doubleValue(a) << endl;
	cout << "Double float: " << doubleValue(f) << endl;
	cout << "Double string: " << doubleValue("Foo") << endl;

	cout << "Template Function:" << endl;
	cout << sum(1, 2) << ", " << sum<int>(10, 100) << endl;
	cout << sum(3.14, 2.23) << ", " << sum<double>(2.719, 2.719) << endl;
	cout << sum(string("Hello "), string(" template "))<< endl;

	cout << "Are equal ? " << areEqual(10, 10.0) << endl;
	
	cout << "Fixed multiply " << fixedMultiply<int,2>(10) << ".\n";
	cout << "Fixed multiply " << fixedMultiply<int,10>(10) << ".\n";

	return 0;
}

