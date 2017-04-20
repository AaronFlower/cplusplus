#include <iostream>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

/**
 * 使用递归。
 */
int lcsRecursive(char * strA, char * strB, int m, int n)
{
	if (m == 0 || n == 0) {
		return 0;
	}
	if (* strA == * strB) {
		return 1 + lcsRecursive(strA + 1, strB + 1, m - 1, n - 1);
	} else {
		int a = lcsRecursive(strA + 1, strB, m - 1, n);
		int b = lcsRecursive(strA, strB + 1, m, n - 1);
		return max(a, b);
	}
}

/**
 * 使用 tabulate
 */
int lcsTabulate(char * strA, char * strB, int m, int n)
{
	// 注意初始化数组大小和循环下标。
	int lcs[m + 1][n + 1], i, j;
	for (i = 0; i <= m; ++i) {
		for (j = 0; j <= n; ++j ) {
			if (i == 0 || j == 0) {
				lcs[i][j] = 0;
			} else if (strA[i - 1] == strB[j - 1]) {
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			} else {
				lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
			}
		}
	}
	return lcs[m][n];
}

int main(int argc, char const *argv[])
{
	char strA[] = "HelloKitXty";
	char strB[] = "eKitty";
	int m = strlen(strA);
	int n = strlen(strB);
	cout << "the longest common subsequence using recurision is :" << lcsRecursive(strA, strB, m, n) << endl;
	cout << "the longest common subsequence using tabulate is :" << lcsTabulate(strA, strB, m, n) << endl;
	return 0;
}