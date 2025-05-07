#include "RadixNode.h"

RadixNode* createRadixNode(bool isEndOfPattern, BitField patternCode) {
    RadixNode* node = malloc(sizeof(RadixNode));
    node->isEndOfPattern = isEndOfPattern;
    node->patternCode = patternCode;
    node->edges = NULL;
    node->numEdges = 0;
    return node;
}
