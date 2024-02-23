#include "../headers/candle.h"





Candle Candle_new(  double max_value, 
                    double min_value, 
                    double open_price, 
                    long open_time,
                    double current_price, 
                    double value, 
                    Trade_time c_time) {
    Candle candle = {max_value, min_value, open_price, open_time, current_price, value, c_time};
    return candle;
}

i32 Candle_check_time(Candle *f, Candle *s, Trade_time t) {
    i32 c_min = ((s->open_time - f->open_time) / 60000) == C_MIN_1;
    switch (t) {
        case C_MIN_1: {
            if (c_min == C_MIN_1) {
                return NEW_CANDLE;
            } else {
                return SAME_CANDLE;
            }
        } break;
        case C_MIN_5: {
            if (c_min == C_MIN_5) {
                return NEW_CANDLE;
            } else {
                return SAME_CANDLE;
            }

        } break;
        case C_MIN_15: {
            if (c_min == C_MIN_15) {
                return NEW_CANDLE;
            } else {
                return SAME_CANDLE;
            }

        } break;
        case C_MIN_30: {
            if (c_min == C_MIN_30) {
                return NEW_CANDLE;
            } else {
                return SAME_CANDLE;
            }

        } break;
        case C_MIN_60: {
            if (c_min == C_MIN_60) {
                return NEW_CANDLE;
            } else {
                return SAME_CANDLE;
            }
        } break;
    }
    return 0;
}

Quotes *Quotes_create(Trade_time t, i32 (*strategy) (Quotes *q), str *ticker) {
    Quotes *q = (Quotes *) malloc(sizeof(Quotes));
    q->t = t;
    q->strategy = strategy;
    q->candle_size = 0;
    q->max_candle_size = 20;
    q->ticker = newstr(ticker->str);
    
    q->candles = (Candle **) malloc(sizeof(Candle *) * q->max_candle_size);

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

    temp->value = c->value;
    temp->current_price = c->current_price;

    return QUOTE_OK;
}

QUOTE_CODE Quotes_action(Quotes *q, Trade *trade) {
    if (q->strategy(q)) {
        if (!Trader_trade(trade)) {
            Trader_print_error();
        }
        return QUOTE_OK;
    } else {
        return QUOTE_NONE;
    }
}

void Candle_free(Candle *c) {
    if (c != NULL)
        free(c);
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
        Trader_destory(q->trader);
        q->ticker = NULL;
        q->trader = NULL;
        q->candle_size = 0;
        q->max_candle_size = 0;
        q->strategy = NULL;
        free(q);
    }
}

