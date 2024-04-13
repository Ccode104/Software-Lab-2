/*BT22CSE104 Abhishek Prashant Chandurkar
CPL Assignment 2 */

#define SIZE_OF_HEAP 100
#include<stdio.h>
#include<stdlib.h>



typedef int Vertex;
typedef struct Node_tag
{
	Vertex v;
	int ref_count;
	struct Node_tag *next[3];
} Node;

typedef struct Stack_tag
{
	Node *roots[10];
} Stack;

//Size of Queue
#define SIZE 40

struct queue {
  Node* items[SIZE];
  int front;
  int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, Node*);
Node* dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

// BFS algorithm used to output adjacency matrix
void print_adjacency_matrix(Node* startVertex) {
  struct queue* q = createQueue();
  int matrix[10][10];

  int visited[10];

  for(int i=0;i<10;i++)
  {
  	visited[i]=0;
  }

  for(int i=0;i<10;i++)
  {
  	for(int j=0;j<10;j++)
  	{
  		matrix[i][j]=0;
  	}
  }

  visited[startVertex->v-1] = 1;
  enqueue(q, startVertex);

  int i=0;
  while (!isEmpty(q)) {
    printQueue(q);
    Node* currentVertex = dequeue(q);
   	printf("Visited %d\n", currentVertex->v);

    Node* temp = currentVertex;
    i=0;
    while ((temp->next[i]!=NULL)&&(i<3)) {
      Node* adjVertex = temp->next[i];

      //printf("bool=%d",visited[adjVertex->v]);
      if (visited[adjVertex->v-1] == 0) {
        visited[adjVertex->v-1] = 1;
        matrix[currentVertex->v-1][adjVertex->v-1]=1;
        enqueue(q, adjVertex);
        //printf("i=%d",i);
      }
      i=i+1;
    }
  }

  for(int i=0;i<10;i++)
  {
  	printf("\n");
  	for(int j=0;j<10;j++)
  	{
  		printf(" %d ",matrix[i][j]);
  	}
  }
}



// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, Node* value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
Node* dequeue(struct queue* q) {
  Node* item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = NULL;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]->v);
    }
  }
}



typedef struct heap_tag
{
	char byte[SIZE_OF_HEAP];
	unsigned int lptr; //free list
} heap;

void init(heap *h)
{
	unsigned int *ptr;
	char *curr=h->byte;
	

	ptr=(unsigned int*)h->byte;

	for(int i=0;i<SIZE_OF_HEAP;i++)
	{
		h->byte[i]=0;
	}//Set Heap vals to 0

	//Initial Metadata
	*ptr=SIZE_OF_HEAP;
	
	curr=curr+4;
	ptr=(unsigned int*)curr;
	*ptr=101;

	h->lptr=0;

}
char* malloc_h(unsigned int size,heap *h)
{
	char *ptr=NULL;//For traversal
	char *prev=ptr;//For prev to ptr
	unsigned int *s;//Store the size of block pointed by ptr
	unsigned int *n;//Store index of next of free block to ptr
	unsigned int *ps;//Store the size of the free block before alloc
	int flag=0;//To break the loop on success 

	size=size+8;//Include size of metadata(8 bytes)

	if(h->lptr==101)
	{
		//Empty free list
		printf("\nMalloc Failure due to full heap\n");
	}
	else{
		//Set ptr to start of free list
		
		ptr=&(h->byte[h->lptr]);

		//First fit
		do
		{
			s=(unsigned int*)ptr;//Get size
			if((*s)>=size)
			{
				flag=1;//Found the block to allocate
				n=(unsigned int*)(ptr+4);//Get index of next block
			}
			else
			{
				//Move forward
				prev=ptr;
				n=(unsigned int*)(ptr+4);//Get index of next block
				if((*n)!=101)
				{
					//Not the last free block
					ptr=&(h->byte[(*n)]);
				}
			}
		}while((*n!=101)&&(flag==0));
	}

	//Termination due to No block of sufficient size found
	if((*n==101)&&(flag==0))
	{
		//External Fragmentation
		printf("\nMalloc Failure due to External Fragmentation\n");
	}
	else if((*n==101)&&(flag==1))
	{
		//Only one free block in heap
		//Set h->lptr 

		(h->lptr)=((ptr)-(h->byte))+size;

		//Get size of first block in free list(to be modified)
		ps=(unsigned int*)(&(h->byte[h->lptr]));
		*ps=(*s)-size;
		
		//Get next block index and set to NULL(101)	
		n=(unsigned int*)(&(h->byte[(h->lptr)+4]));
		*n=101;//Set the next pointer of only free block in the list to NULL(101)
		
		*s=size;//Size of alloc block set
		}
	else{

		if(ptr-(h->byte)==h->lptr)
		{
			//First block in free list
			(h->lptr)=((ptr)-(h->byte))+size;

			ps=(unsigned int*)(h->byte+(h->lptr));
			*ps=(*s)-size;
	
			*s=size;
		}
		else
		{
			if(*s-size>8)
			{
				//Set size of split free nodeG
				ps=(unsigned int*)(ptr+size);
				*ps=(*s)-size;

				//Set next pointer(index val) of split free nodeG
				n=(unsigned int*)(ptr+size+4);
				*n=*(ptr+4);
			
				//Set prev next pointer to split free nodeG
				*(prev+4)=(ptr-h->byte)+size;
				*s=size;
			}
			else{
				//No split in free nodeG
				*s=size;
				*(prev+4)=*(ptr+4);
			}
		}
	}
    
	return (ptr+8);
}

