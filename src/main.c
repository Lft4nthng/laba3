#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "arguments_parser.h"
#include "vector.h"
#include "building.h"
#include "sorter.h"
#include "inout.h"


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);  

    Vector* v1 = NULL;
    vector_init(v1);

    Arguments arg = parse_args(argc, argv);

    if(arg.error == 1){
        return 1;
    }

    Vector v;
    vector_init(&v);
    
    int result = 0; 

    switch (arg.mode) {
        case MODE_GENERATE: {
            printf("Генерация %d случайных записей...\n", arg.generate_count);
            generate_data(&v, arg.generate_count);
            
            if (vector_size(&v) != arg.generate_count) {
                fprintf(stderr, "Ошибка: сгенерировано %d записей вместо %d\n", 
                        vector_size(&v), arg.generate_count);
                result = 1;
                break;
            }
            
            if (!write_csv(arg.output_file, &v)) {
                fprintf(stderr, "Ошибка записи данных\n");
                result = 1;
            } else {
                printf("Успешно сгенерировано %d записей\n", arg.generate_count);
                if (arg.output_file[0]) {
                    printf("Файл: %s\n", arg.output_file);
                }
            }
            break;
        }

        case MODE_SORT: {
            if (!read_csv(arg.input_file, &v)) {
                fprintf(stderr, "Ошибка чтения файла: %s\n", 
                        arg.input_file[0] ? arg.input_file : "(stdin)");
                result = 1;
                break;
            }
            
            int loaded_count = vector_size(&v);
            printf("Загружено записей: %d\n", loaded_count);
            
            if (loaded_count == 0) {
                fprintf(stderr, "Файл пуст или содержит некорректные данные\n");
                result = 1;
                break;
            }
            
            Comparator cmp = NULL;
            if (arg.sort == 1) {
                printf("Сортировка по возрастанию года...\n");
                cmp = cmp_by_year_asc;
            } else { 
                printf("Сортировка по убыванию года...\n");
                cmp = cmp_by_year_desc;
            }

            if (cmp == NULL) {
                fprintf(stderr, "Ошибка: не выбран компаратор сортировки\n");
                result = 1;
                break;
            }
            
            selection_sort(&v, cmp);

            if (loaded_count > 1) {
                Building* first = vector_get(&v, 0);
                Building* last = vector_get(&v, loaded_count - 1);
                if (arg.sort == 1 && first->year > last->year) {
                    fprintf(stderr, "Предупреждение: данные возможно не отсортированы\n");
                }
            }
            
            if (!write_csv(arg.output_file, &v)) {
                fprintf(stderr, "Ошибка записи отсортированных данных\n");
                result = 1;
            } else {
                printf("Данные успешно отсортированы\n");
                if (arg.output_file[0]) {
                    printf("Файл: %s\n", arg.output_file);
                }
            }
            break;
        }

        case MODE_PRINT: {
            if (arg.input_file[0] == '\0') {
                printf("Введите имя файла для чтения: ");
                char filename[256];
                if (!fgets(filename, sizeof(filename), stdin)) {
                    fprintf(stderr, "Ошибка чтения имени файла\n");
                    result = 1;
                    break;
                }
                filename[strcspn(filename, "\n")] = 0;
                strncpy(arg.input_file, filename, FILE_LEN - 1);
                arg.input_file[FILE_LEN - 1] = '\0';
            }

            if (!read_csv(arg.input_file, &v)) {
                fprintf(stderr, "Ошибка чтения файла: %s\n", arg.input_file);
                result = 1;
                break;
            }
            
            int loaded_count = vector_size(&v);
            printf("Загружено записей: %d\n", loaded_count);
            
            if (loaded_count == 0) {
                fprintf(stderr, "Файл пуст или содержит некорректные данные\n");
                result = 1;
                break;
            }
            
            if (arg.output_file[0]) {
                FILE* out = fopen(arg.output_file, "w");
                if (!out) {
                    fprintf(stderr, "Ошибка открытия файла для записи: %s\n", arg.output_file);
                    result = 1;
                    break;
                }
                print_table(&v, out);
                fclose(out);
                printf("Таблица сохранена в файл: %s\n", arg.output_file);
            } else {
                print_table(&v, stdout);
            }
            break;
        }

        default:
            fprintf(stderr, "Неизвестный режим работы. Используйте --help для справки\n");
            result = 1;
            break;
    }

    vector_free(&v);

    return result;
}
