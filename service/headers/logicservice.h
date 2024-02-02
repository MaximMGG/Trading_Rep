#ifndef _LOGIC_H_
#define _LOGIC_H_
#include "getservice.h"
#include "tokens.h"
#include "../../lib/m_string.h"
#include "../../lib/m_list.h"

typedef enum {
    BUY, SELL
}Type;

typedef enum {
    TIME_MISTMACH = -2, NOT_CONTEIN = -1, TARGETS_IS_NULL = -3
} target_error;

typedef enum {
    MAYBE_BUY, MAYBE_SELL, EQUALSE, NOTHING
} predict;

typedef struct {
    str *ticker;
    double size;
    double enter_price;
    Type type;
    int time_type;
}Trade;

typedef struct {
    str *ticker;
    double last_price;
    int time_type;
} Target;

//deside to make trade or stop trade, or don't do enithing
void logic_trade_dispetcher(Res_ticker *res, int t);

#endif //_LOGIC_H_
