#include	<iostream>
using namespace std;

int add (int a, int b)
{
	return a + b;
}

int sub (int a, int b)
{
	return a - b;
}

/**
 * Pointer to function 函数指针的使用。
 * int (* operation) (int, int)
 * 函数返回类型 (* 函数指针名称)(函数参数1， 参数参数2)
 */
int clalc(int (* operation) (int, int), int a, int b)
{
	return operation(a, b);
}
/**
 * 关于数组的参数传递，如果不能传递数组和长度的话，就用一个数组引用来传递。
 * http://stackoverflow.com/questions/1328223/when-a-function-has-a-specific-size-array-parameter-why-is-it-replaced-with-a-p
 */
int * arrayMap(int (& a)[5], int (* mapFunc) (int, int))
{
	int count = sizeof(a) / sizeof(*a);
	int * b = (int *)malloc(sizeof(a));
	for (int i = 0; i < count; ++i) {
		b [i] = mapFunc(a[i], i);
	}
	return b;
}

int main (void) 
{
	int a = 2, b = 1;
	cout << add(a, b) << "\t" << clalc(add, 2, 1) << endl;
	cout << sub(a, b) << "\t" << clalc(sub, 2, 1) << endl;
	int (* clalcFunc) (int, int);
	clalcFunc = add;
	cout << "Calc Func exectue: " << clalcFunc(10, 100) << endl;
	cout << "Self map function: \n" << endl;
	int arr [5] = {1, 2, 3, 4, 5};
	cout << "Indx plus value \n" << endl;
	int * brr = arrayMap(arr, add);
	for (int i = 0; i < 5; ++i) {
		cout << brr[i] << "\t";
	}
	cout << sizeof(brr) / sizeof(brr[0]) << endl;
	// use lambda expressions
	int * crr = arrayMap(arr, [](int value, int index) {
		return value * value;
	});
	cout << "Sqrt map array\n" << endl;
	for (int i = 0; i < 5; ++i) {
		cout << crr[i] << "\t";
	}
	return 0;
}