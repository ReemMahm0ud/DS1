#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "prototypes.h"
#include "linearProbing.h"
#include "separateChaining.h"



int hashCode(image img)//calculates hash code of given image
{
    int i,j,sum,index=0;
    for(i=0; i<28; i++)
    {
        sum=0;
        for(j=0; j<28; j++)
            sum+=img.img_arr[i][j];

        index+=sum*(i+1);
        index%=SIZE;
    }
    return index;
}


void displayHash(int x)//prints the hash array: index, key and status
{
    int i;
    printf("INDEX\tKEY\tSTATUS\n");
    if(x==1)
        for(i=0; i<SIZE; i++)
            printf("%d\t%d\t%d\n",i,hash_table[i].item.key,hash_table[i].status);
    else
    {
        for(i=0; i<SIZE; i++)
        {
            hash* head = hash_table2[i].head;
            if(head==NULL)
                printf("%3d\t\t  0\n",i);
            else
            {
                printf("%3d",i);
                while (head != NULL)
                {
                    printf("\t%3d\t%3d\n",head->item.key,head->status);
                    head = head->next;
                }
            }

        }
    }

}

#endif // FUNCTIONS_H_INCLUDED
