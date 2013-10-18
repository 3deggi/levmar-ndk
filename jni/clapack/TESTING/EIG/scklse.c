/* scklse.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int scklse_(integer *nn, integer *mval, integer *pval, 
	integer *nval, integer *nmats, integer *iseed, real *thresh, integer *
	nmax, real *a, real *af, real *b, real *bf, real *x, real *work, real 
	*rwork, integer *nin, integer *nout, integer *info)
{
    /* Format strings */
    static char fmt_9997[] = "(\002 *** Invalid input  for LSE:  M = \002,"
	    "i6,\002, P = \002,i6,\002, N = \002,i6,\002;\002,/\002     must "
	    "satisfy P <= N <= P+M  \002,\002(this set of values will be skip"
	    "ped)\002)";
    static char fmt_9999[] = "(\002 SLATMS in SCKLSE   INFO = \002,i5)";
    static char fmt_9998[] = "(\002 M=\002,i4,\002 P=\002,i4,\002, N=\002,"
	    "i4,\002, type \002,i2,\002, test \002,i2,\002, ratio=\002,g13.6)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6, i__7;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, m, n, p, ik, nt, lda, ldb, kla, klb, kua, kub, imat;
    char path[3], type__[1];
    integer nrun, modea, modeb, nfail;
    char dista[1], distb[1];
    integer iinfo;
    real anorm, bnorm;
    integer lwork;
    extern /* Subroutine */ int slatb9_(char *, integer *, integer *, integer 
	    *, integer *, char *, integer *, integer *, integer *, integer *, 
	    real *, real *, integer *, integer *, real *, real *, char *, 
	    char *), alahdg_(integer *, char *
);
    real cndnma, cndnmb;
    extern /* Subroutine */ int alareq_(char *, integer *, logical *, integer 
	    *, integer *, integer *), alasum_(char *, integer *, 
	    integer *, integer *, integer *), slarhs_(char *, char *, 
	    char *, char *, integer *, integer *, integer *, integer *, 
	    integer *, real *, integer *, real *, integer *, real *, integer *
, integer *, integer *), slatms_(
	    integer *, integer *, char *, integer *, char *, real *, integer *
, real *, real *, integer *, integer *, char *, real *, integer *, 
	     real *, integer *);
    logical dotype[8], firstt;
    extern /* Subroutine */ int slsets_(integer *, integer *, integer *, real 
	    *, real *, integer *, real *, real *, integer *, real *, real *, 
	    real *, real *, real *, real *, integer *, real *, real *);
    real result[7];

    /* Fortran I/O blocks */
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_9998, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SCKLSE tests SGGLSE - a subroutine for solving linear equality */
/*  constrained least square problem (LSE). */

/*  Arguments */
/*  ========= */

/*  NN      (input) INTEGER */
/*          The number of values of (M,P,N) contained in the vectors */
/*          (MVAL, PVAL, NVAL). */

/*  MVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix row(column) dimension M. */

/*  PVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix row(column) dimension P. */

/*  NVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix column(row) dimension N. */

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

/*  THRESH  (input) REAL */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  NMAX    (input) INTEGER */
/*          The maximum value permitted for M or N, used in dimensioning */
/*          the work arrays. */

/*  A       (workspace) REAL array, dimension (NMAX*NMAX) */

/*  AF      (workspace) REAL array, dimension (NMAX*NMAX) */

/*  B       (workspace) REAL array, dimension (NMAX*NMAX) */

/*  BF      (workspace) REAL array, dimension (NMAX*NMAX) */

/*  X       (workspace) REAL array, dimension (5*NMAX) */

/*  WORK    (workspace) REAL array, dimension (NMAX*NMAX) */

/*  RWORK   (workspace) REAL array, dimension (NMAX) */

/*  NIN     (input) INTEGER */
/*          The unit number for input. */

/*  NOUT    (input) INTEGER */
/*          The unit number for output. */