void free_h(char *ptr,heap *h)
{
	unsigned int *curr_s=NULL;//size of current free block
	unsigned int *prev_s=NULL;//size of prev free block
	unsigned int *ptr_s,*prev_n,*curr_n,*ptr_n;
	char *curr,*prev=NULL;

	if(h->lptr==101)
	{
		//Empty free list
		h->lptr=((ptr-(h->byte)-8));
	}
	else{

		//Set curr at start of free list
		curr=&(h->byte[h->lptr]);

		while(((ptr-(h->byte))-8)>(curr-(h->byte)))
		{
			//ptr comes after curr

			prev=curr;
			curr_n=(unsigned int*)(curr+4);
			if(*(curr_n)!=101)
			{
				//Goto next free block
				curr=(&(h->byte[*(curr_n)]));
			}
			else
				break;
		}
		if(prev!=NULL)
		{
			if((ptr-prev)!=(*prev))
			{
				//prev and ptr not adjacent
				//Insert ptr between prev and curr
				ptr_n=(unsigned int*)(ptr-4);
				prev_n=(unsigned int*)(prev+4);
				*(ptr_n)=curr-(h->byte);
				*(prev_n)=ptr-(h->byte);
			}
			else{
				//prev and ptr adjacent
				//Merge prev and ptr
				prev_n=(unsigned int*)(prev+4);
				*(prev_n)=curr-(h->byte);

				prev_s=(unsigned int*)(prev);
				ptr_s=(unsigned int*)(ptr);
				*prev_s+=*ptr_s;//Accumulate the size
			}
	
			if(curr-prev==(*(prev+4)))
			{
				//prev and curr adjacent
				prev_s=(unsigned int*)(prev);
				curr_s=(unsigned int*)(curr);
				*prev_s+=*curr_s;//Accumulate the size

				prev_n=(unsigned int*)(prev+4);
				curr_n=(unsigned int*)(curr+4);
				*(prev_n)=*(curr_n);
	 		}
	 		
        }
        else{
        	//prev is NULL
        	//If insert at start 
        	ptr_n=(unsigned int*)(ptr-4);
        	*(ptr_n)=(h->lptr);
        	
        	ptr_s=(unsigned int*)(ptr-8);

        	//Check for merge case
        	if((curr-h->byte)==(*ptr_s))
        	{
        		*ptr_s+=*((unsigned int*)curr);
        	}

 
		    h->lptr=(ptr-(h->byte))-8;
		    
        }
		
	}
}

Node* free_ref_count(Node *root,heap *h)
{
	int i=0;
	root->ref_count-=1;
	//printf("ref = %d",root->ref_count);
	if(root->ref_count==0)
	{
		//printf("In");
		while(root->next[i]!=NULL)
		{
			root->next[i]=free_ref_count(root->next[i],h);
			i++;
		}
		free_h((char*)root,h);
		root=NULL;
	}
	else
	{
		print_adjacency_matrix(root);
	}
	return root;
}

