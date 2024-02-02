#include "../headers/app.h"


typedef struct {
    str *token;
    int time;
}Token_s;

Token_s *create_token(char *ticker, int t) {
    Token_s *temp = (Token_s *) malloc(sizeof(Token_s));
    str *s = STR(ticker, s);

    temp->token = s;
    temp->time = t;
    return temp;
}

void free_token(Token_s *t) {
    str_free(t->token);
    free(t);
}

int main() {
    List *ticker = list_create(0, M_STRUCT);
    ticker->struct_size = sizeof(Token_s);
    list_add(ticker, (Token_s *)create_token(BTCUSDT, T_TIME_60));
    data_init();
    logic_create_deposit(1000.0, 10);

    while(true) {
        for(int i = 0; i < ticker->len; i++) {
            data_distributor(send_get_ticker_request(BTCUSDT), T_TIME_60);
        }
    }


    return 0;
}
