#define __ADVANCED_ALIGNED_LIB
#define __REGRESSION_TEST

#include <CVector.h>
#include <Vecasm.h>
#include <Vecstd.h>

/* -----------------------------------------------------------
 * Error message list
 * ----------------------------------------------------------- */

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
 * Floating point test result list
 * ----------------------------------------------------------- */

float FloatList[] = {
  1.5,
  4.0,
  11.0,
  2.2360680103302002,
  10.0,
  36.0,
  78.0,
  105.0,
  21.0,
  122.0,
  2.2360680103302002,
  5.0,
  7.8102498054504395,
  9.2195444107055664,
  3.6055512428283691,
  10.0,
  14.0, 77.0, 194.0, 149.0, 50.0, 693.0, // 16
  3.7416574954986572,                    // 22
  8.7749643325805664,
  13.928388595581055,
  12.206555366516113,
  7.0710678100585937,
  26.324893951416016,
  30.0,174.0,446.0,966.0,230.0,126.0,   // 28
  5.4772257804870605,                   // 34
  13.190905570983887,
  21.118711471557617,
  31.080539703369141,
  15.165750503540039,
  11.224971771240234,
};

vec2 v2Results[] = {
  { 1.0f, 2.0f }, { 3.0f, 4.0f }, { 5.0f, 6.0f }, // 0-2
  { 6.0f, 7.0f }, { 2.0f, 3.0f }, { 6.0f, 8.0f }, // 3-5
  {-1.0f,-2.0f }, { 4.0f, 6.0f }, { 2.0f, 2.0f }, // 6-8
  { 3.0f, 8.0f }, { 1.0f, 1.0f }, { 1.0f, 4.0f }, // 9-11
  { 0.6f, 0.8f }, { 5.0f,11.0f }, // 12-13

  { 2.0f, 4.0f }, { 4.0f, 6.0f }, { 6.0f, 8.0f }, // 14-16
  { 7.0f, 9.0f }, { 3.0f, 5.0f }, { 7.0f,10.0f }, // 17-19,

  { 2.0f, 4.0f }, { 6.0f, 8.0f }, {10.0f,12.0f }, // 20-22
  {12.0f,14.0f }, { 4.0f, 6.0f }, {12.0f,16.0f }, // 23-25

  { 1.0f, 4.0f }, { 3.0f, 8.0f }, { 5.0f,12.0f }, // 26-28
  { 6.0f,15.0f }, { 2.0f, 6.0f }, { 6.0f,16.0f }, // 29-31

  { 1.5f, 3.0f }, { 3.5f, 5.0f }, { 5.5f, 7.0f }, // 32-34
  { 6.5f, 8.0f }, { 2.5f, 4.0f }, { 6.5f, 9.0f }, // 35-37

  { 1.0f, 4.0f }, { 9.0f,16.0f }, {25.0f,36.0f }, // 38-40
  {36.0f,49.0f }, { 4.0f, 9.0f }, {36.0f,64.0f }, // 41-43

  { 0.44721359014511108, 0.89442718029022217 },   // 44
  { 0.6000000238418579,  0.80000001192092896 },   // 45
  { 0.64018440246582031, 0.76822125911712646 },   // 46
  { 0.65079134702682495, 0.75925660133361816 },   // 47
  { 0.55470019578933716, 0.83205032348632813 },   // 48
  { 0.60000002384185791, 0.80000001192092896 },   // 49

  {  2.0,  4.0 }, {  6.0,  8.0 }, { 10.0, 12.0 }, // 50-52
  { 12.0, 14.0 }, {  4.0,  6.0 }, { 12.0, 16.0 }, // 53-55

  {  0.0,  0.0 }, {  0.0,  0.0 }, {  0.0,  0.0 }, // 56-58 
  {  0.0,  0.0 }, {  0.0,  0.0 }, {  0.0,  0.0 }, // 59-61

  {  1.0,  4.0 }, {  9.0, 16.0 }, { 25.0, 36.0 }, // 62-64
  { 36.0, 49.0 }, {  4.0,  9.0 }, { 36.0, 64.0 }, // 65-67

  {  1.0,  1.0 }, {  1.0,  1.0 }, {  1.0,  1.0 }, // 68-70
  {  1.0,  1.0 }, {  1.0,  1.0 }, {  1.0,  1.0 }, // 71-73

  {  2.0,  3.0 }, {  4.0,  5.0 }, {  6.0,  7.0 }, // 74-76
  {  7.0,  8.0 }, {  3.0,  4.0 }, {  7.0,  9.0 }, // 77-79

  {  0.0,  1.0 }, {  2.0,  3.0 }, {  4.0,  5.0 }, // 80-82
  {  5.0,  6.0 }, {  1.0,  2.0 }, {  5.0,  7.0 }, // 83-85

  {  2.0,  4.0 }, {  4.0,  6.0 }, {  6.0, 8.0 }, // 86-88
  {  7.0,  9.0 }, {  3.0,  5.0 }, {  7.0,10.0 }, // 80-91

  { -1.0f,-2.0f }, {-3.0f,-4.0f}, {-5.0f,-6.0f}, // 92-94
  { -6.0f,-7.0f }, {-2.0f,-3.0f}, {-6.0f,-8.0f}, // 95-97

  {   0.0,  0.0 }, { 2.0,  2.0 }, {  4.0,  4.0 }, // 98-100
  {   5.0,  5.0 }, { 1.0,  1.0 }, {  5.0,  6.0 }, // 101-103

  {   1.0,  4.0 }, { 3.0,  8.0 }, {  5.0, 12.0 }, // 104-106
  {   6.0, 14.0 }, { 2.0,  6.0 }, {  6.0, 16.0 }, // 107-109

  {   1.0,  1.0 }, { 3.0,  2.0 }, {  5.0,  3.0 }, // 110-112
  {   6.0,  3.5 }, { 2.0,  1.5 }, {  6.0,  4.0 }, // 113-115
};

