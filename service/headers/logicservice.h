#ifndef _LOGIC_H_
#define _LOGIC_H_
#include "getservice.h"
#include "tokens.h"
#include <util/m_list.h>
#include <util/m_string.h>

typedef enum {
    BUY, SELL, NONE
}Type;

typedef enum {
    TIME_MISTMACH = -2, NOT_CONTEIN = -1, TARGETS_IS_NULL = -3
} target_error;

typedef enum {
    MAYBE_BUY, MAYBE_SELL, EQUALSE, NOTHING, ON_LONG_TRADE, ON_SHORT_TRADE
} predict;

typedef struct {
    double size;
    double enter_price;
    Type type;
}Trade;

typedef struct {
    str *ticker;
    double last_price;
    int time_type;
    int lose_count;
    Trade *trade;
    Type last_trade;
    predict predict;
} Target;

typedef struct {
    double total;
    double start_trade_size;
} DEPOSIT;

//create user deposit and couted trade size
DEPOSIT *logic_create_deposit(double total, int devide_step);

//deside to make trade or stop trade, or don't do enithing
void logic_trade_dispetcher(Res_ticker *res, int t);

#endif //_LOGIC_H_
