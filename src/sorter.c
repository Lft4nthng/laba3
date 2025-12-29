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

    if(a->elevator != b->elevator) return a->elevator - b->elevator;

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