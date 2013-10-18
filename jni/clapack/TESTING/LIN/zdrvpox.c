/* zdrvpox.f -- translated by f2c (version 20061008).
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
#include "memory_alloc.h"

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

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__0 = 0;
static integer c_n1 = -1;
static doublecomplex c_b51 = {0.,0.};
static complex c_b87 = {0.f,0.f};
static doublereal c_b94 = 0.;

/* Subroutine */ int zdrvpo_(logical *dotype, integer *nn, integer *nval, 
	integer *nrhs, doublereal *thresh, logical *tsterr, integer *nmax, 
	doublecomplex *a, doublecomplex *afac, doublecomplex *asav, 
	doublecomplex *b, doublecomplex *bsav, doublecomplex *x, 
	doublecomplex *xact, doublereal *s, doublecomplex *work, doublereal *
	rwork, integer *nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 1988,1989,1990,1991 };
    static char uplos[1*2] = "U" "L";
    static char facts[1*3] = "F" "N" "E";
    static char equeds[1*2] = "N" "Y";

    /* Format strings */
    static char fmt_9999[] = "(1x,a,\002, UPLO='\002,a1,\002', N =\002,i5"
	    ",\002, type \002,i1,\002, test(\002,i1,\002)=\002,g12.5)";
    static char fmt_9997[] = "(1x,a,\002, FACT='\002,a1,\002', UPLO='\002,"
	    "a1,\002', N=\002,i5,\002, EQUED='\002,a1,\002', type \002,i1,"
	    "\002, test(\002,i1,\002) =\002,g12.5)";
    static char fmt_9998[] = "(1x,a,\002, FACT='\002,a1,\002', UPLO='\002,"
	    "a1,\002', N=\002,i5,\002, type \002,i1,\002, test(\002,i1,\002)"
	    "=\002,g12.5)";

    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3, i__4, i__5[2];
    char ch__1[2];

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int zposvxx_(char *, char *, integer *, integer *, 
	     doublecomplex *, integer *, doublecomplex *, integer *, char *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, 
	    doublecomplex *, doublereal *, integer *),
	     zebchvxx_(doublereal *, char *);
    integer i__, k, n;
    doublereal *errbnds_c__, *errbnds_n__;
    integer k1, nb, in, kl, ku, nt, n_err_bnds__, lda;
    char fact[1];
    integer ioff, mode;
    doublereal amax;
    char path[3];
    integer imat, info;
    doublereal *berr;
    char dist[1];
    doublereal rpvgrw_svxx__;
    char uplo[1], type__[1];
    integer nrun, ifact, nfail, iseed[4], nfact;
    extern doublereal dget06_(doublereal *, doublereal *);
    extern logical lsame_(char *, char *);
    char equed[1];
    integer nbmin;
    doublereal rcond, roldc, scond;
    integer nimat;
    doublereal anorm;
    extern /* Subroutine */ int zget04_(integer *, integer *, doublecomplex *, 
	     integer *, doublecomplex *, integer *, doublereal *, doublereal *
);
    logical equil;
    integer iuplo, izero, nerrs;
    extern /* Subroutine */ int zpot01_(char *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublereal *, doublereal *), zpot02_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *, 
	     doublereal *, doublereal *), zpot05_(char *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *, 
	     doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *, doublereal *);
    logical zerot;
    char xtype[1];
    extern /* Subroutine */ int zposv_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *), zlatb4_(char *, integer *, integer *, integer *, char *, 
	     integer *, integer *, doublereal *, integer *, doublereal *, 
	    char *), aladhd_(integer *, char *), alaerh_(char *, char *, integer *, integer *, char *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *);
    logical prefac;
    doublereal rcondc;
    logical nofact;
    integer iequed;
    extern doublereal zlanhe_(char *, char *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    extern /* Subroutine */ int alasvm_(char *, integer *, integer *, integer 
	    *, integer *);
    doublereal cndnum;
    extern /* Subroutine */ int zlaipd_(integer *, doublecomplex *, integer *, 
	     integer *), zlaqhe_(char *, integer *, doublecomplex *, integer *
, doublereal *, doublereal *, doublereal *, char *);
    doublereal ainvnm;
    extern /* Subroutine */ int xlaenv_(integer *, integer *), zlacpy_(char *, 
	     integer *, integer *, doublecomplex *, integer *, doublecomplex *
, integer *), zlarhs_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, integer *, integer *), zlaset_(), zlatms_(integer *, integer *, char *, 
	    integer *, char *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *, integer *, char *, doublecomplex *, 
	    integer *, doublecomplex *, integer *);
    doublereal result[6];
    extern /* Subroutine */ int zpoequ_(integer *, doublecomplex *, integer *, 
	     doublereal *, doublereal *, doublereal *, integer *), zpotrf_(
	    char *, integer *, doublecomplex *, integer *, integer *),
	     zpotri_(char *, integer *, doublecomplex *, integer *, integer *), zerrvx_(char *, integer *), zposvx_(char *, 
	    char *, integer *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, char *, doublereal *, doublecomplex *, 
	     integer *, doublecomplex *, integer *, doublereal *, doublereal *
, doublereal *, doublecomplex *, doublereal *, integer *);

    /* Fortran I/O blocks */
    static cilist io___48 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___58 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_9998, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZDRVPO tests the driver routines ZPOSV, -SVX, and -SVXX. */

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

