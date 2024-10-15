#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

static void zero(int **a)
{
	*a = 0;
}

static void aux(int *a)
{
	free(a);
	zero(&a);
	printf("%p\n", a);
}

int main(void)
{
	int *a;

	a = malloc(sizeof(int) * 1);
	printf("%p\n", a);
	aux(a);
	printf("%p\n", a);
	return (0);
}











