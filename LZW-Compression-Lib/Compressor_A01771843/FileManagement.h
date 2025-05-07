#ifndef _FILE_MANAGEMENT_H
#define _FILE_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 

typedef struct FileManagement FileManagement;

struct FileManagement {
    FILE* file;
    char* filename;
};

FileManagement* createFileManagement(char*filename);
int openFile(FileManagement* handler, char* mode);
void closeFile(FileManagement* handler);
void writeFile(FileManagement* handler, uint8_t data);
FILE* getFile(FileManagement* handler);
void deleteFileManagement(FileManagement* handler);

#endif // FILE_MANAGEMENT_H
