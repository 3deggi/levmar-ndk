/* cget37.f -- translated by f2c (version 20061008).
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

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__6 = 6;
static integer c__4 = 4;
static integer c__20 = 20;
static integer c__1200 = 1200;
static integer c__0 = 0;

/* Subroutine */ int cget37_(real *rmax, integer *lmax, integer *ninfo, 
	integer *knt, integer *nin)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    double r_imag(complex *);

    /* Local variables */
    integer i__, j, m, n;
    real s[20];
    complex t[400]	/* was [20][20] */;
    real v;
    complex w[20], le[400]	/* was [20][20] */, re[400]	/* was [20][
	    20] */;
    real val[3], dum[1], eps, sep[20], sin__[20], tol;
    complex tmp[400]	/* was [20][20] */;
    integer icmp;
    complex cdum[1];
    integer iscl, info, lcmp[3], kmin;
    real wiin[20], vmin, vmax, tnrm;
    integer isrt;
    real wrin[20], vmul, stmp[20];
    complex work[1200], wtmp[20];
    real wsrt[20];
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *);
    real vcmin;
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *);
    real sepin[20], tolin;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    real rwork[40];
    extern /* Subroutine */ int slabad_(real *, real *);
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *);
    extern /* Subroutine */ int cgehrd_(integer *, integer *, integer *, 
	    complex *, integer *, complex *, complex *, integer *, integer *);
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *), clacpy_(char *, integer *, integer *, complex *, integer *, 
	    complex *, integer *);
    logical select[20];
    real bignum;
    extern /* Subroutine */ int chseqr_(char *, char *, integer *, integer *, 
	    integer *, complex *, integer *, complex *, complex *, integer *, 
	    complex *, integer *, integer *), ctrevc_(char *, 
	    char *, logical *, integer *, complex *, integer *, complex *, 
	    integer *, complex *, integer *, integer *, integer *, complex *, 
	    real *, integer *), ctrsna_(char *, char *, 
	    logical *, integer *, complex *, integer *, complex *, integer *, 
	    complex *, integer *, real *, real *, integer *, integer *, 
	    complex *, integer *, real *, integer *);
    real septmp[20], smlnum;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CGET37 tests CTRSNA, a routine for estimating condition numbers of */
/*  eigenvalues and/or right eigenvectors of a matrix. */

/*  The test matrices are read from a file with logical unit number NIN. */

/*  Arguments */
/*  ========== */

/*  RMAX    (output) REAL array, dimension (3) */
/*          Value of the largest test ratio. */
/*          RMAX(1) = largest ratio comparing different calls to CTRSNA */
/*          RMAX(2) = largest error in reciprocal condition */
/*                    numbers taking their conditioning into account */
/*          RMAX(3) = largest error in reciprocal condition */
/*                    numbers not taking their conditioning into */
/*                    account (may be larger than RMAX(2)) */

/*  LMAX    (output) INTEGER array, dimension (3) */
/*          LMAX(i) is example number where largest test ratio */
/*          RMAX(i) is achieved. Also: */
/*          If CGEHRD returns INFO nonzero on example i, LMAX(1)=i */
/*          If CHSEQR returns INFO nonzero on example i, LMAX(2)=i */
/*          If CTRSNA returns INFO nonzero on example i, LMAX(3)=i */

/*  NINFO   (output) INTEGER array, dimension (3) */
/*          NINFO(1) = No. of times CGEHRD returned INFO nonzero */
/*          NINFO(2) = No. of times CHSEQR returned INFO nonzero */
/*          NINFO(3) = No. of times CTRSNA returned INFO nonzero */

/*  KNT     (output) INTEGER */
/*          Total number of examples tested. */

/*  NIN     (input) INTEGER */
/*          Input logical unit number */

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
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --ninfo;
    --lmax;
    --rmax;

    /* Function Body */
    eps = slamch_("P");
    smlnum = slamch_("S") / eps;
    bignum = 1.f / smlnum;
    slabad_(&smlnum, &bignum);

