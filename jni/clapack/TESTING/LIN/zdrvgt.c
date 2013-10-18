/* zdrvgt.f -- translated by f2c (version 20061008).
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
    integer infot, nunit;
    logical ok, lerr;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[32];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static integer c__3 = 3;
static integer c__0 = 0;
static integer c_n1 = -1;
static integer c__1 = 1;
static integer c__2 = 2;
static doublereal c_b43 = 1.;
static doublereal c_b44 = 0.;
static doublecomplex c_b65 = {0.,0.};

/* Subroutine */ int zdrvgt_(logical *dotype, integer *nn, integer *nval, 
	integer *nrhs, doublereal *thresh, logical *tsterr, doublecomplex *a, 
	doublecomplex *af, doublecomplex *b, doublecomplex *x, doublecomplex *
	xact, doublecomplex *work, doublereal *rwork, integer *iwork, integer 
	*nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 0,0,0,1 };
    static char transs[1*3] = "N" "T" "C";

    /* Format strings */
    static char fmt_9999[] = "(1x,a,\002, N =\002,i5,\002, type \002,i2,\002"
	    ", test \002,i2,\002, ratio = \002,g12.5)";
    static char fmt_9998[] = "(1x,a,\002, FACT='\002,a1,\002', TRANS='\002,a"
	    "1,\002', N =\002,i5,\002, type \002,i2,\002, test \002,i2,\002, "
	    "ratio = \002,g12.5)";

    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3, i__4, i__5, i__6[2];
    doublereal d__1, d__2;
    char ch__1[2];

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    integer i__, j, k, m, n;
    doublereal z__[3];
    integer k1, in, kl, ku, ix, nt, lda;
    char fact[1];
    doublereal cond;
    integer mode, koff, imat, info;
    char path[3], dist[1], type__[1];
    integer nrun, ifact, nfail, iseed[4];
    extern doublereal dget06_(doublereal *, doublereal *);
    doublereal rcond;
    integer nimat;
    doublereal anorm;
    integer itran;
    extern /* Subroutine */ int zget04_(integer *, integer *, doublecomplex *, 
	     integer *, doublecomplex *, integer *, doublereal *, doublereal *
);
    char trans[1];
    integer izero, nerrs;
    extern /* Subroutine */ int zgtt01_(integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, doublecomplex *
, doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublereal *, doublereal *), zgtt02_(char *, integer *, 
	     integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *), zgtt05_(char *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, 
	    doublereal *);
    logical zerot;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zgtsv_(integer *, integer *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, doublecomplex *
, integer *, integer *), zlatb4_(char *, integer *, integer *, 
	    integer *, char *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, char *), aladhd_(integer *, 
	    char *), alaerh_(char *, char *, integer *, integer *, 
	    char *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    doublereal rcondc, rcondi;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *), alasvm_(char *, integer *, integer *, 
	     integer *, integer *);
    doublereal rcondo, anormi, ainvnm;
    logical trfcon;
    doublereal anormo;
    extern /* Subroutine */ int zlagtm_(char *, integer *, integer *, 
	    doublereal *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    doublecomplex *, integer *, doublereal *, doublecomplex *, 
	    integer *);
    extern doublereal zlangt_(char *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *);
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dzasum_(integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zlaset_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, integer *), zlatms_(integer *, integer *, char *, integer *, char *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    integer *, char *, doublecomplex *, integer *, doublecomplex *, 
	    integer *), zlarnv_(integer *, integer *, 
	    integer *, doublecomplex *);
    doublereal result[6];
    extern /* Subroutine */ int zgttrf_(integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, integer *, 
	    integer *), zgttrs_(char *, integer *, integer *, doublecomplex *, 
	     doublecomplex *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, integer *), zerrvx_(char *, 
	    integer *), zgtsvx_(char *, char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, doublecomplex *
, doublecomplex *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublecomplex *, 
	    doublereal *, integer *);

    /* Fortran I/O blocks */
    static cilist io___42 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_9998, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZDRVGT tests ZGTSV and -SVX. */

/*  Arguments */
/*  ========= */

/*  DOTYPE  (input) LOGICAL array, dimension (NTYPES) */
/*          The matrix types to be used for testing.  Matrices of type j */
/*          (for 1 <= j <= NTYPES) are used for testing if DOTYPE(j) = */
/*          .TRUE.; if DOTYPE(j) = .FALSE., then type j is not used. */

