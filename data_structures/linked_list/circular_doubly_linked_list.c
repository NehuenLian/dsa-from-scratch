#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

int insert_at_tail(struct LinkedList **linked_list, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*linked_list == NULL) {
        struct LinkedList *new_linked_list = malloc(sizeof(struct LinkedList));

        // if its the first node, will point itself in next and prev. tail and head will be the same node also.
        new_node->next = new_node; 
        new_node->prev = new_node;

        new_linked_list->tail = new_node;
        new_linked_list->head = new_node;

        *linked_list = new_linked_list;

        return 0;
    }
    else {
        new_node->next = (*linked_list)->head;
        new_node->prev = (*linked_list)->tail;

        (*linked_list)->tail->next = new_node; // update before we change the head
        (*linked_list)->head->prev = new_node;

        (*linked_list)->tail = new_node; // only update the tail, head still being the same node, because we inserted in head
            
        return 0;
    }

    return 0;
}

struct LinkedList* insert_at_head(struct LinkedList *linked_list, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (linked_list == NULL) {
        linked_list = malloc(sizeof(struct LinkedList));

        // if its the first node, will point itself in next and prev. tail and head will be the same (and the only one) node also.
        new_node->next = new_node;
        new_node->prev = new_node;

        linked_list->tail = new_node;
        linked_list->head = new_node;


        return linked_list;
    } else {

        new_node->next = linked_list->head;
        new_node->prev = linked_list->tail;

        linked_list->head->prev = new_node; // update before we change the head
        linked_list->tail->next = new_node;

        linked_list->head = new_node; // only update the head, tail still being the same node, because we inserted in head

    }
    return linked_list;
}

void print_list(struct LinkedList *linked_list) {
    struct Node *current = linked_list->head;
    printf("-> ");

    do {
        printf("%d -> ", current->value);
        current = current->next; 
    } while (current != linked_list->head); // do {} while; for skip first iteration, that will be false 

    printf("\n");
}

void free_linked_list(struct LinkedList *linked_list) {
    if (!linked_list->head) return;

    struct Node *current = linked_list->head;
    struct Node *next_node;

    do {
        next_node = current->next;
        free(current);
        current = next_node;
    } while (current != linked_list->head); // do {} while; for skip first iteration, that will be false 
    free(linked_list);
    
    printf("Free memory process completed.\n");
}


int main() {
    struct LinkedList *linked_list = NULL;

    insert_at_tail(&linked_list, 10);
    insert_at_tail(&linked_list, 15);
    insert_at_tail(&linked_list, 20);
    linked_list = insert_at_head(linked_list, 5);
    /*
    Out:
    -> 5 -> 10 -> 15 -> 20 -> 
    */
    print_list(linked_list);
    free_linked_list(linked_list);

    return 0;
}