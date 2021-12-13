#ifndef TRAFFIC_GROUP_STREETS_H
#define TRAFFIC_GROUP_STREETS_H
#include "types.h"

street* new_street(int size, const char* name);
intersection* link_streets(road_entrance north, road_entrance south, road_entrance east, road_entrance west, int start_state[2]);
int is_full(street* st);
void run_cycle(intersection* intersection, int cur_cycle, street* parking);
void print_street(street* st);

#endif //TRAFFIC_GROUP_STREETS_H
