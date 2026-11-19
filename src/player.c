#include "player.h"

#include <stdio.h>
#include <stdlib.h>

int check_memory(const void *memory) {
    if (memory == NULL) { printf("Ошибка выделения памяти\n"); return 0; }
    return 1;
}

//ВВОД НИКНЕЙМА
void player_nickname(Player *player) {
    do {
        printf("Введите никнейм[до 32 символов]: ");
        if (scanf("%255s", player->name) != 1) {
            return;
        }
    } while (utf8_len(player->name) > 32);
}

void *create_player(Player *player) {
    free(player);
    player = malloc(sizeof *player);
    
    if (check_memory(player) == 0) { return NULL; }

    player_nickname(player);
    player->gold = START_GOLD;
    player->max_hp = MAX_HP;
    player->current_hp = MAX_HP;
    player->max_stamina = MAX_STAMINA;
    player->current_stamina = MAX_STAMINA;
    return player;
}

void player_description(Player *player) {
    printf("HP: %i|%i ST: %i|%i GOLD: %i\n", player->current_hp, player->max_hp, player->current_stamina, player->max_stamina, player->gold);
}
