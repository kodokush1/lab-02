#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Библиотеки
#include <time.h>
#include <ctype.h>

#include "adventure.h"
#include "player.h"
#include "time.h"
#include "utils.h"

//МЭЙН
int main(void) {
     
    Player *player = NULL;
    Time game_time = {.current_hour = 8, .current_day = 1};
    load_items();
    load_input();
    srand((unsigned int)time(0));
    
    while(1){
        
        printf("Привет, %s\n1"
               ".Создать персонажа\n2"
               ".Карточка персонажа\n3"
               ".Показать инвентарь\n4"
               ".Поднять предмет\n5"
               ".Обнуление слота\n6"
               ".Любимый ресурс\n7"
               ".Поиск предмета в рюкзаке\n8"
               ".Записать состояние в дневник\n9"
               ".Расписание жителей деревни\n10"
               ".Отправиться в приключение\n0"
               ".Завершить программу\n", player != NULL ? player->name : "???");
        
        switch(input_check()) {
                
            case 1 :
                if (player == NULL) {
                    player = create_player(player);
                }
                else {
                    printf("Персонаж уже создан. Хотите пересоздать? [1.да] [2.НЕТ]\n");
                    switch (input_check()) {
                        case 1:
                            player = create_player(player);
                            break;
                        case 2:
                            break;
                            
                        default:
                            break;
                    }
                }
                break;
            case 2 :
                if (player == NULL) {
                    printf("Персонаж не создан\n");
                    break;
                }
                else { player_description(player); break;}
                
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
                if (player == NULL) {
                    printf("Персонаж не создан\n");
                    break;
                }
                diary(player, &game_time); break;
            case 9:
                check_village(&game_time); break;
            case 10:
                adventure(); break;
            default:
                printf("Нет такого пункта!!!\n"); break;
            case -1:
                printf("Введите один символ и именно число!!!\n"); break;
            case -2:
            case 0 :
                free(player);
                return 0;
                
        }
    }
}
