//КАРТА
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки
#include <time.h>
#include <ctype.h>

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

void create_hero(Adventure *adventure) {
    do {
        
        adventure->hero.x = rand() % adventure->map.width;
        adventure->hero.y = rand() % adventure->map.height;
        
    } while(adventure->map.cells[adventure->hero.y][adventure->hero.x] != '.');
}

void create_bonfire(Adventure *adventure) {
    do {
        
        adventure->bonfire.x = rand() % adventure->map.width;
        adventure->bonfire.y = rand() % adventure->map.height;
        
    } while(adventure->map.cells[adventure->bonfire.y][adventure->bonfire.x] != '.' ||
            (adventure->hero.x == adventure->bonfire.x && adventure->hero.y == adventure->bonfire.y));
    
    adventure->map.cells[adventure->bonfire.y][adventure->bonfire.x] = '^';
}

int move_hero(Adventure *adventure, char move_direction) {
    
    int new_x = adventure->hero.x;
    int new_y = adventure->hero.y;
    
    if (move_direction == 'A') {new_x--;}
    else if (move_direction == 'D') {new_x++;}
    else if (move_direction == 'W') {new_y--;}
    else if (move_direction == 'S') {new_y++;}
    else {return 0;}
    
    if (new_y >= adventure->map.height || new_x >= adventure->map.width || new_x < 0 || new_y < 0) {return NEW_LOCATION;}

    if (adventure->map.cells[new_y][new_x] != '.' && adventure->map.cells[new_y][new_x] != '^') {return 0;}
    
    adventure->hero.x = new_x;
    adventure->hero.y = new_y;
    
    if (adventure->map.cells[new_y][new_x] == '^') {return BONFIRE;}
    
    return 0;
}

void print_map(Adventure *adventure) {
    
    for (int i = 0; i < adventure->map.height; i++) {
        for (int j = 0; j < adventure->map.width; j++) {
            
            int dx = adventure->light.x - j;
            int dy = adventure->light.y - i;
            
            if (i == adventure->hero.y && j == adventure->hero.x) {printf(" \x1B[32m*\x1B[0m"); continue;}
            if (dx * dx + dy * dy <= adventure->light.vision * adventure->light.vision * LIGHT_LEVEL
                && adventure->light.vision > 0) {printf(" %c", adventure->map.cells[i][j]); continue;}
            
            printf(" ?");
        }
        printf("\n");
    }
}

void new_location(Adventure *adventure, char key) {
    
    int width = (rand() % MAX_MAP) + MIN_MAP;
    int height = (rand() % MAX_MAP) + MIN_MAP;
    
    Map next = {0};
    
    if (create_map(&next, height, width) == 0) {printf("Ошибка выделения памяти\n"); return;}
    
    printf("Вы все дальше от дома....\n");

    adventure->light.vision = 0;
    free_map(&adventure->map);
    adventure->map = next;

    adventure->floors++;
    
    generate_map(&adventure->map);

    if (key == 'W') {adventure->hero.x = width / 2; adventure->hero.y = height - 1;}
    else if (key == 'A') {adventure->hero.x = width - 1; adventure->hero.y = height / 2;}
    else if (key == 'S') {adventure->hero.x = width / 2; adventure->hero.y = 0;}
    else if (key == 'D') {adventure->hero.x = 0; adventure->hero.y = height / 2;}

    adventure->map.cells[adventure->hero.y][adventure->hero.x] = '.';

    create_bonfire(adventure);
}


void adventure(void) {

    Adventure adventure = {0};

    int width = (rand() % MAX_MAP) + MIN_MAP;
    int height = (rand() % MAX_MAP) + MIN_MAP;
    char key = ' ';
    int result = 0;

    adventure.light.vision = 0;
    adventure.floors = 1;

    if (create_map(&adventure.map, height, width) == 0) {printf("Ошибка выделения памяти"); return;}
    generate_map(&adventure.map);
    create_hero(&adventure);
    create_bonfire(&adventure);

    while(1) {
        
        printf("\033[2J\033[J");
        
        print_map(&adventure);
        printf("Расстояние до дома: бесконечность и %i\n", adventure.floors);
        if (result == BONFIRE) {printf("Вы чувствуете тепло костра...\n");}
        
        scanf(" %c", &key);
        key = toupper(key);

        if (key == 'R') {adventure.light.vision = 5; adventure.light.x = adventure.hero.x; adventure.light.y = adventure.hero.y; continue;}
        if (key == 'Q') {

            if (adventure.hero.x == adventure.bonfire.x &&
                adventure.hero.y == adventure.bonfire.y) {

                printf("Вас клонит в сон...\n");
                break;

            }

            printf("Слишком страшно спать...\n");
            continue;

        }

        result = move_hero(&adventure, key);

        if (result == NEW_LOCATION) {new_location(&adventure, key);}
        
        if (adventure.light.vision > 0) {adventure.light.vision--;}

    }
    free_map(&adventure.map);
}
