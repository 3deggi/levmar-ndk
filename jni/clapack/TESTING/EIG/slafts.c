/* slafts.f -- translated by f2c (version 20061008).
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

static integer c__1 = 1;
static integer c__4 = 4;

/* Subroutine */ int slafts_(char *type__, integer *m, integer *n, integer *
	imat, integer *ntests, real *result, integer *iseed, real *thresh, 
	integer *iounit, integer *ie)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i3,\002 is\002"
	    ",0p,f8.2)";
    static char fmt_9998[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i3,\002 is\002"
	    ",1p,e10.3)";
    static char fmt_9997[] = "(1x,i5,\002 x\002,i5,\002 matrix, type=\002,"
	    "i2,\002, s\002,\002eed=\002,3(i4,\002,\002),i4,\002: result \002"
	    ",i3,\002 is\002,0p,f8.2)";
    static char fmt_9996[] = "(1x,i5,\002 x\002,i5,\002 matrix, type=\002,"
	    "i2,\002, s\002,\002eed=\002,3(i4,\002,\002),i4,\002: result \002"
	    ",i3,\002 is\002,1p,e10.3)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer k;
    extern /* Subroutine */ int slahd2_(integer *, char *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_9996, 0 };



/*  -- LAPACK auxiliary test routine (version 3.1.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     April 2009 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     SLAFTS tests the result vector against the threshold value to */
/*     see which tests for this matrix type failed to pass the threshold. */
/*     Output is to the file given by unit IOUNIT. */

/*  Arguments */
/*  ========= */

/*  TYPE   - CHARACTER*3 */
/*           On entry, TYPE specifies the matrix type to be used in the */
/*           printed messages. */
/*           Not modified. */

/*  N      - INTEGER */
/*           On entry, N specifies the order of the test matrix. */
/*           Not modified. */

/*  IMAT   - INTEGER */
/*           On entry, IMAT specifies the type of the test matrix. */
/*           A listing of the different types is printed by SLAHD2 */
/*           to the output file if a test fails to pass the threshold. */
/*           Not modified. */

/*  NTESTS - INTEGER */
/*           On entry, NTESTS is the number of tests performed on the */
/*           subroutines in the path given by TYPE. */
/*           Not modified. */

/*  RESULT - REAL               array of dimension( NTESTS ) */
/*           On entry, RESULT contains the test ratios from the tests */
/*           performed in the calling program. */
/*           Not modified. */

/*  ISEED  - INTEGER            array of dimension( 4 ) */
/*           Contains the random seed that generated the matrix used */
/*           for the tests whose ratios are in RESULT. */
/*           Not modified. */

/*  THRESH - REAL */
/*           On entry, THRESH specifies the acceptable threshold of the */
/*           test ratios.  If RESULT( K ) > THRESH, then the K-th test */
/*           did not pass the threshold and a message will be printed. */
/*           Not modified. */

/*  IOUNIT - INTEGER */
/*           On entry, IOUNIT specifies the unit number of the file */
/*           to which the messages are printed. */
/*           Not modified. */

/*  IE     - INTEGER */
/*           On entry, IE contains the number of tests which have */
/*           failed to pass the threshold so far. */
/*           Updated on exit if any of the ratios in RESULT also fail. */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --iseed;
    --result;

    /* Function Body */
    if (*m == *n) {

/*     Output for square matrices: */

	i__1 = *ntests;
	for (k = 1; k <= i__1; ++k) {
	    if (result[k] >= *thresh) {

/*           If this is the first test to fail, call SLAHD2 */
/*           to print a header to the data file. */

		if (*ie == 0) {
		    slahd2_(iounit, type__);
		}
		++(*ie);
		if (result[k] < 1e4f) {
		    io___2.ciunit = *iounit;
		    s_wsfe(&io___2);
		    do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*imat), (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&iseed[1], (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[k], (ftnlen)sizeof(real));
		    e_wsfe();
		} else {
		    io___3.ciunit = *iounit;
		    s_wsfe(&io___3);
		    do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*imat), (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&iseed[1], (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[k], (ftnlen)sizeof(real));
		    e_wsfe();
		}
	    }
/* L10: */
	}
    } else {

/*     Output for rectangular matrices */

	i__1 = *ntests;
	for (k = 1; k <= i__1; ++k) {
	    if (result[k] >= *thresh) {

/*              If this is the first test to fail, call SLAHD2 */
/*              to print a header to the data file. */

		if (*ie == 0) {
		    slahd2_(iounit, type__);
		}
		++(*ie);
		if (result[k] < 1e4f) {
		    io___4.ciunit = *iounit;
		    s_wsfe(&io___4);
		    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*imat), (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&iseed[1], (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[k], (ftnlen)sizeof(real));
		    e_wsfe();
		} else {
		    io___5.ciunit = *iounit;
		    s_wsfe(&io___5);
		    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&(*imat), (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&iseed[1], (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[k], (ftnlen)sizeof(real));
		    e_wsfe();
		}
	    }
/* L20: */
	}

    }
    return 0;

/*     End of SLAFTS */

} /* slafts_ */
