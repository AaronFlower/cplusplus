#include <iostream>

using namespace std;

int main(void) {
	int a = 1;
	int b(3);
	int c{3};
	
	auto result = a + b  * c;
	decltype(result) squared = result * result;

	cout<<"a:"<<a<<" b:"<<b<<" c:"<<c<<" result:"<<result<<endl;
	cout<<squared<<endl;

	return 0;
}

