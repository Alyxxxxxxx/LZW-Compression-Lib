#ifndef _LZW_COMPRESSION_H
#define _LZW_COMPRESSION_H

#include "RadixTree.h"
#include "ByteManagement.h"

void compressLZW(char *inputname);
void initializeDictionary(RadixTree *tree);

#endif // LZW_COMPRESSION_H