/*  NRHS    (input) INTEGER */
/*          The number of right hand side vectors to be generated for */
/*          each linear system. */

/*  THRESH  (input) DOUBLE PRECISION */
/*          The threshold value for the test ratios.  A result is */
/*          included in the output file if RESULT >= THRESH.  To have */
/*          every test ratio printed, use THRESH = 0. */

/*  TSTERR  (input) LOGICAL */
/*          Flag that indicates whether error exits are to be tested. */

/*  NMAX    (input) INTEGER */
/*          The maximum value permitted for N, used in dimensioning the */
/*          work arrays. */

/*  A       (workspace) COMPLEX*16 array, dimension (NMAX*NMAX) */

/*  AFAC    (workspace) COMPLEX*16 array, dimension (NMAX*NMAX) */

/*  ASAV    (workspace) COMPLEX*16 array, dimension (NMAX*NMAX) */

/*  B       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  BSAV    (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  X       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  XACT    (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  S       (workspace) DOUBLE PRECISION array, dimension (NMAX) */

/*  WORK    (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*max(3,NRHS)) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (NMAX+2*NRHS) */

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
    --rwork;
    --work;
    --s;
    --xact;
    --x;
    --bsav;
    --b;
    --asav;
    --afac;
    --a;
    --nval;
    --dotype;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

/*     Initialize constants and the random number seed. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "PO", (ftnlen)2, (ftnlen)2);
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

/*     Set the block size and minimum block size for testing. */

    nb = 1;
    nbmin = 2;
    xlaenv_(&c__1, &nb);
    xlaenv_(&c__2, &nbmin);

