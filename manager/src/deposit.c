#include "../headers/deposit.h"
#include "../../service/error_service/headers/trader_error.h"

static double depo;



DEPO_CODE init_depo(double d) {
    if (d > 0) {
        depo = d;
        return DEPO_OK;
    }
    else {
        seterror("Cant initialize depo with negative number");
        return DEPO_ERROR;
    }
}

DEPO_CODE incrice_depo(double sum) {
    depo += sum;
    if (depo < 0) {
        seterror("Deposit < 0.0");
        return DEPO_ERROR;
    } else {
        return DEPO_OK;
    }
}
