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
int shortestPath(int **graph, int u, int v, int k, int vertexCount) {
    // Table to be filled up using DP. The value sp[i][j][e] will store
    // weight of the shortest path from i to j with exactly k edges
    int shortestPath[vertexCount][vertexCount][k + 1];
    int previous[vertexCount][vertexCount][k + 1];

    // Loop for number of edges from 0 to
    for (int edge = 0; edge <= k; edge++) {
        for (int from = 0; from < vertexCount; from++) {
            for (int to = 0; to < vertexCount; to++) {
                // initialize value
                shortestPath[from][to][edge] = INF;
                previous[from][to][edge] = NO_PREV;
                // from base cases
                if (edge == 0 && from == to) {
                    shortestPath[from][to][edge] = 0;
                    previous[from][to][edge] = from;
                }

                if (edge == 1 && graph[from][to] != INF) {
                    shortestPath[from][to][edge] = graph[from][to];
                    previous[from][to][edge] = from;
                }

                //go to adjacent only when number of edges is more than 1
                if (edge > 1) {
                    for (int step = 0; step < vertexCount; step++) {
                        // There should be an edge from i to a and a
                        // should not be same as either i or j
                        if (graph[from][step] != INF && from != step && to != step &&
                            shortestPath[step][to][edge - 1] != INF) {
                            //printf("Edge: %d, from %d to %d via %d \n", edge, from, to, step);
                            if (shortestPath[from][to][edge] > graph[from][step] + shortestPath[step][to][edge - 1]) {
                                previous[from][to][edge] = previous[step][to][edge - 1];
                            }
                            shortestPath[from][to][edge] = min(shortestPath[from][to][edge],
                                                               graph[from][step] + shortestPath[step][to][edge - 1]);
                        }
                    }
                }
            }
        }
    }
    int prev_node = vertexCount - 1;
    int min = INF;
    int shortest_edge = NO_PREV;
    int i;
    int path[k + 1];
    for (i = 0; i <= k; i++) {
        int path_length = shortestPath[u][prev_node][i];
        if (path_length < min) {
            min = path_length;
            shortest_edge = i;
        }
    }
    int count = k;
    while (prev_node > 0) {
        path[count--] = prev_node;
        prev_node = previous[u][prev_node][shortest_edge];
        shortest_edge--;
    }
    if (shortestPath[u][v][k] == INF) {
        printf("No Path");
    } else {
        printf("%d\n", shortestPath[u][v][k]);
        printf("%d\n", k);

        int j;
        for (j = 0; j <= k; j++) {
            printf("%d\n", path[j]);
        }
    }
    return shortestPath[u][v][k];
}

int readToMatrix(int*** matrix, int* k, char question) {
    int vertexCount = 0;
    if (question == 'a') {
        scanf("%d", &vertexCount);
    } else if (question == 'b') {
        scanf("%d %d", &vertexCount, k);
    }
    *matrix = (int **) malloc(sizeof(int *) * vertexCount);

    int i;
    for (i = 0; i < vertexCount; i++) {
        (*matrix)[i] = (int *) malloc(sizeof(int) * vertexCount);
        int z;
        for (z = 0; z < vertexCount; z++) {
            (*matrix)[i][z] = INF;
        }

        int out_degree = 0;
        scanf("%d", &out_degree);
        int j;
        int end, weight;

        for (j = 0; j < out_degree; j++) {
            scanf("%d %d", &end, &weight);
            (*matrix)[i][end] = weight;
        }
    }
    return vertexCount;
}

int main(){
    int vertexCount, start, end, k;
    int** matrix = NULL;
    vertexCount = readToMatrix(&matrix, &k, 'b');
    start =0;
    end = vertexCount - 1;
    shortestPath(matrix, start, end, k, vertexCount);
    free(matrix);
    matrix = NULL;
}