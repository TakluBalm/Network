#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int sum_func(char* string){
    int sum = 0, k = 1;
    for (int i = 0; string[i] != '\0'; i++){
        sum += k*string[i];
        k *= -1;
    }
    if (sum > 0)    return sum;
    else            return -1*sum;
}

int exp(int base, int power){
    int result = 1;
    if (power >= 0){
        for(int i = 0; i < power; i++){
            result *= base;
        }
        return result;
    }
    else{
        for(int i = power; i < 0; i++){
            result /= base;
        }
        return result;
    }
}

int hash_data(char* __filename, node** hash, int __size_of_hash){
    FILE* fd = fopen(__filename, "r");
    FILE* temp = stdin;
    stdin = fd;
    int num, count = 0;
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
        mediator->id->number = num*(exp(10,LEN)) + alpha_num;
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

int eq_check(char* s1, char* s2){
    int i = 0;
    while(1){
        if (s1[i] == '\0' && s2[i] == '\0') return 1;
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0') return 0;
        i++; 
    }
}

ID* search_hash(char* name, int number, node** hash, int size_of_hash){
    if (number == -1 && name == NULL) return NULL;
    int alpha_num = (number == -1)?hash_func(name)%(size_of_hash):(number%100);
    node* current = hash[alpha_num];
    while(1){
        if (current == NULL) return NULL;
        if (number == -1 && eq_check(current->id->name, name)) return current->id;
        if (number == current->id->number) return current->id;
        current = current->next;
    }
}

void free_list(node* list){
    if (list == NULL) return;
    while(list->next != NULL){
        node* current = list;
        node* prev = NULL;
        while(current->next != NULL){
            prev = current;
            current = current->next;
        }
        prev->next = NULL;
        free(current->id->friends);free(current->id); free(current);
    }
    free(list->id->friends);free(list->id); free(list);
    return;
}

void free_hash(node** hash, int size_of_hash){
    for (int i = 0; i < size_of_hash; i++){
        free_list(hash[i]);
    }
}

int main(){
    // Making a Hash_Table
    node* hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++)    hash[i] = NULL;

    // Filling the table with data
    int people_scanned = hash_data(LIST, hash, HASH_SIZE);
    printf("%d people were scanned\n", people_scanned);
    char name1[20], name2[20];

    // Reading the input of network
    FILE* fd = fopen(FRIENDS, "r");
    FILE* temp = stdin;
    stdin = fd;
    while(1){
        int del = scanf("%s %s", name1, name2);
        if (del == EOF) {stdin = temp; fclose(fd); break;}
        if (del == 0)   continue;
        ID* id1 = search_hash(name1, -1, hash, HASH_SIZE), *id2 = search_hash(name2, -1, hash, HASH_SIZE);
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
    }

    prompt:         // Prompt Label to signify the point at which the prompt section starts;

    printf("Write names to compare: ");
    scanf("%s %s", name1, name2);
    ID *id1 = search_hash(name1, -1, hash, HASH_SIZE), *id2 = search_hash(name2, -1, hash, HASH_SIZE);
    if (id1 != NULL && id2 != NULL){
        int *arr1 = id1->friends, *arr2 = id2->friends, n1 = id1->total_friends, n2 = id2->total_friends;
        int i=0, j=0, count = 0;

        start:      // Start Label signifies the point where the intersection program starts

        while(arr1[i] <= arr2[j]){
            i++;
            if(i == n1) goto leave;
            if (arr1[i] == arr2[j]){
                count++;
                printf("%d) %s\n", count, search_hash(NULL, arr1[i], hash, HASH_SIZE)->name);
            }
        }
        while(arr2[j] <= arr1[i]){
            j++;
            if (j == n2) goto leave;
            if (arr1[i] == arr2[j]){
                count++;
                printf("%d) %s\n", count, search_hash(NULL, arr1[i], hash, HASH_SIZE)->name);
            }
        }
        goto start;
    }
    else {printf("Enter Valid Names\n"); goto prompt;}

    leave:      // Leave Label signifies the point where the program exits

    free_hash(hash, HASH_SIZE);
}