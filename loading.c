#include "defs.h"

int hash_data(char* __filename, node** hash, int __size_of_hash){
    FILE* fd = fopen(__filename, "r");
    FILE* temp = stdin;
    stdin = fd;
    int num, count = 0, multiplier = power_func(10,LEN);
    while(1){
        char name[20];
        int del = scanf("%d,%s", &num, name);
        if (del == EOF){
            fclose(fd);
            stdin = temp;
            return count;
        }
        if (del == 0) continue;
        count++;
        int alpha_num = sum_func(name)%(__size_of_hash);
        node* mediator = malloc(sizeof(node));
        mediator->id = malloc(sizeof(ID));
        mediator->id->total_friends = 0;
        mediator->id->friends = NULL;
        mediator->id->number = num*multiplier + alpha_num;
        int i = 0;
        do{
            mediator->id->name[i] = name[i];
            i++;
        }while(name[i] != '\0');
        mediator->next = NULL;
        if (hash[alpha_num] == NULL) hash[alpha_num] = mediator;
        else{
            mediator->next = hash[alpha_num];
            hash[alpha_num] = mediator;
        }
    }
}


int load_friends(char* __filename, node** hash,int size_of_hash){
    char name1[20], name2[20];
    FILE* fd = fopen(__filename, "r");
    FILE* temp = stdin;
    stdin = fd;
    int friendships = 0;
    while(1){
        int del = scanf("%s %s", name1, name2);
        if (del == EOF) {stdin = temp; fclose(fd); break;}
        if (del == 0)   continue;
        ID* id1 = search_hash(name1, -1, hash, size_of_hash), *id2 = search_hash(name2, -1, hash, size_of_hash);
        int n1 = id1->total_friends++, n2 = id2->total_friends++, max = -1;

        // Putting 2 in friend-list of 1
        int *new1 = malloc(sizeof(int)*(n1+1)), *old1 = id1->friends;
        for (int i = 0; i < n1; i++){
            if(old1[i] < id2->number)   {new1[i] = old1[i];max = i;}
            else                        new1[i+1] = old1[i];
        }
        if (old1 != NULL)   free(old1);
        new1[max+1] = id2->number;
        id1->friends = new1;

        // Putting 1 in friend-list of 2
        int *new2 = malloc(sizeof(int)*(n2+1)), *old2 = id2->friends; max = -1;
        for (int i = 0; i < n2; i++){
            if(old2[i] < id2->number)   {new2[i] = old2[i];max = i;}
            else                        new2[i+1] = old2[i];
        }
        if (old2 != NULL) free(old2);
        new2[max+1] = id1->number;
        id2->friends = new2;

        // Increasing count
        friendships++;
    }
    return friendships;
}