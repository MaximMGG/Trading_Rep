#include "../headers/candleformatting.h"
#include "../../../logic/headers/realtimework.h"
#include <threads.h>


static mtx_t format_mutex;


static int time_format_t;
static Res_ticker res_m1;
static Res_ticker res_m5;
static Res_ticker res_m15;
static Res_ticker res_m30;
static Res_ticker res_m60;
static time_t t;
static struct tm *tm;

void format_init(int time_format) {
    time_format_t = time_format;
}

int format_store(void *ptr) {
    mtx_lock(&format_mutex);

    t = time(&t);
    tm = localtime(&t);

    Res_ticker *res = (Res_ticker *) ptr;
    if (time_format_t & MINUTE_1) {
        if (res_m1.symbol == NULL) {
            res_m1 = *res;
        }
        if (res_m1.openTime != res->openTime) {
            db_insert_ticker_response(res, 1);
            add_candle_in_logic_engine(res, MINUTE_1);
            res_m1 = *res;
        }
    }
    if (time_format_t & MINUTE_5) {
        if (res_m5.symbol == NULL) {
            res_m5 = *res;
        }
        if (res_m5.openTime != res->openTime && (tm->tm_min % 5) == 0) {
            db_insert_ticker_response(res, 5);
            add_candle_in_logic_engine(res, MINUTE_5);
            res_m1 = *res;
            res_m5 = *res;
        }
    }
    if (time_format_t & MINUTE_15) {
        if (res_m15.symbol == NULL) {
            res_m15 = *res;
        }
        if (res_m15.openTime != res->openTime && (tm->tm_min % 15) == 0) {
            db_insert_ticker_response(res, 15);
            add_candle_in_logic_engine(res, MINUTE_15);
            res_m1 = *res;
            res_m15 = *res;
        }
    }
    if (time_format_t & MINUTE_30) {
        if (res_m30.symbol == NULL) {
            res_m30 = *res;
        }
        if (res_m30.openTime != res->openTime && (tm->tm_min % 30) == 0) {
            db_insert_ticker_response(res, 30);
            add_candle_in_logic_engine(res, MINUTE_30);
            res_m1 = *res;
            res_m30 = *res;
        }
    }
    if (time_format_t & MINUTE_60) {
        if (res_m60.symbol == NULL) {
            res_m60 = *res;
        }
        if (res_m60.openTime != res->openTime && (tm->tm_min % 60) == 0) {
            db_insert_ticker_response(res, 60);
            add_candle_in_logic_engine(res, MINUTE_60);
            res_m1 = *res;
            res_m60 = *res;
        }
    }
    mtx_unlock(&format_mutex);
    return 0;
}
