#include "RadixTree.h"

struct RadixTree {
    RadixNode* root;
    BitField nextPatternIdentifier;
    bool isFull;
};

RadixTree* createRadixTree() {
    BitField nextPatternIdentifier = {0};
    RadixTree *tree = malloc(sizeof(RadixTree));
    tree -> root = createRadixNode(false, nextPatternIdentifier);
    tree -> nextPatternIdentifier.value = 256;
    tree -> isFull = false;
    return tree;
}

int findFirstMismatch(unsigned char* pattern, unsigned char* word) {
    int length = strlen((const char*)pattern) < strlen((const char*)word) ? strlen((const char*)pattern) : strlen((const char*)word);
  
    for (int i = 0; i < length; i++) {
      if (pattern[i] != word[i]) {
          return i;
      }
    }
    return -1; 
}

RadixNode* insertPatternWrapper(RadixNode* currentNode, unsigned char* pattern, int *currentIndex, BitField patternCode) {

    if (*currentIndex >= strlen((const char*)pattern)) {
        return NULL; 
    }

    unsigned char transitionChar = pattern[*currentIndex];
    RadixEdge *currentEdge = NULL;

    //Revisar si existe un edge en el currentNode cuyo primer caracter coincida con transitionChar
    for (int i = 0; i < currentNode->numEdges && currentEdge == NULL; i++) {
        if (currentNode->edges[i]->pattern[0] == transitionChar) {
            currentEdge = currentNode->edges[i];
        }
    }

    // Asignar un puntero a la subcadena que comienza en currIndex
    unsigned char *currStr = pattern + *currentIndex;

    //para cuando no existe un edge se crea uno nuevo que apunta a un nodo que guarda 
    //toda la palabra nueva como patrón.
    if (currentEdge == NULL) {
        RadixNode *newNode = createRadixNode(true, patternCode);
        addRadixEdge(currentNode, currStr, newNode);
        return newNode;
    }

    int splitIndex = findFirstMismatch(currStr, currentEdge->pattern);
    
    //cuando currStr y el edge son iguales en todos los indices
    //si se inserta una palabra repetida 
    if (splitIndex == -1) {
        if (strlen((const char*)currStr) == strlen((const char*)currentEdge->pattern)) {
            return currentEdge->nextNode;
        }

        //si currStr es un prefijo de currentEdge->label.
        else if (strlen((const char*)currStr) < strlen((const char*)currentEdge->pattern)) {
            unsigned char *suffix = (unsigned char*)strdup((const char*)currentEdge->pattern + strlen((const char*)currStr));
            currentEdge->pattern = (unsigned char*)strdup((const char*)currStr); //representar nuevo prefijo
            RadixNode *newNext = createRadixNode(true, patternCode);
            RadixNode *afterNewNext = currentEdge->nextNode;
            currentEdge->nextNode = newNext; //ahora el edge apunta al nuevo prefijo
            addRadixEdge(newNext, suffix, afterNewNext);
            free(suffix);
            return newNext;
        }

        //la palabra que se desea ingresar es mas grande que a lo que apunta edge
        //se debe crear un nuevo edge que apunte a un nodo que guarde el sufijo restante
        else {
            splitIndex = strlen((const char*)currentEdge->pattern);
        }
    }

    //cuando las currstr y edge son diferentes en algun indice
    else {
        BitField startPattern = {0};
        unsigned char *suffix = (unsigned char*)strdup((const char*)currentEdge->pattern + splitIndex); //tomar patron de edge sin prefijo
        currentEdge->pattern[splitIndex] = '\0'; //cambias el patron asociado solo al prefijo que coincide
        RadixNode *prevNext = currentEdge->nextNode;
        currentEdge->nextNode = createRadixNode(false, startPattern); // Crear un nuevo nodo para el prefijo "he"
        addRadixEdge(currentEdge->nextNode, suffix, prevNext);// Agregar el sufijo como un nuevo borde
        free(suffix);
    }

    currentNode = currentEdge->nextNode;
    *currentIndex += splitIndex;
    
    return insertPatternWrapper(currentNode, pattern, currentIndex, patternCode);
    
}

