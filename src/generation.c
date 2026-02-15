#include "generation.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define DEVELOPER_COUNT 5
#define DISTRICTS_COUNT 5

static const char* developers[] = {"Ростстрой", "Главстрой", "Эталон", "ПИК", "Самолет"};
static const char* districts[] = {"Новокосино", "Митино", "Ховрино", "Люберцы", "Бутово"};

Building generate_building(){
    Building apt;
    strncpy(apt.builder, developers[rand() % DEVELOPER_COUNT], NAME_LEN - 1);
    strncpy(apt.neighborhood, districts[rand() % DEVELOPER_COUNT], NAME_LEN - 1);
    apt.type = rand() % 3;
    apt.year = 1985 + rand() % 40;
    apt.elevator = rand() % 2;
    apt.garbage_tunnel = rand() % 2;
    apt.flat_count = 50 + rand() % 200;
    apt.floors_count = 5 + rand() % 25;
    apt.avg_area = 40 + (rand() % 700) / 10.0;
    return apt;
}

void generate_data(Vector* v, unsigned count) {
    if (v == NULL) return;
    srand(time(0));
    for (int i = 0; i < count; i++) {
        Building apt = generate_building();
        vector_push_back(v, &apt);
    }
    return;
}

