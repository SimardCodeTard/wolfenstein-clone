#include "struc.h"

level read_level(char* name);
int get_level_wall_count(char* level_data);
char* get_walls_data(char* level_data, int wall_count);
char **get_walls_data_lines(char* walls_data, int wall_count);
wall* get_level_walls(char** walls_data_lines, int wall_count);
char* get_level_name(char* level_data);