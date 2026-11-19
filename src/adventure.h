#ifndef ADVENTURE_H
#define ADVENTURE_H

#include "map.h"

#define BONFIRE 3
#define NEW_LOCATION 2
#define LIGHT_LEVEL 3
#define MIN_MAP 5
#define MAX_MAP 26

typedef struct {
    int x;
    int y;
} Hero;

typedef struct {
    int x;
    int y;
} Bonfire;

typedef struct {
    int x;
    int y;
    int vision;
} Light;

typedef struct {
    Map map;
    Hero hero;
    Bonfire bonfire;
    Light light;
    int floors;
} Adventure;

void adventure(void);

#endif
