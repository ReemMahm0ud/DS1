#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define sizeoffile 784
#define MAX 1000
typedef enum {Empty,Full,Available} Flag;
typedef struct image
{
    int img_arr[sizeoffile];
}image;
typedef struct data_item
{
    image data;
    int key;
}data_item;
typedef struct hashtable_item
{
    Flag flag;
    data_item itm;
    struct hashtable_item* next;

} hashtable_item;
typedef struct chaining
{
    hashtable_item* front;
    hashtable_item* rear;
} chaining;
chaining hashtable_2[MAX];


hashtable_item* new_node(int k,image IMG);
int get (image img);
void put (int key, image current_image);
int Removeimg (image img);
int hash_code (image img);

int main()
{
    FILE *fptr;
    char fnamer[100]="";
    FILE *fp;
    image img;
    image imgtest;
    int i,k,j,p,f,v;
    int choice;
    double total_time;
    clock_t start, end;
    start = clock();
    fptr = fopen("MNIST-data(datastructures_assignment3)_whitespace.txt", "r");
    for(p=0; p<MAX; p++)
    {
        for(i=0; i<28; i++)
            for(j=0; j<28; j++)
                fscanf(fptr,"%d",&img.img_arr[j+i*28]);
        fscanf(fptr,"%d",&k);
        put(k,img);
    }
    fclose(fptr);
    end = clock();
    total_time = ((double) (end - start)) / CLK_TCK;
    printf("done loading Images(using separate chaining method).......\n");
    printf("execution time : %f\n\n",total_time);
   LOOP: printf("\nchoose\n[1]search for images\n[2]remove images\n[3]exit\n");
    scanf("%d",&choice);
    if(choice==3)
    {
        exit(0);
    }
    printf("\nPlease Enter the Full Path of the test file : ");
    scanf("%s",fnamer);
    fp=fopen(fnamer,"r");
    if(fp==NULL)
    {
        printf("\n%s\" File NOT FOUND!",fnamer);
        getch();
        exit(1);
    }
    else
    {

        for(k=0;k<5;k++)
        {
            for(i=0;i<sizeoffile;i++)
                fscanf(fp,"%d",&imgtest.img_arr[i]);
            switch(choice)
            {
            case 1:
                f=get(imgtest);
                if(f==-1)
                {
                    printf("image not found\n");
                }
                else
                {
                    printf("image found id=%d\n",f);
                }break;
            case 2:
                v=Removeimg(imgtest);
                if(v==-1)
                {
                    printf("image not found\n");
                }
                else
                {
                    printf("image found id=%d and deleted\n",v);
                }break;

            }

        }
        fclose(fp);
    }
    printf("*************************************************\n\n");
goto LOOP;

    return 0;
}


hashtable_item* new_node(int k,image IMG)
{
    hashtable_item* node=malloc(sizeof(hashtable_item));
    node->itm.data=IMG;
    node->itm.key=k;
    node->next=NULL;
    node->flag=Full;
    return node;
}
int get(image img)
{
    int i,j;
    int state,x;
    x=hash_code(img);
    hashtable_item* temp=hashtable_2[x].front;
    while(temp!=NULL)
    {
        state=0;
        if(temp->flag==Full)
            for(i=0;i<28;i++)
        {
            for(j=0;j<28;j++)
            {
                if(temp->itm.data.img_arr[j+i*28]!=img.img_arr[j+i*28])
                {
                    state=-1;
                    break;
                }
            }
            if(state==-1)
                break;
        }
        if(i==28&&j==28&&state==0)
            return temp->itm.key;
       temp=temp->next;

    }
    return -1;
}

void put(int key,image current_image)
{
    int x;
    x=hash_code(current_image);
    hashtable_item* n=new_node(key,current_image);
    if(hashtable_2[x].front==NULL)
    {
        hashtable_2[x].front=hashtable_2[x].rear=n;
    }
    else
    {
        hashtable_item* Or=hashtable_2[x].rear;
        hashtable_2[x].rear=n;
        Or->next=n;
    }
}

int Removeimg (image img)
{
    int k=get(img);
    int x=hash_code(img);
    if(k==-1)
        return -1;
    hashtable_item* temp=hashtable_2[x].front;
    hashtable_item* b=NULL;
    while(temp!=NULL)
    {
        if(temp->itm.key==k)
        {
            if(b==NULL)
            {
                hashtable_2[x].front=temp->next;
                if(hashtable_2[x].front==NULL)
                    hashtable_2[x].rear=NULL;
            }
            else
                b->next=temp->next;
            free(temp);
            return k;
        }
        b=temp;
        temp=temp->next;
    }
    return -1;
}

int hash_code(image img)
{
    int i,j;
    int sum=0,k=0;
    for(i=0; i<28; i++)
    {
        for(j=0; j<28; j++)
        {
           sum+=img.img_arr[j+i*28];

        }
        sum=sum*(i+1);
        k+=sum;
        sum=0;
    }
    k=k%MAX;
    return k;
}
