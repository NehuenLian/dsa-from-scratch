#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
This is a circular classic linked list (whitout tail)
*/

struct Node {
    int value;
    struct Node *next;
};

int insert_node(struct Node **head, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    } 

    new_node->value = value;

    if (*head == NULL) {
        new_node->next = new_node; // if there's only one node, it will point itself
        *head = new_node;
        return 0;
    }

    struct Node *current = *head;
    while (current->next != *head) {
        current = current->next; // go to the last 
    }

    current->next = new_node; // add new node at the end
    new_node->next = *head; // close the circle

    return 0;
}

int print_list(struct Node *head) {
    struct Node *current = head;
    if (current == NULL) {
        return -1;
    }
    
    do {
        printf("%d -> ", current->value);
        current = current->next; 
    } while (current != head); // do {} while; for skip first iteration, that will be false 

    printf("HEAD\n");
    return 0;
}

void free_linked_list(struct Node *head) {
    if (!head) {
        return;
    }

    struct Node *current = head->next;
    struct Node *next_node; // the next node after the current

    while (current != head) {
        next_node = current->next;
        free(current);
        current = next_node;  // current was freed so we set the next node to free
    }
    free(head);

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