#ifndef _KLIST_H_
#define _KLIST_H_

typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail; 
} LinkedList;

LinkedList *NewLinkedList();

Node* NewNode(int value);

void FreeLinkedList(LinkedList *ll);

Node* FindNode(LinkedList *ll, int value);

void DeleteNode(LinkedList *ll, Node *node);

Node* AppendCreateNode(LinkedList *ll, int value);

void PrintList(LinkedList *ll);

#endif

