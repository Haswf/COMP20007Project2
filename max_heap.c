//
// Created by Has on 14/05/2019.
//

#include "max_heap.h"

int swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int parent(int i){
    return (i/2);
}
int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i+1;
}

heap* readInputToHeap(){
    heap* h = (heap*)malloc(sizeof(heap));
    h->array = (int*)malloc(sizeof(int)*(h->size+1));
    scanf("%d", &h->size);
    int i = 1;
    for (i;i<=h->size;i++){
        scanf("%d", &h->array[i]);
    }
    return h;
}

int maxChild(heap *h, int p){
    if (h->array[left(p)] > h->array[right(p)]){
        return left(p);
    }
    else {
        return right(p);
    }
}

int siftdown(heap* h, int n, int p){
    while (2*p <= (n-1) && (h->array[p] < h->array[left(p)] || h[p].array < h->array[right(p)])){
        int t = maxChild(h, p);
        swap(&h->array[p], &h->array[t]);
        p = t;
    }
}

