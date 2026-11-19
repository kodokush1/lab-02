#ifndef MAP_H
#define MAP_H

#define TREE_CHANCE 15
#define ROCK_CHANCE 30

typedef struct {
    char **cells;
    int height;
    int width;
} Map;

void free_map(Map *map);
int create_map(Map *map, int height, int width);
void generate_map(Map *map);

#endif
