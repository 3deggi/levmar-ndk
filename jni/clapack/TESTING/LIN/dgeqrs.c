/* dgeqrs.f -- translated by f2c (version 20061008).
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

static doublereal c_b9 = 1.;

/* Subroutine */ int dgeqrs_(integer *m, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *tau, doublereal *b, integer *
	ldb, doublereal *work, integer *lwork, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Local variables */
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *, 
	    integer *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *), xerbla_(
	    char *, integer *), dormqr_(char *, char *, integer *, 
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *);


/*  -- LAPACK routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  Solve the least squares problem */
/*      min || A*X - B || */
/*  using the QR factorization */
/*      A = Q*R */
/*  computed by DGEQRF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  M >= N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of columns of B.  NRHS >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          Details of the QR factorization of the original matrix A as */
/*          returned by DGEQRF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= M. */

/*  TAU     (input) DOUBLE PRECISION array, dimension (N) */
/*          Details of the orthogonal matrix Q. */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          On entry, the m-by-nrhs right hand side matrix B. */
/*          On exit, the n-by-nrhs solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B. LDB >= M. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK) */

/*  LWORK   (input) INTEGER */
/*          The length of the array WORK.  LWORK must be at least NRHS, */
/*          and should be at least NRHS*NB, where NB is the block size */
/*          for this environment. */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0 || *n > *m) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else if (*ldb < max(1,*m)) {
	*info = -8;
    } else if (*lwork < 1 || *lwork < *nrhs && *m > 0 && *n > 0) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0 || *m == 0) {
	return 0;
    }

/*     B := Q' * B */

    dormqr_("Left", "Transpose", m, nrhs, n, &a[a_offset], lda, &tau[1], &b[
	    b_offset], ldb, &work[1], lwork, info);

/*     Solve R*X = B(1:n,:) */

    dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &c_b9, &a[
	    a_offset], lda, &b[b_offset], ldb);

    return 0;

/*     End of DGEQRS */

} /* dgeqrs_ */
