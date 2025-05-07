#ifndef _BYTE_MANAGEMENT_H
#define _BYTE_MANAGEMENT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BitField.h"
#include "FileManagement.h"

#define PATTERN_CODE_LENGTH 12
#define BYTE 8

void writeByte(BitField patternCode, FileManagement *fileHandler);
void convertDecimalToBinary(BitField decimal,  unsigned char* binaryArray);
void clearArray(unsigned char *array, uint8_t size);
void getBufferByte(FileManagement* fileHandler);
uint8_t binaryToUint(unsigned char* binaryNumber);
void getBufferByte();

#endif // BYTE_MANAGEMENT_H