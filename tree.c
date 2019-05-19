//
// Created by Has on 20/05/2019.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void recursiveStoreValue(Node *root, int* sorted, int* n);
static Node* recursiveSearchTree(Node* node, int key);
static void recursive_free_tree(Node *root);
static Node* recursiveInsert(Node* root, Node* new);
static void recursiveInOrder(Node* root);
static void recursive_count_tree(Node* root, int* count);
static void recursive_count_tree(Node* root, int* count);

struct node_t {
    int value;
    Node* left;
    Node* right;
};

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

Node* newNode(int data){
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* insert(Node* root, int data){
    Node* new = newNode(data);
    //printf("%d %p", data, searchTree(root, data));
    if (!root ||!searchTree(root, data)){
        root = recursiveInsert(root, new);
        //printf("%d inserted\n", data);
    }
    return root;
}

static Node* recursiveInsert(Node* root, Node* new){
    if (root==NULL){
        return new;
    }
    else if (root->value > new->value) {
        root->left = recursiveInsert(root->left, new);
    }
    else {
        root->right = recursiveInsert(root->right, new);
    }
}


Node* searchTree(Node* tree, int key){
    assert(tree);
    return recursiveSearchTree(tree, key);
}

void inOrderTraverse(Node* root){
    assert(root);
    recursiveInOrder(root);
}

static void recursiveInOrder(Node* root) {
    if (root) {
        recursiveInOrder(root->left);
        printf("%d", root->value);
        recursiveInOrder(root->right);
    }
}

static Node* recursiveSearchTree(Node* node, int key){
    if (!node){
        return NULL;
    }
    if (node->value > key){
        recursiveSearchTree(node->left, key);
    }
    else if (node->value < key){
        recursiveSearchTree(node->right, key);
    }
    else {
        return node;
    }
}

int storeValue(Node *root, int* sorted){
    assert(root);
    int n = 0;
    recursiveStoreValue(root, sorted, &n);
    return n;
}

static void recursiveStoreValue(Node *root, int* sorted, int* n) {
    if (root) {
        recursiveStoreValue(root->left, sorted, n);
        sorted[(*n)++] = root->value;
        recursiveStoreValue(root->right, sorted, n);
    }
}

/* Release all memory space associated with the tree
   structure. */
void free_tree(Node *tree) {
    assert(tree!=NULL);
    recursive_free_tree(tree);
}

static void recursive_free_tree(Node *root) {
    if (root) {
        recursive_free_tree(root->left);
        recursive_free_tree(root->right);
        free(root);
    }
}



int maxDepth(Node* node){
    if (node == NULL)
        return 0;
    else{
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

Node* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
        return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end+1)/2;
    Node *root = newNode(arr[mid]);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);

    return root;
}

int printLevelOrder(Node* root)
{
    int n = 0;
    int h = maxDepth(root);
    int i;
    for (i = 1; i <= h; i++)
        printGivenLevel(root, i, &n);
    return n;
}

/* Print nodes at a given level */
void printGivenLevel(Node* root, int level, int* n) {
    if (root == NULL) {
        printf("-1\n");
        (*n)++;
        return;
    }
    if (level == 1) {
        printf("%d\n", root->value);
        (*n)++;
    } else if (level > 1) {
        printGivenLevel(root->left, level - 1, n);
        printGivenLevel(root->right, level - 1, n);
    }
}

int printLine(Node* root) {
    int n = 0;
    int h = maxDepth(root);
    int i;
    for (i = 1; i <= h; i++)
        CountGivenLine(root, i, &n);
    return n;
}

void CountGivenLine(Node* root, int level, int* n){
    if (root == NULL){
        return;
    }
    if (level == 1){
        (*n)++;
    }
    else if (level > 1){
        CountGivenLine(root->left, level-1, n);
        CountGivenLine(root->right, level-1, n);
    }
}


int countTree(Node *root){
    assert(root!=NULL);
    int count = 0;
    recursive_count_tree(root, &count);
    return count;
}

static void recursive_count_tree(Node* root, int* count){
    if (root) // if root exist
    {
        recursive_count_tree(root->left, count);
        recursive_count_tree(root->right, count);
        *count += 1;
    }
}


//int main(int argc, char* argv[]){
//    Node* tree = NULL;
//    int* arr = NULL;
//    int count = readArray(&arr);
//    int i;
//    for (i=0;i<count;i++){
//        tree = insert(tree, arr[i]);
//    }
//    int output[count];
//    //inOrderTraverse(tree);
//    printf("%d\n", countTree(tree));
//    printf("%d\n", maxDepth(tree));
//;
//    int output_count = storeValue(tree, output);
//    //for (int j=0; j<output_count;j++){
//    //    printf("%d", output[j]);
//    //}
//    Node* balanced = sortedArrayToBST(output, 0, output_count-1);
//    int line = printLine(balanced);
//    printf("%d\n", line);
//    printLevelOrder(balanced);
//    free_tree(tree);
//    return 0;
//};

