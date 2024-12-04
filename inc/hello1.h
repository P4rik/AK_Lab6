#ifndef HELLO1_H
#define HELLO1_H

struct greeting_data {
    struct list_head list;
    ktime_t time_start;
    ktime_t time_end;
};

void greetings(int count);

#endif
