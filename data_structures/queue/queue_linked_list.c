#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Qeue implemented with a linked list

struct LinkedList {
    struct Node *front;
    struct Node *rear;
};

struct Node {
    int value;
    struct Node *next;
};

struct LinkedList* enqueue(struct LinkedList *linked_list, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));

    new_node->value = value;
    new_node->next = NULL;

    if (linked_list == NULL) {

        linked_list = malloc(sizeof(struct LinkedList));

        linked_list->front = new_node;
        linked_list->rear = new_node;

        return linked_list;
    }

    linked_list->rear->next = new_node;
    linked_list->rear = new_node;

    return linked_list;

}

int dequeue(struct LinkedList *linked_list) {

    if (linked_list == NULL) {
        printf("Nothing to dequeue: list is empty.\n");
        return -1;
    }
    if (linked_list->front == NULL) {
        printf("Nothing to dequeue: list is empty.\n");
        return -1;
    }

    struct Node *new_front = linked_list->front->next;
    struct Node *node_to_delete = linked_list->front;
    free(node_to_delete);

    if (new_front == NULL) {
        printf("Las element dequeued: Queue is empty.\n");
        linked_list->rear = NULL;
        linked_list->front = NULL;
        
        return 0;
    }
    linked_list->front = new_front;

    return 0;
}

int peek(struct LinkedList *linked_list, int *value) {

    if (linked_list->front == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }
    *value = linked_list->front->value;

    return 0;
}

void is_empty(struct LinkedList *linked_list) {
    printf("Is empty?\n");

    if (linked_list->front == NULL) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue has elements.\n");
    }
}

int main() {

    struct LinkedList *linked_list = NULL;

    // enqueue three elements
    linked_list = enqueue(linked_list, 5);
    linked_list = enqueue(linked_list, 10);
    linked_list = enqueue(linked_list, 15);

    // dequeue one element
    dequeue(linked_list);

    // take first added element
    int first_in = 0;
    peek(linked_list, &first_in);
    printf("First added: %d\n", first_in);

    // verify status. expected: "Queue has elements."
    is_empty(linked_list);

    // dequeue the last two elements
    dequeue(linked_list);
    dequeue(linked_list);

    // verify status. expected: "Queue is empty."
    is_empty(linked_list);

    // free references
    free(linked_list);

    return 0;
}