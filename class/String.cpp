#include <iostream>
#include <cstring>

using namespace std;

class String {
public:
	String (const char * str = nullptr);
	~String (void);
	String (const String & other);
	String & operator = (const String & other);

	friend ostream & operator << (ostream &, const String & str);

private:
	char * m_data = nullptr;
};

String::String (const char * str) {
	if (str != nullptr) {
		auto len = strlen(str);
		m_data = new char[len + 1];
		strcpy(m_data, str);
	}
}

String::~String (void) {
	delete [] m_data;
}

String::String(const String & other) {
	if (other.m_data != nullptr) {
		auto len = strlen(other.m_data);
		m_data = new char[len + 1];
		strcpy(m_data, other.m_data);
	}
}

String & String::operator = (const String & other) {
	if (&other == this) {
		return * this;
	}
	if (m_data != nullptr) {
		delete [] m_data;
	}
	auto len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
	return * this;
}

ostream & operator << (ostream &os, const String & str) {
	os << str.m_data ;
	return os;
}

int main(int argc, char const *argv[])
{
	String str("Hello CString Constructor.");
	String str2(str);
	cout << str << endl;
	cout << "String 2 copied from str : " << str2 <<endl;
	String str3;
	str3 = str2;
	cout << "String 3 assigned by str2: " << str3 << endl;
	return 0;
}