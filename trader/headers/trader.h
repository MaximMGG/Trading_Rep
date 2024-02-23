#ifndef _TRADER_H_
#define _TRADER_H_

#include <util/m_string.h>
#include <util/util.h>

typedef enum {
    TRADE_ON_BUY, TRADE_ON_SELL, TRADE_NONE, TRADE_LONG, TRADE_SHORT
} Trade_status;

typedef enum {
    TRADER_OK = 1, TRADER_NOTE_TRADE, TRADER_ERROR = -1
} TRADER_CODE;

typedef struct {
    Trade_status predict;

} Trade_predict;

typedef struct {
    double open_price;
    double close_price;

    double profit;
    double size;
    boolean active;

    Trade_status tstatus;
    Trade_predict *tpredict;
    str *ticker;
} Trade;

Trade *Trader_create(str *ticker);
TRADER_CODE Trader_trade(Trade *trader);

void Trader_destory(Trade *trader);

// int trader_trade(Target *target);
// int trader_close_trade(Target *target);

#endif //_TRADER_H_
