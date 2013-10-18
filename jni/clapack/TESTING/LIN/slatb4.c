/* slatb4.f -- translated by f2c (version 20061008).
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

static integer c__2 = 2;

/* Subroutine */ int slatb4_(char *path, integer *imat, integer *m, integer *
	n, char *type__, integer *kl, integer *ku, real *anorm, integer *mode, 
	 real *cndnum, char *dist)
{
    /* Initialized data */

    static logical first = TRUE_;

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sqrt(doublereal);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    char c2[2];
    integer mat;
    static real eps, badc1, badc2, large, small;
    extern /* Subroutine */ int slabad_(real *, real *);
    extern doublereal slamch_(char *);
    extern logical lsamen_(integer *, char *, char *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SLATB4 sets parameters for the matrix generator based on the type of */
/*  matrix to be generated. */

/*  Arguments */
/*  ========= */

/*  PATH    (input) CHARACTER*3 */
/*          The LAPACK path name. */

/*  IMAT    (input) INTEGER */
/*          An integer key describing which matrix to generate for this */
/*          path. */

/*  M       (input) INTEGER */
/*          The number of rows in the matrix to be generated. */

/*  N       (input) INTEGER */
/*          The number of columns in the matrix to be generated. */

/*  TYPE    (output) CHARACTER*1 */
/*          The type of the matrix to be generated: */
/*          = 'S':  symmetric matrix */
/*          = 'P':  symmetric positive (semi)definite matrix */
/*          = 'N':  nonsymmetric matrix */

/*  KL      (output) INTEGER */
/*          The lower band width of the matrix to be generated. */

/*  KU      (output) INTEGER */
/*          The upper band width of the matrix to be generated. */

/*  ANORM   (output) REAL */
/*          The desired norm of the matrix to be generated.  The diagonal */
/*          matrix of singular values or eigenvalues is scaled by this */
/*          value. */

/*  MODE    (output) INTEGER */
/*          A key indicating how to choose the vector of eigenvalues. */

/*  CNDNUM  (output) REAL */
/*          The desired condition number. */

/*  DIST    (output) CHARACTER*1 */
/*          The type of distribution to be used by the random number */
/*          generator. */

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
/*     .. Save statement .. */
/*     .. */
/*     .. Data statements .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Set some constants for use in the subroutine. */

    if (first) {
	first = FALSE_;
	eps = slamch_("Precision");
	badc2 = .1f / eps;
	badc1 = sqrt(badc2);
	small = slamch_("Safe minimum");
	large = 1.f / small;

/*        If it looks like we're on a Cray, take the square root of */
/*        SMALL and LARGE to avoid overflow and underflow problems. */

	slabad_(&small, &large);
	small = small / eps * .25f;
	large = 1.f / small;
    }

    s_copy(c2, path + 1, (ftnlen)2, (ftnlen)2);

/*     Set some parameters we don't plan to change. */

    *(unsigned char *)dist = 'S';
    *mode = 3;

    if (lsamen_(&c__2, c2, "QR") || lsamen_(&c__2, c2, 
	    "LQ") || lsamen_(&c__2, c2, "QL") || lsamen_(&c__2, c2, "RQ")) {

/*        xQR, xLQ, xQL, xRQ:  Set parameters to generate a general */
/*                             M x N matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the lower and upper bandwidths. */

	if (*imat == 1) {
	    *kl = 0;
	    *ku = 0;
	} else if (*imat == 2) {
	    *kl = 0;
/* Computing MAX */
	    i__1 = *n - 1;
	    *ku = max(i__1,0);
	} else if (*imat == 3) {
/* Computing MAX */
	    i__1 = *m - 1;
	    *kl = max(i__1,0);
	    *ku = 0;
	} else {
/* Computing MAX */
	    i__1 = *m - 1;
	    *kl = max(i__1,0);
/* Computing MAX */
	    i__1 = *n - 1;
	    *ku = max(i__1,0);
	}

/*        Set the condition number and norm. */

	if (*imat == 5) {
	    *cndnum = badc1;
	} else if (*imat == 6) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 7) {
	    *anorm = small;
	} else if (*imat == 8) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "GE")) {

/*        xGE:  Set parameters to generate a general M x N matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the lower and upper bandwidths. */

	if (*imat == 1) {
	    *kl = 0;
	    *ku = 0;
	} else if (*imat == 2) {
	    *kl = 0;
/* Computing MAX */
	    i__1 = *n - 1;
	    *ku = max(i__1,0);
	} else if (*imat == 3) {
/* Computing MAX */
	    i__1 = *m - 1;
	    *kl = max(i__1,0);
	    *ku = 0;
	} else {
/* Computing MAX */
	    i__1 = *m - 1;
	    *kl = max(i__1,0);
/* Computing MAX */
	    i__1 = *n - 1;
	    *ku = max(i__1,0);
	}

/*        Set the condition number and norm. */

	if (*imat == 8) {
	    *cndnum = badc1;
	} else if (*imat == 9) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 10) {
	    *anorm = small;
	} else if (*imat == 11) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "GB")) {

/*        xGB:  Set parameters to generate a general banded matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the condition number and norm. */

	if (*imat == 5) {
	    *cndnum = badc1;
	} else if (*imat == 6) {
	    *cndnum = badc2 * .1f;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 7) {
	    *anorm = small;
	} else if (*imat == 8) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "GT")) {

/*        xGT:  Set parameters to generate a general tridiagonal matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the lower and upper bandwidths. */

	if (*imat == 1) {
	    *kl = 0;
	} else {
	    *kl = 1;
	}
	*ku = *kl;

/*        Set the condition number and norm. */

	if (*imat == 3) {
	    *cndnum = badc1;
	} else if (*imat == 4) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 5 || *imat == 11) {
	    *anorm = small;
	} else if (*imat == 6 || *imat == 12) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "PO") || lsamen_(&
	    c__2, c2, "PP") || lsamen_(&c__2, c2, "SY") || lsamen_(&c__2, c2, "SP")) {

/*        xPO, xPP, xSY, xSP: Set parameters to generate a */
/*        symmetric matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = *(unsigned char *)c2;

/*        Set the lower and upper bandwidths. */

	if (*imat == 1) {
	    *kl = 0;
	} else {
/* Computing MAX */
	    i__1 = *n - 1;
	    *kl = max(i__1,0);
	}
	*ku = *kl;

/*        Set the condition number and norm. */

	if (*imat == 6) {
	    *cndnum = badc1;
	} else if (*imat == 7) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 8) {
	    *anorm = small;
	} else if (*imat == 9) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "PB")) {

/*        xPB:  Set parameters to generate a symmetric band matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'P';

/*        Set the norm and condition number. */

	if (*imat == 5) {
	    *cndnum = badc1;
	} else if (*imat == 6) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 7) {
	    *anorm = small;
	} else if (*imat == 8) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "PT")) {

/*        xPT:  Set parameters to generate a symmetric positive definite */
/*        tridiagonal matrix. */

	*(unsigned char *)type__ = 'P';
	if (*imat == 1) {
	    *kl = 0;
	} else {
	    *kl = 1;
	}
	*ku = *kl;

/*        Set the condition number and norm. */

	if (*imat == 3) {
	    *cndnum = badc1;
	} else if (*imat == 4) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 5 || *imat == 11) {
	    *anorm = small;
	} else if (*imat == 6 || *imat == 12) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "TR") || lsamen_(&
	    c__2, c2, "TP")) {

/*        xTR, xTP:  Set parameters to generate a triangular matrix */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the lower and upper bandwidths. */

	mat = abs(*imat);
	if (mat == 1 || mat == 7) {
	    *kl = 0;
	    *ku = 0;
	} else if (*imat < 0) {
/* Computing MAX */
	    i__1 = *n - 1;
	    *kl = max(i__1,0);
	    *ku = 0;
	} else {
	    *kl = 0;
/* Computing MAX */
	    i__1 = *n - 1;
	    *ku = max(i__1,0);
	}

/*        Set the condition number and norm. */

	if (mat == 3 || mat == 9) {
	    *cndnum = badc1;
	} else if (mat == 4) {
	    *cndnum = badc2;
	} else if (mat == 10) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (mat == 5) {
	    *anorm = small;
	} else if (mat == 6) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}

    } else if (lsamen_(&c__2, c2, "TB")) {

/*        xTB:  Set parameters to generate a triangular band matrix. */

/*        Set TYPE, the type of matrix to be generated. */

	*(unsigned char *)type__ = 'N';

/*        Set the norm and condition number. */

	if (*imat == 2 || *imat == 8) {
	    *cndnum = badc1;
	} else if (*imat == 3 || *imat == 9) {
	    *cndnum = badc2;
	} else {
	    *cndnum = 2.f;
	}

	if (*imat == 4) {
	    *anorm = small;
	} else if (*imat == 5) {
	    *anorm = large;
	} else {
	    *anorm = 1.f;
	}
    }
    if (*n <= 1) {
	*cndnum = 1.f;
    }

    return 0;

/*     End of SLATB4 */

} /* slatb4_ */
