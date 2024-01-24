/**
 * C program to check whether a directory exists or not.
 */

#include <stdio.h>
#include <sys/stat.h>

int isDirectoryExists(const char *path);


int main()
{
    char path[100];

    printf("Enter directory path: ");
    scanf("%s", path);


    // Check if directory exists or not
    if (isDirectoryExists(path))
    {
        printf("Directory exists at path '%s'\n", path);
    }
    else
    {
        printf("Directory does not exists at path '%s'\n", path);
    }

    return 0;
}



/**
 * Function to check whether a directory exists or not.
 * It returns 1 if given path is directory and  exists 
 * otherwise returns 0.
 */
int isDirectoryExists(const char *path)
{
    struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}