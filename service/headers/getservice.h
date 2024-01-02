#ifndef _GETSERVICE_H_
#define _GETSERVICE_H_

#include "tokens.h"

//standart get requst for getting respons with ticker info
#define GET_REQUEST "api1.binance.com/api/v3/ticker?symbol=%s"

// {"symbol":"BTCUSDT","priceChange":"1220.04000000","priceChangePercent":"2.788","weightedAvgPrice":"45152.54947958","openPrice":"43766.95000000","highPrice":"45879.63000000","lowPrice":"43766.94000000","lastPrice":"44986.99000000","volume":"67051.17133000","quoteVolume":"3027531331.14128620","openTime":1704151260000,"closeTime":1704237704418,"firstId":3345802793,"lastId":3348106894,"count":2304102}


struct respons {
    char *symbol;
    char *priceChange;
    char *priceChangePercent;
    char *weightedAvgPrice;
    char *openPrice;
    char *highPrice;
    char *lowPrice;
    char *lastPrice;
    char *volume;
    char *quoteVolume;
    char *openTime;
    char *closeTime;
    char *firstId;
    char *lastId;
    char *count;
};

typedef struct respons Response;

Response *send_get_ticker_request(char *ticker);


#endif //_GETSERVICE_H_
