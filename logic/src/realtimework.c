#include "../headers/realtimework.h"

List *candle_1m;
List *candle_5m;
List *candle_15m;
List *candle_30m;
List *candle_60m;


static void check_strategy(int time_candle) {
    
}



void add_candle_in_logic_engine(Res_ticker *ticker, int time_candle) {
    if (ticker == NULL) {
        fprintf(stderr, "ticker is NULL");
        return;
    }
    if (time_candle | MINUTE_1) {
        list_add(candle_1m, ticker);
    }
    if (time_candle | MINUTE_5) {
        list_add(candle_5m, ticker);
    }
    if (time_candle | MINUTE_15) {
        list_add(candle_15m, ticker);
    }
    if (time_candle | MINUTE_30) {
        list_add(candle_30m, ticker);
    }
    if (time_candle | MINUTE_60) {
        list_add(candle_60m, ticker);
    }
}


int init_candles(int time_candle) {
    if (time_candle == 0) {
        return -1;
    }
    if (time_candle | MINUTE_1) {
        candle_1m = list_create(0, M_STRUCT);
        candle_1m->struct_size = sizeof(Res_ticker);
    }
    if (time_candle | MINUTE_5) {
        candle_1m = list_create(0, M_STRUCT);
        candle_1m->struct_size = sizeof(Res_ticker);
    }
    if (time_candle | MINUTE_15) {
        candle_1m = list_create(0, M_STRUCT);
        candle_1m->struct_size = sizeof(Res_ticker);
    }
    if (time_candle | MINUTE_30) {
        candle_1m = list_create(0, M_STRUCT);
        candle_1m->struct_size = sizeof(Res_ticker);
    }
    if (time_candle | MINUTE_60) {
        candle_1m = list_create(0, M_STRUCT);
        candle_1m->struct_size = sizeof(Res_ticker);
    }
    return 0;
}


