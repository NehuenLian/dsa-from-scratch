#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Hashmap using chaining for collision handling
*/

#define TABLE_SIZE 10

struct Node {
    char* key;
    int value;
    struct Node *next;
};

struct Node* hash_table[TABLE_SIZE];

int hash(char* key) {
    int sum = 0;
    
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

int insert(char* key, int value) {
    int index = hash(key);

    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->key = strdup(key); // duplicates the key string in heap

    if (!new_node->key) {
        perror("strdup failed");
        return -1;
    }
    new_node->value = value;

    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    return 0;
}

int search(char* key, int *value) {
    int index = hash(key);
    struct Node *current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 0;
        }
        current = current->next;
    }

    return -1;
}

void delete(char *key) {
    int index = hash(key);;

    struct Node* current = hash_table[index];
    struct Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {

            if (prev == NULL) {
                hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);

            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key '%s' not found\n", key);
}


void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {

        printf("%d: ", i);
        struct Node* current = hash_table[i];

        while (current != NULL) {
            printf("(%s,%d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {

    insert("Ana", 25);
    insert("Luis", 30);
    insert("Juan", 28);
    insert("Maria", 22);

    print_table();

    int luis_value = 0;
    search("Luis", &luis_value);

    int pedro_value = 0;
    search("Pedro", &pedro_value);

    printf("'Luis' value: %d\n", luis_value);
    printf("'Pedro' value: %d\n", pedro_value);

    printf("\nDeleting 'Juan'...\n");
    delete("Juan");

    print_table();
    /*
    Out:
    0: (Maria,22) -> NULL
    1: NULL
    2: (Ana,25) -> NULL
    3: (Luis,30) -> NULL
    4: NULL
    5: NULL
    6: NULL
    7: NULL
    8: NULL
    9: NULL
    */
    return 0;
}