#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

void show (int a[])
{
	for (int i = 0; i < 10; ++i) {
		cout << a[i] << "\t";
	}
}

int main()
{
	// 基本用法。
	int a [] = {1, 2, 4, 0, 7, 8, 3, -1, 2, 9};
	cout << "Before sorting: ";
	show(a);
	sort(a, a + 10);
	cout << "\n After sorting: ";
	show(a);
	// 传入一个 Lambda 表达式。
	char str[] = "Hello world!";
	int count = strlen(str);
	cout << "\nBefore sorting: " << str << endl;
	sort(str, str + count, [](int a, int b) {
		return tolower(a) < tolower(b);
	});	
	cout << "After sorting:" << str << endl;

	int myints[] = {32, 71, 12, 45, 26, 80, 53, 33};
	std::vector<int> vecNums(myints, myints + 8);
	sort(vecNums.begin(), vecNums.end(), [](int a, int b) {
		int num1 = a - (a / 10) * 10;
		int num2 = b - (b / 10) * 10;
		return num1 < num2;
	});
	cout << "My vector numbers:" ; 
	for (auto ele : vecNums) {
		cout << ele << "\t";
	}
	return 0;
}