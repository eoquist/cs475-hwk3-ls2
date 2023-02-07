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