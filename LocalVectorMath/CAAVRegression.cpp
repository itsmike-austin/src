#define __ADVANCED_ALIGNED_LIB

#include <CVector.h>
#include <stdio.h>

// TBD:
// XXX Add cross and then angle elements after standard vec4 elements
// XXX: Repair (m4d = m4inverse(m4e);)
// XXX: Transpose (m2transpose vs. m3transpose vs transpose)
// XXX: DETERMINE IF METHODS LIKE m2transpose SHOULD BE REDUCED TO JUST transpose(v2);
// XXX: Review [] methods in array elements for single element return
// XXX: Add null constructors for v2array,v2buf,v3array,v3buf,v4...

char* ErrMsg[] = {
  "subtract error\0" ,
  "sum error\0" ,
  "product error\0" ,
  "division error\0",
  "sum/float error\0",
  "sub/float error\0",
  "mul/float error\0",
  "div/float error\0",
  "dot error\0",
  "lerp error\0",
  "sqr error\0",
  "normalize error\0",
  "cross error\0",
  "length error\0",
  "negation error\0",
  "transpose error\0",
  "function error\0",
};

/* -----------------------------------------------------------
 * Error message pointer list
 * ----------------------------------------------------------- */

#define SUB_ERROR        0
#define SUM_ERROR        1
#define MUL_ERROR        2
#define DIV_ERROR        3
#define SUM_FLOAT_ERROR  4
#define SUB_FLOAT_ERROR  5
#define MUL_FLOAT_ERROR  6
#define DIV_FLOAT_ERROR  7
#define DOT_ERROR        8
#define LERP_ERROR       9
#define SQR_ERROR       10
#define NRM_ERROR       11
#define CRS_ERROR       12
#define LTH_ERROR       13
#define NEG_ERROR       14
#define TRANS_ERROR     15
#define FCN_ERROR       16

/* -----------------------------------------------------------
 * Regression test convenience macro
 * ----------------------------------------------------------- */

