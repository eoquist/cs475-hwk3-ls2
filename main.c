#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"
#include <unistd.h>

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	printf("argc = %d\n",argc);

	if(argv[1] == NULL){
		printf("Correct usage is: ./ls2 <path> [exact-match-pattern]\n");
		return 0;
	}

	if(argc == 2){
		ls2List(argv[1],0);
	}else if(argc == 3){
		ls2Search(argv[1], argv[2]);
	}

	// // stack stores the lines to print out
	// stack_t *s = initstack();

	// push(s, "Hello1");
	// push(s, "Hello2");
	// push(s, "Hello3");

	// // print stack
	// printstack(s);

	// // free up stack
	// freestack(s);
	return 0;
}