//КАРТА
#include "map.h"
#include <stdlib.h>

void free_map(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->cells[i]);
    }
    
    free(map->cells);
    
    map->cells = NULL;
    map->width = 0;
    map->height = 0;
}

int create_map(Map *map, int height, int width) {
    
    map->height = height;
    map->width = width;
    
    map->cells = (char**)malloc(height * sizeof(char*));
    
    if (map->cells == NULL) {
        return 0;
    }
    
    for (int i = 0; i < height; i++) {
        map->cells[i] = (char*)malloc(width * sizeof(char));
    
        if (map->cells[i] == NULL) {
            for (int j = 0; j < i; j++) {free(map->cells[j]);}
            free(map->cells);
            return 0;
        }
    }
    
    return 1;
}

void generate_map(Map *map) {
    
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            
            int chance = rand() % 100;
            
            if (chance <= TREE_CHANCE) {map->cells[i][j] = 'T';}
            else if (chance <= ROCK_CHANCE && chance > TREE_CHANCE) {map->cells[i][j] = 'R';}
            else {map->cells[i][j] = '.';}
            
        }
    }
}
