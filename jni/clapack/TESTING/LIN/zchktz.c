/* zchktz.f -- translated by f2c (version 20061008).
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

/* Common Block Declarations */

struct {
    integer infot, iounit;
    logical ok, lerr;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[32];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static doublecomplex c_b10 = {0.,0.};
static doublereal c_b15 = 1.;
static integer c__1 = 1;

/* Subroutine */ int zchktz_(logical *dotype, integer *nm, integer *mval, 
	integer *nn, integer *nval, doublereal *thresh, logical *tsterr, 
	doublecomplex *a, doublecomplex *copya, doublereal *s, doublereal *
	copys, doublecomplex *tau, doublecomplex *work, doublereal *rwork, 
	integer *nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 1988,1989,1990,1991 };

    /* Format strings */
    static char fmt_9999[] = "(\002 M =\002,i5,\002, N =\002,i5,\002, type"
	    " \002,i2,\002, test \002,i2,\002, ratio =\002,g12.5)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, k, m, n, im, in, lda;
    doublereal eps;
    integer mode, info;
    char path[3];
    integer nrun;
    extern /* Subroutine */ int alahd_(integer *, char *);
    integer nfail, iseed[4], imode, mnmin, nerrs, lwork;
    extern doublereal zqrt12_(integer *, integer *, doublecomplex *, integer *
, doublereal *, doublecomplex *, integer *, doublereal *), 
	    zrzt01_(integer *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *), zrzt02_(
	    integer *, integer *, doublecomplex *, integer *, doublecomplex *, 
	     doublecomplex *, integer *), ztzt01_(integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *), ztzt02_(integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *);
    extern /* Subroutine */ int zgeqr2_(integer *, integer *, doublecomplex *, 
	     integer *, doublecomplex *, doublecomplex *, integer *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int dlaord_(char *, integer *, doublereal *, 
	    integer *), alasum_(char *, integer *, integer *, integer 
	    *, integer *), zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *), zlatms_(
	    integer *, integer *, char *, integer *, char *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, integer *, char 
	    *, doublecomplex *, integer *, doublecomplex *, integer *);
    doublereal result[6];
    extern /* Subroutine */ int zerrtz_(char *, integer *), ztzrqf_(
	    integer *, integer *, doublecomplex *, integer *, doublecomplex *, 
	     integer *), ztzrzf_(integer *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, integer *)
	    ;

    /* Fortran I/O blocks */
    static cilist io___21 = { 0, 0, 0, fmt_9999, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZCHKTZ tests ZTZRQF and ZTZRZF. */

/*  Arguments */
/*  ========= */

/*  DOTYPE  (input) LOGICAL array, dimension (NTYPES) */
/*          The matrix types to be used for testing.  Matrices of type j */
/*          (for 1 <= j <= NTYPES) are used for testing if DOTYPE(j) = */
/*          .TRUE.; if DOTYPE(j) = .FALSE., then type j is not used. */

/*  NM      (input) INTEGER */
/*          The number of values of M contained in the vector MVAL. */

/*  MVAL    (input) INTEGER array, dimension (NM) */
/*          The values of the matrix row dimension M. */

/*  NN      (input) INTEGER */
/*          The number of values of N contained in the vector NVAL. */

/*  NVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix column dimension N. */

/*  THRESH  (input) DOUBLE PRECISION */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  TSTERR  (input) LOGICAL */
/*          Flag that indicates whether error exits are to be tested. */

/*  A       (workspace) COMPLEX*16 array, dimension (MMAX*NMAX) */
/*          where MMAX is the maximum value of M in MVAL and NMAX is the */
/*          maximum value of N in NVAL. */

/*  COPYA   (workspace) COMPLEX*16 array, dimension (MMAX*NMAX) */

/*  S       (workspace) DOUBLE PRECISION array, dimension */
/*                      (min(MMAX,NMAX)) */

/*  COPYS   (workspace) DOUBLE PRECISION array, dimension */
/*                      (min(MMAX,NMAX)) */

/*  TAU     (workspace) COMPLEX*16 array, dimension (MMAX) */

/*  WORK    (workspace) COMPLEX*16 array, dimension */
/*                      (MMAX*NMAX + 4*NMAX + MMAX) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (2*NMAX) */

/*  NOUT    (input) INTEGER */
/*          The unit number for output. */

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
/*     .. Scalars in Common .. */
/*     .. */
/*     .. Common blocks .. */
/*     .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --rwork;
    --work;
    --tau;
    --copys;
    --s;
    --copya;
    --a;
    --nval;
    --mval;
    --dotype;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

/*     Initialize constants and the random number seed. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "TZ", (ftnlen)2, (ftnlen)2);
    nrun = 0;
    nfail = 0;
    nerrs = 0;
    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__ - 1] = iseedy[i__ - 1];
/* L10: */
    }
    eps = dlamch_("Epsilon");

/*     Test the error exits */

    if (*tsterr) {
	zerrtz_(path, nout);
    }
    infoc_1.infot = 0;

