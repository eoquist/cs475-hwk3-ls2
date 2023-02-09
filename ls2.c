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

stack_t *ls2Search(char *path, int indent, char *filenameToMatch, stack_t *stack)
{
    DIR *currDir;
    struct dirent *entry;
    struct stat st;
    char tmp[MAX_STRLEN];
    char str[500]; // arbitrary size -- malloc better?
    tmp[0] = '\0';
    str[0] = '\0';

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
                snprintf(tmp, sizeof(tmp), "%*s%s/ (directory)\n", indent, "", entry->d_name);
                strcat(str, tmp);
                tmp[0] = '\0';

                ls2Search(path, indent + 4, filenameToMatch, stack);
            }
            else if (entry->d_type == DT_REG)
            {
                if (strcmp(entry->d_name, filenameToMatch) == 0)
                {
                    stat(entry->d_name, &st);
                    off_t size = st.st_size;

                    snprintf(tmp, sizeof(tmp), "%*s%s (%ld bytes)\n", indent, "", entry->d_name, size);
                    strcat(str, tmp);
                    tmp[0] = '\0';

                    push(stack, str);
                }
            }
        }
        chdir("..");
    }
    closedir(currDir);
    return stack;
}