#include "file.h"
#include <stdlib.h>
#include <stdio.h>

#define LEVEL_MAX_SIZE 1000

char* read_file(char* path) {
    char* file_data = malloc(sizeof(char) * LEVEL_MAX_SIZE);

    FILE *fptr = fopen(path, "r");

    printf("Reading file %s\n", path);
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", path);
        return "";
    }

    int c;
    int i = 0;

    while((c = fgetc(fptr)) != EOF && i < LEVEL_MAX_SIZE) {
        file_data[i] = c;
        i++;
    }
    fclose(fptr);

    return file_data;
}