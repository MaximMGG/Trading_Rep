#include "../headers/datacenter.h"



void data_distributor(Res_ticker *response, i32 t) {
    str *resp_fmt = newstr("insert into ticker_%d"
            "(symbol, priceChange, priceChangePercent, weightedAvgPrice, openPrice, highPrice, "
            "lowPrice, lastPrice, volume, quoteVolume, openTime, closeTime, firstId, lastId, count) values"
            "('%s', %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %ld, %ld, %ld, %ld, %ld);");

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

}

void data_init() {
    str *db_conn_format = newstr("user=%s dbname=%s password=%s");

    str *db_conn = str_format(NULL, db_conn_format, 
                    get_property_from_file("dc/res/property.conf", "user"),
                    get_property_from_file("dc/res/property.conf", "dbname"),
                    get_property_from_file("dc/res/property.conf", "password"));

    db_connectdb(db_conn);
    str_free(db_conn_format);
    str_free(db_conn);
}

void data_close() {
    db_finish();
}