/*     EPSIN = 2**(-24) = precision to which input data computed */

    eps = dmax(eps,5.9605e-8f);
    rmax[1] = 0.f;
    rmax[2] = 0.f;
    rmax[3] = 0.f;
    lmax[1] = 0;
    lmax[2] = 0;
    lmax[3] = 0;
    *knt = 0;
    ninfo[1] = 0;
    ninfo[2] = 0;
    ninfo[3] = 0;
    val[0] = sqrt(smlnum);
    val[1] = 1.f;
    val[2] = sqrt(bignum);

/*     Read input data until N=0.  Assume input eigenvalues are sorted */
/*     lexicographically (increasing by real part if ISRT = 0, */
/*     increasing by imaginary part if ISRT = 1) */

L10:
    io___5.ciunit = *nin;
    s_rsle(&io___5);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&isrt, (ftnlen)sizeof(integer));
    e_rsle();
    if (n == 0) {
	return 0;
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___9.ciunit = *nin;
	s_rsle(&io___9);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__6, &c__1, (char *)&tmp[i__ + j * 20 - 21], (ftnlen)
		    sizeof(complex));
	}
	e_rsle();
/* L20: */
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___12.ciunit = *nin;
	s_rsle(&io___12);
	do_lio(&c__4, &c__1, (char *)&wrin[i__ - 1], (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&wiin[i__ - 1], (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&sin__[i__ - 1], (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&sepin[i__ - 1], (ftnlen)sizeof(real));
	e_rsle();
/* L30: */
    }
    tnrm = clange_("M", &n, &n, tmp, &c__20, rwork);
    for (iscl = 1; iscl <= 3; ++iscl) {

/*        Scale input matrix */

	++(*knt);
	clacpy_("F", &n, &n, tmp, &c__20, t, &c__20);
	vmul = val[iscl - 1];
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    csscal_(&n, &vmul, &t[i__ * 20 - 20], &c__1);
/* L40: */
	}
	if (tnrm == 0.f) {
	    vmul = 1.f;
	}

/*        Compute eigenvalues and eigenvectors */

	i__1 = 1200 - n;
	cgehrd_(&n, &c__1, &n, t, &c__20, work, &work[n], &i__1, &info);
	if (info != 0) {
	    lmax[1] = *knt;
	    ++ninfo[1];
	    goto L260;
	}
	i__1 = n - 2;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = n;
	    for (i__ = j + 2; i__ <= i__2; ++i__) {
		i__3 = i__ + j * 20 - 21;
		t[i__3].r = 0.f, t[i__3].i = 0.f;
/* L50: */
	    }
/* L60: */
	}

/*        Compute Schur form */

	chseqr_("S", "N", &n, &c__1, &n, t, &c__20, w, cdum, &c__1, work, &
		c__1200, &info);
	if (info != 0) {
	    lmax[2] = *knt;
	    ++ninfo[2];
	    goto L260;
	}

/*        Compute eigenvectors */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    select[i__ - 1] = TRUE_;
/* L70: */
	}
	ctrevc_("B", "A", select, &n, t, &c__20, le, &c__20, re, &c__20, &n, &
		m, work, rwork, &info);

/*        Compute condition numbers */

	ctrsna_("B", "A", select, &n, t, &c__20, le, &c__20, re, &c__20, s, 
		sep, &n, &m, work, &n, rwork, &info);
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}

