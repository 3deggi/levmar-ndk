/* schktr.f -- translated by f2c (version 20061008).
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

static integer c__2 = 2;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c_n1 = -1;
static integer c__3 = 3;
static integer c__7 = 7;
static integer c__4 = 4;
static real c_b101 = 1.f;
static integer c__8 = 8;
static integer c__9 = 9;

/* Subroutine */ int schktr_(logical *dotype, integer *nn, integer *nval, 
	integer *nnb, integer *nbval, integer *nns, integer *nsval, real *
	thresh, logical *tsterr, integer *nmax, real *a, real *ainv, real *b, 
	real *x, real *xact, real *work, real *rwork, integer *iwork, integer 
	*nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 1988,1989,1990,1991 };
    static char uplos[1*2] = "U" "L";
    static char transs[1*3] = "N" "T" "C";

    /* Format strings */
    static char fmt_9999[] = "(\002 UPLO='\002,a1,\002', DIAG='\002,a1,\002'"
	    ", N=\002,i5,\002, NB=\002,i4,\002, type \002,i2,\002, test(\002,"
	    "i2,\002)= \002,g12.5)";
    static char fmt_9998[] = "(\002 UPLO='\002,a1,\002', TRANS='\002,a1,\002"
	    "', DIAG='\002,a1,\002', N=\002,i5,\002, NB=\002,i4,\002, type"
	    " \002,i2,\002,                      test(\002,i2,\002)= \002,g12"
	    ".5)";
    static char fmt_9997[] = "(\002 NORM='\002,a1,\002', UPLO ='\002,a1,\002"
	    "', N=\002,i5,\002,\002,11x,\002 type \002,i2,\002, test(\002,i2"
	    ",\002)=\002,g12.5)";
    static char fmt_9996[] = "(1x,a,\002( '\002,a1,\002', '\002,a1,\002', "
	    "'\002,a1,\002', '\002,a1,\002',\002,i5,\002, ... ), type \002,i2,"
	    "\002, test(\002,i2,\002)=\002,g12.5)";

    /* System generated locals */
    address a__1[2], a__2[3], a__3[4];
    integer i__1, i__2, i__3[2], i__4, i__5[3], i__6[4];
    char ch__1[2], ch__2[3], ch__3[4];

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen), s_cat(char *,
	     char **, integer *, integer *, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, k, n, nb, in, lda, inb;
    char diag[1];
    integer imat, info;
    char path[3];
    integer irhs, nrhs;
    char norm[1], uplo[1];
    integer nrun;
    extern /* Subroutine */ int alahd_(integer *, char *);
    integer idiag;
    real scale;
    integer nfail, iseed[4];
    extern logical lsame_(char *, char *);
    real rcond;
    extern /* Subroutine */ int sget04_(integer *, integer *, real *, integer 
	    *, real *, integer *, real *, real *);
    real anorm;
    integer itran;
    char trans[1];
    integer iuplo, nerrs;
    real dummy;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *), strt01_(char *, char *, integer *, real *, integer *, 
	    real *, integer *, real *, real *, real *), 
	    strt02_(char *, char *, char *, integer *, integer *, real *, 
	    integer *, real *, integer *, real *, integer *, real *, real *), strt03_(char *, char *, char *, integer *
, integer *, real *, integer *, real *, real *, real *, real *, 
	    integer *, real *, integer *, real *, real *), strt05_(char *, char *, char *, integer *, integer *, 
	    real *, integer *, real *, integer *, real *, integer *, real *, 
	    integer *, real *, real *, real *), 
	    strt06_(real *, real *, char *, char *, integer *, real *, 
	    integer *, real *, real *);
    char xtype[1];
    extern /* Subroutine */ int alaerh_(char *, char *, integer *, integer *, 
	    char *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    real rcondc, rcondi;
    extern /* Subroutine */ int alasum_(char *, integer *, integer *, integer 
	    *, integer *);
    real rcondo, ainvnm;
    extern /* Subroutine */ int slacpy_(char *, integer *, integer *, real *, 
	    integer *, real *, integer *), slarhs_(char *, char *, 
	    char *, char *, integer *, integer *, integer *, integer *, 
	    integer *, real *, integer *, real *, integer *, real *, integer *
, integer *, integer *), xlaenv_(
	    integer *, integer *);
    extern doublereal slantr_(char *, char *, char *, integer *, integer *, 
	    real *, integer *, real *);
    extern /* Subroutine */ int slatrs_(char *, char *, char *, char *, 
	    integer *, real *, integer *, real *, real *, real *, integer *), slattr_(integer *, char *, char *
, char *, integer *, integer *, real *, integer *, real *, real *, 
	     integer *), strcon_(char *, char *, char 
	    *, integer *, real *, integer *, real *, real *, integer *, 
	    integer *);
    real result[9];
    extern /* Subroutine */ int serrtr_(char *, integer *), strrfs_(
	    char *, char *, char *, integer *, integer *, real *, integer *, 
	    real *, integer *, real *, integer *, real *, real *, real *, 
	    integer *, integer *), strtri_(char *, 
	    char *, integer *, real *, integer *, integer *), 
	    strtrs_(char *, char *, char *, integer *, integer *, real *, 
	    integer *, real *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___27 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_9996, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SCHKTR tests STRTRI, -TRS, -RFS, and -CON, and SLATRS */

/*  Arguments */
/*  ========= */

/*  DOTYPE  (input) LOGICAL array, dimension (NTYPES) */
/*          The matrix types to be used for testing.  Matrices of type j */
/*          (for 1 <= j <= NTYPES) are used for testing if DOTYPE(j) = */
/*          .TRUE.; if DOTYPE(j) = .FALSE., then type j is not used. */

/*  NN      (input) INTEGER */
/*          The number of values of N contained in the vector NVAL. */

/*  NVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix column dimension N. */

/*  NNB     (input) INTEGER */
/*          The number of values of NB contained in the vector NBVAL. */

/*  NBVAL   (input) INTEGER array, dimension (NNB) */
/*          The values of the blocksize NB. */

/*  NNS     (input) INTEGER */
/*          The number of values of NRHS contained in the vector NSVAL. */

/*  NSVAL   (input) INTEGER array, dimension (NNS) */
/*          The values of the number of right hand sides NRHS. */

/*  THRESH  (input) REAL */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  TSTERR  (input) LOGICAL */
/*          Flag that indicates whether error exits are to be tested. */

/*  NMAX    (input) INTEGER */
/*          The leading dimension of the work arrays. */
/*          NMAX >= the maximum value of N in NVAL. */

/*  A       (workspace) REAL array, dimension (NMAX*NMAX) */

/*  AINV    (workspace) REAL array, dimension (NMAX*NMAX) */

/*  B       (workspace) REAL array, dimension (NMAX*NSMAX) */
/*          where NSMAX is the largest entry in NSVAL. */

/*  X       (workspace) REAL array, dimension (NMAX*NSMAX) */

/*  XACT    (workspace) REAL array, dimension (NMAX*NSMAX) */

/*  WORK    (workspace) REAL array, dimension */
/*                      (NMAX*max(3,NSMAX)) */

/*  RWORK   (workspace) REAL array, dimension */
/*                      (max(NMAX,2*NSMAX)) */

/*  IWORK   (workspace) INTEGER array, dimension (NMAX) */

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
/*     .. Scalars in Common .. */
/*     .. */
/*     .. Common blocks .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --iwork;
    --rwork;
    --work;
    --xact;
    --x;
    --b;
    --ainv;
    --a;
    --nsval;
    --nbval;
    --nval;
    --dotype;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

/*     Initialize constants and the random number seed. */

    s_copy(path, "Single precision", (ftnlen)1, (ftnlen)16);
    s_copy(path + 1, "TR", (ftnlen)2, (ftnlen)2);
    nrun = 0;
    nfail = 0;
    nerrs = 0;
    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__ - 1] = iseedy[i__ - 1];
/* L10: */
    }