/*     Do for each value of N in NVAL */

    i__1 = *nn;
    for (in = 1; in <= i__1; ++in) {
	n = nval[in];
	lda = max(n,1);
	*(unsigned char *)xtype = 'N';
	nimat = 9;
	if (n <= 0) {
	    nimat = 1;
	}

	i__2 = nimat;
	for (imat = 1; imat <= i__2; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L120;
	    }

/*           Skip types 3, 4, or 5 if the matrix size is too small. */

	    zerot = imat >= 3 && imat <= 5;
	    if (zerot && n < imat - 2) {
		goto L120;
	    }

/*           Do first for UPLO = 'U', then for UPLO = 'L' */

	    for (iuplo = 1; iuplo <= 2; ++iuplo) {
		*(unsigned char *)uplo = *(unsigned char *)&uplos[iuplo - 1];

/*              Set up parameters with ZLATB4 and generate a test matrix */
/*              with ZLATMS. */

		zlatb4_(path, &imat, &n, &n, type__, &kl, &ku, &anorm, &mode, 
			&cndnum, dist);

		s_copy(srnamc_1.srnamt, "ZLATMS", (ftnlen)32, (ftnlen)6);
		zlatms_(&n, &n, dist, iseed, type__, &rwork[1], &mode, &
			cndnum, &anorm, &kl, &ku, uplo, &a[1], &lda, &work[1], 
			 &info);

/*              Check error code from ZLATMS. */

		if (info != 0) {
		    alaerh_(path, "ZLATMS", &info, &c__0, uplo, &n, &n, &c_n1, 
			     &c_n1, &c_n1, &imat, &nfail, &nerrs, nout);
		    goto L110;
		}

/*              For types 3-5, zero one row and column of the matrix to */
/*              test that INFO is returned correctly. */

		if (zerot) {
		    if (imat == 3) {
			izero = 1;
		    } else if (imat == 4) {
			izero = n;
		    } else {
			izero = n / 2 + 1;
		    }
		    ioff = (izero - 1) * lda;

/*                 Set row and column IZERO of A to 0. */

		    if (iuplo == 1) {
			i__3 = izero - 1;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    i__4 = ioff + i__;
			    a[i__4].r = 0., a[i__4].i = 0.;
/* L20: */
			}
			ioff += izero;
			i__3 = n;
			for (i__ = izero; i__ <= i__3; ++i__) {
			    i__4 = ioff;
			    a[i__4].r = 0., a[i__4].i = 0.;
			    ioff += lda;
/* L30: */
			}
		    } else {
			ioff = izero;
			i__3 = izero - 1;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    i__4 = ioff;
			    a[i__4].r = 0., a[i__4].i = 0.;
			    ioff += lda;
/* L40: */
			}
			ioff -= izero;
			i__3 = n;
			for (i__ = izero; i__ <= i__3; ++i__) {
			    i__4 = ioff + i__;
			    a[i__4].r = 0., a[i__4].i = 0.;
/* L50: */
			}
		    }
		} else {
		    izero = 0;
		}

/*              Set the imaginary part of the diagonals. */

		i__3 = lda + 1;
		zlaipd_(&n, &a[1], &i__3, &c__0);

