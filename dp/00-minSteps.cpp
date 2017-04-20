#include <iostream>
using namespace std;

const int MAX_NUM = 1000;

int findMinStepd(int n)
{
	int dp[MAX_NUM];
	dp[1] = 0;
	for (int i = 2; i <= n; ++i) {
		dp[i] = dp[i - 1] + 1;
		if (i % 2 == 0) {
			dp[i] = dp[i] < (dp[i/2] + 1) ? dp[i] : (dp[i/2] + 1);
		}		
		if (i % 3 == 0) {
			dp[i] = dp[i] < (dp[i/3] + 1) ? dp[i] : (dp[i/3] + 1);
		}
	}
	return dp[n];
}

int main(int argc, char const *argv[])
{
	cout << "The min steps of 20 " << findMinStepd(20) << endl;
	cout << "The min steps of 4 " << findMinStepd(4) << endl;
	cout << "The min steps of 7 " << findMinStepd(7) << endl;
	cout << "The min steps of 10 " << findMinStepd(10) << endl;
	return 0;
}