/*  NN      (input) INTEGER */
/*          The number of values of N contained in the vector NVAL. */

/*  NVAL    (input) INTEGER array, dimension (NN) */
/*          The values of the matrix dimension N. */

/*  THRESH  (input) DOUBLE PRECISION */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  TSTERR  (input) LOGICAL */
/*          Flag that indicates whether error exits are to be tested. */

/*  A       (workspace) COMPLEX*16 array, dimension (NMAX*4) */

/*  AF      (workspace) COMPLEX*16 array, dimension (NMAX*4) */

/*  B       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  X       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  XACT    (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  WORK    (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*max(3,NRHS)) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (NMAX+2*NRHS) */

/*  IWORK   (workspace) INTEGER array, dimension (2*NMAX) */

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
    --iwork;
    --rwork;
    --work;
    --xact;
    --x;
    --b;
    --af;
    --a;
    --nval;
    --dotype;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "GT", (ftnlen)2, (ftnlen)2);
    nrun = 0;
    nfail = 0;
    nerrs = 0;
    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__ - 1] = iseedy[i__ - 1];
/* L10: */
    }

/*     Test the error exits */

    if (*tsterr) {
	zerrvx_(path, nout);
    }
    infoc_1.infot = 0;

    i__1 = *nn;
    for (in = 1; in <= i__1; ++in) {

/*        Do for each value of N in NVAL. */

	n = nval[in];
/* Computing MAX */
	i__2 = n - 1;
	m = max(i__2,0);
	lda = max(1,n);
	nimat = 12;
	if (n <= 0) {
	    nimat = 1;
	}

	i__2 = nimat;
	for (imat = 1; imat <= i__2; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L130;
	    }

/*           Set up parameters with ZLATB4. */

	    zlatb4_(path, &imat, &n, &n, type__, &kl, &ku, &anorm, &mode, &
		    cond, dist);

	    zerot = imat >= 8 && imat <= 10;
	    if (imat <= 6) {

/*              Types 1-6:  generate matrices of known condition number. */

/* Computing MAX */
		i__3 = 2 - ku, i__4 = 3 - max(1,n);
		koff = max(i__3,i__4);
		s_copy(srnamc_1.srnamt, "ZLATMS", (ftnlen)32, (ftnlen)6);
		zlatms_(&n, &n, dist, iseed, type__, &rwork[1], &mode, &cond, 
			&anorm, &kl, &ku, "Z", &af[koff], &c__3, &work[1], &
			info);

/*              Check the error code from ZLATMS. */

		if (info != 0) {
		    alaerh_(path, "ZLATMS", &info, &c__0, " ", &n, &n, &kl, &
			    ku, &c_n1, &imat, &nfail, &nerrs, nout);
		    goto L130;
		}
		izero = 0;

		if (n > 1) {
		    i__3 = n - 1;
		    zcopy_(&i__3, &af[4], &c__3, &a[1], &c__1);
		    i__3 = n - 1;
		    zcopy_(&i__3, &af[3], &c__3, &a[n + m + 1], &c__1);
		}
		zcopy_(&n, &af[2], &c__3, &a[m + 1], &c__1);
	    } else {

/*              Types 7-12:  generate tridiagonal matrices with */
/*              unknown condition numbers. */

		if (! zerot || ! dotype[7]) {

/*                 Generate a matrix with elements from [-1,1]. */

		    i__3 = n + (m << 1);
		    zlarnv_(&c__2, iseed, &i__3, &a[1]);
		    if (anorm != 1.) {
			i__3 = n + (m << 1);
			zdscal_(&i__3, &anorm, &a[1], &c__1);
		    }
		} else if (izero > 0) {

/*                 Reuse the last matrix by copying back the zeroed out */
/*                 elements. */

		    if (izero == 1) {
			i__3 = n;
			a[i__3].r = z__[1], a[i__3].i = 0.;
			if (n > 1) {
			    a[1].r = z__[2], a[1].i = 0.;
			}
		    } else if (izero == n) {
			i__3 = n * 3 - 2;
			a[i__3].r = z__[0], a[i__3].i = 0.;
			i__3 = (n << 1) - 1;
			a[i__3].r = z__[1], a[i__3].i = 0.;
		    } else {
			i__3 = (n << 1) - 2 + izero;
			a[i__3].r = z__[0], a[i__3].i = 0.;
			i__3 = n - 1 + izero;
			a[i__3].r = z__[1], a[i__3].i = 0.;
			i__3 = izero;
			a[i__3].r = z__[2], a[i__3].i = 0.;
		    }
		}

/*              If IMAT > 7, set one column of the matrix to 0. */

		if (! zerot) {
		    izero = 0;
		} else if (imat == 8) {
		    izero = 1;
		    i__3 = n;
		    z__[1] = a[i__3].r;
		    i__3 = n;
		    a[i__3].r = 0., a[i__3].i = 0.;
		    if (n > 1) {
			z__[2] = a[1].r;
			a[1].r = 0., a[1].i = 0.;
		    }
		} else if (imat == 9) {
		    izero = n;
		    i__3 = n * 3 - 2;
		    z__[0] = a[i__3].r;
		    i__3 = (n << 1) - 1;
		    z__[1] = a[i__3].r;
		    i__3 = n * 3 - 2;
		    a[i__3].r = 0., a[i__3].i = 0.;
		    i__3 = (n << 1) - 1;
		    a[i__3].r = 0., a[i__3].i = 0.;
		} else {
		    izero = (n + 1) / 2;
		    i__3 = n - 1;
		    for (i__ = izero; i__ <= i__3; ++i__) {
			i__4 = (n << 1) - 2 + i__;
			a[i__4].r = 0., a[i__4].i = 0.;
			i__4 = n - 1 + i__;
			a[i__4].r = 0., a[i__4].i = 0.;
			i__4 = i__;
			a[i__4].r = 0., a[i__4].i = 0.;
/* L20: */
		    }
		    i__3 = n * 3 - 2;
		    a[i__3].r = 0., a[i__3].i = 0.;
		    i__3 = (n << 1) - 1;
		    a[i__3].r = 0., a[i__3].i = 0.;
		}
	    }

	    for (ifact = 1; ifact <= 2; ++ifact) {
		if (ifact == 1) {
		    *(unsigned char *)fact = 'F';
		} else {
		    *(unsigned char *)fact = 'N';
		}

/*              Compute the condition number for comparison with */
/*              the value returned by ZGTSVX. */

		if (zerot) {
		    if (ifact == 1) {
			goto L120;
		    }
		    rcondo = 0.;
		    rcondi = 0.;

		} else if (ifact == 1) {
		    i__3 = n + (m << 1);
		    zcopy_(&i__3, &a[1], &c__1, &af[1], &c__1);

/*                 Compute the 1-norm and infinity-norm of A. */

		    anormo = zlangt_("1", &n, &a[1], &a[m + 1], &a[n + m + 1]);
		    anormi = zlangt_("I", &n, &a[1], &a[m + 1], &a[n + m + 1]);

/*                 Factor the matrix A. */

		    zgttrf_(&n, &af[1], &af[m + 1], &af[n + m + 1], &af[n + (
			    m << 1) + 1], &iwork[1], &info);

/*                 Use ZGTTRS to solve for one column at a time of */
/*                 inv(A), computing the maximum column sum as we go. */

		    ainvnm = 0.;
		    i__3 = n;
		    for (i__ = 1; i__ <= i__3; ++i__) {
			i__4 = n;
			for (j = 1; j <= i__4; ++j) {
			    i__5 = j;
			    x[i__5].r = 0., x[i__5].i = 0.;
/* L30: */
			}
			i__4 = i__;
			x[i__4].r = 1., x[i__4].i = 0.;
			zgttrs_("No transpose", &n, &c__1, &af[1], &af[m + 1], 
				 &af[n + m + 1], &af[n + (m << 1) + 1], &
				iwork[1], &x[1], &lda, &info);
/* Computing MAX */
			d__1 = ainvnm, d__2 = dzasum_(&n, &x[1], &c__1);
			ainvnm = max(d__1,d__2);
/* L40: */
		    }

/*                 Compute the 1-norm condition number of A. */

		    if (anormo <= 0. || ainvnm <= 0.) {
			rcondo = 1.;
		    } else {
			rcondo = 1. / anormo / ainvnm;
		    }

/*                 Use ZGTTRS to solve for one column at a time of */
/*                 inv(A'), computing the maximum column sum as we go. */

		    ainvnm = 0.;
		    i__3 = n;
		    for (i__ = 1; i__ <= i__3; ++i__) {
			i__4 = n;
			for (j = 1; j <= i__4; ++j) {
			    i__5 = j;
			    x[i__5].r = 0., x[i__5].i = 0.;
/* L50: */
			}
			i__4 = i__;
			x[i__4].r = 1., x[i__4].i = 0.;
			zgttrs_("Conjugate transpose", &n, &c__1, &af[1], &af[
				m + 1], &af[n + m + 1], &af[n + (m << 1) + 1], 
				 &iwork[1], &x[1], &lda, &info);
/* Computing MAX */
			d__1 = ainvnm, d__2 = dzasum_(&n, &x[1], &c__1);
			ainvnm = max(d__1,d__2);
/* L60: */
		    }

/*                 Compute the infinity-norm condition number of A. */

		    if (anormi <= 0. || ainvnm <= 0.) {
			rcondi = 1.;
		    } else {
			rcondi = 1. / anormi / ainvnm;
		    }
		}

		for (itran = 1; itran <= 3; ++itran) {
		    *(unsigned char *)trans = *(unsigned char *)&transs[itran 
			    - 1];
		    if (itran == 1) {
			rcondc = rcondo;
		    } else {
			rcondc = rcondi;
		    }

/*                 Generate NRHS random solution vectors. */

		    ix = 1;
		    i__3 = *nrhs;
		    for (j = 1; j <= i__3; ++j) {
			zlarnv_(&c__2, iseed, &n, &xact[ix]);
			ix += lda;
/* L70: */
		    }

/*                 Set the right hand side. */

		    zlagtm_(trans, &n, nrhs, &c_b43, &a[1], &a[m + 1], &a[n + 
			    m + 1], &xact[1], &lda, &c_b44, &b[1], &lda);

		    if (ifact == 2 && itran == 1) {

/*                    --- Test ZGTSV  --- */

/*                    Solve the system using Gaussian elimination with */
/*                    partial pivoting. */

			i__3 = n + (m << 1);
			zcopy_(&i__3, &a[1], &c__1, &af[1], &c__1);
			zlacpy_("Full", &n, nrhs, &b[1], &lda, &x[1], &lda);

			s_copy(srnamc_1.srnamt, "ZGTSV ", (ftnlen)32, (ftnlen)
				6);
			zgtsv_(&n, nrhs, &af[1], &af[m + 1], &af[n + m + 1], &
				x[1], &lda, &info);

/*                    Check error code from ZGTSV . */

			if (info != izero) {
			    alaerh_(path, "ZGTSV ", &info, &izero, " ", &n, &
				    n, &c__1, &c__1, nrhs, &imat, &nfail, &
				    nerrs, nout);
			}
			nt = 1;
			if (izero == 0) {

/*                       Check residual of computed solution. */

			    zlacpy_("Full", &n, nrhs, &b[1], &lda, &work[1], &
				    lda);
			    zgtt02_(trans, &n, nrhs, &a[1], &a[m + 1], &a[n + 
				    m + 1], &x[1], &lda, &work[1], &lda, &
				    rwork[1], &result[1]);

/*                       Check solution from generated exact solution. */

			    zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, &
				    rcondc, &result[2]);
			    nt = 3;
			}

/*                    Print information about the tests that did not pass */
/*                    the threshold. */

			i__3 = nt;
			for (k = 2; k <= i__3; ++k) {
			    if (result[k - 1] >= *thresh) {
				if (nfail == 0 && nerrs == 0) {
				    aladhd_(nout, path);
				}
				io___42.ciunit = *nout;
				s_wsfe(&io___42);
				do_fio(&c__1, "ZGTSV ", (ftnlen)6);
				do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&result[k - 1], (ftnlen)
					sizeof(doublereal));
				e_wsfe();
				++nfail;
			    }
/* L80: */
			}
			nrun = nrun + nt - 1;
		    }

/*                 --- Test ZGTSVX --- */

		    if (ifact > 1) {

/*                    Initialize AF to zero. */

			i__3 = n * 3 - 2;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    i__4 = i__;
			    af[i__4].r = 0., af[i__4].i = 0.;
/* L90: */
			}
		    }
		    zlaset_("Full", &n, nrhs, &c_b65, &c_b65, &x[1], &lda);

