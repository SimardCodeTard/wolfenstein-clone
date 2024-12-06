#include "engine.h"
#include "../struc.h"
#include "../level/level.c"
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1200
#define FOV 60


void run() {
    int running = 1;

    level level = read_level("0");
    player player;
    player.pos.x = 50;
    player.pos.y = 50;
    player.angle = 0;

    SDL_Renderer *renderer = init_SDL();

    while (running) {
        handle_events(&running, &player);

        reset_view(renderer);

        cast_rays(player, level.walls, level.wall_count, renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // ~60 FPS
    }
}

void handle_events(int *running, player *player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            *running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        player->pos.x += 5 * cos(player->angle);
                        player->pos.y += 5 * sin(player->angle);
                        break;
                    case SDLK_DOWN:
                        player->pos.x -= 5 * cos(player->angle);
                        player->pos.y -= 5 * sin(player->angle);
                        break;
                    case SDLK_LEFT:
                        player->angle -= 0.1;
                        break;
                    case SDLK_RIGHT:
                        player->angle += 0.1;
                        break;
                }
                printf("Player position: (%d, %d)\n", player->pos.x, player->pos.y);
        }
    }
}

SDL_Renderer *init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    exit(1);
    }

    SDL_Window *win = SDL_CreateWindow("Clonefenstein", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    return renderer;
}

int ray_intersects_wall(vec2 ray_origin, vec2 ray_direction, wall wall, float *distance) {
    float x1 = wall.pos1.x;
    float y1 = wall.pos1.y;
    float x2 = wall.pos2.x;
    float y2 = wall.pos2.y;

    float x3 = ray_origin.x;
    float y3 = ray_origin.y;
    float x4 = ray_origin.x + ray_direction.x;
    float y4 = ray_origin.y + ray_direction.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (den == 0.0) return 0;

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t >= 0 && t <= 1 && u >= 0) {
        *distance = u;
        return 1;
    }

    return 0;
}

void cast_rays(player player, wall *walls, int wall_count, SDL_Renderer *renderer) {
    vec2 ray_angle;
}

void draw_column(int col, int line_height, SDL_Renderer *renderer) {
    SDL_Rect column_rect;
    column_rect.x = col;
    column_rect.y = (WINDOW_HEIGHT - line_height) / 2;
    column_rect.w = 1;
    column_rect.h = line_height;

    SDL_SetRenderDrawColor(renderer, col, col, col, 255);
    SDL_RenderFillRect(renderer, &column_rect);
}

void reset_view(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
