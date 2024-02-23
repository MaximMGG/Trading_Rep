#include "../headers/app.h"
#include <util/m_list.h>

struct Quote_args {
    i32 q_time;
    char *q_func_name;
    char *q_ticker;
};

typedef struct {
    Quotes **template;
    u32 quotes_size;
} App_;

static struct Quote_args parse_args(char *arg) {
    List *l = list_create_from_string(arg, M_STRING);
    struct Quote_args q = {atoi(list_get(l, 0)), list_get(l, 1), list_get(l ,2)};
    list_free_all(l);
    return q;
}


App_ *init_app(i32 argc, char **argv) {
    App_ *app = (App_ *) malloc(sizeof(App_));
    app->template = (Quotes **) malloc(sizeof(Quotes *) * argc - 1);
    for(int i = 1; i < argc; i++) {
        struct Quote_args q = parse_args(argv[i]);
        app->template[i] = Quotes_create(q.q_time, (int (*) (Quotes *)) q.q_func_name, newstr(q.q_ticker));
        app->quotes_size++;
    } 
    return app;
}


int main(i32 argc, char **argv) {
    App_ *app = init_app(argc, argv);
    data_init();

    while(true) {
        for(int i = 0; i < app->quotes_size; i++) {
            Res_ticker *res = send_get_ticker_request(app->template[i]->ticker->str);
            Candle new = Candle_new(0, 0, res->lastPrice, res->openTime, res->lastPrice, res->volume, app->template[i]->t);
            if (Candle_check_time(app->template[i]->candles[app->template[i]->candle_size - 1], &new, app->template[i]->t) == NEW_CANDLE) {
                Quotes_add_candle(app->template[i], &new);
                Quotes_action(app->template[i], NULL);

            }
        }
    }
    return 0;
}
