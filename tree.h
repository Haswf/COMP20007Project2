//
// Created by Has on 20/05/2019.
//

#ifndef COMP20007PROJECT2_TREE_H
#define COMP20007PROJECT2_TREE_H


typedef struct node_t Node;
Node* recursive_insert(Node* root, Node* new);
Node* searchTree(Node* tree, int key);
int readArray(int** arr);
int maxDepth(Node* node);
void traverseTree(Node* root);
Node* sortedArrayToBST(int arr[], int start, int end);
void printGivenLevel(Node* root, int level, int* n);
int printLevelOrder(Node* root);
int printLine(Node* root);
void CountGivenLine(Node* root, int level, int* n);
Node* insert(Node* root, int data);
Node* newNode(int data);
int storeValue(Node *root, int* sorted);
void free_tree(Node *tree);
int countTree(Node *root);

#endif //COMP20007PROJECT2_TREE_H
