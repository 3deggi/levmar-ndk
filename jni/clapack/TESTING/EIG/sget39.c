/* sget39.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include "blaswrap.h"

/* Table of constant values */

static integer c__10 = 10;
static integer c__1 = 1;
static logical c_false = FALSE_;
static logical c_true = TRUE_;
static real c_b25 = 1.f;
static real c_b59 = -1.f;

/* Subroutine */ int sget39_(real *rmax, integer *lmax, integer *ninfo, 
	integer *knt)
{
    /* Initialized data */

    static integer idim[6] = { 4,5,5,5,5,5 };
    static integer ival[150]	/* was [5][5][6] */ = { 3,0,0,0,0,1,1,-1,0,0,
	    3,2,1,0,0,4,3,2,2,0,0,0,0,0,0,1,0,0,0,0,2,2,0,0,0,3,3,4,0,0,4,2,2,
	    3,0,1,1,1,1,5,1,0,0,0,0,2,4,-2,0,0,3,3,4,0,0,4,2,2,3,0,1,1,1,1,1,
	    1,0,0,0,0,2,1,-1,0,0,9,8,1,0,0,4,9,1,2,-1,2,2,2,2,2,9,0,0,0,0,6,4,
	    0,0,0,3,2,1,1,0,5,1,-1,1,0,2,2,2,2,2,4,0,0,0,0,2,2,0,0,0,1,4,4,0,
	    0,2,4,2,2,-1,2,2,2,2,2 };

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal), cos(doublereal), sin(doublereal);

    /* Local variables */
    real b[10], d__[20];
    integer i__, j, k, n;
    real t[100]	/* was [10][10] */, w, x[20], y[20], vm1[5], vm2[5], vm3[5], 
	    vm4[5], vm5[3], dum[1], eps;
    integer ivm1, ivm2, ivm3, ivm4, ivm5, ndim, info;
    real dumm;
    extern doublereal sdot_(integer *, real *, integer *, real *, integer *);
    real norm, work[10], scale, domin, resid;
    extern /* Subroutine */ int sgemv_(char *, integer *, integer *, real *, 
	    real *, integer *, real *, integer *, real *, real *, integer *);
    extern doublereal sasum_(integer *, real *, integer *);
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    real xnorm;
    extern /* Subroutine */ int slabad_(real *, real *);
    extern doublereal slamch_(char *), slange_(char *, integer *, 
	    integer *, real *, integer *, real *);
    real bignum;
    extern integer isamax_(integer *, real *, integer *);
    real normtb;
    extern /* Subroutine */ int slaqtr_(logical *, logical *, integer *, real 
	    *, integer *, real *, real *, real *, real *, real *, integer *);
    real smlnum;


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SGET39 tests SLAQTR, a routine for solving the real or */
/*  special complex quasi upper triangular system */

/*       op(T)*p = scale*c, */
/*  or */
/*       op(T + iB)*(p+iq) = scale*(c+id), */

/*  in real arithmetic. T is upper quasi-triangular. */
/*  If it is complex, then the first diagonal block of T must be */
/*  1 by 1, B has the special structure */

/*                 B = [ b(1) b(2) ... b(n) ] */
/*                     [       w            ] */
/*                     [           w        ] */
/*                     [              .     ] */
/*                     [                 w  ] */

/*  op(A) = A or A', where A' denotes the conjugate transpose of */
/*  the matrix A. */

/*  On input, X = [ c ].  On output, X = [ p ]. */
/*                [ d ]                  [ q ] */

/*  Scale is an output less than or equal to 1, chosen to avoid */
/*  overflow in X. */
/*  This subroutine is specially designed for the condition number */
/*  estimation in the eigenproblem routine STRSNA. */

/*  The test code verifies that the following residual is order 1: */

/*       ||(T+i*B)*(x1+i*x2) - scale*(d1+i*d2)|| */
/*     ----------------------------------------- */
/*         max(ulp*(||T||+||B||)*(||x1||+||x2||), */
/*             (||T||+||B||)*smlnum/ulp, */
/*             smlnum) */

/*  (The (||T||+||B||)*smlnum/ulp term accounts for possible */
/*   (gradual or nongradual) underflow in x1 and x2.) */

/*  Arguments */
/*  ========== */

/*  RMAX    (output) REAL */
/*          Value of the largest test ratio. */

/*  LMAX    (output) INTEGER */
/*          Example number where largest test ratio achieved. */

/*  NINFO   (output) INTEGER */
/*          Number of examples where INFO is nonzero. */

/*  KNT     (output) INTEGER */
/*          Total number of examples tested. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. Data statements .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Get machine parameters */

    eps = slamch_("P");
    smlnum = slamch_("S");
    bignum = 1.f / smlnum;
    slabad_(&smlnum, &bignum);

