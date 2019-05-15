//
// Created by Has on 15/05/2019.
//


#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

int main(int argc, char* argv[]) {
    int* dist[V];
}


void testRemove(){
    int* heap = NULL;
    int size = readInputToArray(&heap);
    buildHeap(heap, size);
    int i=0;
    for (i=1; i<=size; i++){
        printf("%d\n", heap[i]);
    }
    removeMax(heap, &size);
    printf("----------------------------\n");
    for (i=1; i<=size; i++){
        printf("%d\n", heap[i]);
    }
    free(heap);
    heap = NULL;
}