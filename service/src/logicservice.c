#include "../headers/logicservice.h"
#include <string.h>

static List *trades = NULL;
static List *targets = NULL;

static int targets_contein(char *ticker, int t) {
    if (targets == NULL) return TARGETS_IS_NULL;

    Target *target;
    for(int i = 0; i < targets->len; i++) {
        target = (Target *) list_get(targets, i);
        if (strcmp(target->ticker->str, ticker) == 0) {
            if (target->time_type == t)
                return i;
            else return TIME_MISTMACH;
        }
    }
    return NOT_CONTEIN;
}


static predict whatch_target(Res_ticker *res, int t) {
    int target_pos = 0;
    if ((target_pos = targets_contein(res->symbol, t)) > 0) {
        Target *target = (Target *)list_get(targets, target_pos);
        if (res->lastPrice > target->last_price) {
            return MAYBE_BUY;
        } else if (res->lastPrice < target->last_price) {
            return MAYBE_SELL;
        } else {
            return EQUALSE;
        }
    } else {
        if (target_pos == TARGETS_IS_NULL) {
            targets = list_create(0, M_STRUCT);
            targets->struct_size = sizeof(Target);
            return NOTHING;
        }
        Target *target = (Target *) malloc(sizeof(Target));
        str *ticker = STR(res->symbol, ticker);
        target->ticker = ticker;
        target->last_price = res->lastPrice;
        target->time_type = t;
        list_add(targets, target);
    }
    return NOTHING;
}

void logic_trade_dispetcher(Res_ticker *res, int t) {
    if (trades == NULL) {
        whatch_target(res, t);
        
    }
}
