/* * * * * * *
 * Module for creating and manipulating directed graphs
 *
 * template created for COMP20007 Design of Algorithms 2019
 * by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * modified by Shuyang Fan for COMP20007 Project 2.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


#define INITIAL_CAPACITY 4

// Creates a new empty graph
Graph *new_graph() {
  Graph *graph = malloc(sizeof(*graph));
  assert(graph);

  // Create space for the (List *) pointers which will be used as
  // adjacency lists
  graph->vertices = malloc(sizeof(List *) * INITIAL_CAPACITY);
  assert(graph->vertices);
  graph->weights = malloc(sizeof(List *) * INITIAL_CAPACITY);
  assert(graph->weights);

  // Graph is initially empty
  graph->size = 0;
  graph->capacity = INITIAL_CAPACITY;

  return graph;
}

// Frees the memory associated with a graph
void free_graph(Graph *graph) {
  int i;

  // Free each of the Lists
  for (i = 0; i < graph->size; i++) {
    free_list(graph->vertices[i]);
    graph->vertices[i] = NULL;
    free_list(graph->weights[i]);
    graph->weights[i] = NULL;
  }

  // Free the array of (List *) pointers
  free(graph->vertices);
  free(graph->weights);

  // Free the actual graph struct
  free(graph);
}

// Creates a new vertex in the graph.
// The new vertex will be given an index and this will be returned.
int graph_add_vertex(Graph *graph) {
  assert(graph != NULL);

  if (graph->size == graph->capacity) {
    graph->capacity *= 2;
    graph->vertices = realloc(graph->vertices,
                              sizeof(List *) * graph->capacity);
    assert(graph->vertices);
    graph->weights = realloc(graph->weights,
                             sizeof(List *) * graph->capacity);
    assert(graph->weights);
  }

  int next_vertex = graph->size;
  graph->vertices[next_vertex] = new_list();
  graph->weights[next_vertex] = new_list();

  graph->size++;

  return next_vertex;
}

// Creates an edge between two vertices in the graph.
// Edges are directional in a directed graph.
// u and v should be the index of the vertices
// w is the weight of the edge
void graph_add_edge(Graph *graph, int u, int v, int w) {
  assert(graph != NULL);
  // Assert that u and v are valid indices
  assert(u >= 0 && u < graph->size);
  assert(v >= 0 && v < graph->size);

  if (w < 0) {
    fprintf(stderr, "Error: negative edge weights not supported\n");
    exit(EXIT_FAILURE);
  }

  if (graph_are_adjacent(graph, u, v)) {
    // Can't add an edge that already exists
    fprintf(stderr, "Error: edge already exists between %d and %d\n", u, v);
    exit(EXIT_FAILURE);
  }

  // Add u to v's adjacency list
  list_add_end(graph->vertices[u], v);
  list_add_end(graph->weights[u], w);
}

// Returns whether or not the vertices u and v are adjacent in the
// graph.
bool graph_are_adjacent(Graph *graph, int u, int v) {
  // Check if v is in list of u
  List *u_neighbours = graph->vertices[u];
  return list_contains(u_neighbours, v);

}

// Saves the indices of u's neighbours in the neighbours array and returns
// the number of neighbours stored.
// Stores the weights in the weights array.
// Gives an error if the size of the array provided (n) is less than the number
// of vertices.
int graph_get_neighbours(Graph *graph, int u, int *neighbours, int *weights, int n) {
  assert(graph != NULL);
  assert(neighbours != NULL);

  List *adjacentcy_list = graph->vertices[u];
  List *weights_list = graph->weights[u];

  // There's only room for n vertex indices in the array neighbours, so if
  // u has more neighbours than this then print an error
  if (list_size(adjacentcy_list) > n) {
    fprintf(stderr,
      "Error: graph_get_neighbours() not provided with a big enough array\n");
    exit(EXIT_FAILURE);
  }

  // Note: We added the ListIterator type for this purpose
  ListIterator *neighbout_iterator = new_list_iterator(adjacentcy_list);
  int i = 0;
  while (list_iterator_has_next(neighbout_iterator)) {
    neighbours[i] = list_iterator_next(neighbout_iterator);
    i++;
  }

  // Now iterate through the weights
  ListIterator *weights_iterator = new_list_iterator(weights_list);
  int j = 0;
  while (list_iterator_has_next(weights_iterator)) {
    weights[j] = list_iterator_next(weights_iterator);
    j++;
  }

  // After the loop, i will store the number of neighbours
  // So should j, so we'll assert that they're equal
  assert(i == j);
  return i;
}

// Get the number of vertices in the graph
int graph_num_vertices(Graph *graph) {
  return graph->size;
}

int readGraph(Graph* graph){
    int vertexCount;
    scanf("%d", &vertexCount);

    int e;
    for (e=0;e<vertexCount;e++){
        graph_add_vertex(graph);
    }

    int i;
    for (i=0;i<vertexCount;i++){
        int out_degree = 0;
        scanf("%d", &out_degree);
        int j;
        int end, weight;
        for (j=0;j<out_degree;j++){
            scanf("%d %d", &end, &weight);
            graph_add_edge(graph, i, end, weight);
        }
    }
    return vertexCount;
}

void displayGraph(Graph* graph)
{
    int i;
    for (i = 0; i < graph_num_vertices(graph); i++)
    {
        printf("%d: ", i);
        int neighbors[50];
        int weights[50];
        int neighborCount = graph_get_neighbours(graph, i, neighbors, weights, 50);
        int j;
        for (j=0;j<neighborCount;j++){
            printf("%d(%d) | ", neighbors[j], weights[j]);
        }
        printf("\n");
    }
}
