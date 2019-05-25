//
// Created by Has on 20/05/2019.
//

#include "deque.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

struct node_t {
    int value;
    tNode* left;
    tNode* right;
};


static void recursiveStoreValue(tNode *root, int* sorted, int* n);
static void* recursiveSearchTree(tNode* tnode, int key);
static void recursiveFreeTree(tNode *root);
static tNode* recursiveInsert(tNode* root, tNode* new);
static void recursiveInOrder(tNode* root);
static void recursive_count_tree(tNode* root, int* count);
static void recursive_count_tree(tNode* root, int* count);

int readArray(int** arr){
    int count;
    scanf("%d", &count);
    *arr = (int*)malloc(sizeof(int)*count);
    int i;
    for (i=0;i<count;i++){
        scanf("%d", *arr+i);
    }
    return count;
}

tNode* newtNode(int data){
    tNode* new = (tNode*)malloc(sizeof(tNode));
    new->value = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

tNode* insert(tNode* root, int data){
    tNode* new = newtNode(data);
    //printf("%d %p", data, searchTree(root, data));
    if (!root ||!searchTree(root, data)){
        root = recursiveInsert(root, new);
        //printf("%d inserted\n", data);
    }
    return root;
}

static tNode* recursiveInsert(tNode* root, tNode* new){
    if (root==NULL){
        return new;
    }
    else if (root->value > new->value) {
        root->left = recursiveInsert(root->left, new);
    }
    else {
        root->right = recursiveInsert(root->right, new);
    }
    return root;
}

tNode* searchTree(tNode* tree, int key){
    assert(tree);
    return recursiveSearchTree(tree, key);
}

void inOrderTraverse(tNode* root){
    assert(root);
    recursiveInOrder(root);
}

static void recursiveInOrder(tNode* root) {
    if (root) {
        recursiveInOrder(root->left);
        printf("%d", root->value);
        recursiveInOrder(root->right);
    }
}

static void* recursiveSearchTree(tNode* tnode, int key){
    if (!tnode){
        return NULL;
    }
    if (tnode->value > key){
        recursiveSearchTree(tnode->left, key);
    }
    else if (tnode->value < key){
        recursiveSearchTree(tnode->right, key);
    }
    else {
        return tnode;
    }
}

int storeValue(tNode *root, int* sorted){
    assert(root);
    int n = 0;
    recursiveStoreValue(root, sorted, &n);
    return n;
}

static void recursiveStoreValue(tNode *root, int* sorted, int* n) {
    if (root) {
        recursiveStoreValue(root->left, sorted, n);
        sorted[(*n)++] = root->value;
        recursiveStoreValue(root->right, sorted, n);
    }
}

/* Release all memory space associated with the tree
   structure. */
void freeTree(tNode *tree) {
    assert(tree!=NULL);
    recursiveFreeTree(tree);
}

static void recursiveFreeTree(tNode *root) {
    if (root) {
        recursiveFreeTree(root->left);
        recursiveFreeTree(root->right);
        free(root);
    }
}

int height(tNode* tnode){
    if (tnode == NULL)
        return 0;
    else{
        /* compute the depth of each subtree */
        int lDepth = height(tnode->left);
        int rDepth = height(tnode->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

tNode* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end){
        tNode* nil = newtNode(-1);
        return nil;

    }

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    tNode *root = newtNode(arr[mid]);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);

    return root;
}

void levelOrderTraverse(tNode* root) {
    Deque *q = new_deque();
    deque_insert(q, root);
    int array[(int) pow(2, height(root))];

    int length = 0;
    while (deque_size(q) > 0) {
        tNode *curr = deque_pop(q);
        array[length++] = curr->value;
        if (curr->left) {
            deque_insert(q, curr->left);
        }
        if (curr->right) {
            deque_insert(q, curr->right);
        }
    }
    while (array[length-1] == -1){
        length--;
    }
    printf("%d\n", length);

    int i;
    for (i=0;i<length;i++){
        printf("%d\n", array[i]);
    }
}

int countTree(tNode *root){
    assert(root!=NULL);
    int count = 0;
    recursive_count_tree(root, &count);
    return count;
}

static void recursive_count_tree(tNode* root, int* count){
    if (root) // if root exist
    {
        recursive_count_tree(root->left, count);
        recursive_count_tree(root->right, count);
        *count += 1;
    }
}


//int main(int argc, char* argv[]){
//    tNode* tree = NULL;
//    int* arr = NULL;
//    int count = readArray(&arr);
//    int i;
//    for (i=0;i<count;i++){
//        tree = insert(tree, arr[i]);
//    };
//
//    int output[count];
//    //inOrderTraverse(tree);
//    printf("%d\n", countTree(tree));
//    printf("%d\n", height(tree));
//    ;
//    int output_count = storeValue(tree, output);
//    //for (int j=0; j<output_count;j++){
//    //    printf("%d", output[j]);
//    //}
//    tNode* balanced = sortedArrayToBST(output, 0, output_count-1);
//    //int line = printLine(balanced);
//    //rintf("%d\n", line);
//    levelOrderTraverse(balanced);
//    free_tree(tree);
//    return 0;
//};

