#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adjacency list graph (directed graph)

struct Node {
    struct Node *next;
    int destiny;
    int value;
};

struct AdjacencyList {
    struct Node *head;
};

struct Graph {
    int V;
    struct AdjacencyList *list;
};

struct Graph* create_graph(int V) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->V = V;
    graph->list = malloc(sizeof(struct AdjacencyList) * V);

    for (int i = 0; i < V; i++) {
        graph->list[i].head = NULL;
    }
    return graph;
}

void add_node(struct Graph *graph, int source, int destiny, int value) {

    if (destiny >= graph->V || destiny < 0) {
        printf("Error: destiny out of range: %d\n", destiny);
        return;
    }
    if (source >= graph->V || source < 0) {
        printf("Error: Out of edge.\nEdge: %d\n", graph->V);
        return;
    }

    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->destiny = destiny;

    new_node->next = graph->list[source].head;
    graph->list[source].head = new_node;

}

void remove_node(struct Graph *graph, int source, int destiny) {

    if (destiny >= graph->V || destiny < 0) {
        printf("Error: destiny out of range: %d\n", destiny);
        return;
    }
    if (source >= graph->V || source < 0) {
        printf("Error: Out of edge.\nEdge: %d\n", graph->V);
        return;
    }

    struct Node *temp = graph->list[source].head;
    struct Node *prev = NULL;

    while (temp != NULL && temp->destiny != destiny) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) { // if no match was found 
        printf("There is not a node associated with destiny: %d.\n", destiny);
        return;
    }

    if (prev == NULL) {
        graph->list[source].head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

void free_graph(struct Graph *graph) {
    if (graph == NULL) {
        printf("Couldn't free the graph: Graph is NULL (empty).\n");
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        struct Node *temp = graph->list[i].head;

        while (temp != NULL) {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(graph->list);
    free(graph);
}

void print_graph(struct Graph *graph) {
    for (int i = 0; i < graph->V; i++) {
        printf("V %d list: ", i);
        struct Node *temp = graph->list[i].head;
        while (temp != NULL) {
            printf("%d -> ", temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {

    struct Graph *graph = create_graph(5); // create graph with 5 vertices

    add_node(graph, 0, 2, 5); // add to vertex 0, points to vertex 2, value: 5
    add_node(graph, 1, 3, 10); // add to vertex 1, points to vertex 3, value: 10
    add_node(graph, 2, 4, 15); // add to vertex 2, points to vertex 4, value: 15
    add_node(graph, 3, 1, 20); // add to vertex 3, points to vertex 1, value: 20

    print_graph(graph); // verify status

    remove_node(graph, 1, 3); // Remove edge from vertex 1 to vertex 3 (first found)

    print_graph(graph); // verify status after remove

    free_graph(graph);
    return 0;
}