#include "../headers/candleformatting.h"

static int time_format_t;
static Res_ticker res_m1;
static Res_ticker res_m5;
static Res_ticker res_m15;
static Res_ticker res_m30;
static Res_ticker res_m60;

void format_init(int time_format) {
    time_format_t = time_format;
}

void format_store(Res_ticker *res) {
    if (time_format_t & MINUTE_1) {
        if (res_m1.symbol == NULL) {
            res_m1 = *res;
        }
        if (res_m1.openTime != res->openTime) {

        }
    }
    if (time_format_t & MINUTE_5) {
        if (res_m5.symbol == NULL) {
            res_m5 = *res;
        }
    }
    if (time_format_t & MINUTE_15) {
        if (res_m15.symbol == NULL) {
            res_m15 = *res;
        }
    }
    if (time_format_t & MINUTE_30) {
        if (res_m30.symbol == NULL) {
            res_m30 = *res;
        }
    }
    if (time_format_t & MINUTE_60) {
        if (res_m60.symbol == NULL) {
            res_m60 = *res;
        }
    }
}
