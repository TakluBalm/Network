#include "defs.h"

int main(){
    // Making a Hash_Table
    node* hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++)    hash[i] = NULL;

    // Filling the table with data
    int people_scanned = hash_data(LIST, hash, HASH_SIZE);
    printf("%d people were scanned\n", people_scanned);
    char name1[20], name2[20];

    // Reading the input of network
    int total = load_friends(FRIENDS, hash, HASH_SIZE);
    printf("%d pairs loaded\n", total);

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
            if(i == n1)	goto leave;
            if (arr1[i] == arr2[j]){
                count++;
                printf("%d) %s\n", count, search_hash(NULL, arr1[i], hash, HASH_SIZE)->name);
            }
        }
        while(arr2[j] <= arr1[i]){
            j++;
            if(j == n2)	goto leave;
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