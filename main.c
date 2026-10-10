#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки

#define md 10    // max_id

int inventory[md] = {0, 5, 2, 1, 0, 5, 0, 1, 8, 2};    // Инвентарь
const char* slot_name[md] = {
    "Пусто",
    "Дерево",
    "Камень",
    "Семена",
    "Золото",
    "Железо",
    "Кирка",
    "Ведро",
    "Земля",
    "Мотыга"};

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

int main(void) {    // Основная функция

    int current_day = 1;    // кейсы 2 и 3(время)
    int current_hour = 8;
    int time_skip;
    
    int slot;
    int item;
    
    while(1){
        
        printf("--------МЕНЮ--------\n1"
               ".Текущее время\n2"
               ".Пропуск времени\n3"
               ".Показать инвентарь\n4"
               ".Поднять предмет\n5"
               ".Обнуление слота\n6"
               ".Любимый ресурс\n7"
               ".Узнать id слотов\n0"
               ".Завершить программу\n");
        
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
                
                for (int i = 0; i < md; ++i) { printf("Слот[%d]: (%d) (%s)\n", i, inventory[i], slot_name[inventory[i]]); }
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
                else { printf("Любимый ресурс: %s\n", slot_name[find_the_greatest()]); }
                break;
            
            case 7:
                
                for (int i = 0; i < md; i++) { printf("%d. %s\n", i, slot_name[i]); }
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
