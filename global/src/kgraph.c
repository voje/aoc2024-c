#include "kgraph.h"
#include <stdio.h>
#include <stdlib.h>

DGraph* newDGraph(size_t maxVertices) {
    DGraph* dg = malloc(sizeof(DGraph));
    dg->vertices = malloc(sizeof(Vertex*) * maxVertices);
    dg->verticesLen = 0;
    return dg;
}

void printDGraph(DGraph* dg) {
    for (size_t i=0; i<dg->verticesLen; i++) {
        printf("%d ", dg->vertices[i]->value);
    }
    printf("\n");
}

void freeDGraph(DGraph* dg) {
    for (size_t i=0; i<dg->verticesLen; i++) {
        freeVertex(dg->vertices[i]);
    }
    free(dg->vertices);
    free(dg);
}

Vertex* newVertex(int value, size_t maxEdges) {
    Vertex* v = malloc(sizeof(Vertex));
    v->value = value;
    v->ielen = 0;
    v->ie = malloc(sizeof(Vertex*) * maxEdges);
    v->oelen = 0;
    v->oe = malloc(sizeof(Vertex*) * maxEdges);
    return v;
}

void freeVertex(Vertex* v) {
    free(v->oe);
    free(v->ie);
    free(v);
}

void addVertex(DGraph* dg, Vertex* ver) {
    dg->vertices[dg->verticesLen] = ver;
    dg->verticesLen++;
}

Vertex* findVertex(DGraph* dg, int value) {
    for (size_t i=0; i<dg->verticesLen; i++) {
        if (dg->vertices[i]->value == value) {
            return dg->vertices[i];
        }
    }
    return NULL;
}

void removeVertex(DGraph* dg, Vertex* ver) {
    // Edge case for last element in array;
    if (dg->verticesLen > 0 && dg->vertices[dg->verticesLen-1] == ver) {
        dg->vertices[dg->verticesLen-1] = NULL;
    };

    int removing = 0;
    for (size_t i=0; i<dg->verticesLen-1; i++) {
        if (dg->vertices[i] == ver) {
            removing = 1;
        }
        if (removing) {
            // Slide elements to the left
            dg->vertices[i] = dg->vertices[i+1];
        }
    }
    if (removing) {
        dg->verticesLen--;
    }
}












