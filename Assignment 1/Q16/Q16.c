/**
 * C program to replace a specific line with another in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define SIZE 100
int main()
{
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    
    char buffer[SIZE];
    char newline[SIZE];
    int line, count;


    printf("Enter path of source file: ");
    scanf("%s", path);

    printf("Enter line number to replace: ");
    scanf("%d", &line);

    printf("Replace '%d' line with: ",line);
    scanf("%s",newline);


    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer,SIZE,fPtr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line){
            fputs(newline, fTemp);
            fputs("\n",fTemp);
        }
        else
            fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("replace.tmp", path);

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

    return 0;
}