/*        Sort eigenvalues and condition numbers lexicographically */
/*        to compare with inputs */

	ccopy_(&n, w, &c__1, wtmp, &c__1);
	if (isrt == 0) {

/*           Sort by increasing real part */

	    i__1 = n;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		i__2 = i__ - 1;
		wsrt[i__ - 1] = w[i__2].r;
/* L80: */
	    }
	} else {

/*           Sort by increasing imaginary part */

	    i__1 = n;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		wsrt[i__ - 1] = r_imag(&w[i__ - 1]);
/* L90: */
	    }
	}
	scopy_(&n, s, &c__1, stmp, &c__1);
	scopy_(&n, sep, &c__1, septmp, &c__1);
	r__1 = 1.f / vmul;
	sscal_(&n, &r__1, septmp, &c__1);
	i__1 = n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    kmin = i__;
	    vmin = wsrt[i__ - 1];
	    i__2 = n;
	    for (j = i__ + 1; j <= i__2; ++j) {
		if (wsrt[j - 1] < vmin) {
		    kmin = j;
		    vmin = wsrt[j - 1];
		}
/* L100: */
	    }
	    wsrt[kmin - 1] = wsrt[i__ - 1];
	    wsrt[i__ - 1] = vmin;
	    i__2 = i__ - 1;
	    vcmin = wtmp[i__2].r;
	    i__2 = i__ - 1;
	    i__3 = kmin - 1;
	    wtmp[i__2].r = w[i__3].r, wtmp[i__2].i = w[i__3].i;
	    i__2 = kmin - 1;
	    wtmp[i__2].r = vcmin, wtmp[i__2].i = 0.f;
	    vmin = stmp[kmin - 1];
	    stmp[kmin - 1] = stmp[i__ - 1];
	    stmp[i__ - 1] = vmin;
	    vmin = septmp[kmin - 1];
	    septmp[kmin - 1] = septmp[i__ - 1];
	    septmp[i__ - 1] = vmin;
/* L110: */
	}

/*        Compare condition numbers for eigenvalues */
/*        taking their condition numbers into account */

/* Computing MAX */
	r__1 = (real) n * 2.f * eps * tnrm;
	v = dmax(r__1,smlnum);
	if (tnrm == 0.f) {
	    v = 1.f;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (v > septmp[i__ - 1]) {
		tol = 1.f;
	    } else {
		tol = v / septmp[i__ - 1];
	    }
	    if (v > sepin[i__ - 1]) {
		tolin = 1.f;
	    } else {
		tolin = v / sepin[i__ - 1];
	    }
/* Computing MAX */
	    r__1 = tol, r__2 = smlnum / eps;
	    tol = dmax(r__1,r__2);
/* Computing MAX */
	    r__1 = tolin, r__2 = smlnum / eps;
	    tolin = dmax(r__1,r__2);
	    if (eps * (sin__[i__ - 1] - tolin) > stmp[i__ - 1] + tol) {
		vmax = 1.f / eps;
	    } else if (sin__[i__ - 1] - tolin > stmp[i__ - 1] + tol) {
		vmax = (sin__[i__ - 1] - tolin) / (stmp[i__ - 1] + tol);
	    } else if (sin__[i__ - 1] + tolin < eps * (stmp[i__ - 1] - tol)) {
		vmax = 1.f / eps;
	    } else if (sin__[i__ - 1] + tolin < stmp[i__ - 1] - tol) {
		vmax = (stmp[i__ - 1] - tol) / (sin__[i__ - 1] + tolin);
	    } else {
		vmax = 1.f;
	    }
	    if (vmax > rmax[2]) {
		rmax[2] = vmax;
		if (ninfo[2] == 0) {
		    lmax[2] = *knt;
		}
	    }
/* L120: */
	}

/*        Compare condition numbers for eigenvectors */
/*        taking their condition numbers into account */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (v > septmp[i__ - 1] * stmp[i__ - 1]) {
		tol = septmp[i__ - 1];
	    } else {
		tol = v / stmp[i__ - 1];
	    }
	    if (v > sepin[i__ - 1] * sin__[i__ - 1]) {
		tolin = sepin[i__ - 1];
	    } else {
		tolin = v / sin__[i__ - 1];
	    }
/* Computing MAX */
	    r__1 = tol, r__2 = smlnum / eps;
	    tol = dmax(r__1,r__2);
