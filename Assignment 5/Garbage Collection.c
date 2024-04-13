#include<stdio.h>

void main()
{
	struct adjacency_matrix
	{
		int adj[10][10];
		int ref_count[10];
	}adj_mat;

	int adj[10][10]={ {0,1,0,0,0,0,0,0,1,1},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,1,0,1},
					  {0,0,0,0,0,0,0,0,0,0},
					  {1,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {1,0,0,0,0,0,0,1,0,0},
					  {0,0,0,0,0,0,0,0,1,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0}
					};

	int ref_count[10];
	int garbage[10]={1,1,1,1,1,1,1,1,1,1};

	for(int i=0;i<10;i++)
	{
		printf("\n");
		for(int j=0;j<10;j++)
		{
			printf(" %d ",adj[i][j]);
			if(adj[i][j]==1)
			{
				ref_count[j]++;
			}
		}
	}

	//Reference Counting Mechanism

	//Start from root1(vertex 1)

	int i=1;
	int j=0;
	int flag=0,k=0;
	while(flag!=1)
	{
		ref_count[i]--;
		garbage[i]=0;
		k=0;
		while(adj[i][k]!=1)
		{
			k++;
		}
		if(k>=10)
		{
			flag=1;
		}
		else
		{
			i=k;
			j=0;
		}
	}

	//Start from root1(vertex 5)

	i=5;
	j=0;
	flag=0;
	k=0;
	while(flag!=1)
	{
		ref_count[i]--;
		garbage[i]=0;
		k=0;
		while(adj[i][k]!=1)
		{
			k++;
		}
		if(k>=10)
		{
			flag=1;
		}
		else
		{
			i=k;
			j=0;
		}
	}

	printf("\n");
	for(int i=0;i<10;i++)
	{
		printf("\n");
		for(int j=0;j<10;j++)
		{
			printf(" %d ",adj[i][j]);
		}
	}

	printf("Garbage Nodes are : ");
	for(int i=0;i<10;i++)
	{
		if(garbage[i]==1)
		{
			printf(" %d ",i);
		}
	}





	

	
}