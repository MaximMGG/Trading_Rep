#ifndef _CANDLE_H_
#define _CANDLE_H_

#include <util/util.h>
#include <util/m_string.h>
#include "../../trader/headers/trader.h"
#include "../../service/error_service/headers/trader_error.h"

typedef enum {
    C_MIN_1 = 1, C_MIN_5 = 5, C_MIN_15 = 15, C_MIN_30 = 30, C_MIN_60 = 60
} Trade_time;

typedef enum {
    QUOTE_OK, QUOTE_UD, QUOTE_ERROR = -1, QUOTE_MALLOC_ERROR
} QUOTE_CODE;


typedef struct {
    double max_value;
    double min_value;
    double open_price;
    long open_time;
    double current_price;
    double value;
    Trade_time c_time;
} Candle;

// typedef struct {
//
// } Tamplate;

typedef struct Quotes{
    Candle **candles;
    u32 candle_size;
    u32 max_candle_size;

    Trade_time t;
    i32 (*strategy) (struct Quotes *q);
    Trade *trader;

    str *ticker;
} Quotes;

Candle Candle_new(  double max_value, 
                    double min_value, 
                    double open_price, 
                    long open_time,
                    double current_price, 
                    double value, 
                    Trade_time c_time);

i32 Candle_check_time(Candle *f, Candle *second, Trade_time t);
Quotes *Quotes_create(Trade_time t, i32 (*strategy) (Quotes *q), str *ticker);
QUOTE_CODE Quotes_add_candle(Quotes *q, Candle *c);
QUOTE_CODE Quotes_update_lastcandle(Quotes *q, Candle *c);
//checking strategy, if true, do trade
QUOTE_CODE Quotes_action(Quotes *q, Trade *trade);

void Candle_free(Candle *c);
void Quotes_destroy(Quotes *q);


#endif //_CANDLE_H_