/*              Save a copy of the matrix A in ASAV. */

		zlacpy_(uplo, &n, &n, &a[1], &lda, &asav[1], &lda);

		for (iequed = 1; iequed <= 2; ++iequed) {
		    *(unsigned char *)equed = *(unsigned char *)&equeds[
			    iequed - 1];
		    if (iequed == 1) {
			nfact = 3;
		    } else {
			nfact = 1;
		    }

		    i__3 = nfact;
		    for (ifact = 1; ifact <= i__3; ++ifact) {
			for (i__ = 1; i__ <= 6; ++i__) {
			    result[i__ - 1] = 0.;
			}
			*(unsigned char *)fact = *(unsigned char *)&facts[
				ifact - 1];
			prefac = lsame_(fact, "F");
			nofact = lsame_(fact, "N");
			equil = lsame_(fact, "E");

			if (zerot) {
			    if (prefac) {
				goto L90;
			    }
			    rcondc = 0.;

			} else if (! lsame_(fact, "N")) 
				{

/*                       Compute the condition number for comparison with */
/*                       the value returned by ZPOSVX (FACT = 'N' reuses */
/*                       the condition number from the previous iteration */
/*                       with FACT = 'F'). */

			    zlacpy_(uplo, &n, &n, &asav[1], &lda, &afac[1], &
				    lda);
			    if (equil || iequed > 1) {

/*                          Compute row and column scale factors to */
/*                          equilibrate the matrix A. */

				zpoequ_(&n, &afac[1], &lda, &s[1], &scond, &
					amax, &info);
				if (info == 0 && n > 0) {
				    if (iequed > 1) {
					scond = 0.;
				    }

/*                             Equilibrate the matrix. */

				    zlaqhe_(uplo, &n, &afac[1], &lda, &s[1], &
					    scond, &amax, equed);
				}
			    }

/*                       Save the condition number of the */
/*                       non-equilibrated system for use in ZGET04. */

			    if (equil) {
				roldc = rcondc;
			    }

/*                       Compute the 1-norm of A. */

			    anorm = zlanhe_("1", uplo, &n, &afac[1], &lda, &
				    rwork[1]);

/*                       Factor the matrix A. */

			    zpotrf_(uplo, &n, &afac[1], &lda, &info);

/*                       Form the inverse of A. */

			    zlacpy_(uplo, &n, &n, &afac[1], &lda, &a[1], &lda);
			    zpotri_(uplo, &n, &a[1], &lda, &info);

/*                       Compute the 1-norm condition number of A. */

			    ainvnm = zlanhe_("1", uplo, &n, &a[1], &lda, &
				    rwork[1]);
			    if (anorm <= 0. || ainvnm <= 0.) {
				rcondc = 1.;
			    } else {
				rcondc = 1. / anorm / ainvnm;
			    }
			}

/*                    Restore the matrix A. */

			zlacpy_(uplo, &n, &n, &asav[1], &lda, &a[1], &lda);

/*                    Form an exact solution and set the right hand side. */

			s_copy(srnamc_1.srnamt, "ZLARHS", (ftnlen)32, (ftnlen)
				6);
			zlarhs_(path, xtype, uplo, " ", &n, &n, &kl, &ku, 
				nrhs, &a[1], &lda, &xact[1], &lda, &b[1], &
				lda, iseed, &info);
			*(unsigned char *)xtype = 'C';
			zlacpy_("Full", &n, nrhs, &b[1], &lda, &bsav[1], &lda);

			if (nofact) {

/*                       --- Test ZPOSV  --- */

/*                       Compute the L*L' or U'*U factorization of the */
/*                       matrix and solve the system. */

			    zlacpy_(uplo, &n, &n, &a[1], &lda, &afac[1], &lda);
			    zlacpy_("Full", &n, nrhs, &b[1], &lda, &x[1], &
				    lda);

			    s_copy(srnamc_1.srnamt, "ZPOSV ", (ftnlen)32, (
				    ftnlen)6);
			    zposv_(uplo, &n, nrhs, &afac[1], &lda, &x[1], &
				    lda, &info);

/*                       Check error code from ZPOSV . */

			    if (info != izero) {
				alaerh_(path, "ZPOSV ", &info, &izero, uplo, &
					n, &n, &c_n1, &c_n1, nrhs, &imat, &
					nfail, &nerrs, nout);
				goto L70;
			    } else if (info != 0) {
				goto L70;
			    }

/*                       Reconstruct matrix from factors and compute */
/*                       residual. */

			    zpot01_(uplo, &n, &a[1], &lda, &afac[1], &lda, &
				    rwork[1], result);

/*                       Compute residual of the computed solution. */

			    zlacpy_("Full", &n, nrhs, &b[1], &lda, &work[1], &
				    lda);
			    zpot02_(uplo, &n, nrhs, &a[1], &lda, &x[1], &lda, 
				    &work[1], &lda, &rwork[1], &result[1]);

/*                       Check solution from generated exact solution. */

			    zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, &
				    rcondc, &result[2]);
			    nt = 3;

/*                       Print information about the tests that did not */
/*                       pass the threshold. */

			    i__4 = nt;
			    for (k = 1; k <= i__4; ++k) {
				if (result[k - 1] >= *thresh) {
				    if (nfail == 0 && nerrs == 0) {
					aladhd_(nout, path);
				    }
				    io___48.ciunit = *nout;
				    s_wsfe(&io___48);
				    do_fio(&c__1, "ZPOSV ", (ftnlen)6);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(doublereal));
				    e_wsfe();
				    ++nfail;
				}
/* L60: */
			    }
			    nrun += nt;
L70:
			    ;
			}

/*                    --- Test ZPOSVX --- */

			if (! prefac) {
			    zlaset_(uplo, &n, &n, &c_b51, &c_b51, &afac[1], &
				    lda);
			}
			zlaset_("Full", &n, nrhs, &c_b51, &c_b51, &x[1], &lda);
			if (iequed > 1 && n > 0) {

/*                       Equilibrate the matrix if FACT='F' and */
/*                       EQUED='Y'. */

			    zlaqhe_(uplo, &n, &a[1], &lda, &s[1], &scond, &
				    amax, equed);
			}

/*                    Solve the system and compute the condition number */
/*                    and error bounds using ZPOSVX. */

			s_copy(srnamc_1.srnamt, "ZPOSVX", (ftnlen)32, (ftnlen)
				6);
			zposvx_(fact, uplo, &n, nrhs, &a[1], &lda, &afac[1], &
				lda, equed, &s[1], &b[1], &lda, &x[1], &lda, &
				rcond, &rwork[1], &rwork[*nrhs + 1], &work[1], 
				 &rwork[(*nrhs << 1) + 1], &info);

