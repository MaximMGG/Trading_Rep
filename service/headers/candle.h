#ifndef _CANDLE_H_
#define _CANDLE_H_


typedef enum {
    C_MIN_1 = 1, C_MIN_5 = 5, C_MIN_15 = 15, C_MIN_30 = 30, C_MIN_60 = 60
} time;


typedef struct {
    double max_value;
    double min_value;
    double open_price;
    double current_price;
    double value;
    time c_time;
} Candle;


Candle Candle_new(double max_value, double min_value, double open_price, double current_price, double value, time c_time);



#endif //_CANDLE_H_
