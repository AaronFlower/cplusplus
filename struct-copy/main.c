#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strcpy

typedef struct {
	int age;
	char* name;
} person;

static void print_person(const person* p, const char* key) {
		printf("%s name: %s, age: %d \n", key, p->name, p->age);	
}

static void destroy_person (person* p) {
	free(p->name);
}

int main (void) {
	person p1, p2, p3;
	char *name;
	name = (char*)malloc(10);
	strcpy(name, "Aaron");
	
	p1.age = 20;
	p1.name = name;

	p2 = p1;
	printf("Before name: %s, %#X \n", name, &name);
	print_person(&p1, "p1");
	print_person(&p2, "p2");

	free(name);
	name = NULL;

	printf("After name: %s, %#X \n", name, &name);
	print_person(&p1, "p1");
	print_person(&p2, "p2");
/*

	p2 = p1;
	
	printf("Before: \n");
	print_person(&p1, "p1");
	print_person(&p2, "p2");
//	strcpy(p2.name, "Flower");
	printf("After: \n");
	print_person(&p1, "p1");
	print_person(&p2, "p2");
	
	memcpy(&p3, &p1, sizeof(p1));
	printf("Before: \n");
	print_person(&p1, "p1");
	print_person(&p3, "p3");
//	strcpy(p3.name, "Eason p3");
	printf("After: \n");
	print_person(&p1, "p1");
	print_person(&p2, "p2");
	print_person(&p3, "p3");

	free(p1.name);
	print_person(&p2, "p2");
	print_person(&p3, "p3");

*/
	return 0;
}
