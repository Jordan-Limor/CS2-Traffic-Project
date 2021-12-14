#include <stdlib.h>
#include <stdio.h>
#include "cars.h"
#include "streets.h"

int next_car_id = 0;

// Faye Van Broeck
car* new_car(int time_entrance) {
    car* update = malloc(sizeof(car));
    update->entry_time = time_entrance;
    update->exit_time = -1;
    update->next_car_ptr = NULL;
    update->car_id = next_car_id++;
    return update;
}
// Aliyah Arruda
void add_to_street(street* st, car* newcar) {
    if (st->front_ptr == NULL || st->rear_ptr == NULL) {
        st->front_ptr = newcar;
        st->rear_ptr = newcar;
        return;

    }
    if (is_full(st)) {
        printf("Street %s is filled", st->street_name);
        return;
    }

    st->rear_ptr->next_car_ptr = newcar;
    st->rear_ptr = newcar;
    st->num_cars += 1;
}

car* pop_off_street(street* st) {

    car* newcar = st->front_ptr;
    if (newcar == NULL) return NULL;
    st->front_ptr = newcar->next_car_ptr;
    st->num_cars -= 1;

    newcar->next_car_ptr = NULL;

    if (st->front_ptr == NULL) {
        st->rear_ptr = NULL;
        st->num_cars = 0;
    }
    return newcar;
}