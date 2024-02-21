#ifndef _CANDLE_H_
#define _CANDLE_H_

#include <util/util.h>
#include <util/m_string.h>
#include "../../trader/headers/trader.h"

typedef enum {
    C_MIN_1 = 1, C_MIN_5 = 5, C_MIN_15 = 15, C_MIN_30 = 30, C_MIN_60 = 60
} Trade_time;

typedef enum {
    QUOTE_OK, QUOTE_UD, QUOTE_ERROR
} QUOTE_CODE;


typedef struct {
    double max_value;
    double min_value;
    double open_price;
    double current_price;
    double value;
    Trade_time c_time;
} Candle;

// typedef struct {
//
// } Tamplate;

typedef struct Quotes{
    Candle **candles;
    u32 size;
    Trade_time t;
    void (*strategy) (struct Quotes *q);

    str *ticker;
} Quotes;

Candle Candle_new(  double max_value, 
                    double min_value, 
                    double open_price, 
                    double current_price, 
                    double value, 
                    Trade_time c_time);

Quotes *Quotes_create(Trade_time t, void (*strategy) (Quotes *q));
QUOTE_CODE Quotes_add_candle(Quotes *q, Candle *c);
QUOTE_CODE Quotes_action(Quotes *q, Trade *trade);



void Quotes_destroy(Quotes *q);




#endif //_CANDLE_H_
