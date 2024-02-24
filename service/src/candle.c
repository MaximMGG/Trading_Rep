#include "../headers/candle.h"



Candle *Candle_new(double open_price, long open_time, Trade_time c_time) {
    Candle *candle = (Candle *) malloc(sizeof(Candle));
    candle->max_value = open_price;
    candle->min_value = open_price;
    candle->open_price = open_price;
    candle->open_time = open_time;
    candle->close_price = 0;
    candle->last_price = open_price;
    candle->c_time = c_time;
    return candle;
}

i32 Candle_check_time(Candle *cur, Candle *new, Trade_time t) {
    i32 c_min = ((new->open_time - cur->open_time) / 60000) == C_MIN_1;
    cur->last_price = new->open_price;
    if (cur->max_value < new->last_price) {
        cur->max_value = new->last_price;
    }
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

    cur->close_price = new->open_price;

    return 0;
}


void Candle_free(Candle *c) {
    if (c != NULL)
        free(c);
}


