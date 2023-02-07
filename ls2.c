#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // lstat(..) system call
#include <unistd.h>
#include "ls2.h"

// TODO: function definitions here for ls2
void ls2List(char *path)
{
    DIR *currDir;
    struct dirent *entry;

    currDir = opendir(path); // Check to see if you can open directory
    if (currDir == NULL)
    {
        printf("Can't open directory '%s'\n", path);
        exit(0); /* return to OS */
    }

    while ((entry = readdir(currDir)) != NULL)
    { // Look at each entry.
        printf("%s ", entry->d_name);
    }

    // if no path found
    // printf("%s is not a directory path! Exiting...",pathname)
    // then exit

    // if matching file found
    // print the directory names plus (directory) and then main with its size
    // if not found - no print required

    // Close directory and exit.
    closedir(currDir);
    exit(0); /* return to OS */
}

void ls2Search(char *path, char *filenameToMatch)
{
    DIR *currDir;
    struct dirent *entry;

    currDir = opendir(path); // Check to see if you can open directory
    if (currDir == NULL)
    {
        printf("Can't open directory '%s'\n", path);
        exit(0); /* return to OS */
    }

    while ((entry = readdir(currDir)) != NULL)
    { // Look at each entry.
        if (strcmp(entry->d_name, filenameToMatch) == 0)
        {
            printf("%s ", entry->d_name);
        }
    }

    // if no path found
    // printf("%s is not a directory path! Exiting...",pathname)
    // then exit

    // if matching file found
    // print the directory names plus (directory) and then main with its size
    // if not found - no print required

    // Close directory and exit.
    closedir(currDir);
    exit(0); /* return to OS */
}

// malloc usage
// Employee *my_employees = (Employee*) malloc(num_employees * sizeof(Employee));  // on the heap!
// free(my_employees); // deallocate space after we're done!
// my_employees = NULL; // defensive programming
