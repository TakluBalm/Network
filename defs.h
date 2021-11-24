#ifndef __MY_DEFS
#define __MY_DEFS

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10
#define LEN 2
#define LIST    "test_names.txt"
#define FRIENDS "test_network.txt"

typedef struct ID{
    int* friends;
    int number;
    int total_friends;
    char name[20];
}ID;

typedef struct node{
    ID* id;
    struct node* next;
}node;

//  loading.c
int load_friends(char* __filename, node** hash,int size_of_hash);
int hash_data(char* __filename, node** hash, int __size_of_hash);

//  extrafuncs.c
int eq_check(char* s1, char* s2);
int power_func(int base, int power);
int sum_func(char* string);

// srchnunld.c
ID* search_hash(char* name, int number, node** hash, int size_of_hash);
void free_list(node* list);
void free_hash(node** hash, int size_of_hash);

#include "extrafuncs.c"
#include "loading.c"
#include "srchnunld.c"

#endif