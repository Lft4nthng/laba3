#include "building.h"
#include <stdio.h>
#include <string.h>

static const char** str = {"панельный", "кирпичный", "монолитный", "неизвестно"};

const char* build_to_str(BuildingType type) {
    return str[type];
}

BuildingType str_to_build(const char* str) {
    for(int i = 0; i < 3; ++i) if (strcmp(str, str[i]) == 0) return (BuildingType)i;
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