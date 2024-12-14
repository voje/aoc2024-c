#ifndef _KGRAPH_H_
#define _KGRAPH_H_

#include <stddef.h>

typedef struct Vertex {
    int value;
    size_t oelen;
    // out Edges
    struct Vertex** oe;
    // in Edges
    size_t ielen;
    struct Vertex** ie;
} Vertex;

// DGraph is a Directed that holds int values
typedef struct DGraph {
    Vertex** vertices;
    size_t verticesLen;
} DGraph;

DGraph* newDGraph(size_t maxVertices);
void freeDGraph(DGraph*);
void printDGraph(DGraph*);

Vertex* newVertex(int value, size_t maxEdges);
void freeVertex(Vertex*);

void addVertex(DGraph* dg, Vertex* ver);

Vertex* findVertex(DGraph* dg, int value);

void removeVertex(DGraph* dg, Vertex* ver);
void removeEdge(Vertex* from, Vertex* to);

#endif
