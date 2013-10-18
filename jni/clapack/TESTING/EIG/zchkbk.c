/* zchkbk.f -- translated by f2c (version 20061008).
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
static integer c__5 = 5;
static integer c__7 = 7;
static integer c__20 = 20;

/* Subroutine */ int zchkbk_(integer *nin, integer *nout)
{
    /* Format strings */
    static char fmt_9999[] = "(1x,\002.. test output of ZGEBAK .. \002)";
    static char fmt_9998[] = "(1x,\002value of largest test error           "
	    "  = \002,d12.3)";
    static char fmt_9997[] = "(1x,\002example number where info is not zero "
	    "  = \002,i4)";
    static char fmt_9996[] = "(1x,\002example number having largest error   "
	    "  = \002,i4)";
    static char fmt_9995[] = "(1x,\002number of examples where info is not 0"
	    "  = \002,i4)";
    static char fmt_9994[] = "(1x,\002total number of examples tested       "
	    "  = \002,i4)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    double d_imag(doublecomplex *);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    doublecomplex e[400]	/* was [20][20] */;
    integer i__, j, n;
    doublereal x;
    integer ihi;
    doublecomplex ein[400]	/* was [20][20] */;
    integer ilo;
    doublereal eps;
    integer knt, info, lmax[2];
    doublereal rmax, vmax, scale[20];
    integer ninfo;
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int zgebak_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublecomplex *, integer *, 
	    integer *);
    doublereal safmin;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___23 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_9994, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ZCHKBK tests ZGEBAK, a routine for backward transformation of */
/*  the computed right or left eigenvectors if the orginal matrix */
/*  was preprocessed by balance subroutine ZGEBAL. */

/*  Arguments */
/*  ========= */

/*  NIN     (input) INTEGER */
/*          The logical unit number for input.  NIN > 0. */

/*  NOUT    (input) INTEGER */
/*          The logical unit number for output.  NOUT > 0. */

/* ====================================================================== */

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
/*     .. Statement Functions .. */
/*     .. */
/*     .. Statement Function definitions .. */
/*     .. */
/*     .. Executable Statements .. */

    lmax[0] = 0;
    lmax[1] = 0;
    ninfo = 0;
    knt = 0;
    rmax = 0.;
    eps = dlamch_("E");
    safmin = dlamch_("S");

L10:

    io___7.ciunit = *nin;
    s_rsle(&io___7);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&ilo, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&ihi, (ftnlen)sizeof(integer));
    e_rsle();
    if (n == 0) {
	goto L60;
    }

    io___11.ciunit = *nin;
    s_rsle(&io___11);
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__5, &c__1, (char *)&scale[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsle();
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___14.ciunit = *nin;
	s_rsle(&io___14);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&e[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L20: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___17.ciunit = *nin;
	s_rsle(&io___17);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&ein[i__ + j * 20 - 21], (ftnlen)
		    sizeof(doublecomplex));
	}
	e_rsle();
/* L30: */
    }

    ++knt;
    zgebak_("B", "R", &n, &ilo, &ihi, scale, &n, e, &c__20, &info);

    if (info != 0) {
	++ninfo;
	lmax[0] = knt;
    }

    vmax = 0.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    i__3 = i__ + j * 20 - 21;
	    i__4 = i__ + j * 20 - 21;
	    z__2.r = e[i__3].r - ein[i__4].r, z__2.i = e[i__3].i - ein[i__4]
		    .i;
	    z__1.r = z__2.r, z__1.i = z__2.i;
	    x = ((d__1 = z__1.r, abs(d__1)) + (d__2 = d_imag(&z__1), abs(d__2)
		    )) / eps;
	    i__3 = i__ + j * 20 - 21;
	    if ((d__1 = e[i__3].r, abs(d__1)) + (d__2 = d_imag(&e[i__ + j * 
		    20 - 21]), abs(d__2)) > safmin) {
		i__4 = i__ + j * 20 - 21;
		x /= (d__3 = e[i__4].r, abs(d__3)) + (d__4 = d_imag(&e[i__ + 
			j * 20 - 21]), abs(d__4));
	    }
	    vmax = max(vmax,x);
/* L40: */
	}
/* L50: */
    }

    if (vmax > rmax) {
	lmax[1] = knt;
	rmax = vmax;
    }

    goto L10;

L60:

    io___22.ciunit = *nout;
    s_wsfe(&io___22);
    e_wsfe();

    io___23.ciunit = *nout;
    s_wsfe(&io___23);
    do_fio(&c__1, (char *)&rmax, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___24.ciunit = *nout;
    s_wsfe(&io___24);
    do_fio(&c__1, (char *)&lmax[0], (ftnlen)sizeof(integer));
    e_wsfe();
    io___25.ciunit = *nout;
    s_wsfe(&io___25);
    do_fio(&c__1, (char *)&lmax[1], (ftnlen)sizeof(integer));
    e_wsfe();
    io___26.ciunit = *nout;
    s_wsfe(&io___26);
    do_fio(&c__1, (char *)&ninfo, (ftnlen)sizeof(integer));
    e_wsfe();
    io___27.ciunit = *nout;
    s_wsfe(&io___27);
    do_fio(&c__1, (char *)&knt, (ftnlen)sizeof(integer));
    e_wsfe();

    return 0;

/*     End of ZCHKBK */

} /* zchkbk_ */
