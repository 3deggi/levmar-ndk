/* dlaran.f -- translated by f2c (version 20061008).
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

doublereal dlaran_(integer *iseed)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    integer it1, it2, it3, it4;
    doublereal rndout;


/*  -- LAPACK auxiliary routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARAN returns a random real number from a uniform (0,1) */
/*  distribution. */

/*  Arguments */
/*  ========= */

/*  ISEED   (input/output) INTEGER array, dimension (4) */
/*          On entry, the seed of the random number generator; the array */
/*          elements must be between 0 and 4095, and ISEED(4) must be */
/*          odd. */
/*          On exit, the seed is updated. */

/*  Further Details */
/*  =============== */

/*  This routine uses a multiplicative congruential method with modulus */
/*  2**48 and multiplier 33952834046453 (see G.S.Fishman, */
/*  'Multiplicative congruential random number generators with modulus */
/*  2**b: an exhaustive analysis for b = 32 and a partial analysis for */
/*  b = 48', Math. Comp. 189, pp 331-344, 1990). */

/*  48-bit integers are stored in 4 integer array elements with 12 bits */
/*  per element. Hence the routine is portable across machines with */
/*  integers of 32 bits or more. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    --iseed;

    /* Function Body */
L10:

/*     multiply the seed by the multiplier modulo 2**48 */

    it4 = iseed[4] * 2549;
    it3 = it4 / 4096;
    it4 -= it3 << 12;
    it3 = it3 + iseed[3] * 2549 + iseed[4] * 2508;
    it2 = it3 / 4096;
    it3 -= it2 << 12;
    it2 = it2 + iseed[2] * 2549 + iseed[3] * 2508 + iseed[4] * 322;
    it1 = it2 / 4096;
    it2 -= it1 << 12;
    it1 = it1 + iseed[1] * 2549 + iseed[2] * 2508 + iseed[3] * 322 + iseed[4] 
	    * 494;
    it1 %= 4096;

/*     return updated seed */

    iseed[1] = it1;
    iseed[2] = it2;
    iseed[3] = it3;
    iseed[4] = it4;

/*     convert 48-bit integer to a real number in the interval (0,1) */

    rndout = ((doublereal) it1 + ((doublereal) it2 + ((doublereal) it3 + (
	    doublereal) it4 * 2.44140625e-4) * 2.44140625e-4) * 2.44140625e-4)
	     * 2.44140625e-4;

    if (rndout == 1.) {
/*        If a real number has n bits of precision, and the first */
/*        n bits of the 48-bit integer above happen to be all 1 (which */
/*        will occur about once every 2**n calls), then DLARAN will */
/*        be rounded to exactly 1.0. */
/*        Since DLARAN is not supposed to return exactly 0.0 or 1.0 */
/*        (and some callers of DLARAN, such as CLARND, depend on that), */
/*        the statistically correct thing to do in this situation is */
/*        simply to iterate again. */
/*        N.B. the case DLARAN = 0.0 should not be possible. */

	goto L10;
    }

    ret_val = rndout;
    return ret_val;

/*     End of DLARAN */

} /* dlaran_ */
