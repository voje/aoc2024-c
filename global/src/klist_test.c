#include "klist.h"
#include <stdio.h>

int main() {
    LinkedList *ll = NewLinkedList();

    Node* n0 = AppendCreateNode(ll, 40);
    Node* n1 = AppendCreateNode(ll, 41);
    Node* n2 = AppendCreateNode(ll, 42);
    Node* n3 = AppendCreateNode(ll, 43);

    DeleteNode(ll, FindNode(ll, 42));

    PrintList(ll);
    FreeLinkedList(ll);

    printf("Pass\n");
    return 0;
}
