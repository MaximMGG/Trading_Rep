#ifndef _CANDLE_H_
#define _CANDLE_H_

#include <util/util.h>
#include <util/m_string.h>
#include "../../service/error_service/headers/trader_error.h"

#define NEW_CANDLE 1
#define SAME_CANDLE 0

typedef enum {
    C_MIN_1 = 1, C_MIN_5 = 5, C_MIN_15 = 15, C_MIN_30 = 30, C_MIN_60 = 60
} Trade_time;



typedef struct {
    double max_value;
    double min_value;
    double open_price;
    double close_price;
    double last_price;
    long open_time;
    Trade_time c_time;
} Candle;

// typedef struct {
//
// } Tamplate;

Candle *Candle_new( double open_price, 
                    long open_time,
                    Trade_time c_time);

i32 Candle_check_time(Candle *f, Candle *second, Trade_time t);

void Candle_free(Candle *c);


#endif //_CANDLE_H_
