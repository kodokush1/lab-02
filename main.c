#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки

#define md 10    // max_id
#define MAX_NAME_LEN 64
#define shedule 13

int inventory[md] = {0, 5, 2, 1, 0, 5, 0, 1, 8, 2};    // Инвентарь
char name_items[md][MAX_NAME_LEN];

char nickname[100];

int current_day = 1;    // Кейсы 2 и 3(время)
int current_hour = 8;
int time_skip;


void enter_nickname(void) {
    do{
        printf("Введите никнейм[до 32 символов]: ");
        scanf("%99s", nickname);
    } while (strlen(nickname) > 32);
}

int check(void) {    // Функция проверка на дурака символы [0 до 9]
    
    char value[10];
    scanf("%9s", value);
    
    if (strlen(value) == 1) {
        if (value[0] >= '0' && value[0] <= '9') {
            return value[0] - '0';
        }
        else {
            return 403;
        }
    }
    else {
        return 403;
    }
    
}

int skip_time(void) { // Функция скип тайм с защитой от дурака
    
    int num;

    if (scanf("%d", &num) != 1 || num <= 0) {
        while (getchar() != '\n');
        return -1;
    }

    while (getchar() != '\n');

    return num;
}

int find_the_greatest(void) { // поиск наибольшего
    
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

char npc_name[shedule][256];
char npc_start[shedule][256];
char npc_end[shedule][256];
char npc_location[shedule][256];


void load_input(void) {
    FILE *f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    char buffer[256];
    int i = 0;

    while (i < 13 && fgets(buffer, sizeof(buffer), f) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        int flag = 0;
        int k = 0;

        for (int j = 0; ; j++) {
            if (buffer[j] == ';' || buffer[j] == '\0') {
                if (flag == 0) npc_name[i][j - k] = '\0';
                if (flag == 1) npc_start[i][j - k] = '\0';
                if (flag == 2) npc_end[i][j - k] = '\0';
                if (flag == 3) npc_location[i][j - k] = '\0';

                if (buffer[j] == '\0')
                    break;

                flag++;
                k = j + 1;
            } else {
                if (flag == 0) npc_name[i][j - k] = buffer[j];
                if (flag == 1) npc_start[i][j - k] = buffer[j];
                if (flag == 2) npc_end[i][j - k] = buffer[j];
                if (flag == 3) npc_location[i][j - k] = buffer[j];
            }
        }

        i++;
    }

    fclose(f);
}

void check_village(void){
    
    FILE *f = fopen("output.txt", "w");
    if (f == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }
    char *q;
    fprintf(f, "Время: %i:00\n", current_hour);
    for(int i = 0; i < shedule; i++){
        if(current_hour >= strtol(npc_start[i],&q ,10) && current_hour <= strtol(npc_end[i],&q ,10)){
            fprintf(f, "%-50s[%s]\n", npc_name[i], npc_location[i]);
        }
        else{
            fprintf(f, "%-50s[Спит дома]\n", npc_name[i]);
        }
    }
    fclose(f);
}

int utf8_len(char const *str){
    int len = 0;
    
    while(*str) {
        
        if ((*str & 0xC0) != 0x80) {
            len++;
        }
        str++;
    }
    
    return len;
    
}

void diary(void) {
  
    FILE *file_diary = fopen("diary.txt", "a");
    if (file_diary == NULL) { printf("Ошибка при открытии файла\n"); return; }
    
    int space = 32 - utf8_len(nickname);
    fprintf(file_diary, "┌────────────────────────────────┐ ┌──────────────┐\n");
    fprintf(file_diary, "│%s", nickname);
    for(int i = 0; i < space; i ++) { fprintf(file_diary, " "); }
    fprintf(file_diary, "│ │%-5i/%-2i:00   │\n", current_day, current_hour);
    fprintf(file_diary, "├────────────────────────────────┤ └──────────────┘\n");
    
    for(int i = 0; i < md; i ++){
        space = 22 - utf8_len(name_items[inventory[i]]);
        fprintf(file_diary, "│ Слот[%d]: %s", i, name_items[inventory[i]]);
        for(int j = 0; j < space; j++) { fprintf(file_diary, " "); }
        fprintf(file_diary, "│\n");
    }
    fprintf(file_diary, "└────────────────────────────────┘\n");
    fclose(file_diary);
}

int find_id_by_name(char find_item[20]){
    
    for(int j = 0; j < md; j++) {
        if(strcmp(find_item, name_items[j]) == 0) {
            return j;
        }
    }
    
    return -1;
}

int find_item_by_id(int id, int i){
    
    if(inventory[i] == id){ return i;}
    else { return 0; }
    
}
    


int main(void) {    // Основная функция
    
    int slot;
    int item;
    
    load_items();
    
    enter_nickname();
    
    load_input();

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
                
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
                
            case 2 :
                
                printf("Сколько часов вы хотите пропустить?\n");
                time_skip = skip_time();
                if (time_skip == -1) { printf("Неверный ввод!!!\n"); break; }
                current_hour = current_hour + time_skip;
                while (current_hour >= 24) { current_hour = current_hour - 24; current_day += 1; }
                break;
            
            case 3 :
                
                for (int i = 0; i < md; ++i) { printf("Слот[%d]: (%d) (%s)\n", i, inventory[i], name_items[inventory[i]]); }
                break;
                
            case 4 :
                
                printf("Введите номер слота (0-9):\n");
                slot = check();
                if (slot == 403) { printf("Ошибка 403: введите одну цифру!\n"); break; }
                printf("Введите ID предмета (0-9):\n");
                item = check();
                if (item == 403) { printf("Ошибка 403: введите одну цифру!\n"); break; }
                inventory[slot] = item;
                break;
                
            case 5 :

                printf("Введите номер слота [0-9]\n");
                slot = check();
                if (slot == 403) { printf("Ошибка 403: введите одну цифру!\n"); break; }
                inventory[slot] = 0;
                break;
                
            case 6 :
                
                if (find_the_greatest() == 0) { printf("Инвентарь пуст\n"); }
                else { printf("Любимый ресурс: %s\n", name_items[find_the_greatest()]); }
                break;
            
            case 7:
                
                printf("Введите название искомого предмета: ");
                char find_item[20];
                scanf("%s", find_item);
                int id = find_id_by_name(find_item);
                if (id == -1) { printf("Такого предмета нет\n"); }
                else {
                    printf("Предмет лежит в слотах: ");
                    for (int i = 0; i < md; i++) { printf("%i ", find_item_by_id(id, i)); }
                }
                printf("\n");
                
            case 8:
                
                diary();
                break;
            
            case 9:
                
                check_village();
                break;
                
            default:
                
                printf("Нет такого пункта!!!\n");
                break;
                
            case 403:
                
                printf("Введите один символ и именно число!!!\n");
                break;
                
            case 0 :
                
                return 0;
                
        }
    }
}
