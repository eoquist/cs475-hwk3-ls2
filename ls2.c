#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2
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
