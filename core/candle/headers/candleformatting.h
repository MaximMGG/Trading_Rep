#ifndef _CANDLEFORMATTING_H_
#define _CANDLEFORMATTING_H_

#include "../../../service/headers/getservice.h"
#include "../../../db/headers/dbinsert.h"

typedef enum {
    MINUTE_1 = 0b01,
    MINUTE_5 = 0b10,
    MINUTE_15 = 0b100,
    MINUTE_30 = 0b1000,
    MINUTE_60 = 0b10000
} Time_candle;

void format_init(int time_format);

int format_store(void *);


#endif //_CANDLEFORMATTING_H_