/*                    Check the error code from ZPOSVX. */

			if (info == n + 1) {
			    goto L90;
			}
			if (info != izero) {
/* Writing concatenation */
			    i__5[0] = 1, a__1[0] = fact;
			    i__5[1] = 1, a__1[1] = uplo;
			    s_cat(ch__1, a__1, i__5, &c__2, (ftnlen)2);
			    alaerh_(path, "ZPOSVX", &info, &izero, ch__1, &n, 
				    &n, &c_n1, &c_n1, nrhs, &imat, &nfail, &
				    nerrs, nout);
			    goto L90;
			}

			if (info == 0) {
			    if (! prefac) {

/*                          Reconstruct matrix from factors and compute */
/*                          residual. */

				zpot01_(uplo, &n, &a[1], &lda, &afac[1], &lda, 
					 &rwork[(*nrhs << 1) + 1], result);
				k1 = 1;
			    } else {
				k1 = 2;
			    }

/*                       Compute residual of the computed solution. */

			    zlacpy_("Full", &n, nrhs, &bsav[1], &lda, &work[1]
, &lda);
			    zpot02_(uplo, &n, nrhs, &asav[1], &lda, &x[1], &
				    lda, &work[1], &lda, &rwork[(*nrhs << 1) 
				    + 1], &result[1]);

/*                       Check solution from generated exact solution. */

			    if (nofact || prefac && lsame_(equed, "N")) {
				zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, 
					 &rcondc, &result[2]);
			    } else {
				zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, 
					 &roldc, &result[2]);
			    }

/*                       Check the error bounds from iterative */
/*                       refinement. */

			    zpot05_(uplo, &n, nrhs, &asav[1], &lda, &b[1], &
				    lda, &x[1], &lda, &xact[1], &lda, &rwork[
				    1], &rwork[*nrhs + 1], &result[3]);
			} else {
			    k1 = 6;
			}

/*                    Compare RCOND from ZPOSVX with the computed value */
/*                    in RCONDC. */

			result[5] = dget06_(&rcond, &rcondc);

/*                    Print information about the tests that did not pass */
/*                    the threshold. */

			for (k = k1; k <= 6; ++k) {
			    if (result[k - 1] >= *thresh) {
				if (nfail == 0 && nerrs == 0) {
				    aladhd_(nout, path);
				}
				if (prefac) {
				    io___51.ciunit = *nout;
				    s_wsfe(&io___51);
				    do_fio(&c__1, "ZPOSVX", (ftnlen)6);
				    do_fio(&c__1, fact, (ftnlen)1);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, equed, (ftnlen)1);
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(doublereal));
				    e_wsfe();
				} else {
				    io___52.ciunit = *nout;
				    s_wsfe(&io___52);
				    do_fio(&c__1, "ZPOSVX", (ftnlen)6);
				    do_fio(&c__1, fact, (ftnlen)1);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(doublereal));
				    e_wsfe();
				}
				++nfail;
			    }
/* L80: */
			}
			nrun = nrun + 7 - k1;

/*                    --- Test ZPOSVXX --- */

/*                    Restore the matrices A and B. */

			zlacpy_("Full", &n, &n, &asav[1], &lda, &a[1], &lda);
			zlacpy_("Full", &n, nrhs, &bsav[1], &lda, &b[1], &lda);
			if (! prefac) {
			    zlaset_(uplo, &n, &n, &c_b87, &c_b87, &afac[1], &
				    lda);
			}
			zlaset_("Full", &n, nrhs, &c_b87, &c_b87, &x[1], &lda);
			if (iequed > 1 && n > 0) {

/*                       Equilibrate the matrix if FACT='F' and */
/*                       EQUED='Y'. */

			    zlaqhe_(uplo, &n, &a[1], &lda, &s[1], &scond, &
				    amax, equed);
			}

