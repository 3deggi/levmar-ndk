/* zdrvsp.f -- translated by f2c (version 20061008).
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

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__0 = 0;
static integer c_n1 = -1;
static doublecomplex c_b61 = {0.,0.};

/* Subroutine */ int zdrvsp_(logical *dotype, integer *nn, integer *nval, 
	integer *nrhs, doublereal *thresh, logical *tsterr, integer *nmax, 
	doublecomplex *a, doublecomplex *afac, doublecomplex *ainv, 
	doublecomplex *b, doublecomplex *x, doublecomplex *xact, 
	doublecomplex *work, doublereal *rwork, integer *iwork, integer *nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 1988,1989,1990,1991 };
    static char facts[1*2] = "F" "N";

    /* Format strings */
    static char fmt_9999[] = "(1x,a,\002, UPLO='\002,a1,\002', N =\002,i5"
	    ",\002, type \002,i2,\002, test \002,i2,\002, ratio =\002,g12.5)";
    static char fmt_9998[] = "(1x,a,\002, FACT='\002,a1,\002', UPLO='\002,"
	    "a1,\002', N =\002,i5,\002, type \002,i2,\002, test \002,i2,\002,"
	    " ratio =\002,g12.5)";

    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3, i__4, i__5, i__6[2];
    char ch__1[2];

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    integer i__, j, k, n, i1, i2, k1, nb, in, kl, ku, nt, lda, npp;
    char fact[1];
    integer ioff, mode, imat, info;
    char path[3], dist[1], uplo[1], type__[1];
    integer nrun, ifact, nfail, iseed[4];
    extern doublereal dget06_(doublereal *, doublereal *);
    integer nbmin;
    doublereal rcond;
    integer nimat;
    doublereal anorm;
    extern /* Subroutine */ int zget04_(integer *, integer *, doublecomplex *, 
	     integer *, doublecomplex *, integer *, doublereal *, doublereal *
);
    integer iuplo, izero, nerrs;
    extern /* Subroutine */ int zspt01_(char *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *), zppt05_(char *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *, doublereal *);
    logical zerot;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zspt02_(char *, integer *, integer *, 
	     doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublereal *, doublereal *);
    char xtype[1];
    extern /* Subroutine */ int zspsv_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *), zlatb4_(char *, integer *, integer *, integer *, char *, 
	     integer *, integer *, doublereal *, integer *, doublereal *, 
	    char *), aladhd_(integer *, char *), alaerh_(char *, char *, integer *, integer *, char *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *);
    doublereal rcondc;
    char packit[1];
    extern /* Subroutine */ int alasvm_(char *, integer *, integer *, integer 
	    *, integer *);
    doublereal cndnum, ainvnm;
    extern /* Subroutine */ int xlaenv_(integer *, integer *), zlacpy_(char *, 
	     integer *, integer *, doublecomplex *, integer *, doublecomplex *
, integer *), zlarhs_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, integer *, integer *), zlaset_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, integer *);
    extern doublereal zlansp_(char *, char *, integer *, doublecomplex *, 
	    doublereal *);
    extern /* Subroutine */ int zlatms_(integer *, integer *, char *, integer 
	    *, char *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, integer *, char *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zlatsp_(char 
	    *, integer *, doublecomplex *, integer *);
    doublereal result[6];
    extern /* Subroutine */ int zsptrf_(char *, integer *, doublecomplex *, 
	    integer *, integer *), zsptri_(char *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zerrvx_(char *, integer *), zspsvx_(char *, char *, 
	    integer *, integer *, doublecomplex *, doublecomplex *, integer *, 
	     doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublecomplex *, 
	    doublereal *, integer *);

    /* Fortran I/O blocks */
    static cilist io___42 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_9998, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZDRVSP tests the driver routines ZSPSV and -SVX. */

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

/*  A       (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*(NMAX+1)/2) */

/*  AFAC    (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*(NMAX+1)/2) */

/*  AINV    (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*(NMAX+1)/2) */

/*  B       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  X       (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  XACT    (workspace) COMPLEX*16 array, dimension (NMAX*NRHS) */

/*  WORK    (workspace) COMPLEX*16 array, dimension */
/*                      (NMAX*max(2,NRHS)) */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (NMAX+2*NRHS) */

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
    --afac;
    --a;
    --nval;
    --dotype;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

/*     Initialize constants and the random number seed. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "SP", (ftnlen)2, (ftnlen)2);
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
	npp = n * (n + 1) / 2;
	*(unsigned char *)xtype = 'N';
	nimat = 11;
	if (n <= 0) {
	    nimat = 1;
	}

	i__2 = nimat;
	for (imat = 1; imat <= i__2; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L170;
	    }

/*           Skip types 3, 4, 5, or 6 if the matrix size is too small. */

	    zerot = imat >= 3 && imat <= 6;
	    if (zerot && n < imat - 2) {
		goto L170;
	    }

/*           Do first for UPLO = 'U', then for UPLO = 'L' */

	    for (iuplo = 1; iuplo <= 2; ++iuplo) {
		if (iuplo == 1) {
		    *(unsigned char *)uplo = 'U';
		    *(unsigned char *)packit = 'C';
		} else {
		    *(unsigned char *)uplo = 'L';
		    *(unsigned char *)packit = 'R';
		}

		if (imat != 11) {

/*                 Set up parameters with ZLATB4 and generate a test */
/*                 matrix with ZLATMS. */

		    zlatb4_(path, &imat, &n, &n, type__, &kl, &ku, &anorm, &
			    mode, &cndnum, dist);

		    s_copy(srnamc_1.srnamt, "ZLATMS", (ftnlen)32, (ftnlen)6);
		    zlatms_(&n, &n, dist, iseed, type__, &rwork[1], &mode, &
			    cndnum, &anorm, &kl, &ku, packit, &a[1], &lda, &
			    work[1], &info);

/*                 Check error code from ZLATMS. */

		    if (info != 0) {
			alaerh_(path, "ZLATMS", &info, &c__0, uplo, &n, &n, &
				c_n1, &c_n1, &c_n1, &imat, &nfail, &nerrs, 
				nout);
			goto L160;
		    }

/*                 For types 3-6, zero one or more rows and columns of */
/*                 the matrix to test that INFO is returned correctly. */

		    if (zerot) {
			if (imat == 3) {
			    izero = 1;
			} else if (imat == 4) {
			    izero = n;
			} else {
			    izero = n / 2 + 1;
			}

			if (imat < 6) {

/*                       Set row and column IZERO to zero. */

			    if (iuplo == 1) {
				ioff = (izero - 1) * izero / 2;
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
				    ioff += i__;
/* L30: */
				}
			    } else {
				ioff = izero;
				i__3 = izero - 1;
				for (i__ = 1; i__ <= i__3; ++i__) {
				    i__4 = ioff;
				    a[i__4].r = 0., a[i__4].i = 0.;
				    ioff = ioff + n - i__;
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
			    if (iuplo == 1) {

/*                          Set the first IZERO rows and columns to zero. */

				ioff = 0;
				i__3 = n;
				for (j = 1; j <= i__3; ++j) {
				    i2 = min(j,izero);
				    i__4 = i2;
				    for (i__ = 1; i__ <= i__4; ++i__) {
					i__5 = ioff + i__;
					a[i__5].r = 0., a[i__5].i = 0.;
/* L60: */
				    }
				    ioff += j;
/* L70: */
				}
			    } else {

/*                          Set the last IZERO rows and columns to zero. */

				ioff = 0;
				i__3 = n;
				for (j = 1; j <= i__3; ++j) {
				    i1 = max(j,izero);
				    i__4 = n;
				    for (i__ = i1; i__ <= i__4; ++i__) {
					i__5 = ioff + i__;
					a[i__5].r = 0., a[i__5].i = 0.;
/* L80: */
				    }
				    ioff = ioff + n - j;
/* L90: */
				}
			    }
			}
		    } else {
			izero = 0;
		    }
		} else {

/*                 Use a special block diagonal matrix to test alternate */
/*                 code for the 2-by-2 blocks. */

		    zlatsp_(uplo, &n, &a[1], iseed);
		}

		for (ifact = 1; ifact <= 2; ++ifact) {

/*                 Do first for FACT = 'F', then for other values. */

		    *(unsigned char *)fact = *(unsigned char *)&facts[ifact - 
			    1];

/*                 Compute the condition number for comparison with */
/*                 the value returned by ZSPSVX. */

		    if (zerot) {
			if (ifact == 1) {
			    goto L150;
			}
			rcondc = 0.;

		    } else if (ifact == 1) {

/*                    Compute the 1-norm of A. */

			anorm = zlansp_("1", uplo, &n, &a[1], &rwork[1]);

/*                    Factor the matrix A. */

			zcopy_(&npp, &a[1], &c__1, &afac[1], &c__1);
			zsptrf_(uplo, &n, &afac[1], &iwork[1], &info);

/*                    Compute inv(A) and take its norm. */

			zcopy_(&npp, &afac[1], &c__1, &ainv[1], &c__1);
			zsptri_(uplo, &n, &ainv[1], &iwork[1], &work[1], &
				info);
			ainvnm = zlansp_("1", uplo, &n, &ainv[1], &rwork[1]);

/*                    Compute the 1-norm condition number of A. */

			if (anorm <= 0. || ainvnm <= 0.) {
			    rcondc = 1.;
			} else {
			    rcondc = 1. / anorm / ainvnm;
			}
		    }

/*                 Form an exact solution and set the right hand side. */

		    s_copy(srnamc_1.srnamt, "ZLARHS", (ftnlen)32, (ftnlen)6);
		    zlarhs_(path, xtype, uplo, " ", &n, &n, &kl, &ku, nrhs, &
			    a[1], &lda, &xact[1], &lda, &b[1], &lda, iseed, &
			    info);
		    *(unsigned char *)xtype = 'C';

/*                 --- Test ZSPSV  --- */

		    if (ifact == 2) {
			zcopy_(&npp, &a[1], &c__1, &afac[1], &c__1);
			zlacpy_("Full", &n, nrhs, &b[1], &lda, &x[1], &lda);

/*                    Factor the matrix and solve the system using ZSPSV. */

			s_copy(srnamc_1.srnamt, "ZSPSV ", (ftnlen)32, (ftnlen)
				6);
			zspsv_(uplo, &n, nrhs, &afac[1], &iwork[1], &x[1], &
				lda, &info);

/*                    Adjust the expected value of INFO to account for */
/*                    pivoting. */

			k = izero;
			if (k > 0) {
L100:
			    if (iwork[k] < 0) {
				if (iwork[k] != -k) {
				    k = -iwork[k];
				    goto L100;
				}
			    } else if (iwork[k] != k) {
				k = iwork[k];
				goto L100;
			    }
			}

/*                    Check error code from ZSPSV . */

			if (info != k) {
			    alaerh_(path, "ZSPSV ", &info, &k, uplo, &n, &n, &
				    c_n1, &c_n1, nrhs, &imat, &nfail, &nerrs, 
				    nout);
			    goto L120;
			} else if (info != 0) {
			    goto L120;
			}

/*                    Reconstruct matrix from factors and compute */
/*                    residual. */

			zspt01_(uplo, &n, &a[1], &afac[1], &iwork[1], &ainv[1]
, &lda, &rwork[1], result);

/*                    Compute residual of the computed solution. */

			zlacpy_("Full", &n, nrhs, &b[1], &lda, &work[1], &lda);
			zspt02_(uplo, &n, nrhs, &a[1], &x[1], &lda, &work[1], 
				&lda, &rwork[1], &result[1]);

/*                    Check solution from generated exact solution. */

			zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, &
				rcondc, &result[2]);
			nt = 3;

/*                    Print information about the tests that did not pass */
/*                    the threshold. */

			i__3 = nt;
			for (k = 1; k <= i__3; ++k) {
			    if (result[k - 1] >= *thresh) {
				if (nfail == 0 && nerrs == 0) {
				    aladhd_(nout, path);
				}
				io___42.ciunit = *nout;
				s_wsfe(&io___42);
				do_fio(&c__1, "ZSPSV ", (ftnlen)6);
				do_fio(&c__1, uplo, (ftnlen)1);
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
/* L110: */
			}
			nrun += nt;
L120:
			;
		    }

/*                 --- Test ZSPSVX --- */

		    if (ifact == 2 && npp > 0) {
			zlaset_("Full", &npp, &c__1, &c_b61, &c_b61, &afac[1], 
				 &npp);
		    }
		    zlaset_("Full", &n, nrhs, &c_b61, &c_b61, &x[1], &lda);

/*                 Solve the system and compute the condition number and */
/*                 error bounds using ZSPSVX. */

		    s_copy(srnamc_1.srnamt, "ZSPSVX", (ftnlen)32, (ftnlen)6);
		    zspsvx_(fact, uplo, &n, nrhs, &a[1], &afac[1], &iwork[1], 
			    &b[1], &lda, &x[1], &lda, &rcond, &rwork[1], &
			    rwork[*nrhs + 1], &work[1], &rwork[(*nrhs << 1) + 
			    1], &info);

/*                 Adjust the expected value of INFO to account for */
/*                 pivoting. */

		    k = izero;
		    if (k > 0) {
L130:
			if (iwork[k] < 0) {
			    if (iwork[k] != -k) {
				k = -iwork[k];
				goto L130;
			    }
			} else if (iwork[k] != k) {
			    k = iwork[k];
			    goto L130;
			}
		    }

/*                 Check the error code from ZSPSVX. */

		    if (info != k) {
/* Writing concatenation */
			i__6[0] = 1, a__1[0] = fact;
			i__6[1] = 1, a__1[1] = uplo;
			s_cat(ch__1, a__1, i__6, &c__2, (ftnlen)2);
			alaerh_(path, "ZSPSVX", &info, &k, ch__1, &n, &n, &
				c_n1, &c_n1, nrhs, &imat, &nfail, &nerrs, 
				nout);
			goto L150;
		    }

		    if (info == 0) {
			if (ifact >= 2) {

/*                       Reconstruct matrix from factors and compute */
/*                       residual. */

			    zspt01_(uplo, &n, &a[1], &afac[1], &iwork[1], &
				    ainv[1], &lda, &rwork[(*nrhs << 1) + 1], 
				    result);
			    k1 = 1;
			} else {
			    k1 = 2;
			}

/*                    Compute residual of the computed solution. */

			zlacpy_("Full", &n, nrhs, &b[1], &lda, &work[1], &lda);
			zspt02_(uplo, &n, nrhs, &a[1], &x[1], &lda, &work[1], 
				&lda, &rwork[(*nrhs << 1) + 1], &result[1]);

/*                    Check solution from generated exact solution. */

			zget04_(&n, nrhs, &x[1], &lda, &xact[1], &lda, &
				rcondc, &result[2]);

/*                    Check the error bounds from iterative refinement. */

			zppt05_(uplo, &n, nrhs, &a[1], &b[1], &lda, &x[1], &
				lda, &xact[1], &lda, &rwork[1], &rwork[*nrhs 
				+ 1], &result[3]);
		    } else {
			k1 = 6;
		    }

/*                 Compare RCOND from ZSPSVX with the computed value */
/*                 in RCONDC. */

		    result[5] = dget06_(&rcond, &rcondc);

/*                 Print information about the tests that did not pass */
/*                 the threshold. */

		    for (k = k1; k <= 6; ++k) {
			if (result[k - 1] >= *thresh) {
			    if (nfail == 0 && nerrs == 0) {
				aladhd_(nout, path);
			    }
			    io___45.ciunit = *nout;
			    s_wsfe(&io___45);
			    do_fio(&c__1, "ZSPSVX", (ftnlen)6);
			    do_fio(&c__1, fact, (ftnlen)1);
			    do_fio(&c__1, uplo, (ftnlen)1);
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
/* L140: */
		    }
		    nrun = nrun + 7 - k1;

L150:
		    ;
		}

L160:
		;
	    }
L170:
	    ;
	}
/* L180: */
    }

/*     Print a summary of the results. */

    alasvm_(path, nout, &nfail, &nrun, &nerrs);

    return 0;

/*     End of ZDRVSP */

} /* zdrvsp_ */
