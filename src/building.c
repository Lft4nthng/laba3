#include "building.h"
#include <stdio.h>
#include <string.h>

const char* build_to_str(BuildingType type) {
    switch (type) {
        case PANEL: return "панельный";
        case BRICK: return "кирпичный";
        case MONOLIT: return "монолитный";
        default: return "неизвестно";
    }
}

BuildingType str_to_build(const char* str) {
    if (strcmp(str, "панельный") == 0) return PANEL;
    if (strcmp(str, "кирпичный") == 0) return BRICK;
    if (strcmp(str, "монолитный") == 0) return MONOLIT;
    return NONE; 
}

void print_building(const Building* build) {
    printf("Застройщик: %s\n", build->builder);
    printf("Микрорайон: %s\n", build->neighborhood);
    printf("Тип: %s\n", build_to_str(build->type));
    printf("Год постройки: %d\n", build->year);
    printf("Лифт: %s\n", build->elevator ? "YES" : "NO");
    printf("Мусоропровод: %s\n", build->garbage_tunnel ? "YES" : "NO");
    printf("Квартир: %d\n", build->flat_count);
    printf("Этажей: %d\n", build->floors_count);
    printf("Ср. площадь: %.2f\n", build->avg_area);
}