/*     Test the error exits */

    if (*tsterr) {
	serrtr_(path, nout);
    }
    infoc_1.infot = 0;
    xlaenv_(&c__2, &c__2);

    i__1 = *nn;
    for (in = 1; in <= i__1; ++in) {

/*        Do for each value of N in NVAL */

	n = nval[in];
	lda = max(1,n);
	*(unsigned char *)xtype = 'N';

	for (imat = 1; imat <= 10; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L80;
	    }

	    for (iuplo = 1; iuplo <= 2; ++iuplo) {

/*              Do first for UPLO = 'U', then for UPLO = 'L' */

		*(unsigned char *)uplo = *(unsigned char *)&uplos[iuplo - 1];

/*              Call SLATTR to generate a triangular test matrix. */

		s_copy(srnamc_1.srnamt, "SLATTR", (ftnlen)32, (ftnlen)6);
		slattr_(&imat, uplo, "No transpose", diag, iseed, &n, &a[1], &
			lda, &x[1], &work[1], &info);

/*              Set IDIAG = 1 for non-unit matrices, 2 for unit. */

		if (lsame_(diag, "N")) {
		    idiag = 1;
		} else {
		    idiag = 2;
		}

		i__2 = *nnb;
		for (inb = 1; inb <= i__2; ++inb) {

/*                 Do for each blocksize in NBVAL */

		    nb = nbval[inb];
		    xlaenv_(&c__1, &nb);

/* +    TEST 1 */
/*                 Form the inverse of A. */

		    slacpy_(uplo, &n, &n, &a[1], &lda, &ainv[1], &lda);
		    s_copy(srnamc_1.srnamt, "STRTRI", (ftnlen)32, (ftnlen)6);
		    strtri_(uplo, diag, &n, &ainv[1], &lda, &info);

/*                 Check error code from STRTRI. */

		    if (info != 0) {
/* Writing concatenation */
			i__3[0] = 1, a__1[0] = uplo;
			i__3[1] = 1, a__1[1] = diag;
			s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
			alaerh_(path, "STRTRI", &info, &c__0, ch__1, &n, &n, &
				c_n1, &c_n1, &nb, &imat, &nfail, &nerrs, nout);
		    }

/*                 Compute the infinity-norm condition number of A. */

		    anorm = slantr_("I", uplo, diag, &n, &n, &a[1], &lda, &
			    rwork[1]);
		    ainvnm = slantr_("I", uplo, diag, &n, &n, &ainv[1], &lda, 
			    &rwork[1]);
		    if (anorm <= 0.f || ainvnm <= 0.f) {
			rcondi = 1.f;
		    } else {
			rcondi = 1.f / anorm / ainvnm;
		    }

/*                 Compute the residual for the triangular matrix times */
/*                 its inverse.  Also compute the 1-norm condition number */
/*                 of A. */

		    strt01_(uplo, diag, &n, &a[1], &lda, &ainv[1], &lda, &
			    rcondo, &rwork[1], result);

/*                 Print the test ratio if it is .GE. THRESH. */

		    if (result[0] >= *thresh) {
			if (nfail == 0 && nerrs == 0) {
			    alahd_(nout, path);
			}
			io___27.ciunit = *nout;
			s_wsfe(&io___27);
			do_fio(&c__1, uplo, (ftnlen)1);
			do_fio(&c__1, diag, (ftnlen)1);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nb, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&c__1, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[0], (ftnlen)sizeof(real)
				);
			e_wsfe();
			++nfail;
		    }
		    ++nrun;

/*                 Skip remaining tests if not the first block size. */

		    if (inb != 1) {
			goto L60;
		    }

		    i__4 = *nns;
		    for (irhs = 1; irhs <= i__4; ++irhs) {
			nrhs = nsval[irhs];
			*(unsigned char *)xtype = 'N';

			for (itran = 1; itran <= 3; ++itran) {

/*                    Do for op(A) = A, A**T, or A**H. */

			    *(unsigned char *)trans = *(unsigned char *)&
				    transs[itran - 1];
			    if (itran == 1) {
				*(unsigned char *)norm = 'O';
				rcondc = rcondo;
			    } else {
				*(unsigned char *)norm = 'I';
				rcondc = rcondi;
			    }

/* +    TEST 2 */
/*                       Solve and compute residual for op(A)*x = b. */

			    s_copy(srnamc_1.srnamt, "SLARHS", (ftnlen)32, (
				    ftnlen)6);
			    slarhs_(path, xtype, uplo, trans, &n, &n, &c__0, &
				    idiag, &nrhs, &a[1], &lda, &xact[1], &lda, 
				     &b[1], &lda, iseed, &info);
			    *(unsigned char *)xtype = 'C';
			    slacpy_("Full", &n, &nrhs, &b[1], &lda, &x[1], &
				    lda);

			    s_copy(srnamc_1.srnamt, "STRTRS", (ftnlen)32, (
				    ftnlen)6);
			    strtrs_(uplo, trans, diag, &n, &nrhs, &a[1], &lda, 
				     &x[1], &lda, &info);

/*                       Check error code from STRTRS. */

			    if (info != 0) {
/* Writing concatenation */
				i__5[0] = 1, a__2[0] = uplo;
				i__5[1] = 1, a__2[1] = trans;
				i__5[2] = 1, a__2[2] = diag;
				s_cat(ch__2, a__2, i__5, &c__3, (ftnlen)3);
				alaerh_(path, "STRTRS", &info, &c__0, ch__2, &
					n, &n, &c_n1, &c_n1, &nrhs, &imat, &
					nfail, &nerrs, nout);
			    }

/*                       This line is needed on a Sun SPARCstation. */

			    if (n > 0) {
				dummy = a[1];
			    }

			    strt02_(uplo, trans, diag, &n, &nrhs, &a[1], &lda, 
				     &x[1], &lda, &b[1], &lda, &work[1], &
				    result[1]);

/* +    TEST 3 */
/*                       Check solution from generated exact solution. */

			    sget04_(&n, &nrhs, &x[1], &lda, &xact[1], &lda, &
				    rcondc, &result[2]);

/* +    TESTS 4, 5, and 6 */
/*                       Use iterative refinement to improve the solution */
/*                       and compute error bounds. */

			    s_copy(srnamc_1.srnamt, "STRRFS", (ftnlen)32, (
				    ftnlen)6);
			    strrfs_(uplo, trans, diag, &n, &nrhs, &a[1], &lda, 
				     &b[1], &lda, &x[1], &lda, &rwork[1], &
				    rwork[nrhs + 1], &work[1], &iwork[1], &
				    info);

/*                       Check error code from STRRFS. */

			    if (info != 0) {
/* Writing concatenation */
				i__5[0] = 1, a__2[0] = uplo;
				i__5[1] = 1, a__2[1] = trans;
				i__5[2] = 1, a__2[2] = diag;
				s_cat(ch__2, a__2, i__5, &c__3, (ftnlen)3);
				alaerh_(path, "STRRFS", &info, &c__0, ch__2, &
					n, &n, &c_n1, &c_n1, &nrhs, &imat, &
					nfail, &nerrs, nout);
			    }

			    sget04_(&n, &nrhs, &x[1], &lda, &xact[1], &lda, &
				    rcondc, &result[3]);
			    strt05_(uplo, trans, diag, &n, &nrhs, &a[1], &lda, 
				     &b[1], &lda, &x[1], &lda, &xact[1], &lda, 
				     &rwork[1], &rwork[nrhs + 1], &result[4]);

/*                       Print information about the tests that did not */
/*                       pass the threshold. */

			    for (k = 2; k <= 6; ++k) {
				if (result[k - 1] >= *thresh) {
				    if (nfail == 0 && nerrs == 0) {
					alahd_(nout, path);
				    }
				    io___36.ciunit = *nout;
				    s_wsfe(&io___36);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, trans, (ftnlen)1);
				    do_fio(&c__1, diag, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&nrhs, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(real));
				    e_wsfe();
				    ++nfail;
				}
/* L20: */
			    }
			    nrun += 5;
/* L30: */
			}
/* L40: */
		    }

/* +    TEST 7 */
/*                       Get an estimate of RCOND = 1/CNDNUM. */

		    for (itran = 1; itran <= 2; ++itran) {
			if (itran == 1) {
			    *(unsigned char *)norm = 'O';
			    rcondc = rcondo;
			} else {
			    *(unsigned char *)norm = 'I';
			    rcondc = rcondi;
			}
			s_copy(srnamc_1.srnamt, "STRCON", (ftnlen)32, (ftnlen)
				6);
			strcon_(norm, uplo, diag, &n, &a[1], &lda, &rcond, &
				work[1], &iwork[1], &info);

/*                       Check error code from STRCON. */

			if (info != 0) {
/* Writing concatenation */
			    i__5[0] = 1, a__2[0] = norm;
			    i__5[1] = 1, a__2[1] = uplo;
			    i__5[2] = 1, a__2[2] = diag;
			    s_cat(ch__2, a__2, i__5, &c__3, (ftnlen)3);
			    alaerh_(path, "STRCON", &info, &c__0, ch__2, &n, &
				    n, &c_n1, &c_n1, &c_n1, &imat, &nfail, &
				    nerrs, nout);
			}

			strt06_(&rcond, &rcondc, uplo, diag, &n, &a[1], &lda, 
				&rwork[1], &result[6]);

/*                    Print the test ratio if it is .GE. THRESH. */

			if (result[6] >= *thresh) {
			    if (nfail == 0 && nerrs == 0) {
				alahd_(nout, path);
			    }
			    io___38.ciunit = *nout;
			    s_wsfe(&io___38);
			    do_fio(&c__1, norm, (ftnlen)1);
			    do_fio(&c__1, uplo, (ftnlen)1);
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&c__7, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&result[6], (ftnlen)sizeof(
				    real));
			    e_wsfe();
			    ++nfail;
			}
			++nrun;
/* L50: */
		    }
