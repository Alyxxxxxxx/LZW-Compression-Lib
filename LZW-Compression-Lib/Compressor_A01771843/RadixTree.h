#ifndef _RADIX_TREE_H
#define _RADIX_TREE_H

typedef struct RadixTree RadixTree;

#include "RadixNode.h"
#define DICT_MAX_SIZE 12

RadixTree* createRadixTree();
void insertAlphabet(RadixTree* tree, unsigned char* pattern);
RadixNode* insertPattern(RadixTree* tree, RadixNode* node, unsigned char* pattern);
RadixNode* insertPatternWrapper(RadixNode* currentNode, unsigned char* pattern, int *currentIndex, BitField patternCode);
RadixNode* searchPattern(RadixNode* node, unsigned char* pattern);
RadixNode* getTreeRoot(RadixTree* tree);
void freeRadixTree(RadixNode* root);
int findFirstMismatch(unsigned char* pattern, unsigned char* text);
void deleteNodes(RadixNode *node);
void freeTree(RadixTree *tree);
void resetRadixTree(RadixTree* tree);

BitField createPatternCode(RadixTree* tree, unsigned char* pattern, bool isAlphabet);
BitField getPatternCode(RadixNode* node);
bool isRadixTreeFull(RadixTree* tree);

bool determineValidPatternCode(unsigned int newPatternCode, unsigned int possibleBits);

#endif // _RADIX_TREE_H
