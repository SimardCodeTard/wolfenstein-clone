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
    vec2 position;
    int value;
} cell;

typedef struct {
    cell** cells;
} level;

typedef struct {
    vec2 pos;
    float angle;
} player;

#endif