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
}






/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {

}

