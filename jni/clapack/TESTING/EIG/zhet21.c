/* zhet21.f -- translated by f2c (version 20061008).
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

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__1 = 1;

/* Subroutine */ int zhet21_(integer *itype, char *uplo, integer *n, integer *
	kband, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, 
	 doublecomplex *u, integer *ldu, doublecomplex *v, integer *ldv, 
	doublecomplex *tau, doublecomplex *work, doublereal *rwork, 
	doublereal *result)
{
    /* System generated locals */
    integer a_dim1, a_offset, u_dim1, u_offset, v_dim1, v_offset, i__1, i__2, 
	    i__3, i__4, i__5, i__6;
    doublereal d__1, d__2;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    integer j, jr;
    doublereal ulp;
    integer jcol;
    doublereal unfl;
    extern /* Subroutine */ int zher_(char *, integer *, doublereal *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    integer jrow;
    extern /* Subroutine */ int zher2_(char *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    extern logical lsame_(char *, char *);
    integer iinfo;
    doublereal anorm;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *);
    char cuplo[1];
    doublecomplex vsave;
    logical lower;
    doublereal wnorm;
    extern /* Subroutine */ int zunm2l_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int zunm2r_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *), zlanhe_(char *, char *, integer 
	    *, doublecomplex *, integer *, doublereal *);
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *), zlarfy_(
	    char *, integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZHET21 generally checks a decomposition of the form */

/*     A = U S U* */

/*  where * means conjugate transpose, A is hermitian, U is unitary, and */
/*  S is diagonal (if KBAND=0) or (real) symmetric tridiagonal (if */
/*  KBAND=1). */

/*  If ITYPE=1, then U is represented as a dense matrix; otherwise U is */
/*  expressed as a product of Householder transformations, whose vectors */
/*  are stored in the array "V" and whose scaling constants are in "TAU". */
/*  We shall use the letter "V" to refer to the product of Householder */
/*  transformations (which should be equal to U). */

/*  Specifically, if ITYPE=1, then: */

/*     RESULT(1) = | A - U S U* | / ( |A| n ulp ) *and* */
/*     RESULT(2) = | I - UU* | / ( n ulp ) */

/*  If ITYPE=2, then: */

/*     RESULT(1) = | A - V S V* | / ( |A| n ulp ) */

/*  If ITYPE=3, then: */

/*     RESULT(1) = | I - UV* | / ( n ulp ) */

/*  For ITYPE > 1, the transformation U is expressed as a product */
/*  V = H(1)...H(n-2),  where H(j) = I  -  tau(j) v(j) v(j)*  and each */
/*  vector v(j) has its first j elements 0 and the remaining n-j elements */
/*  stored in V(j+1:n,j). */

/*  Arguments */
/*  ========= */

/*  ITYPE   (input) INTEGER */
/*          Specifies the type of tests to be performed. */
/*          1: U expressed as a dense unitary matrix: */
/*             RESULT(1) = | A - U S U* | / ( |A| n ulp )   *and* */
/*             RESULT(2) = | I - UU* | / ( n ulp ) */

/*          2: U expressed as a product V of Housholder transformations: */
/*             RESULT(1) = | A - V S V* | / ( |A| n ulp ) */

/*          3: U expressed both as a dense unitary matrix and */
/*             as a product of Housholder transformations: */
/*             RESULT(1) = | I - UV* | / ( n ulp ) */

/*  UPLO    (input) CHARACTER */
/*          If UPLO='U', the upper triangle of A and V will be used and */
/*          the (strictly) lower triangle will not be referenced. */
/*          If UPLO='L', the lower triangle of A and V will be used and */
/*          the (strictly) upper triangle will not be referenced. */

/*  N       (input) INTEGER */
/*          The size of the matrix.  If it is zero, ZHET21 does nothing. */
/*          It must be at least zero. */

/*  KBAND   (input) INTEGER */
/*          The bandwidth of the matrix.  It may only be zero or one. */
/*          If zero, then S is diagonal, and E is not referenced.  If */
/*          one, then S is symmetric tri-diagonal. */

/*  A       (input) COMPLEX*16 array, dimension (LDA, N) */
/*          The original (unfactored) matrix.  It is assumed to be */
/*          hermitian, and only the upper (UPLO='U') or only the lower */
/*          (UPLO='L') will be referenced. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of A.  It must be at least 1 */
/*          and at least N. */

/*  D       (input) DOUBLE PRECISION array, dimension (N) */
/*          The diagonal of the (symmetric tri-) diagonal matrix. */

/*  E       (input) DOUBLE PRECISION array, dimension (N-1) */
/*          The off-diagonal of the (symmetric tri-) diagonal matrix. */
/*          E(1) is the (1,2) and (2,1) element, E(2) is the (2,3) and */
/*          (3,2) element, etc. */
/*          Not referenced if KBAND=0. */

/*  U       (input) COMPLEX*16 array, dimension (LDU, N) */
/*          If ITYPE=1 or 3, this contains the unitary matrix in */
/*          the decomposition, expressed as a dense matrix.  If ITYPE=2, */
/*          then it is not referenced. */

/*  LDU     (input) INTEGER */
/*          The leading dimension of U.  LDU must be at least N and */
/*          at least 1. */

/*  V       (input) COMPLEX*16 array, dimension (LDV, N) */
/*          If ITYPE=2 or 3, the columns of this array contain the */
/*          Householder vectors used to describe the unitary matrix */
/*          in the decomposition.  If UPLO='L', then the vectors are in */
/*          the lower triangle, if UPLO='U', then in the upper */
/*          triangle. */
/*          *NOTE* If ITYPE=2 or 3, V is modified and restored.  The */
/*          subdiagonal (if UPLO='L') or the superdiagonal (if UPLO='U') */
/*          is set to one, and later reset to its original value, during */
/*          the course of the calculation. */
/*          If ITYPE=1, then it is neither referenced nor modified. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of V.  LDV must be at least N and */
/*          at least 1. */

/*  TAU     (input) COMPLEX*16 array, dimension (N) */
/*          If ITYPE >= 2, then TAU(j) is the scalar factor of */
/*          v(j) v(j)* in the Householder transformation H(j) of */
/*          the product  U = H(1)...H(n-2) */
/*          If ITYPE < 2, then TAU is not referenced. */

/*  WORK    (workspace) COMPLEX*16 array, dimension (2*N**2) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (N) */

/*  RESULT  (output) DOUBLE PRECISION array, dimension (2) */
/*          The values computed by the two tests described above.  The */
/*          values are currently limited to 1/ulp, to avoid overflow. */
/*          RESULT(1) is always modified.  RESULT(2) is modified only */
/*          if ITYPE=1. */

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
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --d__;
    --e;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    --tau;
    --work;
    --rwork;
    --result;

    /* Function Body */
    result[1] = 0.;
    if (*itype == 1) {
	result[2] = 0.;
    }
    if (*n <= 0) {
	return 0;
    }

    if (lsame_(uplo, "U")) {
	lower = FALSE_;
	*(unsigned char *)cuplo = 'U';
    } else {
	lower = TRUE_;
	*(unsigned char *)cuplo = 'L';
    }

    unfl = dlamch_("Safe minimum");
    ulp = dlamch_("Epsilon") * dlamch_("Base");

/*     Some Error Checks */

    if (*itype < 1 || *itype > 3) {
	result[1] = 10. / ulp;
	return 0;
    }

/*     Do Test 1 */

/*     Norm of A: */

    if (*itype == 3) {
	anorm = 1.;
    } else {
/* Computing MAX */
	d__1 = zlanhe_("1", cuplo, n, &a[a_offset], lda, &rwork[1]);
	anorm = max(d__1,unfl);
    }

/*     Compute error matrix: */

    if (*itype == 1) {

/*        ITYPE=1: error = A - U S U* */

	zlaset_("Full", n, n, &c_b1, &c_b1, &work[1], n);
	zlacpy_(cuplo, n, n, &a[a_offset], lda, &work[1], n);

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    d__1 = -d__[j];
	    zher_(cuplo, n, &d__1, &u[j * u_dim1 + 1], &c__1, &work[1], n);
/* L10: */
	}

	if (*n > 1 && *kband == 1) {
	    i__1 = *n - 1;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		z__2.r = e[i__2], z__2.i = 0.;
		z__1.r = -z__2.r, z__1.i = -z__2.i;
		zher2_(cuplo, n, &z__1, &u[j * u_dim1 + 1], &c__1, &u[(j - 1) 
			* u_dim1 + 1], &c__1, &work[1], n);
/* L20: */
	    }
	}
	wnorm = zlanhe_("1", cuplo, n, &work[1], n, &rwork[1]);

    } else if (*itype == 2) {

/*        ITYPE=2: error = V S V* - A */

	zlaset_("Full", n, n, &c_b1, &c_b1, &work[1], n);

	if (lower) {
/* Computing 2nd power */
	    i__2 = *n;
	    i__1 = i__2 * i__2;
	    i__3 = *n;
	    work[i__1].r = d__[i__3], work[i__1].i = 0.;
	    for (j = *n - 1; j >= 1; --j) {
		if (*kband == 1) {
		    i__1 = (*n + 1) * (j - 1) + 2;
		    i__2 = j;
		    z__2.r = 1. - tau[i__2].r, z__2.i = 0. - tau[i__2].i;
		    i__3 = j;
		    z__1.r = e[i__3] * z__2.r, z__1.i = e[i__3] * z__2.i;
		    work[i__1].r = z__1.r, work[i__1].i = z__1.i;
		    i__1 = *n;
		    for (jr = j + 2; jr <= i__1; ++jr) {
			i__2 = (j - 1) * *n + jr;
			i__3 = j;
			z__3.r = -tau[i__3].r, z__3.i = -tau[i__3].i;
			i__4 = j;
			z__2.r = e[i__4] * z__3.r, z__2.i = e[i__4] * z__3.i;
			i__5 = jr + j * v_dim1;
			z__1.r = z__2.r * v[i__5].r - z__2.i * v[i__5].i, 
				z__1.i = z__2.r * v[i__5].i + z__2.i * v[i__5]
				.r;
			work[i__2].r = z__1.r, work[i__2].i = z__1.i;
/* L30: */
		    }
		}

		i__1 = j + 1 + j * v_dim1;
		vsave.r = v[i__1].r, vsave.i = v[i__1].i;
		i__1 = j + 1 + j * v_dim1;
		v[i__1].r = 1., v[i__1].i = 0.;
		i__1 = *n - j;
/* Computing 2nd power */
		i__2 = *n;
		zlarfy_("L", &i__1, &v[j + 1 + j * v_dim1], &c__1, &tau[j], &
			work[(*n + 1) * j + 1], n, &work[i__2 * i__2 + 1]);
		i__1 = j + 1 + j * v_dim1;
		v[i__1].r = vsave.r, v[i__1].i = vsave.i;
		i__1 = (*n + 1) * (j - 1) + 1;
		i__2 = j;
		work[i__1].r = d__[i__2], work[i__1].i = 0.;
/* L40: */
	    }
	} else {
	    work[1].r = d__[1], work[1].i = 0.;
	    i__1 = *n - 1;
	    for (j = 1; j <= i__1; ++j) {
		if (*kband == 1) {
		    i__2 = (*n + 1) * j;
		    i__3 = j;
		    z__2.r = 1. - tau[i__3].r, z__2.i = 0. - tau[i__3].i;
		    i__4 = j;
		    z__1.r = e[i__4] * z__2.r, z__1.i = e[i__4] * z__2.i;
		    work[i__2].r = z__1.r, work[i__2].i = z__1.i;
		    i__2 = j - 1;
		    for (jr = 1; jr <= i__2; ++jr) {
			i__3 = j * *n + jr;
			i__4 = j;
			z__3.r = -tau[i__4].r, z__3.i = -tau[i__4].i;
			i__5 = j;
			z__2.r = e[i__5] * z__3.r, z__2.i = e[i__5] * z__3.i;
			i__6 = jr + (j + 1) * v_dim1;
			z__1.r = z__2.r * v[i__6].r - z__2.i * v[i__6].i, 
				z__1.i = z__2.r * v[i__6].i + z__2.i * v[i__6]
				.r;
			work[i__3].r = z__1.r, work[i__3].i = z__1.i;
/* L50: */
		    }
		}

		i__2 = j + (j + 1) * v_dim1;
		vsave.r = v[i__2].r, vsave.i = v[i__2].i;
		i__2 = j + (j + 1) * v_dim1;
		v[i__2].r = 1., v[i__2].i = 0.;
/* Computing 2nd power */
		i__2 = *n;
		zlarfy_("U", &j, &v[(j + 1) * v_dim1 + 1], &c__1, &tau[j], &
			work[1], n, &work[i__2 * i__2 + 1]);
		i__2 = j + (j + 1) * v_dim1;
		v[i__2].r = vsave.r, v[i__2].i = vsave.i;
		i__2 = (*n + 1) * j + 1;
		i__3 = j + 1;
		work[i__2].r = d__[i__3], work[i__2].i = 0.;
/* L60: */
	    }
	}

	i__1 = *n;
	for (jcol = 1; jcol <= i__1; ++jcol) {
	    if (lower) {
		i__2 = *n;
		for (jrow = jcol; jrow <= i__2; ++jrow) {
		    i__3 = jrow + *n * (jcol - 1);
		    i__4 = jrow + *n * (jcol - 1);
		    i__5 = jrow + jcol * a_dim1;
		    z__1.r = work[i__4].r - a[i__5].r, z__1.i = work[i__4].i 
			    - a[i__5].i;
		    work[i__3].r = z__1.r, work[i__3].i = z__1.i;
/* L70: */
		}
	    } else {
		i__2 = jcol;
		for (jrow = 1; jrow <= i__2; ++jrow) {
		    i__3 = jrow + *n * (jcol - 1);
		    i__4 = jrow + *n * (jcol - 1);
		    i__5 = jrow + jcol * a_dim1;
		    z__1.r = work[i__4].r - a[i__5].r, z__1.i = work[i__4].i 
			    - a[i__5].i;
		    work[i__3].r = z__1.r, work[i__3].i = z__1.i;
/* L80: */
		}
	    }
/* L90: */
	}
	wnorm = zlanhe_("1", cuplo, n, &work[1], n, &rwork[1]);

    } else if (*itype == 3) {

/*        ITYPE=3: error = U V* - I */

	if (*n < 2) {
	    return 0;
	}
	zlacpy_(" ", n, n, &u[u_offset], ldu, &work[1], n);
	if (lower) {
	    i__1 = *n - 1;
	    i__2 = *n - 1;
/* Computing 2nd power */
	    i__3 = *n;
	    zunm2r_("R", "C", n, &i__1, &i__2, &v[v_dim1 + 2], ldv, &tau[1], &
		    work[*n + 1], n, &work[i__3 * i__3 + 1], &iinfo);
	} else {
	    i__1 = *n - 1;
	    i__2 = *n - 1;
/* Computing 2nd power */
	    i__3 = *n;
	    zunm2l_("R", "C", n, &i__1, &i__2, &v[(v_dim1 << 1) + 1], ldv, &
		    tau[1], &work[1], n, &work[i__3 * i__3 + 1], &iinfo);
	}
	if (iinfo != 0) {
	    result[1] = 10. / ulp;
	    return 0;
	}

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = (*n + 1) * (j - 1) + 1;
	    i__3 = (*n + 1) * (j - 1) + 1;
	    z__1.r = work[i__3].r - 1., z__1.i = work[i__3].i - 0.;
	    work[i__2].r = z__1.r, work[i__2].i = z__1.i;
/* L100: */
	}

	wnorm = zlange_("1", n, n, &work[1], n, &rwork[1]);
    }

    if (anorm > wnorm) {
	result[1] = wnorm / anorm / (*n * ulp);
    } else {
	if (anorm < 1.) {
/* Computing MIN */
	    d__1 = wnorm, d__2 = *n * anorm;
	    result[1] = min(d__1,d__2) / anorm / (*n * ulp);
	} else {
/* Computing MIN */
	    d__1 = wnorm / anorm, d__2 = (doublereal) (*n);
	    result[1] = min(d__1,d__2) / (*n * ulp);
	}
    }

/*     Do Test 2 */

/*     Compute  UU* - I */

    if (*itype == 1) {
	zgemm_("N", "C", n, n, n, &c_b2, &u[u_offset], ldu, &u[u_offset], ldu, 
		 &c_b1, &work[1], n);

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = (*n + 1) * (j - 1) + 1;
	    i__3 = (*n + 1) * (j - 1) + 1;
	    z__1.r = work[i__3].r - 1., z__1.i = work[i__3].i - 0.;
	    work[i__2].r = z__1.r, work[i__2].i = z__1.i;
/* L110: */
	}

/* Computing MIN */
	d__1 = zlange_("1", n, n, &work[1], n, &rwork[1]), d__2 = (
		doublereal) (*n);
	result[2] = min(d__1,d__2) / (*n * ulp);
    }

    return 0;

/*     End of ZHET21 */

} /* zhet21_ */
