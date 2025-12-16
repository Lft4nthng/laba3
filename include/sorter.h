#pragma once
#include "vector.h"

typedef int (*Comparator)(const Building* a, const Building* b);

void selection_sort(Vector* v, Comparator cmp);
int cmp_by_year_asc(const Building* a, const Building* b);
int cmp_by_year_desc(const Building* a, const Building* b);
int cmp_by_flat_count_asc(const Building* a, const Building* b);

