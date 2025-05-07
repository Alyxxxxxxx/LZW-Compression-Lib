#include "LZWCompression.h"

void compressLZW(char *inputFile) {
    FileManagement* inputObject = createFileManagement(inputFile);
    
    if (!openFile(inputObject, "rb")) {
        printf("Error al abrir el archivo de entrada.\n");
        deleteFileManagement(inputObject);
        return;
    }
    
    FileManagement *outputObject = createFileManagement("compressed.lzw");
    
    if (!openFile(outputObject, "wb")) {
        printf("Error al abrir el archivo de salida.\n");
        deleteFileManagement(inputObject);
        deleteFileManagement(outputObject);
        return;
    }
    
    RadixTree* tree = createRadixTree();
    initializeDictionary(tree);
    
    unsigned char p[2];
    p[0] = fgetc(getFile(inputObject));
    p[1] = '\0';
    
    RadixNode* pNode = searchPattern(getTreeRoot(tree), (unsigned char*) p);
    unsigned char c[5];
    
     while (!feof(getFile(inputObject))) {
        c[0] = getc(getFile(inputObject)); 
        c[1] = '\0';
        
        if (c[0]==0) {
           c[0] = 'c';
           c[1] = 'e';
           c[2] = 'r';
           c[3] = 'o';
           c[4] = '\0';
       }
        
        RadixNode* combinedNodes = searchPattern(pNode, (unsigned char*) c);
 
        if (combinedNodes != NULL) {
          pNode = combinedNodes;
        }
        
        else {
            
            if (!isRadixTreeFull(tree)) {
            	insertPattern(tree, pNode, (unsigned char*) c);
            }
            
            writeByte(getPatternCode(pNode), outputObject);
            
            if (isRadixTreeFull(tree)) {
                resetRadixTree(tree);
                initializeDictionary(tree);
            }
            
            printf("c es ... %s\n", c);
            pNode = searchPattern(getTreeRoot(tree), (unsigned char*) c);
        } 

     }
     

     getBufferByte(outputObject);
     deleteFileManagement(inputObject);
     deleteFileManagement(outputObject);
     freeTree(tree);
}


void initializeDictionary(RadixTree *tree) {

    for (unsigned int patternCode = 0;  patternCode < 256; patternCode++) {
    
        if (patternCode == 0) {
          unsigned char pattern[5] = {'c', 'e', 'r', 'o', '\0'};
          insertAlphabet(tree, (unsigned char*)pattern);
        }
        
        else {
          unsigned char pattern[2] = {(unsigned char)patternCode, '\0' };
          insertAlphabet(tree, (unsigned char*)pattern);
        }
        
        
    }
}
