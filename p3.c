/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ Shuyang Fan ]
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

void problem_3() {

    /* read numbers from input */
    int* arr = NULL;
    int count = readArray(&arr);
    int i;

    /* insert elements in array into a btree */
    tNode* tree = NULL;
    for (i=0;i<count;i++){
        tree = insert(tree, arr[i]);
    };

    /* convert array to a set */
    int set[count];
    int setCount = storeValue(tree, set);

    /* insert elements in set to a balanced tree */
    tNode* balanced = sortedArrayToBST(set, 0, setCount-1);

    /* print outputs */
    printf("%d\n", countTree(tree));
    printf("%d\n", height(tree));
    levelOrderTraverse(balanced);

    /* clean up */
    freeTree(tree);
    freeTree(balanced);
    free(arr);
    arr = NULL;
    tree = NULL;
    balanced = NULL;
};
