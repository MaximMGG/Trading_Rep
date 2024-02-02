#ifndef _REALTIMEWORD_H_
#define _REALTIMEWORD_H_
#include "../../service/headers/getservice.h"
#include "../../core/candle/headers/candleformatting.h"
#include "../../lib/m_list.h"

void add_candle_in_logic_engine(Res_ticker *ticker, int time_candle);
int init_candles(int time_candle);


#endif //_REALTIMEWORD_H_
