#include<stdio.h>

typedef int Vertex;
typedef struct Node_tag
{
	Vertex v;
	struct Node_tag *next[3];
} Node;

void Initialise_Node(Node *nptr)
{
	/*Empty Node(v=0) and Isolated*/
	nptr->v=0;
	nptr->next[0]=nptr->next[1]=nptr->next[2]=NULL;
}

Node* Create_Node()
{
	/*Dynamically allocates and return Initialised Node*/

	Node*nptr=(Node*)malloc(sizeof(Node));
	Initialise_Node(nptr);

	return nptr;
}

void Attach_Nodes(Node*nptr1,Node*nptr2)
{
	/*Links Node1 and Node2 with direction from Node1 to Node2*/

	//Find the emty next field of Node1
	int flag=0;
	for(int i=0;i<3,flag==0;i++)
	{
		if(nptr1->next[i]==NULL)
		{
			//continue;
		}
		else
		{
			//break;
			flag=1;
		}
	}

	if(flag==1)
	{
		//Join Node1 and Node2

		nptr1->next[i]=nptr2;
	}
	else
	{
		//Unable to Join

		printf("Error:The Node1 can have at max 3 successors only");
	}
	
}
Node* Insert_Successor(Node *nptr1,Node *nptr2)
{
	/*The arguments passed are the parent and child nodes*/
	/*The parents is lptr when the list is created*/
	if(nptr1==NULL)
	{
		//Empty list(Passing nptr as NULL means nptr1 is a pointer on stack)
		nptr1=nptr;
	}
	else
	{
		Attach_Nodes(nptr1,nptr2);		
	}
	return nptr1;
}

void main()
{
	Node *lptr=NULL;

	


}