#ifndef TIME_H
#define TIME_H

typedef struct {
    int current_hour;
    int current_day;
} Time;

void print_current_time(Time *time);
void time_skip(Time *time);

#endif
