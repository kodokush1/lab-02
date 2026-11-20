#include "time.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//ТЕКУЩЕЕ ВРЕМЯ
void print_current_time(Time *time) {
    
    printf("Текущее время: День: %d, %d:00\n", time->current_day, time->current_hour);
    
}

//ПРОПУСК ВРЕМЕНИ
void time_skip(Time *time) {
    
    int skip = input_check();
    if (skip < 1) { return; }
    time->current_hour = time->current_hour + skip;
    while (time->current_hour >= 24) { time->current_hour = time->current_hour - 24; time->current_day += 1; }
    
}
