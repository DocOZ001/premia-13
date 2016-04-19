#include <stdio.h>
#include <stdlib.h>

#include "pnl/pnl_cdf.h"
#include "pnl/pnl_mathtools.h"

#include "swaption_black.h"

double atm_strike_swaption(ZCMarketData *ZCMarket, double option_mat, double periodicity, double swap_mat)
{
    double sum_zc_tau;
    double P0_opmat, P0_swapmat, Ti, SwapRate;
    int i, nb_payement;
    double P0_Ti;

    P0_opmat = BondPrice(option_mat, ZCMarket);
    P0_swapmat = BondPrice(swap_mat, ZCMarket);

    nb_payement=(int)((swap_mat-option_mat)/periodicity);
    Ti = option_mat;
    sum_zc_tau = 0.;
    for(i=0;i<nb_payement;i++)
    {
        Ti += periodicity;
        P0_Ti = BondPrice(Ti, ZCMarket);
        sum_zc_tau += periodicity*P0_Ti;
    }

    /*Compute Swap Rate*/
    SwapRate = (P0_opmat-P0_swapmat)/sum_zc_tau;

    return SwapRate;
}

/*Payer Swaption payer_receiver=1, Receiver payer_receiver=-1*/
double black_swaption_price(ZCMarketData *ZCMarket, int payer_receiver, double option_mat, double periodicity, double swap_mat, double Nominal, double swaption_strike, double vol)
{
    double sum_zc_tau;
    double d1, d2, P0_opmat, P0_swapmat, Sigma, Ti, SwapRate, black_forumla;
    int i, nb_payement;
    double P0_Ti;

    P0_opmat = BondPrice(option_mat, ZCMarket);
    P0_swapmat = BondPrice(swap_mat, ZCMarket);

    nb_payement=(int)((swap_mat-option_mat)/periodicity);
    Ti = option_mat;
    sum_zc_tau = 0.;
    for(i=0;i<nb_payement;i++)
    {
        Ti += periodicity;
        P0_Ti = BondPrice(Ti, ZCMarket);
        sum_zc_tau += periodicity*P0_Ti;
    }

    /*Compute Swap Rate*/
    SwapRate = (P0_opmat-P0_swapmat)/sum_zc_tau;

    /*Common Black's formula pag.20 Brigo-Mercurio*/
    Sigma = vol*sqrt(option_mat);
    d1 = payer_receiver*(log(SwapRate/swaption_strike)/Sigma+0.5*Sigma);
    d2 = payer_receiver*(log(SwapRate/swaption_strike)/Sigma-0.5*Sigma);
    black_forumla = SwapRate*payer_receiver*cdf_nor(d1)-swaption_strike*payer_receiver*cdf_nor(d2);

    /*Swaption formula pag.20 Brigo-Mercurio*/
    return Nominal*sum_zc_tau*black_forumla;
}

/* Retrieve the black volatility from a swaption price*/
double bk_swaption_vol_implied_newton(ZCMarketData* ZCMarket, double swaption_price, int payer_receiver, double option_mat, double periodicity, double swap_mat, double Nominal, double swaption_strike)
{
    int i, MAX_ITERATIONS, nb_payement;
    double ACCURACY;
    double T_sqrt, vol_black, price, diff, d1, vega, P0_opmat, P0_swapmat, sum_zc_tau, Ti, P0_Ti, SwapRate;


    P0_opmat = BondPrice(option_mat, ZCMarket);
    P0_swapmat = BondPrice(swap_mat, ZCMarket);

    nb_payement=(int)((swap_mat-option_mat)/periodicity);
    Ti = option_mat;
    sum_zc_tau = 0.;
    for(i=0; i<nb_payement; i++)
    {
        Ti += periodicity;
        P0_Ti = BondPrice(Ti, ZCMarket);
        sum_zc_tau += periodicity*P0_Ti;
    }
    /*Compute Swap Rate*/
    SwapRate = (P0_opmat-P0_swapmat)/sum_zc_tau;

    MAX_ITERATIONS = 100;
    ACCURACY    = 1.0e-8;

    T_sqrt = sqrt(option_mat);
    vol_black = 0.1;

    for (i=0; i<MAX_ITERATIONS; i++)
    {
        price = black_swaption_price(ZCMarket, payer_receiver, option_mat, periodicity, swap_mat, Nominal, swaption_strike, vol_black);
        diff = swaption_price - price;

        if (fabs(diff)<ACCURACY) return vol_black;

        d1 = (log(SwapRate/swaption_strike)+ 0.5*SQR(vol_black)*option_mat)/(vol_black*T_sqrt);

        vega = Nominal * (P0_opmat-P0_swapmat) * cdf_nor(d1) * T_sqrt;
        vol_black = vol_black + diff/vega;
    }

    return vol_black;  // something screwy happened, should throw exception
}