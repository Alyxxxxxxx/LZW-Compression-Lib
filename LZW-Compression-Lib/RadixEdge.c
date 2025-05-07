#include "RadixEdge.h"

RadixEdge* createRadixEdge(unsigned char *pattern, RadixNode* nextNode) {
  RadixEdge* edge = malloc(sizeof(RadixEdge));
  edge->pattern = (unsigned char*)strdup((const char*)pattern);
  edge->nextNode = nextNode;
  return edge;
}

void addRadixEdge(RadixNode *node, unsigned char *pattern, RadixNode *next) {
    node->edges = realloc(node->edges, sizeof(RadixEdge *) * (node->numEdges + 1));
    RadixEdge *newEdge = createRadixEdge(pattern, next);
    node->edges[node->numEdges++] = newEdge;
}
