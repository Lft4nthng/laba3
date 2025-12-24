#pragma once

#include "building.h"

typedef struct {
    Building* data;
    unsigned size;
    unsigned capacity;
} Vector;

void vector_init(Vector* v);
void vector_free(Vector* v);
int vector_size(const Vector* v);
Building* vector_get(const Vector* v, const int index);
Building* vector_front(const Vector* v);
Building* vector_back(const Vector* v);
Building* vector_next(const Vector* v, const Building* current);
Building* vector_prev(const Vector* v, const Building* current);
void vector_push_back(Vector* v, const Building* apt);
void vector_insert(Vector* v, const int index, const Building* apt);
void vector_erase(Vector* v, const int index);
void vector_swap(Vector* v, const int i, const int j);
void vector_clear(Vector* v);
void vector_from_array(const Vector* v, const Building* arr, int n);
Building* vector_to_array(const Vector* v);

