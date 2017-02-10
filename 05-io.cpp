#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main (void) {
	string endStr= "endl has an additional behavior: the stream's buffer (if any) is flushed";
	cout << endStr << endl;
	int i;
	cout << "Please input an integer value:" << endl;
	cin >> i;
 	cout << "The value you entered is : " << i << endl;
	cout << " and its double is :" << i * 2 << ".\n";

	// cin extraction always considers spaces (whitespaces, tabs, new-line... ) as 
	// terminating the value being extracted.
	
	// getline
	getchar();	
	string myStr;
	cout << "What's your name? \n";
 	getline(cin, myStr);
	cout << "Hello " << myStr << ".\n";
	cout << "What's your favorite team?\n";
	getline(cin, myStr);
	cout << "I like " << myStr << " too !\n";	

	// Using stringstream : allow string to be treaded as a stream
	// This feature is most useful to convert strings to numerical values and vice versa.
	string mystr;
	float price = 0;
	int quantity = 0;
  cout << "Please enter the price: " << endl;
	getline(cin, mystr);
	stringstream(mystr) >> price;
	cout << "Please enter the quantity: " << endl;
	getline(cin, mystr);
	stringstream(mystr) >> quantity;
	cout << "The total price is: " << quantity * price << endl;

	
	return 0;
}

