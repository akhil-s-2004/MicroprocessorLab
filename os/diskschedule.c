#include <stdio.h>
#include <stdlib.h>

int n,r[25],rq[25],size,traversal,initial;

void initialize()
{
    int i;
    for(i=0;i<n;i++)
    {
	r[i]=rq[i];
    }
}

void fcfs()
{
    initialize();
    int i,current=initial,seek=0;
    printf("Disk Traversal Order : ");
    for(i=0;i<n;i++)
    {
	seek+=abs(current-rq[i]);
	current=rq[i];
	printf("%d ",current);
    }
    printf("\nSeek Time : %d\n",seek);
}

void scan()
{
    initialize();
    int i,j,temp,index,current=initial,seek=0;
    printf("Disk Traversal Order : ");
    if(traversal==1)
    {
        for(i=0;i<n;i++)
        {
	    for(j=0;j<n-i-1;j++)
	    {
	        if(r[j] > r[j+1])
	        {
		    temp=r[j];
		    r[j]=r[j+1];
		    r[j+1]=temp;
	        }
	    }
        }
	for(i=0;i<n;i++)
	{
	    if(current < r[i])
	    {
		index=i;
		break;
	    }
	}
	for(i=index;i<n;i++)
	{
	    seek+=abs(r[i]-current);
	    current=r[i];
	    printf("%d ",current);
	}
	seek+=abs(size-1-current);
	current=size-1;
	for(i=index-1;i>=0;i--)
	{
	    seek+=abs(current-r[i]);
	    current=r[i];
            printf("%d ",current);
	}
        printf("\nSeek Time : %d\n",seek);
    }
    else if(traversal==2)
    {
       for(i=0;i<n;i++)
        {
            for(j=0;j<n-i-1;j++)
            {
                if(r[j] < r[j+1])
                {
                    temp=r[j];
                    r[j]=r[j+1];
                    r[j+1]=temp;
                }
            }
        }
        for(i=0;i<n;i++)
        {
            if(current > r[i])
            {
                index=i;
                break;
            }
        }
        for(i=index;i<n;i++)
        {
            seek+=abs(current-r[i]);
            current=r[i];
            printf("%d ",current);
        }
        seek+=abs(current-0);
        current=0;
        for(i=index-1;i>=0;i--)
        {
            seek+=abs(r[i]-current);
            current=r[i];
            printf("%d ",current);
        }
        printf("\nSeek Time : %d\n",seek);
    }
}

void cscan()
{
    initialize();
    int i,j,temp,index,current=initial,seek=0;
    printf("Disk Traversal Order : ");
    if(traversal==1)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n-i-1;j++)
            {
                if(r[j] > r[j+1])
                {
                    temp=r[j];
                    r[j]=r[j+1];
                    r[j+1]=temp;
                }
            }
        }
        for(i=0;i<n;i++)
        {
            if(current < r[i])
            {
                index=i;
                break;
            }
        }
        for(i=index;i<n;i++)
        {
            seek+=abs(r[i]-current);
            current=r[i];
            printf("%d ",current);
        }
	seek+=abs(size-1-current);
	current=size-1;
        seek+=abs(current-0);
        current=0;
        for(i=0;i<index;i++)
        {
            seek+=abs(r[i]-current);
            current=r[i];
            printf("%d ",current);
        }
        printf("\nSeek Time : %d\n",seek);
    }
    else if(traversal==2)
    {
       for(i=0;i<n;i++)
        {
            for(j=0;j<n-i-1;j++)
            {
                if(r[j] < r[j+1])
                {
                    temp=r[j];
                    r[j]=r[j+1];
                    r[j+1]=temp;
                }
            }
        }
        for(i=0;i<n;i++)
        {
            if(current > r[i])
            {
                index=i;
                break;
            }
        }
        for(i=index;i<n;i++)
        {
            seek+=abs(current-r[i]);
            current=r[i];
            printf("%d ",current);
        }
        seek+=abs(current-0);
        current=0;
	seek+=abs(size-1-current);
	current=size-1;
        for(i=0;i<index;i++)
        {
            seek+=abs(r[i]-current);
            current=r[i];
            printf("%d ",current);
        }
        printf("\nSeek Time : %d\n",seek);
    }
}

void main()
{
    int i,value;
    char ch='y';
    printf("Enter the disk size : ");
    scanf("%d",&size);
    printf("How many requests ? : ");
    scanf("%d",&n);
    printf("Enter the request sequence : ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&rq[i]);
    }
    printf("Enter the initial position of header : ");
    scanf("%d",&initial);
    while(ch=='y'||ch=='Y')
    {
	printf("1 : FCFS\n2 : SCAN\n3 : C-SCAN\n4 : EXIT\n");
	printf("Enter your choice : ");
	scanf(" %d",&value);
	if(value == 4)
	{
	    break;
	}
	if(value == 2 || value == 3)
	{
	    printf("1 : Increasing Order\n2 : Decreasing Order\n");
	    printf("Enter your choice : ");
	    scanf(" %d",&traversal);
	}
	switch(value)
	{
	    case 1 : fcfs();
	  	     break;
	    case 2 : scan();
		     break;
	    case 3 : cscan();
		     break;
	}
    }
}
