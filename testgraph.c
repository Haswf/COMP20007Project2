//
// Created by Has on 15/05/2019.
//
#include "graph.h"
#include <stdio.h>
#include <limits.h>
#include "priorityqueue.h"
#include <assert.h>

#define NO_PREV -1
#define INFINITY -1

void dijkstras(Graph *graph, int source);


int main(int argc, char* argv[]){
    Graph* dag = new_graph();
    readGraph(dag);
    displayGraph(dag);
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