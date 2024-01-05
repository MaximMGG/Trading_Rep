#include "../headers/realtimework.h"




void put_ticker_info(Res_ticker *res) {
    printf("%s %ld", res->symbol, res->openTime);
}
