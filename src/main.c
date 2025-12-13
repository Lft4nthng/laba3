#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "arguments_parser.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(65001);

    Arguments arg = parse_args(argc, argv);

    if(arg.error == 1){
        return 1;
    }
    return 0;
}