/* clctsx.f -- translated by f2c (version 20061008).
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
    integer m, n, mplusn, i__;
    logical fs;
} mn_;

#define mn_1 mn_

logical clctsx_(complex *alpha, complex *beta)
{
    /* System generated locals */
    logical ret_val;


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  This function is used to determine what eigenvalues will be */
/*  selected.  If this is part of the test driver CDRGSX, do not */
/*  change the code UNLESS you are testing input examples and not */
/*  using the built-in examples. */

/*  Arguments */
/*  ========= */

/*  ALPHA   (input) COMPLEX */
/*  BETA    (input) COMPLEX */
/*          parameters to decide whether the pair (ALPHA, BETA) is */
/*          selected. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     REAL               ZERO */
/*     PARAMETER          ( ZERO = 0.0E+0 ) */
/*     COMPLEX            CZERO */
/*     PARAMETER          ( CZERO = ( 0.0E+0, 0.0E+0 ) ) */
/*     .. */
/*     .. Scalars in Common .. */
/*     .. */
/*     .. Common blocks .. */
/*     .. */
/*     .. Save statement .. */
/*     .. */
/*     .. Executable Statements .. */

    if (mn_1.fs) {
	++mn_1.i__;
	if (mn_1.i__ <= mn_1.m) {
	    ret_val = FALSE_;
	} else {
	    ret_val = TRUE_;
	}
	if (mn_1.i__ == mn_1.mplusn) {
	    mn_1.fs = FALSE_;
	    mn_1.i__ = 0;
	}
    } else {
	++mn_1.i__;
	if (mn_1.i__ <= mn_1.n) {
	    ret_val = TRUE_;
	} else {
	    ret_val = FALSE_;
	}
	if (mn_1.i__ == mn_1.mplusn) {
	    mn_1.fs = TRUE_;
	    mn_1.i__ = 0;
	}
    }

/*      IF( BETA.EQ.CZERO ) THEN */
/*         CLCTSX = ( REAL( ALPHA ).GT.ZERO ) */
/*      ELSE */
/*         CLCTSX = ( REAL( ALPHA/BETA ).GT.ZERO ) */
/*      END IF */

    return ret_val;

/*     End of CLCTSX */

} /* clctsx_ */
