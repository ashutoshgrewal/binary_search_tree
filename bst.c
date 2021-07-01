#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_s {
    struct node_s *left;
    struct node_s *right;
    int value;
} node_t;

typedef enum direction_s {
    LEFT,
    RIGHT,
} direction_t;

static node_t *
find_parent (node_t *node, int value, direction_t *direction)
{
    if (value == node->value) {
        return NULL;
    } else if (value > node->value) {
        if (node->right == NULL) {
            *direction = RIGHT;
            return node;
        } else {
            return find_parent(node->right, value, direction);
        }
    } else {
        if (node->left == NULL) {
            *direction = LEFT;
            return node;
        } else {
            return find_parent(node->left, value, direction);
        }
    }
}

node_t *
new_node (int value) {
    node_t *node;

    node = (node_t *) malloc (sizeof(node_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}
/**
 * We're not supporting duplicate elements.
 */
bool
insert (node_t **root, int value)
{
    node_t *node;
    node_t *parent;
    direction_t direction;

    if (*root == NULL) {
        //Tree is empty;
        node = new_node(value);
        *root = node;

        return true;
    }
    parent = find_parent (*root, value, &direction);
    if (parent != NULL) {
        node = new_node(value);
        if (direction == LEFT) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        return true;
    } else {
        return false;
    }
}

bool
search (node_t *root, int value)
{
    if (root == NULL) {
        return false;
    } else if (value == root->value) {
        return true;
    } else if (value > root->value) {
        return search(root->right, value);
    } else {
        return search(root->left, value);
    }
}

static node_t *
find_node_with_val (node_t *node, int val, node_t **parent)
{
    *parent = NULL; 
    while (node) {
        if (node->value == val) {
            break;
        }
        *parent = node;
        if (val > node->value) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return node;
}

static node_t *
find_successor (node_t *node, node_t **successor_parent)
{
    node = node->right;
    *successor_parent = node;

    while (node->left != NULL) {
        node = node->left;
        *successor_parent = node;
    }

    return node;
}

static void
swap_node_with_successor (node_t *node, node_t *successor)
{
    int temp;

    temp = node->value;
    node->value = successor->value;
    successor->value = temp;
}

static void
delete_node (node_t **root, node_t *node, node_t *parent)
{
    if (node->right == NULL && node->left == NULL) {
        if (parent == NULL) {
            *root = NULL;
        } else {
            if (parent->left == node) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        free(node);
    } else if (node->right != NULL && node->left == NULL) {
        if (parent == NULL) {
            *root = node->right;
        } else {
            if (parent->left == node) {
                parent->left = node->right;
            } else {
                parent->right = node->right;
            }
        }
        free(node);
    } else if (node->right == NULL && node->left != NULL) {
        if (parent == NULL) {
            *root = node->left;
        } else {
            if (parent->left == node) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        }
        free(node);
    } else {
        node_t *successor, *sucessor_parent;
        successor = find_successor(node, &sucessor_parent);
        swap_node_with_successor(node, successor);
        delete_node(successor, sucessor_parent);
        //TBD Mamta
    }
}

bool
delete (node_t **root, int value)
{
    node_t *parent, *node;

    node = find_node_with_val(*root, value, &parent);

    if (node == NULL) {
        return false;
    }

    delete_node(root, node, parent);
    return true;
}

int
main ()
{
    node_t *root = NULL;

    //Search in an empty tree.
    assert(search(root, 2) == false);

    //Insert
    assert(insert(&root, 2) == true);
    assert(insert(&root, 1) == true);
    assert(insert(&root, 3) == true);

    //Search
    assert(search(root, 3) == true);
    assert(search(root, 4) == false);
    return 0;
}