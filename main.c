#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки
#include <time.h>

#define md 10    // max_id
#define MAX_NAME_LEN 64
#define shedule 13

int inventory[md] = {0, 5, 2, 1, 0, 5, 0, 1, 8, 2};    // Инвентарь
char name_items[md][MAX_NAME_LEN];

char nickname[256];

int current_day = 1;    // Кейсы 2 и 3(время)
int current_hour = 8;
int time_skip;

//НАДО ПЕРЕЛЕЛАИТТ

//НАДО ПКЕрЕДАЛТЬ
int check(void) { // Функция скип тайм с защитой от дурака
    
    int num;

    if (scanf("%d", &num) != 1 || num <= 0) {
        while (getchar() != '\n');
        return -1;
    }

    while (getchar() != '\n');

    return num;
    
}

int check_slot(void) {
    
    int num;
    
    do{
        num = check();
    } while(num < md || num >= 0);
    
    return num;
    
}

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

//ВВОД НИКНЕЙМА
void enter_nickname(void) {
    do {

        printf("Введите никнейм[до 32 символов]: ");
        scanf("%255s", nickname);
    } while (utf8_len(nickname) > 32);
    
}

//ТЕКУЩЕЕ ВРЕМЯ
void print_current_hour(void) {
    
    printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
    
}

//ПРОПУСК ВРЕМЕНИ
void print_skip_time(void) {
    
    printf("Сколько часов вы хотите пропустить?\n");
    time_skip = check();
    if (time_skip == -1) { printf("Неверный ввод!!!\n"); return; }
    current_hour = current_hour + time_skip;
    while (current_hour >= 24) { current_hour = current_hour - 24; current_day += 1; }
    
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
    slot = check_slot();
    if (slot == 403) { printf("Ошибка 403: введите одну цифру!\n"); return; }
    printf("Введите ID предмета (0-9):\n");
    item = check_slot();
    if (item == 403) { printf("Ошибка 403: введите одну цифру!\n"); return; }
    inventory[slot] = item;
    
}

