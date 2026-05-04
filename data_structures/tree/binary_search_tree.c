#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    struct Node *left;
    struct Node *right;
    int value;
};

struct Node* insert_node(int value, struct Node *root) {

    if (root == NULL) {
        struct Node *new_node = malloc(sizeof(struct Node));

        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = value;

        return new_node;
    }

    if (value < root->value) {
        root->left = insert_node(value, root->left);
    } 
    else if (value > root->value) {
        root->right = insert_node(value, root->right);
    } else {
        printf("Duplicated value %d. Ignored.\n", value);
    }
    return root;
}

void print_preorder(struct Node *root) {
    if (root == NULL) return;

    printf("%d\n", root->value);
    print_preorder(root->left);
    print_preorder(root->right);
}

void print_inorder(struct Node *root) {
    if (root == NULL) return;

    print_inorder(root->left);
    printf("%d\n", root->value);
    print_inorder(root->right);
}

void print_postorder(struct Node *root) {
    if (root == NULL) return;

    print_postorder(root->left);
    print_postorder(root->right);
    printf("%d\n", root->value);
}

void free_tree(struct Node *root) {
    /*
    A BST should always be freed in postorder
    */
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int get_value(struct Node *root, int value_to_search, int *store_value) {

    if (root == NULL) return -1;

    if (root->value == value_to_search) {
        *store_value = root->value;
        return 0;
    }

    if (value_to_search < root->value) {
        return get_value(root->left, value_to_search, store_value);
    } else if (value_to_search > root->value) {
        return get_value(root->right, value_to_search, store_value);
    }
    return -1;
}

struct Node* min_value_node(struct Node* node) {
    /*
    Search the min value going to the left
    */
    struct Node *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Node* delete_value(struct Node *root, int value) {

    if (root == NULL) return NULL;

    if (value < root->value) {
        root->left = delete_value(root->left, value);
    } else if (value > root->value) {
        root->right = delete_value(root->right, value);
    } else {
        // If left and right are NULL (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) { // If left == NULL we take the right node
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) { // If right == NULL we take the left node
            struct Node *temp = root->left;
            free(root);
            return temp;
        } else { // If node has two children
            struct Node* temp = min_value_node(root->right); // Find the min value in the right subtree

            root->value = temp->value; // Current node now has the value of the min node in the subtree

            root->right = delete_value(root->right, temp->value); // Delete the min node from the right subtree
            /*
            Deleting a value doesn't delete the current node itself. Instead, we copy the value of the min node 
            from the right subtree and delete the node that has the min node from the right subtree. 
            */
        }
    }
    return root;
}

int main() {
    struct Node *root = NULL;

    root = insert_node(10, root); // root must be 10
    root = insert_node(5, root); // left must be 5
    root = insert_node(15, root); // right must be 15
    root = insert_node(24, root);
    root = insert_node(3, root);
    root = insert_node(12, root);
    /*
          10
         / \
        5  15
       /    \
     ...    ...
    */

    int value = 0;
    get_value(root, 24, &value);
    printf("Obtained value: %d\n", value);

    root = delete_value(root, 12);

    // Different ways to show/manipulate the tree
    printf("Inorder:\n");
    print_inorder(root);
    
    printf("\nPreorder:\n");
    print_preorder(root);
    
    printf("\nPostorder:\n");
    print_postorder(root);

    free_tree(root);
    root = NULL;

    return 0;
}