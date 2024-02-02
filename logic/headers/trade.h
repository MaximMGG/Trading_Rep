#ifndef _TRADE_H_
#define _TRADE_H_

enum Type{BUY, SELL};

typedef struct Trade{
    char *ticker;
    enum Type type;
    double size;
}Trade;


int init_trades();
int create_trade(char *ticker, enum Type type, double size);


#endif //_TRADE_H_
