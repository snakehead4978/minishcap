#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	char	*a;
	a = calloc(sizeof(char), 1);
	printf("%lu\n", a);
	return (0);
}











