#pragma once

#define FILE_LEN 256

typedef enum {
    MODE_GENERATE = 1,
    MODE_SORT,
    MODE_PRINT,
    MODE_NONE
} ProgramMode;

typedef struct {
    ProgramMode mode;
    unsigned char sort;
    int generate_count;
    char input_file[FILE_LEN];
    char output_file[FILE_LEN];
    unsigned char error;
} Arguments;

Arguments parse_args(int argc, char* argv[]);

