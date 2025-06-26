// Implementation of the Graph ADT
// Undirected, unweighted
// Vertices are given by integers between 0 and V - 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

struct graph {
	int nV;
	int nE;
	struct adjNode **edges;
};

struct adjNode {
	Vertex v;
	struct adjNode *next;
};

static bool validVertex(Graph g, Vertex v);

/**
 * Returns a new graph with nV vertices
 */
Graph GraphNew(int nV) {

    Graph g = malloc(sizeof(struct graph));
    g->edges = calloc(nV, sizeof(struct adjNode*));
    g->nV = nV;
    g->nE = 0;
    return g;

}

/**
 * Frees all memory allocated to a graph
 */
void GraphFree(Graph g) {
	for (int i = 0; i < g->nV; i++) {
		struct adjNode *curr = g->edges[i];
		while (curr != NULL) {
			struct adjNode *temp = curr;
			curr = curr->next;
			free(temp);
		}
	}
	free(g->edges);
	free(g);
}

/**
 * Returns the number of vertices in a graph
 */
int GraphNumVertices(Graph g) {
	return g->nV;
}

/**
 * Returns the number of edges in a graph
 */
int GraphNumEdges(Graph g) {
	return g->nE;
}

/**
 * Returns true if there is an edge between v and w,
 * and false otherwise
 */
bool GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    // validate v and w
	assert(validVertex(g, v));
	assert(validVertex(g, w));

    // access vertex v, using loop
    // this edge works like array of linked lists
    struct adjNode *curr = g->edges[v];

    while (curr != NULL) {
        if (curr->v == w) {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

/**
 * Inserts an edge between v and w
 */
void GraphInsertEdge(Graph g, Vertex v, Vertex w) {
    // check if the v,w is valid
	assert(validVertex(g, v));
	assert(validVertex(g, w));

    // check if edge between v and w already exists
    if (GraphIsAdjacent(g, v, w)) return;

    // create new node 
    struct adjNode *newNode1 = malloc(sizeof(struct adjNode));
    newNode1->v = w;
    newNode1->next = g->edges[v];   // the v is the array index (src vertex)
    g->edges[v] = newNode1;         // the w is the dest vertex, which is stored inside the linked list value

    // also, this is undirected graph
    struct adjNode *newNode2 = malloc(sizeof(struct adjNode));
    newNode2->v = v;
    newNode2->next = g->edges[w];
    g->edges[w] = newNode2;         // edge[v] -> [vertex w]

    // Increment edge count
    g->nE++;

}

/**
 * Removes an edge between v and w
 */
void GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
	assert(validVertex(g, v));
	assert(validVertex(g, w));

    // check if there is an edge between v and w
    if (GraphIsAdjacent(g, v, w)) return;

    // use temporary memory to find that edge
    struct adjNode *curr1 = g->edges[v];
    while (curr1->v != w) {
        curr1 = curr1->next;
    }
    g->edges[v] = curr1->next;
    free(curr1);

    // use temporary memory to find that edge
    struct adjNode *curr2 = g->edges[w];
    while (curr1->v != v) {
        curr2 = curr2->next;
    }
    g->edges[w] = curr2->next;
    free(curr2);

}

/**
 * Returns the degree of a vertex
 */
int GraphDegree(Graph g, Vertex v) {
	assert(validVertex(g, v));

	// TODO - this is left as an exercise
	return 0;
}

/**
 * Displays a graph
 */
void GraphShow(Graph g) {
	printf("Number of vertices: %d\n", g->nV);
	printf("Number of edges: %d\n", g->nE);
	printf("Edges:\n");
	for (int i = 0; i < g->nV; i++) {
		printf("%2d:", i);
		for (struct adjNode *curr = g->edges[i]; curr != NULL; curr = curr->next) {
			printf(" %d", curr->v);
		}
		printf("\n");
	}
	printf("\n");
}

static bool validVertex(Graph g, Vertex v) {
	return (v >= 0 && v < g->nV);
}
