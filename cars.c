#include <stdlib.h>
#include <stdio.h>
#include "cars.h"
#include "streets.h"

int next_car_id = 0;

car* new_car(int time_entrance) {
    car* update = malloc(sizeof(car));
    update->entry_time = time_entrance;
    update->exit_time = -1;
    update->next_car_ptr = NULL;
    update->car_id = next_car_id++;
    return update;
}

void add_to_street(street* st, car* c) {
    if (is_full(st)) {
        printf("Street %s is full\n", st->street_name);
        return;
    }
    if (st->front_ptr == NULL || st->rear_ptr == NULL) {
        st->front_ptr = c;
        st->rear_ptr = c;
        return;
    }
    st->rear_ptr->next_car_ptr = c;
    st->rear_ptr = c;
    st->num_cars++;
}

car* pop_off_street(street* st) {
    car* c = st->front_ptr;
    if (c == NULL) return NULL;
    st->front_ptr = c->next_car_ptr;
    st->num_cars--;
    c->next_car_ptr = NULL;
    if (st->front_ptr == NULL) {
        st->rear_ptr = NULL;
        st->num_cars = 0;
    }
    return c;
}