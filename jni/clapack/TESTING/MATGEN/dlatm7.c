/* dlatm7.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int dlatm7_(integer *mode, doublereal *cond, integer *irsign, 
	 integer *idist, integer *iseed, doublereal *d__, integer *n, integer 
	*rank, integer *info)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), pow_di(doublereal *, integer *)
	    , log(doublereal), exp(doublereal);

    /* Local variables */
    integer i__;
    doublereal temp, alpha;
    extern doublereal dlaran_(integer *);
    extern /* Subroutine */ int xerbla_(char *, integer *), dlarnv_(
	    integer *, integer *, integer *, doublereal *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Craig Lucas, University of Manchester / NAG Ltd. */
/*     October, 2008 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     DLATM7 computes the entries of D as specified by MODE */
/*     COND and IRSIGN. IDIST and ISEED determine the generation */
/*     of random numbers. DLATM7 is called by DLATMT to generate */
/*     random test matrices. */

/*  Arguments */
/*  ========= */

/*  MODE   - INTEGER */
/*           On entry describes how D is to be computed: */
/*           MODE = 0 means do not change D. */

/*           MODE = 1 sets D(1)=1 and D(2:RANK)=1.0/COND */
/*           MODE = 2 sets D(1:RANK-1)=1 and D(RANK)=1.0/COND */
/*           MODE = 3 sets D(I)=COND**(-(I-1)/(RANK-1)) I=1:RANK */

/*           MODE = 4 sets D(i)=1 - (i-1)/(N-1)*(1 - 1/COND) */
/*           MODE = 5 sets D to random numbers in the range */
/*                    ( 1/COND , 1 ) such that their logarithms */
/*                    are uniformly distributed. */
/*           MODE = 6 set D to random numbers from same distribution */
/*                    as the rest of the matrix. */
/*           MODE < 0 has the same meaning as ABS(MODE), except that */
/*              the order of the elements of D is reversed. */
/*           Thus if MODE is positive, D has entries ranging from */
/*              1 to 1/COND, if negative, from 1/COND to 1, */
/*           Not modified. */

/*  COND   - DOUBLE PRECISION */
/*           On entry, used as described under MODE above. */
/*           If used, it must be >= 1. Not modified. */

/*  IRSIGN - INTEGER */
/*           On entry, if MODE neither -6, 0 nor 6, determines sign of */
/*           entries of D */
/*           0 => leave entries of D unchanged */
/*           1 => multiply each entry of D by 1 or -1 with probability .5 */

/*  IDIST  - CHARACTER*1 */
/*           On entry, IDIST specifies the type of distribution to be */
/*           used to generate a random matrix . */
/*           1 => UNIFORM( 0, 1 ) */
/*           2 => UNIFORM( -1, 1 ) */
/*           3 => NORMAL( 0, 1 ) */
/*           Not modified. */

/*  ISEED  - INTEGER array, dimension ( 4 ) */
/*           On entry ISEED specifies the seed of the random number */
/*           generator. The random number generator uses a */
/*           linear congruential sequence limited to small */
/*           integers, and so should produce machine independent */
/*           random numbers. The values of ISEED are changed on */
/*           exit, and can be used in the next call to DLATM7 */
/*           to continue the same random number sequence. */
/*           Changed on exit. */

/*  D      - DOUBLE PRECISION array, dimension ( MIN( M , N ) ) */
/*           Array to be computed according to MODE, COND and IRSIGN. */
/*           May be changed on exit if MODE is nonzero. */

/*  N      - INTEGER */
/*           Number of entries of D. Not modified. */

/*  RANK   - INTEGER */
/*           The rank of matrix to be generated for modes 1,2,3 only. */
/*           D( RANK+1:N ) = 0. */
/*           Not modified. */

/*  INFO   - INTEGER */
/*            0  => normal termination */
/*           -1  => if MODE not in range -6 to 6 */
/*           -2  => if MODE neither -6, 0 nor 6, and */
/*                  IRSIGN neither 0 nor 1 */
/*           -3  => if MODE neither -6, 0 nor 6 and COND less than 1 */
/*           -4  => if MODE equals 6 or -6 and IDIST not in range 1 to 3 */
/*           -7  => if N negative */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Decode and Test the input parameters. Initialize flags & seed. */

    /* Parameter adjustments */
    --d__;
    --iseed;

    /* Function Body */
    *info = 0;

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Set INFO if an error */

    if (*mode < -6 || *mode > 6) {
	*info = -1;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && (*irsign != 0 && *
	    irsign != 1)) {
	*info = -2;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && *cond < 1.) {
	*info = -3;
    } else if ((*mode == 6 || *mode == -6) && (*idist < 1 || *idist > 3)) {
	*info = -4;
    } else if (*n < 0) {
	*info = -7;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLATM7", &i__1);
	return 0;
    }

/*     Compute D according to COND and MODE */

    if (*mode != 0) {
	switch (abs(*mode)) {
	    case 1:  goto L100;
	    case 2:  goto L130;
	    case 3:  goto L160;
	    case 4:  goto L190;
	    case 5:  goto L210;
	    case 6:  goto L230;
	}

/*        One large D value: */

L100:
	i__1 = *rank;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    d__[i__] = 1. / *cond;
/* L110: */
	}
	i__1 = *n;
	for (i__ = *rank + 1; i__ <= i__1; ++i__) {
	    d__[i__] = 0.;
/* L120: */
	}
	d__[1] = 1.;
	goto L240;

/*        One small D value: */

L130:
	i__1 = *rank - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d__[i__] = 1.;
/* L140: */
	}
	i__1 = *n;
	for (i__ = *rank + 1; i__ <= i__1; ++i__) {
	    d__[i__] = 0.;
/* L150: */
	}
	d__[*rank] = 1. / *cond;
	goto L240;

