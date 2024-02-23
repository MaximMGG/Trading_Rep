#ifndef _QUOTE_H_
#define _QUOTE_H_
#include "candle.h"
#include "../../trader/headers/trader.h"
#include <util/m_list.h>

typedef enum {
    QUOTE_OK = 1, QUOTE_ERROR = -1, QUOTE_NONE
} QUOTE_CODE;


typedef struct Quotes{
    Candle **candles;
    u32 candle_size;
    u32 max_candle_size;

    Trade_time t;
    i32 (*strategy) (struct Quotes *q);
    Trade *trade;

    List *trades;
    str *ticker;
} Quotes;

Quotes *Quotes_create(Trade_time t, i32 (*strategy) (Quotes *q), str *ticker);
QUOTE_CODE Quotes_add_candle(Quotes *q, Candle *c);
QUOTE_CODE Quotes_update_lastcandle(Quotes *q, Candle *c);
//checking strategy, if true, do trade
QUOTE_CODE Quotes_action(Quotes *q);
void Quotes_destroy(Quotes *q);

#endif //_QUOTE_H_
