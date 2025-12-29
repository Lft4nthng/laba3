#include "generation.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>


void generate_data(Vector* v, unsigned count) {
    const char* developers[] = {"Ростстрой", "Главстрой", "Эталон", "ПИК", "Самолет"};
    const char* districts[] = {"Новокосино", "Митино", "Ховрино", "Люберцы", "Бутово"};
    srand(time(0));

    for (int i = 0; i < count; i++) {
        Building apt;
        strncpy(apt.builder, developers[rand() % 5], NAME_LEN - 1);
        strncpy(apt.neighborhood, districts[rand() % 5], NAME_LEN - 1);
        apt.type = rand() % 3;
        apt.year = 1985 + rand() % 40;
        apt.elevator = rand() % 2;
        apt.garbage_tunnel = rand() % 2;
        apt.flat_count = 50 + rand() % 200;
        apt.floors_count = 5 + rand() % 25;
        apt.avg_area = 40 + (rand() % 700) / 10.0;

        vector_push_back(v, &apt);
    }
}