#define TestResult(op,res,expct,lgth,hdr,msg)	\
  op; \
  if ( memcmp((void*)&res,(void*)&expct,lgth) )	\
    fprintf(stderr,"op :"#hdr": "#op" FAILED: %s\n",ErrMsg[msg]); \
  else \
    fprintf(stdout,"op :"#hdr": "#op": OK\n");

/* -----------------------------------------------------------
 * Float Results
 * ----------------------------------------------------------- */

float fResults[] = {
  5.0f,
  2.2360680103302002,
};

/* -----------------------------------------------------------
 * v2 Results
 * ----------------------------------------------------------- */

vec2 v2Results[] = {
  { 1.0, 2.0 },
  { 3.0, 4.0 },
  { 2.0, 4.0 },
  { 1.0, 4.0 },
  { 3.0, 2.0 },
  {-1.0,-2.0 },
  { 0.44721359014511108, 0.89442718029022217 },
  { 0.0, 1.0 },
  { 3.0, 2.0 },
  { 5.0,11.0 },
  {   3.0,   4.0 }, {   5.0,   6.0 }, {   4.0,   6.0 }, {   3.0,   6.0 }, {   5.0,   4.0 }, {   1.0,   0.0 }, // 10-15
  {   2.0,   4.0 }, {   6.0,   8.0 }, {   4.0,   8.0 }, {   2.0,   8.0 }, {   6.0,   4.0 }, {  -2.0,  -4.0 }, // 16-21
  {   2.0,   4.0 }, {   4.0,   6.0 }, {   3.0,   6.0 }, {   2.0,   6.0 }, {   4.0,   4.0 }, {   0.0,   0.0 }, // 22-27
  {   1.0,   4.0 }, {   3.0,   8.0 }, {   2.0,   8.0 }, {   1.0,   8.0 }, {   3.0,   4.0 }, {  -1.0,  -4.0 }, // 28-33
  {   1.0,   4.0 }, {   9.0,  16.0 }, {   4.0,  16.0 }, {   1.0,  16.0 }, {   9.0,   4.0 }, {   1.0,   4.0 }, // 34-39
  {   5.0,  11.0 }, {  11.0,  25.0 }, {  10.0,  22.0 }, {   9.0,  19.0 }, {   7.0,  17.0 }, {  -5.0, -11.0 }, // 40-45
};

/* -----------------------------------------------------------
 * v3 Results
 * ----------------------------------------------------------- */

vec3 v3Results[] = {
  { 1.0, 2.0, 3.0 },
  { 3.0, 4.0, 5.0 },
  { 2.0, 4.0, 6.0 },
  { 1.0, 4.0, 9.0 },
  { 3.0, 2.0, 3.0 },
  {14.0,32.0,50.0 },
  {   3.0,   4.0,   5.0,   0.0 }, {   5.0,   6.0,   7.0,   0.0 }, {   4.0,   6.0,     8.0,   0.0 }, //  6-11
  {   3.0,   6.0,  11.0,   0.0 }, {   5.0,   4.0,   5.0,   0.0 }, {  16.0,  34.0,    52.0,   0.0 },
  {   2.0,   4.0,   6.0,   0.0 }, {   6.0,   8.0,  10.0,   0.0 }, {   4.0,   8.0,    12.0,   0.0 }, // 12-17
  {   2.0,   8.0,  18.0,   0.0 }, {   6.0,   4.0,   6.0,   0.0 }, {  28.0,  64.0,   100.0,   0.0 },
  {   2.0,   4.0,   6.0,   0.0 }, {   4.0,   6.0,   8.0,   0.0 }, {   3.0,   6.0,     9.0,   0.0 }, // 18-23
  {   2.0,   6.0,  12.0,   0.0 }, {   4.0,   4.0,   6.0,   0.0 }, {  15.0,  34.0,    53.0,   0.0 },
  {   1.0,   4.0,   9.0,   0.0 }, {   3.0,   8.0,  15.0,   0.0 }, {   2.0,   8.0,    18.0,   0.0 }, // 24-29
  {   1.0,   8.0,  27.0,   0.0 }, {   3.0,   4.0,   9.0,   0.0 }, {  14.0,  64.0,   150.0,   0.0 },
  {   1.0,   4.0,   9.0,   0.0 }, {   9.0,  16.0,  25.0,   0.0 }, {   4.0,   16.0,   36.0,   0.0 }, // 30-35
  {   1.0,  16.0,  81.0,   0.0 }, {   9.0,   4.0,   9.0,   0.0 }, { 196.0, 1024.0, 2500.0,   0.0 },
  {  14.0,  32.0,  50.0,   0.0 }, {  26.0,  62.0,  98.0,   0.0 }, {  28.0,  64.0,   100.0,   0.0 }, // 36-41
  {  36.0,  78.0, 120.0,   0.0 }, {  16.0,  40.0,  64.0,   0.0 }, { 228.0, 516.0,   804.0,   0.0 },
  {   2.0,  4.0,    6.0,   0.0 }, {   3.0,   4.0,   5.0,   0.0 }, {   2.0,   4.0,     6.0,   0.0 }, // 42-47
  {   1.0,  4.0,    9.0,   0.0 }, {   3.0,   2.0,   3.0,   0.0 }, {  14.0,  32.0,    50.0,   0.0 },
};

/* -----------------------------------------------------------
 * v4 Results
 * ----------------------------------------------------------- */

vec4 v4Results[] = {
  {   1.0,   2.0,   3.0,   4.0 },
  {   3.0,   4.0,   5.0,   6.0 },
  {   2.0,   4.0,   6.0,   8.0 },
  {   1.0,   4.0,   9.0,  16.0 },
  {   3.0,   2.0,   3.0,   4.0 },
  {  30.0,  70.0, 110.0, 150.0 },
  {   3.0,    4.0,    5.0,    6.0 }, {   5.0,    6.0,    7.0,    8.0 }, {   4.0,    6.0,    8.0,   10.0 }, //  6-11
  {   3.0,    6.0,   11.0,   18.0 }, {   5.0,    4.0,    5.0,    6.0 }, {  32.0,   72.0,  112.0,  152.0 },
  {   2.0,    4.0,    6.0,    8.0 }, {   6.0,    8.0,   10.0,   12.0 }, {   4.0,    8.0,   12.0,   16.0 }, // 12-17
  {   2.0,    8.0,   18.0,   32.0 }, {   6.0,    4.0,    6.0,    8.0 }, {  60.0,  140.0,  220.0,  300.0 },
  {   2.0,    4.0,    6.0,    8.0 }, {   4.0,    6.0,    8.0,   10.0 }, {   3.0,    6.0,    9.0,   12.0 }, // 18-23
  {   2.0,    6.0,   12.0,   20.0 }, {   4.0,    4.0,    6.0,    8.0 }, {  31.0,   72.0,  113.0,  154.0 },
  {   1.0,    4.0,    9.0,   16.0 }, {   3.0,    8.0,   15.0,   24.0 }, {   2.0,    8.0,   18.0,   32.0 }, // 24-29
  {   1.0,    8.0,   27.0,   64.0 }, {   3.0,    4.0,    9.0,   16.0 }, {  30.0,  140.0,  330.0,  600.0 },
  {   1.0,    4.0,    9.0,   16.0 }, {   9.0,   16.0,   25.0,   36.0 }, {   4.0,   16.0,   36.0,   64.0 }, // 30-35
  {   1.0,   16.0,   81.0,  256.0 }, {   9.0,    4.0,    9.0,   16.0 }, { 900.0,  4900.0,  12100.0,  22500.0 },
  {  30.0,   70.0,  110.0,  150.0 }, {  50.0,  122.0,  194.0,  266.0 }, {  60.0,  140.0,  220.0,  300.0 }, // 36-41
  { 100.0,  220.0,  340.0,  460.0 }, {  32.0,   80.0,  128.0,  176.0 }, { 1100.0,  2540.0,  3980.0,  5420.0 },
  {   2.0,    4.0,    6.0,    8.0 }, {   3.0,    4.0,    5.0,    6.0 }, {   2.0,    4.0,    6.0,    8.0 }, // 42-47
  {   1.0,    4.0,    9.0,   16.0 }, {   3.0,    2.0,    3.0,    4.0 }, {  30.0,   70.0,  110.0,  150.0 },
  {   2.0,    4.0,    6.0,    8.0 }, {   3.0,    4.0,    5.0,    6.0 }, {   2.0,    4.0,    6.0,    8.0 }, // 48-53
  {   1.0,    4.0,    9.0,   16.0 }, {   3.0,    2.0,    3.0,    4.0 }, {  30.0,   70.0,  110.0,  150.0 },
};

/* -----------------------------------------------------------
 * m2 Results
 * ----------------------------------------------------------- */

mat2 m2Results[] = {
  { 1.0, 2.0, 3.0, 4.0 },    //  0
  { 1.0, 0.0, 0.0, 1.0 },    //  1
  { 3.0, 4.0, 5.0, 6.0 },    //  2
  { 2.0, 4.0, 6.0, 8.0 },    //  3
  { 7.0,10.0,15.0,22.0 },    //  4
  { 2.0, 2.0, 3.0, 4.0 },    //  5
  { 1.0, 3.0, 2.0, 4.0 },    //  6
  {  0.70710724592208862,
    -0.70710635185241699,
     0.70710635185241699,
     0.70710724592208862 },  //  7
  {  0.70710724592208862,
     0.70710635185241699,
     -0.70710635185241699,
     0.70710724592208862 },  //  8
  { 1.0, 0.0, 0.0, 2.0 },    //  9
  {-1.0,-2.0,-3.0,-4.0 },    // 10
};

/* -----------------------------------------------------------
 * m3 Results
 * ----------------------------------------------------------- */

mat3 m3Results[] = {
  {   1.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,    0.0,   0.0,   1.0,   0.0 }, //  0
  {   1.0,   2.0,   3.0,   0.0,    4.0,   5.0,   6.0,   0.0,    7.0,   8.0,   9.0,   0.0 }, //  1
  {   3.0,   4.0,   5.0,   0.0,    6.0,   7.0,   8.0,   0.0,    9.0,  10.0,  11.0,   0.0 }, //  2
  {   2.0,   4.0,   6.0,   0.0,    8.0,  10.0,  12.0,   0.0,   14.0,  16.0,  18.0,   0.0 }, //  3
  {  30.0,  36.0,  42.0,   0.0,   66.0,  81.0,  96.0,   0.0,  102.0, 126.0, 150.0,   0.0 }, //  4
  {   3.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,    0.0,   0.0,   1.0,   0.0 }, //  5
  {  0.0, 0.36358642578125, -0.0908966064453125, 0.0, -1.999725341796875, -1.3634490966796875,
     2.0906219482421875, 0.0, 0.9998626708984375, 0.2726898193359375, -0.8180694580078125,  0.0 }, // 6
  {   1.0,   4.0,   7.0,   0.0,    2.0,   5.0,   8.0,   0.0,    3.0,   6.0,   9.0,   0.0 }, //  7
  {  -1.0,  -2.0,  -3.0,   0.0,   -4.0,  -5.0,  -6.0,   0.0,   -7.0,  -8.0,  -9.0,   0.0 }, //  8
  {  1.0,  0.0,  0.0,  0.0,  0.0,  0.70710724592208862, -0.70710635185241699,  0.0,  0.0,  0.70710635185241699,  0.70710724592208862,  0.0 }, //  9
  {  1.0,  0.0,  0.0,  0.0,  0.0,  0.70710724592208862,  0.70710635185241699,  0.0,  0.0, -0.70710635185241699,  0.70710724592208862,  0.0 }, // 10
  {  0.86602562665939331, 0.0, 0.49999961256980896, 0.0, 0.0, 1.0, 0.0, 0.0, -0.49999961256980896, 0.0, 0.86602562665939331, 0.0 },           // 11
  {  0.86602562665939331, 0.0, -0.49999961256980896, 0.0, 0.0, 1.0, 0.0, 0.0, 0.49999961256980896, 0.0, 0.86602562665939331, 0.0 },           // 12
  {  0.50000077486038208, -0.86602497100830078, 0.0, 0.0, 0.86602497100830078, 0.50000077486038208, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },           // 13
  {  0.50000077486038208, 0.86602497100830078, 0.0, 0.0, -0.86602497100830078, 0.50000077486038208, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },           // 14
  {  0.86602562665939331, 0.0, 0.49999961256980896, 0.0, 0.35355287790298462, 0.70710724592208862, -0.61237221956253052, 0.0, -0.35355332493782043, 0.70710635185241699, 0.6123729944229126, 0.0 },  // 15
  {  0.86602562665939331, 0.0, -0.49999961256980896, 0.0, 0.35355287790298462, 0.70710724592208862, 0.61237221956253052, 0.0, 0.35355332493782043, -0.70710635185241699, 0.6123729944229126, 0.0 },  // 16
  {  0.50000077486038208, -0.86602497100830078, 0.0, 0.0, 0.61237251758575439, 0.35355418920516968, -0.70710635185241699, 0.0, 0.61237174272537231, 0.35355374217033386, 0.70710724592208862, 0.0 }, // 17
  {  0.50000077486038208, 0.86602497100830078, 0.0, 0.0, -0.61237251758575439, 0.35355418920516968, 0.70710635185241699, 0.0, 0.61237174272537231, -0.35355374217033386, 0.70710724592208862, 0.0 }, // 18
  {  0.43301349878311157, -0.74999982118606567, 0.49999961256980896, 0.0, 0.86602497100830078, 0.50000077486038208, 0.0, 0.0, -0.25000020861625671, 0.43301212787628174, 0.86602562665939331, 0.0 }, // 19
  {  0.43301349878311157, 0.74999982118606567, -0.49999961256980896, 0.0, -0.86602497100830078, 0.50000077486038208, 0.0, 0.0, 0.25000020861625671, 0.43301212787628174, 0.86602562665939331, 0.0 }, // 20
  {  0.43301349878311157, -0.74999982118606567, 0.49999961256980896, 0.0, 0.78914922475814819, 0.04736856743693351, -0.61237221956253052, 0.0, 0.43559476733207703, 0.65973973274230957, 0.61237299442291260,  0.0 },  // 21
  {  0.43301349878311157, 0.74999982118606567, -0.49999961256980896, 0.0, -0.43559578061103821, 0.60355365276336670, 0.61237221956253052, 0.0, 0.78914868831634521, -0.047367729246616364, 0.61237299442291260, 0.0 }, // 22
  {   1.0,   0.0,   0.0,   0.0,    0.0,   2.0,   0.0,   0.0,    0.0,   0.0,   3.0,   0.0 }, // 23
  {   1.0,   2.0,   3.0,   0.0,    5.0,   6.0,   7.0,   0.0,    9.0,  10.0,  11.0,   0.0 }, // 24
  { -25.0,  -2.0,  10.0,   0.0,   10.0, -19.0,  10.0,   0.0,    2.0,  14.0,  -9.0,   0.0 }, // 25
};

/* -----------------------------------------------------------
 * m4 Results
 * ----------------------------------------------------------- */

mat4 m4Results[] = {
  {   1.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, //  0
  {   1.0,   2.0,   3.0,   4.0,    5.0,   6.0,   7.0,   8.0,   9.0,  10.0,  11.0,  12.0,  13.0,  14.0,  15.0,  16.0 }, //  1
  {   3.0,   4.0,   5.0,   6.0,    7.0,   8.0,   9.0,  10.0,  11.0,  12.0,  13.0,  14.0,  15.0,  16.0,  17.0,  18.0 }, //  2
  {   2.0,   4.0,   6.0,   8.0,   10.0,  12.0,  14.0,  16.0,  18.0,  20.0,  22.0,  24.0,  26.0,  28.0,  30.0,  32.0 }, //  3
  {  90.0, 100.0, 110.0, 120.0,  202.0, 228.0, 254.0, 280.0, 314.0, 356.0, 398.0, 440.0, 426.0, 484.0, 542.0, 600.0 }, //  4
  {   3.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, //  5
  {   1.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, //  6
  {   1.0,   5.0,   9.0,  13.0,    2.0,   6.0,  10.0,  14.0,   3.0,   7.0,  11.0,  15.0,   4.0,   8.0,  12.0,  16.0 }, //  7
  {  -1.0,  -2.0,  -3.0,  -4.0,   -5.0,  -6.0,  -7.0,  -8.0,  -9.0, -10.0, -11.0, -12.0, -13.0, -14.0, -15.0, -16.0 }, //  8
  {  25.0,  -6.0,  -9.0,  -6.0,   -4.0,  20.0, -12.0,  -8.0,  -5.0, -10.0,  13.0, -10.0,  -1.0,  -2.0,  -3.0,  26.0 }, //  9
  {   1.0,   2.0,   3.0,   4.0,    5.0,   6.0,   7.0,   8.0,  11.0,  12.0,  13.0,  14.0,  13.0,  14.0,  15.0,  16.0 }, // 10
  {   0.40824833512306213,  -0.7071068286895752,  -0.57735025882720947,   0.0,
     -0.81649667024612427,   0.0,  -0.57735025882720947,   0.0,
      0.40824833512306213,   0.70710682868957520,  -0.57735025882720947,   0.0,
     -0.0,  -1.41421365737915040,   6.92820310592651370,   1.0 },                                                      // 11
  {   1.0,   0.0,   0.0,   0.0,    0.0,   2.0,   0.0,   0.0,   0.0,   0.0,   3.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 12
  {   1.0,   0.0,   0.0,   0.0,   0.0,  0.70710724592208862,  -0.70710635185241699,  0.0,
      0.0,  0.70710635185241699,  0.70710724592208862,  0.0,  0.0,  0.0,  0.0,  1.0 },                                 // 13
  {   1.0,  0.0,  0.0,  0.0,  0.0,  0.70710724592208862,  0.70710635185241699,  0.0,  0.0,
      -0.70710635185241699,  0.70710724592208862,  0.0,  0.0,  0.0,  0.0,  1.0 },                                      // 14
  {   0.86602562665939331,  0.0,  0.49999961256980896,  0.0,  0.0,  1.0,  0.0,  0.0,
      -0.49999961256980896,  0.0,  0.86602562665939331,  0.0,  0.0,  0.0,  0.0,  1.0 },                                // 15
  {   0.86602562665939331,  0.0,  -0.49999961256980896,  0.0,  0.0,  1.0,  0.0,  0.0,
      0.49999961256980896,  0.0,  0.86602562665939331,  0.0,  0.0,  0.0,  0.0,  1.0 },                                 // 16
  {   0.50000077486038208,  -0.86602497100830078,  0.0,  0.0,  0.86602497100830078,  0.50000077486038208,
      0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  0.0,  0.0,  0.0,  1.0 },                                                     // 17
  {   0.50000077486038208,  0.86602497100830078,  0.0,  0.0,  -0.86602497100830078,  0.50000077486038208,
      0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  0.0,  0.0,  0.0,  1.0 },                                                     // 18
  {   0.86602562665939331,  0.0,  0.49999961256980896,  0.0,  0.35355287790298462,  0.70710724592208862,
      -0.61237221956253052,  0.0,  -0.35355332493782043,  0.70710635185241699,  0.61237299442291260,  0.0,
      0.0,  0.0,  0.0,  1.0 },                                                                                         // 19
  {   0.86602562665939331,  0.0,  -0.49999961256980896,  0.0,  0.35355287790298462,  0.70710724592208862,
      0.61237221956253052,  0.0,  0.35355332493782043,  -0.70710635185241699,  0.6123729944229126,
      0.0,  0.0,  0.0,  0.0,  1.0 },                                                                                   // 20
  {   0.50000077486038208,  -0.86602497100830078,  0.0,  0.0,  0.61237251758575439,  0.35355418920516968,
      -0.70710635185241699,  0.0,  0.61237174272537231,  0.35355374217033386,  0.70710724592208862,
      0.0,  0.0,  0.0,  0.0,  1.0 },                                                                                   // 21
  {   0.50000077486038208,  0.86602497100830078,  0.0,  0.0,  -0.61237251758575439,  0.35355418920516968,
      0.70710635185241699,  0.0,  0.61237174272537231,  -0.35355374217033386,  0.70710724592208862,
      0.0,  0.0,  0.0,  0.0,  1.0 },                                                                                   // 22
  {   0.43301349878311157,  -0.74999982118606567,  0.49999961256980896,  0.0,  0.86602497100830078,
      0.50000077486038208,  0.0,  0.0,  -0.25000020861625671,  0.43301212787628174,  0.86602562665939331,
      0.0,  0.0,  0.0,  0.0,  1.0 },                                                                                   // 23
  {   0.43301349878311157,  0.74999982118606567,  -0.49999961256980896,  0.0,  -0.86602497100830078,
      0.50000077486038208,  0.0,  0.0,  0.25000020861625671,  0.43301212787628174,  0.86602562665939331,
      0.0,  0.0,  0.0,  0.0,  1.0 },                                                                                   // 24
  {   0.43301349878311157,  -0.74999982118606567,  0.49999961256980896,  0.0,  0.78914922475814819,
      0.047368567436933517,  -0.61237221956253052,  0.0,  0.43559476733207703,  0.65973973274230957,
      0.6123729944229126, 0.0,  0.0,  0.0,  0.0,  1.0 },                                                               // 25
  {   0.43301349878311157,  0.74999982118606567,  -0.49999961256980896,  0.0,  -0.43559578061103821,
      0.6035536527633667,  0.61237221956253052,  0.0,  0.78914868831634521,  -0.047367729246616364,
      0.6123729944229126,  0.0,  0.0,  0.0,  0.0,  1.0 },                                                              // 26
  {   1.0,   0.0,   0.0,   1.0,    0.0,   1.0,   0.0,   2.0,   0.0,   0.0,   1.0,   3.0,   0.0,   0.0,   0.0,   1.0 }, // 27
  {   1.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   1.0,   2.0,   3.0,   1.0 }, // 28
  {   1.0,   0.0,   0.0,  -0.0,    0.0,  -1.0,   0.0,   0.0,   0.0,   0.0,  -0.086956523358821869,
      -0.73913043737411499,        0.0,   0.0,   0.0,   1.0 },                                                         // 29
  {   1.0,   0.0,   0.0,  -0.0,    0.0,  -1.0,   0.0,   0.0,   0.0,   0.0,  -0.043478261679410934,
      0.1304347813129425,  0.0,    0.0,   0.0,   1.0 },                                                                // 30
  { 2.4142158031463623,    0.0,    0.0,   0.0,   0.0,  2.4142158031463623,    0.0,  0.0,   0.0,   0.0,
    0.66666668653488159,  6.6666665077209473,    0.0,   0.0,   1.0,   0.0 },                                           // 31
  { 2.4142158031463623,    0.0,    0.0,   0.0,   0.0,  2.4142158031463623,    0.0,  0.0,   0.0,   0.0,
    0.83333337306976318,  3.3333332538604736,    0.0,   0.0,   1.0,   0.0 },                                           // 32
  {   0.0,   0.0,  -1.0,   0.0,    0.0,   1.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 33
  {   0.0,   0.0,   1.0,   0.0,    0.0,   1.0,   0.0,   0.0,  -1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 34
  {   1.0,   0.0,   0.0,   0.0,    0.0,   0.0,  -1.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 35
  {   1.0,   0.0,   0.0,   0.0,    0.0,   0.0,   1.0,   0.0,   0.0,  -1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 36
  {  -1.0,   0.0,   0.0,   0.0,    0.0,   1.0,   0.0,   0.0,   0.0,   0.0,  -1.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 37
  {   1.0,   2.0,   3.0,   0.0,    4.0,   5.0,   6.0,   0.0,   7.0,   8.0,   9.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 38
  { -25.0,  -2.0,  10.0,   0.0,   10.0, -19.0,  10.0,   0.0,   2.0,  14.0,  -9.0,   0.0,   0.0,   0.0,   0.0,   1.0 }, // 39
};

/* -----------------------------------------------------------
 * quaternion Results
 * ----------------------------------------------------------- */

quaternion qResults[] = {
  {   1.0,   2.0,   3.0,   1.0 }, // 0
  {   2.0,   4.0,   6.0, -13.0 }, // 1
  {  -1.0,  -2.0,  -3.0,   1.0 }, // 2
  {  -1.0,  -2.0,  -3.0,   1.0 }, // 3
  {   2.0,   2.0,   3.0,   1.0 }, // 4
  {   0.25, -0.5,   0.25,  2.0 }, // 5
  { 0.34412360191345215, -0.6882472038269043,  0.34412360191345215, 2.1794495582580566  }, // 6
  { 0.10227636992931366,  0.20455273985862732, 0.30682912468910217, 0.92387968301773071 }, // 7
};

int main()
{
  float fr;

  v2 v2a(1.0,2.0);
  v2 v2b(1.0,2.0);
  v2 v2c;
  v2 v2d;

  fprintf(stdout,"----------------------> v2 Operations\n");

  TestResult(v2a += 2.0,                           *(v2a.vec),v2Results[1], sizeof(vec2), "v2 += float                          ",FCN_ERROR);
  TestResult(v2a -= 2.0,                           *(v2a.vec),v2Results[0], sizeof(vec2), "v2 -= float                          ",FCN_ERROR);
  TestResult(v2a *= 2.0,                           *(v2a.vec),v2Results[2], sizeof(vec2), "v2 *= float                          ",FCN_ERROR);
  TestResult(v2a /= 2.0,                           *(v2a.vec),v2Results[0], sizeof(vec2), "v2 /= float                          ",FCN_ERROR);
  TestResult(v2a += v2b,                           *(v2a.vec),v2Results[2], sizeof(vec2), "v2 += v2                             ",FCN_ERROR);
  TestResult(v2a -= v2b,                           *(v2a.vec),v2Results[0], sizeof(vec2), "v2 -= v2                             ",FCN_ERROR);
  TestResult(v2a *= v2b,                           *(v2a.vec),v2Results[3], sizeof(vec2), "v2 *- v2                             ",FCN_ERROR);
  TestResult(v2a /= v2b,                           *(v2a.vec),v2Results[0], sizeof(vec2), "v2 /= v2                             ",FCN_ERROR);
  TestResult(v2a += *(v2b.vec),                    *(v2a.vec),v2Results[2], sizeof(vec2), "v2a += vec2                          ",FCN_ERROR);
  TestResult(v2a -= *(v2b.vec),                    *(v2a.vec),v2Results[0], sizeof(vec2), "v2a -= vec2                          ",FCN_ERROR);
  TestResult(v2a *= *(v2b.vec),                    *(v2a.vec),v2Results[3], sizeof(vec2), "v2a *= vec2                          ",FCN_ERROR);
  TestResult(v2a /= *(v2b.vec),                    *(v2a.vec),v2Results[0], sizeof(vec2), "v2a /= vec2                          ",FCN_ERROR);
  TestResult(v2a->x = 3.0,                         *(v2a.vec),v2Results[4], sizeof(vec2), "v2a->x = f                           ",FCN_ERROR);
  TestResult(v2d=v2a,                              *(v2d.vec),v2Results[4], sizeof(vec2), "v2d=v2a                              ",FCN_ERROR);
  v2a->x = 1.0;
  TestResult(copy(v2c,v2a),                        *(v2c.vec),v2Results[0], sizeof(vec2), "copy(v2,v2)                          ",FCN_ERROR);
  TestResult(v2d=v2a+2.0,                          *(v2d.vec),v2Results[1], sizeof(vec2), "v2d=v2a+2.0                          ",FCN_ERROR);
  TestResult(v2d=v2d-2.0,                          *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=v2d-2.0                          ",FCN_ERROR);
  TestResult(v2d=v2a*2.0,                          *(v2d.vec),v2Results[2], sizeof(vec2), "v2d=v2a*2.0                          ",FCN_ERROR);
  TestResult(v2d=v2d/2.0,                          *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=v2d/2.0                          ",FCN_ERROR);
  TestResult(v2d=2.0*v2a,                          *(v2d.vec),v2Results[2], sizeof(vec2), "v2d=2.0*v2d                          ",FCN_ERROR);
  v2d /= 2.0;
  TestResult(v2d=-v2a,                             *(v2d.vec),v2Results[5], sizeof(vec2), "v2d=-v2a                             ",FCN_ERROR);
  TestResult(v2d=v2a+v2b,                          *(v2d.vec),v2Results[2], sizeof(vec2), "v2d=v2a+v2b                          ",FCN_ERROR);
  TestResult(v2d=v2d-v2a,                          *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=v2d-v2b                          ",FCN_ERROR);
  TestResult(v2d=v2a*v2b,                          *(v2d.vec),v2Results[3], sizeof(vec2), "v2d=v2a*v2b                          ",FCN_ERROR);
  TestResult(v2d=v2d/v2b,                          *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=v2d/v2b                          ",FCN_ERROR);
  TestResult(v2d=lerp(v2a,v2b,0.5),                *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=lerp(v2a,v2b,0.5)                ",FCN_ERROR);
  TestResult(v2d=sqr(v2a),                         *(v2d.vec),v2Results[3], sizeof(vec2), "v2d=sqr(v2a)                         ",FCN_ERROR);
  TestResult(v2d=sqrt(v2d),                        *(v2d.vec),v2Results[0], sizeof(vec2), "v2d=sqrt(v2a)                        ",FCN_ERROR);
  TestResult(v2d=normalize(v2a),                   *(v2d.vec),v2Results[6], sizeof(vec2), "v2d=normalize(v2a)                   ",FCN_ERROR);
  TestResult(fr=dot(v2a,v2b),                      fr,        fResults[0],  sizeof(float),"fr=dot(v2a,v2b)                      ",FCN_ERROR);
  TestResult(fr=length(v2a),                       fr,        fResults[1],  sizeof(float),"fr=length(v2a)                       ",FCN_ERROR);

  vec2 vec2r;
  v2d = v2a * 2.0f;

  TestResult(vec2r=*(v2a.vec)+2.0f,                vec2r,     v2Results[1], sizeof(vec2), "vec2r=*(v2a.vec)+2.0                 ",FCN_ERROR);
  TestResult(vec2r=*(v2a.vec)-1.0f,                vec2r,     v2Results[7], sizeof(vec2), "vec2r=*(v2a.vec)-2.0                 ",FCN_ERROR);
  TestResult(vec2r=*(v2a.vec)*2.0f,                vec2r,     v2Results[2], sizeof(vec2), "vec2r=*(v2a.vec)*2.0                 ",FCN_ERROR);
  TestResult(vec2r=*(v2d.vec)/2.0f,                vec2r,     v2Results[0], sizeof(vec2), "vec2r=*(v2d.vec)/2.0                 ",FCN_ERROR);
  TestResult(vec2r=lerp(*(v2a.vec),*(v2b.vec),0.5),vec2r,     v2Results[0], sizeof(vec2), "vec2r=lerp(*(v2a.vec),*(v2b.vec),0.5)",FCN_ERROR);
  TestResult(vec2r=sqr(*(v2a.vec)),                vec2r,     v2Results[3], sizeof(vec2), "vec2r=sqr(*(v2a.vec))                ",FCN_ERROR);
  v2d = sqr(v2a);
  TestResult(vec2r=sqrt(*(v2d.vec)),               vec2r,     v2Results[0],sizeof(vec2),  "vec2r=sqrt(*(v2d.vec))               ",FCN_ERROR);
  TestResult(vec2r=normalize(*(v2a.vec)),          vec2r,     v2Results[6],sizeof(vec2),  "vec2r=normalize(*(vec2a.vec))        ",FCN_ERROR);
  TestResult(fr=dot(*(v2a.vec),*(v2b.vec)),        fr,        fResults[0], sizeof(float), "fr=dot(*(v2a.vec),*(v2b.vec))        ",FCN_ERROR);
  TestResult(fr=length(*(v2a.vec)),                fr,        fResults[1], sizeof(float), "fr=length(*(v2a.vec))                ",FCN_ERROR);

  bool bCheck;
  bool bTrue  = true;
  bool bFalse = false;

  TestResult(bCheck=(v2a == v2b),                  bCheck,    bTrue,       sizeof(bool),  "bCheck=(v2a==v2b)                    ",FCN_ERROR);
  TestResult(bCheck=(v2a != v2b),                  bCheck,    bFalse,      sizeof(bool),  "bCheck=(v2a!=v2b)                    ",FCN_ERROR);

  TestResult(bCheck=(*(v2a.vec)==*(v2b.vec)),      bCheck,    bTrue,       sizeof(bool),  "bCheck=(*(v2a.vec)==*(v2b.vec))      ",FCN_ERROR);
  TestResult(bCheck=(*(v2a.vec)!=*(v2b.vec)),      bCheck,    bFalse,      sizeof(bool),  "bCheck=(*(v2a.vec)!=*(v2b.vec))      ",FCN_ERROR);

  fprintf(stdout,"----------------------> v2 Operations\n");

  v3 v3a(1.0f,2.0f,3.0f);
  v3 v3b(1.0f,2.0f,3.0f);
  v3 v3c;
  v3 v3d;

  TestResult(v3d=v3a,                              *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d=v3a                              ",FCN_ERROR);
  TestResult(v3d += 2.0,                           *(v3d.vec),v3Results[1],sizeof(vec3),  "v3d += 2.0                           ",FCN_ERROR);
  TestResult(v3d -= 2.0,                           *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d -= 2.0                           ",FCN_ERROR);
  TestResult(v3d *= 2.0,                           *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d *= 2.0                           ",FCN_ERROR);
  TestResult(v3d /= 2.0,                           *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d /= 2.0                           ",FCN_ERROR);

  TestResult(v3d += v3a,                           *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d += v3a                           ",FCN_ERROR);
  TestResult(v3d -= v3a,                           *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d -= v3a                           ",FCN_ERROR);
  TestResult(v3d *= v3a,                           *(v3d.vec),v3Results[3],sizeof(vec3),  "v3d *= v3a                           ",FCN_ERROR);
  TestResult(v3d /= v3a,                           *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d /= v3a                           ",FCN_ERROR);

  TestResult(v3d += *(v3a.vec),                    *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d += *(v3a.vec)                    ",FCN_ERROR);
  TestResult(v3d -= *(v3a.vec),                    *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d -= *(v3a.vec)                    ",FCN_ERROR);
  TestResult(v3d *= *(v3a.vec),                    *(v3d.vec),v3Results[3],sizeof(vec3),  "v3d *= *(v3a.vec)                    ",FCN_ERROR);
  TestResult(v3d /= *(v3a.vec),                    *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d /= *(v3a.vec)                    ",FCN_ERROR);

  TestResult(v3d->x = 3.0,                         *(v3d.vec),v3Results[4],sizeof(vec3),  "v2d->x = 3.0                         ",FCN_ERROR);

  TestResult(v3d = v3a + 2.0,                      *(v3d.vec),v3Results[1],sizeof(vec3),  "v3d = v3a + 2.0                      ",FCN_ERROR);
  TestResult(v3d = v3d - 2.0,                      *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = v3d - 2.0                      ",FCN_ERROR);
  TestResult(v3d = v3a * 2.0,                      *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d = v3a * 2.0                      ",FCN_ERROR);
  TestResult(v3d = v3d / 2.0,                      *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = v3d / 2.0                      ",FCN_ERROR);
  TestResult(v3d = 2.0 * v3a,                      *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d = 2.0 * v3a                      ",FCN_ERROR);

  TestResult(v3d = v3a + v3b,                      *(v3d.vec),v3Results[2],sizeof(vec3),  "v3d = v3a + v3b                      ",FCN_ERROR);
  TestResult(v3d = v3d - v3b,                      *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = v3d - v3b                      ",FCN_ERROR);
  TestResult(v3d = v3a * v3b,                      *(v3d.vec),v3Results[3],sizeof(vec3),  "v3d = v3a * v3b                      ",FCN_ERROR);
  TestResult(v3d = v3d / v3b,                      *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = v3d / v3b                      ",FCN_ERROR);

  TestResult(v3d = lerp(v3a,v3a,0.5),              *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = lerp(v3a,v3a,0.5)              ",FCN_ERROR);
  TestResult(v3d = sqr(v3a),                       *(v3d.vec),v3Results[3],sizeof(vec3),  "v3d = sql(v3a)                       ",FCN_ERROR);
  TestResult(v3d = sqrt(v3d),                      *(v3d.vec),v3Results[0],sizeof(vec3),  "v3d = sqrt(v3d)                      ",FCN_ERROR);
#if 0
  // XXX: THIS WON'T WORK ON THIS PROCESSOR (haddps)

  TestResult(v3d = normalize(v3a),                 *(v3d.vec),v3Results[x],sizeof(vec3),  "v3d = normalize(v3a)                 ",FCN_ERROR);
  TestResult(fr = dot(v3a,v3b),                    *(v3d.vec),v3Results[x],sizeof(vec3),  "fr = dot(v3a,v3b)                    ",FCN_ERROR);
  TestResult(fr = length(v3a),                     *(v3d.vec),v3Results[x],sizeof(vec3),  "fr = length(v3a)                     ",FCN_ERROR);
#endif

  vec3 vec3r;

  TestResult(vec3r = *(v3a.vec) + 2.0,             vec3r,     v3Results[1],sizeof(vec3),  "vec3r = *(v3a.vec) + 2.0             ",FCN_ERROR);
  v3d = v3a + 2.0;
  TestResult(vec3r = *(v3d.vec) - 2.0,             vec3r,     v3Results[0],sizeof(vec3),  "vec3r = *(v3d.vec) - 2.0             ",FCN_ERROR);
  TestResult(vec3r = *(v3a.vec) * 2.0,             vec3r,     v3Results[2],sizeof(vec3),  "vec3r = *(v3a.vec) * 2.0             ",FCN_ERROR);
  v3d = v3a * 2.0;
  TestResult(vec3r = *(v3d.vec) / 2.0,             vec3r,     v3Results[0],sizeof(vec3),  "vec3r = *(v3d.vec) / 2.0             ",FCN_ERROR);
  TestResult(vec3r = 2.0 * *(v3a.vec),             vec3r,     v3Results[2],sizeof(vec3),  "vec3r = 2.0 * *(v3a.vec)             ",FCN_ERROR);

  TestResult(vec3r = *(v3a.vec) + *(v3b.vec),      vec3r,     v3Results[2],sizeof(vec3),  "vec3r = *(v3a.vec) + *(v3b.vec)      ",FCN_ERROR);
  v3d = v3a * 2.0;
  TestResult(vec3r = *(v3d.vec) - *(v3b.vec),      vec3r,     v3Results[0],sizeof(vec3),  "vec3r = *(v3d.vec) - *(v3b.vec)      ",FCN_ERROR);
  TestResult(vec3r = *(v3a.vec) * *(v3b.vec),      vec3r,     v3Results[3],sizeof(vec3),  "vec3r = *(v3a.vec) * *(v3b.vec)      ",FCN_ERROR);
  v3d = v3a * v3b;
  TestResult(vec3r = *(v3d.vec) / *(v3a.vec),      vec3r,     v3Results[0],sizeof(vec3),  "vec3r = *(v3d.vec) / *(v3a.vec)      ",FCN_ERROR);

  v3d   = sqr(v3a);
  TestResult(vec3r=lerp(*(v3a.vec),*(v3b.vec),0.5),vec3r,     v3Results[0],sizeof(vec3),  "vec3r=lerp(*(v3a.vec),*(v3b.vec),0.5)",FCN_ERROR);
  TestResult(vec3r=sqr(*(v3a.vec)),                vec3r,     v3Results[3],sizeof(vec3),  "vec3r=sqr(*(v3a.vec))                ",FCN_ERROR);
  TestResult(vec3r=sqrt(*(v3d.vec)),               vec3r,     v3Results[0],sizeof(vec3),  "vec3r=sqrt(*(v3d.vec))               ",FCN_ERROR);

#if 0
  vec3r = normalize(*(v3a.vec));
  fr = dot(*(v3a.vec),*(v3b.vec));
  fr = length(*(v3a.vec));
#endif

  TestResult(bCheck = (v3a == v3b),                bCheck,    bTrue,      sizeof(bool),   "bCheck=(v3a==v3b)                    ",FCN_ERROR);
  TestResult(bCheck = (v3a != v3b),                bCheck,    bFalse,     sizeof(bool),   "bCheck=(v3a!=v3b)                    ",FCN_ERROR);

  TestResult(bCheck = (*(v3a.vec) == *(v3b.vec)),  bCheck,    bTrue,      sizeof(bool),   "bCheck=(*(v3a.vec)==*(v3b.vec))      ",FCN_ERROR);
  TestResult(bCheck = (*(v3a.vec) != *(v3b.vec)),  bCheck,    bFalse,     sizeof(bool),   "bCheck=(*(v3a.vec)!=*(v3b.vec))      ",FCN_ERROR);

  // XXX Add cross and then angle elements after standard vec4 elements

  fprintf(stdout,"\n----------------------> v4 Operations\n\n");

  v4 v4a(1.0f,2.0f,3.0f,4.0f);
  v4 v4b(1.0f,2.0f,3.0f,4.0f);
  v4 v4c;
  v4 v4d;

  TestResult(v4d=v4a,                              *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d=v4a                              ",FCN_ERROR);
  TestResult(v4d += 2.0,                           *(v4d.vec),v4Results[1],sizeof(vec3),  "v4d += 2.0                           ",FCN_ERROR);
  TestResult(v4d -= 2.0,                           *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d -= 2.0                           ",FCN_ERROR);
  TestResult(v4d *= 2.0,                           *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d *= 2.0                           ",FCN_ERROR);
  TestResult(v4d /= 2.0,                           *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d /= 2.0                           ",FCN_ERROR);

  TestResult(v4d += v4a,                           *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d += v4a                           ",FCN_ERROR);
  TestResult(v4d -= v4a,                           *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d -= v4a                           ",FCN_ERROR);
  TestResult(v4d *= v4a,                           *(v4d.vec),v4Results[3],sizeof(vec3),  "v4d *= v4a                           ",FCN_ERROR);
  TestResult(v4d /= v4a,                           *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d /= v4a                           ",FCN_ERROR);

  TestResult(v4d += *(v4a.vec),                    *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d += *(v4a.vec)                    ",FCN_ERROR);
  TestResult(v4d -= *(v4a.vec),                    *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d -= *(v4a.vec)                    ",FCN_ERROR);
  TestResult(v4d *= *(v4a.vec),                    *(v4d.vec),v4Results[3],sizeof(vec3),  "v4d *= *(v4a.vec)                    ",FCN_ERROR);
  TestResult(v4d /= *(v4a.vec),                    *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d /= *(v4a.vec)                    ",FCN_ERROR);

  TestResult(v4d->x = 3.0,                         *(v4d.vec),v4Results[4],sizeof(vec3),  "v2d->x = 3.0                         ",FCN_ERROR);

  TestResult(v4d = v4a + 2.0,                      *(v4d.vec),v4Results[1],sizeof(vec3),  "v4d = v4a + 2.0                      ",FCN_ERROR);
  TestResult(v4d = v4d - 2.0,                      *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = v4d - 2.0                      ",FCN_ERROR);
  TestResult(v4d = v4a * 2.0,                      *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d = v4a * 2.0                      ",FCN_ERROR);
  TestResult(v4d = v4d / 2.0,                      *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = v4d / 2.0                      ",FCN_ERROR);
  TestResult(v4d = 2.0 * v4a,                      *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d = 2.0 * v4a                      ",FCN_ERROR);

  TestResult(v4d = v4a + v4b,                      *(v4d.vec),v4Results[2],sizeof(vec3),  "v4d = v4a + v4b                      ",FCN_ERROR);
  TestResult(v4d = v4d - v4b,                      *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = v4d - v4b                      ",FCN_ERROR);
  TestResult(v4d = v4a * v4b,                      *(v4d.vec),v4Results[3],sizeof(vec3),  "v4d = v4a * v4b                      ",FCN_ERROR);
  TestResult(v4d = v4d / v4b,                      *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = v4d / v4b                      ",FCN_ERROR);

  TestResult(v4d = lerp(v4a,v4a,0.5),              *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = lerp(v4a,v4a,0.5)              ",FCN_ERROR);
  TestResult(v4d = sqr(v4a),                       *(v4d.vec),v4Results[3],sizeof(vec3),  "v4d = sql(v4a)                       ",FCN_ERROR);
  TestResult(v4d = sqrt(v4d),                      *(v4d.vec),v4Results[0],sizeof(vec3),  "v4d = sqrt(v4d)                      ",FCN_ERROR);
#if 0
  // XXX: THIS WON'T WORK ON THIS PROCESSOR (haddps)

  TestResult(v4d = normalize(v4a),                 *(v4d.vec),v4Results[x],sizeof(vec3),  "v4d = normalize(v4a)                 ",FCN_ERROR);
  TestResult(fr = dot(v4a,v4b),                    *(v4d.vec),v4Results[x],sizeof(vec3),  "fr = dot(v4a,v4b)                    ",FCN_ERROR);
  TestResult(fr = length(v4a),                     *(v4d.vec),v4Results[x],sizeof(vec3),  "fr = length(v4a)                     ",FCN_ERROR);
#endif

  vec4 vec4r;

  TestResult(vec4r = *(v4a.vec) + 2.0,             vec4r,     v4Results[1],sizeof(vec4),  "vec4r = *(v4a.vec) + 2.0             ",FCN_ERROR);
  v4d = v4a + 2.0;
  TestResult(vec4r = *(v4d.vec) - 2.0,             vec4r,     v4Results[0],sizeof(vec4),  "vec4r = *(v4d.vec) - 2.0             ",FCN_ERROR);
  TestResult(vec4r = *(v4a.vec) * 2.0,             vec4r,     v4Results[2],sizeof(vec4),  "vec4r = *(v4a.vec) * 2.0             ",FCN_ERROR);
  v4d = v4a * 2.0;
  TestResult(vec4r = *(v4d.vec) / 2.0,             vec4r,     v4Results[0],sizeof(vec4),  "vec4r = *(v4d.vec) / 2.0             ",FCN_ERROR);
  TestResult(vec4r = 2.0 * *(v4a.vec),             vec4r,     v4Results[2],sizeof(vec4),  "vec4r = 2.0 * *(v4a.vec)             ",FCN_ERROR);

  TestResult(vec4r = *(v4a.vec) + *(v4b.vec),      vec4r,     v4Results[2],sizeof(vec4),  "vec4r = *(v4a.vec) + *(v4b.vec)      ",FCN_ERROR);
  v4d = v4a * 2.0;
  TestResult(vec4r = *(v4d.vec) - *(v4b.vec),      vec4r,     v4Results[0],sizeof(vec4),  "vec4r = *(v4d.vec) - *(v4b.vec)      ",FCN_ERROR);
  TestResult(vec4r = *(v4a.vec) * *(v4b.vec),      vec4r,     v4Results[3],sizeof(vec4),  "vec4r = *(v4a.vec) * *(v4b.vec)      ",FCN_ERROR);
  v4d = v4a * v4b;
  TestResult(vec4r = *(v4d.vec) / *(v4a.vec),      vec4r,     v4Results[0],sizeof(vec4),  "vec4r = *(v4d.vec) / *(v4a.vec)      ",FCN_ERROR);

  v4d   = sqr(v4a);
  TestResult(vec4r=lerp(*(v4a.vec),*(v4b.vec),0.5),vec4r,     v4Results[0],sizeof(vec4),  "vec4r=lerp(*(v4a.vec),*(v4b.vec),0.5)",FCN_ERROR);
  TestResult(vec4r=sqr(*(v4a.vec)),                vec4r,     v4Results[3],sizeof(vec4),  "vec4r=sqr(*(v4a.vec))                ",FCN_ERROR);
  TestResult(vec4r=sqrt(*(v4d.vec)),               vec4r,     v4Results[0],sizeof(vec4),  "vec4r=sqrt(*(v4d.vec))               ",FCN_ERROR);

#if 0
  vec4r = normalize(*(v4a.vec));
  fr = dot(*(v4a.vec),*(v4b.vec));
  fr = length(*(v4a.vec));
#endif

  TestResult(bCheck = (v4a == v4b),                bCheck,    bTrue,       sizeof(bool),  "bCheck=(v4a==v4b)                    ",FCN_ERROR);
  TestResult(bCheck = (v4a != v4b),                bCheck,    bFalse,      sizeof(bool),  "bCheck=(v4a!=v4b)                    ",FCN_ERROR);

  TestResult(bCheck = (*(v4a.vec) == *(v4b.vec)),  bCheck,    bTrue,       sizeof(bool),  "bCheck=(*(v4a.vec)==*(v4b.vec))      ",FCN_ERROR);
  TestResult(bCheck = (*(v4a.vec) != *(v4b.vec)),  bCheck,    bFalse,      sizeof(bool),  "bCheck=(*(v4a.vec)!=*(v4b.vec))      ",FCN_ERROR);

  // XXX Add cross and then angle elements after standard vec4 elements

  fprintf(stdout,"\n----------------------> m2 Operations\n\n");

  m2 m2a(1.0,2.0,3.0,4.0);
  m2 m2b(1.0,2.0,3.0,4.0);
  m2 m2c;
  m2 m2d;

  TestResult(m2c = m2a,                            *(m2c.m),  m2Results[0],sizeof(mat2),  "m2c = m2a                            ",FCN_ERROR);
  TestResult(m2c.identity(),                       *(m2c.m),  m2Results[1],sizeof(mat2),  "m2.identity()                        ",FCN_ERROR);

  m2c  = m2a;
  TestResult(m2c += 2.0,                           *(m2c.m),  m2Results[2],sizeof(mat2),  "m2c += 2.0                           ",FCN_ERROR);
  TestResult(m2c -= 2.0,                           *(m2c.m),  m2Results[0],sizeof(mat2),  "m2c -= 2.0                           ",FCN_ERROR);
  TestResult(m2c *= 2.0,                           *(m2c.m),  m2Results[3],sizeof(mat2),  "m2c *= 2.0                           ",FCN_ERROR);

  m2c  = m2a;
  TestResult(m2c += m2a,                           *(m2c.m),  m2Results[3],sizeof(mat2),  "m2c += m2a                           ",FCN_ERROR);
  TestResult(m2c -= m2a,                           *(m2c.m),  m2Results[0],sizeof(mat2),  "m2c -= m2a                           ",FCN_ERROR);
  TestResult(m2c *= m2a,                           *(m2c.m),  m2Results[4],sizeof(mat2),  "m2c *= m2a                           ",FCN_ERROR);

  m2c  = m2a;
  TestResult(m2c += *(m2a.m),                      *(m2c.m),  m2Results[3],sizeof(mat2),  "m2c += *(m2a.m)                      ",FCN_ERROR);
  TestResult(m2c -= *(m2a.m),                      *(m2c.m),  m2Results[0],sizeof(mat2),  "m2c -= *(m2a.m)                      ",FCN_ERROR);
  TestResult(m2c *= *(m2a.m),                      *(m2c.m),  m2Results[4],sizeof(mat2),  "m2c *= *(m2a.m)                      ",FCN_ERROR);

  m2c = m2a;
  TestResult(m2c->m00 = 2.0,                       *(m2c.m),  m2Results[5],sizeof(mat2),  "m2c->m00 = 2.0                       ",FCN_ERROR);

  TestResult(m2c = m2identity(),                   *(m2c.m),  m2Results[1],sizeof(mat2),  "m2c=m2identity()                     ",FCN_ERROR);
  TestResult(m2c = m2transpose(m2a),               *(m2c.m),  m2Results[6],sizeof(mat2),  "m2c=m2transpose(m2a)                 ",FCN_ERROR);

  float f2Angle = 3.14159 * 45.0 / 180.0;
  TestResult(m2c = m2rotate(f2Angle),              *(m2c.m),   m2Results[7],sizeof(mat2), "m2c = m2rotate(f2Angle)              ",FCN_ERROR);
  TestResult(m2c = m2rotate_lh(f2Angle),           *(m2c.m),   m2Results[8],sizeof(mat2), "m2c = m2rotate_lh(f2Angle)           ",FCN_ERROR);
  TestResult(m2c = m2rotate_rh(f2Angle),           *(m2c.m),   m2Results[7],sizeof(mat2), "m2c = m2rotate_rh(f2Angle)           ",FCN_ERROR);
  TestResult(m2c = m2scale(1.0,2.0),               *(m2c.m),   m2Results[9],sizeof(mat2), "m2c = m2scale(1.0,2.0)               ",FCN_ERROR);

  TestResult(m2c = m2a + 2.0,                      *(m2c.m),   m2Results[2],sizeof(mat2), "m2c = m2a + 2.0                      ",FCN_ERROR);
  TestResult(m2c = m2c - 2.0,                      *(m2c.m),   m2Results[0],sizeof(mat2), "m2c = m2c - 2.0                      ",FCN_ERROR);
  TestResult(m2c = m2a * 2.0,                      *(m2c.m),   m2Results[3],sizeof(mat2), "m2c = m2a * 2.0                      ",FCN_ERROR);

  TestResult(v2d = m2a * v2a,                      *(v2d.vec), v2Results[9],sizeof(vec2), "v2d = m2a * v2a                      ",FCN_ERROR);
  TestResult(m2c = -m2a,                           *(m2c.m),   m2Results[10],sizeof(mat2), "m2c = -m2a                           ",FCN_ERROR);

  TestResult(m2c = m2a + m2b,                      *(m2c.m),   m2Results[3],sizeof(mat2), "m2c = m2a + m2b                      ",FCN_ERROR);
  TestResult(m2c = m2c - m2b,                      *(m2c.m),   m2Results[0],sizeof(mat2), "m2c = m2c - m2b                      ",FCN_ERROR);
  TestResult(m2c = m2a * m2b,                      *(m2c.m),   m2Results[4],sizeof(mat2), "m2c = m2a * m2b                      ",FCN_ERROR);

  mat2 mat2r;

  TestResult(mat2r = mat2identity(),               mat2r,      m2Results[1],sizeof(mat2), "mat2r = mat2identity()               ",FCN_ERROR);
  TestResult(mat2r = mat2transpose(*(m2a.m)),      mat2r,      m2Results[6],sizeof(mat2), "mat2r = mat2transpose(*(m2a.m))      ",FCN_ERROR);
  TestResult(mat2r = mat2rotate(f2Angle),          mat2r,      m2Results[7],sizeof(mat2), "mat2r = mat2rotate(f2Angle)          ",FCN_ERROR);
  TestResult(mat2r = mat2rotate_lh(f2Angle),       mat2r,      m2Results[8],sizeof(mat2), "mat2 = mat2rotate_lh(f2Angle)        ",FCN_ERROR);
  TestResult(mat2r = mat2rotate_rh(f2Angle),       mat2r,      m2Results[7],sizeof(mat2), "mat2 = mat2rotate_rh(f2Angle)        ",FCN_ERROR);
  TestResult(mat2r = mat2scale(1.0,2.0),           mat2r,      m2Results[9],sizeof(mat2), "mat2 = mat2scale(1.0,2.0)            ",FCN_ERROR);

  TestResult(mat2r = *(m2a.m) + 2.0,               mat2r,      m2Results[2],sizeof(mat2), "mat2r = *(m2a.m) + 2.0               ",FCN_ERROR);
  m2d   = m2a + 2.0;
  TestResult(mat2r = *(m2d.m) - 2.0,               mat2r,      m2Results[0],sizeof(mat2), "mat2r = *(m2d.m) - 2.0               ",FCN_ERROR);
  TestResult(mat2r = *(m2a.m) * 2.0,               mat2r,      m2Results[3],sizeof(mat2), "mat2r = *(m2a.m) * 2.0               ",FCN_ERROR);

  TestResult(mat2r = -(*(m2a.m)),                  mat2r,      m2Results[10],sizeof(mat2), "mat2r = -(*(m2a.m))                  ",FCN_ERROR);
  TestResult(vec2r = *(m2a.m) * *(v2a.vec),        vec2r,      v2Results[9],sizeof(vec2), "vec2r = *(m2a.m) * *(v2a.m)          ",FCN_ERROR);

  m2d   = m2a + m2b;
  TestResult(mat2r = *(m2a.m) + *(m2b.m),          mat2r,      m2Results[3],sizeof(mat2), "mat2r = *(m2a.m) + *(m2b.m)          ",FCN_ERROR);
  TestResult(mat2r = *(m2d.m) - *(m2b.m),          mat2r,      m2Results[0],sizeof(mat2), "mat2r = *(m2d.m) - *(m2b.m)          ",FCN_ERROR);
  TestResult(mat2r = *(m2a.m) * *(m2b.m),          mat2r,      m2Results[4],sizeof(mat2), "mat2r = *(m2a.m) * *(m2b.m)          ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> m3 Operations\n\n");

  m3 m3a(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
  m3 m3b(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
  m3 m3c;
  m3 m3d;
  m3 m3e(6.0,3.0,7.0,5.0,1.0,2.0,9.0,4.0,8.0);

  TestResult(m3d.identity(),                       *(m3d.m),   m3Results[ 0],sizeof(mat3), "m3d.identity()                       ",FCN_ERROR);
  TestResult(m3d  = m3a,                           *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d = m3a                            ",FCN_ERROR);
  TestResult(m3d += 2.0,                           *(m3d.m),   m3Results[ 2],sizeof(mat3), "m3d += 2.0                           ",FCN_ERROR);
  TestResult(m3d -= 2.0,                           *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d -= 2.0                           ",FCN_ERROR);
  TestResult(m3d *= 2.0,                           *(m3d.m),   m3Results[ 3],sizeof(mat3), "m3d *= 2.0                           ",FCN_ERROR);

  m3d  = m3a;
  TestResult(m3d += m3a,                           *(m3d.m),   m3Results[ 3],sizeof(mat3), "m3d += m3a                           ",FCN_ERROR);
  TestResult(m3d -= m3a,                           *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d -= m3a                           ",FCN_ERROR);
  TestResult(m3d *= m3a,                           *(m3d.m),   m3Results[ 4],sizeof(mat3), "m3d *= m3a                           ",FCN_ERROR);

  m3d  = m3a;
  TestResult(m3d += *(m3a.m),                      *(m3d.m),   m3Results[ 3],sizeof(mat3), "m3d += *(m3a.m)                      ",FCN_ERROR);
  TestResult(m3d -= *(m3a.m),                      *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d -= *(m3d.m)                      ",FCN_ERROR);
  TestResult(m3d *= *(m3a.m),                      *(m3d.m),   m3Results[ 4],sizeof(mat3), "m3d *= *(m3a.m)                      ",FCN_ERROR);

  TestResult(m3d.identity(),                       *(m3d.m),   m3Results[ 0],sizeof(mat3), "m3d.identity()                       ",FCN_ERROR);
  TestResult(m3d->m00 = 3.0,                       *(m3d.m),   m3Results[ 5],sizeof(mat3), "m3d->m00 = 3.0                       ",FCN_ERROR);

  TestResult(m3d = m3identity(),                   *(m3d.m),   m3Results[ 0],sizeof(mat3), "m3d = m3identity()                   ",FCN_ERROR);
  TestResult(m3d = m3inverse(m3e),                 *(m3d.m),   m3Results[ 6],sizeof(mat3), "m3d = m3inverse(m3e)                 ",FCN_ERROR);
  TestResult(m3d = m3transpose(m3a),               *(m3d.m),   m3Results[ 7],sizeof(mat3), "m3d = transpose(m3a)                 ",FCN_ERROR);

  TestResult(m3d = m3a + 2.0,                      *(m3d.m),   m3Results[ 2],sizeof(mat3), "m3d = m3a + 2.0                      ",FCN_ERROR);
  TestResult(m3d = m3d - 2.0,                      *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d = m3d - 2.0                      ",FCN_ERROR);
  TestResult(m3d = m3a * 2.0,                      *(m3d.m),   m3Results[ 3],sizeof(mat3), "m3d = m3a * 2.0                      ",FCN_ERROR);

  TestResult(v3d = m3a * v3a,                      *(v3d.vec), v3Results[ 5],sizeof(vec3), "v3d = m3a * v3a                      ",FCN_ERROR);

  TestResult(m3d = -m3a,                           *(m3d.m),   m3Results[ 8],sizeof(mat3), "m3d = -m3a                           ",FCN_ERROR);
  TestResult(m3d = m3a + m3b,                      *(m3d.m),   m3Results[ 3],sizeof(mat3), "m3d = m3a + m3b                      ",FCN_ERROR);
  TestResult(m3d = m3d - m3b,                      *(m3d.m),   m3Results[ 1],sizeof(mat3), "m3d = m3d - m3b                      ",FCN_ERROR);
  TestResult(m3d = m3a * m3b,                      *(m3d.m),   m3Results[ 4],sizeof(mat3), "m3d = m3a * m3b                      ",FCN_ERROR);

  float fXAngle = 3.14159 * 45.0 / 180.0;
  float fYAngle = 3.14159 * 30.0 / 180.0;
  float fZAngle = 3.14159 * 60.0 / 180.0;

  TestResult(m3d = m3rotate_rhx(fXAngle),          *(m3d.m),   m3Results[ 9],sizeof(mat3), "m3d = m3rotate_rhx(fXAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhx(fXAngle),          *(m3d.m),   m3Results[10],sizeof(mat3), "m3d = m3rotate_lhx(fXAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhy(fYAngle),          *(m3d.m),   m3Results[11],sizeof(mat3), "m3d = m3rotate_rhy(fYAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhy(fYAngle),          *(m3d.m),   m3Results[12],sizeof(mat3), "m3d = m3rotate_lhy(fYAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhz(fZAngle),          *(m3d.m),   m3Results[13],sizeof(mat3), "m3d = m3rotate_rhz(fZAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhz(fZAngle),          *(m3d.m),   m3Results[14],sizeof(mat3), "m3d = m3rotate_lhz(fZAngle)          ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhxy(fXAngle,fYAngle), *(m3d.m),   m3Results[15],sizeof(mat3), "m3d = m3rotate_rhxy(fXAngle,fYAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhxy(fXAngle,fYAngle), *(m3d.m),   m3Results[16],sizeof(mat3), "m3d = m3rotate_lhxy(fXAngle,fYAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhxz(fXAngle,fZAngle), *(m3d.m),   m3Results[17],sizeof(mat3), "m3d = m3rotate_rhxz(fXAngle,fZAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhxz(fXAngle,fZAngle), *(m3d.m),   m3Results[18],sizeof(mat3), "m3d = m3rotate_lhxz(fXAngle,fZAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhyz(fYAngle,fZAngle), *(m3d.m),   m3Results[19],sizeof(mat3), "m3d = m3rotate_rhyz(fYAngle,fZAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_lhyz(fYAngle,fZAngle), *(m3d.m),   m3Results[20],sizeof(mat3), "m3d = m3rotate_lhyz(fYAngle,fZAngle) ",FCN_ERROR);
  TestResult(m3d = m3rotate_rhxyz(fXAngle,fYAngle,fZAngle),*(m3d.m),m3Results[21],sizeof(mat3),"m3d = m3rotate_rhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
  TestResult(m3d = m3rotate_lhxyz(fXAngle,fYAngle,fZAngle),*(m3d.m),m3Results[22],sizeof(mat3),"m3d = m3rotate_lhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);

  TestResult(m3d = m3scale(1.0,2.0,3.0),           *(m3d.m),   m3Results[23],sizeof(mat3), "m3d = m3scale(1.0,2.0,3.0)           ",FCN_ERROR);
  TestResult(m3d = m3scale(v3a),                   *(m3d.m),   m3Results[23],sizeof(mat3), "m3d = m3scale(v3a)                   ",FCN_ERROR);

  mat3 mat3r;

  TestResult(mat3r = mat3inverse(*(m3e.m)),        mat3r,      m3Results[ 6],sizeof(mat3), "mat3r = mat3inverse(*(m3a.m))        ",FCN_ERROR);
  TestResult(mat3r = mat3transpose(*(m3a.m)),      mat3r,      m3Results[ 7],sizeof(mat3), "mat3r = mat3transpose(*(m3a.m))      ",FCN_ERROR);

  m3d   = m3a + 2.0;
  TestResult(mat3r = *(m3a.m) + 2.0,               mat3r,      m3Results[ 2],sizeof(mat3), "mat3r = *(m3a.m) + 2.0               ",FCN_ERROR);
  TestResult(mat3r = *(m3d.m) - 2.0,               mat3r,      m3Results[ 1],sizeof(mat3), "mat3r = *(m3d.m) - 2.0               ",FCN_ERROR);
  TestResult(mat3r = *(m3a.m) * 2.0,               mat3r,      m3Results[ 3],sizeof(mat3), "mat3r = *(m3a.m) * 2.0               ",FCN_ERROR);

  TestResult(mat3r = -(*(m3a.m)),                  mat3r,      m3Results[ 8],sizeof(mat3), "mat3r = -(*(m3a.m))                  ",FCN_ERROR);
  TestResult(vec3r = *(m3a.m) * *(v3a.vec),        vec3r,      v3Results[ 5],sizeof(vec3), "vec3r = *(m3a.m) * *(v3a.vec)        ",FCN_ERROR);

  m3d   = m3a + m3b;
  TestResult(mat3r = *(m3a.m) + *(m3b.m),          mat3r,      m3Results[ 3],sizeof(mat3), "mat3r = *(m3a.m) + *(m3b.m)          ",FCN_ERROR);
  TestResult(mat3r = *(m3d.m) - *(m3b.m),          mat3r,      m3Results[ 1],sizeof(mat3), "mat3r = *(m3d.m) - *(m3b.m)          ",FCN_ERROR);
  TestResult(mat3r = *(m3a.m) * *(m3b.m),          mat3r,      m3Results[ 4],sizeof(mat3), "mat3r = *(m3a.m) * *(m3b.m)          ",FCN_ERROR);

  TestResult(mat3r = mat3rotate_rhx(fXAngle),      mat3r,      m3Results[ 9],sizeof(mat3), "mat3r = mat3rotate_rhx(fXAngle)      ",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhx(fXAngle),      mat3r,      m3Results[10],sizeof(mat3), "mat3r = mat3rotate_lhx(fXAngle)      ",FCN_ERROR);
  TestResult(mat3r = mat3rotate_rhy(fYAngle),      mat3r,      m3Results[11],sizeof(mat3), "mat3r = mat3rotate_rhy(fYAngle)      ",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhy(fYAngle),      mat3r,      m3Results[12],sizeof(mat3), "mat3r = mat3rotate_lhy(fYAngle)      ",FCN_ERROR);
  TestResult(mat3r = mat3rotate_rhz(fZAngle),      mat3r,      m3Results[13],sizeof(mat3), "mat3r = mat3rotate_rhz(fZAngle)      ",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhz(fZAngle),      mat3r,      m3Results[14],sizeof(mat3), "mat3r = mat3rotate_lhz(fZAngle)      ",FCN_ERROR);

  TestResult(mat3r = mat3rotate_rhxy(fXAngle,fYAngle),mat3r,   m3Results[15],sizeof(mat3), "mat3r = mat3rotate_rhxy(fXAngle,fYAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhxy(fXAngle,fYAngle),mat3r,   m3Results[16],sizeof(mat3), "mat3r = mat3rotate_lhxy(fXAngle,fYAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_rhxz(fXAngle,fZAngle),mat3r,   m3Results[17],sizeof(mat3), "mat3r = mat3rotate_rhxz(fXAngle,fZAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhxz(fXAngle,fZAngle),mat3r,   m3Results[18],sizeof(mat3), "mat3r = mat3rotate_lhxz(fXAngle,fZAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_rhyz(fYAngle,fZAngle),mat3r,   m3Results[19],sizeof(mat3), "mat3r = mat3rotate_rhyz(fYAngle,fZAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhyz(fYAngle,fZAngle),mat3r,   m3Results[20],sizeof(mat3), "mat3r = mat3rotate_lhyz(fYAngle,fZAngle)",FCN_ERROR);

  TestResult(mat3r = mat3rotate_rhxyz(fXAngle,fYAngle,fZAngle),mat3r,m3Results[21],sizeof(mat3),"mat3r = mat3rotate_rhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
  TestResult(mat3r = mat3rotate_lhxyz(fXAngle,fYAngle,fZAngle),mat3r,m3Results[22],sizeof(mat3),"mat3r = mat3rotate_lhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);

  TestResult(mat3r = mat3scale(1.0,2.0,3.0),          mat3r,   m3Results[23],sizeof(mat3), "mat3r = mat3scale(1.0,2.0,3.0)          ",FCN_ERROR);
  TestResult(mat3r = mat3scale(*(v3a.vec)),           mat3r,   m3Results[23],sizeof(mat3), "mat3r = mat3scale(*(v3a.vec))           ",FCN_ERROR);
  
  fprintf(stdout,"\n----------------------> m4 Operations\n\n");

  m4 m4a(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0);
  m4 m4b(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0);
  m4 m4c;
  m4 m4d;
  m4 m4e(6.0,3.0,7.0,5.0,1.0,2.0,9.0,4.0,8.0,16.0,12.0,18.0,11.0,10.0,14.0,15.0);

  TestResult(m4d.identity(),                       *(m4d.m),   m4Results[ 0],sizeof(mat4), "m4d.identity()                       ",FCN_ERROR);
  TestResult(m4d  = m4a,                           *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d = m4a                            ",FCN_ERROR);
  TestResult(m4d += 2.0,                           *(m4d.m),   m4Results[ 2],sizeof(mat4), "m4d += 2.0                           ",FCN_ERROR);
  TestResult(m4d -= 2.0,                           *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d -= 2.0                           ",FCN_ERROR);
  TestResult(m4d *= 2.0,                           *(m4d.m),   m4Results[ 3],sizeof(mat4), "m4d *= 2.0                           ",FCN_ERROR);

  m4d  = m4a;
  TestResult(m4d += m4a,                           *(m4d.m),   m4Results[ 3],sizeof(mat4), "m4d += m4a                           ",FCN_ERROR);
  TestResult(m4d -= m4a,                           *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d -= m4a                           ",FCN_ERROR);
  TestResult(m4d *= m4a,                           *(m4d.m),   m4Results[ 4],sizeof(mat4), "m4d *= m4a                           ",FCN_ERROR);

  m4d  = m4a;
  TestResult(m4d += *(m4a.m),                      *(m4d.m),   m4Results[ 3],sizeof(mat4), "m4d += *(m4a.m)                      ",FCN_ERROR);
  TestResult(m4d -= *(m4a.m),                      *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d -= *(m4d.m)                      ",FCN_ERROR);
  TestResult(m4d *= *(m4a.m),                      *(m4d.m),   m4Results[ 4],sizeof(mat4), "m4d *= *(m4a.m)                      ",FCN_ERROR);

  TestResult(m4d.identity(),                       *(m4d.m),   m4Results[ 0],sizeof(mat4), "m4d.identity()                       ",FCN_ERROR);
  TestResult(m4d->m00 = 3.0,                       *(m4d.m),   m4Results[ 5],sizeof(mat4), "m4d->m00 = 3.0                       ",FCN_ERROR);

  TestResult(m4d = m4identity(),                   *(m4d.m),   m4Results[ 0],sizeof(mat4), "m4d = m4identity()                   ",FCN_ERROR);

  TestResult(m4d = m4a + 2.0,                      *(m4d.m),   m4Results[ 2],sizeof(mat4), "m4d = m4a + 2.0                      ",FCN_ERROR);
  TestResult(m4d = m4d - 2.0,                      *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d = m4d - 2.0                      ",FCN_ERROR);
  TestResult(m4d = m4a * 2.0,                      *(m4d.m),   m4Results[ 3],sizeof(mat4), "m4d = m4a * 2.0                      ",FCN_ERROR);

  TestResult(v4d = m4a * v4a,                      *(v4d.vec), v4Results[ 5],sizeof(vec4), "v4d = m4a * v4a                      ",FCN_ERROR);

  TestResult(m4d = -m4a,                           *(m4d.m),   m4Results[ 8],sizeof(mat4), "m4d = -m4a                           ",FCN_ERROR);
  TestResult(m4d = m4a + m4b,                      *(m4d.m),   m4Results[ 3],sizeof(mat4), "m4d = m4a + m4b                      ",FCN_ERROR);
  TestResult(m4d = m4d - m4b,                      *(m4d.m),   m4Results[ 1],sizeof(mat4), "m4d = m4d - m4b                      ",FCN_ERROR);
  TestResult(m4d = m4a * m4b,                      *(m4d.m),   m4Results[ 4],sizeof(mat4), "m4d = m4a * m4b                      ",FCN_ERROR);

  // XXX: Repair (m4d = m4inverse(m4e);)
  // XXX: Transpose (m2transpose vs. m3transpose vs transpose)
  //

  // TestResult(m4d = m4inverse(m4e),                 *(m4d.m),   m4Results[ 6],sizeof(mat4), "m4d = m4inverse(m4e)                 ",FCN_ERROR);
  TestResult(m4d = transpose(m4a),               *(m4d.m),   m4Results[ 7],sizeof(mat4), "m4d = transpose(m4a)                 ",FCN_ERROR);

#if 0
  v3d = v3a + 2.0;
  m4d = lookAt(v3a,v3b);
#endif

  v3d = v3a + 2.0;
  TestResult(m4d = shadow(v3a,2.0,v3d),            *(m4d.m),   m4Results[ 9],sizeof(mat4), "m4d = shadow(v3a,2.0,v3d)            ",FCN_ERROR);
  TestResult(m4d = glToD3D(m4a),                   *(m4d.m),   m4Results[10],sizeof(mat4), "m4d = glToD3D(m4a)                   ",FCN_ERROR);

  v3c = v3a + 2.0;
  v3d = v3a - 2.0;
  TestResult(m4d = lookAt_lh(v3c,v3a,v3d),         *(m4d.m),   m4Results[11],sizeof(mat4), "m4d = lookAt_lh(v3c,v3a,v3d)         ",FCN_ERROR);
  TestResult(m4d = m4scale(1.0,2.0,3.0),           *(m4d.m),   m4Results[12],sizeof(mat4), "m4d = m4scale(1.0,2.0,3.0)           ",FCN_ERROR);
  TestResult(m4d = m4scale(v4a),                   *(m4d.m),   m4Results[12],sizeof(mat4), "m4d = m4scale(v4a)                   ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhx(fXAngle),          *(m4d.m),   m4Results[13],sizeof(mat4), "m4d = m4rotate_rhx(fXAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhx(fXAngle),          *(m4d.m),   m4Results[14],sizeof(mat4), "m4d = m4rotate_lhx(fXAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhy(fYAngle),          *(m4d.m),   m4Results[15],sizeof(mat4), "m4d = m4rotate_rhy(fYAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhy(fYAngle),          *(m4d.m),   m4Results[16],sizeof(mat4), "m4d = m4rotate_lhy(fYAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhz(fZAngle),          *(m4d.m),   m4Results[17],sizeof(mat4), "m4d = m4rotate_rhz(fZAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhz(fZAngle),          *(m4d.m),   m4Results[18],sizeof(mat4), "m4d = m4rotate_lhz(fZAngle)          ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhxy(fXAngle,fYAngle), *(m4d.m),   m4Results[19],sizeof(mat4), "m4d = m4rotate_rhxy(fXAngle,fYAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhxy(fXAngle,fYAngle), *(m4d.m),   m4Results[20],sizeof(mat4), "m4d = m4rotate_lhxy(fXAngle,fYAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhxz(fXAngle,fZAngle), *(m4d.m),   m4Results[21],sizeof(mat4), "m4d = m4rotate_lhxy(fXAngle,fYAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhxz(fXAngle,fZAngle), *(m4d.m),   m4Results[22],sizeof(mat4), "m4d = m4rotate_lhxz(fXAngle,fZAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhyz(fYAngle,fZAngle), *(m4d.m),   m4Results[23],sizeof(mat4), "m4d = m4rotate_rhyz(fYAngle,fZAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_lhyz(fYAngle,fZAngle), *(m4d.m),   m4Results[24],sizeof(mat4), "m4d = m4rotate_lhyz(fYAngle,fZAngle) ",FCN_ERROR);
  TestResult(m4d = m4rotate_rhxyz(fXAngle,fYAngle,fZAngle),*(m4d.m),m4Results[25],sizeof(mat4),"m4d = m4rotate_rhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
  TestResult(m4d = m4rotate_lhxyz(fXAngle,fYAngle,fZAngle),*(m4d.m),m4Results[26],sizeof(mat4),"m4d = m4rotate_lhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
  TestResult(m4d = m4translate_rh(1.0,2.0,3.0),    *(m4d.m),   m4Results[27],sizeof(mat4), "m4d = m4translate_rh(1.0,2.0,3.0)    ",FCN_ERROR);
  TestResult(m4d = m4translate_lh(1.0,2.0,3.0),    *(m4d.m),   m4Results[28],sizeof(mat4), "m4d = m4translate_rh(1.0,2.0,3.0)    ",FCN_ERROR);
  TestResult(m4d = translate_rh(v3a),              *(m4d.m),   m4Results[27],sizeof(mat4), "m4d = translate_rh(v3a)              ",FCN_ERROR);
  TestResult(m4d = translate_lh(v3a),              *(m4d.m),   m4Results[28],sizeof(mat4), "m4d = translate_rh(v3a)              ",FCN_ERROR);
  TestResult(m4d = translate_rh(v4a),              *(m4d.m),   m4Results[27],sizeof(mat4), "m4d = translate_rh(v4a)              ",FCN_ERROR);
  TestResult(m4d = translate_lh(v4a),              *(m4d.m),   m4Results[28],sizeof(mat4), "m4d = translate_rh(v4a)              ",FCN_ERROR);

  TestResult(m4d = m4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0),*(m4d.m),m4Results[29],sizeof(mat4),"m4d = m4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0)",FCN_ERROR);
  TestResult(m4d = m4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,1),*(m4d.m),m4Results[30],sizeof(mat4),"m4d = m4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0)",FCN_ERROR);
  TestResult(m4d = m4perspective(fXAngle,1.0,1.0,-4.0,20.0,0),*(m4d.m),m4Results[31],sizeof(mat4),"m4d = m4perspective(fXAngle,1.0,1.0,-4.0,20.0,0)",FCN_ERROR);
  TestResult(m4d = m4perspective(fXAngle,1.0,1.0,-4.0,20.0,1),*(m4d.m),m4Results[32],sizeof(mat4),"m4d = m4perspective(fXAngle,1.0,1.0,-4.0,20.0,0)",FCN_ERROR);

  TestResult(m4d = m4cubemap(0),                   *(m4d.m),   m4Results[33],sizeof(mat4), "m4d = m4cubemap(0)                   ",FCN_ERROR);
  TestResult(m4d = m4cubemap(1),                   *(m4d.m),   m4Results[34],sizeof(mat4), "m4d = m4cubemap(0)                   ",FCN_ERROR);
  TestResult(m4d = m4cubemap(2),                   *(m4d.m),   m4Results[35],sizeof(mat4), "m4d = m4cubemap(0)                   ",FCN_ERROR);
  TestResult(m4d = m4cubemap(3),                   *(m4d.m),   m4Results[36],sizeof(mat4), "m4d = m4cubemap(0)                   ",FCN_ERROR);
  TestResult(m4d = m4cubemap(5),                   *(m4d.m),   m4Results[37],sizeof(mat4), "m4d = m4cubemap(0)                   ",FCN_ERROR);

  TestResult(m3d = m3from_m4(m4a),                 *(m3d.m),   m3Results[24],sizeof(mat3), "m3d = m3from_m4(m4a)                 ",FCN_ERROR);
  TestResult(m4d = m4from_m3(m3a),                 *(m4d.m),   m4Results[38],sizeof(mat4), "m4d = m4from_m3(m3a)                 ",FCN_ERROR);

  mat4 mat4r;

  TestResult(mat4r = m4identity(),                 mat4r,      m4Results[ 0],sizeof(mat4), "mat4r =  mat4identity()              ",FCN_ERROR);

  m4d = m4a + 2.0;
  TestResult(mat4r = *(m4a.m) + 2.0,               mat4r,      m4Results[ 2],sizeof(mat4), "mat4r = *(m4a.m) + 2.0               ",FCN_ERROR);
  TestResult(mat4r = *(m4d.m) - 2.0,               mat4r,      m4Results[ 1],sizeof(mat4), "mat4r = *(m4d.m) - 2.0               ",FCN_ERROR);
  TestResult(mat4r = *(m4a.m) * 2.0,               mat4r,      m4Results[ 3],sizeof(mat4), "mat4r = *(m4a.m) * 2.0               ",FCN_ERROR);

  TestResult(vec4r = *(m4a.m) * *(v4a.vec),        vec4r,      v4Results[ 5],sizeof(vec4), "vec4r = *(m4a.m) * *(v4a.vec)        ",FCN_ERROR);

  m4d = m4a + m4b;
  TestResult(mat4r = -(*(m4a.m)),                  mat4r,      m4Results[ 8],sizeof(mat4), "mat4r = -(*(m4a.m))                  ",FCN_ERROR);
  TestResult(mat4r = *(m4a.m) + *(m4b.m),          mat4r,      m4Results[ 3],sizeof(mat4), "mat4r = *(m4a.m) + *(m4b.m)          ",FCN_ERROR);
  TestResult(mat4r = *(m4d.m) - *(m4b.m),          mat4r,      m4Results[ 1],sizeof(mat4), "mat4r = *(m4d.m) - *(m4b.m)          ",FCN_ERROR);
  TestResult(mat4r = *(m4a.m) * *(m4b.m),          mat4r,      m4Results[ 4],sizeof(mat4), "mat4r = *(m4a.m) * *(m4b.m)          ",FCN_ERROR);


  // XXX: Repair (m4d = m4inverse(m4e);)
  // XXX: Transpose (m2transpose vs. m3transpose vs transpose)
  //

  // TestResult(m4d = m4inverse(m4e),                 *(m4d.m),   m4Results[ 6],sizeof(mat4), "m4d = m4inverse(m4e)                 ",FCN_ERROR);
  TestResult(mat4r = transpose(*(m4a.m)),          mat4r,      m4Results[ 7],sizeof(mat4), "mat4r = transpose(*(m4a.m))          ",FCN_ERROR);

#if 0
  v3d = v3a + 2.0;
  m4d = lookAt(v3a,v3b);
#endif

  v3d = v3a + 2.0;
  TestResult(mat4r = shadow(*(v3a.vec),2.0,*(v3d.vec)),mat4r,  m4Results[ 9],sizeof(mat4), "mat4r=shadow(*(v3a.vec),2.0,*(v3d.vec))",FCN_ERROR);
  TestResult(mat4r = glToD3D(*(m4a.m)),          mat4r,        m4Results[10],sizeof(mat4), "m4d = glToD3D(m4a)                   ",FCN_ERROR);

  v3c = v3a + 2.0;
  v3d = v3a - 2.0;
  TestResult(mat4r = lookAt_lh(*(v3c.vec),*(v3a.vec),*(v3d.vec)),mat4r,m4Results[11],sizeof(mat4),"mat4r=lookAt_lh(*(v3c.vec),*(v3a.vec))",FCN_ERROR);
  TestResult(mat4r = mat4scale(1.0,2.0,3.0),       mat4r,      m4Results[12],sizeof(mat4), "mat4r = mat4scale(1.0,2.0,3.0)       ",FCN_ERROR);
  TestResult(mat4r = mat4scale(*(v4a.vec)),        mat4r,      m4Results[12],sizeof(mat4), "mat4r = mat4scale(*(v4a.vec))        ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhx(fXAngle),      mat4r,      m4Results[13],sizeof(mat4), "mat4r = mat4rotate_rhx(fXAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhx(fXAngle),      mat4r,      m4Results[14],sizeof(mat4), "mat4r = mat4rotate_lhx(fXAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhy(fYAngle),      mat4r,      m4Results[15],sizeof(mat4), "mat4r = mat4rotate_rhy(fYAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhy(fYAngle),      mat4r,      m4Results[16],sizeof(mat4), "mat4r = mat4rotate_lhy(fYAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhz(fZAngle),      mat4r,      m4Results[17],sizeof(mat4), "mat4r = mat4rotate_rhz(fZAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhz(fZAngle),      mat4r,      m4Results[18],sizeof(mat4), "mat4r = mat4rotate_lhz(fZAngle)      ",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhxy(fXAngle,fYAngle),mat4r,   m4Results[19],sizeof(mat4), "mat4r = mat4rotate_rhxy(fXAngle,fYAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhxy(fXAngle,fYAngle),mat4r,   m4Results[20],sizeof(mat4), "mat4r = mat4rotate_lhxy(fXAngle,fYAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhxz(fXAngle,fZAngle),mat4r,   m4Results[21],sizeof(mat4), "mat4r = mat4rotate_lhxy(fXAngle,fYAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhxz(fXAngle,fZAngle),mat4r,   m4Results[22],sizeof(mat4), "mat4r = mat4rotate_lhxz(fXAngle,fZAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhyz(fYAngle,fZAngle),mat4r,   m4Results[23],sizeof(mat4), "mat4r = mat4rotate_rhyz(fYAngle,fZAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhyz(fYAngle,fZAngle),mat4r,   m4Results[24],sizeof(mat4), "mat4r = mat4rotate_lhyz(fYAngle,fZAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_rhxyz(fXAngle,fYAngle,fZAngle),mat4r,m4Results[25],sizeof(mat4),"mat4r=mat4rotate_rhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
  TestResult(mat4r = mat4rotate_lhxyz(fXAngle,fYAngle,fZAngle),mat4r,m4Results[26],sizeof(mat4),"mat4r=mat4rotate_lhxyz(fXAngle,fYAngle,fZAngle)",FCN_ERROR);
 
  TestResult(mat4r = mat4translate_rh(1.0,2.0,3.0),mat4r,      m4Results[27],sizeof(mat4), "mat4r = mat4translate_rh(1.0,2.0,3.0)",FCN_ERROR);
  TestResult(mat4r = mat4translate_lh(1.0,2.0,3.0),mat4r,      m4Results[28],sizeof(mat4), "mat4r = mat4translate_rh(1.0,2.0,3.0)",FCN_ERROR);

  TestResult(mat4r = translate_rh(*(v3a.vec)),     mat4r,      m4Results[27],sizeof(mat4), "mat4r = translate_rh(*(v3a.vec))     ",FCN_ERROR);
  TestResult(mat4r = translate_lh(*(v3a.vec)),     mat4r,      m4Results[28],sizeof(mat4), "mat4r = translate_rh(*(v3a.vec))     ",FCN_ERROR);
  TestResult(mat4r = translate_rh(*(v4a.vec)),     mat4r,      m4Results[27],sizeof(mat4), "mat4r = translate_rh(*(v4a.vec))     ",FCN_ERROR);
  TestResult(mat4r = translate_lh(*(v4a.vec)),     mat4r,      m4Results[28],sizeof(mat4), "mat4r = translate_rh(*(v4a.vec))     ",FCN_ERROR);

  TestResult(mat4r = mat4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0),mat4r,m4Results[29],sizeof(mat4),"mat4r=mat4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0)",FCN_ERROR);
  TestResult(mat4r = mat4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,1),mat4r,m4Results[30],sizeof(mat4),"mat4r=mat4ortho(-1.0,1.0,-1.0,1.0,-3.0,20.0,0)",FCN_ERROR);

  TestResult(mat4r = mat4perspective(fXAngle,1.0,1.0,-4.0,20.0,0),mat4r,m4Results[31],sizeof(mat4),"mat4r=mat4perspective(fXAngle,1.0,1.0,-4.0,20.0,0)",FCN_ERROR);
  TestResult(mat4r = mat4perspective(fXAngle,1.0,1.0,-4.0,20.0,1),mat4r,m4Results[32],sizeof(mat4),"mat4r=mat4perspective(fXAngle,1.0,1.0,-4.0,20.0,0)",FCN_ERROR);

  TestResult(mat4r = mat4cubemap(0),               mat4r,      m4Results[33],sizeof(mat4), "mat4r = mat4cubemap(0)               ",FCN_ERROR);
  TestResult(mat4r = mat4cubemap(1),               mat4r,      m4Results[34],sizeof(mat4), "mat4r = mat4cubemap(0)               ",FCN_ERROR);
  TestResult(mat4r = mat4cubemap(2),               mat4r,      m4Results[35],sizeof(mat4), "mat4r = mat4cubemap(0)               ",FCN_ERROR);
  TestResult(mat4r = mat4cubemap(3),               mat4r,      m4Results[36],sizeof(mat4), "mat4r = mat4cubemap(0)               ",FCN_ERROR);
  TestResult(mat4r = mat4cubemap(5),               mat4r,      m4Results[37],sizeof(mat4), "mat4r = mat4cubemap(0)               ",FCN_ERROR);

  TestResult(mat3r = mat3from_mat4(*(m4a.m)),      mat3r,      m3Results[24],sizeof(mat3), "mat3r = mat3from_mat4(*(m4a.m))      ",FCN_ERROR);
  TestResult(mat4r = mat4from_mat3(*(m3a.m)),      mat4r,      m4Results[38],sizeof(mat4), "mat4r = mat4from_mat3(*(m3a.m))      ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> quat Operations\n\n");

  quat q0(1.0,2.0,3.0,1.0);
  quat q1(1.0,2.0,3.0,1.0);
  quat q3;
  quat q4;

  TestResult(q3 = q0,                              *(q3.q),    qResults[0],sizeof(quaternion),"q3 = q4                              ",FCN_ERROR);
  TestResult(q3 += q0,                             *(q3.q),    qResults[1],sizeof(quaternion),"q3 += q0                             ",FCN_ERROR);
  q3 = q0;
  TestResult(q3 *= q0,                             *(q3.q),    qResults[1],sizeof(quaternion),"q3 *= q0                             ",FCN_ERROR);
  q3 = q0;
  TestResult(q3.inverse(),                         *(q3.q),    qResults[2],sizeof(quaternion),"q3.inverse()                         ",FCN_ERROR);
  q3 = q0;

#if 0
  // XXX: Invalid on this processor
  q3.normalize();
#endif

  q3  = q0;
  TestResult(q3->x = 2.0,                          *(q3.q),    qResults[4],sizeof(quaternion),"q3->x = 2.0                          ",FCN_ERROR);
  TestResult(q3 = q0 + q1,                         *(q3.q),    qResults[1],sizeof(quaternion),"q3 = q0 + q1                         ",FCN_ERROR);
  TestResult(q3 = q0 * q1,                         *(q3.q),    qResults[1],sizeof(quaternion),"q3 = q0 * q1                         ",FCN_ERROR);

#if 0
  // XXX: Invalid on this processor
  q3 = normalize(q0);
#endif

  TestResult(q3 = quatFromAxis(v3a,fXAngle),       *(q3.q),    qResults[7],sizeof(quaternion),"q3 = quatFromAxis(v3a,fXAngle)       ",FCN_ERROR);
  TestResult(q3 = q0 * q1,                         *(q3.q),    qResults[1],sizeof(quaternion),"q3 = q0 * q1                         ",FCN_ERROR);
  TestResult(m4d = quatToM4(q0),                   *(m4d.m),   m4Results[39],sizeof(mat4),    "m4d = quatToM4(q0)                   ",FCN_ERROR);
  TestResult(q3 = quatFromM3(m3a),                 *(q3.q),    qResults[5],sizeof(quaternion),"q3 = quatFromM3(m3a)                 ",FCN_ERROR);
  TestResult(q3 = quatFromM4(m4a),                 *(q3.q),    qResults[6],sizeof(quaternion),"q3 = quatFromM4(m4a)                 ",FCN_ERROR);
  TestResult(mat3r = (mat3)q0,                     mat3r,      m3Results[25],sizeof(mat3),    "mat3r = (mat3)q0                     ",FCN_ERROR);
  TestResult(mat4r = (mat4)q0,                     mat4r,      m4Results[39],sizeof(mat4),    "mat4r = (mat4)q0                     ",FCN_ERROR);
  TestResult(m3c = (m3)q0,                         *(m3c.m),   m3Results[25],sizeof(mat3),    "m3c = (m3)q0                         ",FCN_ERROR);
  TestResult(m4c = (m4)q0,                         *(m4c.m),   m4Results[39],sizeof(mat4),    "m4c = (m4)q0                         ",FCN_ERROR);

#if 0
  // XXX: Invalid on this processor
  fr = dot(q0,q1);
#endif

  TestResult(q3 = quatSlerp(0.5,q0,q1),            *(q3.q),    qResults[0],sizeof(quaternion),"q3 = quatSlerp(0.5,q0,q1)            ",FCN_ERROR);

  quaternion qr;

  TestResult(qr = *(q0.q) + *(q1.q),               qr,         qResults[1],sizeof(quaternion),"qr = *(q0.q) + *(q1.q)               ",FCN_ERROR);
  TestResult(qr = *(q0.q) * *(q1.q),               qr,         qResults[1],sizeof(quaternion),"qr = *(q0.q) * *(q1.q)               ",FCN_ERROR);

#if 0
  // XXX: Invalid on this processor
  TestResult(qr = normalize(*(q0.q)),              qr,         qResults[x],sizeof(quaternion),"qr = normalize(*(q0.q))              ",FCN_ERROR);
#endif
  TestResult(qr = inverse(*(q0.q)),                qr,         qResults[2],sizeof(quaternion),"qr = inverse(*(q0.q))                ",FCN_ERROR);
  TestResult(qr = quaternionFromAxis(v3a,fXAngle), qr,         qResults[7],sizeof(quaternion),"qr = quaternionFromAxis(v3a,fXAngle) ",FCN_ERROR);
  TestResult(mat4r = quatToMat4(*(q0.q)),          mat4r,      m4Results[39],sizeof(mat4),    "mat4r = quatToMat4(*(q0.q))          ",FCN_ERROR);
  TestResult(qr = quatFromMat3(*(m3a.m)),          qr,         qResults[5],sizeof(quaternion),"qr = quatFromMat3(*(m3a.m))          ",FCN_ERROR);
  TestResult(qr = quatFromMat4(*(m4a.m)),          qr,         qResults[6],sizeof(quaternion),"qr = quatFromMat4(*(m4a.m))          ",FCN_ERROR);
  TestResult(qr = quatSlerp(0.5,*(q0.q),*(q1.q)),  qr,         qResults[0],sizeof(quaternion),"qr = quatSlerp(0.5,*(q0.q),*(q1.q))  ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v2array Operations\n\n");

  v2array v2aa(6,v2Results);
  v2array v2ab(6,v2Results);
  v2array v2ad(1.0,2.0);
  v2array v2ac = v2aa;

  TestResult(v2ac += 2.0,                          v2ac.m_Vec2Array[0],v2Results[10],6*sizeof(vec2),"v2ac += 2.0                          ",FCN_ERROR);
  TestResult(v2ac -= 2.0,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac -= 2.0                          ",FCN_ERROR);
  TestResult(v2ac *= 2.0,                          v2ac.m_Vec2Array[0],v2Results[16],6*sizeof(vec2),"v2ac *= 2.0                          ",FCN_ERROR);
  TestResult(v2ac /= 2.0,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac /= 2.0                          ",FCN_ERROR);

  TestResult(v2ac += v2a,                          v2ac.m_Vec2Array[0],v2Results[22],6*sizeof(vec2),"v2ac += v2a                          ",FCN_ERROR);
  TestResult(v2ac -= v2a,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac -= v2a                          ",FCN_ERROR);
  TestResult(v2ac *= v2a,                          v2ac.m_Vec2Array[0],v2Results[28],6*sizeof(vec2),"v2ac *= v2a                          ",FCN_ERROR);
  TestResult(v2ac /= v2a,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac /= v2a                          ",FCN_ERROR);

  TestResult(v2ac += *(v2a.vec),                   v2ac.m_Vec2Array[0],v2Results[22],6*sizeof(vec2),"v2ac += *(v2a.vec)                   ",FCN_ERROR);
  TestResult(v2ac -= *(v2a.vec),                   v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac -= *(v2a.vec)                   ",FCN_ERROR);
  TestResult(v2ac *= *(v2a.vec),                   v2ac.m_Vec2Array[0],v2Results[28],6*sizeof(vec2),"v2ac *= *(v2a.vec)                   ",FCN_ERROR);
  TestResult(v2ac /= *(v2a.vec),                   v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac /= *(v2a.vec)                   ",FCN_ERROR);

  TestResult(v2ac += v2aa,                         v2ac.m_Vec2Array[0],v2Results[16],6*sizeof(vec2),"v2ac += v2aa                         ",FCN_ERROR);
  TestResult(v2ac -= v2aa,                         v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac -= v2aa                         ",FCN_ERROR);
  TestResult(v2ac *= v2aa,                         v2ac.m_Vec2Array[0],v2Results[34],6*sizeof(vec2),"v2ac *= v2aa                         ",FCN_ERROR);
  TestResult(v2ac /= v2aa,                         v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2ac /= v2aa                         ",FCN_ERROR);

  TestResult(v2ac *= m2a,                          v2ac.m_Vec2Array[0],v2Results[40],6*sizeof(vec2),"v2ac *= m2a                          ",FCN_ERROR);
  v2ac  = v2aa;
  TestResult(v2ac *= *(m2a.m),                     v2ac.m_Vec2Array[0],v2Results[40],6*sizeof(vec2),"v2ac *= *(m2a.m)                     ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v2buf Operations\n\n");
  
  v2buf v2ba(6,8,4,v2Results);
  v2buf v2bb(6,8,4,v2Results);
  v2buf v2bc(4,1.0,2.0);
  v2buf v2bd = v2ba;

  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd = v2ba                          ",FCN_ERROR);

  v2bd += 2.0;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[10],6*sizeof(vec2),"v2bd += 2.0                          ",FCN_ERROR);
  v2bd -= 2.0;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd -= 2.0                          ",FCN_ERROR);
  v2bd *= 2.0;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[16],6*sizeof(vec2),"v2bd *= 2.0                          ",FCN_ERROR);
  v2bd /= 2.0;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd /= 2.0                          ",FCN_ERROR);

  v2bd += v2a;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[22],6*sizeof(vec2),"v2bd += v2a                          ",FCN_ERROR);
  v2bd -= v2a;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd -= v2a                          ",FCN_ERROR);
  v2bd *= v2a;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[28],6*sizeof(vec2),"v2bd *= v2a                          ",FCN_ERROR);
  v2bd /= v2a;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd /= v2a                          ",FCN_ERROR);

  v2bd += *(v2a.vec);
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[22],6*sizeof(vec2),"v2bd += *(v2a.vec)                   ",FCN_ERROR);
  v2bd -= *(v2a.vec);
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd -= *(v2a.vec)                   ",FCN_ERROR);
  v2bd *= *(v2a.vec);
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[28],6*sizeof(vec2),"v2bd *= *(v2a.vec)                   ",FCN_ERROR);
  v2bd /= *(v2a.vec);
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd /= *(v2a.vec)                   ",FCN_ERROR);

  v2bd += v2ba;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[16],6*sizeof(vec2),"v2bd += v2ba                         ",FCN_ERROR);
  v2bd -= v2ba;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd -= v2ba                         ",FCN_ERROR);
  v2bd *= v2ba;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[34],6*sizeof(vec2),"v2bd *= v2ba                         ",FCN_ERROR);
  v2bd /= v2ba;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[ 0],6*sizeof(vec2),"v2bd /= v2ba                         ",FCN_ERROR);

  v2bd = v2ba;
  v2bd *= m2a;
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[40],6*sizeof(vec2),"v2bd *= m2a                          ",FCN_ERROR);
  v2bd = v2ba;
  v2bd *= *(m2a.m);
  TestResult(v2ac = v2bd,                          v2ac.m_Vec2Array[0],v2Results[40],6*sizeof(vec2),"v2bd *= *(m2a.m)                     ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v3array Operations\n\n");

  v3array v3aa(6,v3Results);
  v3array v3ab(6,v3Results);
  v3array v3ar;
  v3array v3ap = v3aa;

  TestResult(v3ar=v3aa,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar=v3aa                            ",FCN_ERROR);
  TestResult(v3ar=v3ap,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar=v3ap                            ",FCN_ERROR);

  TestResult(v3ar += 2.0,                   *((vec3*)v3ar.m_VecArray), v3Results[ 6],6*sizeof(vec3),"v3ar += 2.0                          ",FCN_ERROR);
  TestResult(v3ar -= 2.0,                   *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar -= 2.0                          ",FCN_ERROR);
  TestResult(v3ar *= 2.0,                   *((vec3*)v3ar.m_VecArray), v3Results[12],6*sizeof(vec3),"v3ar *= 2.0                          ",FCN_ERROR);
  TestResult(v3ar /= 2.0,                   *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar /= 2.0                          ",FCN_ERROR);

  TestResult(v3ar += v3a,                   *((vec3*)v3ar.m_VecArray), v3Results[18],6*sizeof(vec3),"v3ar += v3a                          ",FCN_ERROR);
  TestResult(v3ar -= v3a,                   *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar -= v3a                          ",FCN_ERROR);
  TestResult(v3ar *= v3a,                   *((vec3*)v3ar.m_VecArray), v3Results[24],6*sizeof(vec3),"v3ar *= v3a                          ",FCN_ERROR);
  TestResult(v3ar /= v3a,                   *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar /= v3a                          ",FCN_ERROR);

  TestResult(v3ar += *(v3a.vec),            *((vec3*)v3ar.m_VecArray), v3Results[18],6*sizeof(vec3),"v3ar += *(v3a.vec)                   ",FCN_ERROR);
  TestResult(v3ar -= *(v3a.vec),            *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar -= *(v3a.vec)                   ",FCN_ERROR);
  TestResult(v3ar *= *(v3a.vec),            *((vec3*)v3ar.m_VecArray), v3Results[24],6*sizeof(vec3),"v3ar *= *(v3a.vec)                   ",FCN_ERROR);
  TestResult(v3ar /= *(v3a.vec),            *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar /= *(v3a.vec)                   ",FCN_ERROR);

  TestResult(v3ar += v3aa,                  *((vec3*)v3ar.m_VecArray), v3Results[12],6*sizeof(vec3),"v3ar += v3aa                         ",FCN_ERROR);
  TestResult(v3ar -= v3aa,                  *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar -= v3aa                         ",FCN_ERROR);
  TestResult(v3ar *= v3aa,                  *((vec3*)v3ar.m_VecArray), v3Results[30],6*sizeof(vec3),"v3ar *= v3aa                         ",FCN_ERROR);
  TestResult(v3ar /= v3aa,                  *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3ar /= v3aa                         ",FCN_ERROR);

  TestResult(v3ar *= m3a,                   *((vec3*)v3ar.m_VecArray), v3Results[36],6*sizeof(vec3),"v3ar *= m3a,                         ",FCN_ERROR);
  v3ar = v3aa;
  TestResult(v3ar *= *(m3a.m),              *((vec3*)v3ar.m_VecArray), v3Results[36],6*sizeof(vec3),"v3ar *= *(m3a.m)                     ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v3array Operations\n\n");

  v3buf v3ba(6,32,16,v3Results);
  v3buf v3bb(6,32,16,v3Results);
  v3buf v3bp = v3ba;
  v3buf v3bd = v3ba;

  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd = v3ba (memberwise init)        ",FCN_ERROR);
  v3bd = v3ba;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd = v3ba (assignment)             ",FCN_ERROR);
  v3bd += 2.0;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 6],6*sizeof(vec3),"v3bd += 2.0                          ",FCN_ERROR);
  v3bd -= 2.0;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd -= 2.0                          ",FCN_ERROR);
  v3bd *= 2.0;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[12],6*sizeof(vec3),"v3bd *= 2.0                          ",FCN_ERROR);
  v3bd /= 2.0;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd /= 2.0                          ",FCN_ERROR);

  v3bd += v3a;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[18],6*sizeof(vec3),"v3bd += v3a                          ",FCN_ERROR);
  v3bd -= v3a;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd -= v3a                          ",FCN_ERROR);
  v3bd *= v3a;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[24],6*sizeof(vec3),"v3bd *= v3a                          ",FCN_ERROR);
  v3bd /= v3a;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd /= v3a                          ",FCN_ERROR);

  v3bd += *(v3a.vec);
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[18],6*sizeof(vec3),"v3bd += *(v3a.vec)                   ",FCN_ERROR);
  v3bd -= *(v3a.vec);
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd -= *(v3a.vec)                   ",FCN_ERROR);
  v3bd *= *(v3a.vec);
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[24],6*sizeof(vec3),"v3bd *= *(v3a.vec)                   ",FCN_ERROR);
  v3bd /= *(v3a.vec);
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd /= *(v3a.vec)                   ",FCN_ERROR);

  v3bd += v3ba;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[12],6*sizeof(vec3),"v3bd += v3ba                         ",FCN_ERROR);
  v3bd -= v3ba;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd -= v3ba                         ",FCN_ERROR);
  v3bd *= v3ba;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[30],6*sizeof(vec3),"v3bd *= v3ba                         ",FCN_ERROR);
  v3bd /= v3ba;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[ 0],6*sizeof(vec3),"v3bd /= v3ba                         ",FCN_ERROR);

  v3bd *= m3a;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[36],6*sizeof(vec3),"v3bd *= m3a                          ",FCN_ERROR);
  v3bd = v3ba;
  v3bd *= *(m3a.m);
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[36],6*sizeof(vec3),"v3bd *= *(m3a.m)                     ",FCN_ERROR);

  // Add single floating point elements and exercise math
  //

  v3buf v3fl0(16,1.0,2.0,3.0);

  v3bd = v3ba;
  v3bd += v3fl0;
  TestResult(v3ar=v3bd,                     *((vec3*)v3ar.m_VecArray), v3Results[42],6*sizeof(vec3),"v3bd += v3fl0                        ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v4array Operations\n\n");

  v4array v4aa(6,v4Results);
  v4array v4ab(6,v4Results);
  v4array v4ar;
  v4array v4ap = v4aa;

  TestResult(v4ar=v4aa,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar=v4aa (assignment)               ",FCN_ERROR);
  TestResult(v4ar=v4ap,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar=v4ap (memberwise initialization)",FCN_ERROR);

  TestResult(v4ar += 2.0,                   *((vec4*)v4ar.m_VecArray), v4Results[ 6],6*sizeof(vec4),"v4ar += 2.0                          ",FCN_ERROR);
  TestResult(v4ar -= 2.0,                   *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar -= 2.0                          ",FCN_ERROR);
  TestResult(v4ar *= 2.0,                   *((vec4*)v4ar.m_VecArray), v4Results[12],6*sizeof(vec4),"v4ar *= 2.0                          ",FCN_ERROR);
  TestResult(v4ar /= 2.0,                   *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar /= 2.0                          ",FCN_ERROR);

  TestResult(v4ar += v4a,                   *((vec4*)v4ar.m_VecArray), v4Results[18],6*sizeof(vec4),"v4ar += v4a                          ",FCN_ERROR);
  TestResult(v4ar -= v4a,                   *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar -= v4a                          ",FCN_ERROR);
  TestResult(v4ar *= v4a,                   *((vec4*)v4ar.m_VecArray), v4Results[24],6*sizeof(vec4),"v4ar *= v4a                          ",FCN_ERROR);
  TestResult(v4ar /= v4a,                   *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar /= v4a                          ",FCN_ERROR);

  TestResult(v4ar += *(v4a.vec),            *((vec4*)v4ar.m_VecArray), v4Results[18],6*sizeof(vec4),"v4ar += *(v4a.vec)                   ",FCN_ERROR);
  TestResult(v4ar -= *(v4a.vec),            *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar -= *(v4a.vec)                   ",FCN_ERROR);
  TestResult(v4ar *= *(v4a.vec),            *((vec4*)v4ar.m_VecArray), v4Results[24],6*sizeof(vec4),"v4ar *= *(v4a.vec)                   ",FCN_ERROR);
  TestResult(v4ar /= *(v4a.vec),            *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar /= *(v4a.vec)                   ",FCN_ERROR);

  TestResult(v4ar += v4aa,                  *((vec4*)v4ar.m_VecArray), v4Results[12],6*sizeof(vec4),"v4ar += v4aa                         ",FCN_ERROR);
  TestResult(v4ar -= v4aa,                  *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar -= v4aa                         ",FCN_ERROR);
  TestResult(v4ar *= v4aa,                  *((vec4*)v4ar.m_VecArray), v4Results[30],6*sizeof(vec4),"v4ar *= v4aa                         ",FCN_ERROR);
  TestResult(v4ar /= v4aa,                  *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar /= v4aa                         ",FCN_ERROR);

  TestResult(v4ar *= m4a,                   *((vec4*)v4ar.m_VecArray), v4Results[36],6*sizeof(vec4),"v4ar *= m4a                          ",FCN_ERROR);
  v4ar = v4aa;
  TestResult(v4ar *= *(m4a.m),              *((vec4*)v4ar.m_VecArray), v4Results[36],6*sizeof(vec4),"v4ar *= *(m4a.m)                     ",FCN_ERROR);

  v4array v4af0(1.0,2.0,3.0,4.0);
  v4ar = v4aa;
  TestResult(v4ar += v4af0,                 *((vec4*)v4ar.m_VecArray), v4Results[42],6*sizeof(vec4),"v4ar += v4af0                        ",FCN_ERROR);

  fprintf(stdout,"\n----------------------> v4buf Operations\n\n");

  v4buf v4ba(6,32,16,v4Results);
  v4buf v4bb(6,32,16,v4Results);
  v4buf v4bp = v4ba;
  v4buf v4bd = v4ba;

  // XXX: Add an empty constructor
  //

  v4bd = v4ba;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar=v4bd (assignment)               ",FCN_ERROR);
  TestResult(v4ar=v4bp,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar=v4bd (memberwise initialization)",FCN_ERROR);

  v4bd += 2.0;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 6],6*sizeof(vec4),"v4bd += 2.0                          ",FCN_ERROR);
  v4bd -= 2.0;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4ar=v4bd                            ",FCN_ERROR);
  v4bd *= 2.0;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[12],6*sizeof(vec4),"v4bd *= 2.0                          ",FCN_ERROR);
  v4bd /= 2.0;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd /= 2.0                          ",FCN_ERROR);

  v4bd += v4a;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[18],6*sizeof(vec4),"v4bd += v4a                          ",FCN_ERROR);
  v4bd -= v4a;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd -= v4a                          ",FCN_ERROR);
  v4bd *= v4a;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[24],6*sizeof(vec4),"v4bd *= v4a                          ",FCN_ERROR);
  v4bd /= v4a;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd /= v4a                          ",FCN_ERROR);

  v4bd += *(v4a.vec);
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[18],6*sizeof(vec4),"v4bd += *(v4a.vec)                   ",FCN_ERROR);
  v4bd -= *(v4a.vec);
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd -= *(v4a.vec)                   ",FCN_ERROR);
  v4bd *= *(v4a.vec);
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[24],6*sizeof(vec4),"v4bd *= *(v4a.vec)                   ",FCN_ERROR);
  v4bd /= *(v4a.vec);
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd /= *(v4a.vec)                   ",FCN_ERROR);

  v4bd += v4ba;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[12],6*sizeof(vec4),"v4bd += v4ba                         ",FCN_ERROR);
  v4bd -= v4ba;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd -= v4ba                         ",FCN_ERROR);
  v4bd *= v4ba;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[30],6*sizeof(vec4),"v4bd *= v4ba                         ",FCN_ERROR);
  v4bd /= v4ba;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[ 0],6*sizeof(vec4),"v4bd /= v4ba                         ",FCN_ERROR);

  v4bd *= m4a;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[36],6*sizeof(vec4),"v4bd *= m4a                          ",FCN_ERROR);
  v4bd = v4ba;
  v4bd *= *(m4a.m);
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[36],6*sizeof(vec4),"v4bd *= *(m4a.m)                     ",FCN_ERROR);

  v4buf v4bfl0(32,16,1.0f,2.0f,3.0f,4.0f);

  v4bd = v4ba;
  v4bd += v4bfl0;
  TestResult(v4ar=v4bd,                     *((vec4*)v4ar.m_VecArray), v4Results[48],6*sizeof(vec4),"v4bd += v4bfl0                       ",FCN_ERROR);

  fprintf(stdout,"Completed\n");

  return 0;
}
