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


void Candle_free(Candle *c) {
    if (c != NULL)
        free(c);
}


