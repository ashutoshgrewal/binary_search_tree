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

bool
delete (node_t **root, int value)
{
    //TBD
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