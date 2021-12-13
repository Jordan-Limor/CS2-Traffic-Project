#ifndef TRAFFIC_GROUP_TYPES_H
#define TRAFFIC_GROUP_TYPES_H

typedef struct car {
    int car_id; // make sure that each car has a unique identifier this way we can trace it through the system
    int entry_time; // record the number of the cycle (engine loop count) when the car entered the system
    int exit_time;  // record the number of the cycle (engine loop count) when the car exits the system
    int entered_street;
    struct car* next_car_ptr;
} car;

// creating the queue for a street type - the header
typedef struct street {
    car *rear_ptr;  // enqueue new cars here
    car *front_ptr;  // dequeue cars leaving the street here
    int maxcarcount; // the number of cars that fill the street
    double service_rate; // this is the number of cycles it takes to process a car
    char street_name[100];
    int num_cars;
} street;

typedef struct road_entrance {
    street* put;
    street* pull;
} road_entrance;

typedef struct intersection {
    road_entrance streets[4];
    int active_streets[2]; // {0, 2} or {1, 3}
    int light_counter; // flip active_streets when light_counter hits 0, then reset light_counter
} intersection;

#endif //TRAFFIC_GROUP_TYPES_H
