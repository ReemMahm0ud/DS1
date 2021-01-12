#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED
#define SIZE 1000
typedef enum {empty,full,available} Status;
typedef struct
{
    int img_arr[28][28];
} image;
typedef struct
{
    image data;
    int key;
} data_item;
typedef struct
{
    Status status;
    data_item item;
    struct hash* next;
} hash;
typedef struct
{
    hash* head, *tail;
} Chain;

hash hash_table[SIZE];
Chain hash_table2[SIZE];

void initialiseChains(Chain* hash_table2);
hash* newNode(int key,image img);
int hashCode(image img);
void displayHash(int x);

void putLP(int key, image img);
int getLP(image img);
int removeLP(image img);

void putSC(int key, image img);
int getSC(image img);
int removeSC(image img);


#endif // PROTOTYPES_H_INCLUDED
