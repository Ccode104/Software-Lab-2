/*Question 2: Write a program to read file contents and display on console*/

#include<stdio.h>
#include<stdlib.h>
void main()
{
	int ch;

	//Create a file pointer

	FILE *fptr;
	

	//Open the file(created in Q1) in reading mode
	fptr=fopen("file1.txt","r");

	ch=fgetc(fptr);
	while(ch != EOF)
	{
		printf("%c",ch);
		ch=fgetc(fptr);
	}

	fclose(fptr);
	
}
