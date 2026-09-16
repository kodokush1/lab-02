#include <stdio.h>
#include <stdlib.h>

int current_day = 1;
int current_hour = 8;
const char* inventory[10] = {"Пусто", "Дерево", "Камень", "Семена", "Дерево", "Железо", "Кирка", "Ведро", "Дерево", "Мотыга"};
int skip_time = 0;
const char* slot = " ";
int i = 0;
int id_slot = 0;

int main(void){
    
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
                
                for(int i = 0; i < 10; ++i){
                    printf("Слот[%d]: %s \n", i, inventory[i]);
            
                }
                break;
            case 4 :

                break;
                
            case 5 :
                
                printf("Введите номер слота, который хотите обнулить\n");
                scanf("%d", &id_slot);
                inventory[id_slot] = "Пусто";
                id_slot = 0;
                break;
                
            case 6 :
                printf("Задание по варианту\n");
                break;

            case 0 :
                return 0;

        }
    }
}