/*  INFO    (output) INTEGER */
/*          = 0 :  successful exit */
/*          > 0 :  If SLATMS returns an error code, the absolute value */
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
    --x;
    --bf;
    --b;
    --af;
    --a;
    --iseed;
    --nval;
    --pval;
    --mval;

    /* Function Body */
    s_copy(path, "LSE", (ftnlen)3, (ftnlen)3);
    *info = 0;
    nrun = 0;
    nfail = 0;
    firstt = TRUE_;
    alareq_(path, nmats, dotype, &c__8, nin, nout);
    lda = *nmax;
    ldb = *nmax;
    lwork = *nmax * *nmax;

/*     Check for valid input values. */

    i__1 = *nn;
    for (ik = 1; ik <= i__1; ++ik) {
	m = mval[ik];
	p = pval[ik];
	n = nval[ik];
	if (p > n || n > m + p) {
	    if (firstt) {
		io___13.ciunit = *nout;
		s_wsle(&io___13);
		e_wsle();
		firstt = FALSE_;
	    }
	    io___14.ciunit = *nout;
	    s_wsfe(&io___14);
	    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/* L10: */
    }
    firstt = TRUE_;

/*     Do for each value of M in MVAL. */

    i__1 = *nn;
    for (ik = 1; ik <= i__1; ++ik) {
	m = mval[ik];
	p = pval[ik];
	n = nval[ik];
	if (p > n || n > m + p) {
	    goto L40;
	}

	for (imat = 1; imat <= 8; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat - 1]) {
		goto L30;
	    }

/*           Set up parameters with SLATB9 and generate test */
/*           matrices A and B with SLATMS. */

	    slatb9_(path, &imat, &m, &p, &n, type__, &kla, &kua, &klb, &kub, &
		    anorm, &bnorm, &modea, &modeb, &cndnma, &cndnmb, dista, 
		    distb);

	    slatms_(&m, &n, dista, &iseed[1], type__, &rwork[1], &modea, &
		    cndnma, &anorm, &kla, &kua, "No packing", &a[1], &lda, &
		    work[1], &iinfo);
	    if (iinfo != 0) {
		io___30.ciunit = *nout;
		s_wsfe(&io___30);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		goto L30;
	    }

	    slatms_(&p, &n, distb, &iseed[1], type__, &rwork[1], &modeb, &
		    cndnmb, &bnorm, &klb, &kub, "No packing", &b[1], &ldb, &
		    work[1], &iinfo);
	    if (iinfo != 0) {
		io___31.ciunit = *nout;
		s_wsfe(&io___31);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		goto L30;
	    }

/*           Generate the right-hand sides C and D for the LSE. */

/* Computing MAX */
	    i__3 = m - 1;
	    i__2 = max(i__3,0);
/* Computing MAX */
	    i__5 = n - 1;
	    i__4 = max(i__5,0);
	    i__6 = max(n,1);
	    i__7 = max(m,1);
	    slarhs_("SGE", "New solution", "Upper", "N", &m, &n, &i__2, &i__4, 
		     &c__1, &a[1], &lda, &x[(*nmax << 2) + 1], &i__6, &x[1], &
		    i__7, &iseed[1], &iinfo);

/* Computing MAX */
	    i__3 = p - 1;
	    i__2 = max(i__3,0);
/* Computing MAX */
	    i__5 = n - 1;
	    i__4 = max(i__5,0);
	    i__6 = max(n,1);
	    i__7 = max(p,1);
	    slarhs_("SGE", "Computed", "Upper", "N", &p, &n, &i__2, &i__4, &
		    c__1, &b[1], &ldb, &x[(*nmax << 2) + 1], &i__6, &x[(*nmax 
		    << 1) + 1], &i__7, &iseed[1], &iinfo);

	    nt = 2;

	    slsets_(&m, &p, &n, &a[1], &af[1], &lda, &b[1], &bf[1], &ldb, &x[
		    1], &x[*nmax + 1], &x[(*nmax << 1) + 1], &x[*nmax * 3 + 1]
, &x[(*nmax << 2) + 1], &work[1], &lwork, &rwork[1], 
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
		    io___35.ciunit = *nout;
		    s_wsfe(&io___35);
		    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[i__ - 1], (ftnlen)sizeof(
			    real));
		    e_wsfe();
		    ++nfail;
		}
/* L20: */
	    }
	    nrun += nt;

L30:
	    ;
	}
L40:
	;
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &c__0);

    return 0;

/*     End of SCKLSE */

} /* scklse_ */
