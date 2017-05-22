#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	cout << "Content-Type: text/html\n\n";
	cout << "<!DOCTYPE html>";
	cout << "<html lang=\"en\">";
	cout << "<head>";
	cout << "	<meta charset=\"UTF-8\">";
	cout << "	<title>Document</title>";
	cout << "</head>";
	cout << "<body>";
	cout << "	Hello Cpp-cgi world!";
	cout << "</body>";
	cout << "</html>" << endl;
	return 0;
}