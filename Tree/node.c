
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint-gcc.h>
#include "node.h"
#include "../List/list.h"
Node* NodeBalance_h(Node* from);

Node* newNode() {
    Node* node = malloc(sizeof(Node));
    if (!node) { return NULL; }

    node->content = NULL;
    node->count = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node* newNode_withList(List* data) {
    Node* node = newNode();
    if (!node) { return NULL; }
    node->content = data;
    node->count = 1;
    return node;
}



///Returns the maximum depth from a node to the bottom of its children
///Returns 0 if given NULL
///Returns 1 for nodes with no children
///etc...
int32_t NodeDepth(Node* from) {
    if (!from) { return 0; }
    int32_t rd = NodeDepth(from->right);
    int32_t ld = NodeDepth(from->left);
    return (rd >= ld) ? (rd+1) : (ld+1);
}

void NodeNicePrint(FILE* file, Node* from) {
    if (from) {
        NodeNicePrint(file, from->left);
        NodeSoloPrint(file, from);
        NodeNicePrint(file, from->right);
    }
}
void NodeSoloPrint(FILE* file, Node* node) {
    if (node) {
        fprintf(file, "[ %-20s ] x %4d\n", node->content->data, node->count);
    }
}


///Rebalances a node in the tree.
///Returns the pointer to the new local root.
Node* NodeBalance(Node* from) {
    if (!from) { return NULL; }

    int32_t rd = NodeDepth(from->right);
    int32_t ld = NodeDepth(from->left);

    if (abs(rd-ld) >= 2) { ///If the difference in depth is big enough...
        if (rd > ld) { ///Rotate left
            Node* pivot = from->right;
            Node* b = pivot->left;

            from->right = b;
            pivot->left = from;

            return pivot;
        } else {    ///Rotate right
            Node* pivot = from->left;
            Node* b = pivot->right;

            from->left = b;
            pivot->right = from;

            return pivot;
        }
    }
    return from;
}

///Comparison on two lists, assuming they carry c-string payloads
int32_t compare(List* a, List* b) {
    return strcmp(a->data, b->data);
}
///Adds a 'word' into the tree
///Also keeps the tree balanced as it does so.
Node* NodeAdd(Node* from, List* data) {
    if (!from) {
        Node* n = newNode_withList(data);
        return n;
    }
    int32_t dir = compare(data, from->content);

    if (dir == 0) {
        from->count++;
        killList(data);
    } else if (dir < 0) {
        if (from->left) {
            from->left = NodeAdd(from->left, data);
        } else {
            Node* n = newNode_withList(data);
            from->left = n;
        }
    } else {
        if (from->right) {
            from->right = NodeAdd(from->right, data);
        } else {
            Node* n = newNode_withList(data);
            from->right = n;
        }
    }

    return NodeBalance(from);
}
