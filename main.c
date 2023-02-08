#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "stack.h"
#include "ls2.h"
#include <unistd.h>

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	if (argv[1] == NULL || argc > 3)
	{
		printf("Correct usage is: ./ls2 <path> [exact-match-pattern]\n");
		return 0;
	}

	DIR *currDir;
	currDir = opendir(argv[1]);
	if (currDir == NULL) // Checkif dir exists
	{
		printf("Can't open directory '%s' Exiting...\n", argv[1]);
		exit(0);
	}

	stack_t *s = initstack(); // stack stores DIR and filenames
	char *path[1000]; // 1000 == length of dir contents -- unknown quantity

	if (argc == 2)
	{
		ls2List(argv[1], 0);
	}
	else if (argc == 3)
	{
		*path = ls2Search(argv[1], argv[2]);
	}

	// /* Now, lets work on b */
	// for (int i = 0; i < MAX_STRLEN; i++)
	// {
	// 	if ((path[i] = malloc(sizeof(char) * MAX_STRLEN)) == NULL)
	// 	{ 
	// 		printf("unable to allocate memory \n");
	// 		return -1;
	// 	}
	// }

	free(path);
	printstack(s); // print stack
	freestack(s);  // free up stack
	return 0;
}