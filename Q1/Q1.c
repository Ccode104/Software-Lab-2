/*Question 1:Write a program to create a file and write contents, save and close the file.*/

#define SIZE 100

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    //Create a array to store data to be wriiten in the file
	char data[SIZE];

	//Create a file pointer
	FILE *fptr;

	//Open the file in writing mode
	fptr=fopen("file1.txt","w");

	printf("Enter the data you want to write: ");
	gets(data);

	fprintf(fptr,"%s",data);

	fclose(fptr);
}