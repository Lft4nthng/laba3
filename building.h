#pragma once

typedef enum {
    PANEL,
    BRICK,
    MONOLIT
} BuildingType;

typedef enum{True, False} Bool;

typedef struct {
    char builder[100];
    char neighborhood[100];
    BuildingType type;
    int year;
    Bool elevator;
    Bool garbage_tunnel;
    int flat_count;
    int floors_count;
    double avg_area;

} Building;