/*                 Solve the system and compute the condition number and */
/*                 error bounds using ZGTSVX. */

		    s_copy(srnamc_1.srnamt, "ZGTSVX", (ftnlen)32, (ftnlen)6);
		    zgtsvx_(fact, trans, &n, nrhs, &a[1], &a[m + 1], &a[n + m 
			    + 1], &af[1], &af[m + 1], &af[n + m + 1], &af[n + 
			    (m << 1) + 1], &iwork[1], &b[1], &lda, &x[1], &
			    lda, &rcond, &rwork[1], &rwork[*nrhs + 1], &work[
			    1], &rwork[(*nrhs << 1) + 1], &info);

/*                 Check the error code from ZGTSVX. */

		    if (info != izero) {
/* Writing concatenation */
			i__6[0] = 1, a__1[0] = fact;
			i__6[1] = 1, a__1[1] = trans;
			s_cat(ch__1, a__1, i__6, &c__2, (ftnlen)2);
			alaerh_(path, "ZGTSVX", &info, &izero, ch__1, &n, &n, 
				&c__1, &c__1, nrhs, &imat, &nfail, &nerrs, 
				nout);
		    }

		    if (ifact >= 2) {

/*                    Reconstruct matrix from factors and compute */
/*                    residual. */

			zgtt01_(&n, &a[1], &a[m + 1], &a[n + m + 1], &af[1], &
				af[m + 1], &af[n + m + 1], &af[n + (m << 1) + 
				1], &iwork[1], &work[1], &lda, &rwork[1], 
				result);
			k1 = 1;
		    } else {
			k1 = 2;
		    }

		    if (info == 0) {
			trfcon = FALSE_;

/*                    Check residual of computed solution. */

			zlacpy_("Full", &n, nrhs, &b[1], &lda, &work[1], &lda);
			zgtt02_(trans, &n, nrhs, &a[1], &a[m + 1], &a[n + m + 
				1], &x[1], &lda, &work[1], &lda, &rwork[1], &
				result[1]);

/*                    Check solution from generated exact solution. */

			zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, &
				rcondc, &result[2]);

