#include <dirent.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // lstat(..) system call
#include <unistd.h>
#include "ls2.h"

/** This prints things in reverse order. Luckily, the listing does not needed to sorted in any particular order.
 * @param path holds the user inputted directory path to search
 * @param indent is an int that keeps track of how far to offset the string. This indents by width 4 each time it recurses.
 */
void ls2List(char *path, int indent)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;

    if ((currDir = opendir(path)) == NULL)
    {
        chdir(".."); // chdir my beloved -- I was using strcat() before and it was awful. Amen.
    }
    else // Look at entries
    {
        while ((entry = readdir(currDir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                {
                    continue; // don't want to get stuck in hell
                }
                printf("%*s%s/ (directory)\n", indent, "", entry->d_name);
                chdir(entry->d_name);

                ls2List(path, indent + 4);
            }
            else if (entry->d_type == DT_REG)
            {
                stat(entry->d_name, &st);
                off_t size = st.st_size;
                printf("%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);
            }
        }
        chdir("..");
    }
    closedir(currDir);
}

/**
 * @param path holds the user inputted directory path to search
 * @param indent is an int that keeps track of how far to offset the string. This indents by width 4 each time it recurses.
 * @param filenameToMatch is the name to match against
 * @param stack is a stack_t that contains all the lines that will be printed at the end of the recursion
 * @param depth is an integer storing how many subdirectory levels the recursion is away from path
 */
struct stack_t *ls2Search(char *path, int indent, char *filenameToMatch, stack_t *stack, int depth)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;
    char tmp[MAX_FILENAME];
    char cwd[MAX_FILENAME];
    tmp[0] = '\0';
    cwd[0] = '\0';

    currDir = opendir(path);
    if (currDir == NULL)
    {
        chdir("..");
    }
    else // Look at entries
    {
        while ((entry = readdir(currDir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                {
                    continue;
                }
                // sprintf(tmp, "%*s%s/ (directory)\n", indent, "", entry->d_name);
                // // tmp is now holding the string we may or may not want to hold onto -- what to do now?
                ls2Search(path, indent + 4, filenameToMatch, stack, ++depth);
            }
            else if ((entry->d_type == DT_REG) && strcmp(entry->d_name, filenameToMatch) == 0)
            {
                printf("%*stest is entry\n", indent, "");
                stat(entry->d_name, &st);
                off_t size = st.st_size;

                sprintf(tmp, "%*s%s (%ld", indent, "", entry->d_name, size);
                strcat(tmp, " )\n");

                printf("%*stest print tmp: %s\n", indent, "", tmp);
                // sprintf(tmp, "%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);

                for (int i = depth; i > 0; i--)
                {
                    chdir("..");
                    if (getcwd(cwd, sizeof(cwd)) == NULL)
                        perror("getcwd() error");
                    else
                    {
                        printf("current working directory is: %s\n", cwd);

                        sprintf(tmp, "%*s%s", indent, "", entry->d_name);
                        strcat(tmp, "/ (directory)\n");
                        // sprintf(tmp, "%*s%s/ (directory)\n", indent, "", cwd);
                        push(stack, tmp);
                    }
                }
            }
        }
        chdir("..");
    }
    if (pop(stack) != NULL)
    {
        printf("test print pre-stack");
        printstack(stack);
        printf("test print post-stack");
    }

    closedir(currDir);
    return stack;
}