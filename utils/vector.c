#include "vector.h"
#include <math.h>

float distance(vec2 v1, vec2 v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}