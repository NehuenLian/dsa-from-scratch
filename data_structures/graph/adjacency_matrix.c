#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXT 20

struct Node {
    int value;
};

struct Graph {
    int matrix[EXT][EXT];
    int total_nodes;
    struct Node* nodes[EXT];
};

struct Graph* add_node(struct Graph *graph, int value) {

    if (graph == NULL) {
        struct Graph *new_graph = calloc(1, sizeof(struct Graph));

        new_graph->total_nodes = 1;
        new_graph->matrix[0][0] = 0;

        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->value = value;
        new_graph->nodes[0] = new_node;

        return new_graph;
    }

    if (graph->total_nodes < EXT) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->value = value;

        graph->total_nodes++;
        int node_index = graph->total_nodes - 1;

        graph->matrix[node_index][node_index] = 0;
        graph->nodes[node_index] = new_node;

        return graph;
    } else {
        printf("Error adding a node: matrix is full.\n");
        return graph; // return struct Graph *graph = NULL;
    }

}

void connect(struct Graph *graph, int index1, int index2) { // O(1)
    if (graph->nodes[index1] != NULL && graph->nodes[index2] != NULL) {
        graph->matrix[index1][index2] = 1;
    } else {
        printf("There is no node in index.\n");
    }
}

void disconnect(struct Graph *graph, int index1, int index2) { // O(1)
    if (graph->nodes[index1] != NULL && graph->nodes[index2] != NULL) {
        graph->matrix[index1][index2] = 0;
    } else {
        printf("There is no node in index.\n");
    }
}

void print_graph(struct Graph *graph) { // O(n)
    for (int i = 0; i < graph->total_nodes; i++) {

        if (graph->nodes[i] != NULL) {
            printf("%d\n", graph->nodes[i]->value);
        }   
    }
}

int get_by_index(struct Graph *graph, int index, int *value) {
    if (index < 0 || index >= graph->total_nodes) {
        printf("Out of index.\n");
        return -1;
    } else if (graph->nodes[index] == NULL) {
        printf("Non existent node at index %d\n.", index);
        return -1;
    } else {
        *value = graph->nodes[index]->value;
        return 0;
    }
}

void remove_node(struct Graph *graph, int index) { // O(n)
    /*
    Disconnect from all nodes
    */
    for (int i = 0; i < graph->total_nodes; i++) {
        graph->matrix[index][i] = 0;
        graph->matrix[i][index] = 0;
    }
    free(graph->nodes[index]);
    graph->nodes[index] = NULL;
}

void free_graph(struct Graph *graph) {
    for (int i = 0; i < graph->total_nodes; i++) {
        free(graph->nodes[i]);
        graph->nodes[i] = NULL;
    }
    free(graph);
}

int main() {
    struct Graph *graph = NULL;
    graph = add_node(graph, 5);
    graph = add_node(graph, 10);
    graph = add_node(graph, 15);
    graph = add_node(graph, 20);

    connect(graph, 1, 2);
    connect(graph, 3, 1);
    connect(graph, 1, 0);

    print_graph(graph);

    disconnect(graph, 1, 2);
    
    int value = 0;
    get_by_index(graph, 3, &value);
    printf("Value obtanied: %d\n", value);

    remove_node(graph, 2);
    free_graph(graph);

    return 0;
}