/*        Exponentially distributed D values: */

L160:
	d__[1] = 1.;
	if (*n > 1) {
	    d__1 = -1. / (doublereal) (*rank - 1);
	    alpha = pow_dd(cond, &d__1);
	    i__1 = *rank;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		i__2 = i__ - 1;
		d__[i__] = pow_di(&alpha, &i__2);
/* L170: */
	    }
	    i__1 = *n;
	    for (i__ = *rank + 1; i__ <= i__1; ++i__) {
		d__[i__] = 0.;
/* L180: */
	    }
	}
	goto L240;

/*        Arithmetically distributed D values: */

L190:
	d__[1] = 1.;
	if (*n > 1) {
	    temp = 1. / *cond;
	    alpha = (1. - temp) / (doublereal) (*n - 1);
	    i__1 = *n;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		d__[i__] = (doublereal) (*n - i__) * alpha + temp;
/* L200: */
	    }
	}
	goto L240;

/*        Randomly distributed D values on ( 1/COND , 1): */

L210:
	alpha = log(1. / *cond);
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d__[i__] = exp(alpha * dlaran_(&iseed[1]));
/* L220: */
	}
	goto L240;

/*        Randomly distributed D values from IDIST */

L230:
	dlarnv_(idist, &iseed[1], n, &d__[1]);

L240:

/*        If MODE neither -6 nor 0 nor 6, and IRSIGN = 1, assign */
/*        random signs to D */

	if (*mode != -6 && *mode != 0 && *mode != 6 && *irsign == 1) {
	    i__1 = *n;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		temp = dlaran_(&iseed[1]);
		if (temp > .5) {
		    d__[i__] = -d__[i__];
		}
/* L250: */
	    }
	}

/*        Reverse if MODE < 0 */

	if (*mode < 0) {
	    i__1 = *n / 2;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		temp = d__[i__];
		d__[i__] = d__[*n + 1 - i__];
		d__[*n + 1 - i__] = temp;
/* L260: */
	    }
	}

    }

    return 0;

/*     End of DLATM7 */

} /* dlatm7_ */
