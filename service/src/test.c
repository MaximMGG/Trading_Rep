#include "../headers/getservice.h"
#include <stdio.h>
#include <util/pr_map.h>


int main() {

    Response *res = send_get_ticker_request(BTCUSDT);

    printf("Symbol %s\n", res->symbol);
    free_struct_map(res, 15);
    
    return 0;
}
