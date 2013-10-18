/* dckgsv.f -- translated by f2c (version 20061008).
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
static integer c__1 = 1;
static integer c__0 = 0;

/* Subroutine */ int dckgsv_(integer *nm, integer *mval, integer *pval, 
	integer *nval, integer *nmats, integer *iseed, doublereal *thresh, 
	integer *nmax, doublereal *a, doublereal *af, doublereal *b, 
	doublereal *bf, doublereal *u, doublereal *v, doublereal *q, 
	doublereal *alpha, doublereal *beta, doublereal *r__, integer *iwork, 
	doublereal *work, doublereal *rwork, integer *nin, integer *nout, 
	integer *info)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 DLATMS in DCKGSV   INFO = \002,i5)";
    static char fmt_9998[] = "(\002 M=\002,i4,\002 P=\002,i4,\002, N=\002,"
	    "i4,\002, type \002,i2,\002, test \002,i2,\002, ratio=\002,g13.6)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, m, n, p, im, nt, lda, ldb, kla, klb, kua, kub, ldq, ldr, ldu,
	     ldv, imat;
    char path[3], type__[1];
    integer nrun, modea, modeb, nfail;
    char dista[1], distb[1];
    integer iinfo;
    doublereal anorm, bnorm;
    integer lwork;
    extern /* Subroutine */ int dlatb9_(char *, integer *, integer *, integer 
	    *, integer *, char *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, char *, char *), 
	    alahdg_(integer *, char *);
    doublereal cndnma, cndnmb;
    extern /* Subroutine */ int alareq_(char *, integer *, logical *, integer 
	    *, integer *, integer *), alasum_(char *, integer *, 
	    integer *, integer *, integer *), dlatms_(integer *, 
	    integer *, char *, integer *, char *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, char *, 
	    doublereal *, integer *, doublereal *, integer *);
    logical dotype[8];
    extern /* Subroutine */ int dgsvts_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *, 
	     integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *, 
	     integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *);
    logical firstt;
    doublereal result[7];

    /* Fortran I/O blocks */
    static cilist io___32 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___33 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9998, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DCKGSV tests DGGSVD: */
/*         the GSVD for M-by-N matrix A and P-by-N matrix B. */

/*  Arguments */
/*  ========= */

/*  NM      (input) INTEGER */
/*          The number of values of M contained in the vector MVAL. */

/*  MVAL    (input) INTEGER array, dimension (NM) */
/*          The values of the matrix row dimension M. */

/*  PVAL    (input) INTEGER array, dimension (NP) */
/*          The values of the matrix row dimension P. */

/*  NVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix column dimension N. */

/*  NMATS   (input) INTEGER */
/*          The number of matrix types to be tested for each combination */
/*          of matrix dimensions.  If NMATS >= NTYPES (the maximum */
/*          number of matrix types), then all the different types are */
/*          generated for testing.  If NMATS < NTYPES, another input line */
/*          is read to get the numbers of the matrix types to be used. */

/*  ISEED   (input/output) INTEGER array, dimension (4) */
/*          On entry, the seed of the random number generator.  The array */
/*          elements should be between 0 and 4095, otherwise they will be */
/*          reduced mod 4096, and ISEED(4) must be odd. */
/*          On exit, the next seed in the random number sequence after */
/*          all the test matrices have been generated. */

/*  THRESH  (input) DOUBLE PRECISION */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  NMAX    (input) INTEGER */
/*          The maximum value permitted for M or N, used in dimensioning */
/*          the work arrays. */

/*  A       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  AF      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  B       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  BF      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  U       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  V       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  Q       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  ALPHA   (workspace) DOUBLE PRECISION array, dimension (NMAX) */

/*  BETA    (workspace) DOUBLE PRECISION array, dimension (NMAX) */

/*  R       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  IWORK   (workspace) INTEGER array, dimension (NMAX) */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (NMAX) */

/*  NIN     (input) INTEGER */
/*          The unit number for input. */

/*  NOUT    (input) INTEGER */
/*          The unit number for output. */

/*  INFO    (output) INTEGER */
/*          = 0 :  successful exit */
/*          > 0 :  If DLATMS returns an error code, the absolute value */
/*                 of it is returned. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Initialize constants and the random number seed. */

    /* Parameter adjustments */
    --rwork;
    --work;
    --iwork;
    --r__;
    --beta;
    --alpha;
    --q;
    --v;
    --u;
    --bf;
    --b;
    --af;
    --a;
    --iseed;
    --nval;
    --pval;
    --mval;

    /* Function Body */
    s_copy(path, "GSV", (ftnlen)3, (ftnlen)3);
    *info = 0;
    nrun = 0;
    nfail = 0;
    firstt = TRUE_;
    alareq_(path, nmats, dotype, &c__8, nin, nout);
    lda = *nmax;
    ldb = *nmax;
    ldu = *nmax;
    ldv = *nmax;
    ldq = *nmax;
    ldr = *nmax;
    lwork = *nmax * *nmax;

/*     Do for each value of M in MVAL. */

    i__1 = *nm;
    for (im = 1; im <= i__1; ++im) {
	m = mval[im];
	p = pval[im];
	n = nval[im];

	for (imat = 1; imat <= 8; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat - 1]) {
		goto L20;
	    }

/*           Set up parameters with DLATB9 and generate test */
/*           matrices A and B with DLATMS. */

	    dlatb9_(path, &imat, &m, &p, &n, type__, &kla, &kua, &klb, &kub, &
		    anorm, &bnorm, &modea, &modeb, &cndnma, &cndnmb, dista, 
		    distb);

/*           Generate M by N matrix A */

	    dlatms_(&m, &n, dista, &iseed[1], type__, &rwork[1], &modea, &
		    cndnma, &anorm, &kla, &kua, "No packing", &a[1], &lda, &
		    work[1], &iinfo);
	    if (iinfo != 0) {
		io___32.ciunit = *nout;
		s_wsfe(&io___32);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		goto L20;
	    }

	    dlatms_(&p, &n, distb, &iseed[1], type__, &rwork[1], &modeb, &
		    cndnmb, &bnorm, &klb, &kub, "No packing", &b[1], &ldb, &
		    work[1], &iinfo);
	    if (iinfo != 0) {
		io___33.ciunit = *nout;
		s_wsfe(&io___33);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		goto L20;
	    }

	    nt = 6;

	    dgsvts_(&m, &p, &n, &a[1], &af[1], &lda, &b[1], &bf[1], &ldb, &u[
		    1], &ldu, &v[1], &ldv, &q[1], &ldq, &alpha[1], &beta[1], &
		    r__[1], &ldr, &iwork[1], &work[1], &lwork, &rwork[1], 
		    result);

/*           Print information about the tests that did not */
/*           pass the threshold. */

	    i__2 = nt;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (result[i__ - 1] >= *thresh) {
		    if (nfail == 0 && firstt) {
			firstt = FALSE_;
			alahdg_(nout, path);
		    }
		    io___37.ciunit = *nout;
		    s_wsfe(&io___37);
		    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    ++nfail;
		}
/* L10: */
	    }
	    nrun += nt;
L20:
	    ;
	}
/* L30: */
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &c__0);

    return 0;

/*     End of DCKGSV */

} /* dckgsv_ */
