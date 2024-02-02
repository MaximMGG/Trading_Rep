#include "../headers/trade.h"
#include <stdlib.h>
#include <string.h>

#define TRADES_SIZE 5 

typedef struct {
    Trade **trades;
    int size;
    int max_size;
}L_Trades;

L_Trades *trades;

int init_trades(){
    trades = (L_Trades *) malloc(sizeof(L_Trades));
    trades->size = 0;
    trades->max_size = TRADES_SIZE;
    trades->trades = (Trade **) malloc(sizeof(Trade *) * TRADES_SIZE);

    if (trades->trades != NULL) {
        return 0;
    }
    return 1;
}

int create_trade(char *ticker, enum Type type, double size) {
    Trade *trade = (Trade *) malloc(sizeof(Trade));
    trade->ticker = (char *) malloc(sizeof(strlen(ticker)));
    strcpy(trade->ticker, ticker);
    trade->type = type;
    trade->size = size;

    trades->trades[trades->size++] = trade;

    if (trades->trades[trades->size] == NULL) {
        return 0;
    }
    return -1;
}
