#pragma once

typedef enum {
    PANEL = 1,
    BRICK,
    MONOLIT,
    NONE 
} BuildingType;

typedef enum{True = 1, False = 0} Bool;

typedef struct {
    char builder[128];
    char neighborhood[128];
    BuildingType type;
    unsigned short year;
    Bool elevator;
    Bool garbage_tunnel;
    unsigned short flat_count;
    unsigned short floors_count;
    double avg_area;
} Building;


void print_building(const Building* build);
const char* build_to_str(BuildingType type);
BuildingType str_to_build(const char* str);