#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	// DIR				*dir;
	// char			*cwd;
	// struct dirent	*file;

	// cwd = getcwd(0, 0);
	// dir = opendir(cwd);
	// free(cwd);
	// file = readdir(dir);
	// while (file)
	// {
	// 	printf("%s\n", file->d_name);
	// 	file = readdir(dir);
	// }
	// closedir(dir);
	int	*a;
	a = calloc(sizeof(int), 1);
	*a = 12;

	printf("%d\n", *a++);
	printf("%d\n", (*a));
	return (0);
}











