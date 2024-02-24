#ifndef _DEPOSIT_H_
#define _DEPOSIT_H_

typedef enum {
    DEPO_OK, DEPO_ERROR
} DEPO_CODE;


DEPO_CODE init_depo(double depo);
DEPO_CODE incrice_depo(double sum);

#endif //_DEPOSIT_H_
