//
// Created by Has on 20/05/2019.
//

#ifndef COMP20007PROJECT2_TREE_H
#define COMP20007PROJECT2_TREE_H

typedef struct node_t tNode;


tNode* recursive_insert(tNode* root, tNode* new);
tNode* searchTree(tNode* tree, int key);
int readArray(int** arr);
int height(tNode* node);
void traverseTree(tNode* root);
tNode* sortedArrayToBST(int arr[], int start, int end);
tNode* insert(tNode* root, int data);
tNode* newNode(int data);
int storeValue(tNode *root, int* sorted);
void free_tree(tNode *tree);
int countTree(tNode *root);
void levelOrderTraverse(tNode *root);
#endif //COMP20007PROJECT2_TREE_H
