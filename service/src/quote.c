#include "../headers/quote.h"
#include "../../trader/headers/trader.h"

Quotes *Quotes_create(Trade_time t, i32 (*strategy) (Quotes *q), str *ticker) {
    Quotes *q = (Quotes *) malloc(sizeof(Quotes));
    q->t = t;
    q->strategy = strategy;
    q->candle_size = 0;
    q->max_candle_size = 20;
    q->ticker = newstr(ticker->str);
    
    q->candles = (Candle **) malloc(sizeof(Candle *) * q->max_candle_size);

    q->trades = list_create(0, M_STRUCT);
    q->trades->struct_size = sizeof(Trade);

    return q;
}

QUOTE_CODE Quotes_add_candle(Quotes *q, Candle *c) {
    q->candles[q->candle_size] = c;
    q->candle_size++;

    if (q->candle_size == q->max_candle_size) {
        q->max_candle_size <<= 1;
        q->candles = (Candle **) realloc(q->candles, q->max_candle_size);

        if (q->candles == NULL) {
            seterror("Realloc error q->candles");
            return QUOTE_ERROR;
        }
    }

    return QUOTE_OK;
}

QUOTE_CODE Quotes_update_lastcandle(Quotes *q, Candle *c) {
    if (c == NULL) {
        seterror("Candle *c == NULL");
        return QUOTE_ERROR;
    }
    Candle *temp = q->candles[q->candle_size - 1];

    if (temp->max_value < c->max_value) {
        temp->max_value = c->max_value;
    }
    if (temp->min_value < c->min_value) {
        temp->min_value = c->min_value;
    }

    temp->last_price = c->last_price;

    return QUOTE_OK;
}

QUOTE_CODE Quotes_action(Quotes *q) {
    if (q->strategy(q)) {
        q->trade = Trader_create(q->ticker);
        if (!Trader_trade(q->trade)) {
            Trader_print_error();
        }
        list_add(q->trades, q->trade);
        return QUOTE_OK;
    } else {
        return QUOTE_NONE;
    }
}

void Quotes_destroy(Quotes *q) {
    if (q != NULL) {
        if (q->candles != NULL) {
            for(int i = 0; i < q->candle_size; i++) {
                Candle_free(q->candles[i]);
            } 
        }
        free(q->candles);
        q->candles = NULL;
        str_free(q->ticker);
        Trader_destory(q->trade);
        q->ticker = NULL;
        q->trade = NULL;
        q->candle_size = 0;
        q->max_candle_size = 0;
        q->strategy = NULL;
        list_free_all(q->trades);
        free(q);
    }
}
