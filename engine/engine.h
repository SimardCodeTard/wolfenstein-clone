#include <SDL2/SDL.h>
#include "../struc.h"

#ifndef ENGINE_H
#define ENGINE_H

void run();
void handle_events(int *running, player *player);
SDL_Renderer *init_SDL();
int ray_intersects_wall(vec2 ray_origin, vec2 ray_direction, wall wall, float *distance);
void cast_rays(player player, wall *walls, int wall_count, SDL_Renderer *renderer);
void draw_column(int col, int line_height, SDL_Renderer *renderer);
void reset_view(SDL_Renderer *renderer);

#endif