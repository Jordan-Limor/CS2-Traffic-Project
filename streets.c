#include <stdlib.h>
#include <libc.h>

#include "streets.h"
#include "cars.h"

#define LIGHT_CYCLE 6

// Maddy Falvey
street* new_street(int size, const char* name) {
    street* new = malloc(sizeof(street));
    new->front_ptr = NULL;
    new->rear_ptr = NULL;
    new->service_rate = 0;
    new->maxcarcount = size;
    new->num_cars = 0;
    memcpy(new->street_name, name, strlen(name)+1);
    return new;
}

intersection* link_streets(road_entrance north, road_entrance south, road_entrance east, road_entrance west, int start_state[2]) {
    intersection* new = malloc(sizeof(intersection));
    memcpy(new->active_streets, start_state, sizeof(int[2]));
    new->streets[0] = north;
    new->streets[1] = east;
    new->streets[2] = south;
    new->streets[3] = west;
    new->light_counter = LIGHT_CYCLE;
    return new;
}

int is_full(street* st) {
    return (st->num_cars == st->maxcarcount);
}

// Faye Van Broeck
void print_street(street* st) {
    for (int i = 0; i < st->maxcarcount - st->num_cars; i++) {
        printf(". ");
    }
    if (st->num_cars == 0) {
        return;
    }
    for (int i = 0; i < st->num_cars; i++) {
        printf("~ ");
    }
    printf("\n");
}
// The run cycle functions purpose is to run 1 intersection per cycle
// Brandon Fontaine
void run_cycle(intersection* intersection, int cur_cycle, street* parking) {
    street* all_streets[4];

    int null_exits = 0; //null_exits is how many null exits, exits simulation if ncount is 4

    for (int direction = 0; direction < 4; direction++) {
        //Runs 4 times because were testing 4 street entrances, some exits dont exist, N,S,E,W
        all_streets[direction] = intersection->streets[direction].put;
        if (all_streets[direction] == NULL) null_exits++;
    }
    for (int active_check = 0; active_check < 2; active_check++) {
        // Runs twice because were checking if street is active or not

        int s = intersection->active_streets[active_check]; //active streets are streets we can pull from
        street* from = intersection->streets[s].pull;// s will be 0,2 OR 1,3


        if (from) { //from is the variable that were pulling cars from. If a car wants to move, then run.

            if (null_exits == 4) {
                // this intersection has no exits; remove the car from the simulation
                if (from->front_ptr) {
                    car *c = pop_off_street(from);
                    from->service_rate += (cur_cycle - c->entered_street);
                    from->service_rate /= 2;
                    c->exit_time = cur_cycle;
                    printf("Car %d exiting from %s from simulation.\n", c->car_id, from->street_name);
                    add_to_street(parking, c);
                }
                return;
            }

            street* dest = NULL;
            while (dest == NULL) {
                dest = all_streets[rand()%4];//generate a random direction
            }

            // When the street is not full and a car is contained at front_ptr, pop from source and push to dest.
            if (!is_full(dest) && from->front_ptr) {
                car *c = pop_off_street(from);
                from->service_rate += (cur_cycle - c->entered_street);
                from->service_rate /= 2;
                c->entered_street = cur_cycle;
                add_to_street(dest, c);
                printf("Car %d Going from %s to %s\n", c->car_id, from->street_name, dest->street_name);
            }
        }
    }
    intersection->light_counter--;
    if (intersection->light_counter == 0) {
        intersection->light_counter = LIGHT_CYCLE;
        if (intersection->active_streets[0] == 0) {
            intersection->active_streets[0] = 1;
            intersection->active_streets[1] = 3;
        } else {
            intersection->active_streets[0] = 0;
            intersection->active_streets[1] = 2;
        }
    }
}