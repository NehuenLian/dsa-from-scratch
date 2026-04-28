#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node *next;
};

int insert_node(struct Node **head, int value) {
    /*
    Inserts a node at the end of the list:
    head -> new_node -> null
    */
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node; // if head is null return new_node as the first node
        return 0;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node; // insert new node an the end
    *head = current;

    return 0;
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void free_linked_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        current = current->next;
        free(head);
        head = current;
    }
    printf("Free memory process completed.\n");
}

int main() {
    struct Node *linked_list = NULL;
    
    insert_node(&linked_list, 5);
    insert_node(&linked_list, 10);
    insert_node(&linked_list, 15);
    /*
    Out: 5 -> 10 -> 15 -> NULL
    */
    print_list(linked_list);
    free_linked_list(linked_list);

    return 0;
}