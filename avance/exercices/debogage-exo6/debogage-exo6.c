#include <stdio.h>

const int TRUE = 1;
const int FALSE = 0;

int function_returning_false()
{
	return FALSE;
}

int main()
{
	if (function_returning_false) {
		printf("function returned true\n");
	}
}

