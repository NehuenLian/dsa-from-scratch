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

        new_linked_list->head = new_node;
        new_linked_list->tail = new_node;
        new_node->prev = NULL;

        *linked_list = new_linked_list;

        return 0;
    } else {
        new_node->prev = (*linked_list)->tail;
        (*linked_list)->tail->next = new_node;
        (*linked_list)->tail = new_node;

        return 0;
    }
    return 0;
}

int insert_at_head(struct LinkedList **linked_list, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    new_node->value = value;
    new_node->prev = NULL;

    if (*linked_list == NULL) {

        struct LinkedList *new_linked_list = malloc(sizeof(struct LinkedList));

        new_linked_list->head = new_node;
        new_linked_list->tail = new_node;

        return 0;
    } else {
        new_node->next = (*linked_list)->head;
        (*linked_list)->head->prev = new_node;
        (*linked_list)->head = new_node;

        return 0;
    }
    return 0;
}

void print_list(struct LinkedList *linked_list) {
    /*
    Print all the list starting by HEAD
    */
    struct Node *current = linked_list->head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void free_linked_list(struct LinkedList *linked_list) {
    /*
    Delete all the list starting by HEAD
    */
    struct Node *current = linked_list->head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(linked_list);
    printf("Free memory process completed.\n");
}

int main() {

    struct LinkedList *linked_list = NULL;

    insert_at_tail(&linked_list, 10);
    insert_at_tail(&linked_list, 15);
    insert_at_tail(&linked_list, 20);
    insert_at_head(&linked_list, 5);
    /*
    Out: 5 -> 10 -> 15 -> 20 -> NULL
    */
    print_list(linked_list);
    free_linked_list(linked_list);

    return 0;
}