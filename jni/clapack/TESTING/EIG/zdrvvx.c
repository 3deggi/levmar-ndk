/* zdrvvx.f -- translated by f2c (version 20061008).
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

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__0 = 0;
static integer c__4 = 4;
static integer c__6 = 6;
static doublereal c_b39 = 1.;
static integer c__1 = 1;
static doublereal c_b49 = 0.;
static integer c__2 = 2;
static logical c_false = FALSE_;
static integer c__3 = 3;
static integer c__7 = 7;
static integer c__5 = 5;
static logical c_true = TRUE_;
static integer c__22 = 22;

/* Subroutine */ int zdrvvx_(integer *nsizes, integer *nn, integer *ntypes, 
	logical *dotype, integer *iseed, doublereal *thresh, integer *niunit, 
	integer *nounit, doublecomplex *a, integer *lda, doublecomplex *h__, 
	doublecomplex *w, doublecomplex *w1, doublecomplex *vl, integer *ldvl, 
	 doublecomplex *vr, integer *ldvr, doublecomplex *lre, integer *ldlre, 
	 doublereal *rcondv, doublereal *rcndv1, doublereal *rcdvin, 
	doublereal *rconde, doublereal *rcnde1, doublereal *rcdein, 
	doublereal *scale, doublereal *scale1, doublereal *result, 
	doublecomplex *work, integer *nwork, doublereal *rwork, integer *info)
{
    /* Initialized data */

    static integer ktype[21] = { 1,2,3,4,4,4,4,4,6,6,6,6,6,6,6,6,6,6,9,9,9 };
    static integer kmagn[21] = { 1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,1,2,3,1,2,3 };
    static integer kmode[21] = { 0,0,0,4,3,1,4,4,4,3,1,5,4,3,1,5,5,5,4,3,1 };
    static integer kconds[21] = { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,0,0,0 };
    static char bal[1*4] = "N" "P" "S" "B";

    /* Format strings */
    static char fmt_9992[] = "(\002 ZDRVVX: \002,a,\002 returned INFO=\002,i"
	    "6,\002.\002,/9x,\002N=\002,i6,\002, JTYPE=\002,i6,\002, ISEED="
	    "(\002,3(i5,\002,\002),i5,\002)\002)";
    static char fmt_9999[] = "(/1x,a3,\002 -- Complex Eigenvalue-Eigenvect"
	    "or \002,\002Decomposition Expert Driver\002,/\002 Matrix types ("
	    "see ZDRVVX for details): \002)";
    static char fmt_9998[] = "(/\002 Special Matrices:\002,/\002  1=Zero mat"
	    "rix.             \002,\002           \002,\002  5=Diagonal: geom"
	    "etr. spaced entries.\002,/\002  2=Identity matrix.              "
	    "      \002,\002  6=Diagona\002,\002l: clustered entries.\002,"
	    "/\002  3=Transposed Jordan block.  \002,\002          \002,\002 "
	    " 7=Diagonal: large, evenly spaced.\002,/\002  \002,\0024=Diagona"
	    "l: evenly spaced entries.    \002,\002  8=Diagonal: s\002,\002ma"
	    "ll, evenly spaced.\002)";
    static char fmt_9997[] = "(\002 Dense, Non-Symmetric Matrices:\002,/\002"
	    "  9=Well-cond., ev\002,\002enly spaced eigenvals.\002,\002 14=Il"
	    "l-cond., geomet. spaced e\002,\002igenals.\002,/\002 10=Well-con"
	    "d., geom. spaced eigenvals. \002,\002 15=Ill-conditioned, cluste"
	    "red e.vals.\002,/\002 11=Well-cond\002,\002itioned, clustered e."
	    "vals. \002,\002 16=Ill-cond., random comp\002,\002lex \002,/\002"
	    " 12=Well-cond., random complex \002,\002         \002,\002 17=Il"
	    "l-cond., large rand. complx \002,/\002 13=Ill-condi\002,\002tion"
	    "ed, evenly spaced.     \002,\002 18=Ill-cond., small rand.\002"
	    ",\002 complx \002)";
    static char fmt_9996[] = "(\002 19=Matrix with random O(1) entries.   "
	    " \002,\002 21=Matrix \002,\002with small random entries.\002,"
	    "/\002 20=Matrix with large ran\002,\002dom entries.   \002,\002 "
	    "22=Matrix read from input file\002,/)";
    static char fmt_9995[] = "(\002 Tests performed with test threshold ="
	    "\002,f8.2,//\002 1 = | A VR - VR W | / ( n |A| ulp ) \002,/\002 "
	    "2 = | transpose(A) VL - VL W | / ( n |A| ulp ) \002,/\002 3 = | "
	    "|VR(i)| - 1 | / ulp \002,/\002 4 = | |VL(i)| - 1 | / ulp \002,"
	    "/\002 5 = 0 if W same no matter if VR or VL computed,\002,\002 1"
	    "/ulp otherwise\002,/\002 6 = 0 if VR same no matter what else co"
	    "mputed,\002,\002  1/ulp otherwise\002,/\002 7 = 0 if VL same no "
	    "matter what else computed,\002,\002  1/ulp otherwise\002,/\002 8"
	    " = 0 if RCONDV same no matter what else computed,\002,\002  1/ul"
	    "p otherwise\002,/\002 9 = 0 if SCALE, ILO, IHI, ABNRM same no ma"
	    "tter what else\002,\002 computed,  1/ulp otherwise\002,/\002 10 "
	    "= | RCONDV - RCONDV(precomputed) | / cond(RCONDV),\002,/\002 11 "
	    "= | RCONDE - RCONDE(precomputed) | / cond(RCONDE),\002)";
    static char fmt_9994[] = "(\002 BALANC='\002,a1,\002',N=\002,i4,\002,I"
	    "WK=\002,i1,\002, seed=\002,4(i4,\002,\002),\002 type \002,i2,"
	    "\002, test(\002,i2,\002)=\002,g10.3)";
    static char fmt_9993[] = "(\002 N=\002,i5,\002, input example =\002,i3"
	    ",\002,  test(\002,i2,\002)=\002,g10.3)";

    /* System generated locals */
    integer a_dim1, a_offset, h_dim1, h_offset, lre_dim1, lre_offset, vl_dim1,
	     vl_offset, vr_dim1, vr_offset, i__1, i__2, i__3, i__4;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    double sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);

    /* Local variables */
    integer i__, j, n;
    doublereal wi, wr;
    integer iwk;
    doublereal ulp;
    integer ibal;
    doublereal cond;
    integer jcol;
    char path[3];
    integer nmax;
    doublereal unfl, ovfl;
    integer isrt;
    logical badnn;
    integer nfail, imode, iinfo;
    doublereal conds, anorm;
    extern /* Subroutine */ int zget23_(logical *, integer *, char *, integer 
	    *, doublereal *, integer *, integer *, integer *, doublecomplex *, 
	     integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublecomplex *, 
	    integer *, doublereal *, integer *);
    integer jsize, nerrs, itype, jtype, ntest;
    doublereal rtulp;
    extern /* Subroutine */ int dlabad_(doublereal *, doublereal *);
    char balanc[1];
    extern doublereal dlamch_(char *);
    integer idumma[1];
    extern /* Subroutine */ int xerbla_(char *, integer *);
    integer ioldsd[4];
    extern /* Subroutine */ int dlasum_(char *, integer *, integer *, integer 
	    *), zlatme_(integer *, char *, integer *, doublecomplex *, 
	     integer *, doublereal *, doublecomplex *, char *, char *, char *, 
	     char *, doublereal *, integer *, doublereal *, integer *, 
	    integer *, doublereal *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *);
    integer ntestf;
    extern /* Subroutine */ int zlatmr_(integer *, integer *, char *, integer 
	    *, char *, doublecomplex *, integer *, doublereal *, 
	    doublecomplex *, char *, char *, doublecomplex *, integer *, 
	    doublereal *, doublecomplex *, integer *, doublereal *, char *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, char 
	    *, doublecomplex *, integer *, integer *, integer *), zlatms_(integer *, 
	    integer *, char *, integer *, char *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, char *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    doublereal ulpinv;
    integer nnwork;
    doublereal rtulpi;
    integer mtypes, ntestt;

    /* Fortran I/O blocks */
    static cilist io___32 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___45 = { 0, 0, 1, 0, 0 };
    static cilist io___48 = { 0, 0, 0, 0, 0 };
    static cilist io___49 = { 0, 0, 0, 0, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___53 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___55 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___56 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___57 = { 0, 0, 0, fmt_9993, 0 };



/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     ZDRVVX  checks the nonsymmetric eigenvalue problem expert driver */
/*     ZGEEVX. */

/*     ZDRVVX uses both test matrices generated randomly depending on */
/*     data supplied in the calling sequence, as well as on data */
/*     read from an input file and including precomputed condition */
/*     numbers to which it compares the ones it computes. */

/*     When ZDRVVX is called, a number of matrix "sizes" ("n's") and a */
/*     number of matrix "types" are specified in the calling sequence. */
/*     For each size ("n") and each type of matrix, one matrix will be */
/*     generated and used to test the nonsymmetric eigenroutines.  For */
/*     each matrix, 9 tests will be performed: */

/*     (1)     | A * VR - VR * W | / ( n |A| ulp ) */

/*       Here VR is the matrix of unit right eigenvectors. */
/*       W is a diagonal matrix with diagonal entries W(j). */

/*     (2)     | A**H  * VL - VL * W**H | / ( n |A| ulp ) */

/*       Here VL is the matrix of unit left eigenvectors, A**H is the */
/*       conjugate transpose of A, and W is as above. */

/*     (3)     | |VR(i)| - 1 | / ulp and largest component real */

/*       VR(i) denotes the i-th column of VR. */

/*     (4)     | |VL(i)| - 1 | / ulp and largest component real */

/*       VL(i) denotes the i-th column of VL. */

/*     (5)     W(full) = W(partial) */

/*       W(full) denotes the eigenvalues computed when VR, VL, RCONDV */
/*       and RCONDE are also computed, and W(partial) denotes the */
/*       eigenvalues computed when only some of VR, VL, RCONDV, and */
/*       RCONDE are computed. */

/*     (6)     VR(full) = VR(partial) */

/*       VR(full) denotes the right eigenvectors computed when VL, RCONDV */
/*       and RCONDE are computed, and VR(partial) denotes the result */
/*       when only some of VL and RCONDV are computed. */

/*     (7)     VL(full) = VL(partial) */

/*       VL(full) denotes the left eigenvectors computed when VR, RCONDV */
/*       and RCONDE are computed, and VL(partial) denotes the result */
/*       when only some of VR and RCONDV are computed. */

/*     (8)     0 if SCALE, ILO, IHI, ABNRM (full) = */
/*                  SCALE, ILO, IHI, ABNRM (partial) */
/*             1/ulp otherwise */

/*       SCALE, ILO, IHI and ABNRM describe how the matrix is balanced. */
/*       (full) is when VR, VL, RCONDE and RCONDV are also computed, and */
/*       (partial) is when some are not computed. */

/*     (9)     RCONDV(full) = RCONDV(partial) */

/*       RCONDV(full) denotes the reciprocal condition numbers of the */
/*       right eigenvectors computed when VR, VL and RCONDE are also */
/*       computed. RCONDV(partial) denotes the reciprocal condition */
/*       numbers when only some of VR, VL and RCONDE are computed. */

/*     The "sizes" are specified by an array NN(1:NSIZES); the value of */
/*     each element NN(j) specifies one size. */
/*     The "types" are specified by a logical array DOTYPE( 1:NTYPES ); */
/*     if DOTYPE(j) is .TRUE., then matrix type "j" will be generated. */
/*     Currently, the list of possible types is: */

/*     (1)  The zero matrix. */
/*     (2)  The identity matrix. */
/*     (3)  A (transposed) Jordan block, with 1's on the diagonal. */

/*     (4)  A diagonal matrix with evenly spaced entries */
/*          1, ..., ULP  and random complex angles. */
/*          (ULP = (first number larger than 1) - 1 ) */
/*     (5)  A diagonal matrix with geometrically spaced entries */
/*          1, ..., ULP  and random complex angles. */
/*     (6)  A diagonal matrix with "clustered" entries 1, ULP, ..., ULP */
/*          and random complex angles. */

/*     (7)  Same as (4), but multiplied by a constant near */
/*          the overflow threshold */
/*     (8)  Same as (4), but multiplied by a constant near */
/*          the underflow threshold */

/*     (9)  A matrix of the form  U' T U, where U is unitary and */
/*          T has evenly spaced entries 1, ..., ULP with random complex */
/*          angles on the diagonal and random O(1) entries in the upper */
/*          triangle. */

/*     (10) A matrix of the form  U' T U, where U is unitary and */
/*          T has geometrically spaced entries 1, ..., ULP with random */
/*          complex angles on the diagonal and random O(1) entries in */
/*          the upper triangle. */

/*     (11) A matrix of the form  U' T U, where U is unitary and */
/*          T has "clustered" entries 1, ULP,..., ULP with random */
/*          complex angles on the diagonal and random O(1) entries in */
/*          the upper triangle. */

/*     (12) A matrix of the form  U' T U, where U is unitary and */
/*          T has complex eigenvalues randomly chosen from */
/*          ULP < |z| < 1   and random O(1) entries in the upper */
/*          triangle. */

/*     (13) A matrix of the form  X' T X, where X has condition */
/*          SQRT( ULP ) and T has evenly spaced entries 1, ..., ULP */
/*          with random complex angles on the diagonal and random O(1) */
/*          entries in the upper triangle. */

/*     (14) A matrix of the form  X' T X, where X has condition */
/*          SQRT( ULP ) and T has geometrically spaced entries */
/*          1, ..., ULP with random complex angles on the diagonal */
/*          and random O(1) entries in the upper triangle. */

/*     (15) A matrix of the form  X' T X, where X has condition */
/*          SQRT( ULP ) and T has "clustered" entries 1, ULP,..., ULP */
/*          with random complex angles on the diagonal and random O(1) */
/*          entries in the upper triangle. */

/*     (16) A matrix of the form  X' T X, where X has condition */
/*          SQRT( ULP ) and T has complex eigenvalues randomly chosen */
/*          from ULP < |z| < 1 and random O(1) entries in the upper */
/*          triangle. */

/*     (17) Same as (16), but multiplied by a constant */
/*          near the overflow threshold */
/*     (18) Same as (16), but multiplied by a constant */
/*          near the underflow threshold */

/*     (19) Nonsymmetric matrix with random entries chosen from |z| < 1 */
/*          If N is at least 4, all entries in first two rows and last */
/*          row, and first column and last two columns are zero. */
/*     (20) Same as (19), but multiplied by a constant */
/*          near the overflow threshold */
/*     (21) Same as (19), but multiplied by a constant */
/*          near the underflow threshold */

/*     In addition, an input file will be read from logical unit number */
/*     NIUNIT. The file contains matrices along with precomputed */
/*     eigenvalues and reciprocal condition numbers for the eigenvalues */
/*     and right eigenvectors. For these matrices, in addition to tests */
/*     (1) to (9) we will compute the following two tests: */

/*    (10)  |RCONDV - RCDVIN| / cond(RCONDV) */

/*       RCONDV is the reciprocal right eigenvector condition number */
/*       computed by ZGEEVX and RCDVIN (the precomputed true value) */
/*       is supplied as input. cond(RCONDV) is the condition number of */
/*       RCONDV, and takes errors in computing RCONDV into account, so */
/*       that the resulting quantity should be O(ULP). cond(RCONDV) is */
/*       essentially given by norm(A)/RCONDE. */

/*    (11)  |RCONDE - RCDEIN| / cond(RCONDE) */

/*       RCONDE is the reciprocal eigenvalue condition number */
/*       computed by ZGEEVX and RCDEIN (the precomputed true value) */
/*       is supplied as input.  cond(RCONDE) is the condition number */
/*       of RCONDE, and takes errors in computing RCONDE into account, */
/*       so that the resulting quantity should be O(ULP). cond(RCONDE) */
/*       is essentially given by norm(A)/RCONDV. */

/*  Arguments */
/*  ========== */

/*  NSIZES  (input) INTEGER */
/*          The number of sizes of matrices to use.  NSIZES must be at */
/*          least zero. If it is zero, no randomly generated matrices */
/*          are tested, but any test matrices read from NIUNIT will be */
/*          tested. */

/*  NN      (input) INTEGER array, dimension (NSIZES) */
/*          An array containing the sizes to be used for the matrices. */
/*          Zero values will be skipped.  The values must be at least */
/*          zero. */

/*  NTYPES  (input) INTEGER */
/*          The number of elements in DOTYPE. NTYPES must be at least */
/*          zero. If it is zero, no randomly generated test matrices */
/*          are tested, but and test matrices read from NIUNIT will be */
/*          tested. If it is MAXTYP+1 and NSIZES is 1, then an */
/*          additional type, MAXTYP+1 is defined, which is to use */
/*          whatever matrix is in A.  This is only useful if */
/*          DOTYPE(1:MAXTYP) is .FALSE. and DOTYPE(MAXTYP+1) is .TRUE. . */

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
/*          next call to ZDRVVX to continue the same random number */
/*          sequence. */

/*  THRESH  (input) DOUBLE PRECISION */
/*          A test will count as "failed" if the "error", computed as */
/*          described above, exceeds THRESH.  Note that the error */
/*          is scaled to be O(1), so THRESH should be a reasonably */
/*          small multiple of 1, e.g., 10 or 100.  In particular, */
/*          it should not depend on the precision (single vs. double) */
/*          or the size of the matrix.  It must be at least zero. */

/*  NIUNIT  (input) INTEGER */
/*          The FORTRAN unit number for reading in the data file of */
/*          problems to solve. */

/*  NOUNIT  (input) INTEGER */
/*          The FORTRAN unit number for printing out error messages */
/*          (e.g., if a routine returns INFO not equal to 0.) */

/*  A       (workspace) COMPLEX*16 array, dimension (LDA, max(NN,12)) */
/*          Used to hold the matrix whose eigenvalues are to be */
/*          computed.  On exit, A contains the last matrix actually used. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of A, and H. LDA must be at */
/*          least 1 and at least max( NN, 12 ). (12 is the */
/*          dimension of the largest matrix on the precomputed */
/*          input file.) */

/*  H       (workspace) COMPLEX*16 array, dimension (LDA, max(NN,12)) */
/*          Another copy of the test matrix A, modified by ZGEEVX. */

/*  W       (workspace) COMPLEX*16 array, dimension (max(NN,12)) */
/*          Contains the eigenvalues of A. */

/*  W1      (workspace) COMPLEX*16 array, dimension (max(NN,12)) */
/*          Like W, this array contains the eigenvalues of A, */
/*          but those computed when ZGEEVX only computes a partial */
/*          eigendecomposition, i.e. not the eigenvalues and left */
/*          and right eigenvectors. */

/*  VL      (workspace) COMPLEX*16 array, dimension (LDVL, max(NN,12)) */
/*          VL holds the computed left eigenvectors. */

/*  LDVL    (input) INTEGER */
/*          Leading dimension of VL. Must be at least max(1,max(NN,12)). */

/*  VR      (workspace) COMPLEX*16 array, dimension (LDVR, max(NN,12)) */
/*          VR holds the computed right eigenvectors. */

/*  LDVR    (input) INTEGER */
/*          Leading dimension of VR. Must be at least max(1,max(NN,12)). */

/*  LRE     (workspace) COMPLEX*16 array, dimension (LDLRE, max(NN,12)) */
/*          LRE holds the computed right or left eigenvectors. */

/*  LDLRE   (input) INTEGER */
/*          Leading dimension of LRE. Must be at least max(1,max(NN,12)) */

/*  RESULT  (output) DOUBLE PRECISION array, dimension (11) */
/*          The values computed by the seven tests described above. */
/*          The values are currently limited to 1/ulp, to avoid */
/*          overflow. */

/*  WORK    (workspace) COMPLEX*16 array, dimension (NWORK) */

/*  NWORK   (input) INTEGER */
/*          The number of entries in WORK.  This must be at least */
/*          max(6*12+2*12**2,6*NN(j)+2*NN(j)**2) = */
/*          max(    360     ,6*NN(j)+2*NN(j)**2)    for all j. */

/*  RWORK   (workspace) DOUBLE PRECISION array, dimension (2*max(NN,12)) */

/*  INFO    (output) INTEGER */
/*          If 0,  then successful exit. */
/*          If <0, then input paramter -INFO is incorrect. */
/*          If >0, ZLATMR, CLATMS, CLATME or ZGET23 returned an error */
/*                 code, and INFO is its absolute value. */

/* ----------------------------------------------------------------------- */

/*     Some Local Variables and Parameters: */
/*     ---- ----- --------- --- ---------- */

/*     ZERO, ONE       Real 0 and 1. */
/*     MAXTYP          The number of types defined. */
/*     NMAX            Largest value in NN or 12. */
/*     NERRS           The number of tests which have exceeded THRESH */
/*     COND, CONDS, */
/*     IMODE           Values to be passed to the matrix generators. */
/*     ANORM           Norm of A; passed to matrix generators. */

/*     OVFL, UNFL      Overflow and underflow thresholds. */
/*     ULP, ULPINV     Finest relative precision and its inverse. */
/*     RTULP, RTULPI   Square roots of the previous 4 values. */

/*             The following four arrays decode JTYPE: */
/*     KTYPE(j)        The general type (1-10) for type "j". */
/*     KMODE(j)        The MODE value to be passed to the matrix */
/*                     generator for type "j". */
/*     KMAGN(j)        The order of magnitude ( O(1), */
/*                     O(overflow^(1/2) ), O(underflow^(1/2) ) */
/*     KCONDS(j)       Selectw whether CONDS is to be 1 or */
/*                     1/sqrt(ulp).  (0 means irrelevant.) */

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
    h_dim1 = *lda;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --w;
    --w1;
    vl_dim1 = *ldvl;
    vl_offset = 1 + vl_dim1;
    vl -= vl_offset;
    vr_dim1 = *ldvr;
    vr_offset = 1 + vr_dim1;
    vr -= vr_offset;
    lre_dim1 = *ldlre;
    lre_offset = 1 + lre_dim1;
    lre -= lre_offset;
    --rcondv;
    --rcndv1;
    --rcdvin;
    --rconde;
    --rcnde1;
    --rcdein;
    --scale;
    --scale1;
    --result;
    --work;
    --rwork;

    /* Function Body */
/*     .. */
/*     .. Executable Statements .. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "VX", (ftnlen)2, (ftnlen)2);

/*     Check for errors */

    ntestt = 0;
    ntestf = 0;
    *info = 0;

/*     Important constants */

    badnn = FALSE_;

/*     7 is the largest dimension in the input file of precomputed */
/*     problems */

    nmax = 7;
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

/*     Check for errors */

    if (*nsizes < 0) {
	*info = -1;
    } else if (badnn) {
	*info = -2;
    } else if (*ntypes < 0) {
	*info = -3;
    } else if (*thresh < 0.) {
	*info = -6;
    } else if (*lda < 1 || *lda < nmax) {
	*info = -10;
    } else if (*ldvl < 1 || *ldvl < nmax) {
	*info = -15;
    } else if (*ldvr < 1 || *ldvr < nmax) {
	*info = -17;
    } else if (*ldlre < 1 || *ldlre < nmax) {
	*info = -19;
    } else /* if(complicated condition) */ {
/* Computing 2nd power */
	i__1 = nmax;
	if (nmax * 6 + (i__1 * i__1 << 1) > *nwork) {
	    *info = -30;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZDRVVX", &i__1);
	return 0;
    }

/*     If nothing to do check on NIUNIT */

    if (*nsizes == 0 || *ntypes == 0) {
	goto L160;
    }

/*     More Important constants */

    unfl = dlamch_("Safe minimum");
    ovfl = 1. / unfl;
    dlabad_(&unfl, &ovfl);
    ulp = dlamch_("Precision");
    ulpinv = 1. / ulp;
    rtulp = sqrt(ulp);
    rtulpi = 1. / rtulp;

/*     Loop over sizes, types */

    nerrs = 0;

    i__1 = *nsizes;
    for (jsize = 1; jsize <= i__1; ++jsize) {
	n = nn[jsize];
	if (*nsizes != 1) {
	    mtypes = min(21,*ntypes);
	} else {
	    mtypes = min(22,*ntypes);
	}

	i__2 = mtypes;
	for (jtype = 1; jtype <= i__2; ++jtype) {
	    if (! dotype[jtype]) {
		goto L140;
	    }

/*           Save ISEED in case of an error. */

	    for (j = 1; j <= 4; ++j) {
		ioldsd[j - 1] = iseed[j];
/* L20: */
	    }

/*           Compute "A" */

/*           Control parameters: */

/*           KMAGN  KCONDS  KMODE        KTYPE */
/*       =1  O(1)   1       clustered 1  zero */
/*       =2  large  large   clustered 2  identity */
/*       =3  small          exponential  Jordan */
/*       =4                 arithmetic   diagonal, (w/ eigenvalues) */
/*       =5                 random log   symmetric, w/ eigenvalues */
/*       =6                 random       general, w/ eigenvalues */
/*       =7                              random diagonal */
/*       =8                              random symmetric */
/*       =9                              random general */
/*       =10                             random triangular */

	    if (mtypes > 21) {
		goto L90;
	    }

	    itype = ktype[jtype - 1];
	    imode = kmode[jtype - 1];

/*           Compute norm */

	    switch (kmagn[jtype - 1]) {
		case 1:  goto L30;
		case 2:  goto L40;
		case 3:  goto L50;
	    }

L30:
	    anorm = 1.;
	    goto L60;

L40:
	    anorm = ovfl * ulp;
	    goto L60;

L50:
	    anorm = unfl * ulpinv;
	    goto L60;

L60:

	    zlaset_("Full", lda, &n, &c_b1, &c_b1, &a[a_offset], lda);
	    iinfo = 0;
	    cond = ulpinv;

/*           Special Matrices -- Identity & Jordan block */

/*              Zero */

	    if (itype == 1) {
		iinfo = 0;

	    } else if (itype == 2) {

/*              Identity */

		i__3 = n;
		for (jcol = 1; jcol <= i__3; ++jcol) {
		    i__4 = jcol + jcol * a_dim1;
		    a[i__4].r = anorm, a[i__4].i = 0.;
/* L70: */
		}

	    } else if (itype == 3) {

/*              Jordan Block */

		i__3 = n;
		for (jcol = 1; jcol <= i__3; ++jcol) {
		    i__4 = jcol + jcol * a_dim1;
		    a[i__4].r = anorm, a[i__4].i = 0.;
		    if (jcol > 1) {
			i__4 = jcol + (jcol - 1) * a_dim1;
			a[i__4].r = 1., a[i__4].i = 0.;
		    }
/* L80: */
		}

	    } else if (itype == 4) {

/*              Diagonal Matrix, [Eigen]values Specified */

		zlatms_(&n, &n, "S", &iseed[1], "H", &rwork[1], &imode, &cond, 
			 &anorm, &c__0, &c__0, "N", &a[a_offset], lda, &work[
			n + 1], &iinfo);

	    } else if (itype == 5) {

/*              Symmetric, eigenvalues specified */

		zlatms_(&n, &n, "S", &iseed[1], "H", &rwork[1], &imode, &cond, 
			 &anorm, &n, &n, "N", &a[a_offset], lda, &work[n + 1], 
			 &iinfo);

	    } else if (itype == 6) {

/*              General, eigenvalues specified */

		if (kconds[jtype - 1] == 1) {
		    conds = 1.;
		} else if (kconds[jtype - 1] == 2) {
		    conds = rtulpi;
		} else {
		    conds = 0.;
		}

		zlatme_(&n, "D", &iseed[1], &work[1], &imode, &cond, &c_b2, 
			" ", "T", "T", "T", &rwork[1], &c__4, &conds, &n, &n, 
			&anorm, &a[a_offset], lda, &work[(n << 1) + 1], &
			iinfo);

	    } else if (itype == 7) {

/*              Diagonal, random eigenvalues */

		zlatmr_(&n, &n, "D", &iseed[1], "S", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &c__0, &
			c__0, &c_b49, &anorm, "NO", &a[a_offset], lda, idumma, 
			 &iinfo);

	    } else if (itype == 8) {

/*              Symmetric, random eigenvalues */

		zlatmr_(&n, &n, "D", &iseed[1], "H", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &n, &n, &
			c_b49, &anorm, "NO", &a[a_offset], lda, idumma, &
			iinfo);

	    } else if (itype == 9) {

/*              General, random eigenvalues */

		zlatmr_(&n, &n, "D", &iseed[1], "N", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &n, &n, &
			c_b49, &anorm, "NO", &a[a_offset], lda, idumma, &
			iinfo);
		if (n >= 4) {
		    zlaset_("Full", &c__2, &n, &c_b1, &c_b1, &a[a_offset], 
			    lda);
		    i__3 = n - 3;
		    zlaset_("Full", &i__3, &c__1, &c_b1, &c_b1, &a[a_dim1 + 3]
, lda);
		    i__3 = n - 3;
		    zlaset_("Full", &i__3, &c__2, &c_b1, &c_b1, &a[(n - 1) * 
			    a_dim1 + 3], lda);
		    zlaset_("Full", &c__1, &n, &c_b1, &c_b1, &a[n + a_dim1], 
			    lda);
		}

	    } else if (itype == 10) {

/*              Triangular, random eigenvalues */

		zlatmr_(&n, &n, "D", &iseed[1], "N", &work[1], &c__6, &c_b39, 
			&c_b2, "T", "N", &work[n + 1], &c__1, &c_b39, &work[(
			n << 1) + 1], &c__1, &c_b39, "N", idumma, &n, &c__0, &
			c_b49, &anorm, "NO", &a[a_offset], lda, idumma, &
			iinfo);

	    } else {

		iinfo = 1;
	    }

	    if (iinfo != 0) {
		io___32.ciunit = *nounit;
		s_wsfe(&io___32);
		do_fio(&c__1, "Generator", (ftnlen)9);
		do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(iinfo);
		return 0;
	    }

L90:

/*           Test for minimal and generous workspace */

	    for (iwk = 1; iwk <= 3; ++iwk) {
		if (iwk == 1) {
		    nnwork = n << 1;
		} else if (iwk == 2) {
/* Computing 2nd power */
		    i__3 = n;
		    nnwork = (n << 1) + i__3 * i__3;
		} else {
/* Computing 2nd power */
		    i__3 = n;
		    nnwork = n * 6 + (i__3 * i__3 << 1);
		}
		nnwork = max(nnwork,1);

/*              Test for all balancing options */

		for (ibal = 1; ibal <= 4; ++ibal) {
		    *(unsigned char *)balanc = *(unsigned char *)&bal[ibal - 
			    1];

/*                 Perform tests */

		    zget23_(&c_false, &c__0, balanc, &jtype, thresh, ioldsd, 
			    nounit, &n, &a[a_offset], lda, &h__[h_offset], &w[
			    1], &w1[1], &vl[vl_offset], ldvl, &vr[vr_offset], 
			    ldvr, &lre[lre_offset], ldlre, &rcondv[1], &
			    rcndv1[1], &rcdvin[1], &rconde[1], &rcnde1[1], &
			    rcdein[1], &scale[1], &scale1[1], &result[1], &
			    work[1], &nnwork, &rwork[1], info);

/*                 Check for RESULT(j) > THRESH */

		    ntest = 0;
		    nfail = 0;
		    for (j = 1; j <= 9; ++j) {
			if (result[j] >= 0.) {
			    ++ntest;
			}
			if (result[j] >= *thresh) {
			    ++nfail;
			}
/* L100: */
		    }

		    if (nfail > 0) {
			++ntestf;
		    }
		    if (ntestf == 1) {
			io___39.ciunit = *nounit;
			s_wsfe(&io___39);
			do_fio(&c__1, path, (ftnlen)3);
			e_wsfe();
			io___40.ciunit = *nounit;
			s_wsfe(&io___40);
			e_wsfe();
			io___41.ciunit = *nounit;
			s_wsfe(&io___41);
			e_wsfe();
			io___42.ciunit = *nounit;
			s_wsfe(&io___42);
			e_wsfe();
			io___43.ciunit = *nounit;
			s_wsfe(&io___43);
			do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(
				doublereal));
			e_wsfe();
			ntestf = 2;
		    }

		    for (j = 1; j <= 9; ++j) {
			if (result[j] >= *thresh) {
			    io___44.ciunit = *nounit;
			    s_wsfe(&io___44);
			    do_fio(&c__1, balanc, (ftnlen)1);
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&iwk, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&result[j], (ftnlen)sizeof(
				    doublereal));
			    e_wsfe();
			}
/* L110: */
		    }

		    nerrs += nfail;
		    ntestt += ntest;

/* L120: */
		}
/* L130: */
	    }
L140:
	    ;
	}
/* L150: */
    }

L160:

/*     Read in data from file to check accuracy of condition estimation. */
/*     Assume input eigenvalues are sorted lexicographically (increasing */
/*     by real part, then decreasing by imaginary part) */

    jtype = 0;
L170:
    io___45.ciunit = *niunit;
    i__1 = s_rsle(&io___45);
    if (i__1 != 0) {
	goto L220;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L220;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&isrt, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L220;
    }
    i__1 = e_rsle();
    if (i__1 != 0) {
	goto L220;
    }

/*     Read input data until N=0 */

    if (n == 0) {
	goto L220;
    }
    ++jtype;
    iseed[1] = jtype;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___48.ciunit = *niunit;
	s_rsle(&io___48);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&a[i__ + j * a_dim1], (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L180: */
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___49.ciunit = *niunit;
	s_rsle(&io___49);
	do_lio(&c__5, &c__1, (char *)&wr, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&wi, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&rcdein[i__], (ftnlen)sizeof(doublereal))
		;
	do_lio(&c__5, &c__1, (char *)&rcdvin[i__], (ftnlen)sizeof(doublereal))
		;
	e_rsle();
	i__2 = i__;
	z__1.r = wr, z__1.i = wi;
	w1[i__2].r = z__1.r, w1[i__2].i = z__1.i;
/* L190: */
    }
/* Computing 2nd power */
    i__2 = n;
    i__1 = n * 6 + (i__2 * i__2 << 1);
    zget23_(&c_true, &isrt, "N", &c__22, thresh, &iseed[1], nounit, &n, &a[
	    a_offset], lda, &h__[h_offset], &w[1], &w1[1], &vl[vl_offset], 
	    ldvl, &vr[vr_offset], ldvr, &lre[lre_offset], ldlre, &rcondv[1], &
	    rcndv1[1], &rcdvin[1], &rconde[1], &rcnde1[1], &rcdein[1], &scale[
	    1], &scale1[1], &result[1], &work[1], &i__1, &rwork[1], info);

/*     Check for RESULT(j) > THRESH */

    ntest = 0;
    nfail = 0;
    for (j = 1; j <= 11; ++j) {
	if (result[j] >= 0.) {
	    ++ntest;
	}
	if (result[j] >= *thresh) {
	    ++nfail;
	}
/* L200: */
    }

    if (nfail > 0) {
	++ntestf;
    }
    if (ntestf == 1) {
	io___52.ciunit = *nounit;
	s_wsfe(&io___52);
	do_fio(&c__1, path, (ftnlen)3);
	e_wsfe();
	io___53.ciunit = *nounit;
	s_wsfe(&io___53);
	e_wsfe();
	io___54.ciunit = *nounit;
	s_wsfe(&io___54);
	e_wsfe();
	io___55.ciunit = *nounit;
	s_wsfe(&io___55);
	e_wsfe();
	io___56.ciunit = *nounit;
	s_wsfe(&io___56);
	do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	e_wsfe();
	ntestf = 2;
    }

    for (j = 1; j <= 11; ++j) {
	if (result[j] >= *thresh) {
	    io___57.ciunit = *nounit;
	    s_wsfe(&io___57);
	    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&result[j], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
/* L210: */
    }

    nerrs += nfail;
    ntestt += ntest;
    goto L170;
L220:

/*     Summary */

    dlasum_(path, nounit, &nerrs, &ntestt);



    return 0;

/*     End of ZDRVVX */

} /* zdrvvx_ */
