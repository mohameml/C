#include <stdio.h>

int main()
{
	int *age;

	printf("Bonjour,\n");
	printf("Entrez votre age\n");
	scanf("%d", age);
	printf("Vous avez %d ans\n", *age);
	return 0;
}
