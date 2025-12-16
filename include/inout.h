#pragma once
#include "vector.h"
#include <stdio.h>

int read_csv(const char* filename, Vector* v);
int write_csv(const char* filename, const Vector* v);

void print_table(const Vector* v, FILE* out);

void generate_data(Vector* v, int count);
