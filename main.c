#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"
#include <unistd.h>
#include <sys/stat.h> // lstat(..) system call

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	if(argc == 1){
		ls2List(argv[1]);
	}else if(argc == 2){
		ls2Search(argv[1], argv[2]);
	}else{
		printf("Correct usage is: ./ls2Sol <path> [exact-match-pattern]");
	}

	// stack stores the lines to print out
	stack_t *s = initstack();

	push(s, "Hello1");
	push(s, "Hello2");
	push(s, "Hello3");

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;
}

void ls2List(char* path){
    currDir = opendir(argv[1]); // Check to see if you can open directory 
    if (currDir == NULL) {
		printf ("Can't open directory '%s'\n", argv[1]);
        return 1;
    }

	// Process each entry.
	entry = readdir(currDir);
    while ( entry != NULL) {
        printf ("%s ", entry.d_name); 
    }

	// if no path found
	// printf("%s is not a directory path! Exiting...",pathname)
	// then exit

    // Close directory and exit.
    closedir (currDir);
    return 0;
}

void ls2Search(char* path, char* filenameToMatch){
	currDir = opendir(argv[1]); // Check to see if you can open directory 
    if (currDir == NULL) {
		printf ("Can't open directory '%s'\n", argv[1]);
        return 1;
    }

	// Process each entry.
	entry = readdir(currDir);
    while ( entry != NULL) {
        printf ("%s ", entry.d_name); 
    }

	// if no path found
	// printf("%s is not a directory path! Exiting...",pathname)
	// then exit

	// if matching file found
	// print the directory names plus (directory) and then main with its size
	// if not found - no print required

    // Close directory and exit.
    closedir (currDir);
    return 0;
}

// malloc usage
// Employee *my_employees = (Employee*) malloc(num_employees * sizeof(Employee));  // on the heap!
// free(my_employees); // deallocate space after we're done!
// my_employees = NULL; // defensive programming