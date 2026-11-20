#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки
#include <ctype.h>
//ТЕКУЩЕЕ ВРЕМЯ

int input_check(void) {
    int num;
    int result = scanf("%d", &num);
    if (result == EOF) {
        return INPUT_END;
    }

    int ch;
    int trailing_text = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (!isspace(ch)) {
            trailing_text = 1;
        }
    }

    if (result != 1 || num < 0 || trailing_text) {
        return INPUT_INVALID;
    }

    return num;
}

int input_inventory_check(void) {
    int num;
    do {
        num = input_check();
        if (num == INPUT_END) {
            return INPUT_END;
        }
        if (num < 0 || num >= md) {
            printf("Введите число от 0 до %d: ", md - 1);
        }
    } while (num < 0 || num >= md);

    return num;
}

int inventory[md] = {0, 5, 2, 1, 0, 5, 0, 1, 8, 2};    // Инвентарь
char name_items[md][MAX_NAME_LEN];

//какая та шляпа чтобы считать количество символов и потом можно было пробелы ставить и там типа красиво
int utf8_len(char const *str) {
    
    int len = 0;

    while(*str) {
        if((*str & 0xC0) != 0x80) {
            len++;
        }
        str++;
    }
    return len;
    
}

//ПОКАЗАТЬ ИНВЕНТАРЬ
void print_inventory(void) {
    
    for (int i = 0; i < md; ++i) { printf("Слот[%d]: (%d) (%s)\n", i, inventory[i], name_items[inventory[i]]); }
    
}

//ПОДНЯТЬ ПРЕДМЕТ
void up_item(void) {
    
    int slot;
    int item;
    
    printf("Введите номер слота (0-9):\n");
    slot = input_inventory_check();
    if (slot == INPUT_END) { return; }
    printf("Введите ID предмета (0-9):\n");
    item = input_inventory_check();
    if (item == INPUT_END) { return; }
    inventory[slot] = item;
    
}

//ЗАНУЛЕНИЕ СЛОТА
void null_slot(void) {

    int slot;
    
    printf("Введите номер слота [0-9]\n");
    slot = input_inventory_check();
    if (slot == INPUT_END) { return; }
    inventory[slot] = 0;
    
}

//ПОИСК НАИБОЛЬШЕГО //НАДО ПЕРЕДЕЛАТЬ
int find_the_greatest(void) {
    
    int count_for_slot[md] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for(int i = 1; i < md; i++){
        for(int j = 0; j < md; j++){
            if (inventory[j] == i){
                count_for_slot[i] += 1;
            }
        }
    }
    
    int max = count_for_slot[0];
    int index = 0;
    
    for(int i = 1; i < md; i++){
        if (max < count_for_slot[i]){
            max = count_for_slot[i];
            index = i;
        }
    }
    
    return index;
    
}

void print_find_the_greatest(void) {
    
    if (find_the_greatest() == 0) { printf("Инвентарь пуст\n"); }
    else { printf("Любимый ресурс: %s\n", name_items[find_the_greatest()]); }
    
}

//ПОИСК ПО НАЗВАНИЮ
void find_id_by_name(void) {

    char find_item[64];
    int count_iteration = 0;
    int id = -1;

    printf("Введите название искомого предмета: ");
    if(scanf("%63s", find_item) != 1) {
        printf("Ошибка ввода\n");
        return;
    }

    for(int i = 0; i < md; i++) {
        if (strcmp(find_item, name_items[i]) == 0) {
            id = i;
            break;
        }
    }

    if(id == -1) { printf("Такого предмета не существует\n"); return; }

    for(int j = 0; j < md; j++) {
        if(id == inventory[j]) {
            if (count_iteration == 0) { printf("Предмет лежит в слотах: "); }
            printf("%i ", j);
            count_iteration++;
        }
    }

    if(count_iteration == 0) { printf("Предмет не найден в инвентаре\n"); }
    else { printf("\n"); }
    
}

