#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int height(BST root)
{
	int lt_ht,rt_ht;

	if(root==NULL){return -1;}//return -1 as root is 0th , not 1st
	
	lt_ht = height(root->l);
	rt_ht = height(root->r);

	if(lt_ht>=rt_ht)
	{
		return lt_ht+1;
	}
	else return rt_ht+1;
}

void printBST(BST root)
{
	printf("\n 		 Preorder : ");preorder(root);
	printf("\n 		 Inorder : ");inorder(root);
	printf("\n 		 Height : %d",height(root) );
	printf("\n");
}

BST left_rotate(BST root)
{
	node *p,*right_s_left,*right;
	p = root;
	right = root->r;
	if(right!=NULL||right->l!=NULL)
	{
		right_s_left = right->l;
		p->r = right_s_left;
		right->l = p;
		return right;
	}
	return root;

}

BST right_rotate(BST root)
{
	node *p,*left_s_right,*left;
	p = root;
	left = root->l;
	if(left!=NULL||left->r!=NULL)
	{
		left_s_right = left->r;
		p->l = left_s_right;
		left->r = p;
		return left;
	}
	return root;

}

//convert tree to list - plain in ascending order
BST makeSkew(BST root)
{
	node *p;
		
	node *dummy_parent;
	dummy_parent = (node *)malloc(sizeof(node));
	dummy_parent->key = -1;
	dummy_parent->l = NULL;
	dummy_parent->r =root;

	p = dummy_parent;
	while(p->r)
	{
		if(p->r->l!=NULL)
		{
			p->r = right_rotate(p->r);
		}
		else
		{
			p = p->r;
		}
	}
	return dummy_parent;//returning such , so that not required again in rebalance

}


//follow right links , make left rotations every alternate node
BST alter_rotor(BST root,int count)
{
	node *p;
	p = root;
	while(count)
	{
		p->r = left_rotate(p->r);
		//printf("left_rotate\n");
		p = p->r;
		count--;
	}
	return root;
}

//generate x^y
int power(int x,int y)
{
	int prod = 1;
	int i;
	for(i=0;i<y;i++)
	{
		prod *= x;
	}
	return prod;
}


//make a almost-complete binary tree
BST rebalance(BST root)
{
	int n,n_2,l,c;
	//refer to the question, too hard to understand from the code
	n = height(root);

	//compute l = floor of log2(n+1)
	n_2 = n+1;l=0;
	while(n_2>1)
	{
		l++;n_2 /= 2;
	}
	//c = count of deepest leaves
	int pow2 ;
	pow2 = power(2,l);
	//printf("pow2 = %d\n",pow2);
	if((n+1)==pow2){c = (n+1)/2;}
	else
	{
		c = n+1 - pow2;
	}

	root = alter_rotor(root,c);
	//printf("aletter pow2 = %d\n",pow2);

	int n_dup = n-c;
	while(n_dup > 1)
	{
		n_dup /= 2;
		root = alter_rotor(root,n_dup);
	}
	//printf("pow2 = %d\n",pow2);
	return root;
}



int main(int argc,char *argv[] )
{
	node *root;
	int i,n,val_insert;

	printf("n = ");
	scanf("%d",&n);

	printf("\n+++ Insert : ");
	for(i = 0;i<n;i++)
	{
		scanf("%d",&val_insert);
		root = insert(root,val_insert);
	}
	printf("+++ Initial BST created 	:\n");
	printBST(root);

/*
	printf("\nOne right rotation : \n");
	printBST(right_rotate(root));
	printf("\nOne left rotation : \n");
	printBST(left_rotate(root));
*/
	root = makeSkew(root);
	printf("+++ The tree is now fully right-skew:\n");
	printBST(root->r);

	//printf("2 ^ 4 = %f\n",pow(2,4));
	root = rebalance(root);
	printf("+++ Balance restored in the tree:\n");
	printBST(root->r);
}