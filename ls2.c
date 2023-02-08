#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // lstat(..) system call
#include <unistd.h>
#include "ls2.h"

void ls2List(char *path, int indent)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;

    if ((currDir = opendir(path)) == NULL)
    {
        strcat(path, "/..");
    }
    else
    {
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

                // path pain
                strcat(path, "/");
                strcat(path, entry->d_name);
                // printf("\t\t current path: %s\n", path);

                ls2List(path, indent + 4);
            }
            else
            {
                stat(entry->d_name, &st);
                off_t size = st.st_size;
                printf("%*s%s (%ld bytes)\n", indent, "", entry->d_name, size); // !!! 8 bytes for way too many files
            }
        }
        strcat(path, "/..");
    }
    closedir(currDir); // Close DIR and exit
}

void ls2Search(char *path, char *filenameToMatch)
{
    DIR *currDir;
    struct dirent *entry;
    // struct stat st;

    currDir = opendir(path);
    if (currDir == NULL)
    {
        // return from whence ye came, wench
    }
    else
    {
        // Look at entries
        while ((entry = readdir(currDir)) != NULL)
        {
            if (strcmp(entry->d_name, filenameToMatch) == 0)
            {
                // if matching file found, push all parent 'dir_name/ (directory)' and the matching file with its size in bytes
                printf("%s ", entry->d_name);
            }
            // if not found - no print required
            // ls2Search(path,filenameToMatch); // such that it's a path that hasnt been explored yet
        }
    }
    closedir(currDir); // Close DIR and exit
}