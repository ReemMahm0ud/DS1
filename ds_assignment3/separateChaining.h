#ifndef SEPARATECHAINING_H_INCLUDED
#define SEPARATECHAINING_H_INCLUDED
#include "functions.h"
#include "prototypes.h"
void initialiseChains(Chain* hash_table2)
{
    int i;
    for(i=0; i<SIZE; i++)
        hash_table2[i].head=hash_table2[i].tail=NULL;
}


hash* newNode(int key,image img)
{
    hash* newNode = malloc(sizeof(hash));
    newNode->item.data=img;
    newNode->item.key=key;
    newNode->status=full;
    newNode->next=NULL;
    return newNode;
}

void putSC(int key, image img)
{
    int index = hashCode(img);
    hash* h=newNode(key,img);
    if(hash_table2[index].head==NULL)
        hash_table2[index].head=hash_table2[index].tail=h;
    else
    {
        hash* oldTail = hash_table2[index].tail;
        hash_table2[index].tail=h;
        oldTail->next=h;
    }
}

int getSC(image img)
{
    int i,j,index,flag;
    index = hashCode(img);
    hash* current = hash_table2[index].head;
    while(current!=NULL)
    {
        flag=0;
        if(current->status==full)
            for(i=0; i<28; i++)
            {
                for(j=0; j<28; j++)
                {
                    if(current->item.data.img_arr[i][j]!=img.img_arr[i][j])
                    {
                        flag = -1;
                        break;
                    }
                }
                if(flag == -1)
                    break;
            }
        if(i == 28 && j == 28 && flag == 0)
            return current->item.key;
        current = current->next;
    }
    return -1;

}

int removeSC(image img)
{
    int key,index;
    index = hashCode(img);
    key = getSC(img);
    if(key==-1)
        return -1;
    hash* current = hash_table2[index].head;
    hash* prev = NULL;
    while(current!=NULL)
    {
        if(current->item.key==key)
        {
            if(prev==NULL)
            {
                hash_table2[index].head=current->next;
                if(hash_table2[index].head==NULL)
                    hash_table2[index].tail=NULL;
            }
            else
                prev->next = current->next;
            free(current);
            return key;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}

#endif // SEPARATECHAINING_H_INCLUDED
