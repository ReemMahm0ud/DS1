#ifndef LINEARPROBING_H_INCLUDED
#define LINEARPROBING_H_INCLUDED
#include "functions.h"
#include "prototypes.h"
void putLP(int key, image img)//puts in hash array using linear probing
{
    int index,temp,i;
    index = temp = hashCode(img);
    for(i=1; i!=SIZE-1; i++)
    {
        if(hash_table[index].status!=full)
        {
            hash_table[index].item.data=img;
            hash_table[index].item.key=key;
            hash_table[index].status=full;
            return;
        }
        index = (temp + i) % SIZE;
    }
}


int getLP(image img)//returns KEY of given image
{
    int index,j,i,flag;
    for(index=0; index<SIZE; index++)
    {
        flag =0;
        if(hash_table[index].status==full)
            for(i=0; i<28; i++)
            {
                for(j=0; j<28; j++)
                {
                    if(hash_table[index].item.data.img_arr[i][j]!=img.img_arr[i][j])
                    {
                        flag = -1;
                        break;
                    }
                }
                if(flag == -1)
                    break;
            }
        if(i == 28 && j == 28 && flag == 0)
            return hash_table[index].item.key;
    }
    return -1;
}


int removeLP(image img)//returns key of removed image
{
    int i,key;
    key = getLP(img);
    if(key==-1)
        return -1;
    for(i=0; i<SIZE; i++)
        if(hash_table[i].item.key==key)
        {
            hash_table[i].item.key=-1;
            hash_table[i].status=available;
            return key;
        }
    return -1;
}



#endif // LINEARPROBING_H_INCLUDED
