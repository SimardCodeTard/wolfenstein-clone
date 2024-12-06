#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "level.h"
#include "../struc.h"
#include "../file/file.c"

#define LEVEL_PATH "data/levels/"
#define LEVEL_PATH_MAX_SIZE 50
#define LEVEL_MAX_HEIGHT 50
#define LEVEL_MAX_WIDTH 50

level read_level(char *name) {
    char path[LEVEL_PATH_MAX_SIZE];
    strcpy(path, LEVEL_PATH);
    strcat(path, name);

    level level;

    char *level_data = read_file(path);

    if(level_data == NULL) {
        printf("Error, level data for level %s is null", name);
        return level;
    }

    int data_length = strlen(level_data);

    if(data_length > LEVEL_MAX_HEIGHT * LEVEL_MAX_HEIGHT + LEVEL_MAX_HEIGHT + 1) { // Add level max height again to account for line breaks & add 1 for eventual EOF
        printf("Level %s exceeds max size.\n", name);
        return level;
    }

    int colIndex = 0;
    int rowIndex = 0;

    cell** rows = malloc(sizeof(cell*) * LEVEL_MAX_HEIGHT);
    
    for (int i = 0; i < LEVEL_MAX_HEIGHT; i++) {
        rows[i] = malloc(sizeof(cell) * LEVEL_MAX_WIDTH);
    }

    for(int i = 0; i < data_length; i++) {
        if(level_data[i] == '\n') {
            colIndex = 0;
            continue;
        }
        rows[rowIndex][colIndex].position.x = colIndex;
        rows[rowIndex][colIndex].position.y = rowIndex;
        rows[rowIndex][colIndex].value = (int) level_data[i];

        colIndex++;
    }

    free(level_data);
    free(rows);

    return level;
}
