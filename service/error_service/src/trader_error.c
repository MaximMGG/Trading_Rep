#include <string.h>
#include <stdio.h>

#include "../headers/trader_error.h"

char Trader_error[ERROR_SIZE];
i32 Trader_error_line;
char Trader_error_func[ERROR_SIZE];
char Trader_error_file[ERROR_SIZE];

char Trader_error_message[ERROR_SIZE * 2 + 24];

void _Trader_set_error(const char *t_error, i32 t_error_line, char *t_error_func, char *t_error_file) {
    Trader_error_line = t_error_line;
    strcpy(Trader_error, t_error);
    strcpy(Trader_error_func, t_error_func);
    strcpy(Trader_error_file, t_error_file);
}

char *Trader_get_error() {
    char *error_fmt = "File - %s, func - %s, line - %d, ->> %s";
    snprintf(Trader_error_message, ERROR_SIZE * 2 + 24, error_fmt, 
                                Trader_error_file, 
                                Trader_error_func, 
                                Trader_error_line,
                                Trader_error);
    return Trader_error_message;
}

void Trader_print_error() {
    fprintf(stderr, "%s\n", Trader_get_error());
}
