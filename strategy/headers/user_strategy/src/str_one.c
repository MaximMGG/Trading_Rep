#include "../headers/str_one.h"


STRATEGY_CODE strategy_one_starter(Quotes *q) {
    if (q->candle_size == 1) {
        return STRATEGY_NONE;
    }
    Candle *cur = q->candles[q->candle_size - 1];
    Candle *last = q->candles[q->candle_size - 2];
    Trade *trader = Trader_create(q->ticker);

    if((cur->open_price > last->open_price)
        && last->close_price < last->open_price) {
        trader->tpredict = TRADE_PLONG;
    }

    return 0;
}
