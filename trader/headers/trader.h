#ifndef _TRADER_H_
#define _TRADER_H_

typedef enum {
    TRADE_ON_BUY, TRADE_ON_SELL, TRADE_NONE
} Trade_status;

typedef enum {
    LAST_WAS_LONG, LAST_WAS_SHORT, LAST_NONE
} Trade_last;

typedef enum {
    TRADER_OK, TRADER_NOTE_TRADE, TRADER_ERROR
} TRADER_CODE;

typedef struct {
    Trade_status predict;

} Trade_predict;

typedef struct {
    double open_price;
    Trade_status tstatus;
    Trade_last tlast;

    Trade_predict *tpredict;
} Trade;

TRADER_CODE Trader_create();


// int trader_trade(Target *target);
// int trader_close_trade(Target *target);

#endif //_TRADER_H_
