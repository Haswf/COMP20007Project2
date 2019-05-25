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

#include "graph.h"
#include "priorityqueue.h"

#define NO_PREV -1
#define INFINITY -1
#define INF INT_MAX
int readToMatrix(int*** matrix, int* k, char question);
int shortestPath(int **graph, int u, int v, int k, int vertexCount);
int min(int i, int j);
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

void dijkstras(Graph *graph, int source);

/* TODO: Implement your solution to Problem 2.a. in this function. */
void problem_2_a() {
    Graph* dag = new_graph();
    readGraph(dag);
    //displayGraph(dag);
    dijkstras(dag, 0);
    free_graph(dag);
    dag = NULL;
}

void dijkstras(Graph *graph, int source) {
    int MAX_NODES = graph->size;
    PriorityQueue *queue = new_priority_queue();
    int i, degree, from, to, weight, new_cost;
    bool in_queue;

    // To store results from graph_get_neighbours
    int neighbours[MAX_NODES];
    int weights[MAX_NODES];

    // To store current min-costs and previous vertices
    int previous[MAX_NODES];
    int cost[MAX_NODES];

    for (i = 0; i < graph_num_vertices(graph); i++) {
        previous[i] = NO_PREV;
        cost[i] = INFINITY;
    }

    cost[source] = 0;
    priority_queue_insert(queue, source, cost[source]);

    while (!priority_queue_is_empty(queue)) {
        from = priority_queue_remove_min(queue);
        degree = graph_get_neighbours(graph, from, neighbours, weights, MAX_NODES);
        for (i = 0; i < degree; i++) {
            to = neighbours[i];
            weight = weights[i];

            if (cost[to] == INFINITY || cost[to] > cost[from] + weight) {
                new_cost = cost[from] + weight;
                if (cost[to] == INFINITY) { // to is not in the priority queueu
                    priority_queue_insert(queue, to, new_cost);
                } else { // we must update the cost
                    in_queue = priority_queue_update(queue, to, new_cost);
                    assert(in_queue); // confirm that this node was in fact in the queue
                }

                cost[to] = new_cost;
                previous[to] = from;
            }
        }
    }
    if (cost[MAX_NODES-1] == INFINITY){
        printf("No Path");
    }
    else {
        int prev = previous[MAX_NODES-1];
        int path[MAX_NODES];
        int count = 0;
        path[count] = MAX_NODES-1;
        while (prev >= 0){
            count += 1;
            path[count] = prev;
            prev = previous[prev];
        }

        printf("%d\n", cost[MAX_NODES-1]);
        printf("%d\n", count);
        int p=0;
        for (p=count;p>=0;p--){
            printf("%d\n", path[p]);
        }
    }
    free(queue);
    queue = NULL;
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

int min(int i, int j){
    if (i > j){
        return j;
    }
    else {
        return i;
    }
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
    int prev_node = vertexCount-1;
    int min = INF;
    int shortest_edge = NO_PREV;
    int i;
    int path[k+1];
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
    if (shortestPath[u][v][k] == INF){
        printf("No Path");
    }
    else{
        printf("%d\n", shortestPath[u][v][k]);
        printf("%d\n", k);

        int j;
        for (j=0;j<=k;j++){
            printf("%d\n", path[j]);
        }
    }
    return shortestPath[u][v][k];
}