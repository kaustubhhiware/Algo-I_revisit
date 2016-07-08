#include <stdio.h>
#include <stdlib.h>
//z

typedef struct node_{
	int key;
	struct node_ *l,*r;
}node;

typedef node *BST;


BST insert(BST root,int x)
{
	node *p;
	p = root;

	if(p==NULL)
	{
		p = (node *)malloc(sizeof(node));
		p->key = x;
		p->l=NULL;p->r=NULL;
		return p;
	}
	else if(p->key == x)
	{
		return root;
	}

	if(p->key > x)
	{
		p->l = insert(p->l,x);
	}
	else
	{
		p->r = insert(p->r,x);
	}
	return root;
}


void inorder(BST root)
{
	node *p;
	p = root;
	if(p==NULL){return;}
	if(p->l!=NULL){inorder(p->l);}
	printf("%d ",p->key );
	if(p->r!=NULL){inorder(p->r);}
}


void preorder(BST root)
{
	node *p;
	p = root;
	if(p==NULL){return;}
	printf("%d ",p->key );
	if(p->l!=NULL){preorder(p->l);}
	if(p->r!=NULL){preorder(p->r);}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
void spacebar(int level)
{
	int i;
	for (i=0;i<level;i++)
	{
		printf("    ");
	}
}
void fancyprint(BST root,int* level_ptr)
{
	node *p;
	int i;
	p = root;
	if(*level_ptr==0){printf("BST\n");}
	//spacebar(*level);
	if(p==NULL)	{printf("NULL\n");}
	else
	{
		printf("%d\n",p->key);
		*level_ptr = *level_ptr+1;
		spacebar((*level_ptr)-2);printf("---->l: ");fancyprint(p->l,level_ptr);
		spacebar((*level_ptr)-2);printf("---->r: ");fancyprint(p->r,level_ptr);
	}
}
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void printBST(BST root)
{
	printf("\n+++ The BST created has the following listings");
	printf("\nPreorder : ");preorder(root);
	printf("\nInorder : ");inorder(root);
	printf("\n");
	//fancyprint(root);
}

//return smallest node >=x
BST search1(BST root,int x)
{
	node *p,*res;
	p = root;
	int min = 100000000;
	res=NULL;
	while(p)
	{
		if(p->key==x){return p;}
		else if (p->key > x)
		{
			if(p->key < min)
			{
				min = p->key;
				res = p;
			}
			p = p->l;
		}
		else{p = p->r;}
	}
	return res;
}

//return largest node <= y
BST search2(BST root , int y)
{
	node *p,*res;
	p = root;
	int max = -99999999;
	res=NULL;
	while(p)
	{
		if (p->key==y){return p;}
		else if(p->key < y)
		{
			if(p->key > max)
			{
				max = p->key;
				res = p;
			}
			p = p->r;
		}
		else{p = p->l;}

	}
	return res;
}


//lowest common ancestor of two nodes in BST
//inputs as node to verify values are in BST
BST lca(BST root,node *x,node *y)
{
	node *p;
	p = root;
	int temp;
	node *a,*b;
	a = x;b = y;
	//force a <= b
	if(a->key>b->key)
	{
		temp = a->key;
		a->key = b->key;
		b->key = temp;
		//free(temp);
	}
	
	while(p)
	{
		//note : a->key  < res->key < b->key
		if(p->key < a->key ){p = p->r;}
		else if(p->key > b->key){p = p->l;}
		else if(p->key > a->key && p->key < b->key){return p;}
	}
}


//print all node values within two values
void printrange(BST root,int x,int y)
{
	node *p;
	p = root;
	int temp;
	//force x <= y
	if(x>y)
	{
		temp = x;
		x = y;
		y = temp;
		//free(temp);
	}
	
	//p = lca(root,x_more,y_less);//find only in relevant subtree
	while(p)
	{
		if(p->key < x ){p = p->r;}
		else if(p->key > y){p = p->l;}
		else if(p->key > x && p->key < y)
		{
			printrange(p->l,x,y);//here , could skip right subtree in some conditions
			printf("%d ",p->key );
			printrange(p->r,x,y);
			break;
		}
	}

}

int main(int argc,char *argv[] )
{
	node *root = NULL;
	//root = (node *)malloc(sizeof(node));
	int level;
	level = 0;

	int n,i,val_insert;
	printf("n = ");
	scanf("%d",&n);
	
	printf("\n+++Insert... : ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&val_insert);
		root = insert(root,val_insert);
		//printf("You entered : %d",val_insert);
		//printbst(root,&level);
	}
	printBST(root);

	int x,y;
	printf("x = \n");
	scanf("%d",&x);
	printf("y = \n");
	scanf("%d",&y);

	node* x_more = search1(root,x);
	node* y_less = search2(root,y);
	printf("+++search1(%d) = %d\n", x,x_more->key);
	printf("+++search1(%d) = %d\n", y,y_less->key);

	printf("\n+++lca(%d,%d) = %d\n",x_more->key,y_less->key,lca(root,x_more,y_less)->key);

	printf("+++Values in T within the range of %d and %d are : ",x,y);
	printrange(root,x,y);
	printf("\n");

}

