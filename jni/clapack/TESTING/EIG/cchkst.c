/* cchkst.f -- translated by f2c (version 20061008).
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

static complex c_b1 = {0.f,0.f};
static complex c_b2 = {1.f,0.f};
static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__0 = 0;
static integer c__6 = 6;
static real c_b39 = 1.f;
static real c_b49 = 0.f;
static integer c__4 = 4;
static integer c__3 = 3;
static integer c__10 = 10;
static integer c__11 = 11;

/* Subroutine */ int cchkst_(integer *nsizes, integer *nn, integer *ntypes, 
	logical *dotype, integer *iseed, real *thresh, integer *nounit, 
	complex *a, integer *lda, complex *ap, real *sd, real *se, real *d1, 
	real *d2, real *d3, real *d4, real *d5, real *wa1, real *wa2, real *
	wa3, real *wr, complex *u, integer *ldu, complex *v, complex *vp, 
	complex *tau, complex *z__, complex *work, integer *lwork, real *
	rwork, integer *lrwork, integer *iwork, integer *liwork, real *result, 
	 integer *info)
{
    /* Initialized data */

    static integer ktype[21] = { 1,2,4,4,4,4,4,5,5,5,5,5,8,8,8,9,9,9,9,9,10 };
    static integer kmagn[21] = { 1,1,1,1,1,2,3,1,1,1,2,3,1,2,3,1,1,1,2,3,1 };
    static integer kmode[21] = { 0,0,4,3,1,4,4,4,3,1,4,4,0,0,0,4,3,1,4,4,3 };

    /* Format strings */
    static char fmt_9999[] = "(\002 CCHKST: \002,a,\002 returned INFO=\002,i"
	    "6,\002.\002,/9x,\002N=\002,i6,\002, JTYPE=\002,i6,\002, ISEED="
	    "(\002,3(i5,\002,\002),i5,\002)\002)";
    static char fmt_9998[] = "(/1x,a3,\002 -- Complex Hermitian eigenvalue p"
	    "roblem\002)";
    static char fmt_9997[] = "(\002 Matrix types (see CCHKST for details):"
	    " \002)";
    static char fmt_9996[] = "(/\002 Special Matrices:\002,/\002  1=Zero mat"
	    "rix.                        \002,\002  5=Diagonal: clustered ent"
	    "ries.\002,/\002  2=Identity matrix.                    \002,\002"
	    "  6=Diagonal: large, evenly spaced.\002,/\002  3=Diagonal: evenl"
	    "y spaced entries.    \002,\002  7=Diagonal: small, evenly spaced."
	    "\002,/\002  4=Diagonal: geometr. spaced entries.\002)";
    static char fmt_9995[] = "(\002 Dense \002,a,\002 Matrices:\002,/\002  8"
	    "=Evenly spaced eigenvals.            \002,\002 12=Small, evenly "
	    "spaced eigenvals.\002,/\002  9=Geometrically spaced eigenvals.  "
	    "   \002,\002 13=Matrix with random O(1) entries.\002,/\002 10=Cl"
	    "ustered eigenvalues.              \002,\002 14=Matrix with large"
	    " random entries.\002,/\002 11=Large, evenly spaced eigenvals.   "
	    "  \002,\002 15=Matrix with small random entries.\002)";
    static char fmt_9994[] = "(\002 16=Positive definite, evenly spaced eige"
	    "nvalues\002,/\002 17=Positive definite, geometrically spaced eig"
	    "envlaues\002,/\002 18=Positive definite, clustered eigenvalue"
	    "s\002,/\002 19=Positive definite, small evenly spaced eigenvalues"
	    "\002,/\002 20=Positive definite, large evenly spaced eigenvalue"
	    "s\002,/\002 21=Diagonally dominant tridiagonal, geometrically"
	    "\002,\002 spaced eigenvalues\002)";
    static char fmt_9987[] = "(/\002Test performed:  see CCHKST for details"
	    ".\002,/)";
    static char fmt_9989[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i3,\002 is\002"
	    ",0p,f8.2)";
    static char fmt_9988[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i3,\002 is\002"
	    ",1p,e10.3)";

    /* System generated locals */
    integer a_dim1, a_offset, u_dim1, u_offset, v_dim1, v_offset, z_dim1, 
	    z_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    real r__1, r__2, r__3, r__4;
    complex q__1;

    /* Builtin functions */
    double log(doublereal), sqrt(doublereal);
    integer pow_ii(integer *, integer *);
    double c_abs(complex *);
    void r_cnjg(complex *, complex *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, j, m, n, m2, m3, jc, il, jr, iu;
    real vl, vu;
    integer nap, lgn;
    real ulp;
    integer inde;
    real cond;
    integer nmax;
    real unfl, ovfl, temp1, temp2, temp3, temp4;
    logical badnn;
    extern doublereal ssxt1_(integer *, real *, integer *, real *, integer *, 
	    real *, real *, real *);
    extern /* Subroutine */ int chet21_(integer *, char *, integer *, integer 
	    *, complex *, integer *, real *, real *, complex *, integer *, 
	    complex *, integer *, complex *, complex *, real *, real *);
    integer imode, lwedc;
    extern /* Subroutine */ int chpt21_(integer *, char *, integer *, integer 
	    *, complex *, real *, real *, complex *, integer *, complex *, 
	    complex *, complex *, real *, real *);
    real dumma[1];
    integer iinfo;
    real aninv, anorm;
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *);
    integer itemp;
    extern /* Subroutine */ int cstt21_(integer *, integer *, real *, real *, 
	    real *, real *, complex *, integer *, complex *, real *, real *), 
	    cstt22_(integer *, integer *, integer *, real *, real *, real *, 
	    real *, complex *, integer *, complex *, integer *, real *, real *
);
    integer nmats, jsize, nerrs, itype, jtype, ntest;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    integer iseed2[4], log2ui;
    extern /* Subroutine */ int slabad_(real *, real *), cstedc_(char *, 
	    integer *, real *, real *, complex *, integer *, complex *, 
	    integer *, real *, integer *, integer *, integer *, integer *);
    integer liwedc, nblock;
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int chetrd_(char *, integer *, complex *, integer 
	    *, real *, real *, complex *, complex *, integer *, integer *), clacpy_(char *, integer *, integer *, complex *, integer 
	    *, complex *, integer *);
    integer idumma[1];
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *);
    integer ioldsd[4], lrwedc;
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *);
    extern /* Subroutine */ int clatmr_(integer *, integer *, char *, integer 
	    *, char *, complex *, integer *, real *, complex *, char *, char *
, complex *, integer *, real *, complex *, integer *, real *, 
	    char *, integer *, integer *, integer *, real *, real *, char *, 
	    complex *, integer *, integer *, integer *);
    extern doublereal slarnd_(integer *, integer *);
    real abstol;
    extern /* Subroutine */ int chptrd_(char *, integer *, complex *, real *, 
	    real *, complex *, integer *), clatms_(integer *, integer 
	    *, char *, integer *, char *, real *, integer *, real *, real *, 
	    integer *, integer *, char *, complex *, integer *, complex *, 
	    integer *), cstein_(integer *, real *, 
	    real *, integer *, real *, integer *, integer *, complex *, 
	    integer *, real *, integer *, integer *, integer *), xerbla_(char 
	    *, integer *), sstech_(integer *, real *, real *, real *, 
	    real *, real *, integer *);
    integer indrwk;
    extern /* Subroutine */ int cpteqr_(char *, integer *, real *, real *, 
	    complex *, integer *, real *, integer *), cstemr_(char *, 
	    char *, integer *, real *, real *, real *, real *, integer *, 
	    integer *, integer *, real *, complex *, integer *, integer *, 
	    integer *, logical *, real *, integer *, integer *, integer *, 
	    integer *), csteqr_(char *, integer *, real *, 
	    real *, complex *, integer *, real *, integer *), cungtr_(
	    char *, integer *, complex *, integer *, complex *, complex *, 
	    integer *, integer *);
    logical tryrac;
    extern /* Subroutine */ int cupgtr_(char *, integer *, complex *, complex 
	    *, complex *, integer *, complex *, integer *), slasum_(
	    char *, integer *, integer *, integer *);
    integer nsplit;
    real rtunfl, rtovfl, ulpinv;
    integer mtypes, ntestt;
    extern /* Subroutine */ int sstebz_(char *, char *, integer *, real *, 
	    real *, integer *, integer *, real *, real *, real *, integer *, 
	    integer *, real *, integer *, integer *, real *, integer *, 
	    integer *), ssterf_(integer *, real *, real *, 
	    integer *);

    /* Fortran I/O blocks */
    static cilist io___42 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___53 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___58 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___67 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___68 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___73 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___74 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___75 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___78 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___79 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___80 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___81 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___82 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___83 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___84 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___85 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___86 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___87 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___88 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___89 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___90 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___91 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___92 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___93 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___94 = { 0, 0, 0, fmt_9987, 0 };
    static cilist io___95 = { 0, 0, 0, fmt_9989, 0 };
    static cilist io___96 = { 0, 0, 0, fmt_9988, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CCHKST  checks the Hermitian eigenvalue problem routines. */

/*     CHETRD factors A as  U S U* , where * means conjugate transpose, */
/*     S is real symmetric tridiagonal, and U is unitary. */
/*     CHETRD can use either just the lower or just the upper triangle */
/*     of A; CCHKST checks both cases. */
/*     U is represented as a product of Householder */
/*     transformations, whose vectors are stored in the first */
/*     n-1 columns of V, and whose scale factors are in TAU. */

/*     CHPTRD does the same as CHETRD, except that A and V are stored */
/*     in "packed" format. */

/*     CUNGTR constructs the matrix U from the contents of V and TAU. */

/*     CUPGTR constructs the matrix U from the contents of VP and TAU. */

/*     CSTEQR factors S as  Z D1 Z* , where Z is the unitary */
/*     matrix of eigenvectors and D1 is a diagonal matrix with */
/*     the eigenvalues on the diagonal.  D2 is the matrix of */
/*     eigenvalues computed when Z is not computed. */

/*     SSTERF computes D3, the matrix of eigenvalues, by the */
/*     PWK method, which does not yield eigenvectors. */

/*     CPTEQR factors S as  Z4 D4 Z4* , for a */
/*     Hermitian positive definite tridiagonal matrix. */
/*     D5 is the matrix of eigenvalues computed when Z is not */
/*     computed. */

/*     SSTEBZ computes selected eigenvalues.  WA1, WA2, and */
/*     WA3 will denote eigenvalues computed to high */
/*     absolute accuracy, with different range options. */
/*     WR will denote eigenvalues computed to high relative */
/*     accuracy. */

/*     CSTEIN computes Y, the eigenvectors of S, given the */
/*     eigenvalues. */

/*     CSTEDC factors S as Z D1 Z* , where Z is the unitary */
/*     matrix of eigenvectors and D1 is a diagonal matrix with */
/*     the eigenvalues on the diagonal ('I' option). It may also */
/*     update an input unitary matrix, usually the output */
/*     from CHETRD/CUNGTR or CHPTRD/CUPGTR ('V' option). It may */
/*     also just compute eigenvalues ('N' option). */

/*     CSTEMR factors S as Z D1 Z* , where Z is the unitary */
/*     matrix of eigenvectors and D1 is a diagonal matrix with */
/*     the eigenvalues on the diagonal ('I' option).  CSTEMR */
/*     uses the Relatively Robust Representation whenever possible. */

/*  When CCHKST is called, a number of matrix "sizes" ("n's") and a */
/*  number of matrix "types" are specified.  For each size ("n") */
/*  and each type of matrix, one matrix will be generated and used */
/*  to test the Hermitian eigenroutines.  For each matrix, a number */
/*  of tests will be performed: */

/*  (1)     | A - V S V* | / ( |A| n ulp ) CHETRD( UPLO='U', ... ) */

/*  (2)     | I - UV* | / ( n ulp )        CUNGTR( UPLO='U', ... ) */

/*  (3)     | A - V S V* | / ( |A| n ulp ) CHETRD( UPLO='L', ... ) */

/*  (4)     | I - UV* | / ( n ulp )        CUNGTR( UPLO='L', ... ) */

/*  (5-8)   Same as 1-4, but for CHPTRD and CUPGTR. */

/*  (9)     | S - Z D Z* | / ( |S| n ulp ) CSTEQR('V',...) */

/*  (10)    | I - ZZ* | / ( n ulp )        CSTEQR('V',...) */

/*  (11)    | D1 - D2 | / ( |D1| ulp )        CSTEQR('N',...) */

/*  (12)    | D1 - D3 | / ( |D1| ulp )        SSTERF */

/*  (13)    0 if the true eigenvalues (computed by sturm count) */
/*          of S are within THRESH of */
/*          those in D1.  2*THRESH if they are not.  (Tested using */
/*          SSTECH) */

/*  For S positive definite, */

/*  (14)    | S - Z4 D4 Z4* | / ( |S| n ulp ) CPTEQR('V',...) */

/*  (15)    | I - Z4 Z4* | / ( n ulp )        CPTEQR('V',...) */

/*  (16)    | D4 - D5 | / ( 100 |D4| ulp )       CPTEQR('N',...) */

/*  When S is also diagonally dominant by the factor gamma < 1, */

/*  (17)    max | D4(i) - WR(i) | / ( |D4(i)| omega ) , */
/*           i */
/*          omega = 2 (2n-1) ULP (1 + 8 gamma**2) / (1 - gamma)**4 */
/*                                               SSTEBZ( 'A', 'E', ...) */

/*  (18)    | WA1 - D3 | / ( |D3| ulp )          SSTEBZ( 'A', 'E', ...) */

/*  (19)    ( max { min | WA2(i)-WA3(j) | } + */
/*             i     j */
/*            max { min | WA3(i)-WA2(j) | } ) / ( |D3| ulp ) */
/*             i     j */
/*                                               SSTEBZ( 'I', 'E', ...) */

/*  (20)    | S - Y WA1 Y* | / ( |S| n ulp )  SSTEBZ, CSTEIN */

/*  (21)    | I - Y Y* | / ( n ulp )          SSTEBZ, CSTEIN */

/*  (22)    | S - Z D Z* | / ( |S| n ulp )    CSTEDC('I') */

/*  (23)    | I - ZZ* | / ( n ulp )           CSTEDC('I') */

/*  (24)    | S - Z D Z* | / ( |S| n ulp )    CSTEDC('V') */

/*  (25)    | I - ZZ* | / ( n ulp )           CSTEDC('V') */

/*  (26)    | D1 - D2 | / ( |D1| ulp )           CSTEDC('V') and */
/*                                               CSTEDC('N') */

/*  Test 27 is disabled at the moment because CSTEMR does not */
/*  guarantee high relatvie accuracy. */

/*  (27)    max | D6(i) - WR(i) | / ( |D6(i)| omega ) , */
/*           i */
/*          omega = 2 (2n-1) ULP (1 + 8 gamma**2) / (1 - gamma)**4 */
/*                                               CSTEMR('V', 'A') */

/*  (28)    max | D6(i) - WR(i) | / ( |D6(i)| omega ) , */
/*           i */
/*          omega = 2 (2n-1) ULP (1 + 8 gamma**2) / (1 - gamma)**4 */
/*                                               CSTEMR('V', 'I') */

/*  Tests 29 through 34 are disable at present because CSTEMR */
/*  does not handle partial specturm requests. */

/*  (29)    | S - Z D Z* | / ( |S| n ulp )    CSTEMR('V', 'I') */

/*  (30)    | I - ZZ* | / ( n ulp )           CSTEMR('V', 'I') */

/*  (31)    ( max { min | WA2(i)-WA3(j) | } + */
/*             i     j */
/*            max { min | WA3(i)-WA2(j) | } ) / ( |D3| ulp ) */
/*             i     j */
/*          CSTEMR('N', 'I') vs. CSTEMR('V', 'I') */

/*  (32)    | S - Z D Z* | / ( |S| n ulp )    CSTEMR('V', 'V') */

/*  (33)    | I - ZZ* | / ( n ulp )           CSTEMR('V', 'V') */

/*  (34)    ( max { min | WA2(i)-WA3(j) | } + */
/*             i     j */
/*            max { min | WA3(i)-WA2(j) | } ) / ( |D3| ulp ) */
/*             i     j */
/*          CSTEMR('N', 'V') vs. CSTEMR('V', 'V') */

/*  (35)    | S - Z D Z* | / ( |S| n ulp )    CSTEMR('V', 'A') */

/*  (36)    | I - ZZ* | / ( n ulp )           CSTEMR('V', 'A') */

/*  (37)    ( max { min | WA2(i)-WA3(j) | } + */
/*             i     j */
/*            max { min | WA3(i)-WA2(j) | } ) / ( |D3| ulp ) */
/*             i     j */
/*          CSTEMR('N', 'A') vs. CSTEMR('V', 'A') */

/*  The "sizes" are specified by an array NN(1:NSIZES); the value of */
/*  each element NN(j) specifies one size. */
/*  The "types" are specified by a logical array DOTYPE( 1:NTYPES ); */
/*  if DOTYPE(j) is .TRUE., then matrix type "j" will be generated. */
/*  Currently, the list of possible types is: */

/*  (1)  The zero matrix. */
/*  (2)  The identity matrix. */

/*  (3)  A diagonal matrix with evenly spaced entries */
/*       1, ..., ULP  and random signs. */
/*       (ULP = (first number larger than 1) - 1 ) */
/*  (4)  A diagonal matrix with geometrically spaced entries */
/*       1, ..., ULP  and random signs. */
/*  (5)  A diagonal matrix with "clustered" entries 1, ULP, ..., ULP */
/*       and random signs. */

/*  (6)  Same as (4), but multiplied by SQRT( overflow threshold ) */
/*  (7)  Same as (4), but multiplied by SQRT( underflow threshold ) */

/*  (8)  A matrix of the form  U* D U, where U is unitary and */
/*       D has evenly spaced entries 1, ..., ULP with random signs */
/*       on the diagonal. */

/*  (9)  A matrix of the form  U* D U, where U is unitary and */
/*       D has geometrically spaced entries 1, ..., ULP with random */
/*       signs on the diagonal. */

/*  (10) A matrix of the form  U* D U, where U is unitary and */
/*       D has "clustered" entries 1, ULP,..., ULP with random */
/*       signs on the diagonal. */

/*  (11) Same as (8), but multiplied by SQRT( overflow threshold ) */
/*  (12) Same as (8), but multiplied by SQRT( underflow threshold ) */

/*  (13) Hermitian matrix with random entries chosen from (-1,1). */
/*  (14) Same as (13), but multiplied by SQRT( overflow threshold ) */
/*  (15) Same as (13), but multiplied by SQRT( underflow threshold ) */
/*  (16) Same as (8), but diagonal elements are all positive. */
/*  (17) Same as (9), but diagonal elements are all positive. */
/*  (18) Same as (10), but diagonal elements are all positive. */
/*  (19) Same as (16), but multiplied by SQRT( overflow threshold ) */
/*  (20) Same as (16), but multiplied by SQRT( underflow threshold ) */
/*  (21) A diagonally dominant tridiagonal matrix with geometrically */
/*       spaced diagonal entries 1, ..., ULP. */

/*  Arguments */
/*  ========= */

/*  NSIZES  (input) INTEGER */
/*          The number of sizes of matrices to use.  If it is zero, */
/*          CCHKST does nothing.  It must be at least zero. */

/*  NN      (input) INTEGER array, dimension (NSIZES) */
/*          An array containing the sizes to be used for the matrices. */
/*          Zero values will be skipped.  The values must be at least */
/*          zero. */

/*  NTYPES  (input) INTEGER */
/*          The number of elements in DOTYPE.   If it is zero, CCHKST */
/*          does nothing.  It must be at least zero.  If it is MAXTYP+1 */
/*          and NSIZES is 1, then an additional type, MAXTYP+1 is */
/*          defined, which is to use whatever matrix is in A.  This */
/*          is only useful if DOTYPE(1:MAXTYP) is .FALSE. and */
/*          DOTYPE(MAXTYP+1) is .TRUE. . */

/*  DOTYPE  (input) LOGICAL array, dimension (NTYPES) */
/*          If DOTYPE(j) is .TRUE., then for each size in NN a */
/*          matrix of that size and of type j will be generated. */
/*          If NTYPES is smaller than the maximum number of types */
/*          defined (PARAMETER MAXTYP), then types NTYPES+1 through */
/*          MAXTYP will not be generated.  If NTYPES is larger */
/*          than MAXTYP, DOTYPE(MAXTYP+1) through DOTYPE(NTYPES) */
/*          will be ignored. */

/*  ISEED   (input/output) INTEGER array, dimension (4) */
/*          On entry ISEED specifies the seed of the random number */
/*          generator. The array elements should be between 0 and 4095; */
/*          if not they will be reduced mod 4096.  Also, ISEED(4) must */
/*          be odd.  The random number generator uses a linear */
/*          congruential sequence limited to small integers, and so */
/*          should produce machine independent random numbers. The */
/*          values of ISEED are changed on exit, and can be used in the */
/*          next call to CCHKST to continue the same random number */
/*          sequence. */

/*  THRESH  (input) REAL */
/*          A test will count as "failed" if the "error", computed as */
/*          described above, exceeds THRESH.  Note that the error */
/*          is scaled to be O(1), so THRESH should be a reasonably */
/*          small multiple of 1, e.g., 10 or 100.  In particular, */
/*          it should not depend on the precision (single vs. double) */
/*          or the size of the matrix.  It must be at least zero. */

/*  NOUNIT  (input) INTEGER */
/*          The FORTRAN unit number for printing out error messages */
/*          (e.g., if a routine returns IINFO not equal to 0.) */

/*  A       (input/workspace/output) COMPLEX array of */
/*                                  dimension ( LDA , max(NN) ) */
/*          Used to hold the matrix whose eigenvalues are to be */
/*          computed.  On exit, A contains the last matrix actually */
/*          used. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of A.  It must be at */
/*          least 1 and at least max( NN ). */

/*  AP      (workspace) COMPLEX array of */
/*                      dimension( max(NN)*max(NN+1)/2 ) */
/*          The matrix A stored in packed format. */

/*  SD      (workspace/output) REAL array of */
/*                             dimension( max(NN) ) */
/*          The diagonal of the tridiagonal matrix computed by CHETRD. */
/*          On exit, SD and SE contain the tridiagonal form of the */
/*          matrix in A. */

/*  SE      (workspace/output) REAL array of */
/*                             dimension( max(NN) ) */
/*          The off-diagonal of the tridiagonal matrix computed by */
/*          CHETRD.  On exit, SD and SE contain the tridiagonal form of */
/*          the matrix in A. */

/*  D1      (workspace/output) REAL array of */
/*                             dimension( max(NN) ) */
/*          The eigenvalues of A, as computed by CSTEQR simlutaneously */
/*          with Z.  On exit, the eigenvalues in D1 correspond with the */
/*          matrix in A. */

/*  D2      (workspace/output) REAL array of */
/*                             dimension( max(NN) ) */
/*          The eigenvalues of A, as computed by CSTEQR if Z is not */
/*          computed.  On exit, the eigenvalues in D2 correspond with */
/*          the matrix in A. */

/*  D3      (workspace/output) REAL array of */
/*                             dimension( max(NN) ) */
/*          The eigenvalues of A, as computed by SSTERF.  On exit, the */
/*          eigenvalues in D3 correspond with the matrix in A. */

/*  U       (workspace/output) COMPLEX array of */
/*                             dimension( LDU, max(NN) ). */
/*          The unitary matrix computed by CHETRD + CUNGTR. */

/*  LDU     (input) INTEGER */
/*          The leading dimension of U, Z, and V.  It must be at least 1 */
/*          and at least max( NN ). */

/*  V       (workspace/output) COMPLEX array of */
/*                             dimension( LDU, max(NN) ). */
/*          The Housholder vectors computed by CHETRD in reducing A to */
/*          tridiagonal form.  The vectors computed with UPLO='U' are */
/*          in the upper triangle, and the vectors computed with UPLO='L' */
/*          are in the lower triangle.  (As described in CHETRD, the */
/*          sub- and superdiagonal are not set to 1, although the */
/*          true Householder vector has a 1 in that position.  The */
/*          routines that use V, such as CUNGTR, set those entries to */
/*          1 before using them, and then restore them later.) */

/*  VP      (workspace) COMPLEX array of */
/*                      dimension( max(NN)*max(NN+1)/2 ) */
/*          The matrix V stored in packed format. */

/*  TAU     (workspace/output) COMPLEX array of */
/*                             dimension( max(NN) ) */
/*          The Householder factors computed by CHETRD in reducing A */
/*          to tridiagonal form. */

/*  Z       (workspace/output) COMPLEX array of */
/*                             dimension( LDU, max(NN) ). */
/*          The unitary matrix of eigenvectors computed by CSTEQR, */
/*          CPTEQR, and CSTEIN. */

/*  WORK    (workspace/output) COMPLEX array of */
/*                      dimension( LWORK ) */

/*  LWORK   (input) INTEGER */
/*          The number of entries in WORK.  This must be at least */
/*          1 + 4 * Nmax + 2 * Nmax * lg Nmax + 3 * Nmax**2 */
/*          where Nmax = max( NN(j), 2 ) and lg = log base 2. */

/*  IWORK   (workspace/output) INTEGER array, */
/*             dimension (6 + 6*Nmax + 5 * Nmax * lg Nmax ) */
/*          where Nmax = max( NN(j), 2 ) and lg = log base 2. */
/*          Workspace. */

/*  RWORK   (workspace/output) REAL array of */
/*                      dimension( ??? ) */

/*  RESULT  (output) REAL array, dimension (26) */
/*          The values computed by the tests described above. */
/*          The values are currently limited to 1/ulp, to avoid */
/*          overflow. */

/*  INFO    (output) INTEGER */
/*          If 0, then everything ran OK. */
/*           -1: NSIZES < 0 */
/*           -2: Some NN(j) < 0 */
/*           -3: NTYPES < 0 */
/*           -5: THRESH < 0 */
/*           -9: LDA < 1 or LDA < NMAX, where NMAX is max( NN(j) ). */
/*          -23: LDU < 1 or LDU < NMAX. */
/*          -29: LWORK too small. */
/*          If  CLATMR, CLATMS, CHETRD, CUNGTR, CSTEQR, SSTERF, */
/*              or CUNMC2 returns an error code, the */
/*              absolute value of it is returned. */

/* ----------------------------------------------------------------------- */

/*       Some Local Variables and Parameters: */
/*       ---- ----- --------- --- ---------- */
/*       ZERO, ONE       Real 0 and 1. */
/*       MAXTYP          The number of types defined. */
/*       NTEST           The number of tests performed, or which can */
/*                       be performed so far, for the current matrix. */
/*       NTESTT          The total number of tests performed so far. */
/*       NBLOCK          Blocksize as returned by ENVIR. */
/*       NMAX            Largest value in NN. */
/*       NMATS           The number of matrices generated so far. */
/*       NERRS           The number of tests which have exceeded THRESH */
/*                       so far. */
/*       COND, IMODE     Values to be passed to the matrix generators. */
/*       ANORM           Norm of A; passed to matrix generators. */

/*       OVFL, UNFL      Overflow and underflow thresholds. */
/*       ULP, ULPINV     Finest relative precision and its inverse. */
/*       RTOVFL, RTUNFL  Square roots of the previous 2 values. */
/*               The following four arrays decode JTYPE: */
/*       KTYPE(j)        The general type (1-10) for type "j". */
/*       KMODE(j)        The MODE value to be passed to the matrix */
/*                       generator for type "j". */
/*       KMAGN(j)        The order of magnitude ( O(1), */
/*                       O(overflow^(1/2) ), O(underflow^(1/2) ) */

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
/*     .. Data statements .. */
    /* Parameter adjustments */
    --nn;
    --dotype;
    --iseed;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ap;
    --sd;
    --se;
    --d1;
    --d2;
    --d3;
    --d4;
    --d5;
    --wa1;
    --wa2;
    --wa3;
    --wr;
    z_dim1 = *ldu;
    z_offset = 1 + z_dim1;
    z__ -= z_offset;
    v_dim1 = *ldu;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    --vp;
    --tau;
    --work;
    --rwork;
    --iwork;
    --result;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

/*     Keep ftnchek happy */
    idumma[0] = 1;

/*     Check for errors */

    ntestt = 0;
    *info = 0;

/*     Important constants */

    badnn = FALSE_;
    tryrac = TRUE_;
    nmax = 1;
    i__1 = *nsizes;
    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = nmax, i__3 = nn[j];
	nmax = max(i__2,i__3);
	if (nn[j] < 0) {
	    badnn = TRUE_;
	}
/* L10: */
    }

    nblock = ilaenv_(&c__1, "CHETRD", "L", &nmax, &c_n1, &c_n1, &c_n1);
/* Computing MIN */
    i__1 = nmax, i__2 = max(1,nblock);
    nblock = min(i__1,i__2);

/*     Check for errors */

    if (*nsizes < 0) {
	*info = -1;
    } else if (badnn) {
	*info = -2;
    } else if (*ntypes < 0) {
	*info = -3;
    } else if (*lda < nmax) {
	*info = -9;
    } else if (*ldu < nmax) {
	*info = -23;
    } else /* if(complicated condition) */ {
/* Computing 2nd power */
	i__1 = max(2,nmax);
	if (i__1 * i__1 << 1 > *lwork) {
	    *info = -29;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CCHKST", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*nsizes == 0 || *ntypes == 0) {
	return 0;
    }

/*     More Important constants */

    unfl = slamch_("Safe minimum");
    ovfl = 1.f / unfl;
    slabad_(&unfl, &ovfl);
    ulp = slamch_("Epsilon") * slamch_("Base");
    ulpinv = 1.f / ulp;
    log2ui = (integer) (log(ulpinv) / log(2.f));
    rtunfl = sqrt(unfl);
    rtovfl = sqrt(ovfl);

/*     Loop over sizes, types */

    for (i__ = 1; i__ <= 4; ++i__) {
	iseed2[i__ - 1] = iseed[i__];
/* L20: */
    }
    nerrs = 0;
    nmats = 0;

    i__1 = *nsizes;
    for (jsize = 1; jsize <= i__1; ++jsize) {
	n = nn[jsize];
	if (n > 0) {
	    lgn = (integer) (log((real) n) / log(2.f));
	    if (pow_ii(&c__2, &lgn) < n) {
		++lgn;
	    }
	    if (pow_ii(&c__2, &lgn) < n) {
		++lgn;
	    }
/* Computing 2nd power */
	    i__2 = n;
	    lwedc = (n << 2) + 1 + (n << 1) * lgn + i__2 * i__2 * 3;
/* Computing 2nd power */
	    i__2 = n;
	    lrwedc = n * 3 + 1 + (n << 1) * lgn + i__2 * i__2 * 3;
	    liwedc = n * 6 + 6 + n * 5 * lgn;
	} else {
	    lwedc = 8;
	    lrwedc = 7;
	    liwedc = 12;
	}
	nap = n * (n + 1) / 2;
	aninv = 1.f / (real) max(1,n);

	if (*nsizes != 1) {
	    mtypes = min(21,*ntypes);
	} else {
	    mtypes = min(22,*ntypes);
	}

	i__2 = mtypes;
	for (jtype = 1; jtype <= i__2; ++jtype) {
	    if (! dotype[jtype]) {
		goto L300;
	    }
	    ++nmats;
	    ntest = 0;

	    for (j = 1; j <= 4; ++j) {
		ioldsd[j - 1] = iseed[j];
/* L30: */
	    }

/*           Compute "A" */

/*           Control parameters: */

/*               KMAGN  KMODE        KTYPE */
/*           =1  O(1)   clustered 1  zero */
/*           =2  large  clustered 2  identity */
/*           =3  small  exponential  (none) */
/*           =4         arithmetic   diagonal, (w/ eigenvalues) */
/*           =5         random log   Hermitian, w/ eigenvalues */
/*           =6         random       (none) */
/*           =7                      random diagonal */
/*           =8                      random Hermitian */
/*           =9                      positive definite */
/*           =10                     diagonally dominant tridiagonal */

	    if (mtypes > 21) {
		goto L100;
	    }

	    itype = ktype[jtype - 1];
	    imode = kmode[jtype - 1];

/*           Compute norm */

	    switch (kmagn[jtype - 1]) {
		case 1:  goto L40;
		case 2:  goto L50;
		case 3:  goto L60;
	    }

L40:
	    anorm = 1.f;
	    goto L70;

L50:
	    anorm = rtovfl * ulp * aninv;
	    goto L70;

L60:
	    anorm = rtunfl * n * ulpinv;
	    goto L70;

L70:

	    claset_("Full", lda, &n, &c_b1, &c_b1, &a[a_offset], lda);
	    iinfo = 0;
	    if (jtype <= 15) {
		cond = ulpinv;
	    } else {
		cond = ulpinv * aninv / 10.f;
	    }

/*           Special Matrices -- Identity & Jordan block */

/*              Zero */

	    if (itype == 1) {
		iinfo = 0;

	    } else if (itype == 2) {

/*              Identity */

		i__3 = n;
		for (jc = 1; jc <= i__3; ++jc) {
		    i__4 = jc + jc * a_dim1;
		    a[i__4].r = anorm, a[i__4].i = 0.f;
/* L80: */
		}

	    } else if (itype == 4) {

/*              Diagonal Matrix, [Eigen]values Specified */

		clatms_(&n, &n, "S", &iseed[1], "H", &rwork[1], &imode, &cond, 
			 &anorm, &c__0, &c__0, "N", &a[a_offset], lda, &work[
			1], &iinfo);


	    } else if (itype == 5) {

/*              Hermitian, eigenvalues specified */

		clatms_(&n, &n, "S", &iseed[1], "H", &rwork[1], &imode, &cond, 
			 &anorm, &n, &n, "N", &a[a_offset], lda, &work[1], &
			iinfo);

	    } else if (itype == 7) {

/*              Diagonal, random eigenvalues */

		clatmr_(&n, &n, "S", &iseed[1], "H", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &c__0, &
			c__0, &c_b49, &anorm, "NO", &a[a_offset], lda, &iwork[
			1], &iinfo);

	    } else if (itype == 8) {

/*              Hermitian, random eigenvalues */

		clatmr_(&n, &n, "S", &iseed[1], "H", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &n, &n, &
			c_b49, &anorm, "NO", &a[a_offset], lda, &iwork[1], &
			iinfo);

	    } else if (itype == 9) {

/*              Positive definite, eigenvalues specified. */

		clatms_(&n, &n, "S", &iseed[1], "P", &rwork[1], &imode, &cond, 
			 &anorm, &n, &n, "N", &a[a_offset], lda, &work[1], &
			iinfo);

	    } else if (itype == 10) {

/*              Positive definite tridiagonal, eigenvalues specified. */

		clatms_(&n, &n, "S", &iseed[1], "P", &rwork[1], &imode, &cond, 
			 &anorm, &c__1, &c__1, "N", &a[a_offset], lda, &work[
			1], &iinfo);
		i__3 = n;
		for (i__ = 2; i__ <= i__3; ++i__) {
		    temp1 = c_abs(&a[i__ - 1 + i__ * a_dim1]);
		    i__4 = i__ - 1 + (i__ - 1) * a_dim1;
		    i__5 = i__ + i__ * a_dim1;
		    q__1.r = a[i__4].r * a[i__5].r - a[i__4].i * a[i__5].i, 
			    q__1.i = a[i__4].r * a[i__5].i + a[i__4].i * a[
			    i__5].r;
		    temp2 = sqrt(c_abs(&q__1));
		    if (temp1 > temp2 * .5f) {
			i__4 = i__ - 1 + i__ * a_dim1;
			i__5 = i__ - 1 + i__ * a_dim1;
			r__1 = temp2 * .5f / (unfl + temp1);
			q__1.r = r__1 * a[i__5].r, q__1.i = r__1 * a[i__5].i;
			a[i__4].r = q__1.r, a[i__4].i = q__1.i;
			i__4 = i__ + (i__ - 1) * a_dim1;
			r_cnjg(&q__1, &a[i__ - 1 + i__ * a_dim1]);
			a[i__4].r = q__1.r, a[i__4].i = q__1.i;
		    }
/* L90: */
		}

	    } else {

		iinfo = 1;
	    }

	    if (iinfo != 0) {
		io___42.ciunit = *nounit;
		s_wsfe(&io___42);
		do_fio(&c__1, "Generator", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		return 0;
	    }

L100:

/*           Call CHETRD and CUNGTR to compute S and U from */
/*           upper triangle. */

	    clacpy_("U", &n, &n, &a[a_offset], lda, &v[v_offset], ldu);

	    ntest = 1;
	    chetrd_("U", &n, &v[v_offset], ldu, &sd[1], &se[1], &tau[1], &
		    work[1], lwork, &iinfo);

	    if (iinfo != 0) {
		io___43.ciunit = *nounit;
		s_wsfe(&io___43);
		do_fio(&c__1, "CHETRD(U)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[1] = ulpinv;
		    goto L280;
		}
	    }

	    clacpy_("U", &n, &n, &v[v_offset], ldu, &u[u_offset], ldu);

	    ntest = 2;
	    cungtr_("U", &n, &u[u_offset], ldu, &tau[1], &work[1], lwork, &
		    iinfo);
	    if (iinfo != 0) {
		io___44.ciunit = *nounit;
		s_wsfe(&io___44);
		do_fio(&c__1, "CUNGTR(U)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[2] = ulpinv;
		    goto L280;
		}
	    }

/*           Do tests 1 and 2 */

	    chet21_(&c__2, "Upper", &n, &c__1, &a[a_offset], lda, &sd[1], &se[
		    1], &u[u_offset], ldu, &v[v_offset], ldu, &tau[1], &work[
		    1], &rwork[1], &result[1]);
	    chet21_(&c__3, "Upper", &n, &c__1, &a[a_offset], lda, &sd[1], &se[
		    1], &u[u_offset], ldu, &v[v_offset], ldu, &tau[1], &work[
		    1], &rwork[1], &result[2]);

/*           Call CHETRD and CUNGTR to compute S and U from */
/*           lower triangle, do tests. */

	    clacpy_("L", &n, &n, &a[a_offset], lda, &v[v_offset], ldu);

	    ntest = 3;
	    chetrd_("L", &n, &v[v_offset], ldu, &sd[1], &se[1], &tau[1], &
		    work[1], lwork, &iinfo);

	    if (iinfo != 0) {
		io___45.ciunit = *nounit;
		s_wsfe(&io___45);
		do_fio(&c__1, "CHETRD(L)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[3] = ulpinv;
		    goto L280;
		}
	    }

	    clacpy_("L", &n, &n, &v[v_offset], ldu, &u[u_offset], ldu);

	    ntest = 4;
	    cungtr_("L", &n, &u[u_offset], ldu, &tau[1], &work[1], lwork, &
		    iinfo);
	    if (iinfo != 0) {
		io___46.ciunit = *nounit;
		s_wsfe(&io___46);
		do_fio(&c__1, "CUNGTR(L)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[4] = ulpinv;
		    goto L280;
		}
	    }

	    chet21_(&c__2, "Lower", &n, &c__1, &a[a_offset], lda, &sd[1], &se[
		    1], &u[u_offset], ldu, &v[v_offset], ldu, &tau[1], &work[
		    1], &rwork[1], &result[3]);
	    chet21_(&c__3, "Lower", &n, &c__1, &a[a_offset], lda, &sd[1], &se[
		    1], &u[u_offset], ldu, &v[v_offset], ldu, &tau[1], &work[
		    1], &rwork[1], &result[4]);

/*           Store the upper triangle of A in AP */

	    i__ = 0;
	    i__3 = n;
	    for (jc = 1; jc <= i__3; ++jc) {
		i__4 = jc;
		for (jr = 1; jr <= i__4; ++jr) {
		    ++i__;
		    i__5 = i__;
		    i__6 = jr + jc * a_dim1;
		    ap[i__5].r = a[i__6].r, ap[i__5].i = a[i__6].i;
/* L110: */
		}
/* L120: */
	    }

/*           Call CHPTRD and CUPGTR to compute S and U from AP */

	    ccopy_(&nap, &ap[1], &c__1, &vp[1], &c__1);

	    ntest = 5;
	    chptrd_("U", &n, &vp[1], &sd[1], &se[1], &tau[1], &iinfo);

	    if (iinfo != 0) {
		io___48.ciunit = *nounit;
		s_wsfe(&io___48);
		do_fio(&c__1, "CHPTRD(U)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[5] = ulpinv;
		    goto L280;
		}
	    }

	    ntest = 6;
	    cupgtr_("U", &n, &vp[1], &tau[1], &u[u_offset], ldu, &work[1], &
		    iinfo);
	    if (iinfo != 0) {
		io___49.ciunit = *nounit;
		s_wsfe(&io___49);
		do_fio(&c__1, "CUPGTR(U)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[6] = ulpinv;
		    goto L280;
		}
	    }

/*           Do tests 5 and 6 */

	    chpt21_(&c__2, "Upper", &n, &c__1, &ap[1], &sd[1], &se[1], &u[
		    u_offset], ldu, &vp[1], &tau[1], &work[1], &rwork[1], &
		    result[5]);
	    chpt21_(&c__3, "Upper", &n, &c__1, &ap[1], &sd[1], &se[1], &u[
		    u_offset], ldu, &vp[1], &tau[1], &work[1], &rwork[1], &
		    result[6]);

/*           Store the lower triangle of A in AP */

	    i__ = 0;
	    i__3 = n;
	    for (jc = 1; jc <= i__3; ++jc) {
		i__4 = n;
		for (jr = jc; jr <= i__4; ++jr) {
		    ++i__;
		    i__5 = i__;
		    i__6 = jr + jc * a_dim1;
		    ap[i__5].r = a[i__6].r, ap[i__5].i = a[i__6].i;
/* L130: */
		}
/* L140: */
	    }

/*           Call CHPTRD and CUPGTR to compute S and U from AP */

	    ccopy_(&nap, &ap[1], &c__1, &vp[1], &c__1);

	    ntest = 7;
	    chptrd_("L", &n, &vp[1], &sd[1], &se[1], &tau[1], &iinfo);

	    if (iinfo != 0) {
		io___50.ciunit = *nounit;
		s_wsfe(&io___50);
		do_fio(&c__1, "CHPTRD(L)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[7] = ulpinv;
		    goto L280;
		}
	    }

	    ntest = 8;
	    cupgtr_("L", &n, &vp[1], &tau[1], &u[u_offset], ldu, &work[1], &
		    iinfo);
	    if (iinfo != 0) {
		io___51.ciunit = *nounit;
		s_wsfe(&io___51);
		do_fio(&c__1, "CUPGTR(L)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[8] = ulpinv;
		    goto L280;
		}
	    }

	    chpt21_(&c__2, "Lower", &n, &c__1, &ap[1], &sd[1], &se[1], &u[
		    u_offset], ldu, &vp[1], &tau[1], &work[1], &rwork[1], &
		    result[7]);
	    chpt21_(&c__3, "Lower", &n, &c__1, &ap[1], &sd[1], &se[1], &u[
		    u_offset], ldu, &vp[1], &tau[1], &work[1], &rwork[1], &
		    result[8]);

/*           Call CSTEQR to compute D1, D2, and Z, do tests. */

/*           Compute D1 and Z */

	    scopy_(&n, &sd[1], &c__1, &d1[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
	    }
	    claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

	    ntest = 9;
	    csteqr_("V", &n, &d1[1], &rwork[1], &z__[z_offset], ldu, &rwork[n 
		    + 1], &iinfo);
	    if (iinfo != 0) {
		io___52.ciunit = *nounit;
		s_wsfe(&io___52);
		do_fio(&c__1, "CSTEQR(V)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[9] = ulpinv;
		    goto L280;
		}
	    }

/*           Compute D2 */

	    scopy_(&n, &sd[1], &c__1, &d2[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
	    }

	    ntest = 11;
	    csteqr_("N", &n, &d2[1], &rwork[1], &work[1], ldu, &rwork[n + 1], 
		    &iinfo);
	    if (iinfo != 0) {
		io___53.ciunit = *nounit;
		s_wsfe(&io___53);
		do_fio(&c__1, "CSTEQR(N)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[11] = ulpinv;
		    goto L280;
		}
	    }

/*           Compute D3 (using PWK method) */

	    scopy_(&n, &sd[1], &c__1, &d3[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
	    }

	    ntest = 12;
	    ssterf_(&n, &d3[1], &rwork[1], &iinfo);
	    if (iinfo != 0) {
		io___54.ciunit = *nounit;
		s_wsfe(&io___54);
		do_fio(&c__1, "SSTERF", (ftnlen)6);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[12] = ulpinv;
		    goto L280;
		}
	    }

/*           Do Tests 9 and 10 */

	    cstt21_(&n, &c__0, &sd[1], &se[1], &d1[1], dumma, &z__[z_offset], 
		    ldu, &work[1], &rwork[1], &result[9]);

/*           Do Tests 11 and 12 */

	    temp1 = 0.f;
	    temp2 = 0.f;
	    temp3 = 0.f;
	    temp4 = 0.f;

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		r__3 = temp1, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 = max(
			r__3,r__4), r__4 = (r__2 = d2[j], dabs(r__2));
		temp1 = dmax(r__3,r__4);
/* Computing MAX */
		r__2 = temp2, r__3 = (r__1 = d1[j] - d2[j], dabs(r__1));
		temp2 = dmax(r__2,r__3);
/* Computing MAX */
		r__3 = temp3, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 = max(
			r__3,r__4), r__4 = (r__2 = d3[j], dabs(r__2));
		temp3 = dmax(r__3,r__4);
/* Computing MAX */
		r__2 = temp4, r__3 = (r__1 = d1[j] - d3[j], dabs(r__1));
		temp4 = dmax(r__2,r__3);
/* L150: */
	    }

/* Computing MAX */
	    r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
	    result[11] = temp2 / dmax(r__1,r__2);
/* Computing MAX */
	    r__1 = unfl, r__2 = ulp * dmax(temp3,temp4);
	    result[12] = temp4 / dmax(r__1,r__2);

/*           Do Test 13 -- Sturm Sequence Test of Eigenvalues */
/*                         Go up by factors of two until it succeeds */

	    ntest = 13;
	    temp1 = *thresh * (.5f - ulp);

	    i__3 = log2ui;
	    for (j = 0; j <= i__3; ++j) {
		sstech_(&n, &sd[1], &se[1], &d1[1], &temp1, &rwork[1], &iinfo)
			;
		if (iinfo == 0) {
		    goto L170;
		}
		temp1 *= 2.f;
/* L160: */
	    }

L170:
	    result[13] = temp1;

/*           For positive definite matrices ( JTYPE.GT.15 ) call CPTEQR */
/*           and do tests 14, 15, and 16 . */

	    if (jtype > 15) {

/*              Compute D4 and Z4 */

		scopy_(&n, &sd[1], &c__1, &d4[1], &c__1);
		if (n > 0) {
		    i__3 = n - 1;
		    scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		}
		claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

		ntest = 14;
		cpteqr_("V", &n, &d4[1], &rwork[1], &z__[z_offset], ldu, &
			rwork[n + 1], &iinfo);
		if (iinfo != 0) {
		    io___58.ciunit = *nounit;
		    s_wsfe(&io___58);
		    do_fio(&c__1, "CPTEQR(V)", (ftnlen)9);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[14] = ulpinv;
			goto L280;
		    }
		}

/*              Do Tests 14 and 15 */

		cstt21_(&n, &c__0, &sd[1], &se[1], &d4[1], dumma, &z__[
			z_offset], ldu, &work[1], &rwork[1], &result[14]);

/*              Compute D5 */

		scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		if (n > 0) {
		    i__3 = n - 1;
		    scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		}

		ntest = 16;
		cpteqr_("N", &n, &d5[1], &rwork[1], &z__[z_offset], ldu, &
			rwork[n + 1], &iinfo);
		if (iinfo != 0) {
		    io___59.ciunit = *nounit;
		    s_wsfe(&io___59);
		    do_fio(&c__1, "CPTEQR(N)", (ftnlen)9);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[16] = ulpinv;
			goto L280;
		    }
		}

/*              Do Test 16 */

		temp1 = 0.f;
		temp2 = 0.f;
		i__3 = n;
		for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		    r__3 = temp1, r__4 = (r__1 = d4[j], dabs(r__1)), r__3 = 
			    max(r__3,r__4), r__4 = (r__2 = d5[j], dabs(r__2));
		    temp1 = dmax(r__3,r__4);
/* Computing MAX */
		    r__2 = temp2, r__3 = (r__1 = d4[j] - d5[j], dabs(r__1));
		    temp2 = dmax(r__2,r__3);
/* L180: */
		}

/* Computing MAX */
		r__1 = unfl, r__2 = ulp * 100.f * dmax(temp1,temp2);
		result[16] = temp2 / dmax(r__1,r__2);
	    } else {
		result[14] = 0.f;
		result[15] = 0.f;
		result[16] = 0.f;
	    }

/*           Call SSTEBZ with different options and do tests 17-18. */

/*              If S is positive definite and diagonally dominant, */
/*              ask for all eigenvalues with high relative accuracy. */

	    vl = 0.f;
	    vu = 0.f;
	    il = 0;
	    iu = 0;
	    if (jtype == 21) {
		ntest = 17;
		abstol = unfl + unfl;
		sstebz_("A", "E", &n, &vl, &vu, &il, &iu, &abstol, &sd[1], &
			se[1], &m, &nsplit, &wr[1], &iwork[1], &iwork[n + 1], 
			&rwork[1], &iwork[(n << 1) + 1], &iinfo);
		if (iinfo != 0) {
		    io___67.ciunit = *nounit;
		    s_wsfe(&io___67);
		    do_fio(&c__1, "SSTEBZ(A,rel)", (ftnlen)13);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[17] = ulpinv;
			goto L280;
		    }
		}

/*              Do test 17 */

		temp2 = (n * 2.f - 1.f) * 2.f * ulp * 3.f / .0625f;

		temp1 = 0.f;
		i__3 = n;
		for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		    r__3 = temp1, r__4 = (r__2 = d4[j] - wr[n - j + 1], dabs(
			    r__2)) / (abstol + (r__1 = d4[j], dabs(r__1)));
		    temp1 = dmax(r__3,r__4);
/* L190: */
		}

		result[17] = temp1 / temp2;
	    } else {
		result[17] = 0.f;
	    }

/*           Now ask for all eigenvalues with high absolute accuracy. */

	    ntest = 18;
	    abstol = unfl + unfl;
	    sstebz_("A", "E", &n, &vl, &vu, &il, &iu, &abstol, &sd[1], &se[1], 
		     &m, &nsplit, &wa1[1], &iwork[1], &iwork[n + 1], &rwork[1]
, &iwork[(n << 1) + 1], &iinfo);
	    if (iinfo != 0) {
		io___68.ciunit = *nounit;
		s_wsfe(&io___68);
		do_fio(&c__1, "SSTEBZ(A)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[18] = ulpinv;
		    goto L280;
		}
	    }

/*           Do test 18 */

	    temp1 = 0.f;
	    temp2 = 0.f;
	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		r__3 = temp1, r__4 = (r__1 = d3[j], dabs(r__1)), r__3 = max(
			r__3,r__4), r__4 = (r__2 = wa1[j], dabs(r__2));
		temp1 = dmax(r__3,r__4);
/* Computing MAX */
		r__2 = temp2, r__3 = (r__1 = d3[j] - wa1[j], dabs(r__1));
		temp2 = dmax(r__2,r__3);
/* L200: */
	    }

