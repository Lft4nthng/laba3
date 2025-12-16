#include "inout.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int read_csv(const char* filename, Vector* v) {
    FILE* f = filename[0] ? fopen(filename, "r") : stdin;
    if (!f) return 0;

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        Building apt = {0};
        char type_str[50];
        char elevator[10], garbage[10];
        if (sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%d,%lf", apt.builder, apt.neighborhood, type_str, &apt.year,elevator, garbage, &apt.flat_count, &apt.floors_count, &apt.avg_area) == 9) {
            apt.type = str_to_build(type_str);
            apt.elevator = (strcmp(elevator, "YES") == 0);
            apt.garbage_tunnel = (strcmp(garbage, "YES") == 0);
            vector_push_back(v, &apt);
        }
    }

    if (f != stdin) fclose(f);
    return 1;
}

int write_csv(const char* filename, const Vector* v) {
    FILE* f = filename[0] ? fopen(filename, "w") : stdout;
    if (!f) return 0;

    for (int i = 0; i < vector_size(v); i++) {
        Building* apt = vector_get(v, i);
        fprintf(f, "%s,%s,%s,%d,%s,%s,%d,%d,%.2f\n", apt->builder, apt->neighborhood, build_to_str(apt->type), apt->year, apt->elevator ? "YES" : "NO", apt->garbage_tunnel ? "YES" : "NO", apt->flat_count, apt->floors_count, apt->avg_area);
    }

    if (f != stdout) fclose(f);
    return 1;
}

void print_table(const Vector* v, FILE* out) {
    fprintf(out, "%-20s%-15s %-12s %4s %3s %3s %5s %4s %8s\n", "Застройщик |", "Микрорайон", "Тип", "Год", "ЛФ", "МП", "Кварт", "Эт", "Площадь");
    fprintf(out, "--------------------------------------------------------------------------------\n");

    for (int i = 0; i < vector_size(v); i++) {
        Building* apt = vector_get(v, i);
        fprintf(out, "%-20s %-15s %-12s %4d %3s %3s %5d %4d %8.2f\n", apt->builder, apt->neighborhood, build_to_str(apt->type), apt->year, apt->elevator ? "YES" : "NO", apt->garbage_tunnel ? "YES" : "NO", apt->flat_count,
                apt->floors_count,
                apt->avg_area);
    }
}

void generate_data(Vector* v, int count) {
    const char* developers[] = {"Ростстрой", "Главстрой", "Эталон", "ПИК", "Самолет"};
    const char* districts[] = {"Новокосино", "Митино", "Ховрино", "Люберцы", "Бутово"};
    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        Building apt;
        strcpy(apt.builder, developers[rand() % 5]);
        strcpy(apt.neighborhood, districts[rand() % 5]);
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