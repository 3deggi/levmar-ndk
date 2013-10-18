/* dtpt06.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int dtpt06_(doublereal *rcond, doublereal *rcondc, char *
	uplo, char *diag, integer *n, doublereal *ap, doublereal *work, 
	doublereal *rat)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Local variables */
    doublereal eps, rmin, rmax, anorm;
    extern /* Subroutine */ int dlabad_(doublereal *, doublereal *);
    extern doublereal dlamch_(char *);
    doublereal bignum;
    extern doublereal dlantp_(char *, char *, char *, integer *, doublereal *, 
	     doublereal *);
    doublereal smlnum;


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTPT06 computes a test ratio comparing RCOND (the reciprocal */
/*  condition number of a triangular matrix A) and RCONDC, the estimate */
/*  computed by DTPCON.  Information about the triangular matrix A is */
/*  used if one estimate is zero and the other is non-zero to decide if */
/*  underflow in the estimate is justified. */

/*  Arguments */
/*  ========= */

/*  RCOND   (input) DOUBLE PRECISION */
/*          The estimate of the reciprocal condition number obtained by */
/*          forming the explicit inverse of the matrix A and computing */
/*          RCOND = 1/( norm(A) * norm(inv(A)) ). */

/*  RCONDC  (input) DOUBLE PRECISION */
/*          The estimate of the reciprocal condition number computed by */
/*          DTPCON. */

/*  UPLO    (input) CHARACTER */
/*          Specifies whether the matrix A is upper or lower triangular. */
/*          = 'U':  Upper triangular */
/*          = 'L':  Lower triangular */

/*  DIAG    (input) CHARACTER */
/*          Specifies whether or not the matrix A is unit triangular. */
/*          = 'N':  Non-unit triangular */
/*          = 'U':  Unit triangular */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input) DOUBLE PRECISION array, dimension (N*(N+1)/2) */
/*          The upper or lower triangular matrix A, packed columnwise in */
/*          a linear array.  The j-th column of A is stored in the array */
/*          AP as follows: */
/*          if UPLO = 'U', AP((j-1)*j/2 + i) = A(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', */
/*             AP((j-1)*(n-j) + j*(j+1)/2 + i-j) = A(i,j) for j<=i<=n. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  RAT     (output) DOUBLE PRECISION */
/*          The test ratio.  If both RCOND and RCONDC are nonzero, */
/*             RAT = MAX( RCOND, RCONDC )/MIN( RCOND, RCONDC ) - 1. */
/*          If RAT = 0, the two estimates are exactly the same. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --work;
    --ap;

    /* Function Body */
    eps = dlamch_("Epsilon");
    rmax = max(*rcond,*rcondc);
    rmin = min(*rcond,*rcondc);

/*     Do the easy cases first. */

    if (rmin < 0.) {

/*        Invalid value for RCOND or RCONDC, return 1/EPS. */

	*rat = 1. / eps;

    } else if (rmin > 0.) {

/*        Both estimates are positive, return RMAX/RMIN - 1. */

	*rat = rmax / rmin - 1.;

    } else if (rmax == 0.) {

/*        Both estimates zero. */

	*rat = 0.;

    } else {

/*        One estimate is zero, the other is non-zero.  If the matrix is */
/*        ill-conditioned, return the nonzero estimate multiplied by */
/*        1/EPS; if the matrix is badly scaled, return the nonzero */
/*        estimate multiplied by BIGNUM/TMAX, where TMAX is the maximum */
/*        element in absolute value in A. */

	smlnum = dlamch_("Safe minimum");
	bignum = 1. / smlnum;
	dlabad_(&smlnum, &bignum);
	anorm = dlantp_("M", uplo, diag, n, &ap[1], &work[1]);

/* Computing MIN */
	d__1 = bignum / max(1.,anorm), d__2 = 1. / eps;
	*rat = rmax * min(d__1,d__2);
    }

    return 0;

/*     End of DTPT06 */

} /* dtpt06_ */