/*                    Check the error bounds from iterative refinement. */

			zgtt05_(trans, &n, nrhs, &a[1], &a[m + 1], &a[n + m + 
				1], &b[1], &lda, &x[1], &lda, &xact[1], &lda, 
				&rwork[1], &rwork[*nrhs + 1], &result[3]);
			nt = 5;
		    }

/*                 Print information about the tests that did not pass */
/*                 the threshold. */

		    i__3 = nt;
		    for (k = k1; k <= i__3; ++k) {
			if (result[k - 1] >= *thresh) {
			    if (nfail == 0 && nerrs == 0) {
				aladhd_(nout, path);
			    }
			    io___46.ciunit = *nout;
			    s_wsfe(&io___46);
			    do_fio(&c__1, "ZGTSVX", (ftnlen)6);
			    do_fio(&c__1, fact, (ftnlen)1);
			    do_fio(&c__1, trans, (ftnlen)1);
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&result[k - 1], (ftnlen)
				    sizeof(doublereal));
			    e_wsfe();
			    ++nfail;
			}
/* L100: */
		    }

/*                 Check the reciprocal of the condition number. */

		    result[5] = dget06_(&rcond, &rcondc);
		    if (result[5] >= *thresh) {
			if (nfail == 0 && nerrs == 0) {
			    aladhd_(nout, path);
			}
			io___47.ciunit = *nout;
			s_wsfe(&io___47);
			do_fio(&c__1, "ZGTSVX", (ftnlen)6);
			do_fio(&c__1, fact, (ftnlen)1);
			do_fio(&c__1, trans, (ftnlen)1);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[k - 1], (ftnlen)sizeof(
				doublereal));
			e_wsfe();
			++nfail;
		    }
		    nrun = nrun + nt - k1 + 2;

/* L110: */
		}
L120:
		;
	    }
L130:
	    ;
	}
/* L140: */
    }

/*     Print a summary of the results. */

    alasvm_(path, nout, &nfail, &nrun, &nerrs);

    return 0;

/*     End of ZDRVGT */

} /* zdrvgt_ */
