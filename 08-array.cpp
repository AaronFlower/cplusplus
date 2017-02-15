#include <iostream>
// 如果想使用 array 库的话.
#include <array>

using namespace std;

int main(void) {
	int foo[] = {10, 20, 30, 40};
	int bar [] {11, 22, 33, 44, 55 };
	int j = 0;
	for(auto ele : foo) {
		cout << "foo " << j++ << " : " << ele << "\n";
	}
	int i = 0;
	for(auto ele: bar) {
		cout << "bar " << i++ << " : " << ele << "\n";
	}

	// using array lib
	array<int, 4> zoo {2, 4, 6, 8};
	for(int i = 0; i < zoo.size(); ++i) {
		zoo[i]*=zoo[i];
	}
	int k = 0;
	for(auto ele: zoo) {
		cout << "zoo " << k++ << " : " << ele  << "\n";
	}

	return 0;
}
