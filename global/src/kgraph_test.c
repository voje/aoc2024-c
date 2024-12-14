#include "kgraph.h"
#include <stdio.h>

const size_t MAXVERTICES = 1000;
const size_t MAXEDGES = 1000;

int main() {
    DGraph* dg = newDGraph(MAXVERTICES);

    int values[] = {39, 11, 25, 34, 19, 44};

    for (size_t i=0; i<(sizeof(values)/sizeof(int)); i++) {
        Vertex* v = newVertex(values[i], MAXEDGES);
        addVertex(dg, v);
    }

    printDGraph(dg);
    Vertex* v = findVertex(dg, 25);
    if (v != NULL) {
        removeVertex(dg, v);
    }
    freeVertex(v);
    printDGraph(dg);

    freeDGraph(dg);
    printf("Pass\n");
    return 0;
}
