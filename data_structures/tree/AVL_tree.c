#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-balancing binary search tree (AVL) / Adelson-Velsky and Landis

// forward declarations
struct Node* balance(struct Node *root);
struct Node* rotate_right(struct Node *root);
struct Node* rotate_left(struct Node *root);
struct Node* rotate_right_left(struct Node *root);
struct Node* rotate_left_right(struct Node *root);
//

struct Node {
    int height;
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node* insert_node(struct Node *root, int value) {
    if (root == NULL) {
        struct Node *new_node = malloc(sizeof(struct Node));

        new_node->value = value;
        new_node->height = 1;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }

    if (value < root->value) {
        root->left = insert_node(root->left, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, value);
    } else {
        printf("Value ignored cause its in the tree already: %d\n", value);
        return root;
    }
    // Re-calculate heights and balance the tree 
    root = balance(root);

    return root;
}

// deleting a node
struct Node *min_value_node(struct Node* node) {
    /*
    Aux function: search the min value going to the left
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
        // If left and right are NULL
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) { // If left is NULL take the right node
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) { // If right is NULL take the left node
            struct Node *temp = root->left;
            free(root);
            return temp;
        } else { // If node has two children
            struct Node *temp = min_value_node(root->right);

            root->value = temp->value;
            root->right = delete_value(root->right, temp->value);
        }
    }
    // Re-calculate heights and balance the tree 
    root = balance(root);

    return root;
}

// aux func: recaltulate heights

int height(struct Node *node) {
    // gets the height attribute in the node
    if (node == NULL) return 0;
    return node->height;
}

struct Node* balance(struct Node *root) {
    int left_height = height(root->left);
    int right_height = height(root->right);

    if (left_height > right_height) {
        root->height = 1 + left_height;
    } else {
        root->height = 1 + right_height;    
    }
    int factor = left_height - right_height;

    if (factor >= 2) {
        if (height(root->left->left) >= height(root->left->right)) {
            root = rotate_right(root);
        } else {
            root = rotate_left_right(root);
        }

    } else if (factor <= -2) {
        if (height(root->right->right) >= height(root->right->left)) {
            root = rotate_left(root);
        } else {
            root = rotate_right_left(root);
        }
    }
    return root;
}

/*
====================== Heights
*/

int compute_height(struct Node *node) {
    // calculates the total tree height
    if (node == NULL) return 0;

    int left_height = compute_height(node->left);
    int right_height = compute_height(node->right);

    if (left_height > right_height) {
        return 1 + left_height;
    } else {
        return 1 + right_height;
    }
}

/*
====================== Rotations
*/

struct Node* rotate_right(struct Node *root) {

    struct Node *root_left = root->left;
    struct Node *root_left_right = root_left->right;

    root_left->right = root;
    root->left = root_left_right;

    // root descended one level so it will be recalculated its height
    int left_height = height(root->left);
    int right_height = height(root->right);

    if (left_height > right_height) {
        root->height = 1 + left_height;
    } else {
        root->height = 1 + right_height;
    }

    // root descended, and this ascended, so it will recalculated too
    left_height = height(root_left->left);
    right_height = height(root_left->right);

    if (left_height > right_height) {
        root_left->height = 1 + left_height;
    } else {
        root_left->height = 1 + right_height;
    }

    return root_left;
}

struct Node* rotate_left(struct Node *root) {

    struct Node *root_right = root->right;
    struct Node *root_right_left = root_right->left;

    root_right->left = root;
    root->right = root_right_left;

    int left_height = height(root->left);
    int right_height = height(root->right);

    if (left_height > right_height) {
        root->height = 1 + left_height;
    } else {
        root->height = 1 + right_height;
    }

    left_height = height(root_right->left);
    right_height = height(root_right->right);

    if (left_height > right_height) {
        root_right->height = 1 + left_height;
    } else {
        root_right->height = 1 + right_height;
    }

    return root_right;
}

struct Node* rotate_right_left(struct Node *root) {
    root->right = rotate_right(root->right);
    root = rotate_left(root);

    return root;
}

struct Node* rotate_left_right(struct Node *root) {
    root->left = rotate_left(root->left);
    root = rotate_right(root);

    return root;
}

/*
====================== Print tree
*/

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
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// get a value
int get_value(struct Node *root, int value) {
    if (root == NULL) return -1; // special value

    if (root->value == value) return root->value;

    if (value < root->value) {
        return get_value(root->left, value);
    } else if (value > root->value) {
        return get_value(root->right, value);
    }
    return -1;
}

int main() {
    struct Node *root = NULL;
    
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 14);
    root = insert_node(root, 53);
    root = insert_node(root, 5);
    root = insert_node(root, 17);
    /*
           10
          /  \
         5   40
        /      \
      ...     ...
    */
    
    int value = get_value(root, 53);
    printf("Obtained value: %d\n", value);

    int height = compute_height(root);
    printf("Tree height: %d\n", height);

    root = delete_value(root, 14);
    
    // Print in diffrent orders
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