//ПОДГРУЗКА ИМЕН ДЛЯ ИНВЕНТАРЯ
void default_items(void) {
    
    strcpy(name_items[0], "Пусто");
    strcpy(name_items[1], "Дерево");
    strcpy(name_items[2], "Камень");
    strcpy(name_items[3], "Меч");
    strcpy(name_items[4], "Золото");
    strcpy(name_items[5], "Железо");
    strcpy(name_items[6], "Кирка");
    strcpy(name_items[7], "Ведро");
    strcpy(name_items[8], "Земля");
    strcpy(name_items[9], "Мотыга");
    
}

void load_items(void) {
  
    FILE *file_items = fopen("items.txt", "r");
    if (file_items == NULL) { printf("Ошибка при открытии файла\nЗагружены резервные значения\n"); default_items(); return; }
    
    int id;
    char name[MAX_NAME_LEN];
    
    while(fscanf(file_items, "%d %63s", &id, name) == 2) {
        strcpy(name_items[id], name);
    }
    
    fclose(file_items);
    
}

//РАСПИСАНИЕ ЖИТЕЛЕЙ
typedef struct {
    char name[256];
    int start;
    int end;
    char location[256];
} NPC;

NPC villagers[shedule];

void load_input(void) {
    
    FILE *f = fopen("input.txt", "r");
    if(f == NULL) { printf("Ошибка открытия файла!"); return; }
    
    char buffer[256];
    int i = 0;
    
    while(i < shedule && fgets(buffer, sizeof(buffer), f) != NULL) {
        NPC *npc = &villagers[i];
        sscanf(buffer, "%255[^;];%d;%d;%255[^\r\n]", npc -> name, &npc -> start, &npc -> end, npc -> location);
        i++;
    }

    fclose(f);
    
}

void check_village(Time *time) {

    FILE *f = fopen("output.txt", "w");
    if(f == NULL) { printf("Ошибка при открытии файла\n"); return; }

    fprintf(f, "Время: %i:00\n", time->current_hour);

    for(int i = 0; i < shedule; i++) {

        int duplicate = 0;

        for(int k = 0; k < i; k++) {
            if(strcmp(villagers[i].name, villagers[k].name) == 0) { duplicate = 1; }
        }

        if (duplicate == 1) { continue; }

        const char *location = "Спит_дома";

        for(int j = 0; j < shedule; j++) {

            if(strcmp(villagers[i].name, villagers[j].name) == 0) {

                if((time->current_hour >= villagers[j].start && time->current_hour < villagers[j].end) ||
                    (villagers[j].start > villagers[j].end && time->current_hour <= villagers[j].start && time->current_hour > villagers[j].end)) {

                    location = villagers[j].location;
                }
            }
        }

        int space = 22 - utf8_len(villagers[i].name);
        
        fprintf(f, "%s", villagers[i].name);
        for(int j = 0; j < space; j++) { fprintf(f, " "); }
        fprintf(f, "[%s]\n", location);
    }

    fclose(f);
    
}

//ДНЕВНИК
void diary(Player *player, Time *time) {
  
    FILE *file_diary = fopen("diary.txt", "a");
    if (file_diary == NULL) { printf("Ошибка при открытии файла\n"); return; }
    
    int space = 32 - utf8_len(player->name);
    fprintf(file_diary, "┌────────────────────────────────┐\n");
    printf("┌────────────────────────────────┐\n");
    fprintf(file_diary, "│%s", player->name);
    printf("│%s", player->name);
    for(int i = 0; i < space; i ++) { fprintf(file_diary, " "); printf(" "); }
    fprintf(file_diary, "│ %d День/%d:00\n", time->current_day, time->current_hour);
    printf("│ %d День/%d:00\n", time->current_day, time->current_hour);
    fprintf(file_diary, "├────────────────────────────────┤\n");
    printf("├────────────────────────────────┤\n");
    
    for(int i = 0; i < md; i ++){
        space = 22 - utf8_len(name_items[inventory[i]]);
        fprintf(file_diary, "│ Слот[%d]: %s", i, name_items[inventory[i]]);
        printf("│ Слот[%d]: %s", i, name_items[inventory[i]]);
        for(int j = 0; j < space; j++) { fprintf(file_diary, " "); printf(" "); }
        fprintf(file_diary, "│\n");
        printf("│\n");
    }
    fprintf(file_diary, "└────────────────────────────────┘\n");
    printf("└────────────────────────────────┘\n");
    fclose(file_diary);
    
}
