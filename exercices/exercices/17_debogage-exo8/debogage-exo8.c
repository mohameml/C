#include <stdio.h>

int main()
{
	char *hello = "hello, world!" + 3;
	char *charstring = 'h' + "ello, world!";

	printf("hello=%s, charstring=%s.\n", hello, charstring);
	printf("Eh non, on n'est pas en Java !\n");
	return 0;
}

