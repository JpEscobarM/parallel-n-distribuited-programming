//
// Created by jmartins on 03/08/2026.
//

#include <hashTable.h>
#include <stdio.h>

static int table[TAM];

void init_table()
{

    for (int i=0;i<TAM;i++)
    {
        table[i] = EMPTY_VALUE;

    }

}

int hash_function(int key){return key % TAM;}

int insert(int value){
    int id  = hash_function(value);

    int attempts = 0;

    while (table[id] != EMPTY_VALUE && attempts < TAM)
    {
        if (table[id] == value)
        {
            printf("\nThis value it's alredy added in the table");
            return 0;
        }

        id = hash_function(++id);
        attempts++;
    }

    if (table[id] == EMPTY_VALUE)
    {
        table[id] = value;
        return 1;

    }
    printf("\nThe hash table is full.");
    return 0;
}

int search( int value)
{
    int id = hash_function(value);
    int attempts = 0;

    while (table[id] != EMPTY_VALUE && attempts < TAM)
    {
        if (table[id] == value)
        {
            printf("\nThis value it's finded in position {%d}", id);
            return  id;
        }

        id = hash_function(++id);
    }
    printf("\nThis value was not found ");
    return -1;
}

void print_table()
{
    printf("\n====================");
    for (int i=0;i<TAM;i++)
    {
        printf("\nid=%d value=%d",i,table[i]);
    }
    printf("\n====================");
}