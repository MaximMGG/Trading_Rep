#include "../headers/trader.h"
#include <stdlib.h>
#include <stdio.h>




Trade *Trader_create(str *ticker) {
    Trade *t = (Trade *) malloc(sizeof(Trade));
    t->open_price = 0;
    t->close_price = 0;
    t->size = 0;
    t->profit = 0;
    t->ticker = newstr(ticker->str);

    return t;
}

TRADER_CODE Trader_trade(Trade *trader) {

    if (trader->active) {
        //Trader_close_trade(trader);
        printf("Trade close");
    
        if (trader->tstatus == TRADE_ON_BUY) {
            trader->profit = (trader->close_price - trader->open_price) * trader->size; 
        } else if (trader->tstatus == TRADE_ON_SELL){
            trader->profit = (trader->close_price - trader->open_price) * trader->size * -1; 
        }

        return TRADER_OK;
    }

    if (trader->tpredict == TRADE_ON_BUY) {
        //Trader_long_trade(trader);
        printf("Buy at price %lf, trade size if %lf", trader->open_price, trader->size);

    } else if (trader->tpredict == TRADE_ON_SELL) {
        //Trader_short_trade(trader);
        printf("Sell at price %lf, trade size if %lf", trader->open_price, trader->size);
    }

    return TRADER_OK;
}

void Trader_destory(Trade *trader) {
    if (trader != NULL) {
        str_free(trader->ticker);
        trader->open_price = 0;
        trader->profit = 0;
        trader->size = 0;
    }
    free(trader);
}