/* Computing MAX */
	    r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
	    result[18] = temp2 / dmax(r__1,r__2);

/*           Choose random values for IL and IU, and ask for the */
/*           IL-th through IU-th eigenvalues. */

	    ntest = 19;
	    if (n <= 1) {
		il = 1;
		iu = n;
	    } else {
		il = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		iu = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		if (iu < il) {
		    itemp = iu;
		    iu = il;
		    il = itemp;
		}
	    }

	    sstebz_("I", "E", &n, &vl, &vu, &il, &iu, &abstol, &sd[1], &se[1], 
		     &m2, &nsplit, &wa2[1], &iwork[1], &iwork[n + 1], &rwork[
		    1], &iwork[(n << 1) + 1], &iinfo);
	    if (iinfo != 0) {
		io___71.ciunit = *nounit;
		s_wsfe(&io___71);
		do_fio(&c__1, "SSTEBZ(I)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[19] = ulpinv;
		    goto L280;
		}
	    }

/*           Determine the values VL and VU of the IL-th and IU-th */
/*           eigenvalues and ask for all eigenvalues in this range. */

	    if (n > 0) {
		if (il != 1) {
/* Computing MAX */
		    r__1 = (wa1[il] - wa1[il - 1]) * .5f, r__2 = ulp * anorm, 
			    r__1 = max(r__1,r__2), r__2 = rtunfl * 2.f;
		    vl = wa1[il] - dmax(r__1,r__2);
		} else {
/* Computing MAX */
		    r__1 = (wa1[n] - wa1[1]) * .5f, r__2 = ulp * anorm, r__1 =
			     max(r__1,r__2), r__2 = rtunfl * 2.f;
		    vl = wa1[1] - dmax(r__1,r__2);
		}
		if (iu != n) {
/* Computing MAX */
		    r__1 = (wa1[iu + 1] - wa1[iu]) * .5f, r__2 = ulp * anorm, 
			    r__1 = max(r__1,r__2), r__2 = rtunfl * 2.f;
		    vu = wa1[iu] + dmax(r__1,r__2);
		} else {
/* Computing MAX */
		    r__1 = (wa1[n] - wa1[1]) * .5f, r__2 = ulp * anorm, r__1 =
			     max(r__1,r__2), r__2 = rtunfl * 2.f;
		    vu = wa1[n] + dmax(r__1,r__2);
		}
	    } else {
		vl = 0.f;
		vu = 1.f;
	    }

	    sstebz_("V", "E", &n, &vl, &vu, &il, &iu, &abstol, &sd[1], &se[1], 
		     &m3, &nsplit, &wa3[1], &iwork[1], &iwork[n + 1], &rwork[
		    1], &iwork[(n << 1) + 1], &iinfo);
	    if (iinfo != 0) {
		io___73.ciunit = *nounit;
		s_wsfe(&io___73);
		do_fio(&c__1, "SSTEBZ(V)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[19] = ulpinv;
		    goto L280;
		}
	    }

	    if (m3 == 0 && n != 0) {
		result[19] = ulpinv;
		goto L280;
	    }

