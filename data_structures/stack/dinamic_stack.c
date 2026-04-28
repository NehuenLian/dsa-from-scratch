#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is a dinamic stack O(1) made with a linked list.

struct Node {
    int value;
    struct Node *next;
};

struct Node* push(struct Node *head, int value) {
    
    struct Node *new_node = malloc(sizeof(struct Node));

    new_node->value = value;
    new_node->next = NULL;  

    if (head == NULL) {
        return new_node;
    }

    new_node->next = head;
    
    return new_node;
}

struct Node* pop(struct Node *head) {
    if (head == NULL) {
        printf("Couldn't pop element: the stack is empty.\n");
        exit(1);
    }

    struct Node *prev = head->next;
    free(head);

    return prev;
}

int peek(struct Node *head, int *value) {
    if (head == NULL) {
        printf("The stack is empty.\n");
        return -1;
    }
    *value = head->value;

    return 0;
}

void is_empty(struct Node *head) {
    printf("Is empty?:\n");
    if (head == NULL) {
        printf("The stack is empty.\n");
    } else {
        printf("The stack has elements.\n");
    }
}

void print_stack(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = NULL;

    // push some elements
    head = push(head, 5);
    head = push(head, 10);
    head = push(head, 15);

    print_stack(head);
    /*
    Out: 15 -> 10 -> 5 -> NULL
    */
    head = pop(head);

    print_stack(head);
    /*
    Out: 10 -> 5 -> NULL
    */

    // verify status (must be "The stack has elements.")
    is_empty(head);

    // get the last
    int value = 0;
    int peek_last = peek(head, &value);
    printf("Last element: %d\n", peek_last);

    // pop last 2 elements remaining
    head = pop(head);
    head = pop(head);

    // verify status (must be "The stack is empty.")
    is_empty(head);

    return 0;
}