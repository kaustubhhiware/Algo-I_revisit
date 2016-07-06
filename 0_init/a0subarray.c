#include <stdio.h>
//z

int main()
{
	int n,t;

	printf("Enter n : ");
	scanf("%d",&n);

	printf("\nEnter target sum : ");
	scanf("%d",&t);

	int a[n],k;

	printf("\nEnter n-sized array : ");
	for(k=0;k<n;k++){
		scanf("%d",&a[k]);
	}
	
	int i,j;
	i = 0 ;j = 0;//i is the start and j is finish
	int sum = a[0];
	int found = 0;
	while(j>=i){

		if(sum<t)
		{
			j++;
			if (j == n ){
				break;
			}
			else{	
				sum += a[j];
			}
		}
		else if(sum>t)
		{
			i++;
			if(i==n){
				break;
			}
			else{
				sum -= a[i-1];
			}
		}
		else{
			found = 1;
			break;
		}

	}
	if(found==0){
		printf("\nNot found\n");
	}
	else
	{
		printf("\nTarget sum found between %d and %d ",i,j);
			
	printf("\n+++Subarray found ...\n %d =",t);
	for(k=i;k<j+1;k++){
		printf(" %d ",a[k]);
		if (k!=j){
			printf("+");
		}
	}
	printf("\n");
	

	}

}