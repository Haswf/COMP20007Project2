//
// Created by Has on 14/05/2019.
//

#include "max_heap.h"

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int parent(int i){
    return (i/2);
}
int left_child(int i){
    return 2*i;
}

int right_child(int i){
    return 2*i+1;
}

int readInputToArray(int** output){
    int size;
    scanf("%d", &size);
    *output = (int*)malloc(sizeof(int)*size+1);
    int i;
    for (i=1;i<=size;i++){
        scanf("%d", &(*output)[i]);
    }
    return size;
}

int* build_heap(int* array, int size){
    int last = size;
    int i;
    for (i=parent(last-1);i>0;i--){
        heapify(array, size, i);
    }
    return array;
}

void heapify(int* heap, int size, int i){
    if (i>size){
        return;
    }
    int left = left_child(i);
    int right = right_child(i);
    int max = i;
    if (left <= size && heap[left]>heap[max]){
        max = left;
    }
    if (right <= size && heap[right]>heap[max]){
        max = right;
    }
    if (max!=i){
        swap(&heap[max], &heap[i]);
        heapify(heap, size, max);
    }
}

void buildHeap(int* array, int size){
    int height = log2(size+1);
    int m = pow(2, height-1);
    while (m>0){
        int p;
        for (p=m;p<=2*m-1;p++){
            siftdown(array, size, p);
        }
        m = parent(m);
    }
}


void siftdown(int* heap, int size, int p){
    while (left_child(p)<=size && (heap[p] < heap[left_child(p)] || heap[p] < heap[right_child(p)])){
        int left = left_child(p);
        int right = right_child(p);
        int max = p;
        if (heap[left]>heap[max]){
            max = left;
        }
        if (heap[right]>heap[max]){
            max = right;
        }
        swap(&heap[max], &heap[p]);
        p = max;
    }
}
