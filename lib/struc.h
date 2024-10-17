#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    int x;
    int y;
} vec2;

typedef struct {
    int x;
    int y;
    int z;
} vec3;

typedef struct {
    vec2 pos1;
    vec2 pos2;
} wall;

typedef struct {
    wall *walls;
    int wall_count;
    char *name;
} level;

#endif