L60:
		    ;
		}
/* L70: */
	    }
L80:
	    ;
	}

/*        Use pathological test matrices to test SLATRS. */

	for (imat = 11; imat <= 18; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L110;
	    }

	    for (iuplo = 1; iuplo <= 2; ++iuplo) {

/*              Do first for UPLO = 'U', then for UPLO = 'L' */

		*(unsigned char *)uplo = *(unsigned char *)&uplos[iuplo - 1];
		for (itran = 1; itran <= 3; ++itran) {

/*                 Do for op(A) = A, A**T, and A**H. */

		    *(unsigned char *)trans = *(unsigned char *)&transs[itran 
			    - 1];

/*                 Call SLATTR to generate a triangular test matrix. */

		    s_copy(srnamc_1.srnamt, "SLATTR", (ftnlen)32, (ftnlen)6);
		    slattr_(&imat, uplo, trans, diag, iseed, &n, &a[1], &lda, 
			    &x[1], &work[1], &info);

/* +    TEST 8 */
/*                 Solve the system op(A)*x = b. */

		    s_copy(srnamc_1.srnamt, "SLATRS", (ftnlen)32, (ftnlen)6);
		    scopy_(&n, &x[1], &c__1, &b[1], &c__1);
		    slatrs_(uplo, trans, diag, "N", &n, &a[1], &lda, &b[1], &
			    scale, &rwork[1], &info);

/*                 Check error code from SLATRS. */

		    if (info != 0) {
/* Writing concatenation */
			i__6[0] = 1, a__3[0] = uplo;
			i__6[1] = 1, a__3[1] = trans;
			i__6[2] = 1, a__3[2] = diag;
			i__6[3] = 1, a__3[3] = "N";
			s_cat(ch__3, a__3, i__6, &c__4, (ftnlen)4);
			alaerh_(path, "SLATRS", &info, &c__0, ch__3, &n, &n, &
				c_n1, &c_n1, &c_n1, &imat, &nfail, &nerrs, 
				nout);
		    }

		    strt03_(uplo, trans, diag, &n, &c__1, &a[1], &lda, &scale, 
			     &rwork[1], &c_b101, &b[1], &lda, &x[1], &lda, &
			    work[1], &result[7]);

/* +    TEST 9 */
/*                 Solve op(A)*X = b again with NORMIN = 'Y'. */

		    scopy_(&n, &x[1], &c__1, &b[n + 1], &c__1);
		    slatrs_(uplo, trans, diag, "Y", &n, &a[1], &lda, &b[n + 1]
, &scale, &rwork[1], &info);

/*                 Check error code from SLATRS. */

		    if (info != 0) {
/* Writing concatenation */
			i__6[0] = 1, a__3[0] = uplo;
			i__6[1] = 1, a__3[1] = trans;
			i__6[2] = 1, a__3[2] = diag;
			i__6[3] = 1, a__3[3] = "Y";
			s_cat(ch__3, a__3, i__6, &c__4, (ftnlen)4);
			alaerh_(path, "SLATRS", &info, &c__0, ch__3, &n, &n, &
				c_n1, &c_n1, &c_n1, &imat, &nfail, &nerrs, 
				nout);
		    }

		    strt03_(uplo, trans, diag, &n, &c__1, &a[1], &lda, &scale, 
			     &rwork[1], &c_b101, &b[n + 1], &lda, &x[1], &lda, 
			     &work[1], &result[8]);

/*                 Print information about the tests that did not pass */
/*                 the threshold. */

		    if (result[7] >= *thresh) {
			if (nfail == 0 && nerrs == 0) {
			    alahd_(nout, path);
			}
			io___40.ciunit = *nout;
			s_wsfe(&io___40);
			do_fio(&c__1, "SLATRS", (ftnlen)6);
			do_fio(&c__1, uplo, (ftnlen)1);
			do_fio(&c__1, trans, (ftnlen)1);
			do_fio(&c__1, diag, (ftnlen)1);
			do_fio(&c__1, "N", (ftnlen)1);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&c__8, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[7], (ftnlen)sizeof(real)
				);
			e_wsfe();
			++nfail;
		    }
		    if (result[8] >= *thresh) {
			if (nfail == 0 && nerrs == 0) {
			    alahd_(nout, path);
			}
			io___41.ciunit = *nout;
			s_wsfe(&io___41);
			do_fio(&c__1, "SLATRS", (ftnlen)6);
			do_fio(&c__1, uplo, (ftnlen)1);
			do_fio(&c__1, trans, (ftnlen)1);
			do_fio(&c__1, diag, (ftnlen)1);
			do_fio(&c__1, "Y", (ftnlen)1);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&c__9, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[8], (ftnlen)sizeof(real)
				);
			e_wsfe();
			++nfail;
		    }
		    nrun += 2;
/* L90: */
		}
/* L100: */
	    }
L110:
	    ;
	}
/* L120: */
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &nerrs);

    return 0;

/*     End of SCHKTR */

} /* schktr_ */
