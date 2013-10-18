/* dlarge.f -- translated by f2c (version 20061008).
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

static integer c__3 = 3;
static integer c__1 = 1;
static doublereal c_b8 = 1.;
static doublereal c_b10 = 0.;

/* Subroutine */ int dlarge_(integer *n, doublereal *a, integer *lda, integer 
	*iseed, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;
    doublereal d__1;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);

    /* Local variables */
    integer i__;
    doublereal wa, wb, wn, tau;
    extern /* Subroutine */ int dger_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *), dgemv_(char *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *), xerbla_(char *, integer *), dlarnv_(integer *, integer *, integer *, doublereal *);


/*  -- LAPACK auxiliary test routine (version 3.1) */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARGE pre- and post-multiplies a real general n by n matrix A */
/*  with a random orthogonal matrix: A = U*D*U'. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the original n by n matrix A. */
/*          On exit, A is overwritten by U*A*U' for some random */
/*          orthogonal matrix U. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= N. */

/*  ISEED   (input/output) INTEGER array, dimension (4) */
/*          On entry, the seed of the random number generator; the array */
/*          elements must be between 0 and 4095, and ISEED(4) must be */
/*          odd. */
/*          On exit, the seed is updated. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (2*N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --iseed;
    --work;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*lda < max(1,*n)) {
	*info = -3;
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("DLARGE", &i__1);
	return 0;
    }

/*     pre- and post-multiply A by random orthogonal matrix */

    for (i__ = *n; i__ >= 1; --i__) {

/*        generate random reflection */

	i__1 = *n - i__ + 1;
	dlarnv_(&c__3, &iseed[1], &i__1, &work[1]);
	i__1 = *n - i__ + 1;
	wn = dnrm2_(&i__1, &work[1], &c__1);
	wa = d_sign(&wn, &work[1]);
	if (wn == 0.) {
	    tau = 0.;
	} else {
	    wb = work[1] + wa;
	    i__1 = *n - i__;
	    d__1 = 1. / wb;
	    dscal_(&i__1, &d__1, &work[2], &c__1);
	    work[1] = 1.;
	    tau = wb / wa;
	}

/*        multiply A(i:n,1:n) by random reflection from the left */

	i__1 = *n - i__ + 1;
	dgemv_("Transpose", &i__1, n, &c_b8, &a[i__ + a_dim1], lda, &work[1], 
		&c__1, &c_b10, &work[*n + 1], &c__1);
	i__1 = *n - i__ + 1;
	d__1 = -tau;
	dger_(&i__1, n, &d__1, &work[1], &c__1, &work[*n + 1], &c__1, &a[i__ 
		+ a_dim1], lda);

/*        multiply A(1:n,i:n) by random reflection from the right */

	i__1 = *n - i__ + 1;
	dgemv_("No transpose", n, &i__1, &c_b8, &a[i__ * a_dim1 + 1], lda, &
		work[1], &c__1, &c_b10, &work[*n + 1], &c__1);
	i__1 = *n - i__ + 1;
	d__1 = -tau;
	dger_(n, &i__1, &d__1, &work[*n + 1], &c__1, &work[1], &c__1, &a[i__ *
		 a_dim1 + 1], lda);
/* L10: */
    }
    return 0;

/*     End of DLARGE */

} /* dlarge_ */
