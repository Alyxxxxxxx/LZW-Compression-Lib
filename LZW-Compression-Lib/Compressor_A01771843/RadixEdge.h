#ifndef _RADIX_EDGE_H
#define _RADIX_EDGE_H

typedef struct RadixEdge RadixEdge;

#include "RadixNode.h"

struct RadixEdge {
  unsigned char* pattern;
  RadixNode* nextNode;
};

RadixEdge* createRadixEdge(unsigned char *pattern, RadixNode* nextNode);
void addRadixEdge(RadixNode *node, unsigned char *pattern, RadixNode *next);

#endif // _RADIX_EDGE_H
