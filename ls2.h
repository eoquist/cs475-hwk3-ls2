#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "
#define MAX_STRLEN 260

// TODO: Function declarations here for ls2
void ls2List(char *path, int indent);
stack_t *ls2Search(char *path, int indent, char *filenameToMatch, stack_t *stack);

#endif
