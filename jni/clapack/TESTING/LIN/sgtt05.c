/* sgtt05.f -- translated by f2c (version 20061008).
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

static integer c__1 = 1;

/* Subroutine */ int sgtt05_(char *trans, integer *n, integer *nrhs, real *dl, 
	 real *d__, real *du, real *b, integer *ldb, real *x, integer *ldx, 
	real *xact, integer *ldxact, real *ferr, real *berr, real *reslts)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, xact_dim1, xact_offset, i__1, 
	    i__2;
    real r__1, r__2, r__3, r__4;

    /* Local variables */
    integer i__, j, k, nz;
    real eps, tmp, diff, axbi;
    integer imax;
    real unfl, ovfl;
    extern logical lsame_(char *, char *);
    real xnorm;
    extern doublereal slamch_(char *);
    real errbnd;
    extern integer isamax_(integer *, real *, integer *);
    logical notran;


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SGTT05 tests the error bounds from iterative refinement for the */
/*  computed solution to a system of equations A*X = B, where A is a */
/*  general tridiagonal matrix of order n and op(A) = A or A**T, */
/*  depending on TRANS. */

/*  RESLTS(1) = test of the error bound */
/*            = norm(X - XACT) / ( norm(X) * FERR ) */

/*  A large value is returned if this ratio is not less than one. */

/*  RESLTS(2) = residual from the iterative refinement routine */
/*            = the maximum of BERR / ( NZ*EPS + (*) ), where */
/*              (*) = NZ*UNFL / (min_i (abs(op(A))*abs(X) +abs(b))_i ) */
/*              and NZ = max. number of nonzeros in any row of A, plus 1 */

/*  Arguments */
/*  ========= */

/*  TRANS   (input) CHARACTER*1 */
/*          Specifies the form of the system of equations. */
/*          = 'N':  A * X = B     (No transpose) */
/*          = 'T':  A**T * X = B  (Transpose) */
/*          = 'C':  A**H * X = B  (Conjugate transpose = Transpose) */

/*  N       (input) INTEGER */
/*          The number of rows of the matrices X and XACT.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of columns of the matrices X and XACT.  NRHS >= 0. */

/*  DL      (input) REAL array, dimension (N-1) */
/*          The (n-1) sub-diagonal elements of A. */

/*  D       (input) REAL array, dimension (N) */
/*          The diagonal elements of A. */

/*  DU      (input) REAL array, dimension (N-1) */
/*          The (n-1) super-diagonal elements of A. */

/*  B       (input) REAL array, dimension (LDB,NRHS) */
/*          The right hand side vectors for the system of linear */
/*          equations. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  X       (input) REAL array, dimension (LDX,NRHS) */
/*          The computed solution vectors.  Each vector is stored as a */
/*          column of the matrix X. */

/*  LDX     (input) INTEGER */
/*          The leading dimension of the array X.  LDX >= max(1,N). */

/*  XACT    (input) REAL array, dimension (LDX,NRHS) */
/*          The exact solution vectors.  Each vector is stored as a */
/*          column of the matrix XACT. */

/*  LDXACT  (input) INTEGER */
/*          The leading dimension of the array XACT.  LDXACT >= max(1,N). */

/*  FERR    (input) REAL array, dimension (NRHS) */
/*          The estimated forward error bounds for each solution vector */
/*          X.  If XTRUE is the true solution, FERR bounds the magnitude */
/*          of the largest entry in (X - XTRUE) divided by the magnitude */
/*          of the largest entry in X. */

/*  BERR    (input) REAL array, dimension (NRHS) */
/*          The componentwise relative backward error of each solution */
/*          vector (i.e., the smallest relative change in any entry of A */
/*          or B that makes X an exact solution). */

/*  RESLTS  (output) REAL array, dimension (2) */
/*          The maximum over the NRHS solution vectors of the ratios: */
/*          RESLTS(1) = norm(X - XACT) / ( norm(X) * FERR ) */
/*          RESLTS(2) = BERR / ( NZ*EPS + (*) ) */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick exit if N = 0 or NRHS = 0. */

    /* Parameter adjustments */
    --dl;
    --d__;
    --du;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    xact_dim1 = *ldxact;
    xact_offset = 1 + xact_dim1;
    xact -= xact_offset;
    --ferr;
    --berr;
    --reslts;

    /* Function Body */
    if (*n <= 0 || *nrhs <= 0) {
	reslts[1] = 0.f;
	reslts[2] = 0.f;
	return 0;
    }

    eps = slamch_("Epsilon");
    unfl = slamch_("Safe minimum");
    ovfl = 1.f / unfl;
    notran = lsame_(trans, "N");
    nz = 4;

