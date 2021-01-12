#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num_slots,num_processes;
typedef struct
{
    char name[50];
    int start_time;
    int excution_time;
} Process;
typedef struct
{
    int data;
    struct Node* next;

} Node;
typedef struct
{
    Node* front;
    Node* rear;
} Queue;



void initialize(Queue *q);
int dequeue (Queue *q);
void enqueue(Queue *q,int v);
int isEmpty(Queue *q);
Node* newNode(int v);
Process* rf(char* filename);



int main()
{
    char* filename = "test.txt";
    Process* process = rf(filename);
    int i,k,position;
    for(i=0; i<num_processes; i++)
        printf("%s %d %d\n",process[i].name,process[i].start_time,process[i].excution_time );
    Process swap;
    for(i=0; i<num_processes-1; i++)
    {
        position = i;
        for(k=i+1; k<num_processes; k++)
            if(process[position].start_time>process[k].start_time)
                position = k;
        if(position!=i)
        {
            swap = process[position];
            process[position]=process[i];
            process[i]=swap;
        }
    }

    printf("\nSorted: \n");
    for(i=0; i<num_processes; i++)
        printf("%s %d %d\n",process[i].name,process[i].start_time,process[i].excution_time );

    int timer=0,p,x=0,size=0;
    Queue rq;
    initialize(&rq);

    for(; timer<num_slots; timer++)
    {
        for(p=size; p<num_processes; p++)
        {

            if(timer>=process[p].start_time)
            {
                if(process[p].excution_time!=0)
                {
                    enqueue(&rq,p+1);
                    process[p].excution_time--;
                    size++;
                }
            }
        }
        if(!isEmpty(&rq))
        {
            x = dequeue(&rq);
            printf("\n%s  (%d-->%d)",process[x-1].name,timer,timer+1);
            if(process[x-1].excution_time!=0)
            {
                enqueue(&rq,x);

                process[x-1].excution_time--;
            }
            else

                printf("  %s aborts",process[x-1].name);
        }
        else if(isEmpty(&rq))
            printf("\nidle   (%d-->%d)",timer,timer+1);


    }
    printf("\nstop");
    return 0;
}

Node* newNode(int v)
{
    Node* node =(Node*)malloc(sizeof(Node));
    node->data=v;
    node->next=NULL;
    return node;
}
void initialize(Queue *q)
{
    q->front=q->rear=NULL;
}
int dequeue (Queue *q)
{
    int temp;
    if(isEmpty(q))
        return 0;
    else
    {
        temp = q->front->data;
        q->front = q->front->next;
        return temp;
    }
}
void enqueue(Queue *q,int v)
{
    Node* node = newNode(v);
    if(isEmpty(q))
        q->front = q->rear = node;
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
}
int isEmpty(Queue *q)
{
    if(q->front==NULL)
        return 1;
    return 0;
}

Process* rf(char* filename)
{
    FILE *fptr;
    fptr = fopen(filename, "r");
    int i;
    if (fptr == NULL)
    {
        printf("Error no file");
        exit(1);
    }
    fscanf(fptr,"%d\n",&num_slots);
    printf(" the watching time slots: %d\n",num_slots);
    Process* process=(Process*)malloc(num_slots*sizeof(Process));
    while(!feof(fptr))
    {
        for(i=0; i<num_slots; i++)
        {
            fscanf(fptr,"%s %d %d",process[i].name,&process[i].start_time,&process[i].excution_time);
            if(feof(fptr))
                break;
        }
    }
    num_processes=i;
    fclose(fptr);
    return process;
}