//ЗАНУЛЕНИЕ СЛОТА
void null_slot(void) {

    int slot;
    
    printf("Введите номер слота [0-9]\n");
    slot = check_slot();
    if (slot == 403) { printf("Ошибка 403: введите одну цифру!\n"); return; }
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

void check_village(void) {

    FILE *f = fopen("output.txt", "w");
    if(f == NULL) { printf("Ошибка при открытии файла\n"); return; }

    fprintf(f, "Время: %i:00\n", current_hour);

    for(int i = 0; i < shedule; i++) {

        int duplicate = 0;

        for(int k = 0; k < i; k++) {
            if(strcmp(villagers[i].name, villagers[k].name) == 0) { duplicate = 1; }
        }

        if (duplicate == 1) { continue; }

        const char *location = "Спит_дома";

        for(int j = 0; j < shedule; j++) {

            if(strcmp(villagers[i].name, villagers[j].name) == 0) {

                if((current_hour >= villagers[j].start && current_hour < villagers[j].end) ||
                    (villagers[j].start > villagers[j].end && current_hour <= villagers[j].start && current_hour > villagers[j].end)) {

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
void diary(void) {
  
    FILE *file_diary = fopen("diary.txt", "a");
    if (file_diary == NULL) { printf("Ошибка при открытии файла\n"); return; }
    
    int space = 32 - utf8_len(nickname);
    fprintf(file_diary, "┌────────────────────────────────┐\n");
    printf("┌────────────────────────────────┐\n");
    fprintf(file_diary, "│%s", nickname);
    printf("│%s", nickname);
    for(int i = 0; i < space; i ++) { fprintf(file_diary, " "); printf(" "); }
    fprintf(file_diary, "│ %d День/%d:00\n", current_day, current_hour);
    printf("│ %d День/%d:00\n", current_day, current_hour);
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

//КАРТА
typedef struct {
    char **cells;
    int height;
    int width;
} Map;

typedef struct {
    int x;
    int y;
} Hero;

typedef struct {
    int x;
    int y;
} Bonfire;

typedef struct {
    Map map;
    Hero hero;
    Bonfire bonfire;
    int vision;
    int rooms;
} Adventure;

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
            return 0;
        }
    }
    
    return 1;
}

void generate_map(Map *map) {
    
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            
            int chance = rand() % 100;
            
            if (chance <= 15) {map->cells[i][j] = 'T';}
            else if (chance <= 30 && chance > 15) {map->cells[i][j] = 'R';}
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
    
    if (new_y >= adventure->map.height || new_x >= adventure->map.width || new_x < 0 || new_y < 0) {return 2;}

    if (adventure->map.cells[new_y][new_x] != '.' && adventure->map.cells[new_y][new_x] != '^') {return 0;}
    
    adventure->hero.x = new_x;
    adventure->hero.y = new_y;
    
    if (adventure->map.cells[new_y][new_x] == '^') {return 3;}
    
    return 0;
}

void print_map(Adventure *adventure) {
    for (int i = 0; i < adventure->map.height; i++) {
        for (int j = 0; j < adventure->map.width; j++) {
            if (i == adventure->hero.y && j == adventure->hero.x) {printf(" *"); continue;}
            
            int dx = adventure->hero.x - j;
            int dy = adventure->hero.y - i;
            
            if (dx * dx + dy * dy <= 49 && adventure->vision > 0) {printf(" %c", adventure->map.cells[i][j]); continue;}
            
            printf(" ?");
        }
        printf("\n");
    }
}

void new_location(Adventure *adventure, char key) {

    printf("Вы все дальше от дома....\n");

    free_map(&adventure->map);

    int width = (rand() % 26) + 5;
    int height = width;

    adventure->rooms++;
    
    if (create_map(&adventure->map, height, width) == 0) {printf("Ошибка выделения памяти\n");}
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

    int width = (rand() % 26) + 5;
    int height = width;
    char key = ' ';
    int result = 0;

    adventure.vision = 0;
    adventure.rooms = 1;

    if (create_map(&adventure.map, height, width) == 0) {printf("Ошибка выделения памяти");}
    generate_map(&adventure.map);
    create_hero(&adventure);
    create_bonfire(&adventure);

    while(1) {

        print_map(&adventure);

        scanf(" %c", &key);

        if (key == 'R') {adventure.vision = 3; continue;}
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

        if (result == 2) {new_location(&adventure, key);}
        if (result == 3) {printf("Вы чувствуете тепло костра...\n");}

        printf("Расстояние до дома: бесконечность и %i\n", adventure.rooms);

        if (adventure.vision > 0) {adventure.vision--;}

    }
    free_map(&adventure.map);
}

//МЭЙН
int main(void) {
    
    load_items();
    enter_nickname();
    load_input();
    srand((unsigned int)time(0));
    
    while(1){
        
        printf("Привет, %s\n1"
               ".Текущее время\n2"
               ".Пропуск времени\n3"
               ".Показать инвентарь\n4"
               ".Поднять предмет\n5"
               ".Обнуление слота\n6"
               ".Любимый ресурс\n7"
               ".Поиск предмета в рюкзаке\n8"
               ".Записать состояние в дневник\n9"
               ".Расписание жителей деревни\n0"
               ".Завершить программу\n", nickname);
        
        switch(check()) {
                
            case 1 :
                print_current_hour(); break;
            case 2 :
                print_skip_time(); break;
            case 3 :
                print_inventory(); break;
            case 4 :
                up_item(); break;
            case 5 :
                null_slot(); break;
            case 6 :
                print_find_the_greatest(); break;
            case 7:
                find_id_by_name();
                break;
            case 8:
                diary(); break;
            case 9:
                check_village(); break;
            case 10:
                adventure(); break;
            default:
                printf("Нет такого пункта!!!\n"); break;
            case 403:
                printf("Введите один символ и именно число!!!\n"); break;
            case 0 :
                return 0;
                
        }
    }
}
