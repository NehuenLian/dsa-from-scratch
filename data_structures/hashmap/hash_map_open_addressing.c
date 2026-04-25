#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Open addressing collision method hashmap (using linear probing) index = (hash(key) + i) % TABLE SIZE
Other probing methods:

-Quadratic Probing: index = (hash(key) + i^2) % TABLE SIZE

-Double Hashing: index = (hash1(key) + i * hash2(key)) % TABLE SIZE
*/

#define TABLE_SIZE 10

struct HashNode {
    char* key;
    int value;
    int is_occupied; // 0 = free, 1 = occupied, 2 = deleted
};

struct HashNode hash_table[TABLE_SIZE];

int hash(char *key) {
    int sum = 0;
    
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

int insert(char* key, int value) {
    int index = hash(key);
    int original_index = index;

    while (hash_table[index].is_occupied == 1) {
        index = (index + 1) % TABLE_SIZE; // linear probing

        if (index == original_index) {
            printf("Table is full, couldn't insert\n");
            return -1;
        }
    }

    hash_table[index].key = strdup(key); // duplicates the key string in heap
        
    if (!hash_table[index].key) {
        perror("strdup failed");
        return -1;
    }
    hash_table[index].value = value;
    hash_table[index].is_occupied = 1;

    return 0;
}

int search(char* key, int *value) {
    int index = hash(key);
    int original_index = index;

    while (hash_table[index].is_occupied != 0) {
        if (hash_table[index].is_occupied == 1 && strcmp(hash_table[index].key, key) == 0) {
            *value = hash_table[index].value;
            return 0;
        }

        index = (index + 1) % TABLE_SIZE; // linear probing
        if (index == original_index) {
            break;
        }
    }
    return -1;
}

void delete(char* key) {
    int index = hash(key);
    int original_index = index;

    while (hash_table[index].is_occupied != 0) {
        if (hash_table[index].is_occupied == 1 && strcmp(hash_table[index].key, key) == 0) {

            free(hash_table[index].key); // free the key string in heap made it previously with strdup()
            hash_table[index].key = NULL;
            hash_table[index].is_occupied = 2;
            return;
        }

        index = (index + 1) % TABLE_SIZE; // linear probing
        if (index == original_index) {
            break;
        }
    }
    printf("Key '%s' not found.\n", key);
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {

        if (hash_table[i].is_occupied == 1) {
            printf("%d: (%s,%d)", i, hash_table[i].key, hash_table[i].value);
        }
        else if (hash_table[i].is_occupied == 2) {
            printf("%d: <deleted>\n", i);
        }
        else {
            printf("%d: <empty>\n", i);
        }
    }
}

int main() {

    insert("Ana", 25);
    insert("Luis", 30);
    insert("Juan", 28);
    insert("Maria", 22);

    print_table();

    int juan_value = 0;
    search("Juan", &juan_value);

    printf("Searching 'Juan': %d\n", juan_value);
    printf("Deleting 'Juan'...\n");
    delete("Juan");

    print_table();
    /*
    Out:
    0: (Maria,22)1: <empty>
    2: (Ana,25)3: (Luis,30)4: <empty>
    5: <empty>
    6: <empty>
    7: <empty>
    8: <deleted>
    9: <empty>
    */
    return 0;
}