/*           Do test 19 */

	    temp1 = ssxt1_(&c__1, &wa2[1], &m2, &wa3[1], &m3, &abstol, &ulp, &
		    unfl);
	    temp2 = ssxt1_(&c__1, &wa3[1], &m3, &wa2[1], &m2, &abstol, &ulp, &
		    unfl);
	    if (n > 0) {
/* Computing MAX */
		r__2 = (r__1 = wa1[n], dabs(r__1)), r__3 = dabs(wa1[1]);
		temp3 = dmax(r__2,r__3);
	    } else {
		temp3 = 0.f;
	    }

/* Computing MAX */
	    r__1 = unfl, r__2 = temp3 * ulp;
	    result[19] = (temp1 + temp2) / dmax(r__1,r__2);

/*           Call CSTEIN to compute eigenvectors corresponding to */
/*           eigenvalues in WA1.  (First call SSTEBZ again, to make sure */
/*           it returns these eigenvalues in the correct order.) */

	    ntest = 21;
	    sstebz_("A", "B", &n, &vl, &vu, &il, &iu, &abstol, &sd[1], &se[1], 
		     &m, &nsplit, &wa1[1], &iwork[1], &iwork[n + 1], &rwork[1]
, &iwork[(n << 1) + 1], &iinfo);
	    if (iinfo != 0) {
		io___74.ciunit = *nounit;
		s_wsfe(&io___74);
		do_fio(&c__1, "SSTEBZ(A,B)", (ftnlen)11);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[20] = ulpinv;
		    result[21] = ulpinv;
		    goto L280;
		}
	    }

	    cstein_(&n, &sd[1], &se[1], &m, &wa1[1], &iwork[1], &iwork[n + 1], 
		     &z__[z_offset], ldu, &rwork[1], &iwork[(n << 1) + 1], &
		    iwork[n * 3 + 1], &iinfo);
	    if (iinfo != 0) {
		io___75.ciunit = *nounit;
		s_wsfe(&io___75);
		do_fio(&c__1, "CSTEIN", (ftnlen)6);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[20] = ulpinv;
		    result[21] = ulpinv;
		    goto L280;
		}
	    }

