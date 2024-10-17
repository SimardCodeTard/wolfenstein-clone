#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "level.h"
#include "struc.h"
#include "file.c"

#define LEVEL_PATH "levels/"
#define LEVEL_MAX_WALLS 100
#define LEVEL_MAX_WALL_DATA_SIZE (3 * 2 + 2 + 1)  * 2 // 3 digits for each x and y, 2 commas, 1 semicolon and 1 null terminator for each point
#define LEVEL_NAME_IDENTIFIER "name:\n"
#define LEVEL_WALLS_IDENTIFIER "walls:\n"

level read_level(char *name) {
    printf("=======================================\n");
    printf("Entering read_level function \n");

    char path[50];
    strcpy(path, LEVEL_PATH);
    strcat(path, name);

    level level;

    char *level_data = read_file(path);
    if (level_data == NULL) {
        printf("Failed to read level file\n");
        exit(1);
    }

    printf("Level data:\n%s\n", level_data);
    
    char *level_name = get_level_name(level_data);

    int wall_count = get_level_wall_count(level_data);

    char *walls_data = get_walls_data(level_data, wall_count);
    if (walls_data == NULL) {
        printf("Failed to parse walls data\n");
        free(level_data);
        exit(1);
    }


    char **walls_data_lines = get_walls_data_lines(walls_data, wall_count);
    if(walls_data_lines == NULL) {
        printf("Failed to parse walls data lines\n");
        free(walls_data);
        exit(1);
    }

    wall *walls = get_level_walls(walls_data_lines, wall_count);
    if (walls == NULL) {
        printf("Failed to create walls\n");
        exit(1);
    }
    
    free(level_data);
    free(walls_data);
    free(walls_data_lines);

    level.name = level_name;
    level.walls = walls;
    level.wall_count = wall_count;

    printf("Finished reading level %s\n", name);
    printf("Level name: %s\n", level.name);
    printf("Level walls:\n");
    for (int i = 0; i < wall_count; i++) {
        printf("Wall %d: (%d, %d) - (%d, %d)\n", i, walls[i].pos1.x, walls[i].pos1.y, walls[i].pos2.x, walls[i].pos2.y);
    }


    printf("Exiting read_level function \n");
    printf("=======================================\n");
    return level;
}

char* get_level_name(char *level_data) {
    printf("=======================================\n");
    printf("Entering get_level_name function \n");

    char *found = strstr(level_data, LEVEL_NAME_IDENTIFIER);
    if (found == NULL) {
        printf("LEVEL_NAME_IDENTIFIER not found in level_data\n");
        return NULL;
    }

    int name_index = found - level_data + strlen(LEVEL_NAME_IDENTIFIER);

    char *name = malloc(sizeof(char) * 50);
    if (name == NULL) {
        printf("Memory allocation failed for level name\n");
        exit(1);
    }

    int i = 0;
    while (level_data[name_index + i] != '\n') {
        name[i] = level_data[name_index + i];
        i++;
    }
    name[i] = '\0';

    printf("Exiting get_level_name function \n");
    printf("=======================================\n");
    return name;
}

int get_level_wall_count(char *level_data) {
    printf("=======================================\n");
    printf("Entering get_level_wall_count function \n");

    int level_wall_count = 0;

    int walls_index = strstr(level_data, LEVEL_WALLS_IDENTIFIER) - level_data;

    int c;

    int length = strlen(level_data); 
    while (walls_index < length && (c = level_data[walls_index]) != '\0') {
        if (c == '\n') {
            level_wall_count++;
        }
        walls_index++;
    }


    printf("Exiting get_level_wall_count function \n");
    printf("=======================================\n");
    return level_wall_count;
}

char *get_walls_data(char *level_data, int wall_count) {
    printf("=======================================\n");
    printf("Entering get_walls_data function \n");

    char *found = strstr(level_data, LEVEL_WALLS_IDENTIFIER);
    if (found == NULL) {
        printf("LEVEL_WALL_IDENTIFIER not found in level_data\n");
        return NULL;
    }

    int walls_index = found - level_data + strlen(LEVEL_WALLS_IDENTIFIER);

    char *walls_data = malloc(sizeof(char) * (LEVEL_MAX_WALL_DATA_SIZE * wall_count + 1));
    if (walls_data == NULL) {
        printf("Memory allocation failed for walls data\n");
        exit(1);
    }

    int i = 0;
    while (level_data[walls_index + i] != '\0') {
        walls_data[i] = level_data[walls_index + i];
        i++;
    }
    walls_data[i] = '\0';

    printf("Exiting get_walls_data function \n");
    printf("=======================================\n");
    return walls_data;
}

char **get_walls_data_lines(char* wall_data, int wall_count) {
    printf("=======================================\n");
    printf("Entering get_walls_data_lines function \n");

    char **walls_data_lines = malloc(sizeof(char *) * wall_count);
    if (walls_data_lines == NULL) {
        printf("Memory allocation failed for walls data lines\n");
        exit(1);
    }

    char *token = strtok(wall_data, "\n");

    for (int i = 0; i < wall_count; i++) {
        if (token == NULL) {
            printf("Error parsing walls data in get_walls_data_lines\n");
            free(walls_data_lines);
            return NULL;
        }

        walls_data_lines[i] = token;
        token = strtok(NULL, "\n");
    }

    printf("Exiting get_walls_data_lines function \n");
    printf("=======================================\n");


    return walls_data_lines;
}


wall *get_level_walls(char **walls_data_lines, int wall_count) {
    printf("=======================================\n");
    printf("Entering get_level_walls function \n");

    wall *walls = malloc(sizeof(wall) * wall_count);
    if (walls == NULL) {
        printf("Memory allocation failed for walls\n");
        exit(1);
    }

    vec2 wall_pos1;
    vec2 wall_pos2;

    char *wall_pos1_str;
    char *wall_pos2_str;
    char *wall_pos_x;
    char *wall_pos_y;
    for (int i = 0; i < wall_count; i++) {
        printf("Parsing wall %s\n", walls_data_lines[i]);
        wall_pos1_str = strtok(walls_data_lines[i], ";");

        if (wall_pos1_str == NULL) {
            printf("Error parsing walls data in get_level_walls (strtok call 1)\n");
            free(walls);
            return NULL;
        }

        wall_pos2_str = strtok(NULL, ";"); 

        if (wall_pos2_str == NULL) {
            printf("Error parsing walls data in get_level_walls (strtok call 2)\n");
            free(walls);
            return NULL;
        }

        // Parsing wall position 1 (x, y)
        wall_pos_x = strtok(wall_pos1_str, ",");
        wall_pos_y = strtok(NULL, ",");
        if (wall_pos_x == NULL || wall_pos_y == NULL) {
            free(walls);
            return NULL;
        }
        wall_pos1.x = atoi(wall_pos_x);
        wall_pos1.y = atoi(wall_pos_y);

        // Parsing wall position 2 (x, y)
        wall_pos_x = strtok(wall_pos2_str, ",");
        wall_pos_y = strtok(NULL, ",");
        if (wall_pos_x == NULL || wall_pos_y == NULL) {
            printf("Error parsing wall position 2\n");
            free(walls);
            return NULL;
        }
        wall_pos2.x = atoi(wall_pos_x);
        wall_pos2.y = atoi(wall_pos_y);

        // Assign the positions to the wall
        walls[i].pos1 = wall_pos1;
        walls[i].pos2 = wall_pos2;
    }

    printf("Exiting get_level_walls function \n");
    printf("=======================================\n");
    return walls;
}
