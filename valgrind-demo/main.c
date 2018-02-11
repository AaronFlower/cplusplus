#include <stdlib.h>
#include <stdio.h>

void foo () {
	int*	pi = (int*)malloc(sizeof(int) * 10);
	pi[11] = 100;
	printf("pi[11]: %d", pi[11]);
//	free(pi);
	pi = NULL;
}

int main (int argc, char* argv[]) {
	foo();
	return 0;
}
