#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // lstat(..) system call
#include <unistd.h>
#include "ls2.h"

/* This prints things in reverse order. Luckily, the listing does not needed to sorted in any particular order. */
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

char *ls2Search(char *path, char *filenameToMatch)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;
    char *cwd[MAX_STRLEN];

    // ptr = (int *)malloc(100 * sizeof(int));
    // // Since the size of int is 4 bytes, this statement will allocate 400 bytes of memory.
    // // And, the pointer ptr holds the address of the first byte in the allocated memory.
    // ptr = realloc(ptr, newSize);
    // // where ptr is reallocated with new size 'newSize'.

    currDir = opendir(path);
    if (currDir == NULL)
    {
        chdir("..");
    }
    else // Look at entries
    {
        while ((entry = readdir(currDir)) != NULL)
        {
            if (strcmp(entry->d_name, filenameToMatch) == 0)
            {
                stat(entry->d_name, &st);
                off_t size = st.st_size;
                getcwd(cwd, sizeof(cwd));

                // if matching file found, push all parent 'dir_name/ (directory)' and the matching file with its size in bytes
                // snprintf(str, sizeof(str), "%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);
            }
            // if not found - no print required
            // ls2Search(path,filenameToMatch); // such that it's a path that hasnt been explored yet
        }
        chdir("..");
    }
    closedir(currDir);
    return path;
}