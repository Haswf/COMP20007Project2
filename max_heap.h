//
// Created by Has on 14/05/2019.
//

#ifndef COMP20007PROJECT2_MAX_HEAP_H
#define COMP20007PROJECT2_MAX_HEAP_H

#endif //COMP20007PROJECT2_MAX_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int readInputToArray(int** output);
void siftdown(int* heap, int size, int p);
void buildHeap(int* array, int size);
void removeMax(int* heap, int* size);
void buildRightHandedHeap(int* array, int size);