/*                    Solve the system and compute the condition number */
/*                    and error bounds using ZPOSVXX. */

			s_copy(srnamc_1.srnamt, "ZPOSVXX", (ftnlen)32, (
				ftnlen)7);

			dalloc3();

			zposvxx_(fact, uplo, &n, nrhs, &a[1], &lda, &afac[1], 
				&lda, equed, &s[1], &b[1], &lda, &x[1], &lda, 
				&rcond, &rpvgrw_svxx__, berr, &n_err_bnds__, 
				errbnds_n__, errbnds_c__, &c__0, &c_b94, &
				work[1], &rwork[(*nrhs << 1) + 1], &info);

			free3();

/*                    Check the error code from ZPOSVXX. */

			if (info == n + 1) {
			    goto L90;
			}
			if (info != izero) {
/* Writing concatenation */
			    i__5[0] = 1, a__1[0] = fact;
			    i__5[1] = 1, a__1[1] = uplo;
			    s_cat(ch__1, a__1, i__5, &c__2, (ftnlen)2);
			    alaerh_(path, "ZPOSVXX", &info, &izero, ch__1, &n, 
				     &n, &c_n1, &c_n1, nrhs, &imat, &nfail, &
				    nerrs, nout);
			    goto L90;
			}

			if (info == 0) {
			    if (! prefac) {

/*                          Reconstruct matrix from factors and compute */
/*                          residual. */

				zpot01_(uplo, &n, &a[1], &lda, &afac[1], &lda, 
					 &rwork[(*nrhs << 1) + 1], result);
				k1 = 1;
			    } else {
				k1 = 2;
			    }

/*                       Compute residual of the computed solution. */

			    zlacpy_("Full", &n, nrhs, &bsav[1], &lda, &work[1]
, &lda);
			    zpot02_(uplo, &n, nrhs, &asav[1], &lda, &x[1], &
				    lda, &work[1], &lda, &rwork[(*nrhs << 1) 
				    + 1], &result[1]);

/*                       Check solution from generated exact solution. */

			    if (nofact || prefac && lsame_(equed, "N")) {
				zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, 
					 &rcondc, &result[2]);
			    } else {
				zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, 
					 &roldc, &result[2]);
			    }

/*                       Check the error bounds from iterative */
/*                       refinement. */

			    zpot05_(uplo, &n, nrhs, &asav[1], &lda, &b[1], &
				    lda, &x[1], &lda, &xact[1], &lda, &rwork[
				    1], &rwork[*nrhs + 1], &result[3]);
			} else {
			    k1 = 6;
			}

/*                    Compare RCOND from ZPOSVXX with the computed value */
/*                    in RCONDC. */

			result[5] = dget06_(&rcond, &rcondc);

/*                    Print information about the tests that did not pass */
/*                    the threshold. */

			for (k = k1; k <= 6; ++k) {
			    if (result[k - 1] >= *thresh) {
				if (nfail == 0 && nerrs == 0) {
				    aladhd_(nout, path);
				}
				if (prefac) {
				    io___58.ciunit = *nout;
				    s_wsfe(&io___58);
				    do_fio(&c__1, "ZPOSVXX", (ftnlen)7);
				    do_fio(&c__1, fact, (ftnlen)1);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, equed, (ftnlen)1);
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(doublereal));
				    e_wsfe();
				} else {
				    io___59.ciunit = *nout;
				    s_wsfe(&io___59);
				    do_fio(&c__1, "ZPOSVXX", (ftnlen)7);
				    do_fio(&c__1, fact, (ftnlen)1);
				    do_fio(&c__1, uplo, (ftnlen)1);
				    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&imat, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&result[k - 1], (
					    ftnlen)sizeof(doublereal));
				    e_wsfe();
				}
				++nfail;
			    }
/* L85: */
			}
			nrun = nrun + 7 - k1;
L90:
			;
		    }
/* L100: */
		}
L110:
		;
	    }
L120:
	    ;
	}
/* L130: */
    }

/*     Print a summary of the results. */

    alasvm_(path, nout, &nfail, &nrun, &nerrs);

/*     Test Error Bounds for ZGESVXX */
    zebchvxx_(thresh, path);
    return 0;

/*     End of ZDRVPO */

} /* zdrvpo_ */
