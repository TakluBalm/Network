#include "defs.h"

ID* search_hash(char* name, int number, node** hash, int size_of_hash){
    if (number == -1 && name == NULL) return NULL;
    int alpha_num = (number == -1)?sum_func(name)%(size_of_hash):(number%100);
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