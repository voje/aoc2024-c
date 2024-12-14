#include "klist.h"
#include <stdio.h>
#include <string.h>

enum {
  RULES,
  PAGES,
};

int nodesAreOrdered(Node *n1, Node *n2) {
    while (n1 != NULL) {
        if (n1 == n2) { return 1; }
        n1 = n1->next;
    }
    return 0;
};

void insertRule(LinkedList *ll, int left, int right) {
  Node *nl = FindNode(ll, left);
  Node *nr = FindNode(ll, right);

  if (nl == NULL && nr == NULL) {
    AppendCreateNode(ll, left);
    AppendCreateNode(ll, right);
  } else if (nl == NULL && nr != NULL) {
    // Create and prepend to right node
    nl = NewNode(left);
    nl->prev = nr->prev;
    nl->next = nr;

    if (nr->prev) {
      nr->prev->next = nl;
    }
    nr->prev = nl;
  } else if (nl != NULL && nr == NULL) {
    // Create and append to left
    nr = NewNode(right);
    nr->prev = nl;
    nr->next = nl->next;

    if (nl->next) {
      nl->next->prev = nr;
    }
    nl->next = nr;
  } else if (nl != NULL && nr != NULL) {
    if (nodesAreOrdered(nl, nr)) {
        printf("Nodes already ordered\n");
    } else {
        printf("Reordering...\n");
    }
    PrintList(ll);
  } else {
    printf("Should not be here");
  }
}

// Parse first half of input, returl a linked list with sorted pages
int parseInputFile(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    printf("Error reading file");
    return 1;
  }

  LinkedList *rules = NewLinkedList();

  char line[256];
  int left, right;
  int parsing = RULES;
  while (fgets(line, sizeof(line), f)) {
    if (strlen(line) == 1) {
      parsing = PAGES;
      continue;
    }
    if (parsing == RULES) {
      sscanf(line, "%d|%d\n", &left, &right);
      printf("rule: %d, %d\n", left, right);
      insertRule(rules, left, right);
    } else if (parsing == PAGES) {
      // printf("pages: %s", line);
      char *token;
      token = strtok(line, ",");
      while (token != NULL) {
        // printf("%s\n", token);
        token = strtok(NULL, ",");
      }
    }
  }

  PrintList(rules);
  FreeLinkedList(rules);
  fclose(f);
  return 0;
}

int main() {
  parseInputFile("./examples/exampleA.txt");
  return 0;
}
