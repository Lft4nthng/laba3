#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 10

void vector_init(Vector* v) {
    if(v == NULL) return;
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_free(Vector* v) {
    if(v == NULL) return;
    free(v->data);
    v->data = NULL;
    v->size = v->capacity = 0;
}

int vector_size(const Vector* v) {
    if(v == NULL) return 0;
    return v->size;
}

Building* vector_get(const Vector* v, int index) {
    if (v == NULL || index < 0 || index >= v->size) return NULL;
    return &v->data[index];
}

Building* vector_front(const Vector* v) {
    if(v == NULL) return NULL;
    return vector_get(v, 0);
}

Building* vector_back(const Vector* v) {
    if(v == NULL) return NULL;
    return vector_get(v, v->size - 1);
}

Building* vector_next(const Vector* v, const Building* current) {
    if (v == NULL ||current == NULL || current - v->data >= v->size - 1) return NULL;
    return current + 1;
}

Building* vector_prev(const Vector* v, const Building* current) {
    if (v == NULL || current == NULL || current - v->data <= 0) return NULL;
    return current - 1;
}

static void resize(Vector* v, const int new_capacity) {
    if(v == NULL) return;
    Building* new_data = realloc(v->data, new_capacity * sizeof(Building));
    if (new_data) {
        v->data = new_data;
        v->capacity = new_capacity;
    }
    return;
}

void vector_push_back(Vector* v, const Building* build) {
    if(v == NULL) return;
    if (v->size >= v->capacity) {
        int new_cap = (v->capacity == 0) ? INIT_CAPACITY : v->capacity * 2;
        resize(v, new_cap);
    }
    v->data[v->size++] = *build;
    return;
}

void vector_insert(Vector* v, const int index, const Building* build) {
    if (v == NULL || index < 0 || index > v->size) return;
    if (v->size >= v->capacity) {
        int new_cap = (v->capacity == 0) ? INIT_CAPACITY : v->capacity * 2;
        resize(v, new_cap);
    }
    memmove(&v->data[index + 1], &v->data[index], (v->size - index) * sizeof(Building));
    v->data[index] = *build;
    v->size++;
}

void vector_erase(Vector* v, const int index) {
    if (v == NULL || index < 0 || index >= v->size) return;
    memmove(&v->data[index], &v->data[index + 1], (v->size - index - 1) * sizeof(Building));
    v->size--;
}

void vector_swap(Vector* v, const int i, const int j) {
    if (v == NULL || i < 0 || i >= v->size || j < 0 || j >= v->size) return;
    Building temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_clear(Vector* v) {
    if(v == NULL) return;
    v->size = 0;
}

void vector_from_array(const Vector* v, const Building* arr, int n) {
    if(v == NULL) return;
    vector_clear(v);
    for (int i = 0; i < n; i++) {
        vector_push_back(v, &arr[i]);
    }
}

Building* vector_to_array(const Vector* v) {
    if(v == NULL) return NULL;
    Building* arr = malloc(v->size * sizeof(Building));
    if (arr) {
        memcpy(arr, v->data, v->size * sizeof(Building));
    }
    return arr;
}