/* Computing MAX */
	    r__1 = tolin, r__2 = smlnum / eps;
	    tolin = dmax(r__1,r__2);
	    if (eps * (sepin[i__ - 1] - tolin) > septmp[i__ - 1] + tol) {
		vmax = 1.f / eps;
	    } else if (sepin[i__ - 1] - tolin > septmp[i__ - 1] + tol) {
		vmax = (sepin[i__ - 1] - tolin) / (septmp[i__ - 1] + tol);
	    } else if (sepin[i__ - 1] + tolin < eps * (septmp[i__ - 1] - tol))
		     {
		vmax = 1.f / eps;
	    } else if (sepin[i__ - 1] + tolin < septmp[i__ - 1] - tol) {
		vmax = (septmp[i__ - 1] - tol) / (sepin[i__ - 1] + tolin);
	    } else {
		vmax = 1.f;
	    }
	    if (vmax > rmax[2]) {
		rmax[2] = vmax;
		if (ninfo[2] == 0) {
		    lmax[2] = *knt;
		}
	    }
/* L130: */
	}

/*        Compare condition numbers for eigenvalues */
/*        without taking their condition numbers into account */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (sin__[i__ - 1] <= (real) (n << 1) * eps && stmp[i__ - 1] <= (
		    real) (n << 1) * eps) {
		vmax = 1.f;
	    } else if (eps * sin__[i__ - 1] > stmp[i__ - 1]) {
		vmax = 1.f / eps;
	    } else if (sin__[i__ - 1] > stmp[i__ - 1]) {
		vmax = sin__[i__ - 1] / stmp[i__ - 1];
	    } else if (sin__[i__ - 1] < eps * stmp[i__ - 1]) {
		vmax = 1.f / eps;
	    } else if (sin__[i__ - 1] < stmp[i__ - 1]) {
		vmax = stmp[i__ - 1] / sin__[i__ - 1];
	    } else {
		vmax = 1.f;
	    }
	    if (vmax > rmax[3]) {
		rmax[3] = vmax;
		if (ninfo[3] == 0) {
		    lmax[3] = *knt;
		}
	    }
/* L140: */
	}

/*        Compare condition numbers for eigenvectors */
/*        without taking their condition numbers into account */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (sepin[i__ - 1] <= v && septmp[i__ - 1] <= v) {
		vmax = 1.f;
	    } else if (eps * sepin[i__ - 1] > septmp[i__ - 1]) {
		vmax = 1.f / eps;
	    } else if (sepin[i__ - 1] > septmp[i__ - 1]) {
		vmax = sepin[i__ - 1] / septmp[i__ - 1];
	    } else if (sepin[i__ - 1] < eps * septmp[i__ - 1]) {
		vmax = 1.f / eps;
	    } else if (sepin[i__ - 1] < septmp[i__ - 1]) {
		vmax = septmp[i__ - 1] / sepin[i__ - 1];
	    } else {
		vmax = 1.f;
	    }
	    if (vmax > rmax[3]) {
		rmax[3] = vmax;
		if (ninfo[3] == 0) {
		    lmax[3] = *knt;
		}
	    }
/* L150: */
	}

/*        Compute eigenvalue condition numbers only and compare */

	vmax = 0.f;
	dum[0] = -1.f;
	scopy_(&n, dum, &c__0, stmp, &c__1);
	scopy_(&n, dum, &c__0, septmp, &c__1);
	ctrsna_("E", "A", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (stmp[i__ - 1] != s[i__ - 1]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
/* L160: */
	}

/*        Compute eigenvector condition numbers only and compare */

	scopy_(&n, dum, &c__0, stmp, &c__1);
	scopy_(&n, dum, &c__0, septmp, &c__1);
	ctrsna_("V", "A", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (stmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != sep[i__ - 1]) {
		vmax = 1.f / eps;
	    }
/* L170: */
	}

/*        Compute all condition numbers using SELECT and compare */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    select[i__ - 1] = TRUE_;
/* L180: */
	}
	scopy_(&n, dum, &c__0, stmp, &c__1);
	scopy_(&n, dum, &c__0, septmp, &c__1);
	ctrsna_("B", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (septmp[i__ - 1] != sep[i__ - 1]) {
		vmax = 1.f / eps;
	    }
	    if (stmp[i__ - 1] != s[i__ - 1]) {
		vmax = 1.f / eps;
	    }
/* L190: */
	}