/*     Test 1:  Compute the maximum of */
/*        norm(X - XACT) / ( norm(X) * FERR ) */
/*     over all the vectors X and XACT using the infinity-norm. */

    errbnd = 0.f;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	imax = isamax_(n, &x[j * x_dim1 + 1], &c__1);
/* Computing MAX */
	r__2 = (r__1 = x[imax + j * x_dim1], dabs(r__1));
	xnorm = dmax(r__2,unfl);
	diff = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
	    r__2 = diff, r__3 = (r__1 = x[i__ + j * x_dim1] - xact[i__ + j * 
		    xact_dim1], dabs(r__1));
	    diff = dmax(r__2,r__3);
/* L10: */
	}

	if (xnorm > 1.f) {
	    goto L20;
	} else if (diff <= ovfl * xnorm) {
	    goto L20;
	} else {
	    errbnd = 1.f / eps;
	    goto L30;
	}

L20:
	if (diff / xnorm <= ferr[j]) {
/* Computing MAX */
	    r__1 = errbnd, r__2 = diff / xnorm / ferr[j];
	    errbnd = dmax(r__1,r__2);
	} else {
	    errbnd = 1.f / eps;
	}
L30:
	;
    }
    reslts[1] = errbnd;

/*     Test 2:  Compute the maximum of BERR / ( NZ*EPS + (*) ), where */
/*     (*) = NZ*UNFL / (min_i (abs(op(A))*abs(X) +abs(b))_i ) */

    i__1 = *nrhs;
    for (k = 1; k <= i__1; ++k) {
	if (notran) {
	    if (*n == 1) {
		axbi = (r__1 = b[k * b_dim1 + 1], dabs(r__1)) + (r__2 = d__[1]
			 * x[k * x_dim1 + 1], dabs(r__2));
	    } else {
		axbi = (r__1 = b[k * b_dim1 + 1], dabs(r__1)) + (r__2 = d__[1]
			 * x[k * x_dim1 + 1], dabs(r__2)) + (r__3 = du[1] * x[
			k * x_dim1 + 2], dabs(r__3));
		i__2 = *n - 1;
		for (i__ = 2; i__ <= i__2; ++i__) {
		    tmp = (r__1 = b[i__ + k * b_dim1], dabs(r__1)) + (r__2 = 
			    dl[i__ - 1] * x[i__ - 1 + k * x_dim1], dabs(r__2))
			     + (r__3 = d__[i__] * x[i__ + k * x_dim1], dabs(
			    r__3)) + (r__4 = du[i__] * x[i__ + 1 + k * x_dim1]
			    , dabs(r__4));
		    axbi = dmin(axbi,tmp);
/* L40: */
		}
		tmp = (r__1 = b[*n + k * b_dim1], dabs(r__1)) + (r__2 = dl[*n 
			- 1] * x[*n - 1 + k * x_dim1], dabs(r__2)) + (r__3 = 
			d__[*n] * x[*n + k * x_dim1], dabs(r__3));
		axbi = dmin(axbi,tmp);
	    }
	} else {
	    if (*n == 1) {
		axbi = (r__1 = b[k * b_dim1 + 1], dabs(r__1)) + (r__2 = d__[1]
			 * x[k * x_dim1 + 1], dabs(r__2));
	    } else {
		axbi = (r__1 = b[k * b_dim1 + 1], dabs(r__1)) + (r__2 = d__[1]
			 * x[k * x_dim1 + 1], dabs(r__2)) + (r__3 = dl[1] * x[
			k * x_dim1 + 2], dabs(r__3));
		i__2 = *n - 1;
		for (i__ = 2; i__ <= i__2; ++i__) {
		    tmp = (r__1 = b[i__ + k * b_dim1], dabs(r__1)) + (r__2 = 
			    du[i__ - 1] * x[i__ - 1 + k * x_dim1], dabs(r__2))
			     + (r__3 = d__[i__] * x[i__ + k * x_dim1], dabs(
			    r__3)) + (r__4 = dl[i__] * x[i__ + 1 + k * x_dim1]
			    , dabs(r__4));
		    axbi = dmin(axbi,tmp);
/* L50: */
		}
		tmp = (r__1 = b[*n + k * b_dim1], dabs(r__1)) + (r__2 = du[*n 
			- 1] * x[*n - 1 + k * x_dim1], dabs(r__2)) + (r__3 = 
			d__[*n] * x[*n + k * x_dim1], dabs(r__3));
		axbi = dmin(axbi,tmp);
	    }
	}
/* Computing MAX */
	r__1 = axbi, r__2 = nz * unfl;
	tmp = berr[k] / (nz * eps + nz * unfl / dmax(r__1,r__2));
	if (k == 1) {
	    reslts[2] = tmp;
	} else {
	    reslts[2] = dmax(reslts[2],tmp);
	}
/* L60: */
    }

    return 0;

/*     End of SGTT05 */

} /* sgtt05_ */
