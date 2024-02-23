#ifndef _TRADER_ERROR_H_
#define _TRADER_ERROR_H_

#include <util/util.h>
#include <stdlib.h>

#define ERROR_SIZE 200

extern char Trade_error[ERROR_SIZE];
extern i32 Trader_error_line;
extern char Trader_error_func[ERROR_SIZE];
extern char Trader_error_file[ERROR_SIZE];

#define seterror(error) _Trader_set_error((error), __LINE__, (char *)__FUNCTION__, __FILE__)

void _Trader_set_error(const char *t_error, i32 t_error_line, char *t_error_func, char *t_error_file);
char *Trader_get_error();
void Trader_print_error();

#endif //_TRADER_ERROR_H_
