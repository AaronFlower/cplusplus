#include<iostream>

using namespace std;

namespace foo 
{
	int value() {return 5;}
}

namespace bar 
{
	const double pi = 3.1416;
	double value() { return 2 * pi; }
}
// namespaces can be split: Two segments of a code can be declared int the same namespace:
namespace foo
{
	float exp = 2.718;
}	

namespace first
{
	int x = 5;
	int y = 10;
}

namespace second 
{
	double x = 3.1416;
	double y = 2.7183;
}


int main(void) {
	cout << "namespace foo::value() " << foo::value() << "\n";
	cout << "namespace bar::value() " << bar::value() << "\n";
	cout << "namespace bar::pi " << bar::pi << endl;
	cout << "namespace split declared, foo::exp " << foo::exp << "\n";

	// The keyword using introduces a name into the current declarative region.
	using first::x;
	using second::y;
	using namespace second;
	cout << "first::x " << x<< "\n";
	cout << "second::y " << y<< "\n";
	cout << "first::y " << first::y << "\n";
	return 0;
}

