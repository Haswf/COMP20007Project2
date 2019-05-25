/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_3();

int main(int argc, char **argv) {
  problem_3();
  return 0;
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 3 in this function. */
void problem_3() {
    tNode* tree = NULL;
    int* arr = NULL;
    int count = readArray(&arr);
    int i;
    for (i=0;i<count;i++){
        tree = insert(tree, arr[i]);
    };

    int output[count];
    //inOrderTraverse(tree);
    printf("%d\n", countTree(tree));
    printf("%d\n", height(tree));
    ;
    int output_count = storeValue(tree, output);
    //for (int j=0; j<output_count;j++){
    //    printf("%d", output[j]);
    //}
    tNode* balanced = sortedArrayToBST(output, 0, output_count-1);
    //int line = printLine(balanced);
    //rintf("%d\n", line);
    levelOrderTraverse(balanced);
    freeTree(tree);
    freeTree(balanced);
    free(arr);
    arr = NULL;
    tree = NULL;
    balanced = NULL;
};
