#ifndef _STRATEGY_INIT_H_
#define _STRATEGY_INIT_H_

#include <util/util.h>
#include "../../service/headers/quote.h"
#include "../../trader/headers/trader.h"
#include "../../manager/headers/deposit.h"

typedef enum {
    STRATEGY_OK, 
    STRATEGY_ERROR, 
    STRATEGY_LONG, 
    STRATEGY_SHORT, 
    STRATEGY_CLOSE_LONG, 
    STRATEGY_CLOSE_SHORT, 
    STRATEGY_NONE
} STRATEGY_CODE;




#endif //_STRATEGY_INIT_H_
