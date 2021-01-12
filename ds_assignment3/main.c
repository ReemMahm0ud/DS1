#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main()
{
    FILE *fptr;
    int key,i,j,k,x;
    image img;

    initialiseChains(hash_table2);
    printf("Choose type of collision handling:\n1-Linear Probing\n2-Separate chaining\n");
    scanf("%d",&x);
    while(x!=1&&x!=2)
    {
        printf("wrong input, please enter 1 or 2...");
        scanf("%d",&x);
    }
    clock_t start,end;
    double time;
    start = clock();

    fptr = fopen("MNIST-data(datastructures_assignment3)_whitespace.txt", "r");
    for(k=0; k<SIZE; k++)
    {
        for(i=0; i<28; i++)
            for(j=0; j<28; j++)
                fscanf(fptr,"%d",&img.img_arr[i][j]);
        fscanf(fptr,"%d",&key);
        switch (x)
        {
        case 1:
            putLP(key,img);
            break;
        case 2:
            putSC(key,img);
            break;
        }
    }

    fclose(fptr);
    end = clock();
    time = ((double)(end-start))/ CLOCKS_PER_SEC;
    printf("time taken: %f\n",time);
    displayHash(x);
    int whatevs;
    printf("insert image: ");
    for(i=0; i<28; i++)
            for(j=0; j<28; j++)
                scanf("%d",&img.img_arr[i][j]);
    whatevs = getSC(img);
    printf("whatevs get is: %d",whatevs);
    whatevs = removeSC(img);
    printf("whatevs remove is: %d",whatevs);
    displayHash(x);

    outputFILE(x);
    return 0;
}

