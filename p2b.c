//
// Created by Has on 18/05/2019.
//

#include "p2b.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF INT_MAX
#define NO_PREV -1

int min(int i, int j){
    if (i > j){
        return j;
    }
    else {
        return i;
    }
}
// A naive recursive function to count walks from u to v with k edges
int shortestPath(int **graph, int u, int v, int k, int vertexCount){
    // Table to be filled up using DP. The value sp[i][j][e] will store
    // weight of the shortest path from i to j with exactly k edges
    int shortestPAth[vertexCount][vertexCount][k+1];
    int previous[vertexCount][vertexCount][k+1];

    // Loop for number of edges from 0 to
    for (int edge = 0; edge <= k; edge++){
        for (int from = 0; from < vertexCount; from++){
            for (int to = 0; to < vertexCount; to++){
                // initialize value
                shortestPAth[from][to][edge] = INF;
                previous[from][to][edge]= NO_PREV;
                // from base cases
                if (edge == 0 && from == to)
                    shortestPAth[from][to][edge] = 0;
                if (edge == 1 && graph[from][to] != INF)
                    shortestPAth[from][to][edge] = graph[from][to];

                //go to adjacent only when number of edges is more than 1
                if (edge > 1){
                    for (int step = 0; step < vertexCount; step++){
                        // There should be an edge from i to a and a
                        // should not be same as either i or j
                        if (graph[from][step] != INF && from != step && to!= step && shortestPAth[step][to][edge-1] != INF) {
                            //printf("Edge: %d, from %d to %d via %d \n", edge, from, to, step);
                            if (shortestPAth[from][to][edge] > graph[from][step] + shortestPAth[step][to][edge - 1]){
                                previous[from][to][edge] = step;
                            }
                            shortestPAth[from][to][edge] = min(shortestPAth[from][to][edge], graph[from][step] + shortestPAth[step][to][edge - 1]);
                        }
                    }
                }
            }
        }
    }
    int path[vertexCount];
    int count = 0;
    path[count++] = v;
    int prev = previous[u][v][k];
    while (prev > 0){
        int from;
        for (from=0; from<vertexCount;from++){
            if (previous[from][prev][k]){
                path[count++] = prev;
                prev = from;
                break;
            }
        }
    }
    printf("%d\n", shortestPAth[u][v][k]);
    printf("%d\n", count);
    path[count++] = u;
    for (int i=count-1; i>=0; i--){
        printf("%d\n", path[i]);
    }
    return shortestPAth[u][v][k];
}

// driver program to test above function
int main(){
    /* Let us create the graph shown in above diagram*/
    int vertexCount, start, end, k;

    scanf("%d %d", &vertexCount, &k);
    int** matrix = (int**)malloc(sizeof(int*)*vertexCount);

    int i;
    for (i=0;i<vertexCount;i++) {
        matrix[i] = (int *) malloc(sizeof(int) * vertexCount);
        int z;
        for (z = 0; z < vertexCount; z++) {
            matrix[i][z] = INF;
        }

        int out_degree = 0;
        scanf("%d", &out_degree);
        int j;
        int end, weight;

        for (j = 0; j < out_degree; j++) {
            scanf("%d %d", &end, &weight);
            matrix[i][end] = weight;
        }
    }
    start =0;
    end = vertexCount - 1;
    shortestPath(matrix, start, end, k, vertexCount);
    return 0;
}

void printPrev(int*** previous, int from, int to, int max_edge){
    int i=0;
    for (i=0;i<=max_edge;i++){
        printf("%d, ", previous[from][to][i]);
    }
}