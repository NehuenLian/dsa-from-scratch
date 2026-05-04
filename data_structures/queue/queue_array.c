#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int queue[MAX];
int front = 0;
int rear = 0;

int enqueue(int element) {

    if ((rear + 1) % MAX == front) { // if the result of rear + 1 % 10 == current value of front...
        printf("Queue is full.\n");
        return -1;
    }
    queue[rear] = element;
    rear = (rear + 1) % MAX;

    return 0;
}

int dequeue(int *value) {
    if (value == NULL) {
        return -1;
    }

    if (front == rear) {
        printf("Queue is empty.\n");
        return -1;
    }

    *value = queue[front];
    front = (front + 1) % MAX;

    return 0;   
}

int is_empty() {
    if (front == rear) {
        printf("Queue is empty.\n");
        return 0;
    } else {
        return -1;
    }
}

int is_full() {
    if ((rear + 1) % MAX == front) { // if the result of rear + 1 % 10 == current value of front...
        printf("Queue is full.\n");
        return 0;
    } else {
        return -1;
    }
}

int peek(int *value) {

    if (front == rear) {
        printf("Queue is empty.\n");
        return -1;
    }
    *value = queue[front];

    return 0;
}

int main() {

    // enqueue elements
    enqueue(5);
    enqueue(10);
    enqueue(15);

    // take the first added
    int first_in = 0;
    peek(&first_in);
    printf("First added: %d\n", first_in);

    // dequeue the three elements added
    int dummy = 0;
    dequeue(&dummy);
    dequeue(&dummy);
    dequeue(&dummy);

    // verify status
    is_empty();

    return 0;
}