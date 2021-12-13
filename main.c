#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "streets.h"
#include "types.h"
#include "cars.h"

/*  Maddy made the map        Dorrance
                                 ^          W
[0] < (2) -[1]- Weybosset -(1) >[2]        N S
            |                    |          E
            |                    |
            Page (1)            (1)
            |                    |
            v                    |
[3] < (2) -[4]- - - - pine (1) -[5]
            |                    |
           (2)                  (2)
            v                    v
           [6]                  [7]
                              Dorrance
*/

int main() {
    street* weybosset_N1 = new_street(10, "Weybosset North 1");
    street* weybosset_N2 = new_street(10, "Weybosset North 2");
    street* weybosset_S1 = new_street(10, "Weybosset South 1");
    street* weybosset_S2 = new_street(10, "Weybosset South 2");
    street* page_E1 = new_street(10, "Page East 1");
    street* page_E2 = new_street(10, "Page East 2");
    street* pine_N1 = new_street(10, "Pine North 1");
    street* pine_N2 = new_street(10, "Pine North 2");
    street* dorrance_W1 = new_street(10, "Dorrance West 1");
    street* dorrance_W2 = new_street(10, "Dorrance West 2");
    street* dorrance_E1 = new_street(10, "Dorrance East 1");
    street* dorrance_E2 = new_street(10, "Dorrance East 2");
    street* all_streets[] = {
            weybosset_N1,
            weybosset_N2,
            weybosset_S1,
            weybosset_S2,
            page_E1,
            page_E2,
            pine_N1,
            pine_N2,
            dorrance_W1,
            dorrance_W2,
            dorrance_E1,
            dorrance_E2
    };
    street* entrances[] = {
            weybosset_S2,
            weybosset_N1,
            dorrance_W2,
            dorrance_E1
    };
    int rates[] = { // Cars per 1 cycle (second)
            5, // every 5 cycles
            5, // every 5 cycles
            2, // every 2 cycles
            2  // every 2 cycles
    };
    intersection* all_intersections[8];
    all_intersections[0] = link_streets(
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, weybosset_N2},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (int[2]){0,2});
    all_intersections[1] = link_streets(
            (road_entrance){weybosset_N2, weybosset_S2},
            (road_entrance){weybosset_S1, weybosset_N1},
            (road_entrance){page_E1, NULL},
            (road_entrance){NULL, NULL},
            (int[2]){0,2});
    all_intersections[2] = link_streets(
            (road_entrance){weybosset_N1, weybosset_S1},
            (road_entrance){NULL, NULL},
            (road_entrance){dorrance_E1, dorrance_W1},
            (road_entrance){NULL, NULL},
            (int[2]){0,2});
    all_intersections[3] = link_streets(//maddy is doing this
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, pine_N2},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (int[2]){0,2});
    all_intersections[4] = link_streets(//faye is doing this
            (road_entrance){pine_N2, NULL},
            (road_entrance){NULL, pine_N1},
            (road_entrance){page_E2, NULL},
            (road_entrance){NULL, page_E1},
            (int[2]){0,2});
    all_intersections[5] = link_streets( // maddy is doing this
            (road_entrance){pine_N1, NULL},
            (road_entrance){NULL, NULL},
            (road_entrance){dorrance_E2, dorrance_W2},
            (road_entrance){dorrance_W1, dorrance_E1},
            (int[2]){0,2});
    all_intersections[6] = link_streets( // maddy is doing this
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, page_E2},
            (int[2]){0,2});
    all_intersections[7] = link_streets(// maddy is doing this
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, NULL},
            (road_entrance){NULL, dorrance_E2},
            (int[2]){0,2});

    // Jordan wrote to following to combine group code
    street* parking = new_street(-1, "Parking");
    int cycle = 0;
    while(1) {
        for (int i = 0; i < (sizeof(rates) / sizeof(int)); i++) {
            // loop over all rates, adding cars (every 10)
            if (cycle % rates[i] == 0) {
                car* new = new_car(cycle);
                add_to_street(entrances[i], new);
            }
        }
        for (int i = 0; i < 8; i++) {
            run_cycle(all_intersections[i], cycle, parking);
        }
        cycle++;
        if (cycle % 10 == 0) {
            // do this every 10 cycles (10 seconds)
            // traverse running cars, find finished cars, and free
            printf("\x1b[2J");
            car* c;
            printf("Finished Cars:\n");
            while((c = pop_off_street(parking))) {
                printf("\tCar %d: start=%d, end=%d\n", c->car_id, c->entry_time, c->exit_time);
                free(c);
            }
        }
        if (cycle % 100 == 0) {
            // do this every 100 cycles (100 seconds)
            // loop over all streets and print service times
            for (int i = 0; i < (sizeof(all_streets) / sizeof(street*)); i++) {
                printf("Street %s Service Time: %.2f\n", all_streets[i]->street_name, all_streets[i]->service_rate);
            }
        }
        sleep(1);
    }
    return 0;
}