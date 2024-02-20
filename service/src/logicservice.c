#include "../headers/logicservice.h"
#include "../../trader/headers/trader.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define null NULL

static List *targets = NULL;
static DEPOSIT *depo;

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


static Target *whatch_target(Res_ticker *res, int t) {
    int target_pos = 0;
    if ((target_pos = targets_contein(res->symbol, t)) > 0) {
        Target *target = (Target *)list_get(targets, target_pos);
        if (res->lastPrice > target->last_price) {
            if (target->trade == NULL) {
                target->predict = MAYBE_BUY;
                return target;
            } else {
                target->predict = target->trade->type == BUY ? ON_LONG_TRADE : ON_SHORT_TRADE;
            }
        } else if (res->lastPrice < target->last_price) {
            if (target->trade == NULL) {
                target->predict = MAYBE_SELL;
                return target;
            } else {
                target->predict = target->trade->type == BUY ? ON_LONG_TRADE : ON_SHORT_TRADE;
            }
        } else {
            if (target->trade == NULL)
                target->predict = EQUALSE;
            else 
                target->predict = target->trade->type == BUY ? ON_LONG_TRADE : ON_SHORT_TRADE;
        }
    }else {
        if (target_pos == TARGETS_IS_NULL) {
            targets = list_create(0, M_STRUCT);
            targets->struct_size = sizeof(Target);
        } 
    }
    return null;
}

void logic_trade_dispetcher(Res_ticker *res, int t) {
     Target *target = whatch_target(res, t);
     if (target == null) {
         target = (Target *) malloc(sizeof(Target));
         str *ticker = newstr(res->symbol);
         target->ticker = ticker;
         target->trade = NULL;
         target->predict = NOTHING;
         target->time_type = t;
         target->last_price = res->lastPrice;
         target->lose_count = 0;
         target->last_trade = NONE;

         list_add(targets, target);
     } else {
         switch(target->predict) {
             case MAYBE_BUY: {
                                 if (target->last_trade == BUY) {
                                     break;
                                 }
                                 Trade *trade = (Trade *) malloc(sizeof(Trade));
                                 trade->type = BUY;
                                 trade->size = (1 * depo->start_trade_size) / res->lastPrice;
                                 for(int i = 0; i < target->lose_count; i++) {
                                     trade->size *= 2;
                                 }
                                 trade->enter_price = res->lastPrice;
                                 //TODO(Maxim) do trade logic
                                 trader_trade(target);
                                 target->last_trade = NONE;
                                 target->last_price = res->lastPrice;
                                 target->trade = trade;
                                 break;
                             }
             case MAYBE_SELL: {
                                  if (target->last_trade == SELL) {
                                      break;
                                  }
                                  Trade *trade = (Trade *) malloc(sizeof(Trade));
                                  trade->type = SELL;
                                  trade->size = (1 * depo->start_trade_size) / res->lastPrice;
                                  for(int i = 0; i < target->lose_count; i++) {
                                      trade->size *= 2;
                                  }
                                  trade->enter_price = res->lastPrice;
                                  //TODO(Maxim) do trade logic
                                  trader_trade(target);
                                  target->last_trade = NONE;
                                  target->last_price = res->lastPrice;
                                  target->trade = trade;
                                  break;
                              }
             case EQUALSE: {
                               //nothing

                               break;
                           }
             case ON_LONG_TRADE: {
                                     trader_close_trade(target);
                                     printf("%lf", depo->total);
                                     double current_profit = (res->lastPrice - target->trade->enter_price) * target->trade->size;
                                     if (current_profit > 0) {
                                         target->lose_count = 0;
                                     } else {
                                         target->lose_count++;
                                     }
                                     depo->total += current_profit;
                                     target->last_trade = BUY;
                                     free(target->trade);
                                     target->trade = NULL;
                                     target->last_price = res->lastPrice;
                                     target->predict = NOTHING;
                                     break;
                                 }
             case ON_SHORT_TRADE: {
                                      trader_close_trade(target);
                                      printf("%lf", depo->total);
                                      double current_profit = (target->trade->enter_price - res->lastPrice) * target->trade->size;
                                      if (current_profit > 0) {
                                          target->lose_count = 0;
                                      } else {
                                          target->lose_count++;
                                      }
                                      depo->total += current_profit;
                                      target->last_trade = SELL;
                                      free(target->trade);
                                      target->trade = NULL;
                                      target->last_price = res->lastPrice;
                                      target->predict = NOTHING;
                                      break;
                                  }
             case NOTHING: {
                               //nothing
                               break;
                           }
         }
     }
}


DEPOSIT *logic_create_deposit(double total, int devide_step) {
    depo = (DEPOSIT *) malloc(sizeof(DEPOSIT));
    depo->total = total;
    depo->start_trade_size = total / devide_step;
    return depo;
}