void Initialise_Node(Node *nptr)
{
	/*Empty Node(v=0) and Isolated*/
	nptr->v=0;
	nptr->ref_count=0;
	nptr->next[0]=NULL;
	nptr->next[1]=NULL;
	nptr->next[2]=NULL;
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
	
	int i=0;
	//Find the empty next field of Node1
	
	int flag=0;
	while(nptr1->next[i]!=NULL)
	{
		i++;
	}
	//printf("i=%d",i);
	if(i<3)
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
		//printf("root=NULL");
		//Empty list(Passing nptr as NULL means nptr1 is a pointer on stack)
		nptr1=nptr2;
	}
	else
	{
		//printf("Not NULL");
		Attach_Nodes(nptr1,nptr2);		
	}
	nptr2->ref_count+=1;
	return nptr1;
}


void mark_helper(Node*root)
{
	Node *curr=root;
	int i=0;

	visited[curr->v-1]=1;
	while(curr->next[i]!=NULL)
	{
		visited[curr->next[i]->v-1]=1;
		i++;
	}

}
void mark(Stack *s)
{
	int i=0;
	while(s->roots[i]!=NULL)
	{
		mark_helper(s->roots[i]);
	}
}

void main()
{
	heap h;//Create a virtual heap 
	init(&h);//Initialise the heap as all vals to 0 and metadata:size=100,next=101

	//Create the pointers 
	Node*nptr;

	Stack s;

	s.roots[1]=NULL;
	s.roots[2]=NULL;
	s.roots[3]=NULL;
	s.roots[4]=NULL;

	nptr=Create_Node();
	nptr->v=7;
	s.roots[3]=Insert_Successor(s.roots[3],nptr);//s.roots[3]->7
	//printf("s.roots[3]->v = %d",s.roots[3]->v);

	nptr=Create_Node();
	nptr->v=8;
	s.roots[3]=Insert_Successor(s.roots[3],nptr);//7->8
	//printf("s.roots[3]->next[0]->v = %d",s.roots[3]->next[0]->v);

	nptr=Create_Node();
	nptr->v=3;
	s.roots[4]=Insert_Successor(s.roots[4],nptr);//s.roots[4]->3
	//printf("s.roots[4]->next[0]->v = %d",s.roots[4]->next[0]->v);

	nptr=Create_Node();
	nptr->v=5;
	s.roots[2]=Insert_Successor(s.roots[2],nptr);//s.roots[2]->5
	//printf("s.roots[2]->v = %d",s.roots[2]->v);

	//printf("  %d  ",s.roots[2]->v);
	nptr=Create_Node();
	nptr->v=1;
	s.roots[1]=Insert_Successor(s.roots[1],nptr);//s.roots[1]->1
	//printf("ref=1=%d",s.roots[1]->ref_count);
	s.roots[2]=Insert_Successor(s.roots[2],nptr);//5->1
	//printf("\n%d\n",s.roots[2]->next[0]->v);
	s.roots[3]=Insert_Successor(s.roots[3],nptr);//7->8,1

	nptr=Create_Node();
	nptr->v=2;
	s.roots[1]=Insert_Successor(s.roots[1],nptr);
	//printf("ref=1=%d",s.roots[1]->ref_count);

	nptr=Create_Node();
	nptr->v=9;
	s.roots[1]=Insert_Successor(s.roots[1],nptr);

	nptr=Create_Node();
	nptr->v=10;
	s.roots[1]=Insert_Successor(s.roots[1],nptr);
	s.roots[4]=Insert_Successor(s.roots[4],nptr);

	printf("  %d   ",s.roots[2]->next[0]->next[2]->v);

	printf("The adjacency matrix for s.roots[1] pointing to vertex 1\n");
	print_adjacency_matrix(s.roots[1]);
	printf("The adjacency matrix for s.roots[1] pointing to vertex 5\n");
	print_adjacency_matrix(s.roots[2]);

	//Reference Counting

	printf("\nReference Counting\n");
	s.roots[2]=free_ref_count(s.roots[2],&h);




	
	




	
			

}
/*
int main() {
  
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 4);
  addEdge(graph, 1, 3);
  addEdge(graph, 2, 4);
  addEdge(graph, 3, 4);

  print_adjacency_matrix(graph, 0);

  return 0;
}*/