#include<iostream>
#include<vector>

using namespace std;

class PermutationGenerator {
	private:
		vector<int> base;
		int size;
	
	public:
		PermutationGenerator (int n): size(n){}

		vector<int> operator()() {
			if (base.empty()) {
				for (int i = 0; i < size; ++i) {
					base.push_back(i + 1);
				}
			}
			return base;
		}
};

void print(vector<int> v) {
	 vector<int>::const_iterator b = v.cbegin();
	 while(b < v.cend()) {
		cout << *b << "\t";
		b++;
	 }
 	 cout << endl;	 
}

int main(void) {
	PermutationGenerator p(5);
	print(p());
	return 0;
}
