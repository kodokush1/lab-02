#include <stdio.h>
#include <stdlib.h>

int current_day = 1;
int current_hour = 8;
int inventory = {10};
int skip_time = 0;

int main(){
    
    while(1){
        
        int i = 0;
        scanf("%d", &i);
        
        switch(i)
        {
            case 1 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 2 :
                printf("Ск2олько часов вы хотите пропустить? ");
                scanf("%d", &skip_time);
                current_hour = current_hour + skip_time;
                while (current_hour >= 24) {current_hour = current_hour - 24; current_day += 1;}
                skip_time = 0;
                break;
            case 3 :
                break;
            case 4 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 5 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 6 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 7 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 8 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 9 :
                printf("Текущее время: День: %d, %d:00\n", current_day, current_hour);
                break;
            case 0 :
                return 0;

        }
    }
}
