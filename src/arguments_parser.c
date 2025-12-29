#include "arguments_parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static void print_help() {
    puts("Режимы (обязательно указать один):");
    puts("  -g, --generate N - Сгенерировать N случайных записей");
    puts("  -s, --sort - Сортировать данные");
    puts("  -P, --print - Вывести данные в виде таблицы\n");
    puts("  -i, --in=FILE - Входной файл (для --sort, --print)");
    puts("  -o, --out=FILE - Файл вывода");
    puts("  -t A|D, --type=asc|desc - Порядок сортировки");
}

Arguments parse_args(int argc, char* argv[]) {
    Arguments args;
    args.mode = MODE_NONE;
    args.sort = 1;
    args.generate_count = 0;
    args.input_file[0] = '\0';
    args.output_file[0] = '\0';
    args.error = 0;

    if (argc == 1) { //нету аргументов
        print_help();
        args.error =  1;
        return args;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (args.mode != MODE_NONE){
                puts("Можно выбрать только один режим");
                args.error = 1;
                return args;
            }
            args.mode = MODE_GENERATE;
            if (i + 1 < argc) {
                args.generate_count = atoi(argv[++i]);
                if(args.generate_count <= 0){
                    puts("Число для генерации должно быть положителльным");
                    args.error = 1;
                    return args;
                }
            }
            else{
                puts("Необходимо ввести число для генерации");
                args.error = 1;
                return args;
            }
        } else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            if (args.mode != MODE_NONE){
                puts("Можно выбрать только один режим");
                args.error = 1;
                return args;
            }
            args.mode = MODE_SORT;
        } else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            if (args.mode != MODE_NONE){
                puts("Можно выбрать только один режим");
                args.error = 1;
                return args;
            }
            args.mode = MODE_PRINT;
        } else if (strcmp(argv[i], "--type=asc") == 0) {
            args.sort = 1;
            if (strcmp(argv[i], "-t") == 0) ++i;
        } else if (strcmp(argv[i], "--type=desc") == 0) {
            args.sort = 0;
            if (strcmp(argv[i], "-t") == 0) ++i;
        } else if(strcmp(argv[i], "-t") == 0){
            if (i + 1 >= argc){
                puts("Нет аргумента после -t");
                args.error = 1;
                return args;
            }
            if (strcmp(argv[i + 1], "D") == 0){
                args.sort = 0;
                ++i;
            }
            else if (strcmp(argv[i + 1], "A") == 0){
                args.sort = 1;
                ++i;
            }
            else{
                puts("Неизвестный аргумент после -t");
                args.error = 1;
                return args;
            }
        } else if (strncmp(argv[i], "--out=", 6) == 0) {
            if (*(argv[i] + 6) == '\0') {
                puts("Ошибка: пустое имя файла после --out=");
                args.error = 1;
                return args;
            }
            strncpy(args.output_file, argv[i] + 6, sizeof(args.output_file) - 1);
            args.output_file[sizeof(args.output_file) - 1] = '\0';
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc){
                puts("Нет аргумента после -o");
                args.error = 1;
                return args;
            }
            stnrcpy(args.output_file, argv[++i], sizeof(args.output_file) - 1);
            args.output_file[sizeof(args.output_file) - 1] = '\0';
        } else if (strncmp(argv[i], "--in=", 5) == 0) {
            if (*(argv[i] + 5) == '\0') {
                puts("Ошибка: пустое имя файла после --im=");
                args.error = 1;
                return args;
            }
            strncpy(args.input_file, argv[i] + 5, sizeof(args.input_file) - 1);
            args.input_file[sizeof(args.input_file) - 1] = '\0';
        } else if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 >= argc){
                puts("Нет аргумента после -i");
                args.error = 1;
                return args;
            }
            strncpy(args.input_file, argv[++i], sizeof(args.input_file) - 1);
            args.input_file[sizeof(args.input_file) - 1] = '\0';
        }
        else{
            printf("Unknown argument %s", argv[i]);
            args.error =1;
            return args;
        }
    }

    if (args.mode == MODE_NONE) {
        puts("Ошибка: не указан режим работы");
        args.error = 1;
        return args;
    }

    return args;
}

