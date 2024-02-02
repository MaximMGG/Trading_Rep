#include "../headers/trader.h"

int trader_trade(Target *target) {
    if (target->trade->type == BUY) {
        printf("Ticker %s, buy at price %lf", target->ticker->str, target->trade->enter_price);
    } else {
        printf("Ticker %s, sell at price %lf", target->ticker->str, target->trade->enter_price);
    }
    return 0;
}
int trader_close_trade(Target *target) {
    printf("Close trade: ticker %s, price %lf", target->ticker->str, target->trade->enter_price);
    return 0;
}
