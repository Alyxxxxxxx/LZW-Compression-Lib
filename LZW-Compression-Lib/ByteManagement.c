#include "ByteManagement.h"

unsigned char bufferArray[BYTE + 1] =  {0};

void convertDecimalToBinary(BitField decimal, unsigned char* binaryArray) {
	int index = PATTERN_CODE_LENGTH - 1;

	for (int i = 0; i < PATTERN_CODE_LENGTH; i++) {
	binaryArray[i] = '0';
	}

	while (decimal.value > 0 && index >= 0) {
	binaryArray[index] = (decimal.value % 2) ? '1' : '0';
	decimal.value = decimal.value / 2;
	index--;
	}

	binaryArray[PATTERN_CODE_LENGTH] = '\0'; 
}

uint8_t binaryToUint(unsigned char* byteArray) {
    uint8_t number = 0;
    
    for (int i = 0; i < BYTE; i++) {
        number = (number << 1) | (byteArray[i] - '0');
    }
    
    return number;
}

void clearArray(unsigned char* array, uint8_t size) {
  for (int i = 0; i < size; i++) {
      array[i] = '\0';
  }
}

void writeByte(BitField patternCode, FileManagement* fileHandler) {    
    unsigned char twelveBitArray[PATTERN_CODE_LENGTH + 1] = {0};
    unsigned char byteArray[BYTE + 1] =  {0};
    int j = 0;
    int k = 0;
    
    convertDecimalToBinary(patternCode, twelveBitArray);
    uint8_t bufferLength = strlen((const char*) bufferArray);
    
    if (bufferLength < BYTE) {

        for (int i = 0; i < bufferLength; i++) {
          byteArray[i] = bufferArray[i];
        }
    
        for (int i = bufferLength; i < BYTE; i++) {
          byteArray[i] = twelveBitArray[j];
          j++;
        }

        clearArray(bufferArray, BYTE);
        
        for (int i = j; i < PATTERN_CODE_LENGTH; i++) {
          bufferArray[k] = twelveBitArray[i];
          k++;
        }
        
        uint8_t finalByte = binaryToUint(byteArray);
         printf("ARRAY: %s\n", byteArray);
         printf("byte %d\n", finalByte);
        writeFile(fileHandler, finalByte);
    }
    
    else{
        
        for (int i = 0; i < bufferLength; i++) {
            byteArray[i] = bufferArray[i];
        }
        
        uint8_t finalByte = binaryToUint(byteArray);
        printf("ARRAYINBUFFER: %s\n", byteArray);
        printf("byte %d\n", finalByte);
        writeFile(fileHandler, finalByte);
        
        for (int i = 0; i < BYTE; i++) {
            byteArray[i] = twelveBitArray[i];
        }
        
        clearArray(bufferArray, BYTE);
    
        for (int i = BYTE; i < PATTERN_CODE_LENGTH; i++) {
          bufferArray[j] = twelveBitArray[i];
          j++;
        }
        
        finalByte = binaryToUint(byteArray);
        printf("ARRAY AFTER BUFFER: %s\n", byteArray);
        printf("byte %d\n", finalByte);
        writeFile(fileHandler, finalByte);
    }
}

void getBufferByte(FileManagement* fileHandler){
    uint8_t bufferLength = strlen((const char*)bufferArray);
    
    if (bufferLength > 0){
        
        for (int i = bufferLength; i < BYTE; i++) {
            bufferArray[i] = '0';
        }
     
    uint8_t finalByte = binaryToUint(bufferArray);
    writeFile(fileHandler, finalByte);
    }
}
