#include <stdio.h>
#include <stdlib.h>
#define size 10

struct process
{
    int pid;
    int priority;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
    int remaining;
    int completed;
}p[size],temp_p;

int n,slice;
float avgtt,avgrt,avgwt;
void initialize()
{
    int i;
    for(i=0;i<n;i++)
    {
        p[i].completion=0;
        p[i].turnaround=0;
        p[i].waiting=0;
        p[i].response=0;
        p[i].remaining=0;
        p[i].completed=0;
        avgtt=0;
        avgrt=0;
        avgwt=0;
    }
}

void display()
{
    int i;
    printf("PID\t|PRIORITY\t|ARRIVAL TIME\t|BURST TIME\t|COMPLETION TIME\t|TURNAROUND TIME\t|RESPONSE TIME\t|WAITING TIME\t|\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t|%d\t\t|%d\t\t|%d\t\t|%d\t\t\t|%d\t\t\t|%d\t\t|%d\t\t|\n",p[i].pid,p[i].priority,p[i].arrival,p[i].burst,p[i].completion,p[i].turnaround,p[i].response,p[i].waiting);
        avgtt+=p[i].turnaround;
        avgrt+=p[i].response;
        avgwt+=p[i].waiting;
    }
    avgtt=avgtt/n;
    avgrt=avgrt/n;
    avgwt=avgwt/n;
    printf("Average Turnaround Time = %.2f\n",avgtt);
    printf("Average Response Time = %.2f\n",avgrt);
    printf("Average Waiting Time = %.2f\n",avgwt);
}

void fcfs()
{   initialize();
    int i,j;
    int currenttime=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival > p[j+1].arrival)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        while(p[i].arrival > currenttime)
        {
            currenttime++;
        }
        p[i].completion=currenttime+p[i].burst;
        p[i].turnaround=p[i].completion-p[i].arrival;
        p[i].waiting=currenttime-p[i].arrival;
        p[i].response=currenttime-p[i].arrival;
        currenttime+=p[i].burst;
    }
    display();
}

void sjf()
{
    initialize();
    int i,j;
    int minindex,minimum;
    int completed=0,currenttime=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival > p[j+1].arrival)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival == p[j+1].arrival && p[j].burst > p[j+1].burst)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    while(completed!=n)
    {
        minindex=-1;
        minimum=10000;
        for(i=0;i<n;i++)
        {
            if(p[i].arrival <= currenttime && p[i].completed == 0)
            {
                if(p[i].burst < minimum)
                {
                    minindex=i;
                    minimum=p[i].burst;
                }
                if(p[i].burst == minimum)
                {
                    if(p[i].arrival <p[minindex].arrival)
                    {
                        minindex=i;
                        minimum=p[i].burst;
                    }
                }
            }
        }
        if(minindex == -1)
        {
            currenttime++;
         }
        else
        {
            p[minindex].completion=currenttime+p[minindex].burst;
            p[minindex].turnaround=p[minindex].completion-p[minindex].arrival;
            p[minindex].waiting=currenttime-p[minindex].arrival;
            p[minindex].response=currenttime-p[minindex].arrival;
            currenttime+=p[minindex].burst;
            p[minindex].completed=1;
            completed++;
        }
    }
    display();
}

void priority()
{
    initialize();
    int i,j;
    int minindex,minimum;
    int completed=0,currenttime=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival > p[j+1].arrival)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival == p[j+1].arrival && p[j].priority > p[j+1].priority)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    while(completed!=n)
    {
        minindex=-1;
        minimum=10000;
        for(i=0;i<n;i++)
        {
            if(p[i].arrival <= currenttime && p[i].completed == 0)
            {
                if(p[i].priority < minimum)
                {
                    minindex=i;
                    minimum=p[i].priority;
                }
                if(p[i].priority == minimum)
                {
                    if(p[i].arrival <p[minindex].arrival)
                    {
                        minindex=i;
                        minimum=p[i].priority;
                    }
                }
            }
        }
        if(minindex == -1)
        {
            currenttime++;
         }
        else
        {
            p[minindex].completion=currenttime+p[minindex].burst;
            p[minindex].turnaround=p[minindex].completion-p[minindex].arrival;
            p[minindex].waiting=currenttime-p[minindex].arrival;
            p[minindex].response=currenttime-p[minindex].arrival;
            currenttime+=p[minindex].burst;
            p[minindex].completed=1;
            completed++;
        }
    }
    display();
}
void roundrobin()
{
    initialize();
    int i,j,m,ready[50],count=0;
    int remaining=n,currenttime=0,flag=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].arrival > p[j+1].arrival)
            {
                temp_p=p[j];
                p[j]=p[j+1];
                p[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        p[i].remaining=p[i].burst;
        p[i].completed=0;
    }
    for(currenttime=0,i=0;remaining!=0;)
    {
        if(p[i].remaining <= slice && p[i].remaining > 0)
        {
            if(p[i].remaining == p[i].burst)
            {
                p[i].response=currenttime;
            }
            currenttime+=p[i].remaining;
            p[i].remaining=0;
            flag=1;
        }
        else if(p[i].remaining >0)
        {
            if(p[i].remaining == p[i].burst)
            {
                p[i].response=currenttime;
            }
            p[i].remaining=p[i].remaining-slice;
            currenttime=currenttime+slice;
        }
        if(p[i].remaining == 0 && flag==1)
        {
            remaining--;
            flag=0;
            p[i].completion=currenttime;
            p[i].turnaround=p[i].completion-p[i].arrival;
            p[i].waiting=p[i].completion-p[i].arrival-p[i].burst;
        }
        m=0;
        for(j=0;j<n;j++)
        {
            if(p[j].arrival <= currenttime && p[j].remaining!=0)
            {
                ready[m++]=j;
            }
        }
        if(m > 0)
        {
            count=(count+1)%m;
            i=ready[count];
        }
        else
        {
            currenttime++;
        }
    }
    display();
}
void main()
{
    int i,value;
    char ch='y';
    while(ch=='y' || ch =='Y')
    {
        printf("1 : FCFS\n");
        printf("2 : SJF\n");
        printf("3 : PRIORITY\n");
        printf("4 : ROUND ROBIN\n");
        printf("5 : EXIT\n");
        printf("Enter your choice : ");
        scanf("%d",&value);
        if(value == 5)
        {
            ch='n';
            break;
        }
        printf("How many process ? : ");
        scanf("%d",&n);
        printf("Enter the Process Arrival Time\n");
        for(i=0;i<n;i++)
        {
            p[i].pid=i+1;
            printf("P[%d] : ",i+1);
            scanf("%d",&p[i].arrival);
        }
        if(value == 3)
        {
            printf("Enter the Process Priority\n");
            for(i=0;i<n;i++)
            {
                printf("P[%d] : ",i+1);
                scanf("%d",&p[i].priority);
            }
        }
        printf("Enter the Process Burst Time\n");
        for(i=0;i<n;i++)
        {
            printf("P[%d] : ",i+1);
            scanf("%d",&p[i].burst);
        }
        if(value == 4)
        {
            printf("Enter the time slice : ");
            scanf("%d",&slice);
        }
        switch(value)
        {
            case 1 : fcfs();
                     break;
            case 2 : sjf();
                     break;
            case 3 : priority();
                     break;
            case 4 : roundrobin();
                     break;
        }
    }
}
