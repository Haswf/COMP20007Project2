/*
 * Problem 2 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define NO_PREV -1
#define INFINITY INT_MAX
#define INF INT_MAX
void bellmanFord(int** matrix, int source, int vertexCount);

int readToMatrix(int*** matrix, int* k, char question);
int shortestPath(int **graph, int u, int v, int k, int vertexCount);
/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_2_a();
void problem_2_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_2_a(),
   * run problem_2_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_2_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_2_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 2.a. in this function. */
void problem_2_a() {
    int vertexCount, k;
    int** matrix = NULL;
    vertexCount = readToMatrix(&matrix, &k, 'a');
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


/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {
    /* Let us create the graph shown in above diagram*/
    int vertexCount, start, end, k;
    int** matrix = NULL;
    vertexCount = readToMatrix(&matrix, &k, 'b');
    start =0;
    end = vertexCount - 1;
    shortestPath(matrix, start, end, k, vertexCount);
    free(matrix);
    matrix = NULL;
}

// Read graph and store as a adjacency matrix.
int readToMatrix(int*** matrix, int* k, char question) {
    int vertexCount = 0;
    if (question == 'a') {
        scanf("%d", &vertexCount);
    } else if (question == 'b') {
        scanf("%d %d", &vertexCount, k); // read vertex number and maximum edge allowed.
    }
    *matrix = (int **) malloc(sizeof(int *) * vertexCount);

    int i;
    // for each vertex, save its edges
    for (i = 0; i < vertexCount; i++) {
        (*matrix)[i] = (int *) malloc(sizeof(int) * vertexCount);
        // initialise this "row" to infinity
        int z;
        for (z = 0; z < vertexCount; z++) {
            (*matrix)[i][z] = INF;
        }

        // read out_degree
        int out_degree = 0;
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
                shortestPath[from][to][edge] = INFINITY;
                previous[from][to][edge] = NO_PREV;
                // from base cases
                if (edge == 0 && from == to) {
                    shortestPath[from][to][edge] = 0;
                    previous[from][to][edge] = from;
                }
                // if from and to are directly connected
                if (edge == 1 && graph[from][to] != INFINITY) {
                    shortestPath[from][to][edge] = graph[from][to];
                    previous[from][to][edge] = from;
                }

                //go to adjacent only when number of edges is more than 1
                if (edge > 1) {
                    for (int step = 0; step < vertexCount; step++) {
                        // There should be an edge from i to a and a
                        // should not be same as either i or j
                        if (graph[from][step] != INFINITY && from != step && to != step &&
                            shortestPath[step][to][edge - 1] != INFINITY) {
                            // update new cost and previous point
                            if (shortestPath[from][to][edge] > graph[from][step] + shortestPath[step][to][edge - 1]) {
                                shortestPath[from][to][edge] = graph[from][step] + shortestPath[step][to][edge - 1];
                                previous[from][to][edge] = previous[step][to][edge - 1];
                            }
                        }
                    }
                }
            }
        }
    }
    int minCost = INFINITY;
    int shortest_edge = NO_PREV;
    int i;

    // find edge that has minimum cost
    for (i = 0; i <= k; i++) {
        int path_length = shortestPath[u][v][i];
        if (path_length < minCost) {
            minCost = path_length;
            shortest_edge = i;
        }
    }

    int path[k+1]; // To store path. A path with k edges can have at most k+1 point.
    int count = k;
    int prev_node = vertexCount-1;
    // Keep saving points to path until start is reached
    while (prev_node > u) {
        path[count--] = prev_node;
        prev_node = previous[u][prev_node][shortest_edge];
        shortest_edge--;
    }

    // Print No path is v is reachable from u via k edges
    if (shortestPath[u][v][k] == INFINITY){
        printf("No Path");
    }
    // print output
    else{
        printf("%d\n", shortestPath[u][v][k]);
        printf("%d\n", k);
        // print path
        int j;
        for (j=0;j<=k;j++){
            printf("%d\n", path[j]);
        }
    }
    return shortestPath[u][v][k];
}