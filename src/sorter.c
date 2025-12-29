#include "sorter.h"
#include <math.h>
#include <string.h>

void selection_sort(Vector* v, Comparator cmp) {
    int n = vector_size(v);
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (cmp(vector_get(v, j), vector_get(v, min_idx)) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            vector_swap(v, i, min_idx);
        }
    }
}
static int segmentation(Vector* v, Comparator cmp, int low, int high) {
    void* pivot = vector_get(v, high);
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (cmp(vector_get(v, j), pivot) <= 0) {
            ++i;
            if (i != j) {
                vector_swap(v, i, j);
            }
        }
    }
    if (i + 1 != high) {
        vector_swap(v, i + 1, high);
    }
    return i + 1;
}

static void quick_sort_rec(Vector* v, Comparator cmp, int low, int high) {
    if (low < high) {
        int pivot_index = segmentation(v, cmp, low, high);
        quick_sort_rec(v, cmp, low, pivot_index - 1);
        quick_sort_rec(v, cmp, pivot_index + 1, high);
    }
}

void quick_sort(Vector* v, Comparator cmp) {
    int size = vector_size(v);
    if (size <= 1) return;
    quick_sort_rec(v, cmp, 0, size - 1);
}

int cmp_by_year_asc(const Building* a, const Building* b) {
    return (int)a->year - (int)b->year;
}

int cmp_by_year_desc(const Building* a, const Building* b) {
    return (int)b->year - (int)a->year;
}

int cmp_by_flat_count_asc(const Building* a, const Building* b) {
    return (int)a->flat_count - (int)b->flat_count;
}
int cmp_by_all_asc(const Building* a, const Building* b) {
    if (a->year != b->year) return (int)a->year - (int)b->year;

    if(fabs(a->avg_area - b->avg_area) > 0.009) return (a->avg_area > b->avg_area) ? 1 : -1;

    if (a->flat_count != b->flat_count) return (int)a->flat_count - (int)b->flat_count;
    
    if (a->floors_count != b->floors_count) return (int)a->floors_count - (int)b->floors_count;

    if (a->type != b->type) return (int)(a->type - b->type);

    if(a->elevator != b->elevator) return (int)(a->elevator - b->elevator);

    if(a->garbage_tunnel != b ->garbage_tunnel) return (int)(a->garbage_tunnel - b->garbage_tunnel);

    return 0;
}


int cmp_by_all_desc(const Building* a, const Building* b) {
    if (a->year != b->year) return (int)b->year - (int)a->year;

    if(fabs(a->avg_area - b->avg_area) > 0.009) return (b->avg_area > a->avg_area) ? 1 : -1;

    if (a->flat_count != b->flat_count) return (int)b->flat_count - (int)a->flat_count;
    
    if (a->floors_count != b->floors_count) return (int)b->floors_count - (int)a->floors_count;

    if (a->type != b->type) return (int)(b->type - a->type);

    if(a->elevator != b->elevator) return (int)(b->elevator - a->elevator);

    if(a->garbage_tunnel != b ->garbage_tunnel) return (int)(b->garbage_tunnel - a->garbage_tunnel);

    return 0;
}