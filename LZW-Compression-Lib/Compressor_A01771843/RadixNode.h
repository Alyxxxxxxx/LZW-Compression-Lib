#ifndef _RADIX_NODE_H
#define _RADIX_NODE_H

typedef struct RadixNode RadixNode;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BitField.h"
#include "RadixEdge.h"

struct RadixNode {
  BitField patternCode;
  bool isEndOfPattern;
  RadixEdge** edges;
  unsigned int numEdges;
};

RadixNode* createRadixNode(bool inEndOfPattern, BitField patternCode);

#endif // _RADIX_NODE_H
