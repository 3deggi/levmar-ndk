/* ztzt01.f -- translated by f2c (version 20061008).
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

static integer c__8 = 8;
static doublecomplex c_b6 = {0.,0.};
static integer c__1 = 1;
static doublecomplex c_b15 = {-1.,0.};

doublereal ztzt01_(integer *m, integer *n, doublecomplex *a, doublecomplex *
	af, integer *lda, doublecomplex *tau, doublecomplex *work, integer *
	lwork)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, i__1, i__2, i__3, i__4;
    doublereal ret_val;

    /* Local variables */
    integer i__, j;
    doublereal norma, rwork[1];
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    extern /* Subroutine */ int zlaset_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, integer *), zlatzm_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    integer *, doublecomplex *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZTZT01 returns */
/*       || A - R*Q || / ( M * eps * ||A|| ) */
/*  for an upper trapezoidal A that was factored with ZTZRQF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrices A and AF. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrices A and AF. */

/*  A       (input) COMPLEX*16 array, dimension (LDA,N) */
/*          The original upper trapezoidal M by N matrix A. */

/*  AF      (input) COMPLEX*16 array, dimension (LDA,N) */
/*          The output of ZTZRQF for input matrix A. */
/*          The lower triangle is not referenced. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the arrays A and AF. */

/*  TAU     (input) COMPLEX*16 array, dimension (M) */
/*          Details of the  Householder transformations as returned by */
/*          ZTZRQF. */

/*  WORK    (workspace) COMPLEX*16 array, dimension (LWORK) */

/*  LWORK   (input) INTEGER */
/*          The length of the array WORK.  LWORK >= m*n + m. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1;
    af -= af_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    ret_val = 0.;

    if (*lwork < *m * *n + *m) {
	xerbla_("ZTZT01", &c__8);
	return ret_val;
    }

/*     Quick return if possible */

    if (*m <= 0 || *n <= 0) {
	return ret_val;
    }

    norma = zlange_("One-norm", m, n, &a[a_offset], lda, rwork);

/*     Copy upper triangle R */

    zlaset_("Full", m, n, &c_b6, &c_b6, &work[1], m);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = (j - 1) * *m + i__;
	    i__4 = i__ + j * af_dim1;
	    work[i__3].r = af[i__4].r, work[i__3].i = af[i__4].i;
/* L10: */
	}
/* L20: */
    }

/*     R = R * P(1) * ... *P(m) */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *n - *m + 1;
	zlatzm_("Right", &i__, &i__2, &af[i__ + (*m + 1) * af_dim1], lda, &
		tau[i__], &work[(i__ - 1) * *m + 1], &work[*m * *m + 1], m, &
		work[*m * *n + 1]);
/* L30: */
    }

/*     R = R - A */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	zaxpy_(m, &c_b15, &a[i__ * a_dim1 + 1], &c__1, &work[(i__ - 1) * *m + 
		1], &c__1);
/* L40: */
    }

    ret_val = zlange_("One-norm", m, n, &work[1], m, rwork);

    ret_val /= dlamch_("Epsilon") * (doublereal) max(*m,*n);
    if (norma != 0.) {
	ret_val /= norma;
    }

    return ret_val;

/*     End of ZTZT01 */

} /* ztzt01_ */
