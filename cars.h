#ifndef TRAFFIC_GROUP_CARS_H
#define TRAFFIC_GROUP_CARS_H

#include "types.h"

car* new_car(int entry_time);
void add_to_street(street* st, car* c);
car* pop_off_street(street* st);

#endif //TRAFFIC_GROUP_CARS_H
