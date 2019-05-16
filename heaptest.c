//
// Created by Has on 15/05/2019.
//


#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"
void testRemove();

int main(int argc, char* argv[]) {
    int* heap = NULL;
    int size = readInputToArray(&heap);
    buildRightHandedHeap(heap, size);
    int i;
    for (i=1;i<=size;i++){
        printf("%d\n", heap[i]);
    }
    free(heap);
    heap = NULL;
    return 0;
}


void testRemove(){
    int* heap = NULL;
    int size = readInputToArray(&heap);
    buildRightHandedHeap(heap, size);
    int i=0;
    for (i=1; i<=size; i++){
        printf("%d\n", heap[i]);
    }
    free(heap);
    heap = NULL;
}