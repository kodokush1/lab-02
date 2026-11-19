#ifndef PLAYER_H
#define PLAYER_H

#define MAX_SLOTS 10
#define MAX_NAME_LEN 64

#define START_GOLD 1000
#define MAX_HP 100
#define MAX_STAMINA 100

typedef struct {
    char name[256];
    int gold;
    int max_hp;
    int current_hp;
    int max_stamina;
    int current_stamina;
    int inventory[MAX_SLOTS];
    int x;
    int y;
} Player;

typedef struct {
    Player player;
} Creature;

int utf8_len(const char *str);
void player_nickname(Player *player);
int check_creature(Creature *creature);
void *create_player(Player *player);
void player_description(Player *player);

#endif