/*           Do tests 20 and 21 */

	    cstt21_(&n, &c__0, &sd[1], &se[1], &wa1[1], dumma, &z__[z_offset], 
		     ldu, &work[1], &rwork[1], &result[20]);

/*           Call CSTEDC(I) to compute D1 and Z, do tests. */

/*           Compute D1 and Z */

	    inde = 1;
	    indrwk = inde + n;
	    scopy_(&n, &sd[1], &c__1, &d1[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[inde], &c__1);
	    }
	    claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

	    ntest = 22;
	    cstedc_("I", &n, &d1[1], &rwork[inde], &z__[z_offset], ldu, &work[
		    1], &lwedc, &rwork[indrwk], &lrwedc, &iwork[1], &liwedc, &
		    iinfo);
	    if (iinfo != 0) {
		io___78.ciunit = *nounit;
		s_wsfe(&io___78);
		do_fio(&c__1, "CSTEDC(I)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[22] = ulpinv;
		    goto L280;
		}
	    }

/*           Do Tests 22 and 23 */

	    cstt21_(&n, &c__0, &sd[1], &se[1], &d1[1], dumma, &z__[z_offset], 
		    ldu, &work[1], &rwork[1], &result[22]);

/*           Call CSTEDC(V) to compute D1 and Z, do tests. */