    i__1 = *nm;
    for (im = 1; im <= i__1; ++im) {

/*        Do for each value of M in MVAL. */

	m = mval[im];
	lda = max(1,m);

	i__2 = *nn;
	for (in = 1; in <= i__2; ++in) {

/*           Do for each value of N in NVAL for which M .LE. N. */

	    n = nval[in];
	    mnmin = min(m,n);
/* Computing MAX */
	    i__3 = 1, i__4 = n * n + (m << 2) + n;
	    lwork = max(i__3,i__4);

	    if (m <= n) {
		for (imode = 1; imode <= 3; ++imode) {

/*                 Do for each type of singular value distribution. */
/*                    0:  zero matrix */
/*                    1:  one small singular value */
/*                    2:  exponential distribution */

		    mode = imode - 1;

/*                 Test ZTZRQF */

/*                 Generate test matrix of size m by n using */
/*                 singular value distribution indicated by `mode'. */

		    if (mode == 0) {
			zlaset_("Full", &m, &n, &c_b10, &c_b10, &a[1], &lda);
			i__3 = mnmin;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    copys[i__] = 0.;
/* L20: */
			}
		    } else {
			d__1 = 1. / eps;
			zlatms_(&m, &n, "Uniform", iseed, "Nonsymmetric", &
				copys[1], &imode, &d__1, &c_b15, &m, &n, 
				"No packing", &a[1], &lda, &work[1], &info);
			zgeqr2_(&m, &n, &a[1], &lda, &work[1], &work[mnmin + 
				1], &info);
			i__3 = m - 1;
			zlaset_("Lower", &i__3, &n, &c_b10, &c_b10, &a[2], &
				lda);
			dlaord_("Decreasing", &mnmin, &copys[1], &c__1);
		    }

/*                 Save A and its singular values */

		    zlacpy_("All", &m, &n, &a[1], &lda, &copya[1], &lda);

/*                 Call ZTZRQF to reduce the upper trapezoidal matrix to */
/*                 upper triangular form. */

		    s_copy(srnamc_1.srnamt, "ZTZRQF", (ftnlen)32, (ftnlen)6);
		    ztzrqf_(&m, &n, &a[1], &lda, &tau[1], &info);

/*                 Compute norm(svd(a) - svd(r)) */

		    result[0] = zqrt12_(&m, &m, &a[1], &lda, &copys[1], &work[
			    1], &lwork, &rwork[1]);

/*                 Compute norm( A - R*Q ) */

		    result[1] = ztzt01_(&m, &n, &copya[1], &a[1], &lda, &tau[
			    1], &work[1], &lwork);

/*                 Compute norm(Q'*Q - I). */

		    result[2] = ztzt02_(&m, &n, &a[1], &lda, &tau[1], &work[1]
, &lwork);

/*                 Test ZTZRZF */

/*                 Generate test matrix of size m by n using */
/*                 singular value distribution indicated by `mode'. */

		    if (mode == 0) {
			zlaset_("Full", &m, &n, &c_b10, &c_b10, &a[1], &lda);
			i__3 = mnmin;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    copys[i__] = 0.;
/* L30: */
			}
		    } else {
			d__1 = 1. / eps;
			zlatms_(&m, &n, "Uniform", iseed, "Nonsymmetric", &
				copys[1], &imode, &d__1, &c_b15, &m, &n, 
				"No packing", &a[1], &lda, &work[1], &info);
			zgeqr2_(&m, &n, &a[1], &lda, &work[1], &work[mnmin + 
				1], &info);
			i__3 = m - 1;
			zlaset_("Lower", &i__3, &n, &c_b10, &c_b10, &a[2], &
				lda);
			dlaord_("Decreasing", &mnmin, &copys[1], &c__1);
		    }

/*                 Save A and its singular values */

		    zlacpy_("All", &m, &n, &a[1], &lda, &copya[1], &lda);

/*                 Call ZTZRZF to reduce the upper trapezoidal matrix to */
/*                 upper triangular form. */

		    s_copy(srnamc_1.srnamt, "ZTZRZF", (ftnlen)32, (ftnlen)6);
		    ztzrzf_(&m, &n, &a[1], &lda, &tau[1], &work[1], &lwork, &
			    info);

/*                 Compute norm(svd(a) - svd(r)) */

		    result[3] = zqrt12_(&m, &m, &a[1], &lda, &copys[1], &work[
			    1], &lwork, &rwork[1]);

/*                 Compute norm( A - R*Q ) */

		    result[4] = zrzt01_(&m, &n, &copya[1], &a[1], &lda, &tau[
			    1], &work[1], &lwork);

/*                 Compute norm(Q'*Q - I). */

		    result[5] = zrzt02_(&m, &n, &a[1], &lda, &tau[1], &work[1]
, &lwork);

/*                 Print information about the tests that did not pass */
/*                 the threshold. */

		    for (k = 1; k <= 6; ++k) {
			if (result[k - 1] >= *thresh) {
			    if (nfail == 0 && nerrs == 0) {
				alahd_(nout, path);
			    }
			    io___21.ciunit = *nout;
			    s_wsfe(&io___21);
			    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&imode, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&result[k - 1], (ftnlen)
				    sizeof(doublereal));
			    e_wsfe();
			    ++nfail;
			}
/* L40: */
		    }
		    nrun += 6;
/* L50: */
		}
	    }
/* L60: */
	}
/* L70: */
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &nerrs);


/*     End if ZCHKTZ */

    return 0;
} /* zchktz_ */