/*     Set up test case parameters */

    vm1[0] = 1.f;
    vm1[1] = sqrt(smlnum);
    vm1[2] = sqrt(vm1[1]);
    vm1[3] = sqrt(bignum);
    vm1[4] = sqrt(vm1[3]);

    vm2[0] = 1.f;
    vm2[1] = sqrt(smlnum);
    vm2[2] = sqrt(vm2[1]);
    vm2[3] = sqrt(bignum);
    vm2[4] = sqrt(vm2[3]);

    vm3[0] = 1.f;
    vm3[1] = sqrt(smlnum);
    vm3[2] = sqrt(vm3[1]);
    vm3[3] = sqrt(bignum);
    vm3[4] = sqrt(vm3[3]);

    vm4[0] = 1.f;
    vm4[1] = sqrt(smlnum);
    vm4[2] = sqrt(vm4[1]);
    vm4[3] = sqrt(bignum);
    vm4[4] = sqrt(vm4[3]);

    vm5[0] = 1.f;
    vm5[1] = eps;
    vm5[2] = sqrt(smlnum);

/*     Initalization */

    *knt = 0;
    *rmax = 0.f;
    *ninfo = 0;
    smlnum /= eps;

/*     Begin test loop */

    for (ivm5 = 1; ivm5 <= 3; ++ivm5) {
	for (ivm4 = 1; ivm4 <= 5; ++ivm4) {
	    for (ivm3 = 1; ivm3 <= 5; ++ivm3) {
		for (ivm2 = 1; ivm2 <= 5; ++ivm2) {
		    for (ivm1 = 1; ivm1 <= 5; ++ivm1) {
			for (ndim = 1; ndim <= 6; ++ndim) {

			    n = idim[ndim - 1];
			    i__1 = n;
			    for (i__ = 1; i__ <= i__1; ++i__) {
				i__2 = n;
				for (j = 1; j <= i__2; ++j) {
				    t[i__ + j * 10 - 11] = (real) ival[i__ + (
					    j + ndim * 5) * 5 - 31] * vm1[
					    ivm1 - 1];
				    if (i__ >= j) {
					t[i__ + j * 10 - 11] *= vm5[ivm5 - 1];
				    }
/* L10: */
				}
/* L20: */
			    }

			    w = vm2[ivm2 - 1] * 1.f;

			    i__1 = n;
			    for (i__ = 1; i__ <= i__1; ++i__) {
				b[i__ - 1] = cos((real) i__) * vm3[ivm3 - 1];
/* L30: */
			    }

			    i__1 = n << 1;
			    for (i__ = 1; i__ <= i__1; ++i__) {
				d__[i__ - 1] = sin((real) i__) * vm4[ivm4 - 1]
					;
/* L40: */
			    }

			    norm = slange_("1", &n, &n, t, &c__10, work);
			    k = isamax_(&n, b, &c__1);
			    normtb = norm + (r__1 = b[k - 1], dabs(r__1)) + 
				    dabs(w);

			    scopy_(&n, d__, &c__1, x, &c__1);
			    ++(*knt);
			    slaqtr_(&c_false, &c_true, &n, t, &c__10, dum, &
				    dumm, &scale, x, work, &info);
			    if (info != 0) {
				++(*ninfo);
			    }

/*                       || T*x - scale*d || / */
/*                         max(ulp*||T||*||x||,smlnum/ulp*||T||,smlnum) */

			    scopy_(&n, d__, &c__1, y, &c__1);
			    r__1 = -scale;
			    sgemv_("No transpose", &n, &n, &c_b25, t, &c__10, 
				    x, &c__1, &r__1, y, &c__1);
			    xnorm = sasum_(&n, x, &c__1);
			    resid = sasum_(&n, y, &c__1);
/* Computing MAX */
			    r__1 = smlnum, r__2 = smlnum / eps * norm, r__1 = 
				    max(r__1,r__2), r__2 = norm * eps * xnorm;
			    domin = dmax(r__1,r__2);
			    resid /= domin;
			    if (resid > *rmax) {
				*rmax = resid;
				*lmax = *knt;
			    }

			    scopy_(&n, d__, &c__1, x, &c__1);
			    ++(*knt);
			    slaqtr_(&c_true, &c_true, &n, t, &c__10, dum, &
				    dumm, &scale, x, work, &info);
			    if (info != 0) {
				++(*ninfo);
			    }

/*                       || T*x - scale*d || / */
/*                         max(ulp*||T||*||x||,smlnum/ulp*||T||,smlnum) */

			    scopy_(&n, d__, &c__1, y, &c__1);
			    r__1 = -scale;
			    sgemv_("Transpose", &n, &n, &c_b25, t, &c__10, x, 
				    &c__1, &r__1, y, &c__1);
			    xnorm = sasum_(&n, x, &c__1);
			    resid = sasum_(&n, y, &c__1);
/* Computing MAX */
			    r__1 = smlnum, r__2 = smlnum / eps * norm, r__1 = 
				    max(r__1,r__2), r__2 = norm * eps * xnorm;
			    domin = dmax(r__1,r__2);
			    resid /= domin;
			    if (resid > *rmax) {
				*rmax = resid;
				*lmax = *knt;
			    }

			    i__1 = n << 1;
			    scopy_(&i__1, d__, &c__1, x, &c__1);
			    ++(*knt);
			    slaqtr_(&c_false, &c_false, &n, t, &c__10, b, &w, 
				    &scale, x, work, &info);
			    if (info != 0) {
				++(*ninfo);
			    }

/*                       ||(T+i*B)*(x1+i*x2) - scale*(d1+i*d2)|| / */
/*                          max(ulp*(||T||+||B||)*(||x1||+||x2||), */
/*                                  smlnum/ulp * (||T||+||B||), smlnum ) */


			    i__1 = n << 1;
			    scopy_(&i__1, d__, &c__1, y, &c__1);
			    y[0] = sdot_(&n, b, &c__1, &x[n], &c__1) + scale *
				     y[0];
			    i__1 = n;
			    for (i__ = 2; i__ <= i__1; ++i__) {
				y[i__ - 1] = w * x[i__ + n - 1] + scale * y[
					i__ - 1];
/* L50: */
			    }
			    sgemv_("No transpose", &n, &n, &c_b25, t, &c__10, 
				    x, &c__1, &c_b59, y, &c__1);

			    y[n] = sdot_(&n, b, &c__1, x, &c__1) - scale * y[
				    n];
			    i__1 = n;
			    for (i__ = 2; i__ <= i__1; ++i__) {
				y[i__ + n - 1] = w * x[i__ - 1] - scale * y[
					i__ + n - 1];
/* L60: */
			    }
			    sgemv_("No transpose", &n, &n, &c_b25, t, &c__10, 
				    &x[n], &c__1, &c_b25, &y[n], &c__1);

			    i__1 = n << 1;
			    resid = sasum_(&i__1, y, &c__1);
/* Computing MAX */
			    i__1 = n << 1;
			    r__1 = smlnum, r__2 = smlnum / eps * normtb, r__1 
				    = max(r__1,r__2), r__2 = eps * (normtb * 
				    sasum_(&i__1, x, &c__1));
			    domin = dmax(r__1,r__2);
			    resid /= domin;
			    if (resid > *rmax) {
				*rmax = resid;
				*lmax = *knt;
			    }

			    i__1 = n << 1;
			    scopy_(&i__1, d__, &c__1, x, &c__1);
			    ++(*knt);
			    slaqtr_(&c_true, &c_false, &n, t, &c__10, b, &w, &
				    scale, x, work, &info);
			    if (info != 0) {
				++(*ninfo);
			    }

/*                       ||(T+i*B)*(x1+i*x2) - scale*(d1+i*d2)|| / */
/*                          max(ulp*(||T||+||B||)*(||x1||+||x2||), */
/*                                  smlnum/ulp * (||T||+||B||), smlnum ) */

			    i__1 = n << 1;
			    scopy_(&i__1, d__, &c__1, y, &c__1);
			    y[0] = b[0] * x[n] - scale * y[0];
			    i__1 = n;
			    for (i__ = 2; i__ <= i__1; ++i__) {
				y[i__ - 1] = b[i__ - 1] * x[n] + w * x[i__ + 
					n - 1] - scale * y[i__ - 1];
/* L70: */
			    }
			    sgemv_("Transpose", &n, &n, &c_b25, t, &c__10, x, 
				    &c__1, &c_b25, y, &c__1);

			    y[n] = b[0] * x[0] + scale * y[n];
			    i__1 = n;
			    for (i__ = 2; i__ <= i__1; ++i__) {
				y[i__ + n - 1] = b[i__ - 1] * x[0] + w * x[
					i__ - 1] + scale * y[i__ + n - 1];
/* L80: */
			    }
			    sgemv_("Transpose", &n, &n, &c_b25, t, &c__10, &x[
				    n], &c__1, &c_b59, &y[n], &c__1);

			    i__1 = n << 1;
			    resid = sasum_(&i__1, y, &c__1);
/* Computing MAX */
			    i__1 = n << 1;
			    r__1 = smlnum, r__2 = smlnum / eps * normtb, r__1 
				    = max(r__1,r__2), r__2 = eps * (normtb * 
				    sasum_(&i__1, x, &c__1));
			    domin = dmax(r__1,r__2);
			    resid /= domin;
			    if (resid > *rmax) {
				*rmax = resid;
				*lmax = *knt;
			    }

/* L90: */
			}
/* L100: */
		    }
/* L110: */
		}
/* L120: */
	    }
/* L130: */
	}
/* L140: */
    }

    return 0;

/*     End of SGET39 */

} /* sget39_ */