/*           Compute D1 and Z */

	    scopy_(&n, &sd[1], &c__1, &d1[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[inde], &c__1);
	    }
	    claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

	    ntest = 24;
	    cstedc_("V", &n, &d1[1], &rwork[inde], &z__[z_offset], ldu, &work[
		    1], &lwedc, &rwork[indrwk], &lrwedc, &iwork[1], &liwedc, &
		    iinfo);
	    if (iinfo != 0) {
		io___79.ciunit = *nounit;
		s_wsfe(&io___79);
		do_fio(&c__1, "CSTEDC(V)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[24] = ulpinv;
		    goto L280;
		}
	    }

/*           Do Tests 24 and 25 */

	    cstt21_(&n, &c__0, &sd[1], &se[1], &d1[1], dumma, &z__[z_offset], 
		    ldu, &work[1], &rwork[1], &result[24]);

/*           Call CSTEDC(N) to compute D2, do tests. */

/*           Compute D2 */

	    scopy_(&n, &sd[1], &c__1, &d2[1], &c__1);
	    if (n > 0) {
		i__3 = n - 1;
		scopy_(&i__3, &se[1], &c__1, &rwork[inde], &c__1);
	    }
	    claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

	    ntest = 26;
	    cstedc_("N", &n, &d2[1], &rwork[inde], &z__[z_offset], ldu, &work[
		    1], &lwedc, &rwork[indrwk], &lrwedc, &iwork[1], &liwedc, &
		    iinfo);
	    if (iinfo != 0) {
		io___80.ciunit = *nounit;
		s_wsfe(&io___80);
		do_fio(&c__1, "CSTEDC(N)", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		if (iinfo < 0) {
		    return 0;
		} else {
		    result[26] = ulpinv;
		    goto L280;
		}
	    }

/*           Do Test 26 */

	    temp1 = 0.f;
	    temp2 = 0.f;

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		r__3 = temp1, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 = max(
			r__3,r__4), r__4 = (r__2 = d2[j], dabs(r__2));
		temp1 = dmax(r__3,r__4);
/* Computing MAX */
		r__2 = temp2, r__3 = (r__1 = d1[j] - d2[j], dabs(r__1));
		temp2 = dmax(r__2,r__3);
/* L210: */
	    }