vec3 v3Results[] = {
  { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }, // 0-2
  { 6.0f, 7.0f, 8.0f }, { 3.0f, 4.0f, 5.0f }, {12.0f,15.0f,18.0f }, // 3-5
  {-1.0f,-2.0f,-3.0f }, { 5.0f, 7.0f, 9.0f }, { 3.0f, 3.0f, 3.0f }, // 6-8
  { 4.0f,10.0f,18.0f }, { 1.0f, 1.0f, 1.0f }, { 2.5f, 3.5f, 4.5f }, // 9-11
  { 1.0f, 4.0f, 9.0f }, { 1.0f, 1.0f, 1.0f }, {-3.0f, 6.0f,-3.0f }, // 12-14
  {14.0f,32.0f,50.0f },                                             // 15
  {-1.0f,-2.0f,-3.0f }, {-4.0f,-5.0f,-6.0f }, {-7.0f,-8.0f,-9.0f }, // 16-18

  { 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f }, { 8.0f, 9.0f,10.0f }, // 19-21
  { 7.0f, 8.0f, 9.0f }, { 4.0f, 5.0f, 6.0f }, {13.0f,16.0f,19.0f }, // 22-24

  { 2.0f, 4.0f, 6.0f }, { 8.0f,10.0f,12.0f }, {14.0f,16.0f,18.0f }, // 25-27
  {12.0f,14.0f,16.0f }, { 6.0f, 8.0f,10.0f }, {24.0f,30.0f,36.0f }, // 28-30

  { 2.0f, 4.0f, 6.0f }, { 5.0f, 7.0f, 9.0f }, { 8.0f,10.0f,12.0f }, // 31-33
  { 7.0f, 9.0f,11.0f }, { 4.0f, 6.0f, 8.0f }, {13.0f,17.0f,21.0f }, // 34-36

  { 1.0f, 4.0f, 9.0f }, { 4.0f,10.0f,18.0f }, { 7.0f,16.0f,27.0f }, // 37-39
  { 6.0f,14.0f,24.0f }, { 3.0f, 8.0f,15.0f }, {12.0f,30.0f,54.0f }, // 40-42

  { 1.0f, 4.0f, 9.0f }, {16.0f,25.0f,36.0f }, {49.0f,64.0f,81.0f },   // 43-45
  {36.0f,49.0f,64.0f }, { 9.0f,16.0f,25.0f }, {144.0f,225.0f,324.0f}, // 46-48

  { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, // 49-51
  { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, // 52-54

  { 0.26726123690605164, 0.53452247381210327, 0.80178368091583252 }, // 55-60
  { 0.45584231615066528, 0.56980288028717041, 0.68376344442367554 },
  { 0.50257068872451782, 0.57436650991439819, 0.64616233110427856 },
  { 0.49153915047645569, 0.57346236705780029, 0.65538555383682251 },
  { 0.42426407337188721, 0.56568545103073120, 0.70710676908493042 },
  { 0.45584228634834290, 0.56980288028717041, 0.68376344442367554 },

  {  1.0,  2.0,  3.0 }, {  4.0,  5.0,  6.0 }, {  7.0,  8.0,  9.0 },  // 61-63
  {  6.0,  7.0,  8.0 }, {  3.0,  4.0,  5.0 }, { 12.0, 15.0, 18.0 },  // 64-66

  { 0.26726123690605164, 0.53452247381210327, 0.80178374052047729 }, // 67-72
  { 0.45584231615066528, 0.56980288028717041, 0.68376344442367554 },
  { 0.50257068872451782, 0.57436650991439819, 0.64616233110427856 },
  { 0.49153915047645569, 0.57346236705780029, 0.65538555383682251 },
  { 0.42426407337188721, 0.56568545103073120, 0.70710676908493042 },
  { 0.45584231615066528, 0.56980288028717041, 0.68376344442367554 },
};

vec4 v4Results[] = {
  { 1.0f, 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 14.0f, 15.0f, 16.0f, 17.0f }, // 0-3
  { 6.0f, 7.0f, 8.0f, 9.0f }, { 4.0f, 5.0f, 6.0f, 7.0f }, {15.0f, 18.0f, 21.0f, 24.0f }, { -1.0f, -2.0f, -3.0f, -4.0f }, // 4-7
  { 6.0f, 8.0f,10.0f,12.0f }, { 4.0f, 4.0f, 4.0f, 4.0f }, { 5.0f, 12.0f, 21.0f, 32.0f }, {  1.0f,  1.0f,  1.0f,  1.0f }, // 8-11
  { 3.0f, 4.0f, 5.0f, 6.0f }, { 1.0f, 4.0f, 9.0f,16.0f }, {-4.0f,  8.0f, -4.0f,  0.0f }, { 30.0f, 70.0f,110.0f,150.0f }, // 12-15
  {  2.0,  3.0,  4.0,  5.0 }, {  6.0,  7.0,  8.0,  9.0 }, { 10.0, 11.0, 12.0, 13.0 },                                    // 16-18
  { 15.0, 16.0, 17.0, 18.0 }, {  7.0,  8.0,  9.0, 10.0 }, {  5.0,  6.0,  7.0,  8.0 },                                    // 19-21

  {  2.0,  4.0,  6.0,  8.0 }, { 10.0, 12.0, 14.0, 16.0 }, { 18.0, 20.0, 22.0, 24.0 },                                    // 22-24
  { 28.0, 30.0, 32.0, 34.0 }, { 12.0, 14.0, 16.0, 18.0 }, {  8.0, 10.0, 12.0, 14.0 },                                    // 25-27

  { -1.0, -2.0, -3.0, -4.0 }, { -5.0, -6.0, -7.0, -8.0 }, { -9.0,-10.0,-11.0,-12.0 },                                    // 28-30
  {-14.0,-15.0,-16.0,-17.0 }, { -6.0, -7.0, -8.0, -9.0 }, { -4.0, -5.0, -6.0, -7.0 },                                    // 31-33
  {  2.0,  4.0,  6.0,  8.0 }, {  6.0,  8.0, 10.0, 12.0 }, { 10.0, 12.0, 14.0, 16.0 },                                    // 34-36
  { 15.0, 17.0, 19.0, 21.0 }, {  7.0,  9.0, 11.0, 13.0 }, {  5.0,  7.0,  9.0, 11.0 },                                    // 37-39
  {  1.0,  4.0,  9.0, 16.0 }, {  5.0, 12.0, 21.0, 32.0 }, {  9.0, 20.0, 33.0, 48.0 },                                    // 40-42
  { 14.0, 30.0, 48.0, 68.0 }, {  6.0, 14.0, 24.0, 36.0 }, {  4.0, 10.0, 18.0, 28.0 },                                    // 43-45

  {   1.0,   4.0,   9.0,  16.0 }, { 25.0, 36.0, 49.0, 64.0 }, { 81.0, 100.0, 121.0, 144.0 },                             // 46-48
  { 196.0, 225.0, 256.0, 289.0 }, { 36.0, 49.0, 64.0, 81.0 }, { 16.0,  25.0,  36.0,  49.0 },                             // 49-51

  { 0.18257418274879456, 0.36514836549758911, 0.54772251844406128, 0.73029673099517822 },                                // 52-57
  { 0.37904903292655945, 0.45485883951187134, 0.53066861629486084, 0.60647845268249512 },
  { 0.42616236209869385, 0.47351375222206116, 0.52086508274078369, 0.56821650266647339 },
  { 0.45044264197349548, 0.48261711001396179, 0.51479154825210571, 0.54696607589721680 },
  { 0.39562830328941345, 0.46156632900238037, 0.52750438451766968, 0.59344244003295898 },
  { 0.35634833574295044, 0.44543540477752686, 0.53452247381210327, 0.62360960245132446 },

  {  0.0,  0.0,  0.0,  0.0 }, {  0.0,  0.0,  0.0,  0.0 }, {  0.0,  0.0,  0.0,  0.0 },                                    // 58-60
  {  0.0,  0.0,  0.0,  0.0 }, {  0.0,  0.0,  0.0,  0.0 }, {  0.0,  0.0,  0.0,  0.0 },                                    // 61-63

  { 0.18257418274879456, 0.36514836549758911, 0.54772257804870605, 0.73029673099517822 },                                // 64-69
  { 0.37904903292655945, 0.45485883951187134, 0.53066861629486084, 0.60647845268249512 },
  { 0.42616236209869385, 0.47351372241973877, 0.52086508274078369, 0.56821644306182861 },
  { 0.45044261217117310, 0.48261708021163940, 0.51479154825210571, 0.54696601629257202 },
  { 0.39562827348709106, 0.46156632900238037, 0.52750438451766968, 0.59344244003295898 },
  { 0.35634833574295044, 0.44543540477752686, 0.53452247381210327, 0.62360954284667969 },
};

mat2 m2Results[] = {
  { -1.0f, -2.0f, -3.0f, -4.0f }, { 6.0f, 8.0f, 10.0f, 12.0f }, { 6.0f, 7.0f, 8.0f, 9.0f }, { 4.0f, 4.0f, 4.0f, 4.0f },     // 0-3
  { 19.0f, 22.0f, 43.0f, 50.0f }, { 4.0f, 5.0f,  6.0f,  7.0f }, { 2.0f, 4.0f, 6.0f, 8.0f }, { 1.0f, 0.0f, 0.0f, 1.0f },     // 4-7
  {  1.0f,  3.0f,  2.0f,  4.0f }, { 0.70738822221755981, 0.70682519674301147, -0.70682519674301147, 0.70738822221755981 },  // 8-9
  {  0.5f,  0.0f,  0.0f,  1.0f },
};

m3 m3Results[] = {
  m3(   1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f),
  m3(   1.0f,   0.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   0.0f,   1.0f),
  m3(  -1.0f,  -2.0f,  -3.0f,  -4.0f,  -5.0f,  -6.0f,  -7.0f,  -8.0f,  -9.0f),
  m3(   2.0f,   4.0f,   6.0f,   8.0f,  10.0f,  12.0f,  14.0f,  16.0f,  18.0f),
  m3(   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f,  10.0f),
  m3(   9.0f,   9.0f,   9.0f,   9.0f,   9.0f,   9.0f,   9.0f,   9.0f,   9.0f),
  m3(   1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f),
  m3(  84.0f,  90.0f,  96.0f, 201.0f, 216.0f, 231.0f, 318.0f, 342.0f, 366.0f),
  m3(  -7.5f,   6.0f,   1.0f,  17.5f, -15.0f,  -2.0f,  -9.0f,   8.0f,   1.0f),
  m3( -7.4981689453125,  5.99853515625,  0.999755859375, 17.4957275390625, -14.996337890625, -1.99951171875, -8.997802734375, 7.998046875,  0.999755859375),
  m3(   2.0f,   4.0f,   6.0f,   8.0f,  10.0f,  12.0f,  14.0f,  16.0f,  18.0f),
  m3(   1.0f,   4.0f,   7.0f,   2.0f,   5.0f,   8.0f,   3.0f,   6.0f,   9.0f),
  m3(   1.0f,   0.0f,   0.0f,   0.0f, 0.50045961141586304f, -0.86575984954833984f, 0.0f,  0.86575984954833984f, 0.50045961141586304f),
  m3(   1.0f,   0.0f,   0.0f,   0.0f, 0.50045961141586304f,  0.86575984954833984f, 0.0f, -0.86575984954833984f, 0.50045961141586304f),
  m3(0.50045961141586304,0.0,0.86575984954833984,0.0,1.0,0.0,-0.86575984954833984,0.0,0.50045961141586304),
  m3(0.50045961141586304,0.0,-0.86575984954833984,0.0,1.0,0.0,0.86575984954833984,0.0,0.50045961141586304),
  m3(0.50045961141586304,-0.86575984954833984,0.0,0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,1.0),
  m3(0.50045961141586304,0.86575984954833984,0.0,-0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,1.0),
  m3(0.50045961141586304,0.0,0.86575984954833984,0.74954015016555786,0.50045961141586304,-0.43327787518501282,-0.43327787518501282,0.86575984954833984,0.25045984983444214),
  m3(0.50045961141586304,0.0,0.86575984954833984,0.74954009056091309,0.50045961141586304,-0.43327784538269043,-0.43327784538269043,0.86575984954833984,0.25045982003211975),
  m3(0.50045961141586304,0.0,-0.86575984954833984,0.74954015016555786,0.50045961141586304,0.43327787518501282,0.43327787518501282,-0.86575984954833984,0.25045984983444214),
  m3(0.50045961141586304,0.0,-0.86575984954833984,0.74954009056091309,0.50045961141586304,0.43327784538269043,0.43327784538269043,-0.86575984954833984,0.25045982003211975),
  m3(0.50045961141586304,-0.86575984954833984,0.0,0.43327787518501282,0.25045984983444214,-0.86575984954833984,0.74954015016555786,0.43327787518501282,0.50045961141586304),
  m3(0.50045961141586304,-0.86575984954833984,0.0,0.43327784538269043,0.25045982003211975,-0.86575984954833984,0.74954009056091309,0.43327784538269043,0.50045961141586304),
  m3(0.50045961141586304,0.86575984954833984,0.0,-0.43327787518501282,0.25045984983444214,0.86575984954833984,0.74954015016555786,-0.43327787518501282,0.50045961141586304),
  m3(0.50045961141586304,0.86575984954833984,0.0,-0.43327784538269043,0.25045982003211975,0.86575984954833984,0.74954009056091309,-0.43327784538269043,0.50045961141586304),
  m3(0.25045984983444214,-0.43327787518501282,0.86575984954833984,0.86575984954833984,0.50045961141586304,0.0,-0.43327787518501282,0.74954015016555786,0.50045961141586304),
  m3(0.25045982003211975,-0.43327784538269043,0.86575984954833984,0.86575984954833984,0.50045961141586304,0.0,-0.43327784538269043,0.74954009056091309,0.50045961141586304),
  m3(0.25045984983444214,0.43327787518501282,-0.86575984954833984,-0.86575984954833984,0.50045961141586304,0.0,0.43327787518501282,0.74954015016555786,0.50045961141586304),
  m3(0.25045982003211975,0.43327784538269043,-0.86575984954833984,-0.86575984954833984,0.50045961141586304,0.0,0.43327784538269043,0.74954009056091309,0.50045961141586304),
  m3(0.25045984983444214,-0.43327787518501282,0.86575984954833984,0.80839246511459351,-0.3984619677066803,-0.43327787518501282,0.53270208835601807,0.80839246511459351,0.25045984983444214),
  m3(0.25045982003211975,-0.43327784538269043,0.86575984954833984,0.80839240550994873,-0.39846190810203552,-0.43327784538269043,0.53270208835601807,0.80839240550994873,0.25045982003211975),
  m3(0.25045984983444214,0.43327787518501282,-0.86575984954833984,-0.058163274079561234,0.89938163757324219,0.43327787518501282,0.96637821197509766,-0.058163274079561234,0.25045984983444214),
  m3(0.25045982003211975,0.43327784538269043,-0.86575984954833984,-0.05816328153014183,0.89938157796859741,0.43327784538269043,0.96637815237045288,-0.05816328153014183,0.25045982003211975),
  m3( 2.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0),
  m3( 1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 3.0),
  m3( 1.0, 2.0, 3.0, 5.0, 6.0, 7.0, 9.0,10.0,11.0),
  m3(-25.0,-20.0,22.0,28.0,-19.0,4.0,-10.0,20.0,-9.0),
};


m4 m4Results[] = {
  m4(   1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f,   10.0f,   11.0f,   12.0f,   13.0f,   14.0f,   15.0f,   16.0f),
  m4(  -1.0f,  -2.0f,  -3.0f,  -4.0f,  -5.0f,  -6.0f,  -7.0f,  -8.0f,  -9.0f,  -10.0f,  -11.0f,  -12.0f,  -13.0f,  -14.0f,  -15.0f,  -16.0f),
  m4(   2.0f,   4.0f,   6.0f,   8.0f,  10.0f,  12.0f,  14.0f,  16.0f,  18.0f,   20.0f,   22.0f,   24.0f,   26.0f,   28.0f,   30.0f,   32.0f),
  m4(   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f,  10.0f,   11.0f,   12.0f,   13.0f,   14.0f,   15.0f,   16.0f,   17.0f),
  m4(  16.0f,  16.0f,  16.0f,  16.0f,  16.0f,  16.0f,  16.0f,  16.0f,  16.0f,   16.0f,   16.0f,   16.0f,   16.0f,   16.0f,   16.0f,   16.0f),
  m4(  16.0f,  17.0f,  18.0f,  19.0f,  20.0f,  21.0f,  22.0f,  23.0f,  24.0f,   25.0f,   26.0f,   27.0f,   28.0f,   29.0f,   30.0f,   31.0f),
  m4(  90.0f, 100.0f, 110.0f, 120.0f, 202.0f, 228.0f, 254.0f, 280.0f, 314.0f,  356.0f,  398.0f,  440.0f,  426.0f,  484.0f,  542.0f,  600.0f),
  m4(-0.70710676908493042,0.0,0.70710676908493042,-1.4142135381698608,-0.40824830532073975,0.81649661064147949,-0.40824830532073975,0.0,-0.57735025882720947,-0.57735025882720947,-0.57735025882720947,13.85640621185302700,0.0,0.0,0.0,0.0),
  m4(   2.0f,   4.0f,   6.0f,   8.0f,  10.0f,  12.0f,  14.0f,  16.0f,  18.0f,   20.0f,   22.0f,   24.0f,   26.0f,   28.0f,   30.0f,   32.0f),
  m4(   1.0f,   5.0f,   9.0f,  13.0f,   2.0f,   6.0f,  10.0f,  14.0f,   3.0f,    7.0f,   11.0f,   15.0f,    4.0f,    8.0f,   12.0f,   16.0f),
  m4(  33.0f,  -8.0f,  -9.0f,  10.0f, -14.0f,  24.0f, -18.0f,  20.0f, -21.0f,  -24.0f,   13.0f,   30.0f,   -7.0f,   -8.0f,   -9.0f,   50.0f),
  m4( -97.0f,-112.0f,-126.0f, 140.0f,-112.0f,-127.0f,-144.0f, 160.0f,-126.0f, -144.0f, -161.0f,  180.0f,    0.0f,    0.0f,    0.0f,    1.0f),
  m4(   1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,  11.0f,   12.0f,   13.0f,   14.0f,   13.0f,   14.0f,   15.0f,   16.0f),
  m4(0.40824821591377258,-0.70710688829421997,-0.57735031843185425,0.0,-0.81649655103683472,0.000000089406967163085938,-0.57735031843185425,0.0,0.40824836492538452,0.70710676908493042,-0.57735031843185425,0.0,-0.000000476837158203125,-1.4142136573791504,13.85640811920166,1.0),
  m4(0.40824830532073975,-0.70710676908493042,-0.57735025882720947,0.0,-0.81649661064147949,0.0,                       -0.57735025882720947,0.0,0.40824830532073975,0.70710676908493042,-0.57735025882720947,0.0,-0.0,                    -1.4142135381698608,13.856406211853027,1.0),
  m4(   1.0f,   0.0f,   0.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   0.0f,    0.0f,    1.0f,    0.0f,    0.0f,    0.0f,    0.0f,    1.0f),
  m4(   2.0f,   0.0f,   0.0f,   0.0f,   0.0f,   3.0f,   0.0f,   0.0f,   0.0f,    0.0f,    4.0f,    0.0f,    0.0f,    0.0f,    0.0f,    1.0f),
  m4(1.0,0.0,0.0,0.0,0.0,0.50045961141586304,-0.86575984954833984,0.0,0.0,0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,0.50045961141586304,0.86575984954833984,0.0,0.0,-0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,0.86575984954833984,0.0,0.0,1.0,0.0,0.0,-0.86575984954833984,0.0,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,-0.86575984954833984,0.0,0.0,1.0,0.0,0.0,0.86575984954833984,0.0,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,-0.86575984954833984,0.0,0.0,0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.86575984954833984,0.0,0.0,-0.86575984954833984,0.50045961141586304,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,0.86575984954833984,0.0,0.74954015016555786,0.50045961141586304,-0.43327787518501282,0.0,-0.43327787518501282,0.86575984954833984,0.25045984983444214,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,0.86575984954833984,0.0,0.74954009056091309,0.50045961141586304,-0.43327784538269043,0.0,-0.43327784538269043,0.86575984954833984,0.25045982003211975,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,-0.86575984954833984,0.0,0.74954015016555786,0.50045961141586304,0.43327787518501282,0.0,0.43327787518501282,-0.86575984954833984,0.25045984983444214,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.0,-0.86575984954833984,0.0,0.74954009056091309,0.50045961141586304,0.43327784538269043,0.0,0.43327784538269043,-0.86575984954833984,0.25045982003211975,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,-0.86575984954833984,0.0,0.0,0.43327787518501282,0.25045984983444214,-0.86575984954833984,0.0,0.74954015016555786,0.43327787518501282,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,-0.86575984954833984,0.0,0.0,0.43327784538269043,0.25045982003211975,-0.86575984954833984,0.0,0.74954009056091309,0.43327784538269043,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.86575984954833984,0.0,0.0,-0.43327787518501282,0.25045984983444214,0.86575984954833984,0.0,0.74954015016555786,-0.43327787518501282,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.50045961141586304,0.86575984954833984,0.0,0.0,-0.43327784538269043,0.25045982003211975,0.86575984954833984,0.0,0.74954009056091309,-0.43327784538269043,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045984983444214,-0.43327787518501282,0.86575984954833984,0.0,0.86575984954833984,0.50045961141586304,0.0,0.0,-0.43327787518501282,0.74954015016555786,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045982003211975,-0.43327784538269043,0.86575984954833984,0.0,0.86575984954833984,0.50045961141586304,0.0,0.0,-0.43327784538269043,0.74954009056091309,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045984983444214,0.43327787518501282,-0.86575984954833984,0.0,-0.86575984954833984,0.50045961141586304,0.0,0.0,0.43327787518501282,0.74954015016555786,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045982003211975,0.43327784538269043,-0.86575984954833984,0.0,-0.86575984954833984,0.50045961141586304,0.0,0.0,0.43327784538269043,0.74954009056091309,0.50045961141586304,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045984983444214,-0.43327787518501282,0.86575984954833984,0.0,0.80839246511459351,-0.3984619677066803, -0.43327787518501282,0.0,0.53270208835601807,0.80839246511459351,0.25045984983444214,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045982003211975,-0.43327784538269043,0.86575984954833984,0.0,0.80839240550994873,-0.39846190810203552,-0.43327784538269043,0.0,0.53270208835601807,0.80839240550994873,0.25045982003211975,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045984983444214,0.43327787518501282,-0.86575984954833984,0.0,-0.058163274079561234,0.89938163757324219,0.43327787518501282,0.0,0.96637821197509766,-0.058163274079561234,0.25045984983444214,0.0,0.0,0.0,0.0,1.0),
  m4(0.25045982003211975,0.43327784538269043,-0.86575984954833984,0.0,-0.05816328153014183, 0.89938157796859741,0.43327784538269043,0.0,0.96637815237045288,-0.05816328153014183, 0.25045982003211975,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,2.0,0.0,1.0,0.0,3.0,0.0,0.0,1.0,4.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,2.0,3.0,4.0,1.0),
  m4(1.0,0.0,0.0,1.0,0.0,1.0,0.0,2.0,0.0,0.0,1.0,3.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,2.0,3.0,1.0),
  m4(1.0,0.0,0.0,1.0,0.0,1.0,0.0,2.0,0.0,0.0,1.0,3.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,2.0,3.0,1.0),
  m4(0.020202020183205605,0.0,0.0,-1.0202020406723022,0.0,-0.020202020183205605,0.0,1.0202020406723022,0.0,0.0,0.01666666753590107,-0.66666668653488159,0.0,0.0,0.0,1.0),
  m4(1.5423510074615479,0.0,0.0,0.0,0.0,1.5423510074615479,0.0,0.0,0.0,0.0,0.6666666865348815,-33.33333206176757,0.0,0.0,1.0,0.0),
  m4(0.0,0.0,-1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0),
  m4(0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,-1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,0.0,-1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,-1.0,0.0,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0),
  m4(-1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,0.0,1.0),
  m4(1.0,0.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,0.0,0.96078431606292725,3.9215686321258545,0.0,0.0,1.0,0.0),
  m4(1.0,2.0,3.0,0.0,5.0,6.0,7.0,0.0,9.0,10.0,11.0,0.0,0.0,0.0,0.0,1.0),
  m4(-25.0,-20.0,22.0,0.0,28.0,-19.0,4.0,0.0,-10.0,20.0,-9.0,0.0,0.0,0.0,0.0,1.0),
};

quat qResults[] = {
  quat(32.0,32.0,56.0,-22.0),
  quat(24.0,48.0,48.0, -6.0),
  quat(-1.0,-2.0,-3.0,  4.0),
  quat(0.13356918096542358,0.26713836193084717,0.40070757269859314,0.86615806818008423),
  quat(0.13356918096542358,0.26713836193084717,0.40070754289627075,0.86615806818008423),
  quat(0.25,-0.5,0.25,2.0),
  quat(1.2247449159622192,0.40824830532073975,0.61237245798110962,-0.61237245798110962),
  quat(1.2247449159622192,0.40824827551841736,0.61237239837646484,-0.61237239837646484),
  quat(0.40824830532073975,1.2247449159622192,1.0206207036972046,0.20412415266036987),
  quat(0.40824827551841736,1.2247449159622192,1.0206207036972046,0.20412413775920868),
  quat(0.61237245798110962,1.0206207036972046,1.2247449159622192,0.0),
  quat(0.61237239837646484,1.0206207036972046,1.2247449159622192,0.0),
  quat(0.34412360191345215,-0.6882472038269043,0.34412360191345215,2.1794495582580566),
  quat(0.0,0.0,0.0,0.70637744665145874),
};

int main()
{
  float fr;
  float fa = 1.0f;
  float fb = 2.0f;
  float fd = 0.5f;

  fprintf(stdout,"\n-------------> Float Methods\n\n");

  TestResult(fr=FloatLerpAsm(fa,fb,fd),       fr,FloatList[0],sizeof(float),"FloatLerp()        ",LERP_ERROR);
  TestResult(fr=FloatLerpStd(fa,fb,fd),       fr,FloatList[0],sizeof(float),"FloatLerpStd()     ",LERP_ERROR);
  TestResult(FloatLerpPtrAsm(&fr,&fa,&fb,&fd),fr,FloatList[0],sizeof(float),"FloatLerpStd()     ",LERP_ERROR);
  TestResult(FloatLerpPtrStd(&fr,&fa,&fb,&fd),fr,FloatList[0],sizeof(float),"FloatLerpStd()     ",LERP_ERROR);
  TestResult(fr=FloatSqrAsm(fb),              fr,FloatList[1],sizeof(float),"FloatSqr()         ",SQR_ERROR);
  TestResult(fr=FloatSqrStd(fb),              fr,FloatList[1],sizeof(float),"FloatSqr()         ",SQR_ERROR);
  TestResult(fr=FloatSqrPtrAsm(&fb),          fr,FloatList[1],sizeof(float),"FloatSqr()         ",SQR_ERROR);
  TestResult(fr=FloatSqrPtrStd(&fb),          fr,FloatList[1],sizeof(float),"FloatSqr()         ",SQR_ERROR);
  
  fprintf(stdout,"\n-------------> Vec2 Methods\n\n");

  v2 v2a(1.0f,2.0f);
  v2 v2b(3.0f,4.0f);
  v2 v2c(5.0f,6.0f);
  v2 v2d;

  vec2* v2List[] = {
    (vec2*)v2a,
    (vec2*)v2b,
    (vec2*)v2c
  };

  char* pUnalignedPackedArray = (char*)malloc( 6*sizeof(float) );

  TestResult(BuildVec2PackedArrayAsm((vec2*)pUnalignedPackedArray,(const vec2**)v2List,3),
	     *((vec2*)pUnalignedPackedArray),
	     v2Results[0],
	     3*sizeof(vec2),
	     "BuildVec2PackedArrayAsm()",FCN_ERROR);
  TestResult(BuildVec2PackedArrayStd((vec2*)pUnalignedPackedArray,(const vec2**)v2List,3),
	     *((vec2*)pUnalignedPackedArray),
	     v2Results[0],
	     3*sizeof(vec2),
	     "BuildVec2PackedArrayStd()",FCN_ERROR);

  TestResult(Vec2CopyAsm(v2d.vec,v2a.vec),              *(v2d.vec),v2Results[ 0],sizeof(vec2), "Vec2CopyAsm()         ",FCN_ERROR);
  TestResult(Vec2CopyStd(v2d.vec,v2a.vec),              *(v2d.vec),v2Results[ 0],sizeof(vec2), "Vec2CopyStd()         ",FCN_ERROR);
  TestResult(Vec2AddFloatAsm(v2d.vec,v2a.vec,5.0f),     *(v2d.vec),v2Results[ 3],sizeof(vec2), "Vec2AddFloatAsm()     ",FCN_ERROR);
  TestResult(Vec2AddFloatStd(v2d.vec,v2a.vec,5.0f),     *(v2d.vec),v2Results[ 3],sizeof(vec2), "Vec2AddFloatStd()     ",FCN_ERROR);
  TestResult(Vec2SubtractFloatAsm(v2d.vec,v2b.vec,1.0f),*(v2d.vec),v2Results[ 4],sizeof(vec2), "Vec2SubtractFloatAsm()",FCN_ERROR);
  TestResult(Vec2SubtractFloatStd(v2d.vec,v2b.vec,1.0f),*(v2d.vec),v2Results[ 4],sizeof(vec2), "Vec2SubtractFloatStd()",FCN_ERROR);
  TestResult(Vec2MultiplyFloatAsm(v2d.vec,v2b.vec,2.0f),*(v2d.vec),v2Results[ 5],sizeof(vec2), "Vec2MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Vec2MultiplyFloatStd(v2d.vec,v2b.vec,2.0f),*(v2d.vec),v2Results[ 5],sizeof(vec2), "Vec2MultiplyFloatStd()",FCN_ERROR);
  TestResult(Vec2DivideFloatAsm(v2d.vec,v2b.vec,1.0f),  *(v2d.vec),v2Results[ 1],sizeof(vec2), "Vec2DivideFloatAsm()  ",FCN_ERROR);
  TestResult(Vec2DivideFloatStd(v2d.vec,v2b.vec,1.0f),  *(v2d.vec),v2Results[ 1],sizeof(vec2), "Vec2DivideFloatStd()  ",FCN_ERROR);
  TestResult(Vec2NegateAsm(v2d.vec,v2a.vec),            *(v2d.vec),v2Results[ 6],sizeof(vec2), "Vec2NegateAsm()       ",FCN_ERROR);
  TestResult(Vec2NegateStd(v2d.vec,v2a.vec),            *(v2d.vec),v2Results[ 6],sizeof(vec2), "Vec2NegateStd()       ",FCN_ERROR);
  TestResult(Vec2AddAsm(v2d.vec,v2a.vec,v2b.vec),       *(v2d.vec),v2Results[ 7],sizeof(vec2), "Vec2AddAsm()          ",FCN_ERROR);
  TestResult(Vec2AddStd(v2d.vec,v2a.vec,v2b.vec),       *(v2d.vec),v2Results[ 7],sizeof(vec2), "Vec2AddStd()          ",FCN_ERROR);
  TestResult(Vec2SubtractAsm(v2d.vec,v2b.vec,v2a.vec),  *(v2d.vec),v2Results[ 8],sizeof(vec2), "Vec2SubtractAsm()     ",FCN_ERROR);
  TestResult(Vec2SubtractStd(v2d.vec,v2b.vec,v2a.vec),  *(v2d.vec),v2Results[ 8],sizeof(vec2), "Vec2SubtractStd()     ",FCN_ERROR);
  TestResult(Vec2MultiplyAsm(v2d.vec,v2a.vec,v2b.vec),  *(v2d.vec),v2Results[ 9],sizeof(vec2), "Vec2MultiplyAsm()     ",FCN_ERROR);
  TestResult(Vec2MultiplyStd(v2d.vec,v2a.vec,v2b.vec),  *(v2d.vec),v2Results[ 9],sizeof(vec2), "Vec2MultiplyStd()     ",FCN_ERROR);
  TestResult(Vec2DivideAsm(v2d.vec,v2a.vec,v2a.vec),    *(v2d.vec),v2Results[10],sizeof(vec2), "Vec2DivideAsm()       ",FCN_ERROR);
  TestResult(Vec2DivideStd(v2d.vec,v2a.vec,v2a.vec),    *(v2d.vec),v2Results[10],sizeof(vec2), "Vec2DivideStd()       ",FCN_ERROR);
  TestResult(Vec2LerpAsm(v2d.vec,v2a.vec,v2b.vec,0.5f), *(v2d.vec),v2Results[ 4],sizeof(vec2), "Vec2LerpAsm()         ",FCN_ERROR);
  TestResult(Vec2LerpStd(v2d.vec,v2a.vec,v2b.vec,0.5f), *(v2d.vec),v2Results[ 4],sizeof(vec2), "Vec2LerpStd()         ",FCN_ERROR);
  TestResult(Vec2SqrAsm(v2d.vec,v2a.vec),               *(v2d.vec),v2Results[11],sizeof(vec2), "Vec2SqrAsm()          ",FCN_ERROR);
  TestResult(Vec2SqrStd(v2d.vec,v2a.vec),               *(v2d.vec),v2Results[11],sizeof(vec2), "Vec2SqrStd()          ",FCN_ERROR);
  TestResult(Vec2NormalizeAsm(v2d.vec,v2b.vec),         *(v2d.vec),v2Results[12],sizeof(vec2), "Vec2NormalizeAsm()    ",FCN_ERROR);
  TestResult(Vec2NormalizeStd(v2d.vec,v2b.vec),         *(v2d.vec),v2Results[12],sizeof(vec2), "Vec2NormalizeStd()    ",FCN_ERROR);
  TestResult(Vec2DotAsm(&fr,v2a.vec,v2b.vec),           fr,        FloatList[ 2],sizeof(float),"Vec2DotAsm()          ",FCN_ERROR);
  TestResult(Vec2DotStd(&fr,v2a.vec,v2b.vec),           fr,        FloatList[ 2],sizeof(float),"Vec2DotStd()          ",FCN_ERROR);
  TestResult(Vec2LengthAsm(&fr,v2a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec2LengthAsm()       ",FCN_ERROR);
  TestResult(Vec2LengthStd(&fr,v2a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec2LengthStd()       ",FCN_ERROR);

#if 0
 XXX: THIS WILL NOT WORK ON THIS PROCESSOR

  int32_t bResult;

  TestResult(Vec2EqualsAsm(&bResult,v2a.vec,v2a.vec),   bResult,     IntList[ 0],  sizeof(int),"Vec2EqualsAsm()       ",FCN_ERROR);
  TestResult(Vec2EqualsStd(&bResult,v2a.vec,v2a.vec),   bResult,     IntList[ 0],  sizeof(int),"Vec2EqualsStd()       ",FCN_ERROR);
  TestResult(Vec2NotEqualsAsm(&bResult,v2a.vec,v2a.vec),bResult,     IntList[ 1],  sizeof(int),"Vec2NotEqualsAsm()    ",FCN_ERROR);
  TestResult(Vec2NotEqualsStd(&bResult,v2a.vec,v2a.vec),bResult,     IntList[ 1],  sizeof(int),"Vec2NotEqualsStd()    ",FCN_ERROR);
#endif

  free((void*)pUnalignedPackedArray);

  fprintf(stdout,"\n-------------> Vec3 Methods\n\n");

  v3 v3a(1.0f,2.0f,3.0f);
  v3 v3b(4.0f,5.0f,6.0f);
  v3 v3c(7.0f,8.0f,9.0f);
  v3 v3e(1.0f,2.0f,3.0f);
  v3 v3d;

  vec3* v3List[] = {
    (vec3*)v3a,
    (vec3*)v3b,
    (vec3*)v3c
  };

  pUnalignedPackedArray = (char*)malloc( 12*sizeof(float) );

  TestResult(BuildVec3PackedArrayAsm((vec3*)pUnalignedPackedArray,(const vec3**)v3List,3),
	     *((vec3*)pUnalignedPackedArray),
	     v3Results[0],
	     3*sizeof(vec3),
	     "BuildVec3PackedArrayAsm()",FCN_ERROR);
  TestResult(BuildVec3PackedArrayStd((vec3*)pUnalignedPackedArray,(const vec3**)v3List,3),
	     *((vec3*)pUnalignedPackedArray),
	     v3Results[0],
	     3*sizeof(vec3),
	     "BuildVec3PackedArrayStd()",FCN_ERROR);

  TestResult(Vec3CopyAsm(v3d.vec,v3a.vec),              *(v3d.vec),v3Results[ 0],sizeof(vec3), "Vec3CopyAsm()         ",FCN_ERROR);
  TestResult(Vec3CopyStd(v3d.vec,v3a.vec),              *(v3d.vec),v3Results[ 0],sizeof(vec3), "Vec3CopyStd()         ",FCN_ERROR);
  TestResult(Vec3AddFloatAsm(v3d.vec,v3a.vec,5.0f),     *(v3d.vec),v3Results[ 3],sizeof(vec3), "Vec3AddFloatAsm()     ",FCN_ERROR);
  TestResult(Vec3AddFloatStd(v3d.vec,v3a.vec,5.0f),     *(v3d.vec),v3Results[ 3],sizeof(vec3), "Vec3AddFloatStd()     ",FCN_ERROR);
  TestResult(Vec3SubtractFloatAsm(v3d.vec,v3b.vec,1.0f),*(v3d.vec),v3Results[ 4],sizeof(vec3), "Vec3SubtractFloatAsm()",FCN_ERROR);
  TestResult(Vec3SubtractFloatStd(v3d.vec,v3b.vec,1.0f),*(v3d.vec),v3Results[ 4],sizeof(vec3), "Vec3SubtractFloatStd()",FCN_ERROR);
  TestResult(Vec3MultiplyFloatAsm(v3d.vec,v3b.vec,3.0f),*(v3d.vec),v3Results[ 5],sizeof(vec3), "Vec3MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Vec3MultiplyFloatStd(v3d.vec,v3b.vec,3.0f),*(v3d.vec),v3Results[ 5],sizeof(vec3), "Vec3MultiplyFloatStd()",FCN_ERROR);
  TestResult(Vec3DivideFloatAsm(v3d.vec,v3b.vec,1.0f),  *(v3d.vec),v3Results[ 1],sizeof(vec3), "Vec3DivideFloatAsm()  ",FCN_ERROR);
  TestResult(Vec3DivideFloatStd(v3d.vec,v3b.vec,1.0f),  *(v3d.vec),v3Results[ 1],sizeof(vec3), "Vec3DivideFloatStd()  ",FCN_ERROR);
  TestResult(Vec3NegateAsm(v3d.vec,v3a.vec),            *(v3d.vec),v3Results[ 6],sizeof(vec3), "Vec3NegateAsm()       ",FCN_ERROR);
  TestResult(Vec3NegateStd(v3d.vec,v3a.vec),            *(v3d.vec),v3Results[ 6],sizeof(vec3), "Vec3NegateStd()       ",FCN_ERROR);
  TestResult(Vec3AddAsm(v3d.vec,v3a.vec,v3b.vec),       *(v3d.vec),v3Results[ 7],sizeof(vec3), "Vec3AddAsm()          ",FCN_ERROR);
  TestResult(Vec3AddStd(v3d.vec,v3a.vec,v3b.vec),       *(v3d.vec),v3Results[ 7],sizeof(vec3), "Vec3AddStd()          ",FCN_ERROR);
  TestResult(Vec3SubtractAsm(v3d.vec,v3b.vec,v3a.vec),  *(v3d.vec),v3Results[ 8],sizeof(vec3), "Vec3SubtractAsm()     ",FCN_ERROR);
  TestResult(Vec3SubtractStd(v3d.vec,v3b.vec,v3a.vec),  *(v3d.vec),v3Results[ 8],sizeof(vec3), "Vec3SubtractStd()     ",FCN_ERROR);
  TestResult(Vec3MultiplyAsm(v3d.vec,v3a.vec,v3b.vec),  *(v3d.vec),v3Results[ 9],sizeof(vec3), "Vec3MultiplyAsm()     ",FCN_ERROR);
  TestResult(Vec3MultiplyStd(v3d.vec,v3a.vec,v3b.vec),  *(v3d.vec),v3Results[ 9],sizeof(vec3), "Vec3MultiplyStd()     ",FCN_ERROR);
  TestResult(Vec3DivideAsm(v3d.vec,v3a.vec,v3e.vec),    *(v3d.vec),v3Results[10],sizeof(vec3), "Vec3DivideAsm()       ",FCN_ERROR);
  TestResult(Vec3DivideStd(v3d.vec,v3a.vec,v3e.vec),    *(v3d.vec),v3Results[10],sizeof(vec3), "Vec3DivideStd()       ",FCN_ERROR);
  TestResult(Vec3LerpAsm(v3d.vec,v3a.vec,v3b.vec,0.5f), *(v3d.vec),v3Results[11],sizeof(vec3), "Vec3LerpAsm()         ",FCN_ERROR);
  TestResult(Vec3LerpStd(v3d.vec,v3a.vec,v3b.vec,0.5f), *(v3d.vec),v3Results[11],sizeof(vec3), "Vec3LerpStd()         ",FCN_ERROR);
  TestResult(Vec3SqrAsm(v3d.vec,v3a.vec),               *(v3d.vec),v3Results[12],sizeof(vec3), "Vec3SqrAsm()          ",FCN_ERROR);
  TestResult(Vec3SqrStd(v3d.vec,v3a.vec),               *(v3d.vec),v3Results[12],sizeof(vec3), "Vec3SqrStd()          ",FCN_ERROR);
#if 0
  // XXX: THESE WON'T WORK ON THIS PROCESSOR
  TestResult(Vec3NormalizeAsm(v3d.vec,v3b.vec),         *(v3d.vec),v3Results[13],sizeof(vec3), "Vec3NormalizeAsm()    ",FCN_ERROR);
  TestResult(Vec3NormalizeStd(v3d.vec,v3b.vec),         *(v3d.vec),v3Results[13],sizeof(vec3), "Vec3NormalizeStd()    ",FCN_ERROR);
  TestResult(Vec3DotAsm(&fr,v3a.vec,v3b.vec),           fr,        FloatList[ 3],sizeof(float),"Vec3DotAsm()          ",FCN_ERROR);
  TestResult(Vec3DotStd(&fr,v3a.vec,v3b.vec),           fr,        FloatList[ 3],sizeof(float),"Vec3DotStd()          ",FCN_ERROR);
  TestResult(Vec3LengthAsm(&fr,v3a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec3LengthAsm()       ",FCN_ERROR);
  TestResult(Vec3LengthStd(&fr,v3a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec3LengthStd()       ",FCN_ERROR);
#endif

  TestResult(Vec3CrossAsm(v3d.vec,v3a.vec,v3b.vec),     *(v3d.vec),v3Results[14],sizeof(vec3), "Vec3CrossAsm()        ",FCN_ERROR);
  TestResult(Vec3CrossStd(v3d.vec,v3a.vec,v3b.vec),     *(v3d.vec),v3Results[14],sizeof(vec3), "Vec3CrossStd()        ",FCN_ERROR);

  free((void*)pUnalignedPackedArray);

  fprintf(stdout,"\n-------------> Vec4 Methods\n\n");fflush(stdout);

  v4 v4a(1.0f,2.0f,3.0f,4.0f);

  v4 v4b(5.0f,6.0f,7.0f,8.0f);
  v4 v4c(9.0f,10.0f,11.0f,12.0f);
  v4 v4d(14.0f,15.0f,16.0f,17.0f);
  v4 v4r;

  vec4* v4List[] = {
    (vec4*)v4a,
    (vec4*)v4b,
    (vec4*)v4c,
    (vec4*)v4d
  };

  pUnalignedPackedArray = (char*)malloc( 16*sizeof(float) );

  TestResult(BuildVec4PackedArrayAsm((vec4*)pUnalignedPackedArray,(const vec4**)v4List,4),
	     *((vec4*)pUnalignedPackedArray),
	     v4Results[0],
	     4*sizeof(vec4),
	     "BuildVec4PackedArrayAsm()",FCN_ERROR);
  TestResult(BuildVec4PackedArrayStd((vec4*)pUnalignedPackedArray,(const vec4**)v4List,4),
	     *((vec4*)pUnalignedPackedArray),
	     v4Results[0],
	     4*sizeof(vec4),
	     "BuildVec4PackedArrayStd()",FCN_ERROR);

  TestResult(Vec4CopyAsm(v4r.vec,v4a.vec),              *(v4r.vec),v4Results[ 0],sizeof(vec4), "Vec4CopyAsm()         ",FCN_ERROR);
  TestResult(Vec4CopyStd(v4r.vec,v4a.vec),              *(v4r.vec),v4Results[ 0],sizeof(vec4), "Vec4CopyStd()         ",FCN_ERROR);
  TestResult(Vec4AddFloatAsm(v4r.vec,v4a.vec,5.0f),     *(v4r.vec),v4Results[ 4],sizeof(vec4), "Vec4AddFloatAsm()     ",FCN_ERROR);
  TestResult(Vec4AddFloatStd(v4r.vec,v4a.vec,5.0f),     *(v4r.vec),v4Results[ 4],sizeof(vec4), "Vec4AddFloatStd()     ",FCN_ERROR);
  TestResult(Vec4SubtractFloatAsm(v4r.vec,v4b.vec,1.0f),*(v4r.vec),v4Results[ 5],sizeof(vec4), "Vec4SubtractFloatAsm()",FCN_ERROR);
  TestResult(Vec4SubtractFloatStd(v4r.vec,v4b.vec,1.0f),*(v4r.vec),v4Results[ 5],sizeof(vec4), "Vec4SubtractFloatStd()",FCN_ERROR);
  TestResult(Vec4MultiplyFloatAsm(v4r.vec,v4b.vec,3.0f),*(v4r.vec),v4Results[ 6],sizeof(vec4), "Vec4MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Vec4MultiplyFloatStd(v4r.vec,v4b.vec,3.0f),*(v4r.vec),v4Results[ 6],sizeof(vec4), "Vec4MultiplyFloatStd()",FCN_ERROR);
  TestResult(Vec4DivideFloatAsm(v4r.vec,v4b.vec,1.0f),  *(v4r.vec),v4Results[ 1],sizeof(vec4), "Vec4DivideFloatAsm()  ",FCN_ERROR);
  TestResult(Vec4DivideFloatStd(v4r.vec,v4b.vec,1.0f),  *(v4r.vec),v4Results[ 1],sizeof(vec4), "Vec4DivideFloatStd()  ",FCN_ERROR);
  TestResult(Vec4NegateAsm(v4r.vec,v4a.vec),            *(v4r.vec),v4Results[ 7],sizeof(vec4), "Vec4NegateAsm()       ",FCN_ERROR);
  TestResult(Vec4NegateStd(v4r.vec,v4a.vec),            *(v4r.vec),v4Results[ 7],sizeof(vec4), "Vec4NegateStd()       ",FCN_ERROR);
  TestResult(Vec4AddAsm(v4r.vec,v4a.vec,v4b.vec),       *(v4r.vec),v4Results[ 8],sizeof(vec4), "Vec4AddAsm()          ",FCN_ERROR);
  TestResult(Vec4AddStd(v4r.vec,v4a.vec,v4b.vec),       *(v4r.vec),v4Results[ 8],sizeof(vec4), "Vec4AddStd()          ",FCN_ERROR);
  TestResult(Vec4SubtractAsm(v4r.vec,v4b.vec,v4a.vec),  *(v4r.vec),v4Results[ 9],sizeof(vec4), "Vec4SubtractAsm()     ",FCN_ERROR);
  TestResult(Vec4SubtractStd(v4r.vec,v4b.vec,v4a.vec),  *(v4r.vec),v4Results[ 9],sizeof(vec4), "Vec4SubtractStd()     ",FCN_ERROR);
  TestResult(Vec4MultiplyAsm(v4r.vec,v4a.vec,v4b.vec),  *(v4r.vec),v4Results[10],sizeof(vec4), "Vec4MultiplyAsm()     ",FCN_ERROR);
  TestResult(Vec4MultiplyStd(v4r.vec,v4a.vec,v4b.vec),  *(v4r.vec),v4Results[10],sizeof(vec4), "Vec4MultiplyStd()     ",FCN_ERROR);
  TestResult(Vec4DivideAsm(v4r.vec,v4a.vec,v4a.vec),    *(v4r.vec),v4Results[11],sizeof(vec4), "Vec4DivideAsm()       ",FCN_ERROR);
  TestResult(Vec4DivideStd(v4r.vec,v4a.vec,v4a.vec),    *(v4r.vec),v4Results[11],sizeof(vec4), "Vec4DivideStd()       ",FCN_ERROR);
  TestResult(Vec4LerpAsm(v4r.vec,v4a.vec,v4b.vec,0.5f), *(v4r.vec),v4Results[12],sizeof(vec4), "Vec4LerpAsm()         ",FCN_ERROR);
  TestResult(Vec4LerpStd(v4r.vec,v4a.vec,v4b.vec,0.5f), *(v4r.vec),v4Results[12],sizeof(vec4), "Vec4LerpStd()         ",FCN_ERROR);
  TestResult(Vec4SqrAsm(v4r.vec,v4a.vec),               *(v4r.vec),v4Results[13],sizeof(vec4), "Vec4SqrAsm()          ",FCN_ERROR);
  TestResult(Vec4SqrStd(v4r.vec,v4a.vec),               *(v4r.vec),v4Results[13],sizeof(vec4), "Vec4SqrStd()          ",FCN_ERROR);
  TestResult(Vec4CrossAsm(v4r.vec,v4a.vec,v4b.vec),     *(v4r.vec),v4Results[14],sizeof(vec4), "Vec4CrossAsm()        ",FCN_ERROR);
  TestResult(Vec4CrossStd(v4r.vec,v4a.vec,v4b.vec),     *(v4r.vec),v4Results[14],sizeof(vec4), "Vec4CrossStd()        ",FCN_ERROR);

#if 0
  // XXX: THESE WON'T WORK ON THIS PROCESSOR
  TestResult(Vec4NormalizeAsm(v4r.vec,v4b.vec),         *(v4r.vec),v4Results[13],sizeof(vec4), "Vec4NormalizeAsm()    ",FCN_ERROR);
  TestResult(Vec4NormalizeStd(v4r.vec,v4b.vec),         *(v4r.vec),v4Results[13],sizeof(vec4), "Vec4NormalizeStd()    ",FCN_ERROR);
  TestResult(Vec4DotAsm(&fr,v4a.vec,v4b.vec),           fr,        FloatList[ 3],sizeof(float),"Vec4DotAsm()          ",FCN_ERROR);
  TestResult(Vec4DotStd(&fr,v4a.vec,v4b.vec),           fr,        FloatList[ 3],sizeof(float),"Vec4DotStd()          ",FCN_ERROR);
  TestResult(Vec4LengthAsm(&fr,v4a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec4LengthAsm()       ",FCN_ERROR);
  TestResult(Vec4LengthStd(&fr,v4a.vec),                fr,        FloatList[ 3],sizeof(float),"Vec4LengthStd()       ",FCN_ERROR);
#endif

  free((void*)pUnalignedPackedArray);

  fprintf(stdout,"\n-------------> Mat2 Methods\n\n");

  m2 m2a(1.0f,2.0f,3.0f,4.0f);
  m2 m2b(5.0f,6.0f,7.0f,8.0f);
  m2 m2c(9.0f,10.0f,11.0f,12.0f);
  m2 m2r;

  TestResult(Mat2NegateAsm(m2r.m,m2a.m),                  *(m2r.m),  m2Results[ 0],sizeof(mat2), "Mat2NegateAsm()       ",FCN_ERROR);
  TestResult(Mat2NegateStd(m2r.m,m2a.m),                  *(m2r.m),  m2Results[ 0],sizeof(mat2), "Mat2NegateStd()       ",FCN_ERROR);
  TestResult(Mat2AddAsm(m2r.m,m2a.m,m2b.m),               *(m2r.m),  m2Results[ 1],sizeof(mat2), "Mat2AddAsm()          ",FCN_ERROR);
  TestResult(Mat2AddStd(m2r.m,m2a.m,m2b.m),               *(m2r.m),  m2Results[ 1],sizeof(mat2), "Mat2AddStd()          ",FCN_ERROR);
  TestResult(Mat2AddFloatAsm(m2r.m,m2b.m,1.0f),           *(m2r.m),  m2Results[ 2],sizeof(mat2), "Mat2AddFloatAsm()     ",FCN_ERROR);
  TestResult(Mat2AddFloatStd(m2r.m,m2b.m,1.0f),           *(m2r.m),  m2Results[ 2],sizeof(mat2), "Mat2AddFloatStd()     ",FCN_ERROR);
  TestResult(Mat2SubtractAsm(m2r.m,m2b.m,m2a.m),          *(m2r.m),  m2Results[ 3],sizeof(mat2), "Mat2SubtractAsm()     ",FCN_ERROR);
  TestResult(Mat2SubtractStd(m2r.m,m2b.m,m2a.m),          *(m2r.m),  m2Results[ 3],sizeof(mat2), "Mat2SubtractStd()     ",FCN_ERROR);
  TestResult(Mat2SubtractFloatAsm(m2r.m,m2b.m,1.0f),      *(m2r.m),  m2Results[ 5],sizeof(mat2), "Mat2SubtractFloatAsm()",FCN_ERROR);
  TestResult(Mat2SubtractFloatStd(m2r.m,m2b.m,1.0f),      *(m2r.m),  m2Results[ 5],sizeof(mat2), "Mat2SubtractFloatStd()",FCN_ERROR);
  TestResult(Mat2MultiplyAsm(m2r.m,m2a.m,m2b.m),          *(m2r.m),  m2Results[ 4],sizeof(mat2), "Mat2MultiplyAsm()     ",FCN_ERROR);
  TestResult(Mat2MultiplyStd(m2r.m,m2a.m,m2b.m),          *(m2r.m),  m2Results[ 4],sizeof(mat2), "Mat2MultiplyStd()     ",FCN_ERROR);
  TestResult(Mat2MultiplyVecAsm(v2d.vec,m2a.m,v2a.vec),   *(v2d.vec),v2Results[13],sizeof(vec2), "Mat2MultiplyVecAsm()  ",FCN_ERROR);
  TestResult(Mat2MultiplyVecStd(v2d.vec,m2a.m,v2a.vec),   *(v2d.vec),v2Results[13],sizeof(vec2), "Mat2MultiplyVecStd()  ",FCN_ERROR);
  TestResult(Mat2MultiplyFloatAsm(m2r.m,m2a.m,2.0f),      *(m2r.m),  m2Results[ 6],sizeof(mat2), "Mat2MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Mat2MultiplyFloatStd(m2r.m,m2a.m,2.0f),      *(m2r.m),  m2Results[ 6],sizeof(mat2), "Mat2MultiplyFloatStd()",FCN_ERROR);
  TestResult(Mat2IdentityAsm(m2r.m),                      *(m2r.m),  m2Results[ 7],sizeof(mat2), "Mat2IdentityAsm()     ",FCN_ERROR);
  TestResult(Mat2IdentityStd(m2r.m),                      *(m2r.m),  m2Results[ 7],sizeof(mat2), "Mat2IdentityStd()     ",FCN_ERROR);
  TestResult(Mat2TransposeAsm(m2r.m,m2a.m),               *(m2r.m),  m2Results[ 8],sizeof(mat2), "Mat2TransposeAsm()    ",FCN_ERROR);
  TestResult(Mat2TransposeStd(m2r.m,m2a.m),               *(m2r.m),  m2Results[ 8],sizeof(mat2), "Mat2TransposeStd()    ",FCN_ERROR);
  TestResult(Mat2RotateLHAsm(m2r.m,(45.0/90.0)*1.57),     *(m2r.m),  m2Results[ 9],sizeof(mat2), "Mat2RotateLHAsm()     ",FCN_ERROR);
  TestResult(Mat2RotateLHStd(m2r.m,(45.0/90.0)*1.57),     *(m2r.m),  m2Results[ 9],sizeof(mat2), "Mat2RotateLHStd()     ",FCN_ERROR);
  TestResult(Mat2ScaleAsm(m2r.m,0.5f,1.0f),               *(m2r.m),  m2Results[10],sizeof(mat2), "Mat2ScaleAsm()        ",FCN_ERROR);
  TestResult(Mat2ScaleStd(m2r.m,0.5f,1.0f),               *(m2r.m),  m2Results[10],sizeof(mat2), "Mat2ScaleStd()        ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Mat3 Methods\n\n");

  m3 m3a(1.0f,2.0f,3.0f,4.0f,5.0,6.0,7.0,8.0,9.0);
  m3 m3b(10.0f,11.0f,12.0f,13.0f,14.0,15.0,16.0,17.0,18.0);
  m3 m3c(20.0f,21.0f,22.0f,23.0f,24.0,25.0,26.0,27.0,28.0);
  m3 m3d(2.0f,4.0f,6.0f,1.0f,3.0f,5.0f,10.0f,12.0f,15.0f);
  m3 m3r;

  TestResult(Mat3CopyAsm(m3r.m,m3a.m),                    *(m3r.m),  *(m3Results[ 0].m),sizeof(mat3), "Mat3CopyAsm()         ",FCN_ERROR);
  TestResult(Mat3CopyStd(m3r.m,m3a.m),                    *(m3r.m),  *(m3Results[ 0].m),sizeof(mat3), "Mat3CopyStd()         ",FCN_ERROR);
  TestResult(Mat3IdentityAsm(m3r.m),                      *(m3r.m),  *(m3Results[ 1].m),sizeof(mat3), "Mat3IdentityAsm()     ",FCN_ERROR);
  TestResult(Mat3IdentityStd(m3r.m),                      *(m3r.m),  *(m3Results[ 1].m),sizeof(mat3), "Mat3IdentityStd()     ",FCN_ERROR);
  TestResult(Mat3NegateAsm(m3r.m,m3a.m),                  *(m3r.m),  *(m3Results[ 2].m),sizeof(mat3), "Mat3NegateAsm()       ",FCN_ERROR);
  TestResult(Mat3NegateStd(m3r.m,m3a.m),                  *(m3r.m),  *(m3Results[ 2].m),sizeof(mat3), "Mat3NegateStd()       ",FCN_ERROR);
  TestResult(Mat3AddAsm(m3r.m,m3a.m,m3a.m),               *(m3r.m),  *(m3Results[ 3].m),sizeof(mat3), "Mat3AddAsm()          ",FCN_ERROR);
  TestResult(Mat3AddStd(m3r.m,m3a.m,m3a.m),               *(m3r.m),  *(m3Results[ 3].m),sizeof(mat3), "Mat3AddStd()          ",FCN_ERROR);
  TestResult(Mat3AddFloatAsm(m3r.m,m3a.m,1.0f),           *(m3r.m),  *(m3Results[ 4].m),sizeof(mat3), "Mat3AddFloatAsm()     ",FCN_ERROR);
  TestResult(Mat3AddFloatStd(m3r.m,m3a.m,1.0f),           *(m3r.m),  *(m3Results[ 4].m),sizeof(mat3), "Mat3AddFloatStd()     ",FCN_ERROR);
  TestResult(Mat3SubtractAsm(m3r.m,m3b.m,m3a.m),          *(m3r.m),  *(m3Results[ 5].m),sizeof(mat3), "Mat3SubtractAsm()     ",FCN_ERROR);
  TestResult(Mat3SubtractStd(m3r.m,m3b.m,m3a.m),          *(m3r.m),  *(m3Results[ 5].m),sizeof(mat3), "Mat3SubtractStd()     ",FCN_ERROR);
  TestResult(Mat3SubtractFloatAsm(m3r.m,m3b.m,9.0f),      *(m3r.m),  *(m3Results[ 6].m),sizeof(mat3), "Mat3SubtractFloatAsm()",FCN_ERROR);
  TestResult(Mat3SubtractFloatStd(m3r.m,m3b.m,9.0f),      *(m3r.m),  *(m3Results[ 6].m),sizeof(mat3), "Mat3SubtractFloatStd()",FCN_ERROR);
  TestResult(Mat3MultiplyAsm(m3r.m,m3a.m,m3b.m),          *(m3r.m),  *(m3Results[ 7].m),sizeof(mat3), "Mat3MultiplyAsm()     ",FCN_ERROR);
  TestResult(Mat3MultiplyStd(m3r.m,m3a.m,m3b.m),          *(m3r.m),  *(m3Results[ 7].m),sizeof(mat3), "Mat3MultiplyStd()     ",FCN_ERROR);
  TestResult(Mat3MultiplyVecAsm(v3d.vec,m3a.m,v3a.vec),   *(v3d.vec),v3Results[15],     sizeof(vec3), "Mat3MultiplyVecAsm()  ",FCN_ERROR);
  TestResult(Mat3MultiplyVecStd(v3d.vec,m3a.m,v3a.vec),   *(v3d.vec),v3Results[15],     sizeof(vec3), "Mat3MultiplyVecStd()  ",FCN_ERROR);
  TestResult(Mat3InverseAsm(m3r.m,m3d.m),                 *(m3r.m),  *(m3Results[ 9].m),sizeof(mat3), "Mat3InverseAsm()      ",FCN_ERROR);
  TestResult(Mat3InverseStd(m3r.m,m3d.m),                 *(m3r.m),  *(m3Results[ 8].m),sizeof(mat3), "Mat3InverseStd()      ",FCN_ERROR);
  TestResult(Mat3MultiplyFloatAsm(m3r.m,m3a.m,2.0f),      *(m3r.m),  *(m3Results[10].m),sizeof(mat3), "Mat3MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Mat3MultiplyFloatStd(m3r.m,m3a.m,2.0f),      *(m3r.m),  *(m3Results[10].m),sizeof(mat3), "Mat3MultiplyFloatStd()",FCN_ERROR);
  TestResult(Mat3TransposeAsm(m3r.m,m3a.m),               *(m3r.m),  *(m3Results[11].m),sizeof(mat3), "Mat3TransposeAsm()    ",FCN_ERROR);
  TestResult(Mat3TransposeStd(m3r.m,m3a.m),               *(m3r.m),  *(m3Results[11].m),sizeof(mat3), "Mat3TransposeStd()    ",FCN_ERROR);
  TestResult(Mat3RotateRHX_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[12].m),sizeof(mat3), "Mat3RotateRHX_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateRHX_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[12].m),sizeof(mat3), "Mat3RotateRHX_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateLHX_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[13].m),sizeof(mat3), "Mat3RotateLHX_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateLHX_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[13].m),sizeof(mat3), "Mat3RotateLHX_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateRHY_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[14].m),sizeof(mat3), "Mat3RotateRHY_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateRHY_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[14].m),sizeof(mat3), "Mat3RotateRHY_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateLHY_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[15].m),sizeof(mat3), "Mat3RotateLHY_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateLHY_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[15].m),sizeof(mat3), "Mat3RotateLHY_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateRHZ_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[16].m),sizeof(mat3), "Mat3RotateRHZ_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateRHZ_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[16].m),sizeof(mat3), "Mat3RotateRHZ_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateLHZ_Asm(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[17].m),sizeof(mat3), "Mat3RotateLHZ_Asm()   ",FCN_ERROR);
  TestResult(Mat3RotateLHZ_Std(m3r.m,60.0f/90.0f*1.57),   *(m3r.m),  *(m3Results[17].m),sizeof(mat3), "Mat3RotateLHZ_Std()   ",FCN_ERROR);
  TestResult(Mat3RotateRHXY_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[18].m),sizeof(mat3), "Mat3RotateRHXY_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateRHXY_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[19].m),sizeof(mat3), "Mat3RotateRHXY_Std()  ",FCN_ERROR);
  TestResult(Mat3RotateLHXY_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[20].m),sizeof(mat3), "Mat3RotateLHXY_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateLHXY_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[21].m),sizeof(mat3), "Mat3RotateLHXY_Std()  ",FCN_ERROR);
  TestResult(Mat3RotateRHXZ_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[22].m),sizeof(mat3), "Mat3RotateRHXZ_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateRHXZ_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[23].m),sizeof(mat3), "Mat3RotateRHXZ_Std()  ",FCN_ERROR);
  TestResult(Mat3RotateLHXZ_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[24].m),sizeof(mat3), "Mat3RotateLHXZ_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateLHXZ_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[25].m),sizeof(mat3), "Mat3RotateLHXZ_Std()  ",FCN_ERROR);
  TestResult(Mat3RotateRHYZ_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[26].m),sizeof(mat3), "Mat3RotateRHYZ_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateRHYZ_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[27].m),sizeof(mat3), "Mat3RotateRHYZ_Std()  ",FCN_ERROR);
  TestResult(Mat3RotateLHYZ_Asm(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[28].m),sizeof(mat3), "Mat3RotateLHYZ_Asm()  ",FCN_ERROR);
  TestResult(Mat3RotateLHYZ_Std(m3r.m,60.0f/90.0f*1.57,60.0f/90.0f*1.57),*(m3r.m),*(m3Results[29].m),sizeof(mat3), "Mat3RotateLHYZ_Std()  ",FCN_ERROR);

  float fAngle = 60.0f/90.0f*1.57;

  TestResult(Mat3RotateRHXYZ_Asm(m3r.m,fAngle,fAngle,fAngle),  *(m3r.m),*(m3Results[30].m),sizeof(mat3), "Mat3RotateRHXYZ_Asm() ",FCN_ERROR);
  TestResult(Mat3RotateRHXYZ_Std(m3r.m,fAngle,fAngle,fAngle),  *(m3r.m),*(m3Results[31].m),sizeof(mat3), "Mat3RotateRHXYZ_Std() ",FCN_ERROR);
  TestResult(Mat3RotateLHXYZ_Asm(m3r.m,fAngle,fAngle,fAngle),  *(m3r.m),*(m3Results[32].m),sizeof(mat3), "Mat3RotateLHXYZ_Asm() ",FCN_ERROR);
  TestResult(Mat3RotateLHXYZ_Std(m3r.m,fAngle,fAngle,fAngle),  *(m3r.m),*(m3Results[33].m),sizeof(mat3), "Mat3RotateLHXYZ_Std() ",FCN_ERROR);

  TestResult(Mat3ScaleAsm(m3r.m,2.0f,3.0f,4.0f),          *(m3r.m),  *(m3Results[34].m),sizeof(mat3), "Mat3ScaleAsm()        ",FCN_ERROR);
  TestResult(Mat3ScaleStd(m3r.m,2.0f,3.0f,4.0f),          *(m3r.m),  *(m3Results[34].m),sizeof(mat3), "Mat3ScaleStd()        ",FCN_ERROR);

  TestResult(Mat3ScaleByVec3Asm(m3r.m,v3a.vec),           *(m3r.m),  *(m3Results[35].m),sizeof(mat3), "Mat3ScaleByVec3Asm()  ",FCN_ERROR);
  TestResult(Mat3ScaleByVec3Std(m3r.m,v3a.vec),           *(m3r.m),  *(m3Results[35].m),sizeof(mat3), "Mat3ScaleByVec3Std()  ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Mat4 Methods\n\n");

  m4 m4a(1.0f,2.0f,3.0f,4.0f,
	 5.0f,6.0f,7.0f,8.0f,
	 9.0f,10.0f,11.0f,12.0f,
	 13.0f,14.0f,15.0f,16.0f);
  m4 m4b(1.0f,2.0f,3.0f,4.0f,
	 5.0f,6.0f,7.0f,8.0f,
	 9.0f,10.0f,11.0f,12.0f,
	 13.0f,14.0f,15.0f,16.0f);
  m4 m4c(17.0f,18.0f,19.0f,20.0f,
	 21.0f,22.0f,23.0f,24.0f,
	 25.0f,26.0f,27.0f,28.0f,
	 29.0f,30.0f,31.0f,32.0f);
  m4 m4r;

  TestResult(Mat4CopyAsm(m4r.m,m4a.m),                    *(m4r.m),  *(m4Results[ 0].m),sizeof(mat4), "Mat4CopyAsm()         ",FCN_ERROR);
  TestResult(Mat4CopyStd(m4r.m,m4a.m),                    *(m4r.m),  *(m4Results[ 0].m),sizeof(mat4), "Mat4CopyStd()         ",FCN_ERROR);
  TestResult(Mat4NegateAsm(m4r.m,m4a.m),                  *(m4r.m),  *(m4Results[ 1].m),sizeof(mat4), "Mat4NegateAsm()       ",FCN_ERROR);
  TestResult(Mat4NegateStd(m4r.m,m4a.m),                  *(m4r.m),  *(m4Results[ 1].m),sizeof(mat4), "Mat4NegateStd()       ",FCN_ERROR);
  TestResult(Mat4AddAsm(m4r.m,m4a.m,m4b.m),               *(m4r.m),  *(m4Results[ 2].m),sizeof(mat4), "Mat4AddAsm()          ",FCN_ERROR);
  TestResult(Mat4AddStd(m4r.m,m4a.m,m4b.m),               *(m4r.m),  *(m4Results[ 2].m),sizeof(mat4), "Mat4AddStd()          ",FCN_ERROR);
  TestResult(Mat4AddFloatAsm(m4r.m,m4a.m,1.0f),           *(m4r.m),  *(m4Results[ 3].m),sizeof(mat4), "Mat4AddFloatAsm()     ",FCN_ERROR);
  TestResult(Mat4AddFloatStd(m4r.m,m4a.m,1.0f),           *(m4r.m),  *(m4Results[ 3].m),sizeof(mat4), "Mat4AddFloatStd()     ",FCN_ERROR);
  TestResult(Mat4SubtractAsm(m4r.m,m4c.m,m4a.m),          *(m4r.m),  *(m4Results[ 4].m),sizeof(mat4), "Mat4SubtractAsm()     ",FCN_ERROR);
  TestResult(Mat4SubtractStd(m4r.m,m4c.m,m4a.m),          *(m4r.m),  *(m4Results[ 4].m),sizeof(mat4), "Mat4SubtractStd()     ",FCN_ERROR);
  TestResult(Mat4SubtractFloatAsm (m4r.m,m4c.m,1.0f),     *(m4r.m),  *(m4Results[ 5].m),sizeof(mat4), "Mat4SubtractFloatAsm()",FCN_ERROR);
  TestResult(Mat4SubtractFloatStd (m4r.m,m4c.m,1.0f),     *(m4r.m),  *(m4Results[ 5].m),sizeof(mat4), "Mat4SubtractFloatStd()",FCN_ERROR);
  TestResult(Mat4MultiplyAsm(m4r.m,m4a.m,m4b.m),          *(m4r.m),  *(m4Results[ 6].m),sizeof(mat4), "Mat4MultiplyAsm()     ",FCN_ERROR);
  TestResult(Mat4MultiplyStd(m4r.m,m4a.m,m4b.m),          *(m4r.m),  *(m4Results[ 6].m),sizeof(mat4), "Mat4MultiplyStd()     ",FCN_ERROR);
  TestResult(Mat4MultiplyVecAsm(v4r.vec,m4a.m,v4a.vec),   *(v4r.vec),     v4Results[15],sizeof(vec4), "Mat4MultiplyVecAsm()  ",FCN_ERROR);
  TestResult(Mat4MultiplyVecStd(v4r.vec,m4a.m,v4a.vec),   *(v4r.vec),     v4Results[15],sizeof(vec4), "Mat4MultiplyVecStd()  ",FCN_ERROR);

#if 0
  // XXX: THIS WON'T WORK ON THIS PROCESSOR
  //
  Mat4LookAtAsm(m4r.m,v3c.vec,v3a.vec);
#endif
  TestResult(Mat4LookAtStd(m4r.m,v3c.vec,v3a.vec),        *(m4r.m),  *(m4Results[ 7].m),sizeof(mat4), "Mat4LookAtStd()       ",FCN_ERROR);

  TestResult(Mat4MultiplyFloatAsm(m4r.m,m4a.m,2.0f),      *(m4r.m),  *(m4Results[ 8].m),sizeof(mat4), "Mat4MultiplyFloatAsm()",FCN_ERROR);
  TestResult(Mat4MultiplyFloatStd(m4r.m,m4a.m,2.0f),      *(m4r.m),  *(m4Results[ 8].m),sizeof(mat4), "Mat4MultiplyFloatStd()",FCN_ERROR);
  TestResult(Mat4TransposeAsm(m4r.m,m4a.m),               *(m4r.m),  *(m4Results[ 9].m),sizeof(mat4), "Mat4TransposeAsm()    ",FCN_ERROR);
  TestResult(Mat4TransposeStd(m4r.m,m4a.m),               *(m4r.m),  *(m4Results[ 9].m),sizeof(mat4), "Mat4TransposeStd()    ",FCN_ERROR);
  TestResult(Mat4ShadowMatrixAsm(m4r.m,v3c.vec,-10.0f,v3a.vec),*(m4r.m),  *(m4Results[10].m),sizeof(mat4), "Mat4ShadowMatrixAsm() ",FCN_ERROR);
  TestResult(Mat4ShadowMatrixStd(m4r.m,v3c.vec,-10.0f,v3a.vec),*(m4r.m),  *(m4Results[10].m),sizeof(mat4), "Mat4ShadowMatrixStd() ",FCN_ERROR);
  TestResult(Mat4MirrorMatrixAsm(m4r.m,v3c.vec,-10.0f),   *(m4r.m),  *(m4Results[11].m),sizeof(mat4), "Mat4MirrorMatrixAsm() ",FCN_ERROR);
  TestResult(Mat4MirrorMatrixStd(m4r.m,v3c.vec,-10.0f),   *(m4r.m),  *(m4Results[11].m),sizeof(mat4), "Mat4MirrorMatrixStd() ",FCN_ERROR);
  TestResult(Mat4GlToD3DProjMatAsm(m4r.m,m4a.m),          *(m4r.m),  *(m4Results[12].m),sizeof(mat4), "Mat4GlToD3DProjMatAsm(",FCN_ERROR);
  TestResult(Mat4GlToD3DProjMatStd(m4r.m,m4a.m),          *(m4r.m),  *(m4Results[12].m),sizeof(mat4), "Mat4GlToD3DProjMatStd(",FCN_ERROR);
  TestResult(Mat4LookAtLHAsm(m4r.m,v3c.vec,v3a.vec,v3b.vec),*(m4r.m),  *(m4Results[13].m),sizeof(mat4), "Mat4LookAtLHAsm()     ",FCN_ERROR);
  TestResult(Mat4LookAtLHStd(m4r.m,v3c.vec,v3a.vec,v3b.vec),*(m4r.m),  *(m4Results[14].m),sizeof(mat4), "Mat4LookAtLHStd()     ",FCN_ERROR);
  TestResult(Mat4IdentityAsm(m4r.m),                      *(m4r.m),  *(m4Results[15].m),sizeof(mat4), "Mat4IdentityAsm()     ",FCN_ERROR);
  TestResult(Mat4IdentityStd(m4r.m),                      *(m4r.m),  *(m4Results[15].m),sizeof(mat4), "Mat4IdentityStd()     ",FCN_ERROR);
  TestResult(Mat4ScaleAsm(m4r.m,2.0f,3.0f,4.0f),          *(m4r.m),  *(m4Results[16].m),sizeof(mat4), "Mat4ScaleAsm()        ",FCN_ERROR);
  TestResult(Mat4ScaleStd(m4r.m,2.0f,3.0f,4.0f),          *(m4r.m),  *(m4Results[16].m),sizeof(mat4), "Mat4ScaleStd()        ",FCN_ERROR);
  TestResult(Mat4RotateRHX_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[17].m),sizeof(mat4), "Mat4RotateRHX_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHX_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[17].m),sizeof(mat4), "Mat4RotateRHX_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHX_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[18].m),sizeof(mat4), "Mat4RotateLHX_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHX_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[18].m),sizeof(mat4), "Mat4RotateLHX_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHY_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[19].m),sizeof(mat4), "Mat4RotateRHY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHY_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[19].m),sizeof(mat4), "Mat4RotateRHY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHY_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[20].m),sizeof(mat4), "Mat4RotateLHY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHY_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[20].m),sizeof(mat4), "Mat4RotateLHY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHZ_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[21].m),sizeof(mat4), "Mat4RotateRHZ_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHZ_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[21].m),sizeof(mat4), "Mat4RotateRHZ_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHZ_Asm(m4r.m,fAngle),             *(m4r.m),  *(m4Results[22].m),sizeof(mat4), "Mat4RotateLHZ_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHZ_Std(m4r.m,fAngle),             *(m4r.m),  *(m4Results[22].m),sizeof(mat4), "Mat4RotateLHZ_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHXY_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[23].m),sizeof(mat4), "Mat4RotateRHXY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHXY_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[24].m),sizeof(mat4), "Mat4RotateRHXY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHXY_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[25].m),sizeof(mat4), "Mat4RotateLHXY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHXY_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[26].m),sizeof(mat4), "Mat4RotateLHXY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHXZ_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[27].m),sizeof(mat4), "Mat4RotateRHXY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHXZ_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[28].m),sizeof(mat4), "Mat4RotateRHXY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHXZ_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[29].m),sizeof(mat4), "Mat4RotateLHXY_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHXZ_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[30].m),sizeof(mat4), "Mat4RotateLHXY_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHYZ_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[31].m),sizeof(mat4), "Mat4RotateRHYZ_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateRHYZ_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[32].m),sizeof(mat4), "Mat4RotateRHYZ_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateLHYZ_Asm(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[33].m),sizeof(mat4), "Mat4RotateLHYZ_Asm()   ",FCN_ERROR);
  TestResult(Mat4RotateLHYZ_Std(m4r.m,fAngle,fAngle),     *(m4r.m),  *(m4Results[34].m),sizeof(mat4), "Mat4RotateLHYZ_Std()   ",FCN_ERROR);
  TestResult(Mat4RotateRHXYZ_Asm(m4r.m,fAngle,fAngle,fAngle),*(m4r.m),  *(m4Results[35].m),sizeof(mat4), "Mat4RotateRHXYZ_Asm()  ",FCN_ERROR);
  TestResult(Mat4RotateRHXYZ_Std(m4r.m,fAngle,fAngle,fAngle),*(m4r.m),  *(m4Results[36].m),sizeof(mat4), "Mat4RotateRHXYZ_Std()  ",FCN_ERROR);
  TestResult(Mat4RotateLHXYZ_Asm(m4r.m,fAngle,fAngle,fAngle),*(m4r.m),  *(m4Results[37].m),sizeof(mat4), "Mat4RotateLHXYZ_Asm()  ",FCN_ERROR);
  TestResult(Mat4RotateLHXYZ_Std(m4r.m,fAngle,fAngle,fAngle),*(m4r.m),  *(m4Results[38].m),sizeof(mat4), "Mat4RotateLHXYZ_Std()  ",FCN_ERROR);
  TestResult(Mat4TranslateRH_Asm(m4r.m,2.0f,3.0f,4.0f),   *(m4r.m),  *(m4Results[39].m),sizeof(mat4), "Mat4TranslateRH_Asm()  ",FCN_ERROR);
  TestResult(Mat4TranslateRH_Std(m4r.m,2.0f,3.0f,4.0f),   *(m4r.m),  *(m4Results[39].m),sizeof(mat4), "Mat4TranslateRH_Std()  ",FCN_ERROR);
  TestResult(Mat4TranslateLH_Asm(m4r.m,2.0f,3.0f,4.0f),   *(m4r.m),  *(m4Results[40].m),sizeof(mat4), "Mat4TranslateLH_Asm()  ",FCN_ERROR);
  TestResult(Mat4TranslateLH_Std(m4r.m,2.0f,3.0f,4.0f),   *(m4r.m),  *(m4Results[40].m),sizeof(mat4), "Mat4TranslateLH_Std()  ",FCN_ERROR);
  TestResult(Mat4TranslateRH_Vec3Asm(m4r.m,v3a.vec),      *(m4r.m),  *(m4Results[41].m),sizeof(mat4), "Mat4TranslateRH_Vec3Asm",FCN_ERROR);
  TestResult(Mat4TranslateRH_Vec3Std(m4r.m,v3a.vec),      *(m4r.m),  *(m4Results[41].m),sizeof(mat4), "Mat4TranslateRH_Vec3Std",FCN_ERROR);
  TestResult(Mat4TranslateLH_Vec3Asm(m4r.m,v3a.vec),      *(m4r.m),  *(m4Results[42].m),sizeof(mat4), "Mat4TranslateLH_Vec3Asm",FCN_ERROR);
  TestResult(Mat4TranslateLH_Vec3Std(m4r.m,v3a.vec),      *(m4r.m),  *(m4Results[42].m),sizeof(mat4), "Mat4TranslateLH_Vec3Std",FCN_ERROR);
  TestResult(Mat4TranslateRH_Vec4Asm(m4r.m,v4a.vec),      *(m4r.m),  *(m4Results[43].m),sizeof(mat4), "Mat4TranslateRH_Vec4Asm",FCN_ERROR);
  TestResult(Mat4TranslateRH_Vec4Std(m4r.m,v4a.vec),      *(m4r.m),  *(m4Results[43].m),sizeof(mat4), "Mat4TranslateRH_Vec4Std",FCN_ERROR);
  TestResult(Mat4TranslateLH_Vec4Asm(m4r.m,v4a.vec),      *(m4r.m),  *(m4Results[44].m),sizeof(mat4), "Mat4TranslateLH_Vec4Asm",FCN_ERROR);
  TestResult(Mat4TranslateLH_Vec4Std(m4r.m,v4a.vec),      *(m4r.m),  *(m4Results[44].m),sizeof(mat4), "Mat4TranslateLH_Vec4Std",FCN_ERROR);
  TestResult(Mat4OrthoMatrixAsm(m4r.m,1.0f,100.0f,1.0f,100.0f,20.0f,-100.0f,0),*(m4r.m),*(m4Results[45].m),sizeof(mat4), "Mat4OrthoMatrixAsm()   ",FCN_ERROR);
  TestResult(Mat4OrthoMatrixStd(m4r.m,1.0f,100.0f,1.0f,100.0f,20.0f,-100.0f,0),*(m4r.m),*(m4Results[45].m),sizeof(mat4), "Mat4OrthoMatrixStd()   ",FCN_ERROR);
  TestResult(Mat4PerspectiveAsm(m4r.m,20.0f,100.0f,100.0f,20.0f,-100.0f,0),*(m4r.m),*(m4Results[46].m),sizeof(mat4), "Mat4PerspectiveAsm()   ",FCN_ERROR);
  TestResult(Mat4PerspectiveStd(m4r.m,20.0f,100.0f,100.0f,20.0f,-100.0f,0),*(m4r.m),*(m4Results[46].m),sizeof(mat4), "Mat4PerspectiveStd()   ",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,0),               *(m4r.m),  *(m4Results[47].m),sizeof(mat4), "Mat4CubemapMatrixAsm(0)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,0),               *(m4r.m),  *(m4Results[47].m),sizeof(mat4), "Mat4CubemapMatrixStd(0)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,1),               *(m4r.m),  *(m4Results[48].m),sizeof(mat4), "Mat4CubemapMatrixAsm(1)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,1),               *(m4r.m),  *(m4Results[48].m),sizeof(mat4), "Mat4CubemapMatrixStd(1)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,2),               *(m4r.m),  *(m4Results[49].m),sizeof(mat4), "Mat4CubemapMatrixAsm(2)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,2),               *(m4r.m),  *(m4Results[49].m),sizeof(mat4), "Mat4CubemapMatrixStd(2)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,3),               *(m4r.m),  *(m4Results[50].m),sizeof(mat4), "Mat4CubemapMatrixAsm(3)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,3),               *(m4r.m),  *(m4Results[50].m),sizeof(mat4), "Mat4CubemapMatrixStd(3)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,4),               *(m4r.m),  *(m4Results[51].m),sizeof(mat4), "Mat4CubemapMatrixAsm(4)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,4),               *(m4r.m),  *(m4Results[51].m),sizeof(mat4), "Mat4CubemapMatrixStd(4)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixAsm(m4r.m,5),               *(m4r.m),  *(m4Results[52].m),sizeof(mat4), "Mat4CubemapMatrixAsm(5)",FCN_ERROR);
  TestResult(Mat4CubemapMatrixStd(m4r.m,5),               *(m4r.m),  *(m4Results[52].m),sizeof(mat4), "Mat4CubemapMatrixStd(5)",FCN_ERROR);
  TestResult(Mat4CubemapProjectionMatAsm(m4r.m,-2.0f,100.0f,0),*(m4r.m),  *(m4Results[53].m),sizeof(mat4), "Mat4CubemapProjectAsm  ",FCN_ERROR);
  TestResult(Mat4CubemapProjectionMatStd(m4r.m,-2.0f,100.0f,0),*(m4r.m),  *(m4Results[53].m),sizeof(mat4), "Mat4CubemapProjectStd  ",FCN_ERROR);
  TestResult(Mat3RotationFromMat4Asm(m3r.m,m4a.m),        *(m3r.m),  *(m3Results[36].m),sizeof(mat3), "Mat3RotationFromMat4As",FCN_ERROR);
  TestResult(Mat3RotationFromMat4Std(m3r.m,m4a.m),        *(m3r.m),  *(m3Results[36].m),sizeof(mat3), "Mat3RotationFromMat4St",FCN_ERROR);
  TestResult(Mat4FromMat3Asm(m4r.m,m3r.m),                *(m4r.m),  *(m4Results[54].m),sizeof(mat4), "Mat4FromMat3Asm()     ",FCN_ERROR);
  TestResult(Mat4FromMat3Std(m4r.m,m3r.m),                *(m4r.m),  *(m4Results[54].m),sizeof(mat4), "Mat4FromMat3Std()     ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Quaternion Methods\n\n");

  quat qa(1.0f,2.0f,3.0f,4.0f);
  quat qb(5.0f,6.0f,7.0f,8.0f);
  quat qr;

  TestResult(QuaternionAddAsm(qr.q,qa.q,qb.q),            *(qr.q),   *(qResults[ 0].q), sizeof(quaternion), "QuaternionAddAsm()    ",FCN_ERROR);
  TestResult(QuaternionAddStd(qr.q,qa.q,qb.q),            *(qr.q),   *(qResults[ 0].q), sizeof(quaternion), "QuaternionAddStd()    ",FCN_ERROR);
  TestResult(QuaternionMultiplyAsm(qr.q,qa.q,qb.q),       *(qr.q),   *(qResults[ 1].q), sizeof(quaternion), "QuaternionMultiplyAsm ",FCN_ERROR);
  TestResult(QuaternionMultiplyStd(qr.q,qa.q,qb.q),       *(qr.q),   *(qResults[ 1].q), sizeof(quaternion), "QuaternionMultiplyStd ",FCN_ERROR);
  TestResult(QuaternionInverseAsm(qr.q,qa.q),             *(qr.q),   *(qResults[ 2].q), sizeof(quaternion), "QuaternionMultiplyAsm ",FCN_ERROR);
  TestResult(QuaternionInverseStd(qr.q,qa.q),             *(qr.q),   *(qResults[ 2].q), sizeof(quaternion), "QuaternionMultiplyStd ",FCN_ERROR);
  TestResult(QuaternionToMat3Asm(m3r.m,qa.q),            *(m3r.m),  *(m3Results[37].m),       sizeof(mat3), "QuaternionToMat3Asm() ",FCN_ERROR);
  TestResult(QuaternionToMat3Std(m3r.m,qa.q),            *(m3r.m),  *(m3Results[37].m),       sizeof(mat3), "QuaternionToMat3Std() ",FCN_ERROR);
  TestResult(QuaternionFromAxisAsm(qr.q,v3a.vec,fAngle),  *(qr.q),   *(qResults[ 3].q), sizeof(quaternion), "QuaternionFromAxisAsm ",FCN_ERROR);
  TestResult(QuaternionFromAxisStd(qr.q,v3a.vec,fAngle),  *(qr.q),   *(qResults[ 4].q), sizeof(quaternion), "QuaternionFromAxisStd ",FCN_ERROR);
  TestResult(QuaternionToMat4Asm(m4r.m,qa.q),            *(m4r.m),  *(m4Results[55].m),sizeof(mat4), "QuaternionToMat4Asm()  ",FCN_ERROR);
  TestResult(QuaternionToMat4Std(m4r.m,qa.q),            *(m4r.m),  *(m4Results[55].m),sizeof(mat4), "QuaternionToMat4Std()  ",FCN_ERROR);

  TestResult(QuaternionFromMat3Asm(qr.q,m3a.m),           *(qr.q),   *(qResults[ 5].q), sizeof(quaternion), "QuaternionFromMat3Asm ",FCN_ERROR);
  TestResult(QuaternionFromMat3Std(qr.q,m3a.m),           *(qr.q),   *(qResults[ 5].q), sizeof(quaternion), "QuaternionFromMat3Std ",FCN_ERROR);

  m3 m3x(1.0f,1.0f,2.0f,
	 1.0f,-1.0f,4.0f,
	 1.0f, 1.0f,-3.0f);

  TestResult(QuaternionFromMat3Asm(qr.q,m3x.m),           *(qr.q),   *(qResults[ 6].q), sizeof(quaternion), "QuaternionFromMat3Asm ",FCN_ERROR);
  TestResult(QuaternionFromMat3Std(qr.q,m3x.m),           *(qr.q),   *(qResults[ 7].q), sizeof(quaternion), "QuaternionFromMat3Std ",FCN_ERROR);

  m3 m3y(-1.0f,1.0f,2.0f,
	 1.0f, 1.0f, 4.0f,
	 1.0f, 1.0f, -3.0f);
	 
  TestResult(QuaternionFromMat3Asm(qr.q,m3y.m),           *(qr.q),   *(qResults[ 8].q), sizeof(quaternion), "QuaternionFromMat3Asm ",FCN_ERROR);
  TestResult(QuaternionFromMat3Std(qr.q,m3y.m),           *(qr.q),   *(qResults[ 9].q), sizeof(quaternion), "QuaternionFromMat3Std ",FCN_ERROR);

  m3 m3z(-1.0f,1.0f,2.0f,
	 1.0f,-3.0f,4.0f,
	 1.0f,1.0f,1.0f);

  TestResult(QuaternionFromMat3Asm(qr.q,m3z.m),           *(qr.q),   *(qResults[10].q), sizeof(quaternion), "QuaternionFromMat3Asm ",FCN_ERROR);
  TestResult(QuaternionFromMat3Std(qr.q,m3z.m),           *(qr.q),   *(qResults[11].q), sizeof(quaternion), "QuaternionFromMat3Std ",FCN_ERROR);

  TestResult(QuaternionFromMat4Asm(qr.q,m4a.m),           *(qr.q),   *(qResults[12].q), sizeof(quaternion), "QuaternionFromMat4Asm ",FCN_ERROR);
  TestResult(QuaternionFromMat4Std(qr.q,m4a.m),           *(qr.q),   *(qResults[12].q), sizeof(quaternion), "QuaternionFromMat4Std ",FCN_ERROR);

  quat qc(0.0f,0.0f,0.0f,.25);
  quat qd(0.0f,0.0f,0.0f,.85);

  TestResult(QuaternionSlerpAsm(qr.q,.5,qc.q,qd.q),       *(qr.q),   *(qResults[13].q), sizeof(quaternion), "QuaternionSlerpAsm()  ",FCN_ERROR);
  TestResult(QuaternionSlerpStd(qr.q,.5,qc.q,qd.q),       *(qr.q),   *(qResults[13].q), sizeof(quaternion), "QuaternionSlerpStd()  ",FCN_ERROR);

