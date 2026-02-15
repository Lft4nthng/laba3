#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "vector.h"
#include "sorter.h"
#include "generation.h"

double get_time_ms() {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000.0 / (double)frequency.QuadPart;
}

Vector copy_vector(Vector* src) {
    Vector dest;
    vector_init(&dest);
    for (int i = 0; i < vector_size(src); i++) {
        Building* b = vector_get(src, i);
        vector_push_back(&dest, b);
    }
    return dest;
}

double check_selection_sort(Vector* v) {
    Vector test_vec = copy_vector(v);
    double start = get_time_ms();
    selection_sort(&test_vec, cmp_by_all_asc);
    double end = get_time_ms();
    vector_free(&test_vec);
    return end - start;
}

double check_quick_sort(Vector* v) {
    Vector test_vec = copy_vector(v);
    double start = get_time_ms();
    quick_sort(&test_vec, cmp_by_all_asc);
    double end = get_time_ms();
    vector_free(&test_vec);
    return end - start;
}

int main() {
    FILE* results = fopen("tests.csv", "w");
    
    int sizes[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 7500, 10000, 15000, 20000, 30000, 40000, 50000,100000,150000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        
        Vector data;
        vector_init(&data);
        generate_data(&data, size);
        
        double sel_time = check_selection_sort(&data);
        double quick_time = check_quick_sort(&data);
        
        fprintf(results, "%d,%.3f,%.3f\n", size, sel_time, quick_time);
        
        vector_free(&data);
    }
    
    fclose(results);
    return 0;
}