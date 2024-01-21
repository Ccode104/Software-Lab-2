/**
 * C program to remove empty lines from a file.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

/* Function declarations */
int  isEmpty(const char *str);
void removeEmptyLines(FILE *srcFile, FILE *tempFile);
void printFile(FILE *fptr);


int main()
{
    FILE *srcFile;
    FILE *tempFile;

    char path[100];


    /* Input file path */
    printf("Enter file path: ");
    scanf("%s", path);


    /* Try to open file */
    srcFile  = fopen(path, "r");
    tempFile = fopen("remove-blanks.tmp", "w");


    /* Exit if file not opened successfully */
    if (srcFile == NULL || tempFile == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }



    printf("\nFile contents before removing all empty lines.\n\n");
    printFile(srcFile);


    // Move src file pointer to beginning
    rewind(srcFile);

    // Remove empty lines from file.
    removeEmptyLines(srcFile, tempFile);


    /* Close all open files */
    fclose(srcFile);
    fclose(tempFile);


    /* Delete src file and rename temp file as src */
    remove(path);
    rename("remove-blanks.tmp", path);


    printf("\n\n\nFile contents after removing all empty line.\n\n");

    // Open source file and print its contents
    srcFile = fopen(path, "r");
    printFile(srcFile);
    fclose(srcFile);

    return 0;
}


/**
 * Print contents of a file.
 */
void printFile(FILE *fptr)
{
    char ch;

    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}



/**
 * Checks, whether a given string is empty or not.
 * A string is empty if it only contains white space
 * characters.
 * 
 * Returns 1 if given string is empty otherwise 0.
 */
int isEmpty(const char *str)
{
    char ch;

    do
    {
        ch = *(str++);

        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;

    } while (ch != '\0');

    return 1;
}



/**
 * Function to remove empty lines from a file.
 */
void removeEmptyLines(FILE *srcFile, FILE *tempFile)
{
    char buffer[BUFFER_SIZE];

    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        /* If current line is not empty then write to temporary file */
        if(!isEmpty(buffer))
            fputs(buffer, tempFile);
    }
}