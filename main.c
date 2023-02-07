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
int main(int argc, char* argv[]) {
	if(argv[1] == NULL){
		printf("Correct usage is: ./ls2 <path> [exact-match-pattern]\n");
		return 0;
	}

	// Check to see if you can open directory
	DIR *currDir;
    currDir = opendir(argv[1]); 
    if (currDir == NULL)
    {
        printf("Can't open directory '%s' Exiting...\n", argv[1]);
        exit(0); /* return to OS */
    }

	if(argc == 2){
		ls2List(argv[1],0);
	}else if(argc == 3){
		ls2Search(argv[1], argv[2]);
	}
	return 0;
}