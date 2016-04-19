#ifndef MIN_DEF
#define MIN_DEF

class BaseFunctional {
public: 
  virtual double evaluateFG(double * x, double * g, int n)=0; 
};

class GradTester : public BaseFunctional {
		BaseFunctional & bf;
		double step;
		double acu;
	public:
		double evaluateFG(double * x, double * g, int n); 
		GradTester(BaseFunctional & _bf, double _step, double _acu) : bf(_bf), step(_step), acu(_acu) {} 

};



// Limited Memory BFGS with linear constraints
// x contains the initial guess
// l contains lower bounds; u contains upper bounds
// nbd describes the nature of bounds
// 0 ==== no bounds
// 1 ==== lower bound
// 2 ==== lower and upper 
// 3 ==== only upper
/*     factr is a double precision variable. */
/*       The iteration will stop when */

/*         (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= factr*epsmch */

/*         where epsmch is the machine precision, which is automatically */
/*         generated by the code. Typical values for factr: 1.d+12 for */
/*         low accuracy; 1.d+7 for moderate accuracy; 1.d+1 for extremely */
/*         high accuracy. */

/*     pgtol is a double precision variable. */
/*       On entry pgtol >= 0 is specified by the user.  The iteration */
/*         will stop when */

/*                 max{|proj g_i | i = 1, ..., n} <= pgtol */

/*         where pg_i is the ith component of the projected gradient. */
/*       On exit pgtol is unchanged. */

/*     Maxit is the maximum allowed number of BFGS iterations */

double minimizeBFGS(double * x, double * l, double * u, long int * nbd, int n, BaseFunctional & func, double factr, double pgtol, int maxit);


#endif