/*        Compute eigenvalue condition numbers using SELECT and compare */

	scopy_(&n, dum, &c__0, stmp, &c__1);
	scopy_(&n, dum, &c__0, septmp, &c__1);
	ctrsna_("E", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (stmp[i__ - 1] != s[i__ - 1]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
/* L200: */
	}

/*        Compute eigenvector condition numbers using SELECT and compare */

	scopy_(&n, dum, &c__0, stmp, &c__1);
	scopy_(&n, dum, &c__0, septmp, &c__1);
	ctrsna_("V", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (stmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != sep[i__ - 1]) {
		vmax = 1.f / eps;
	    }
/* L210: */
	}
	if (vmax > rmax[1]) {
	    rmax[1] = vmax;
	    if (ninfo[1] == 0) {
		lmax[1] = *knt;
	    }
	}

/*        Select second and next to last eigenvalues */

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    select[i__ - 1] = FALSE_;
/* L220: */
	}
	icmp = 0;
	if (n > 1) {
	    icmp = 1;
	    lcmp[0] = 2;
	    select[1] = TRUE_;
	    ccopy_(&n, &re[20], &c__1, re, &c__1);
	    ccopy_(&n, &le[20], &c__1, le, &c__1);
	}
	if (n > 3) {
	    icmp = 2;
	    lcmp[1] = n - 1;
	    select[n - 2] = TRUE_;
	    ccopy_(&n, &re[(n - 1) * 20 - 20], &c__1, &re[20], &c__1);
	    ccopy_(&n, &le[(n - 1) * 20 - 20], &c__1, &le[20], &c__1);
	}

/*        Compute all selected condition numbers */

	scopy_(&icmp, dum, &c__0, stmp, &c__1);
	scopy_(&icmp, dum, &c__0, septmp, &c__1);
	ctrsna_("B", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = icmp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = lcmp[i__ - 1];
	    if (septmp[i__ - 1] != sep[j - 1]) {
		vmax = 1.f / eps;
	    }
	    if (stmp[i__ - 1] != s[j - 1]) {
		vmax = 1.f / eps;
	    }
/* L230: */
	}

/*        Compute selected eigenvalue condition numbers */

	scopy_(&icmp, dum, &c__0, stmp, &c__1);
	scopy_(&icmp, dum, &c__0, septmp, &c__1);
	ctrsna_("E", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = icmp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = lcmp[i__ - 1];
	    if (stmp[i__ - 1] != s[j - 1]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
/* L240: */
	}

/*        Compute selected eigenvector condition numbers */

	scopy_(&icmp, dum, &c__0, stmp, &c__1);
	scopy_(&icmp, dum, &c__0, septmp, &c__1);
	ctrsna_("V", "S", select, &n, t, &c__20, le, &c__20, re, &c__20, stmp, 
		 septmp, &n, &m, work, &n, rwork, &info)
		;
	if (info != 0) {
	    lmax[3] = *knt;
	    ++ninfo[3];
	    goto L260;
	}
	i__1 = icmp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = lcmp[i__ - 1];
	    if (stmp[i__ - 1] != dum[0]) {
		vmax = 1.f / eps;
	    }
	    if (septmp[i__ - 1] != sep[j - 1]) {
		vmax = 1.f / eps;
	    }
/* L250: */
	}
	if (vmax > rmax[1]) {
	    rmax[1] = vmax;
	    if (ninfo[1] == 0) {
		lmax[1] = *knt;
	    }
	}
L260:
	;
    }
    goto L10;

/*     End of CGET37 */

} /* cget37_ */
