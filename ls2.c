#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // lstat(..) system call
#include <unistd.h>
#include "ls2.h"

// TODO: function definitions here for ls2
void ls2List(char *path, int indent)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;
    // char str[300]; 
    // stack_t *s = initstack(); // stack stores DIR and filenames
    
    // Check to see if you can open directory
    currDir = opendir(path); 
    if (currDir == NULL)
    {
        // printf("Can't open directory '%s' Exiting...\n", path);
        exit(0); /* return to OS */
        /*for some reason the tags dir doesnt exist in ls2Sol so idk why its causing me so much problems here :( */
    }

    // Look at entries
    while ((entry = readdir(currDir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        { 
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            { 
                continue; // don't want to get stuck in hell
            }
            printf("%*s%s/ (directory)\n", indent, "", entry->d_name);
            // snprintf(str, sizeof(str),"%*s%s/ (directory)\n", indent, "", entry->d_name);
            // push(s,str);
            // str[0] = '\0';

            /*
                clowning !!!
                need to make sure its not doing this depth first, essentially

                push(s,str);
            */
            // Construct new path from our base path
            strcat(path, "/");
            strcat(path, entry->d_name);
            ls2List(path, indent + 4);
        }
        else
        {
            stat(entry->d_name, &st);
            off_t size = st.st_size;

            printf("%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);
            // snprintf(str, sizeof(str),"%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);
            // push(s,str);
            // str[0] = '\0';
        }
    }

    // printstack(s); // print stack
    // freestack(s);  // free up stack

    closedir(currDir); // Close DIR and exit
}

void ls2Search(char *path, char *filenameToMatch)
{
    DIR *currDir;
    struct dirent *entry;
    // struct stat st;
    stack_t *s = initstack(); // stack stores DIR and filenames

    // Check to see if you can open directory
    currDir = opendir(path); 
    if (currDir == NULL)
    {
        printf("Can't open directory '%s' Exiting...\n", path);
        exit(0); /* return to OS */
    }

    // Look at entries
    while ((entry = readdir(currDir)) != NULL)
    { 
        if (strcmp(entry->d_name, filenameToMatch) == 0)
        {
            printf("%s ", entry->d_name);
        }
    }

    // if matching file found
    // print the directory names plus (directory) and then main with its size
    // if not found - no print required

    printstack(s); // print stack
    freestack(s);  // free up stack

    closedir(currDir); // Close DIR and exit
}

// malloc usage
// Employee *my_employees = (Employee*) malloc(num_employees * sizeof(Employee));  // on the heap!
// free(my_employees); // deallocate space after we're done!
// my_employees = NULL; // defensive programming
