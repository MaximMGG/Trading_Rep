#include "../headers/app.h"

#include <stdbool.h>
#include <string.h>
#include <threads.h>

bool run = true;

void candle_manage() {
    PGconn *conn = db_connectdb();
    Res_ticker *prev = NULL;
    format_init(MINUTE_1 | MINUTE_5);
    thrd_t t;

    while(run) {
        Res_ticker *res = send_get_ticker_request(BTCUSDT);
        thrd_create(&t, &format_store, (void *) res);
        format_store(res);
    }
    db_finish(conn);
}