#if 0
  // XXX: THESE WON'T WORK ON THIS PROCESSOR
  QuaternionNormalizeAsm(qr.q,qa.q);
  QuaternionDotAsm(qr.q,qa.q,qb.q);
#endif

#if 0
  // XXX: This needs work
  QuaternionCosAsm(&fr,qa.q,qb.q);

  fprintf(stdout,"angle: %5.3f\n",(fr > 6.28 ? fr/6.28 : fr));
#endif
	  

  fprintf(stdout,"\n-------------> Vector2 Block Methods\n\n");

  v2array v2aa(12,v2Results);
  v2array v2ar(12,v2Results);

  TestResult(Vec2AddFloatToBlockAsm(v2ar,0.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2AddFloatToBlock()  ",FCN_ERROR);
  TestResult(Vec2AddFloatToBlockStd(v2ar,0.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2AddFloatToBlock()  ",FCN_ERROR);
  TestResult(Vec2AddFloatToBlockSizeAsm(v2ar,0.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2AddFloatToSizeBlock()  ",FCN_ERROR);
  TestResult(Vec2AddFloatToBlockSizeStd(v2ar,0.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2AddFloatToSizeBlock()  ",FCN_ERROR);
  TestResult(Vec2SubtractFloatFromBlockAsm(v2ar,0.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"VecSubFloatFromBlockAsm()  ",FCN_ERROR);
  TestResult(Vec2SubtractFloatFromBlockStd(v2ar,0.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2SubFloatFromBlockStd()  ",FCN_ERROR);
  TestResult(Vec2SubFloatFromBlockSizeAsm(v2ar,0.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"VecSubFloatFromBlockAsm()  ",FCN_ERROR);
  TestResult(Vec2SubFloatFromBlockSizeStd(v2ar,0.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2SubFloatFromBlockStd()  ",FCN_ERROR);
  TestResult(Vec2MultiplyBlockByFloatAsm(v2ar,1.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2MultiplyBlockByFloatAsm()  ",FCN_ERROR);
  TestResult(Vec2MultiplyBlockByFloatStd(v2ar,1.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2MultiplyBlockByFloatStd()  ",FCN_ERROR);
  TestResult(Vec2MultiplyBlkByFloatSizeAsm(v2ar,1.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2MultiplyBlkByFloatSizeAsm()  ",FCN_ERROR);
  TestResult(Vec2MultiplyBlkByFloatSizeStd(v2ar,1.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2MultiplyBlkByFloatSizeStd()  ",FCN_ERROR);
  TestResult(Vec2DivideBlockByFloatAsm(v2ar,1.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2DivideBlockByFloatAsm()  ",FCN_ERROR);
  TestResult(Vec2DivideBlockByFloatStd(v2ar,1.0,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2DivideBlockByFloatStd()  ",FCN_ERROR);
  TestResult(Vec2DivideBlockByFloatSizeAsm(v2ar,1.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2DivideBlockByFloatSizeAsm()  ",FCN_ERROR);
  TestResult(Vec2DivideBlockByFloatSizeStd(v2ar,1.0,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2DivideBlockByFloatSizeStd()  ",FCN_ERROR);

  Vec2NegateBlockAsm(v2ar,v2ar.length());
  TestResult(Vec2NegateBlockAsm(v2ar,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2NegateBlockAsm()       ",FCN_ERROR);
  Vec2NegateBlockAsm(v2ar,v2ar.length());
  TestResult(Vec2NegateBlockStd(v2ar,v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2NegateBlockStd()       ",FCN_ERROR);
  Vec2NegateBlockAsm(v2ar,v2ar.length());
  TestResult(Vec2NegateBlockBySizeAsm(v2ar,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2NegateBlockBySizeAsm() ",FCN_ERROR);
  Vec2NegateBlockAsm(v2ar,v2ar.length());
  TestResult(Vec2NegateBlockBySizeStd(v2ar,sizeof(vec2),v2ar.length()),v2ar.m_Vec2Array[0],v2Results[0],
	     v2ar.length()*sizeof(float),"Vec2NegateBlockBySizeStd() ",FCN_ERROR);

  v2 v2ATest(1.0f,2.0f);

  TestResult(Vec2AddVec2ToBlockAsm(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[14],
	     6*sizeof(float),"Vec2AddVec2ToBlockAsm()    ",FCN_ERROR);
  for( int i=0 ; i < 12 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2AddVec2ToBlockStd(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[14],
	     6*sizeof(float),"Vec2AddVec2ToBlockStd()    ",FCN_ERROR);
  TestResult(Vec2SubtractVec2FromBlockAsm(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2SubtractVec2FromBlockAsm()",FCN_ERROR);
  Vec2AddVec2ToBlockAsm(v2ar,v2ATest,6);
  TestResult(Vec2SubtractVec2FromBlockStd(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2SubtractVec2FromBlockStd()",FCN_ERROR);

  for( int i=0 ; i < 12 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2MultiplyBlockByVec2Asm(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[26],
	     6*sizeof(float),"Vec2MultiplyBlockByVec2Asm()",FCN_ERROR);
  for( int i=0 ; i < 12 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2MultiplyBlockByVec2Asm(v2ar,v2ATest,6),v2ar.m_Vec2Array[0],v2Results[26],
	     6*sizeof(float),"Vec2MultiplyBlockByVec2Asm()",FCN_ERROR);

  v2 v2BTest(1.0f,1.0f);

  for( int i=0 ; i < 12 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2DivideBlockByVec2Asm(v2ar,v2BTest,6),v2ar.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2DivideBlockByVec2Asm()",FCN_ERROR);
  TestResult(Vec2DivideBlockByVec2Std(v2ar,v2BTest,6),v2ar.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2DivideBlockByVec2Std()",FCN_ERROR);

  v2array v2lerp0(12,v2Results);
  v2array v2lerp1(12,&v2Results[14]);

  TestResult(Vec2LerpBlockAsm(v2ar,v2lerp0,v2lerp1,0.5,6),v2ar.m_Vec2Array[0],v2Results[32],
	     6*sizeof(float),"Vec2LerpBlockAsm()  ",FCN_ERROR);
  TestResult(Vec2LerpBlockStd(v2ar,v2lerp0,v2lerp1,0.5,6),v2ar.m_Vec2Array[0],v2Results[32],
	     6*sizeof(float),"Vec2LerpBlockStd()  ",FCN_ERROR);
  TestResult(Vec2SqrBlockAsm(v2ar,v2lerp0,6),v2ar.m_Vec2Array[0],v2Results[38],
	     6*sizeof(float),"Vec2SqrBlockAsm()    ",FCN_ERROR);
  TestResult(Vec2SqrBlockStd(v2ar,v2lerp0,6),v2ar.m_Vec2Array[0],v2Results[38],
	     6*sizeof(float),"Vec2SqrBlockStd()    ",FCN_ERROR);
  TestResult(Vec2NormalizeBlockAsm(v2ar,v2lerp0,6),v2ar.m_Vec2Array[0],v2Results[44],
	     6*sizeof(float),"Vec2NormalizeBlockAsm()", FCN_ERROR);
  TestResult(Vec2NormalizeBlockStd(v2ar,v2lerp0,6),v2ar.m_Vec2Array[0],v2Results[44],
	     6*sizeof(float),"Vec2NormalizeBlockStd()", FCN_ERROR);

  float fRes[6];

  TestResult(Vec2DotBlockAsm(fRes,v2lerp0,v2lerp1,6),fRes[0],FloatList[4],
	     6*sizeof(float),"Vec2DotBlockAsm()      ",FCN_ERROR);
  TestResult(Vec2DotBlockStd(fRes,v2lerp0,v2lerp1,6),fRes[0],FloatList[4],
	     6*sizeof(float),"Vec2DotBlockStd()      ",FCN_ERROR);
  TestResult(Vec2LengthBlockAsm(fRes,v2lerp0,6),fRes[0],FloatList[10],
	     6*sizeof(float),"Vec2LengthBlockAsm()   ",FCN_ERROR);
  TestResult(Vec2LengthBlockStd(fRes,v2lerp0,6),fRes[0],FloatList[10],
	     6*sizeof(float),"Vec2LengthBlockStd()   ",FCN_ERROR);

  for( int i=0 ; i < 6 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2AddBlockToBlockAsm(v2ar,v2aa,6),v2ar.m_Vec2Array[0],v2Results[50],
	     6*sizeof(float),"Vec2AddBlockToBlockAsm()",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2SubtractBlockFromBlockAsm(v2ar,v2aa,6),v2ar.m_Vec2Array[0],v2Results[56],
	     6*sizeof(float),"Vec2SubtractBlockFromBlockAsm()",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2MultiplyBlockByBlockAsm(v2ar,v2aa,6),v2ar.m_Vec2Array[0],v2Results[62],
	     6*sizeof(float),"Vec2MultiplyBlockByBlockAsm()",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) v2ar[i] = v2Results[i];
  TestResult(Vec2DivideBlockByBlockAsm(v2ar,v2aa,6),v2ar.m_Vec2Array[0],v2Results[68],
	     6*sizeof(float),"Vec2DivideBlockByBlockAsm()",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) v2ar[i] = v2Results[i];

  v2buf v2b0(6,8,4,v2Results);
  v2buf v2b1(6,8,4,v2Results);
  v2buf v2br(6,8,4,v2Results);

  Vec2BufAddFloatToBlockAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),
			    (void*)(((char*)(vec2*)v2b0)+v2b0.offset()),
			    1.0,v2b0.size(),v2b0.length());
  v2array v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[74],
	     6*sizeof(float),"Vec2BufAddFloatToBlockAsm()",FCN_ERROR);
  Vec2BufAddFloatToBlockStd((void*)(((char*)(vec2*)v2br+v2br.offset())),
			    (void*)(((char*)(vec2*)v2b0)+v2b0.offset()),
			    1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[74],
	     6*sizeof(float),"Vec2BufAddFloatToBlockStd()",FCN_ERROR);

  Vec2BufSubFloatFromBlkSizeAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[80],
	     6*sizeof(float),"Vec2BufSubFloatFromBlkSizeAsm()",FCN_ERROR);
  Vec2BufSubFloatFromBlkSizeStd((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[80],
	     6*sizeof(float),"Vec2BufSubFloatFromBlkSizeStd()",FCN_ERROR);

  Vec2BufMulBlockByFloatSizeAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufMulBlockByFloatSizeAsm()",FCN_ERROR);
  Vec2BufMulBlockByFloatSizeStd((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufMulBlockByFloatSizeStd()",FCN_ERROR);

  Vec2BufDivBlockByFloatSizeAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufDivBlockByFloatSizeAsm()",FCN_ERROR);
  Vec2BufDivBlockByFloatSizeStd((void*)(((char*)(vec2*)v2br+v2br.offset())),
				(void*)(((char*)(vec2*)v2b0+v2b0.offset())),
				1.0,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufDivBlockByFloatSizeStd()",FCN_ERROR);

  Vec2BufNegateBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			      (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			      v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[92],
	     6*sizeof(float),"Vec2BufNegateBlockBySizeAsm()   ",FCN_ERROR);
  Vec2BufNegateBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			      (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			      v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[92],
	     6*sizeof(float),"Vec2BufNegateBlockBySizeStd()   ",FCN_ERROR);

  Vec2BufAddVec2ToBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
				 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
				 v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[86],
	     6*sizeof(float),"Vec2BufAddVec2ToBlockBySizeAsm()",FCN_ERROR);
  Vec2BufAddVec2ToBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
				 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
				 v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[86],
	     6*sizeof(float),"Vec2BufAddVec2ToBlockBySizeStd()",FCN_ERROR);

  Vec2BufSubVec2FromBlkBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
				 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
				 v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[98],
	     6*sizeof(float),"Vec2BufSubVec2ToBlockBySizeAsm()",FCN_ERROR);
  Vec2BufSubVec2FromBlkBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
				 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
				 v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[98],
	     6*sizeof(float),"Vec2BufSubVec2ToBlockBySizeStd()",FCN_ERROR);

  Vec2BufMulVec2ByBlockSizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			       (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			       v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[104],
	     6*sizeof(float),"Vec2BufMulVec2ByBlockSizeAsm()",FCN_ERROR);
  Vec2BufMulVec2ByBlockSizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			       (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			       v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[104],
	     6*sizeof(float),"Vec2BufMulVec2ByBlockSizeStd()",FCN_ERROR);

  Vec2BufDivVec2ByBlockSizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			       (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			       v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[110],
	     6*sizeof(float),"Vec2BufDivVec2ByBlockSizeAsm()",FCN_ERROR);
  Vec2BufDivVec2ByBlockSizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			       (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			       v2a,v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[110],
	     6*sizeof(float),"Vec2BufDivVec2ByBlockSizeStd()",FCN_ERROR);

  Vec2BufAddFloatToBufAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			  (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			  1.0,
			  v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[74],
	     6*sizeof(float),"Vec2BufAddFloatToBufAsm()",FCN_ERROR);
  Vec2BufAddFloatToBufStd((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			  (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			  1.0,
			  v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[74],
	     6*sizeof(float),"Vec2BufAddFloatToBufStd()",FCN_ERROR);


  Vec2BufSubFloatFromBufAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			    (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			    1.0,
			    v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[80],
	     6*sizeof(float),"Vec2BufSubFloatFromBufAsm()    ",FCN_ERROR);
  Vec2BufSubFloatFromBufStd((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			    (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			    1.0,
			    v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[80],
	     6*sizeof(float),"Vec2BufSubFloatFromBufStd()    ",FCN_ERROR);

  Vec2BufMulBlockByFloatBufAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			       (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			       1.0,
			       v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufMulBlockByFloatBufAsm() ",FCN_ERROR);
  Vec2BufMulBlockByFloatBufStd((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			       (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			       1.0,
			       v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufMulBlockByFloatBufStd() ",FCN_ERROR);

  Vec2BufDivBufByFloatAsm((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			  (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			  1.0,
			  v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufDivBufByFloatAsm()      ",FCN_ERROR);
  Vec2BufDivBufByFloatStd((void*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			  (void*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			  1.0,
			  v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[0],
	     6*sizeof(float),"Vec2BufDivBufByFloatStd()      ",FCN_ERROR);

  Vec2BufNegateBufBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			    (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			    v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[92],
	     6*sizeof(float),"Vec2BufNegateBufBySizeAsm()    ",FCN_ERROR);
  Vec2BufNegateBufBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			    (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			    v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[92],
	     6*sizeof(float),"Vec2BufNegateBufBySizeStd()    ",FCN_ERROR);

  Vec2BufAddBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[50],
	     6*sizeof(float),"Vec2BufAddBlockBySizeAsm()     ",FCN_ERROR);
  Vec2BufAddBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[50],
	     6*sizeof(float),"Vec2BufAddBlockBySizeStd()     ",FCN_ERROR);

  Vec2BufSubBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[56],
	     6*sizeof(float),"Vec2BufSubBlockBySizeAsm()     ",FCN_ERROR);
  Vec2BufSubBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[56],
	     6*sizeof(float),"Vec2BufSubBlockBySizeStd()     ",FCN_ERROR);

  Vec2BufMulBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[38],
	     6*sizeof(float),"Vec2BufMulBlockBySizeAsm()     ",FCN_ERROR);
  Vec2BufMulBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[38],
	     6*sizeof(float),"Vec2BufMulBlockBySizeStd()     ",FCN_ERROR);

  Vec2BufDivBlockBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[68],
	     6*sizeof(float),"Vec2BufDivBlockBySizeAsm()     ",FCN_ERROR);
  Vec2BufDivBlockBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),
			   (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),
			   (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),
			   v2b0.size(),v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[68],
	     6*sizeof(float),"Vec2BufDivBlockBySizeStd()     ",FCN_ERROR);

  Vec2BufAddBufBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[50],
	     6*sizeof(float),"Vec2BufAddBufBySizeAsm()       ",FCN_ERROR);
  Vec2BufAddBufBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[50],
	     6*sizeof(float),"Vec2BufAddBufBySizeStd()       ",FCN_ERROR);

  Vec2BufSubBufBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[56],
	     6*sizeof(float),"Vec2BufSubBufBySizeAsm()       ",FCN_ERROR);
  Vec2BufSubBufBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[56],
	     6*sizeof(float),"Vec2BufSubBufBySizeStd()       ",FCN_ERROR);

  Vec2BufMulBufBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),

			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[62],
	     6*sizeof(float),"Vec2BufMulBufBySizeAsm()       ",FCN_ERROR);
  Vec2BufMulBufBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[62],
	     6*sizeof(float),"Vec2BufMulBufBySizeStd()       ",FCN_ERROR);

  Vec2BufDivBufBySizeAsm((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[68],
	     6*sizeof(float),"Vec2BufDivBufBySizeAsm()       ",FCN_ERROR);
  Vec2BufDivBufBySizeStd((vec2*)(((char*)(vec2*)v2br+v2br.offset())),v2br.size(),
			 (vec2*)(((char*)(vec2*)v2b0+v2b0.offset())),v2b0.size(),
			 (vec2*)(((char*)(vec2*)v2b1+v2b1.offset())),v2b1.size(),
			 v2b0.length());
  v2ar0 = v2br;
  TestResult(v2ar0,v2ar0.m_Vec2Array[0],v2Results[68],
	     6*sizeof(float),"Vec2BufDivBufBySizeStd()       ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector3 Block Methods\n\n");

  char* pBaseBlock_0 = (char*)malloc(16*6+16);
  char* pBaseBlock_1 = (char*)malloc(16*6+16);
  char* pBaseBlock_r = (char*)malloc(16*6+16);

  vec3* pBlock_0 = (vec3*)(pBaseBlock_0 + ((unsigned int)pBaseBlock_0 % 16));
  vec3* pBlock_1 = (vec3*)(pBaseBlock_1 + ((unsigned int)pBaseBlock_1 % 16));
  vec3* pBlock_r = (vec3*)(pBaseBlock_r + ((unsigned int)pBaseBlock_r % 16));

  for( int i=0 ; i < 6 ; ++i )
    {
      pBlock_0[i] = v3Results[i];
      pBlock_1[i] = v3Results[i];
    }

  for( int i=0 ; i < 6 ; ++i ) pBlock_r[i] = pBlock_0[i];
  TestResult(Vec3AddFloatToBlockAsm(pBlock_r,1.0,6),pBlock_r[0],v3Results[19],
	     6*sizeof(vec3),"Vec3AddFloatToBlockAsm()",FCN_ERROR);
  TestResult(Vec3SubtractFloatFromBlockAsm(pBlock_r,1.0,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubtractFloatFromBlockAsm()",FCN_ERROR);
  TestResult(Vec3AddFloatToBlockStd(pBlock_r,1.0,6),pBlock_r[0],v3Results[19],
	     6*sizeof(vec3),"Vec3AddFloatToBlockStd()",FCN_ERROR);
  TestResult(Vec3SubtractFloatFromBlockStd(pBlock_r,1.0,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubtractFloatFromBlockStd()",FCN_ERROR);
  TestResult(Vec3MultiplyFloatToBlockAsm(pBlock_r,2.0,6),pBlock_r[0],v3Results[25],
	     6*sizeof(vec3),"Vec3MultiplyFloatToBlockAsm()  ",FCN_ERROR);
  TestResult(Vec3DivideBlockByFloatAsm(pBlock_r,2.0,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivideFloatByBlockAsm()    ",FCN_ERROR);
  TestResult(Vec3MultiplyFloatToBlockStd(pBlock_r,2.0,6),pBlock_r[0],v3Results[25],
	     6*sizeof(vec3),"Vec3MultiplyFloatToBlockStd()  ",FCN_ERROR);
  TestResult(Vec3DivideBlockByFloatStd(pBlock_r,2.0,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivideFloatByBlockStd()    ",FCN_ERROR);
  TestResult(Vec3NegateBlockAsm(pBlock_0,3),pBlock_0[0],v3Results[16],
	     3*sizeof(vec3),"Vec3NegateBlockAsm()           ",FCN_ERROR);
  TestResult(Vec3NegateBlockStd(pBlock_0,3),pBlock_0[0],v3Results[0],
	     3*sizeof(vec3),"Vec3NegateBlockStd()           ",FCN_ERROR);
  TestResult(Vec3AddVecToBlockAsm(pBlock_0,v3a,6),pBlock_0[0],v3Results[31],
	     6*sizeof(vec3),"Vec3AddVecToBlockAsm()         ",FCN_ERROR);
  TestResult(Vec3SubVecFromBlockAsm(pBlock_0,v3a,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubVecFromBlockAsm()       ",FCN_ERROR);
  TestResult(Vec3AddVecToBlockStd(pBlock_0,v3a,6),pBlock_0[0],v3Results[31],
	     6*sizeof(vec3),"Vec3AddVecToBlockStd()         ",FCN_ERROR);
  TestResult(Vec3SubVecFromBlockStd(pBlock_0,v3a,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubVecFromBlockStd()       ",FCN_ERROR);
  TestResult(Vec3MulBlockByVecAsm(pBlock_0,v3a,6),pBlock_0[0],v3Results[37],
	     6*sizeof(vec3),"Vec3MulBlockByVecAsm()         ",FCN_ERROR);
  TestResult(Vec3DivBlockByVecAsm(pBlock_0,v3a,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivBlockByVecAsm()         ",FCN_ERROR);
  TestResult(Vec3MulBlockByVecStd(pBlock_0,v3a,6),pBlock_0[0],v3Results[37],
	     6*sizeof(vec3),"Vec3MulBlockByVecStd()         ",FCN_ERROR);
  TestResult(Vec3DivBlockByVecStd(pBlock_0,v3a,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivBlockByVecStd()         ",FCN_ERROR);
  TestResult(Vec3LerpBlockAsm(pBlock_r,pBlock_0,0.5,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3LerpBlockAsm()             ",FCN_ERROR);
  TestResult(Vec3LerpBlockStd(pBlock_r,pBlock_0,0.5,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3LerpBlockStd()             ",FCN_ERROR);
  TestResult(Vec3SqrBlockAsm(pBlock_r,6),pBlock_r[0],v3Results[43],
	     6*sizeof(vec3),"Vec3SqrBlockAsm()              ",FCN_ERROR);
  TestResult(Vec3SqrtBlockAsm(pBlock_r,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SqrtBlockAsm()             ",FCN_ERROR);
  TestResult(Vec3SqrBlockStd(pBlock_r,6),pBlock_r[0],v3Results[43],
	     6*sizeof(vec3),"Vec3SqrBlockStd()              ",FCN_ERROR);
  TestResult(Vec3SqrtBlockStd(pBlock_r,6),pBlock_r[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SqrtBlockStd()             ",FCN_ERROR);
  TestResult(Vec3AddBlockToBlockAsm(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[25],
	     6*sizeof(vec3),"Vec3AddBlockToBlockAsm()        ",FCN_ERROR);
  TestResult(Vec3SubBlockFromBlockAsm(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubBlockFromBlockAsm()      ",FCN_ERROR);
  TestResult(Vec3AddBlockToBlockStd(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[25],
	     6*sizeof(vec3),"Vec3AddBlockToBlockStd()        ",FCN_ERROR);
  TestResult(Vec3SubBlockFromBlockStd(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3SubBlockFromBlockStd()      ",FCN_ERROR);
  TestResult(Vec3MulBlockByBlockAsm(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[43],
	     6*sizeof(vec3),"Vec3MulBlockByBlockAsm()        ",FCN_ERROR);
  TestResult(Vec3DivBlockByBlockAsm(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivBlockByBlockAsm()        ",FCN_ERROR);
  TestResult(Vec3MulBlockByBlockStd(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[43],
	     6*sizeof(vec3),"Vec3MulBlockByBlockStd()        ",FCN_ERROR);
  TestResult(Vec3DivBlockByBlockStd(pBlock_0,pBlock_1,6),pBlock_0[0],v3Results[0],
	     6*sizeof(vec3),"Vec3DivBlockByBlockStd()        ",FCN_ERROR);

  TestResult(Vec3NormalizeBlockStd(pBlock_r,6),pBlock_r[0],v3Results[55],
	     6*sizeof(vec3),"Vec3NormalizeBlockAsm()        ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pBlock_r[i] = pBlock_0[i];

  TestResult(Vec3CrossBlockAsm(pBlock_r,pBlock_0,6),pBlock_r[0],v3Results[49],
	     6*sizeof(vec3),"Vec3CrossBlockAsm()            ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pBlock_r[i] = pBlock_0[i];
  TestResult(Vec3CrossBlockStd(pBlock_r,pBlock_0,6),pBlock_r[0],v3Results[49],
	     6*sizeof(vec3),"Vec3CrossBlockStd()            ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pBlock_r[i] = pBlock_0[i];

  float fBase[6];

  TestResult(Vec3DotBlockAsm(fBase,pBlock_0,pBlock_1,6),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3DotBlockAsm                ",FCN_ERROR);
  TestResult(Vec3DotBlockStd(fBase,pBlock_0,pBlock_1,6),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3DotBlockStd                ",FCN_ERROR);
  TestResult(Vec3LengthBlockStd(fBase,pBlock_0,6),fBase[0],FloatList[22],
	     6*sizeof(float),"Vec3LengthBlockStd()           ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector3 Sized Block Methods (v3array:aligned)\n\n");

  v3array v3aa(6,v3Results);
  v3array v3ar(6,v3Results);

  TestResult(Vec3AddFloatToBlockBySizeAsm(v3ar,1.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3AddFloatToBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec3SubFloatFromBlockBySizeAsm(v3ar,1.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubFloatFromBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec3AddFloatToBlockBySizeStd(v3ar,1.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3AddFloatToBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec3SubFloatFromBlockBySizeStd(v3ar,1.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubFloatFromBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec3MulFloatToBlockBySizeAsm(v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3MulFloatToBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec3DivBlockByFloatBySizeAsm(v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByFloatBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec3MulFloatToBlockBySizeStd(v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3MulFloatToBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec3DivBlockByFloatBySizeStd(v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByFloatBySizeStd()  ",FCN_ERROR);
  TestResult(Vec3BufAddFloatToBlockAsm(v3ar,v3aa,1.0,v3aa.size(),v3aa.length()),*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec3BufSubFloatFromBlockAsm(v3ar,v3aa,0.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubFloatFromBlockAsm()   ",FCN_ERROR);
  TestResult(Vec3BufAddFloatToBlockStd(v3ar,v3aa,1.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec3BufSubFloatFromBlockStd(v3ar,v3aa,0.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubFloatFromBlockAsm()   ",FCN_ERROR);
  TestResult(Vec3BufMulFloatToBlockAsm(v3ar,v3aa,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec3BufDivBlockByFloatAsm(v3ar,v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec3BufMulFloatToBlockStd(v3ar,v3aa,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec3BufDivBlockByFloatStd(v3ar,v3ar,2.0,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec3NegateBlockBySizeAsm(v3ar,v3ar.size(),3),*((vec3*)v3ar.m_VecArray),v3Results[16],
	     3*sizeof(vec3),"Vec3NegateBlockBySizeAsm()      ",FCN_ERROR);
  TestResult(Vec3NegateBlockBySizeStd(v3ar,v3ar.size(),3),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     3*sizeof(vec3),"Vec3NegateBlockBySizeStd()      ",FCN_ERROR);
  TestResult(Vec3BufNegateBlockAsm(v3ar,v3aa,v3aa.size(),3),*((vec3*)v3ar.m_VecArray),v3Results[16],
	     3*sizeof(vec3),"Vec3NegateBlockBySizeAsm()      ",FCN_ERROR);
  TestResult(Vec3BufNegateBlockStd(v3ar,v3ar,v3ar.size(),3),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     3*sizeof(vec3),"Vec3NegateBlockBySizeStd()      ",FCN_ERROR);
  TestResult(Vec3AddVecToBlockBySizeAsm(v3ar,v3a,v3ar.size(),6),*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3AddVecToBlockBySizeAsm()    ",FCN_ERROR);
  TestResult(Vec3SubVecFromBlockBySizeAsm(v3ar,v3a,v3ar.size(),6),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubVecFromBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec3AddVecToBlockBySizeStd(v3ar,v3a,v3ar.size(),6),*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3AddVecToBlockBySizeStd()    ",FCN_ERROR);
  TestResult(Vec3SubVecFromBlockBySizeStd(v3ar,v3a,v3ar.size(),6),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubVecFromBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec3MulBlockByVecUseSizeAsm(v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3MulBlockByVecUseSizeAsm()   ",FCN_ERROR);
  TestResult(Vec3DivBlockByVecUseSizeAsm(v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByVecUseSizeAsm()   ",FCN_ERROR);
  TestResult(Vec3MulBlockByVecUseSizeStd(v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3MulBlockByVecUseSizeStd()   ",FCN_ERROR);
  TestResult(Vec3DivBlockByVecUseSizeStd(v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByVecUseSizeStd()   ",FCN_ERROR);
  TestResult(Vec3AddBlockToBlockBySizeAsm(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3AddBlockToBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec3SubBlockFromBlockBySizeAsm(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubBlockFromBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec3AddBlockToBlockBySizeStd(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3AddBlockToBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec3SubBlockFromBlockBySizeStd(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SubBlockFromBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec3MulBlockByBlockUseSizeAsm(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3MulBlockByBlockUseSizeAsm() ",FCN_ERROR);
  TestResult(Vec3DivBlockByBlockUseSizeAsm(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByBlockUseSizeAsm() ",FCN_ERROR);
  TestResult(Vec3MulBlockByBlockUseSizeStd(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3MulBlockByBlockUseSizeStd() ",FCN_ERROR);
  TestResult(Vec3DivBlockByBlockUseSizeStd(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3DivBlockByBlockUseSizeStd() ",FCN_ERROR);
  TestResult(Vec3BufAddVecToBlockAsm(v3ar,v3aa,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddVecToBlockAsm()       ",FCN_ERROR);



  TestResult(Vec3BufSubVecFromBlockAsm(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubVecFromBlockAsm()     ",FCN_ERROR);
  TestResult(Vec3BufAddVecToBlockStd(v3ar,v3aa,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddVecToBlockStd()       ",FCN_ERROR);
  TestResult(Vec3BufSubVecFromBlockStd(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubVecFromBlockStd()     ",FCN_ERROR);
  TestResult(Vec3BufMulBufByVecAsm(v3ar,v3aa,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByVecAsm()         ",FCN_ERROR);
  TestResult(Vec3BufDivBufByVecAsm(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecAsm()         ",FCN_ERROR);
  TestResult(Vec3BufMulBufByVecStd(v3ar,v3aa,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByVecStd()         ",FCN_ERROR);
  TestResult(Vec3BufDivBufByVecStd(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecStd()         ",FCN_ERROR);
  TestResult(Vec3SqrBlockUseSizeAsm(v3ar,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3SqrBlockUseSizeAsm()        ",FCN_ERROR);
  TestResult(Vec3SqrtBlockUseSizeAsm(v3ar,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SqrtBlockUseSizeAsm()       ",FCN_ERROR);
  TestResult(Vec3SqrBlockUseSizeStd(v3ar,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3SqrBlockUseSizeStd()        ",FCN_ERROR);
  TestResult(Vec3SqrtBlockUseSizeStd(v3ar,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3SqrtBlockUseSizeStd()       ",FCN_ERROR);
  TestResult(Vec3LerpBlockUseSizeAsm(v3ar,v3aa,0.5,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3LerpBlockUseSizeAsm()       ",FCN_ERROR);
  TestResult(Vec3LerpBlockUseSizeStd(v3ar,v3aa,0.5,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3LerpBlockUseSizeStd()       ",FCN_ERROR);

  Vec3MulBlockByVecUseSizeAsm(v3ar,v3a,v3ar.size(),v3ar.length());
  TestResult(Vec3BufDivBufByVecAsm(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecAsm()         ",FCN_ERROR);
  Vec3MulBlockByVecUseSizeStd(v3ar,v3a,v3ar.size(),v3ar.length());
  TestResult(Vec3BufDivBufByVecStd(v3ar,v3ar,v3a,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecAsm()         ",FCN_ERROR);

  TestResult(Vec3BufLerpBlockAsm(v3ar,v3ar.size(),v3ar,v3ar.size(),pBlock_r,0.5,6),*((vec3*)v3ar.m_VecArray),v3Results[61],
	     6*sizeof(vec3),            "Vec3BufLerpBlockAsm()           ",FCN_ERROR);
  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];
  TestResult(Vec3BufLerpBlockStd(v3ar,v3ar.size(),v3ar,v3ar.size(),pBlock_r,0.5,6),*((vec3*)v3ar.m_VecArray),v3Results[61],
	     6*sizeof(vec3),            "Vec3BufLerpBlockStd()           ",FCN_ERROR);
  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];

  TestResult(Vec3CrossBlockUseSizeAsm(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[49],
	     v3ar.length()*sizeof(vec3),"Vec3CrossBlockUseSizeAsm()      ",FCN_ERROR);
  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];
  TestResult(Vec3CrossBlockUseSizeStd(v3ar,v3aa,v3ar.size(),v3ar.length()),*((vec3*)v3ar.m_VecArray),v3Results[49],
	     v3ar.length()*sizeof(vec3),"Vec3CrossBlockUseSizeStd()      ",FCN_ERROR);
  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];

  TestResult(Vec3NormalizeBlockUseSizeStd(v3ar,v3ar.size(),6),*((vec3*)v3ar.m_VecArray),v3Results[55],
	     6*sizeof(vec3),"Vec3NormalizeBlockUseSizeStd() ",FCN_ERROR);
  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];

  TestResult(Vec3DotBlockUseSizeAsm(fBase,v3ar,v3aa,v3ar.size(),v3ar.length()),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3DotBlockUseSizeAsm()       ",FCN_ERROR);
  TestResult(Vec3DotBlockUseSizeStd(fBase,v3ar,v3aa,v3ar.size(),v3ar.length()),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3DotBlockUseSizeStd()       ",FCN_ERROR);

  TestResult(Vec3LengthBlockUseSizeStd(fBase,v3ar,v3ar.size(),v3ar.length()),fBase[0],FloatList[22],
	     6*sizeof(float),"Vec3LengthBlockUstSizeStd()    ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector3 Buffer Methods (v3buf:aligned)\n\n");

  v3buf v3ba(6,32,16,v3Results);
  v3buf v3br(6,32,16,v3Results);

  Vec3BufAddFloatToBufAsm(v3br,v3br.size(),v3ba,v3ba.size(),1.0,v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddFloatToBufAsm()       ",FCN_ERROR);
  Vec3BufSubFloatFromBufAsm(v3br,v3br.size(),v3br,v3br.size(),1.0,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubFloatFromBufAsm()     ",FCN_ERROR);
  Vec3BufAddFloatToBufStd(v3br,v3br.size(),v3ba,v3ba.size(),1.0,v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[19],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddFloatToBufStd()       ",FCN_ERROR);
  Vec3BufSubFloatFromBufStd(v3br,v3br.size(),v3br,v3br.size(),1.0,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubFloatFromBufStd()     ",FCN_ERROR);
  Vec3BufMulFloatToBufAsm(v3br,v3br.size(),v3ba,v3ba.size(),2.0,v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulFloatToBufAsm()       ",FCN_ERROR);
  Vec3BufDivBufByFloatAsm(v3br,v3br.size(),v3br,v3br.size(),2.0,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByFloatAsm()       ",FCN_ERROR);
  Vec3BufMulFloatToBufStd(v3br,v3br.size(),v3ba,v3ba.size(),2.0,v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulFloatToBufStd()       ",FCN_ERROR);
  Vec3BufDivBufByFloatStd(v3br,v3br.size(),v3br,v3br.size(),2.0,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByFloatStd()       ",FCN_ERROR);

  Vec3BufNegateBufAsm(v3br,v3br.size(),v3ba,v3ba.size(),3);
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[16],
	     3*sizeof(vec3),"Vec3BufNegateBufAsm()           ",FCN_ERROR);
  Vec3BufNegateBufStd(v3br,v3br.size(),v3br,v3br.size(),3);
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     3*sizeof(vec3),"Vec3BufNegateBufStd()           ",FCN_ERROR);

  Vec3BufAddVecToBufAsm(v3br,v3br.size(),v3ba,v3ba.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddVecToBufAsm()         ",FCN_ERROR);
  Vec3BufSubVecFromBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubVecFromBufAsm()       ",FCN_ERROR);
  Vec3BufAddVecToBufStd(v3br,v3br.size(),v3ba,v3ba.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[31],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddVecToBufStd()         ",FCN_ERROR);
  Vec3BufSubVecFromBufStd(v3br,v3br.size(),v3br,v3br.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubVecFromBufStd()       ",FCN_ERROR);

  Vec3BufMulBufByVecUseSizeAsm(v3br,v3br.size(),v3ba,v3ba.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByVecUseSizeAsm()  ",FCN_ERROR);
  Vec3BufDivBufByVecUseSizeAsm(v3br,v3br.size(),v3br,v3br.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecUseSizeAsm()  ",FCN_ERROR);
  Vec3BufMulBufByVecUseSizeStd(v3br,v3br.size(),v3ba,v3ba.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[37],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByVecUseSizeStd()  ",FCN_ERROR);
  Vec3BufDivBufByVecUseSizeStd(v3br,v3br.size(),v3br,v3br.size(),v3a,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByVecUseSizeStd()  ",FCN_ERROR);

  Vec3BufAddBlockToBufAsm(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddBlockToBufAsm()       ",FCN_ERROR);
  Vec3BufSubBlockFromBufAsm(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubBlockFromBufAsm()     ",FCN_ERROR);
  Vec3BufAddBlockToBufStd(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddBlockToBufStd()       ",FCN_ERROR);
  Vec3BufSubBlockFromBufStd(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubBlockFromBufStd()     ",FCN_ERROR);

  Vec3BufMulBufByBlockAsm(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByBlockAsm()       ",FCN_ERROR);
  Vec3BufDivBufByBlockAsm(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByBlockAsm()       ",FCN_ERROR);
  Vec3BufMulBufByBlockStd(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByBlockStd()       ",FCN_ERROR);
  Vec3BufDivBufByBlockStd(v3br,v3br,v3ba,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByBlockStd()       ",FCN_ERROR);

  Vec3BufAddBufToBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddBufToBufAsm()         ",FCN_ERROR);
  Vec3BufSubBufFromBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubBufFromBufAsm()       ",FCN_ERROR);
  Vec3BufAddBufToBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[25],
	     v3ar.length()*sizeof(vec3),"Vec3BufAddBufToBufStd()         ",FCN_ERROR);
  Vec3BufSubBufFromBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSubBufFromBufStd()       ",FCN_ERROR);

  Vec3BufMulBufByBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByBufAsm()         ",FCN_ERROR);
  Vec3BufDivBufByBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByBufAsm()         ",FCN_ERROR);
  Vec3BufMulBufByBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufMulBufByBufStd()         ",FCN_ERROR);
  Vec3BufDivBufByBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufDivBufByBufStd()         ",FCN_ERROR);

  Vec3BufSqrBufAsm(v3br,v3br.size(),v3ba,v3ba.size(),v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufSqrBufAsm()              ",FCN_ERROR);
  Vec3BufSqrtBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSqrtBufAsm()             ",FCN_ERROR);
  Vec3BufSqrBufStd(v3br,v3br.size(),v3ba,v3ba.size(),v3ba.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[43],
	     v3ar.length()*sizeof(vec3),"Vec3BufSqrBufStd()              ",FCN_ERROR);
  Vec3BufSqrtBufStd(v3br,v3br.size(),v3br,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufSqrtBufStd()             ",FCN_ERROR);

  Vec3BufCrossBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[49],
	     v3ar.length()*sizeof(vec3),"Vec3BufCrossBufAsm()            ",FCN_ERROR);
  for( int i=0 ; i < v3br.length() ; ++i ) v3br[i] = v3ba[i];
  Vec3BufCrossBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[49],
	     v3ar.length()*sizeof(vec3),"Vec3BufCrossBufStd()            ",FCN_ERROR);
  for( int i=0 ; i < v3br.length() ; ++i ) v3br[i] = v3ba[i];

  Vec3BufLerpBufAsm(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),0.5,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufLerpBufAsm()             ",FCN_ERROR);
  Vec3BufLerpBufStd(v3br,v3br.size(),v3br,v3br.size(),v3ba,v3ba.size(),0.5,v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[0],
	     v3ar.length()*sizeof(vec3),"Vec3BufLerpBufStd()             ",FCN_ERROR);

  Vec3BufNormalizeBufStd(v3br,v3br.size(),v3br,v3br.size(),v3br.length());
  TestResult(v3ar=v3br,*((vec3*)v3ar.m_VecArray),v3Results[67],
	     v3ar.length()*sizeof(vec3),"Vec3BufNormalizeBufStd()        ",FCN_ERROR);
  for( int i=0 ; i < v3br.length() ; ++i ) v3br[i] = v3ba[i];

  TestResult(Vec3BufDotBufAsm((void*)fBase,sizeof(float),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length()),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3BufDotBufAsm()              ",FCN_ERROR);
  TestResult(Vec3BufDotBufStd((void*)fBase,sizeof(float),v3br,v3br.size(),v3ba,v3ba.size(),v3br.length()),fBase[0],FloatList[16],
	     6*sizeof(float),"Vec3BufDotBufStd()              ",FCN_ERROR);

  TestResult(Vec3BufLengthBufStd((void*)fBase,sizeof(float),v3br,v3br.size(),v3br.length()),fBase[0],FloatList[22],
	     v3ar.length()*sizeof(float),"Vec3BufLengthBufStd()           ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector3 Logical Methods (aligned)\n\n");

  int32_t iFlag;
  int32_t iTrue = 1;
  int32_t iFalse = 0;

  for( int i=0 ; i < v3ar.length() ; ++i ) v3ar[i] = v3aa[i];
  TestResult(Vec3EqualsAsm(&iFlag,v3ar,v3aa),iFlag,iTrue,
	     sizeof(int32_t),"Vec3EqualsAsm()                 ",FCN_ERROR);
  TestResult(Vec3NotEqualsAsm(&iFlag,v3ar,v3aa),iFlag,iFalse,
	     sizeof(int32_t),"Vec3NotEqualsAsm()              ",FCN_ERROR);
  TestResult(Vec3EqualsStd(&iFlag,v3ar,v3aa),iFlag,iTrue,
	     sizeof(int32_t),"Vec3EqualsStd()                 ",FCN_ERROR);
  TestResult(Vec3NotEqualsStd(&iFlag,v3ar,v3aa),iFlag,iFalse,
	     sizeof(int32_t),"Vec3NotEqualsStd()              ",FCN_ERROR);

#if 0
  extern __C void Vec3ReflectAsm (vec3* r,const vec3* u,const vec3* v);
#endif
 
  fprintf(stdout,"\n-------------> Vector4 Block Methods\n\n");

  vec4* pVec4_0 = (vec4*)pBlock_0;
  vec4* pVec4_1 = (vec4*)pBlock_1;
  vec4* pVec4_r = (vec4*)pBlock_r;

  for( int i=0 ; i < 6 ; ++i )
    {
      pVec4_0[i] = v4Results[i];
      pVec4_1[i] = v4Results[i];
      pVec4_r[i] = v4Results[i];
    }

  TestResult(Vec4AddFloatToBlockAsm(pVec4_r,1.0,6),pVec4_r[0],v4Results[16],
	     6*sizeof(vec4),"Vec4AddFloatToBlockAsm()",FCN_ERROR);
  TestResult(Vec4SubtractFloatFromBlockAsm(pVec4_r,1.0,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubtractFloatFromBlockAsm()",FCN_ERROR);
  TestResult(Vec4AddFloatToBlockStd(pVec4_r,1.0,6),pVec4_r[0],v4Results[16],
	     6*sizeof(vec4),"Vec4AddFloatToBlockStd()",FCN_ERROR);
  TestResult(Vec4SubtractFloatFromBlockStd(pVec4_r,1.0,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubtractFloatFromBlockStd()",FCN_ERROR);
  TestResult(Vec4MultiplyFloatToBlockAsm(pVec4_r,2.0,6),pVec4_r[0],v4Results[22],
	     6*sizeof(vec4),"Vec4MultiplyFloatToBlockAsm()  ",FCN_ERROR);
  TestResult(Vec4DivideBlockByFloatAsm(pVec4_r,2.0,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivideFloatByBlockAsm()    ",FCN_ERROR);
  TestResult(Vec4MultiplyFloatToBlockStd(pVec4_r,2.0,6),pVec4_r[0],v4Results[22],
	     6*sizeof(vec4),"Vec4MultiplyFloatToBlockStd()  ",FCN_ERROR);
  TestResult(Vec4DivideBlockByFloatStd(pVec4_r,2.0,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivideFloatByBlockStd()    ",FCN_ERROR);
  TestResult(Vec4NegateBlockAsm(pVec4_r,6),pVec4_r[0],v4Results[28],
	     6*sizeof(vec4),"Vec4NegateBlockAsm()           ",FCN_ERROR);
  TestResult(Vec4NegateBlockStd(pVec4_r,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4NegateBlockStd()           ",FCN_ERROR);
  TestResult(Vec4AddVecToBlockAsm(pVec4_r,v4a,6),pVec4_r[0],v4Results[34],
	     6*sizeof(vec4),"Vec4AddVecToBlockAsm()         ",FCN_ERROR);
  TestResult(Vec4SubVecFromBlockAsm(pVec4_r,v4a,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubVecFromBlockAsm()       ",FCN_ERROR);
  TestResult(Vec4AddVecToBlockStd(pVec4_r,v4a,6),pVec4_r[0],v4Results[34],
	     6*sizeof(vec4),"Vec4AddVecToBlockStd()         ",FCN_ERROR);
  TestResult(Vec4SubVecFromBlockStd(pVec4_r,v4a,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubVecFromBlockStd()       ",FCN_ERROR);
  TestResult(Vec4MulBlockByVecAsm(pVec4_r,v4a,6),pVec4_r[0],v4Results[40],
	     6*sizeof(vec4),"Vec4MulBlockByVecAsm()         ",FCN_ERROR);
  TestResult(Vec4DivBlockByVecAsm(pVec4_r,v4a,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivBlockByVecAsm()         ",FCN_ERROR);
  TestResult(Vec4MulBlockByVecStd(pVec4_r,v4a,6),pVec4_r[0],v4Results[40],
	     6*sizeof(vec4),"Vec4MulBlockByVecStd()         ",FCN_ERROR);
  TestResult(Vec4DivBlockByVecStd(pVec4_r,v4a,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivBlockByVecStd()         ",FCN_ERROR);

  TestResult(Vec4LerpBlockAsm(pVec4_r,pVec4_r,0.5,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4LerpBlockAsm()             ",FCN_ERROR);
  TestResult(Vec4LerpBlockStd(pVec4_r,pVec4_r,0.5,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4LerpBlockStd()             ",FCN_ERROR);
  TestResult(Vec4SqrBlockAsm(pVec4_r,6),pVec4_r[0],v4Results[46],
	     6*sizeof(vec4),"Vec4SqrBlockAsm()              ",FCN_ERROR);
  TestResult(Vec4SqrtBlockAsm(pVec4_r,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SqrtBlockAsm()             ",FCN_ERROR);
  TestResult(Vec4SqrBlockStd(pVec4_r,6),pVec4_r[0],v4Results[46],
	     6*sizeof(vec4),"Vec4SqrBlockStd()              ",FCN_ERROR);
  TestResult(Vec4SqrtBlockStd(pVec4_r,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SqrtBlockStd()             ",FCN_ERROR);
  TestResult(Vec4AddBlockToBlockAsm(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[22],
	     6*sizeof(vec4),"Vec4AddBlockToBlockAsm()        ",FCN_ERROR);
  TestResult(Vec4SubBlockFromBlockAsm(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubBlockFromBlockAsm()      ",FCN_ERROR);
  TestResult(Vec4AddBlockToBlockStd(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[22],
	     6*sizeof(vec4),"Vec4AddBlockToBlockStd()        ",FCN_ERROR);
  TestResult(Vec4SubBlockFromBlockStd(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4SubBlockFromBlockStd()      ",FCN_ERROR);
  TestResult(Vec4MulBlockByBlockAsm(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[46],
	     6*sizeof(vec4),"Vec4MulBlockByBlockAsm()        ",FCN_ERROR);
  TestResult(Vec4DivBlockByBlockAsm(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivBlockByBlockAsm()        ",FCN_ERROR);
  TestResult(Vec4MulBlockByBlockStd(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[46],
	     6*sizeof(vec4),"Vec4MulBlockByBlockStd()        ",FCN_ERROR);
  TestResult(Vec4DivBlockByBlockStd(pVec4_r,pVec4_1,6),pVec4_r[0],v4Results[0],
	     6*sizeof(vec4),"Vec4DivBlockByBlockStd()        ",FCN_ERROR);

  TestResult(Vec4NormalizeBlockStd(pVec4_r,6),pVec4_r[0],v4Results[52],
	     6*sizeof(vec4),"Vec4NormalizeBlockStd()        ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pVec4_r[i] = pVec4_0[i];

  TestResult(Vec4CrossBlockAsm(pVec4_r,pVec4_0,6),pVec4_r[0],v4Results[58],
	     6*sizeof(vec4),"Vec4CrossBlockAsm()            ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pVec4_r[i] = pVec4_0[i];
  TestResult(Vec4CrossBlockStd(pVec4_r,pVec4_0,6),pVec4_r[0],v4Results[58],
	     6*sizeof(vec4),"Vec4CrossBlockStd()            ",FCN_ERROR);
  for( int i=0 ; i < 6 ; ++i ) pVec4_r[i] = pVec4_0[i];

  TestResult(Vec4DotBlockStd(fBase,pVec4_0,pVec4_1,6),fBase[0],FloatList[28],
	     6*sizeof(float),"Vec4DotBlockAsm                ",FCN_ERROR);

  TestResult(Vec4LengthBlockStd(fBase,pVec4_0,6),fBase[0],FloatList[34],
	     6*sizeof(float),"Vec4LengthBlockStd()           ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector4 Sized Block Methods (v3array:aligned)\n\n");

  v4array v4aa(6,v4Results);
  v4array v4ar(6,v4Results);

  TestResult(Vec4AddFloatToBlockBySizeAsm(v4ar,1.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4AddFloatToBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec4SubFloatFromBlockBySizeAsm(v4ar,1.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v3ar.length()*sizeof(vec4),"Vec4SubFloatFromBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec4AddFloatToBlockBySizeStd(v4ar,1.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4AddFloatToBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec4SubFloatFromBlockBySizeStd(v4ar,1.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v3ar.length()*sizeof(vec4),"Vec4SubFloatFromBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec4MulFloatToBlockBySizeAsm(v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4MulFloatToBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec4DivBlockByFloatBySizeAsm(v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByFloatBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec4MulFloatToBlockBySizeStd(v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4MulFloatToBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec4DivBlockByFloatBySizeStd(v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByFloatBySizeStd()  ",FCN_ERROR);
  TestResult(Vec4BufAddFloatToBlockAsm(v4ar,v4aa,1.0,v4aa.size(),v4aa.length()),*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec4BufSubFloatFromBlockAsm(v4ar,v4aa,0.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubFloatFromBlockAsm()   ",FCN_ERROR);
  TestResult(Vec4BufAddFloatToBlockStd(v4ar,v4aa,1.0,v4aa.size(),v4aa.length()),*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec4BufSubFloatFromBlockStd(v4ar,v4aa,0.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubFloatFromBlockStd()   ",FCN_ERROR);
  TestResult(Vec4BufMulFloatToBlockAsm(v4ar,v4aa,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec4BufDivBlockByFloatAsm(v4ar,v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivFloatToBlockAsm()     ",FCN_ERROR);
  TestResult(Vec4BufMulFloatToBlockStd(v4ar,v4aa,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec4BufDivBlockByFloatStd(v4ar,v4ar,2.0,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivFloatToBlockStd()     ",FCN_ERROR);
  TestResult(Vec4NegateBlockBySizeAsm(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[28],
	     v4ar.length()*sizeof(vec4),"Vec4NegateBlockBySizeAsm()      ",FCN_ERROR);
  TestResult(Vec4NegateBlockBySizeStd(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4NegateBlockBySizeStd()      ",FCN_ERROR);
  TestResult(Vec4BufNegateBlockAsm(v4ar,v4aa,v4aa.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[28],
	     v4ar.length()*sizeof(vec4),"Vec4NegateBlockBySizeAsm()      ",FCN_ERROR);
  TestResult(Vec4BufNegateBlockStd(v4ar,v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4NegateBlockBySizeStd()      ",FCN_ERROR);
  TestResult(Vec4AddVecToBlockBySizeAsm(v4ar,v4a,v4ar.size(),6),*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4AddVecToBlockBySizeAsm()    ",FCN_ERROR);
  TestResult(Vec4SubVecFromBlockBySizeAsm(v4ar,v4a,v4ar.size(),6),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SubVecFromBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec4AddVecToBlockBySizeStd(v4ar,v4a,v4ar.size(),6),*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4AddVecToBlockBySizeStd()    ",FCN_ERROR);
  TestResult(Vec4SubVecFromBlockBySizeStd(v4ar,v4a,v4ar.size(),6),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SubVecFromBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec4MulBlockByVecUseSizeAsm(v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4ar.length()*sizeof(vec4),"Vec4MulBlockByVecUseSizeAsm()   ",FCN_ERROR);
  TestResult(Vec4DivBlockByVecUseSizeAsm(v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByVecUseSizeAsm()   ",FCN_ERROR);
  TestResult(Vec4MulBlockByVecUseSizeStd(v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4ar.length()*sizeof(vec4),"Vec4MulBlockByVecUseSizeStd()   ",FCN_ERROR);
  TestResult(Vec4DivBlockByVecUseSizeStd(v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByVecUseSizeStd()   ",FCN_ERROR);
  TestResult(Vec4AddBlockToBlockBySizeAsm(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4AddBlockToBlockBySizeAsm()  ",FCN_ERROR);
  TestResult(Vec4SubBlockFromBlockBySizeAsm(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SubBlockFromBlockBySizeAsm()",FCN_ERROR);
  TestResult(Vec4AddBlockToBlockBySizeStd(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4AddBlockToBlockBySizeStd()  ",FCN_ERROR);
  TestResult(Vec4SubBlockFromBlockBySizeStd(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SubBlockFromBlockBySizeStd()",FCN_ERROR);
  TestResult(Vec4MulBlockByBlockUseSizeAsm(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4MulBlockByBlockUseSizeAsm() ",FCN_ERROR);
  TestResult(Vec4DivBlockByBlockUseSizeAsm(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByBlockUseSizeAsm() ",FCN_ERROR);
  TestResult(Vec4MulBlockByBlockUseSizeStd(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4MulBlockByBlockUseSizeStd() ",FCN_ERROR);
  TestResult(Vec4DivBlockByBlockUseSizeStd(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4DivBlockByBlockUseSizeStd() ",FCN_ERROR);
  TestResult(Vec4BufAddVecToBlockAsm(v4ar,v4aa,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddVecToBlockAsm()       ",FCN_ERROR);
  TestResult(Vec4BufSubVecFromBlockAsm(v4ar,v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubVecFromBlockAsm()     ",FCN_ERROR);
  TestResult(Vec4BufAddVecToBlockStd(v4ar,v4aa,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddVecToBlockStd()       ",FCN_ERROR);
  TestResult(Vec4BufSubVecFromBlockStd(v4ar,v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubVecFromBlockStd()     ",FCN_ERROR);
  TestResult(Vec4BufMulBufByVecAsm(v4ar,v4aa,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByVecAsm()         ",FCN_ERROR);
  TestResult(Vec4BufDivBufByVecAsm(v4ar,v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByVecAsm()         ",FCN_ERROR);
  TestResult(Vec4BufMulBufByVecStd(v4ar,v4aa,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByVecStd()         ",FCN_ERROR);
  TestResult(Vec4BufDivBufByVecStd(v4ar,v4ar,v4a,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByVecStd()         ",FCN_ERROR);
  TestResult(Vec4SqrBlockUseSizeAsm(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4SqrBlockUseSizeAsm()        ",FCN_ERROR);
  TestResult(Vec4SqrtBlockUseSizeAsm(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SqrtBlockUseSizeAsm()       ",FCN_ERROR);
  TestResult(Vec4SqrBlockUseSizeStd(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4SqrBlockUseSizeStd()        ",FCN_ERROR);
  TestResult(Vec4SqrtBlockUseSizeStd(v4ar,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4SqrtBlockUseSizeStd()       ",FCN_ERROR);
  TestResult(Vec4LerpBlockUseSizeAsm(v4ar,v4aa,0.5,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4LerpBlockUseSizeAsm()       ",FCN_ERROR);
  TestResult(Vec4LerpBlockUseSizeStd(v4ar,v4aa,0.5,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4LerpBlockUseSizeStd()       ",FCN_ERROR);

  TestResult(Vec4BufLerpBlockAsm(v4ar,v4ar.size(),v4ar,v4ar.size(),pVec4_r,0.5,6),*((vec4*)v4ar.m_VecArray),v4Results[0],
	     6*sizeof(vec4),            "Vec4BufLerpBlockAsm()           ",FCN_ERROR);
  for( int i=0 ; i < v4ar.length() ; ++i ) v4ar[i] = v4aa[i];

  TestResult(Vec4CrossBlockUseSizeAsm(v4ar,v4aa,v4ar.size(),v4ar.length()),*((vec4*)v4ar.m_VecArray),v4Results[58],
	     v4ar.length()*sizeof(vec4),"Vec4CrossBlockUseSizeAsm()      ",FCN_ERROR);
  for( int i=0 ; i < v4ar.length() ; ++i ) v4ar[i] = v4aa[i];

  TestResult(Vec4NormalizeBlockUseSizeStd(v4ar,v4ar.size(),6),*((vec4*)v4ar.m_VecArray),v4Results[52],
	     6*sizeof(vec4),"Vec4NormalizeBlockUseSizeStd() ",FCN_ERROR);
  for( int i=0 ; i < v4ar.length() ; ++i ) v4ar[i] = v4aa[i];

  TestResult(Vec4DotBlockUseSizeStd(fBase,v4ar,v4aa,v4ar.size(),v4ar.length()),fBase[0],FloatList[28],
	     6*sizeof(float),"Vec4DotBlockUseSizeAsm()       ",FCN_ERROR);

  TestResult(Vec4LengthBlockUseSizeStd(fBase,v4ar,v4ar.size(),v4ar.length()),fBase[0],FloatList[34],
	     6*sizeof(float),"Vec4LengthBlockUseSizeStd()    ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector4 Buffer Methods (v4buf:aligned)\n\n");

  v4buf v4ba(6,32,16,v4Results);
  v4buf v4br(6,32,16,v4Results);

  Vec4BufAddFloatToBufAsm(v4br,v4br.size(),v4ba,v4ba.size(),1.0,v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddFloatToBufAsm()       ",FCN_ERROR);
  Vec4BufSubFloatFromBufAsm(v4br,v4br.size(),v4br,v4br.size(),1.0,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubFloatFromBufAsm()     ",FCN_ERROR);
  Vec4BufAddFloatToBufStd(v4br,v4br.size(),v4ba,v4ba.size(),1.0,v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[16],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddFloatToBufStd()       ",FCN_ERROR);
  Vec4BufSubFloatFromBufStd(v4br,v4br.size(),v4br,v4br.size(),1.0,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubFloatFromBufStd()     ",FCN_ERROR);
  Vec4BufMulFloatToBufAsm(v4br,v4br.size(),v4ba,v4ba.size(),2.0,v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulFloatToBufAsm()       ",FCN_ERROR);
  Vec4BufDivBufByFloatAsm(v4br,v4br.size(),v4br,v4br.size(),2.0,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByFloatAsm()       ",FCN_ERROR);
  Vec4BufMulFloatToBufStd(v4br,v4br.size(),v4ba,v4ba.size(),2.0,v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulFloatToBufStd()       ",FCN_ERROR);
  Vec4BufDivBufByFloatStd(v4br,v4br.size(),v4br,v4br.size(),2.0,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByFloatStd()       ",FCN_ERROR);
  Vec4BufNegateBufAsm(v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[28],
	     v4br.length()*sizeof(vec4),"Vec4BufNegateBufAsm()           ",FCN_ERROR);
  Vec4BufNegateBufStd(v4br,v4br.size(),v4br,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4br.length()*sizeof(vec4),"Vec4BufNegateBufStd()           ",FCN_ERROR);

  Vec4BufAddVecToBufAsm(v4br,v4br.size(),v4ba,v4ba.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddVecToBufAsm()         ",FCN_ERROR);
  Vec4BufSubVecFromBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubVecFromBufAsm()       ",FCN_ERROR);
  Vec4BufAddVecToBufStd(v4br,v4br.size(),v4ba,v4ba.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[34],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddVecToBufStd()         ",FCN_ERROR);
  Vec4BufSubVecFromBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubVecFromBufAsm()       ",FCN_ERROR);

  Vec4BufMulBufByVecUseSizeAsm(v4br,v4br.size(),v4ba,v4ba.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4br.length()*sizeof(vec4),"Vec4BufMulBufByVecUseSizeAsm()  ",FCN_ERROR);
  Vec4BufDivBufByVecUseSizeAsm(v4br,v4br.size(),v4br,v4br.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByVecUseSizeAsm()  ",FCN_ERROR);
  Vec4BufMulBufByVecUseSizeStd(v4br,v4br.size(),v4ba,v4ba.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[40],
	     v4br.length()*sizeof(vec4),"Vec4BufMulBufByVecUseSizeStd()  ",FCN_ERROR);
  Vec4BufDivBufByVecUseSizeStd(v4br,v4br.size(),v4br,v4br.size(),v4a,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByVecUseSizeStd()  ",FCN_ERROR);

  Vec4BufAddBlockToBufAsm(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddBlockToBufAsm()       ",FCN_ERROR);
  Vec4BufSubBlockFromBufAsm(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubBlockFromBufAsm()     ",FCN_ERROR);
  Vec4BufAddBlockToBufStd(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddBlockToBufStd()       ",FCN_ERROR);
  Vec4BufSubBlockFromBufStd(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubBlockFromBufStd()     ",FCN_ERROR);

  Vec4BufMulBufByBlockAsm(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByBlockAsm()       ",FCN_ERROR);
  Vec4BufDivBufByBlockAsm(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByBlockAsm()       ",FCN_ERROR);
  Vec4BufMulBufByBlockStd(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByBlockStd()       ",FCN_ERROR);
  Vec4BufDivBufByBlockStd(v4br,v4br,v4ba,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByBlockStd()       ",FCN_ERROR);

  Vec4BufAddBufToBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddBufToBufAsm()         ",FCN_ERROR);
  Vec4BufSubBufFromBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubBufFromBufAsm()       ",FCN_ERROR);
  Vec4BufAddBufToBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[22],
	     v4ar.length()*sizeof(vec4),"Vec4BufAddBufToBufStd()         ",FCN_ERROR);
  Vec4BufSubBufFromBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSubBufFromBufStd()       ",FCN_ERROR);

  Vec4BufMulBufByBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByBufAsm()         ",FCN_ERROR);
  Vec4BufDivBufByBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByBufAsm()         ",FCN_ERROR);
  Vec4BufMulBufByBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufMulBufByBufStd()         ",FCN_ERROR);
  Vec4BufDivBufByBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufDivBufByBufStd()         ",FCN_ERROR);

  Vec4BufSqrBufAsm(v4br,v4br.size(),v4ba,v4ba.size(),v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufSqrBufAsm()              ",FCN_ERROR);
  Vec4BufSqrtBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSqrtBufAsm()             ",FCN_ERROR);
  Vec4BufSqrBufStd(v4br,v4br.size(),v4ba,v4ba.size(),v4ba.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[46],
	     v4ar.length()*sizeof(vec4),"Vec4BufSqrBufStd()              ",FCN_ERROR);
  Vec4BufSqrtBufStd(v4br,v4br.size(),v4br,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufSqrtBufStd()             ",FCN_ERROR);

  Vec3BufCrossBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[58],
	     v4ar.length()*sizeof(vec4),"Vec4BufCrossBufAsm()            ",FCN_ERROR);
  for( int i=0 ; i < v4br.length() ; ++i ) v4br[i] = v4ba[i];
  Vec4BufCrossBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[58],
	     v4ar.length()*sizeof(vec4),"Vec4BufCrossBufStd()            ",FCN_ERROR);
  for( int i=0 ; i < v4br.length() ; ++i ) v4br[i] = v4ba[i];

  Vec4BufLerpBufAsm(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),0.5,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufLerpBufAsm()             ",FCN_ERROR);
  Vec4BufLerpBufStd(v4br,v4br.size(),v4br,v4br.size(),v4ba,v4ba.size(),0.5,v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[0],
	     v4ar.length()*sizeof(vec4),"Vec4BufLerpBufStd()             ",FCN_ERROR);

  Vec4BufNormalizeBufStd(v4br,v4br.size(),v4br,v4br.size(),v4br.length());
  TestResult(v4ar=v4br,*((vec4*)v4ar.m_VecArray),v4Results[64],
	     v4ar.length()*sizeof(vec4),"Vec4BufNormalizeBufStd()        ",FCN_ERROR);
  for( int i=0 ; i < v4br.length() ; ++i ) v4br[i] = v4ba[i];

  TestResult(Vec4BufDotBufStd((void*)fBase,sizeof(float),v4br,v4br.size(),v4ba,v4ba.size(),v4br.length()),fBase[0],FloatList[28],
	     v4br.length()*sizeof(float),"Vec4BufDotBufStd()              ",FCN_ERROR);
  TestResult(Vec4BufLengthBufStd((void*)fBase,sizeof(float),v4br,v4br.size(),v4br.length()),fBase[0],FloatList[34],
	     v4ar.length()*sizeof(float),"Vec4BufLengthBufStd()           ",FCN_ERROR);

  fprintf(stdout,"\n-------------> Vector4Logical Methods (aligned)\n\n");

  for( int i=0 ; i < v4ar.length() ; ++i ) v4ar[i] = v4aa[i];
  TestResult(Vec4EqualsAsm(&iFlag,v4ar,v4aa),iFlag,iTrue,
	     sizeof(int32_t),"Vec4EqualsAsm()                 ",FCN_ERROR);
  TestResult(Vec4NotEqualsAsm(&iFlag,v4ar,v4aa),iFlag,iFalse,
	     sizeof(int32_t),"Vec4NotEqualsAsm()              ",FCN_ERROR);

  return 0;
}
