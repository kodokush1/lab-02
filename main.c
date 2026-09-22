#include <stdio.h>
#include <stdlib.h>

#define md 10         // max_id

int current_day = 1;
int current_hour = 8;
int inventory[md] = {0, 5, 2, 1, 0, 5, 0, 1, 8, 2};
int inventory_score[md] = {};
int skip_time = 0;
const char* slot = " ";
int id_slot = 0;
int i = 0;
int slot1 = 0;

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

int main(void){
    
    for(int i = 0; i < md; i++){
        printf("%s, %i\n", slot_name[i], i);
    }
    
    while(1){
        
        printf("--------МЕНЮ--------\n1.Текущее время\n2.Пропуск времени\n3.Показать инвентарь\n4.Поднять предмет\n5.Обнуление слота\n6.Любимый ресурс\n0.Завершить программу\n");
        
        int number = 0;
        scanf("%d", &number);
        
        switch(number)
        {
            case 1 :
                
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
                
            case 2 :
                
                printf("Сколько часов вы хотите пропустить? ");
                scanf("%d", &skip_time);
                current_hour = current_hour + skip_time;
                while (current_hour >= 24) {current_hour = current_hour - 24; current_day += 1;}
                skip_time = 0;
                break;
                
            case 3 :
                
                for(int i = 0; i < md; ++i){
                    
                    printf("Слот[%d]: (%d) (%s)\n", i, inventory[i], slot_name[inventory[i]]);
                    
                }
                break;
                
            case 4 :
                
                printf("Чтобы положить/заменить предмет в слот\nУкажите слот [0 до 9]\n");
                scanf("%d", &slot1);
                printf("Введите id предмета который хотите поднять. Введите 10 чтобы увидеть список\n");
                scanf("%d", &id_slot);
                if (id_slot == md){
                    for(int i = 0; i < md; i++){
                        printf("%i.(%s)\n", i, slot_name[i]);
                    }
                }
                inventory[slot1] = id_slot;
                
                
                break;
                
            case 5 :
                
                printf("Введите номер слота, который хотите обнулить [0 до 9]\n");
                scanf("%d", &id_slot);
                
                inventory[id_slot] = 0;
                id_slot = 0;
                printf("Слот %d обнулён\n", id_slot);
                
                break;
                
            case 6 :
                
                int count[md] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                
                for(int i = 1; i < md; i++){
                    for(int j = 0; j < md; j++){
                        if (inventory[j] == i){
                            count[i] += 1;
                        }
                    }
                }
                
                int max[1] = {count[0], 0};
                
                for(int i = 0; i < md; i++){
                    if (max[0] < count[i]){
                        max[0] = count[i];
                        max[1] = i;
                    }
                        }
                
                if (max[0] == 0){
                    printf("Инвентарь пуст\n");
                }
                else{
                    printf("Любимый ресурс: %s %i шт.\n", slot_name[max[1]], max[0]);
                }
                
                break;

            case 0 :
                
                return 0;
                
            default:
                
                printf("Такого пункта в меню нет.\n");
                break;

        }
    }
}
