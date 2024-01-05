#include "../headers/app.h"
#include "../headers/realtimework.h"

#include <stdbool.h>
#include <string.h>

bool run = true;

void candle_manage() {
    PGconn *conn = db_connectdb();
    Res_ticker *prev = NULL;

    while(run) {
        Res_ticker *res = send_get_ticker_request(BTCUSDT);
        if (prev == NULL) {
            prev = res;
        } else {
            if (prev->openTime != res->openTime) {
                db_insert_ticker_response(res, conn);
            }
        }
        put_ticker_info(res);
    }
    db_finish(conn);
}
