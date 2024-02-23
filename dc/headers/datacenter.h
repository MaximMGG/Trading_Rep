#ifndef __DATA_CENTER_H_
#define __DATA_CENTER_H_
#include "../../service/headers/getservice.h"
#include "dbinsert.h"
#include <util/m_string.h>
#include <util/util.h>

typedef enum {
    T_TIME_1 = 1, T_TIME_5 = 5, T_TIME_15 = 15, T_TIME_30 = 30, T_TIME_60 = 60 
}Time;

//take Res_ticker and put it in database and get it to logic service
void data_distributor(Res_ticker *response, Time t);

//initialize database
void data_init();



#endif //__DATA_CENTER_H_
