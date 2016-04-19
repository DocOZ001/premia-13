#include  "std.h"

static NumFunc_1 digit=
  {
    Digit,
    {{"Strike",PDOUBLE,{100},ALLOW,SETABLE},
     {"Rebate",PDOUBLE,{10},ALLOW,SETABLE},
     {" ",PREMIA_NULLTYPE,{0},FORBID,SETABLE}
    },
    CHK_digit
  };

static TYPEOPT DigitAmer=
  {
    /*PayOff*/   {"Payoff",NUMFUNC_1,{0},FORBID,SETABLE},
    /*Maturity*/ {"Maturity",DATE,{0},ALLOW,SETABLE},
    /*EuOrAm*/   {"Amer",BOOL,{AMER},FORBID,UNSETABLE}
  };

static int OPT(Init)(Option *opt,Model *mod)
{
  TYPEOPT* pt=(  TYPEOPT*)(opt->TypeOpt);

  if (opt->init == 0 )
    {
      opt->init = 1;
      opt->nvar = 3;
      opt->nvar_setable = 2;

      pt->PayOff.Val.V_NUMFUNC_1=&digit;

      (pt->EuOrAm).Val.V_BOOL=AMER;
      (pt->Maturity).Val.V_DATE=1.0;
      (pt->PayOff.Val.V_NUMFUNC_1)->Par[0].Val.V_PDOUBLE=100.0;
      (pt->PayOff.Val.V_NUMFUNC_1)->Par[1].Val.V_PDOUBLE=10.0;

    }

  return OK;
}

MAKEOPT(DigitAmer);