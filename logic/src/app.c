#include "../headers/app.h"

#include <stdbool.h>
#include <string.h>
#include <threads.h>

bool run = true;

void candle_manage() {
    PGconn *conn = db_connectdb();
    Res_ticker *prev = NULL;
    format_init(MINUTE_1 | MINUTE_5);
    init_candles(MINUTE_1 | MINUTE_5 | MINUTE_60);
    thrd_t t;

    while(run) {
        List *tickers = list_create(0, M_STRING);
        list_add(tickers, BTCUSDT);
        for(int i = 0; i < tickers->len; i++) {
            Res_ticker *res = send_get_ticker_request(list_get(tickers, i));
            thrd_create(&t, &format_store, (void *) res);
        }
    }

    db_finish(conn);
}
