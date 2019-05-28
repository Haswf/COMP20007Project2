//
// Created by Has on 28/05/2019.
//

#include "q2a.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define NO_PREV -1
#define INFINITY INT_MAX

void bellmanFord(int** matrix, int source, int vertexCount);
int readToMatrix(int*** matrix);
void problem_2_a();


int main(){
    problem_2_a();
}

void problem_2_a() {
    /* Let us create the graph shown in above diagram*/
    int vertexCount, start, end, k;
    int** matrix = NULL;
    vertexCount = readToMatrix(&matrix);
    int source =0;
    bellmanFord(matrix, source, vertexCount);
    free(matrix);
    matrix = NULL;
}

// Read graph and store as a adjacency matrix.
void bellmanFord(int** matrix, int source, int vertexCount) {
    // To store current min-costs and previous vertices
    int previous[vertexCount];
    int cost[vertexCount];


    // inisitalize distance to all vertex as infinity
    int i;
    for (i = 0; i < vertexCount; i++) {
        previous[i] = NO_PREV;
        cost[i] = INFINITY;
    }
    cost[source] = 0;
    for (int j=0; j<=vertexCount-1;j++){
        for (int from=0; from<vertexCount; from++){
            for (int to=0; to<vertexCount; to++){
                if (matrix[from][to] != INFINITY && cost[from] != INFINITY && cost[from]+matrix[from][to] < cost[to]){
                    cost[to] = cost[from] + matrix[from][to];
                    previous[to] = from;
                }
            }
        }
    }
    // if last node is unreachable, print 'No Path'
    if (cost[vertexCount-1] == INFINITY){
        printf("No Path");
    }
    else {
        int prev = previous[vertexCount-1];
        int path[vertexCount];
        int count = 0;
        path[count] = vertexCount-1;
        // store path to array path
        while (prev >= 0){
            count += 1;
            path[count] = prev;
            prev = previous[prev];
        }

        printf("%d\n", cost[vertexCount-1]);
        printf("%d\n", count);
        // print path
        int p=0;
        for (p=count;p>=0;p--){
            printf("%d\n", path[p]);
        }
    }
}

int readToMatrix(int*** matrix) {
    int vertexCount = 0;
    scanf("%d", &vertexCount);

    *matrix = (int **) malloc(sizeof(int *) * vertexCount);
    int i;
    // for each vertex, save its edges
    for (i = 0; i < vertexCount; i++) {
        (*matrix)[i] = (int *) malloc(sizeof(int) * vertexCount);
        // initialise this "row" to infinity
        int z;
        for (z = 0; z < vertexCount; z++) {
            (*matrix)[i][z] = INFINITY;
        }

        // read out_degree
        int out_degree;
        scanf("%d", &out_degree);
        int j;
        int end, weight;

        // save w
        for (j = 0; j < out_degree; j++) {
            scanf("%d %d", &end, &weight);
            (*matrix)[i][end] = weight;
        }
    }
    return vertexCount;
}