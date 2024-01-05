#include "../headers/realtimework.h"



void put_ticker_info(Res_ticker *res) {
    fprintf(stdout, "%s %ld\n", res->symbol, res->openTime);
}