/* Computing MAX */
	    r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
	    result[26] = temp2 / dmax(r__1,r__2);

/*           Only test CSTEMR if IEEE compliant */

	    if (ilaenv_(&c__10, "CSTEMR", "VA", &c__1, &c__0, &c__0, &c__0) == 1 && ilaenv_(&c__11, "CSTEMR", 
		    "VA", &c__1, &c__0, &c__0, &c__0) ==
		     1) {

/*           Call CSTEMR, do test 27 (relative eigenvalue accuracy) */

/*              If S is positive definite and diagonally dominant, */
/*              ask for all eigenvalues with high relative accuracy. */

		vl = 0.f;
		vu = 0.f;
		il = 0;
		iu = 0;
		if (FALSE_) {
		    ntest = 27;
		    abstol = unfl + unfl;
		    i__3 = *lwork - (n << 1);
		    cstemr_("V", "A", &n, &sd[1], &se[1], &vl, &vu, &il, &iu, 
			    &m, &wr[1], &z__[z_offset], ldu, &n, &iwork[1], &
			    tryrac, &rwork[1], lrwork, &iwork[(n << 1) + 1], &
			    i__3, &iinfo);
		    if (iinfo != 0) {
			io___81.ciunit = *nounit;
			s_wsfe(&io___81);
			do_fio(&c__1, "CSTEMR(V,A,rel)", (ftnlen)15);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			e_wsfe();
			*info = abs(iinfo);
			if (iinfo < 0) {
			    return 0;
			} else {
			    result[27] = ulpinv;
			    goto L270;
			}
		    }

/*              Do test 27 */

		    temp2 = (n * 2.f - 1.f) * 2.f * ulp * 3.f / .0625f;

		    temp1 = 0.f;
		    i__3 = n;
		    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
			r__3 = temp1, r__4 = (r__2 = d4[j] - wr[n - j + 1], 
				dabs(r__2)) / (abstol + (r__1 = d4[j], dabs(
				r__1)));
			temp1 = dmax(r__3,r__4);
/* L220: */
		    }

		    result[27] = temp1 / temp2;

		    il = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		    iu = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		    if (iu < il) {
			itemp = iu;
			iu = il;
			il = itemp;
		    }

		    if (FALSE_) {
			ntest = 28;
			abstol = unfl + unfl;
			i__3 = *lwork - (n << 1);
			cstemr_("V", "I", &n, &sd[1], &se[1], &vl, &vu, &il, &
				iu, &m, &wr[1], &z__[z_offset], ldu, &n, &
				iwork[1], &tryrac, &rwork[1], lrwork, &iwork[(
				n << 1) + 1], &i__3, &iinfo);

			if (iinfo != 0) {
			    io___82.ciunit = *nounit;
			    s_wsfe(&io___82);
			    do_fio(&c__1, "CSTEMR(V,I,rel)", (ftnlen)15);
			    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				    integer));
			    e_wsfe();
			    *info = abs(iinfo);
			    if (iinfo < 0) {
				return 0;
			    } else {
				result[28] = ulpinv;
				goto L270;
			    }
			}


