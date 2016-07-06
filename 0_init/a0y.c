#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//z

#define MERGE_PROB 0.5
//probability of merging two nodes

typedef struct node_{

	int val;
	struct node_ *next;
}node;


void printlist(node *list)
{

	while(list){
		printf("%d ",list->val );
		list = list->next;
	}
	printf("\n");
}

//solution for part a
void populate(int t,node **a,node **b)
{
	int i,is_merged = 0;
	node *p,*q,*new_node,*tail_p,*tail_q;

	p = q = tail_p = tail_q = NULL;

	double to_merge = (double)rand()/(double)RAND_MAX;
	if(to_merge <MERGE_PROB)
	{
		is_merged = 1;
	}

	for (i = 0;i < t; i++)
	{
		//New node
		new_node=(node *)malloc(sizeof(node));
		new_node->val = rand()%1000;
		new_node->next = NULL;


		if(is_merged)
		{

			if(p==NULL) {p = new_node;}
			if (q==NULL) {q = new_node;}

			if(tail_p) tail_p->next = new_node;
			tail_p = new_node;
		}
		else if((double)rand()/(double)RAND_MAX <= MERGE_PROB)
		{
			//merge here
			if (p==NULL)p = new_node;
			if(q==NULL)q = new_node;
			if (tail_p) tail_p->next = new_node;
			if (tail_q) tail_q->next = new_node;
			tail_q = new_node;
			is_merged = 1;
		}
		//at this point , new_node goes to either one 
		else if(rand()%2 == 0 )
		{
			if (p==NULL)
			{
				p = tail_p = new_node;
			}else
			{
				tail_p->next = new_node;tail_p = new_node;
			}
		}
		else
		{
			if(q==NULL)
			{
				q = tail_q = new_node;
			}else{
				tail_q->next=new_node;tail_q = new_node;
			}
		}
	}
	*a = p;*b = q;

}


void findsize(int* s,node *p)
{
	*s = 0;
	while(p){
		p = p->next;
		(*s)++;
	}
}

//note : only headers for two lists are given
void separatelists(node *a,node *b)
{

	int i,m,n;//sizes of two lists

	node *p,*q,*r;
	p = a;q = b;
	//find sizes
	findsize(&m,p);//printf("length : %d",m);
	findsize(&n,q);//printf("length : %d",n);

	//cross the extra part of one list
	//if they are joined , they end with the common part
	p = a;q = b;
	if(m>n)
	{
		for (i=0;i<m-n;i++)
		{
			p = p->next;
		}
	}
	else if(m<n)
	{
		for (i=0;i<n-m;i++)
		{
			q=q->next;
		}
	}

	//locate first common mode in equal parts
	while(1)
	{
		if(p==q){break;}
		p = p->next;q =q->next;
	}
	r = p;

	printf("Initial part of A : ");
	p = a;
	while(p!=r)
	{
		printf("%d ",p->val);
		p = p->next;
	}printf("\n");

	printf("Initial part of B : ");
	q = b;
	while(q!=r)
	{
		printf("%d ",q->val);
		q = q->next;
	}printf("\n");

	printf(" Common part     : ");
	while(r)
	{
		printf("%d ",r->val);
		r = r->next;
	}printf("\n");
}



int main(int argc , char* argv[] )
{

	int t;
	node *a,*b;
	srand((unsigned int)time(NULL));//need this for new nodes each time
	
	printf("Enter t : ");
	scanf("%d",&t);

	printf("\n+++part(a) ...\n");
	populate(t,&a,&b);
	printf("List A            : ");printlist(a);
	printf("List B            : ");printlist(b);

	printf("\n+++part(b) ...\n");
	separatelists(a,b);
}