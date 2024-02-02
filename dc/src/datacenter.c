#include "../headers/datacenter.h"

static long time_1 = 0;
static long time_5 = 0;
static long time_15 = 0;
static long time_30 = 0;
static long time_60 = 0;

static _Bool new_candle(long cur_time, Time t) {
    switch (t) {
        case T_TIME_1:
            if (time_1 != cur_time) {
                time_1 = cur_time;
                return true;
            }
            break;
        case T_TIME_5:
            if (time_5 != cur_time) {
                time_5 = cur_time;
                return true;
            }
            break;
        case T_TIME_15:
            if (time_15 != cur_time) {
                time_15 = cur_time;
                return true;
            }
            break;
        case T_TIME_30:
            if (time_30 != cur_time) {
                time_30 = cur_time;
                return true;
            }
            break;
        case T_TIME_60:
            if (time_60 != cur_time) {
                time_60 = cur_time;
                return true;
            }
            break;
    }
    return false;
}


void data_distributor(Res_ticker *response, Time t) {
    if (new_candle(response->openTime, t)) {
        str *resp_fmt = STR("insert into ticker_%d"
                "(symbol, priceChange, priceChangePercent, weightedAvgPrice, openPrice, highPrice, "
                "lowPrice, lastPrice, volume, quoteVolume, openTime, closeTime, firstId, lastId, count) values"
                "('%s', %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %ld, %ld, %ld, %ld, %ld);"
                , resp_fmt);

        str *resp = str_format(NULL, resp_fmt, t,
                response->symbol,
                response->priceChange,
                response->priceChangePercent,
                response->weightedAvgPrice,
                response->openPrice,
                response->highPrice,
                response->lowPrice,
                response->lastPrice,
                response->volume,
                response->quoteVolume,
                response->openTime,
                response->closeTime,
                response->firstId,
                response->lastId,
                response->count
                );

        db_insert_ticker_response(resp);
        str_free(resp);
        str_free(resp_fmt);

        //TODO(Maxim) send data in logic service
    } else return;
}

void data_init() {
    str *db_conn_format = STR("user=%s dbname=%s password=%s", db_conn_format);

    str *db_conn = str_format(NULL, db_conn_format, 
                    get_property_from_file("dc/res/property.conf", "user"),
                    get_property_from_file("dc/res/property.conf", "dbname"),
                    get_property_from_file("dc/res/property.conf", "password"));

    db_connectdb(db_conn);
    str_free(db_conn_format);
    str_free(db_conn);
}
