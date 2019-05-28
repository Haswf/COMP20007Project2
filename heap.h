//
// Created by Has on 14/05/2019.
//

#ifndef HEAP_H
#define HEAP_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// read input from stdin, store values to array output
int readInputToArray(int** output);
// convert array to a heap
void buildHeap(int* array, int size);
// convert array to a right-handed heap
void buildRightHandedHeap(int* array, int size);

#endif //HEAP_H
