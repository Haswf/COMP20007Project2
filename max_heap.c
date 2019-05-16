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

int readInputToArray(int** output) {
    int size;
    scanf("%d", &size);
    *output = (int *) malloc(sizeof(int) * size + 1);
    int i;
    for (i = 1; i <= size; i++) {
        scanf("%d", &(*output)[i]);
    }
    return size;
}
void buildRightHandedHeap(int* array, int size) {
    buildHeap(array, size);
    int height = log2(size + 1);
    int m = 1;
    while (m<=(int)pow(2,height)){
        int p;
        for (p=m;p>=(m+1)/2 && left_child(p) < size;p--){
            if (array[left_child(p)] > array[right_child(p)]){
                swap(&array[left_child(p)], &array[right_child(p)]);
                siftdown(array, size, left_child(p));
            }
        }
        m = 2*m + 1;
    }
 //       printf("i: %d", (int)pow(2,i)-1);
//        int p = (int)pow(2,i)-1;
  //      for (p; p > pow(2,height-1); p--) {
  //          printf("p: %d", p);
  //      }
            //      siftdown(array, size, p);
 //   }
    //int m = pow(2, height - 1);
    //while (m < size) {
     //   int p = 0;
     //   for (p = m; p <= 2 * m - 1; p++) {
      //      siftdown(array, size, p);
       // }
   // }
}



void buildHeap(int* array, int size){
    int height = log2(size+1);
    int m = pow(2, height-1);
    while (m>0) {
        int p;
        for (p = m; p <= 2 * m - 1; p++) {
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

void removeMax(int* heap, int* size){
    heap[1] = heap[*size];
    siftdown(heap, *size, 1);
    *size -= 1;
}