void insertAlphabet(RadixTree* tree, unsigned char* pattern) {
    RadixNode* node = tree->root;
    int currentIndex = 0;
    BitField patternCode = createPatternCode(tree, pattern, true);
    insertPatternWrapper(node, pattern, &currentIndex, patternCode);
    
}

RadixNode* insertPattern(RadixTree* tree, RadixNode* node, unsigned char* pattern) {
    int currentIndex = 0;
    BitField patternCode = createPatternCode(tree, pattern, false);
    return insertPatternWrapper(node, pattern, &currentIndex, patternCode);
}

RadixNode* searchPattern(RadixNode* node, unsigned char* pattern) {
    int currentIndex = 0;
    while (currentIndex < strlen((const char*)pattern)) {
        unsigned char transitionChar = pattern[currentIndex];
        RadixEdge *currentEdge = NULL;
        
        for (int i = 0; i < node->numEdges && currentEdge == NULL; i++) {
            if (node->edges[i]->pattern[0] == transitionChar) {
                currentEdge = node->edges[i];
                printf("pattern %s\n", currentEdge->pattern);
            }
        }

        if (currentEdge == NULL) {
            return NULL; // No encontrado
        }
        
	size_t edgePatternLength = strlen((const char*)currentEdge->pattern);
	
        if (strncmp((const char*)(pattern + currentIndex), (const char*)currentEdge->pattern, edgePatternLength) != 0) {
            return NULL; // No encontrado
        }
        currentIndex += strlen((const char*)currentEdge->pattern);
        node = currentEdge->nextNode;
    }
    
    return node->isEndOfPattern ? node : NULL; 
}

void deleteNodes(RadixNode* node) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < node->numEdges; i++) {
        free(node->edges[i]->pattern);
        deleteNodes(node->edges[i]->nextNode);
        free(node->edges[i]);
    }
    
    free(node->edges);
    free(node);
}

void freeTree(RadixTree* tree) {
    if (tree == NULL) {
        return;
    }
    
    deleteNodes(tree->root); 
    free(tree); 
}

void resetRadixTree(RadixTree* tree) {
    if (tree == NULL) {
        return;
    }

    deleteNodes(tree->root);
    tree->root = createRadixNode(false, (BitField){0});
    tree->nextPatternIdentifier.value = 256;
    tree->isFull = false; 
}


BitField createPatternCode(RadixTree* tree, unsigned char* pattern, bool isAlphabet) {
    BitField patternCode = {0};
    unsigned int newPatternCode = tree->nextPatternIdentifier.value;
    newPatternCode += 1;
    
    if (isAlphabet) {
    	if (strcmp((const char*)pattern, "cero") == 0) {
    	    patternCode.value = 0;
    	}
    	
    	else {
        patternCode.value = (unsigned int)pattern[0]; 
        }
    } 
        
    else {
        patternCode.value = tree->nextPatternIdentifier.value;
        
        if (determineValidPatternCode(newPatternCode, DICT_MAX_SIZE)) {
           tree->nextPatternIdentifier.value++;
        }
        
        else {
           tree->isFull = true;
        }
    }

    return patternCode;
}

bool determineValidPatternCode(unsigned int newPatternCode, unsigned int possibleBits) {
    unsigned int maxValue = (1U << possibleBits) - 1;
    
    if (newPatternCode <=maxValue) {
       return true;
    }
    
     else {
       return false;
    }
}

BitField getPatternCode(RadixNode* node) {
    return node->patternCode;
}

RadixNode* getTreeRoot(RadixTree* tree) {
    return tree->root;
}

bool isRadixTreeFull(RadixTree* tree) {
    return tree->isFull;
}
