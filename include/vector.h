#pragma once

#include "building.h"

typedef struct {
    Building* data;
    int size;
    int capacity;
} Vector;

void vector_init(Vector* v);
void vector_free(Vector* v);
int vector_size(const Vector* v);
Building* vector_get(const Vector* v, int index);
Building* vector_front(Vector* v);
Building* vector_back(Vector* v);
Building* vector_next(Vector* v, Building* current);
Building* vector_prev(Vector* v, Building* current);
void vector_push_back(Vector* v, const Building* apt);
void vector_insert(Vector* v, int index, const Building* apt);
void vector_erase(Vector* v, int index);
void vector_swap(Vector* v, int i, int j);
void vector_clear(Vector* v);
void vector_from_array(Vector* v, Building* arr, int n);
Building* vector_to_array(const Vector* v);

