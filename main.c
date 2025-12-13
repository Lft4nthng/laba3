#include <stdio.h>
#include <stdlib.h>

#define FILE_LEN 256

typedef enum {
    MODE_GENERATE = 1,
    MODE_SORT,
    MODE_PRINT,
    NONE = 0
} ProgramMode;

int main(int argc, char* argv[]) {
    char* input_file = malloc(FILE_LEN), *output_file = malloc(FILE_LEN);
    ProgramMode mode = 0;
    unsigned char sort = 1;
    int gen_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            mode = MODE_GENERATE;
            if (i + 1 < argc) {
                gen_count = atoi(argv[++i]);
            }
        } else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            mode = MODE_SORT;
        } else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            mode = MODE_PRINT;
        } else if (strcmp(argv[i], "--type=asc") == 0 || strcmp(argv[i], "-t") == 0 || (i + 1 < argc && strcmp(argv[i], "-t") == 0 && strcmp(argv[i+1], "A") == 0)) {
            sort = 1;
            if (strcmp(argv[i], "-t") == 0) i++;
        } else if (strcmp(argv[i], "--type=desc") == 0 || (i + 1 < argc && strcmp(argv[i], "-t") == 0 && strcmp(argv[i+1], "D") == 0)) {
            sort = 0;
            if (strcmp(argv[i], "-t") == 0) i++;
        } else if (strncmp(argv[i], "--out=", 6) == 0) {
            strcpy(output_file, argv[i] + 6);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(output_file, argv[++i]);
        } else if (strncmp(argv[i], "--in=", 5) == 0) {
            strcpy(input_file, argv[i] + 5);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            strcpy(input_file, argv[++i]);
        }
        else{
            puts("Unknown argumet");
            return 1;
        }
    }

    return 0;
}