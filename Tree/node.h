#include "../List/list.h"
#ifndef NODE_INC
#define NODE_INC
typedef struct Node {
    List* content;
    int count;
    struct Node* left;
    struct Node* right;
} Node;

///Constructs a new, empty node.
///content is null
///left and right are null.
///count is zero.
Node* newNode();

///Constructs a new node
///Initializes with a list pointer for content
///count is one
///left and right are null
Node* newNode_withList();

///Balances a tree, and returns the node to be considered the root.
///May or may not modify the root, based on the tree's balance.
Node* NodeBalance(Node* root);

///Prints out a tree, in-order traversal, to a given FILE*, from a given node.
void NodeNicePrint(FILE* file, Node* from);
///Prints out just one node.
void NodeSoloPrint(FILE* file, Node* from);

#endif // NODE_INC
