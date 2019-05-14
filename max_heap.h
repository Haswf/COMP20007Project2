//
// Created by Has on 14/05/2019.
//

#ifndef COMP20007PROJECT2_MAX_HEAP_H
#define COMP20007PROJECT2_MAX_HEAP_H

#endif //COMP20007PROJECT2_MAX_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int readInputToArray(int** output);
void heapify(int* heap, int size, int i);
void right_heapify(int* heap, int size, int i);
int* build_heap(int* array, int size);
int* build_right_heap(int* array, int size);
void siftdown(int* heap, int size, int p);
void buildHeap(int* array, int size);

