#pragma once

#define NAME_LEN 128

typedef enum {
    PANEL = 0,
    BRICK = 1,
    MONOLIT = 2,
    NONE = 3
} BuildingType;

typedef enum{True = 1, False = 0} Bool;

typedef struct {
    char builder[NAME_LEN];
    char neighborhood[NAME_LEN];
    BuildingType type;
    unsigned short year;
    Bool elevator;
    Bool garbage_tunnel;
    unsigned short flat_count;
    unsigned short floors_count;
    float avg_area;
} Building;


void print_building(const Building* build);
const char* build_to_str(BuildingType type);
BuildingType str_to_build(const char* str);