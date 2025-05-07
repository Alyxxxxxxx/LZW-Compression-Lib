#include "FileManagement.h"

FileManagement* createFileManagement(char *filename) {
    FileManagement *handler = malloc(sizeof(FileManagement));
    handler->filename = strdup(filename);
    return handler;
}


int openFile(FileManagement *handler, char *mode) {
    handler->file = fopen(handler->filename, mode);
    return (handler->file != NULL);
}

void closeFile(FileManagement *handler) {
    if (handler->file) {
        fclose(handler->file);
        handler->file = NULL;
    }
}

void writeFile(FileManagement *handler, uint8_t data) {
    if (handler->file) {
	printf("DATO A ESCRIBIR....%d\n", data);
	fwrite(&data, sizeof(uint8_t), 1, handler->file);
    }
}

void deleteFileManagement(FileManagement *handler) {
    closeFile(handler);
    free(handler->filename);
    free(handler);
}

FILE* getFile(FileManagement *handler) {
    return handler->file;
}