/*                 Do test 28 */

			temp2 = (n * 2.f - 1.f) * 2.f * ulp * 3.f / .0625f;

			temp1 = 0.f;
			i__3 = iu;
			for (j = il; j <= i__3; ++j) {
/* Computing MAX */
			    r__3 = temp1, r__4 = (r__2 = wr[j - il + 1] - d4[
				    n - j + 1], dabs(r__2)) / (abstol + (r__1 
				    = wr[j - il + 1], dabs(r__1)));
			    temp1 = dmax(r__3,r__4);
/* L230: */
			}

			result[28] = temp1 / temp2;
		    } else {
			result[28] = 0.f;
		    }
		} else {
		    result[27] = 0.f;
		    result[28] = 0.f;
		}

/*           Call CSTEMR(V,I) to compute D1 and Z, do tests. */

/*           Compute D1 and Z */

		scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		if (n > 0) {
		    i__3 = n - 1;
		    scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		}
		claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

		if (FALSE_) {
		    ntest = 29;
		    il = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		    iu = (n - 1) * (integer) slarnd_(&c__1, iseed2) + 1;
		    if (iu < il) {
			itemp = iu;
			iu = il;
			il = itemp;
		    }
		    i__3 = *lrwork - n;
		    i__4 = *liwork - (n << 1);
		    cstemr_("V", "I", &n, &d5[1], &rwork[1], &vl, &vu, &il, &
			    iu, &m, &d1[1], &z__[z_offset], ldu, &n, &iwork[1]
, &tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) 
			    + 1], &i__4, &iinfo);
		    if (iinfo != 0) {
			io___83.ciunit = *nounit;
			s_wsfe(&io___83);
			do_fio(&c__1, "CSTEMR(V,I)", (ftnlen)11);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			e_wsfe();
			*info = abs(iinfo);
			if (iinfo < 0) {
			    return 0;
			} else {
			    result[29] = ulpinv;
			    goto L280;
			}
		    }

/*           Do Tests 29 and 30 */


/*           Call CSTEMR to compute D2, do tests. */

/*           Compute D2 */

		    scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		    if (n > 0) {
			i__3 = n - 1;
			scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		    }

		    ntest = 31;
		    i__3 = *lrwork - n;
		    i__4 = *liwork - (n << 1);
		    cstemr_("N", "I", &n, &d5[1], &rwork[1], &vl, &vu, &il, &
			    iu, &m, &d2[1], &z__[z_offset], ldu, &n, &iwork[1]
, &tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) 
			    + 1], &i__4, &iinfo);
		    if (iinfo != 0) {
			io___84.ciunit = *nounit;
			s_wsfe(&io___84);
			do_fio(&c__1, "CSTEMR(N,I)", (ftnlen)11);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			e_wsfe();
			*info = abs(iinfo);
			if (iinfo < 0) {
			    return 0;
			} else {
			    result[31] = ulpinv;
			    goto L280;
			}
		    }

