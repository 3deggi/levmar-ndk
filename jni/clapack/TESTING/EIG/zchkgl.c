/* zchkgl.f -- translated by f2c (version 20061008).
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
static integer c__7 = 7;
static integer c__5 = 5;
static integer c__20 = 20;

/* Subroutine */ int zchkgl_(integer *nin, integer *nout)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 .. test output of ZGGBAL .. \002)";
    static char fmt_9998[] = "(\002 ratio of largest test error             "
	    " = \002,d12.3)";
    static char fmt_9997[] = "(\002 example number where info is not zero   "
	    " = \002,i4)";
    static char fmt_9996[] = "(\002 example number where ILO or IHI is wrong"
	    " = \002,i4)";
    static char fmt_9995[] = "(\002 example number having largest error     "
	    " = \002,i4)";
    static char fmt_9994[] = "(\002 number of examples where info is not 0  "
	    " = \002,i4)";
    static char fmt_9993[] = "(\002 total number of examples tested         "
	    " = \002,i4)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3;
    doublecomplex z__1;

    /* Builtin functions */
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    double z_abs(doublecomplex *);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    doublecomplex a[400]	/* was [20][20] */, b[400]	/* was [20][
	    20] */;
    integer i__, j, n;
    doublecomplex ain[400]	/* was [20][20] */, bin[400]	/* was [20][
	    20] */;
    integer ihi, ilo;
    doublereal eps;
    integer knt, info, lmax[3];
    doublereal rmax, vmax, work[120];
    integer ihiin, ninfo, iloin;
    doublereal anorm, bnorm;
    extern doublereal dlamch_(char *);
    doublereal lscale[20];
    extern /* Subroutine */ int zggbal_(char *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    doublereal rscale[20];
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    doublereal lsclin[20], rsclin[20];

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___19 = { 0, 0, 0, 0, 0 };
    static cilist io___21 = { 0, 0, 0, 0, 0 };
    static cilist io___23 = { 0, 0, 0, 0, 0 };
    static cilist io___34 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9993, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZCHKGL tests ZGGBAL, a routine for balancing a matrix pair (A, B). */

/*  Arguments */
/*  ========= */

/*  NIN     (input) INTEGER */
/*          The logical unit number for input.  NIN > 0. */

/*  NOUT    (input) INTEGER */
/*          The logical unit number for output.  NOUT > 0. */

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

    lmax[0] = 0;
    lmax[1] = 0;
    lmax[2] = 0;
    ninfo = 0;
    knt = 0;
    rmax = 0.;

    eps = dlamch_("Precision");

L10:

    io___6.ciunit = *nin;
    s_rsle(&io___6);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    e_rsle();
    if (n == 0) {
	goto L90;
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___9.ciunit = *nin;
	s_rsle(&io___9);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&a[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L20: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___12.ciunit = *nin;
	s_rsle(&io___12);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&b[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L30: */
    }

    io___14.ciunit = *nin;
    s_rsle(&io___14);
    do_lio(&c__3, &c__1, (char *)&iloin, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&ihiin, (ftnlen)sizeof(integer));
    e_rsle();
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___17.ciunit = *nin;
	s_rsle(&io___17);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&ain[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L40: */
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___19.ciunit = *nin;
	s_rsle(&io___19);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&bin[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L50: */
    }

    io___21.ciunit = *nin;
    s_rsle(&io___21);
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__5, &c__1, (char *)&lsclin[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsle();
    io___23.ciunit = *nin;
    s_rsle(&io___23);
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__5, &c__1, (char *)&rsclin[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsle();

    anorm = zlange_("M", &n, &n, a, &c__20, work);
    bnorm = zlange_("M", &n, &n, b, &c__20, work);

    ++knt;

    zggbal_("B", &n, a, &c__20, b, &c__20, &ilo, &ihi, lscale, rscale, work, &
	    info);

    if (info != 0) {
	++ninfo;
	lmax[0] = knt;
    }

    if (ilo != iloin || ihi != ihiin) {
	++ninfo;
	lmax[1] = knt;
    }

    vmax = 0.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
	    i__3 = i__ + j * 20 - 21;
	    i__4 = i__ + j * 20 - 21;
	    z__1.r = a[i__3].r - ain[i__4].r, z__1.i = a[i__3].i - ain[i__4]
		    .i;
	    d__1 = vmax, d__2 = z_abs(&z__1);
	    vmax = max(d__1,d__2);
/* Computing MAX */
	    i__3 = i__ + j * 20 - 21;
	    i__4 = i__ + j * 20 - 21;
	    z__1.r = b[i__3].r - bin[i__4].r, z__1.i = b[i__3].i - bin[i__4]
		    .i;
	    d__1 = vmax, d__2 = z_abs(&z__1);
	    vmax = max(d__1,d__2);
/* L60: */
	}
/* L70: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__2 = vmax, d__3 = (d__1 = lscale[i__ - 1] - lsclin[i__ - 1], abs(
		d__1));
	vmax = max(d__2,d__3);
/* Computing MAX */
	d__2 = vmax, d__3 = (d__1 = rscale[i__ - 1] - rsclin[i__ - 1], abs(
		d__1));
	vmax = max(d__2,d__3);
/* L80: */
    }

    vmax /= eps * max(anorm,bnorm);

    if (vmax > rmax) {
	lmax[2] = knt;
	rmax = vmax;
    }

    goto L10;

L90:

    io___34.ciunit = *nout;
    s_wsfe(&io___34);
    e_wsfe();

    io___35.ciunit = *nout;
    s_wsfe(&io___35);
    do_fio(&c__1, (char *)&rmax, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___36.ciunit = *nout;
    s_wsfe(&io___36);
    do_fio(&c__1, (char *)&lmax[0], (ftnlen)sizeof(integer));
    e_wsfe();
    io___37.ciunit = *nout;
    s_wsfe(&io___37);
    do_fio(&c__1, (char *)&lmax[1], (ftnlen)sizeof(integer));
    e_wsfe();
    io___38.ciunit = *nout;
    s_wsfe(&io___38);
    do_fio(&c__1, (char *)&lmax[2], (ftnlen)sizeof(integer));
    e_wsfe();
    io___39.ciunit = *nout;
    s_wsfe(&io___39);
    do_fio(&c__1, (char *)&ninfo, (ftnlen)sizeof(integer));
    e_wsfe();
    io___40.ciunit = *nout;
    s_wsfe(&io___40);
    do_fio(&c__1, (char *)&knt, (ftnlen)sizeof(integer));
    e_wsfe();

    return 0;

/*     End of ZCHKGL */

} /* zchkgl_ */
