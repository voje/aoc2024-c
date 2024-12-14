// Linked list
#include "klist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* NewLinkedList() {
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

Node* NewNode(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void FreeLinkedList(LinkedList *ll) {
    if (ll == NULL) { return; }
    Node *node = ll->head;
    while (node != NULL) {
        Node *tmp = node;
        node = node->next;
        free(tmp);
    }
    free(ll);
}

Node* FindNode(LinkedList *ll, int nodeValue) {
    Node *node = ll->head;
    while (node != NULL) {
        if (node->value == nodeValue) { return node; }
        node = node->next;
    }
    return NULL;
}

void DeleteNode(LinkedList *ll, Node *node) {
    if (ll->head == node) {
        ll->head = node->next;
    }
    if (ll->tail == node) {
        ll->tail = node->prev;
    }

    if (node->next != NULL) { node->next->prev = node->prev; }
    if (node->prev != NULL) { node->prev->next = node->next; }

    free(node);
}

Node* AppendCreateNode(LinkedList *ll, int nodeValue) {
    Node* node = NewNode(nodeValue);
    node->prev = ll->tail;
    if (ll->tail == NULL) {
        ll->tail = node;
        ll->head = node;
    } else {
        ll->tail->next = node;
        ll->tail = node;
    }
    return node;
}

void PrintList(LinkedList *ll) {
    Node *node = ll->head;
    while (node != NULL) {
        printf("%d - ", node->value);
        node = node->next;
    }
    printf("\n");
}
