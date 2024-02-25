#include "../headers/app.h"
#include "../headers/deposit.h"
#include "../../strategy/headers/user_strategy/headers/str_one.h"
#include <util/m_list.h>

struct Quote_args {
    i32 q_time;
    STRATEGY_CODE (*strategy) (Quotes *);
    char *q_ticker;
};

typedef struct {
    Quotes **template;
    u32 quotes_size;
} App_;

static struct Quote_args parse_args(char *arg) {
    List *l = list_create_from_string(arg, M_STRING);
    struct Quote_args q = {atoi(list_get(l, 0)), strategy_one_starter, list_get(l ,2)};
    list_free_all(l);
    return q;
}


#ifdef TEST
App_ *init_app(i32 argc, char **argv) {
    App_ *app = (App_ *) malloc(sizeof(App_));
    app->template = (Quotes **) malloc(sizeof(Quotes *) * argc - 1);
    app->quotes_size = 0;
    for(int i = 1; i < argc; i++) {
        struct Quote_args q = parse_args(argv[i]);
        app->template[i] = Quotes_create(q.q_time, (int (*) (Quotes *)) q.strategy, newstr(q.q_ticker));
        app->quotes_size++;
    } 
    return app;
}
#else
App_ *init_app() {
    App_ *app = (App_ *) malloc(sizeof(App_));
    app->template = (Quotes **) malloc(sizeof(Quotes *) * 1);
    app->template[0] = Quotes_create(1, (i32 (*) (Quotes *))strategy_one_starter, newstr("BTCUSDT"));
    app->quotes_size = 1;
    return app;
}
#endif


void close_app(App_ *app) {
    for(int i = 0; i < app->quotes_size; i++) {
        Quotes_destroy(app->template[i]);
    }
}

int main(i32 argc, char **argv) {
#ifdef TEST
    App_ *app = init_app(2, (char **)abc);
#else
    App_ *app = init_app();
#endif
    data_init();

    while(true) {
        for(int i = 0; i < app->quotes_size; i++) {
            Res_ticker *res = send_get_ticker_request(app->template[i]->ticker->str);
            Candle *new = Candle_new(res->lastPrice, res->openTime, app->template[i]->t);
            //TODO(Maxim) app->template[i]->candles is NULL for start app, need
            //to correct that
            if (Candle_check_time(app->template[i]->candles[app->template[i]->candle_size - 1], new, app->template[i]->t) == NEW_CANDLE) {
                Quotes_add_candle(app->template[i], new);
                Quotes_action(app->template[i]);
                if (app->template[i]->trade != NULL) {
                    if (app->template[i]->trade->profit != 0.0) {
                        incrice_depo(app->template[i]->trade->profit);
                        list_add(app->template[i]->trades, app->template[i]->trade);
                        app->template[i]->trade = NULL;
                    }
                }
                data_distributor(res, app->template[i]->t);
            }
        }
    }

    data_close();
    close_app(app);
    return 0;
}
