#include <iostream>
#include <string>

using namespace std;

int main(void){
	string str1 = "This is initial string";
	string str2("Hello");
	string str3{"Hello"};
	cout<<str1<<endl;
	str1 = "Changed! String changed!";
	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
	cout<<strcmp(str2.c_str(),str3.c_str()) << endl;

	// String with prefix
	string rawStr = R"(Kidding with raw stirng!\n escape is omitted!\t!)";
	cout<<rawStr<<endl;
	cout<<R"(string \n with \backslash)" << endl;
	//cout<<R"&%$(string with \backslash)&%$" << endl;	
	return 0;
}