/*           Do Test 31 */

		    temp1 = 0.f;
		    temp2 = 0.f;

		    i__3 = iu - il + 1;
		    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
			r__3 = temp1, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 
				= max(r__3,r__4), r__4 = (r__2 = d2[j], dabs(
				r__2));
			temp1 = dmax(r__3,r__4);
/* Computing MAX */
			r__2 = temp2, r__3 = (r__1 = d1[j] - d2[j], dabs(r__1)
				);
			temp2 = dmax(r__2,r__3);
/* L240: */
		    }

/* Computing MAX */
		    r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
		    result[31] = temp2 / dmax(r__1,r__2);


/*           Call CSTEMR(V,V) to compute D1 and Z, do tests. */

/*           Compute D1 and Z */

		    scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		    if (n > 0) {
			i__3 = n - 1;
			scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		    }
		    claset_("Full", &n, &n, &c_b1, &c_b2, &z__[z_offset], ldu);

		    ntest = 32;

		    if (n > 0) {
			if (il != 1) {
/* Computing MAX */
			    r__1 = (d2[il] - d2[il - 1]) * .5f, r__2 = ulp * 
				    anorm, r__1 = max(r__1,r__2), r__2 = 
				    rtunfl * 2.f;
			    vl = d2[il] - dmax(r__1,r__2);
			} else {
/* Computing MAX */
			    r__1 = (d2[n] - d2[1]) * .5f, r__2 = ulp * anorm, 
				    r__1 = max(r__1,r__2), r__2 = rtunfl * 
				    2.f;
			    vl = d2[1] - dmax(r__1,r__2);
			}
			if (iu != n) {
/* Computing MAX */
			    r__1 = (d2[iu + 1] - d2[iu]) * .5f, r__2 = ulp * 
				    anorm, r__1 = max(r__1,r__2), r__2 = 
				    rtunfl * 2.f;
			    vu = d2[iu] + dmax(r__1,r__2);
			} else {
/* Computing MAX */
			    r__1 = (d2[n] - d2[1]) * .5f, r__2 = ulp * anorm, 
				    r__1 = max(r__1,r__2), r__2 = rtunfl * 
				    2.f;
			    vu = d2[n] + dmax(r__1,r__2);
			}
		    } else {
			vl = 0.f;
			vu = 1.f;
		    }

		    i__3 = *lrwork - n;
		    i__4 = *liwork - (n << 1);
		    cstemr_("V", "V", &n, &d5[1], &rwork[1], &vl, &vu, &il, &
			    iu, &m, &d1[1], &z__[z_offset], ldu, &n, &iwork[1]
, &tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) 
			    + 1], &i__4, &iinfo);
		    if (iinfo != 0) {
			io___85.ciunit = *nounit;
			s_wsfe(&io___85);
			do_fio(&c__1, "CSTEMR(V,V)", (ftnlen)11);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			e_wsfe();
			*info = abs(iinfo);
			if (iinfo < 0) {
			    return 0;
			} else {
			    result[32] = ulpinv;
			    goto L280;
			}
		    }

/*           Do Tests 32 and 33 */

		    cstt22_(&n, &m, &c__0, &sd[1], &se[1], &d1[1], dumma, &
			    z__[z_offset], ldu, &work[1], &m, &rwork[1], &
			    result[32]);

/*           Call CSTEMR to compute D2, do tests. */

/*           Compute D2 */

		    scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		    if (n > 0) {
			i__3 = n - 1;
			scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		    }

		    ntest = 34;
		    i__3 = *lrwork - n;
		    i__4 = *liwork - (n << 1);
		    cstemr_("N", "V", &n, &d5[1], &rwork[1], &vl, &vu, &il, &
			    iu, &m, &d2[1], &z__[z_offset], ldu, &n, &iwork[1]
, &tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) 
			    + 1], &i__4, &iinfo);
		    if (iinfo != 0) {
			io___86.ciunit = *nounit;
			s_wsfe(&io___86);
			do_fio(&c__1, "CSTEMR(N,V)", (ftnlen)11);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			e_wsfe();
			*info = abs(iinfo);
			if (iinfo < 0) {
			    return 0;
			} else {
			    result[34] = ulpinv;
			    goto L280;
			}
		    }

/*           Do Test 34 */

		    temp1 = 0.f;
		    temp2 = 0.f;

		    i__3 = iu - il + 1;
		    for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
			r__3 = temp1, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 
				= max(r__3,r__4), r__4 = (r__2 = d2[j], dabs(
				r__2));
			temp1 = dmax(r__3,r__4);
/* Computing MAX */
			r__2 = temp2, r__3 = (r__1 = d1[j] - d2[j], dabs(r__1)
				);
			temp2 = dmax(r__2,r__3);
/* L250: */
		    }

/* Computing MAX */
		    r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
		    result[34] = temp2 / dmax(r__1,r__2);
		} else {
		    result[29] = 0.f;
		    result[30] = 0.f;
		    result[31] = 0.f;
		    result[32] = 0.f;
		    result[33] = 0.f;
		    result[34] = 0.f;
		}


/*           Call CSTEMR(V,A) to compute D1 and Z, do tests. */

/*           Compute D1 and Z */

		scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		if (n > 0) {
		    i__3 = n - 1;
		    scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		}

		ntest = 35;

		i__3 = *lrwork - n;
		i__4 = *liwork - (n << 1);
		cstemr_("V", "A", &n, &d5[1], &rwork[1], &vl, &vu, &il, &iu, &
			m, &d1[1], &z__[z_offset], ldu, &n, &iwork[1], &
			tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) + 1], &
			i__4, &iinfo);
		if (iinfo != 0) {
		    io___87.ciunit = *nounit;
		    s_wsfe(&io___87);
		    do_fio(&c__1, "CSTEMR(V,A)", (ftnlen)11);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[35] = ulpinv;
			goto L280;
		    }
		}

/*           Do Tests 35 and 36 */

		cstt22_(&n, &m, &c__0, &sd[1], &se[1], &d1[1], dumma, &z__[
			z_offset], ldu, &work[1], &m, &rwork[1], &result[35]);

/*           Call CSTEMR to compute D2, do tests. */

/*           Compute D2 */

		scopy_(&n, &sd[1], &c__1, &d5[1], &c__1);
		if (n > 0) {
		    i__3 = n - 1;
		    scopy_(&i__3, &se[1], &c__1, &rwork[1], &c__1);
		}

		ntest = 37;
		i__3 = *lrwork - n;
		i__4 = *liwork - (n << 1);
		cstemr_("N", "A", &n, &d5[1], &rwork[1], &vl, &vu, &il, &iu, &
			m, &d2[1], &z__[z_offset], ldu, &n, &iwork[1], &
			tryrac, &rwork[n + 1], &i__3, &iwork[(n << 1) + 1], &
			i__4, &iinfo);
		if (iinfo != 0) {
		    io___88.ciunit = *nounit;
		    s_wsfe(&io___88);
		    do_fio(&c__1, "CSTEMR(N,A)", (ftnlen)11);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[37] = ulpinv;
			goto L280;
		    }
		}

/*           Do Test 34 */

		temp1 = 0.f;
		temp2 = 0.f;

		i__3 = n;
		for (j = 1; j <= i__3; ++j) {
/* Computing MAX */
		    r__3 = temp1, r__4 = (r__1 = d1[j], dabs(r__1)), r__3 = 
			    max(r__3,r__4), r__4 = (r__2 = d2[j], dabs(r__2));
		    temp1 = dmax(r__3,r__4);
/* Computing MAX */
		    r__2 = temp2, r__3 = (r__1 = d1[j] - d2[j], dabs(r__1));
		    temp2 = dmax(r__2,r__3);
/* L260: */
		}

/* Computing MAX */
		r__1 = unfl, r__2 = ulp * dmax(temp1,temp2);
		result[37] = temp2 / dmax(r__1,r__2);
	    }
L270:
L280:
	    ntestt += ntest;

/*           End of Loop -- Check for RESULT(j) > THRESH */


/*           Print out tests which fail. */

	    i__3 = ntest;
	    for (jr = 1; jr <= i__3; ++jr) {
		if (result[jr] >= *thresh) {

/*                 If this is the first test to fail, */
/*                 print a header to the data file. */

		    if (nerrs == 0) {
			io___89.ciunit = *nounit;
			s_wsfe(&io___89);
			do_fio(&c__1, "CST", (ftnlen)3);
			e_wsfe();
			io___90.ciunit = *nounit;
			s_wsfe(&io___90);
			e_wsfe();
			io___91.ciunit = *nounit;
			s_wsfe(&io___91);
			e_wsfe();
			io___92.ciunit = *nounit;
			s_wsfe(&io___92);
			do_fio(&c__1, "Hermitian", (ftnlen)9);
			e_wsfe();
			io___93.ciunit = *nounit;
			s_wsfe(&io___93);
			e_wsfe();

/*                    Tests performed */

			io___94.ciunit = *nounit;
			s_wsfe(&io___94);
			e_wsfe();
		    }
		    ++nerrs;
		    if (result[jr] < 1e4f) {
			io___95.ciunit = *nounit;
			s_wsfe(&io___95);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&jr, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[jr], (ftnlen)sizeof(
				real));
			e_wsfe();
		    } else {
			io___96.ciunit = *nounit;
			s_wsfe(&io___96);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&jr, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[jr], (ftnlen)sizeof(
				real));
			e_wsfe();
		    }
		}
/* L290: */
	    }
L300:
	    ;
	}
/* L310: */
    }

/*     Summary */

    slasum_("CST", nounit, &nerrs, &ntestt);
    return 0;




/* L9993: */
/* L9992: */
/* L9991: */
/* L9990: */

/*     End of CCHKST */

} /* cchkst_ */
