/* * * * * * *
 * Module for creating and manipulating undirected graphs
 *
 * template created for COMP20007 Design of Algorithms 2019
 * by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#include "list.h"

struct graph {
    List **vertices; // Array of adjacency Lists
    List **weights; // Array of weight Lists
    int size; // Number of vertices in the array
    int capacity; // Max number of vertices the current array can hold
};

typedef struct graph Graph;

// Creates a new empty graph
Graph *new_graph();

// Frees the memory associated with a graph
void free_graph(Graph *graph);

// Creates a new vertex in the graph.
// The new vertex will be given an index and this will be returned.
int graph_add_vertex(Graph *graph);

// Creates an edge between two vertices in the graph.
// Edges are bidirectional in an undirected graph.
// u and v should be the index of the vertices
// w is the weight of the edge
void graph_add_edge(Graph *graph, int u, int v, int w);

// Returns whether or not the vertices u and v are adjacent in the
// graph.
bool graph_are_adjacent(Graph *graph, int u, int v);

// Saves the indices of u's neighbours in the neighbours array and returns
// the number of neighbours stored.
// Stores the weights in the weights array.
// Gives an error if the size of the array provided (n) is less than the number
// of vertices.
int graph_get_neighbours(Graph *graph, int u, int *neighbours, int *weights, int n);

// Get the number of vertices in the graph
int graph_num_vertices(Graph *graph);

void displayGraph(Graph* graph);

int readGraph(Graph* graph);
#endif
