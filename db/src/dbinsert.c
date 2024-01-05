#include "../headers/dbinsert.h"
#include <libpq-fe.h>

#define PROPERTY_LEN 1024


PGconn *db_connectdb() {
    char con_inf[256] = {0};

    snprintf(con_inf, 256, "user=%s dbname=%s password=%s",
            get_property_from_file("db/res/property.conf", "user"),
            get_property_from_file("db/res/property.conf", "dbname"),
            get_property_from_file("db/res/property.conf", "password")
            );

    PGconn *conn = PQconnectdb(con_inf);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to db error %s", PQerrorMessage(conn));
    }

    return conn;
}

int db_insert_ticker_response(Res_ticker *resp, PGconn *conn) {
    char *insert_msg = (char *) malloc(PROPERTY_LEN);
    tryp(insert_msg);
    PGresult *res;
    snprintf(insert_msg, PROPERTY_LEN, "insert into ticker(symbol, priceChange, priceChangePercent, weightedAvgPrice, openPrice, highPrice, "
            "lowPrice, lastPrice, volume, quoteVolume, openTime, closeTime, firstId, lastId, count) values ("
            "'%s', %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %ld, %ld, %ld, %ld, %ld);",
                            resp->symbol,
                            resp->priceChange, 
                            resp->priceChangePercent,
                            resp->weightedAvgPrice,
                            resp->openPrice,
                            resp->highPrice,
                            resp->lowPrice,
                            resp->lastPrice,
                            resp->volume,
                            resp->quoteVolume,
                            resp->openTime,
                            resp->closeTime,
                            resp->firstId,
                            resp->lastId,
                            resp->count
                            );
    res = PQexec(conn, insert_msg);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Con not insert in db %s\n", PQerrorMessage(conn));
    }
    PQclear(res);
    return 0;
};

void db_finish(PGconn *conn) {
    PQfinish(conn);
}
