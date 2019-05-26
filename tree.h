//
// Created by Has on 20/05/2019.
//

#ifndef COMP20007PROJECT2_TREE_H
#define COMP20007PROJECT2_TREE_H
#endif //COMP20007PROJECT2_TREE_H

typedef struct node_t tNode;

int readArray(int** arr);
tNode* searchTree(tNode* tree, int key);
int height(tNode* node);
void traverseTree(tNode* root);
tNode* sortedArrayToBST(int arr[], int start, int end);
tNode* insert(tNode* root, int data);
int storeValue(tNode *root, int* sorted);
void freeTree(tNode *tree);
int countTree(tNode *root);
void levelOrderTraverse(tNode *root);
