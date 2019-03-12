#ifndef _VECMATH_INCLUDE
#define _VECMATH_INCLUDE

/* -----------------------------------------------------------
 * Grab the common include files
 * ----------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <mmintrin.h>
#include <emmintrin.h>
#include <float.h>
#include <string.h>

/* -----------------------------------------------------------
 * Either GNU or Microsoft
 * ----------------------------------------------------------- */

// THIS REQUIRES EXTERNAL CONFIGURATION

#if defined(_USE_SIMD)

#if defined(__linux__) && defined(__i386) && defined(__MMX__)
#define __Linux_SIMD
#elif defined(_WIN32) || defined(_WIN64)
#define __MSoft_SIMD
#else
#define __No_SIMD
#endif

#else
#define __No_SIMD
#endif

/* -----------------------------------------------------------
 * Define the high performance interface specification
 * ----------------------------------------------------------- */

#if defined(__linux__) && defined(_USE_SIMD)
#define AlignStruct(a) struct __attribute__((aligned(a)))
#elif defined(__linux__)
#define AlignStruct(a) struct __attribute__((aligned(a)))
#else
#define AlignStruct(a) __declspec(align(a)) struct
#endif


/* -----------------------------------------------------------
 * Define some global constants
 * ----------------------------------------------------------- */

extern const float fZero;
extern const float fOne;

/* -----------------------------------------------------------
 * Error handler for Microsoft IEEE error management
 * ----------------------------------------------------------- */

#if defined(__MSoft)
enum FpErrorClass { fpInexact=1,fpUnderflow,fpOverflow,fpZeroDivide,fpInvalidOperation };
#endif

/* -----------------------------------------------------------
 * 16-bit float as fixed-point integer format
 * ----------------------------------------------------------- */

struct half {
  unsigned short sh;
  half(const float x);
  operator float () const;
};

/* -----------------------------------------------------------
 * One dimensional methods
 * ----------------------------------------------------------- */

#if defined(__No_SIMD)

#define FloatLerp FloatLerpStd
#define FloatSqr  FloatSqrStd

#else

#define FloatLerp FloatLerpAsm
#define FloatSqr  FloatSqrAsm

#endif

extern float FloatLerpAsm(const float a,const float b,const float c);
extern float FloatLerpStd(const float u,const float v,const float x);
extern float FloatSqrAsm(float x);
extern float FloatSqrStd(float x);

/* Embedded integrated methods */

float lerp(const float u, const float v, const float x);
float sqr(float x);

/* -----------------------------------------------------------
 * 2D single-precision floating-point vector
 * ----------------------------------------------------------- */

AlignStruct(8) vec2 {
  float x, y;

  vec2(){}
  vec2(const float iv) : x(iv),y(iv) {}
  vec2(const float ix, const float iy) : x(ix),y(iy) {}

  operator const float *() const { return &x;	}

  void operator += (const vec2 &v);
  void operator += (const float s);
  void operator -= (const vec2 &v);
  void operator -= (const float s);
  void operator *= (const vec2 &v);
  void operator *= (const float s);
  void operator /= (const vec2 &v);
  void operator /= (const float s);
};

#define vec2size 2*sizeof(float)

#if defined(__linux__)
#define Vec2AddAsm           _Vec2AddAsm
#define Vec2AddFloatAsm      _Vec2AddFloatAsm
#define Vec2SubtractAsm      _Vec2SubtractAsm
#define Vec2SubtractFloatAsm _Vec2SubtractFloatAsm
#define Vec2NegateAsm        _Vec2NegateAsm
#define Vec2MultiplyAsm      _Vec2MultiplyAsm
#define Vec2MultiplyFloatAsm _Vec2MultiplyFloatAsm
#define Vec2FloatMultiplyAsm _Vec2FloatMultiplyAsm
#define Vec2DivideAsm        _Vec2DivideAsm
#define Vec2DivideFloatAsm   _Vec2DivideFloatAsm
#define Vec2LerpAsm          _Vec2LerpAsm
#define Vec2SqrAsm           _Vec2SqrAsm
#define Vec2NormalizeAsm     _Vec2NormalizeAsm
#define Vec2DotAsm           _Vec2DotAsm
#define Vec2LengthAsm        _Vec2LengthAsm
#endif

#if defined(__No_SIMD)

#define Vec2Add           Vec2AddStd
#define Vec2AddFloat      Vec2AddFloatStd
#define Vec2Subtract      Vec2SubtractStd
#define Vec2SubtractFloat Vec2SubtractFloatStd
#define Vec2Negate        Vec2NegateStd
#define Vec2Multiply      Vec2MultiplyStd
#define Vec2MultiplyFloat Vec2MultiplyFloatStd
#define Vec2FloatMultiply Vec2FloatMultiplyStd
#define Vec2Divide        Vec2DivideStd
#define Vec2DivideFloat   Vec2DivideFloatStd
#define Vec2Lerp          Vec2LerpStd
#define Vec2Sqr           Vec2SqrStd
#define Vec2Normalize     Vec2NormalizeStd
#define Vec2Dot           Vec2DotStd
#define Vec2Length        Vec2LengthStd

#else

#define Vec2Add           Vec2AddAsm
#define Vec2AddFloat      Vec2AddFloatAsm
#define Vec2Subtract      Vec2SubtractAsm
#define Vec2SubtractFloat Vec2SubtractFloatAsm
#define Vec2Negate        Vec2NegateAsm
#define Vec2Multiply      Vec2MultiplyAsm
#define Vec2MultiplyFloat Vec2MultiplyFloatAsm
#define Vec2FloatMultiply Vec2FloatMultiplyAsm
#define Vec2Divide        Vec2DivideAsm
#define Vec2DivideFloat   Vec2DivideFloatAsm
#define Vec2Lerp          Vec2LerpAsm
#define Vec2Sqr           Vec2SqrAsm
#define Vec2Normalize     Vec2NormalizeAsm
#define Vec2Dot           Vec2DotAsm
#define Vec2Length        Vec2LengthAsm

#endif

/* ---------------------------------------------------------
 * Two dimensional methods
 * --------------------------------------------------------- */

extern void  Vec2CopyAsm(vec2& r,const vec2& v);
extern void  Vec2CopyStd(vec2& r,const vec2& v);
extern void  Vec2AddAsm(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2AddStd(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2AddFloatAsm(vec2& r,const vec2& u,const float s);
extern void  Vec2AddFloatStd(vec2& r,const vec2& v,const float s);
extern void  Vec2SubtractAsm(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2SubtractStd(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2SubtractFloatAsm(vec2& r,const vec2& v,const float s);
extern void  Vec2SubtractFloatStd(vec2& r,const vec2& v,const float s);
extern void  Vec2NegateAsm(vec2& r,const vec2& u);
extern void  Vec2NegateStd(vec2& r,vec2& v);
extern void  Vec2MultiplyAsm(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2MultiplyStd(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2MultiplyFloatAsm(vec2& r,const vec2& v,const float s);
extern void  Vec2MultiplyFloatStd(vec2& r,const vec2& v,const float s);
extern void  Vec2FloatMultiplyAsm(vec2& r,const float s,const vec2& v);
extern void  Vec2FloatMultiplyStd(vec2& r,const float s,const vec2& v);
extern void  Vec2DivideAsm(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2DivideStd(vec2& r,const vec2& u,const vec2& v);
extern void  Vec2DivideFloatAsm(vec2& r,const vec2& v,const float s);
extern void  Vec2DivideFloatStd(vec2& r,const vec2& v,const float s);
extern void  Vec2LerpAsm(vec2& r,const vec2& u,const vec2& v,const float step);
extern void  Vec2LerpStd(vec2& r,const vec2& u,const vec2& v,const float x);
extern void  Vec2SqrAsm(vec2& r,const vec2& u);
extern void  Vec2SqrStd(vec2& r,const vec2& v);
extern void  Vec2NormalizeAsm(vec2& r,const vec2& v);
extern void  Vec2NormalizeStd(vec2& r,const vec2& v);
extern float Vec2DotAsm(const vec2& u,const vec2& v);
extern float Vec2DotStd(const vec2& u,const vec2& v);
extern float Vec2LengthAsm(const vec2& v);
extern float Vec2LengthStd(const vec2& v);

vec2  operator + (const vec2& u,const vec2& v);
vec2  operator + (const vec2& u,const float s);
vec2  operator - (const vec2& u,const vec2& v);
vec2  operator - (const vec2& u,const float s);
vec2  operator - (const vec2& u);
vec2  operator * (const vec2& u,const vec2& v);
vec2  operator * (const vec2& u,const float s);
vec2  operator * (const float s,const vec2& v);
vec2  operator / (const vec2& u,const vec2& v);
vec2  operator / (const vec2& u,const float s);
vec2  lerp       (const vec2& u,const vec2& v,const float step);
vec2  sqr        (const vec2& u);
vec2  normalize  (const vec2& v);
float dot        (const vec2& u,const vec2& v);
float length     (const vec2& u);

bool operator == (const vec2 &u, const vec2 &v);
bool operator != (const vec2 &u, const vec2 &v);

/* ---------------------------------------------
 * 3D single-precision floating-point vector
 * --------------------------------------------- */

AlignStruct(16) vec3
{
  float x,y,z,n;

  vec3(){}
  vec3(const float iv) : x(iv),y(iv),z(iv) {}
  vec3(const vec2 &xy, const float iz) : x(xy.x),y(xy.y),z(iz) {}
  vec3(const float ix, const float iy, const float iz) : x(ix),y(iy),z(iz) {}

  operator const float *() const { return &x; }

  void operator += (const vec3& v);
  void operator += (const float s);
  void operator -= (const vec3& v);
  void operator -= (const float s);
  void operator *= (const vec3& v);
  void operator *= (const float s);
  void operator /= (const vec3& v);
  void operator /= (const float s);
};

#define vec3size 3*sizeof(float)

#if defined(__No_SIMD)

#define Vec3Add           Vec3AddStd
#define Vec3AddFloat      Vec3AddFloatStd
#define Vec3FloatAdd      Vec3FloatAddStd
#define Vec3Subtract      Vec3SubtractStd
#define Vec3SubtractFloat Vec3SubtractFloatStd
#define Vec3FloatSubtract Vec3FloatSubtractStd
#define Vec3Negate        Vec3NegateStd
#define Vec3Multiply      Vec3MultiplyStd
#define Vec3MultiplyFloat Vec3MultiplyFloatStd
#define Vec3FloatMultiply Vec3FloatMultiplyStd
#define Vec3Divide        Vec3DivideStd
#define Vec3DivideFloat   Vec3DivideFloatStd
#define Vec3Dot           Vec3DotStd
#define Vec3Lerp          Vec3LerpStd
#define Vec3Sqr           Vec3SqrStd
#define Vec3Normalize     Vec3NormalizeStd
#define Vec3Length        Vec3LengthStd
#define Vec3Cross         Vec3CrossStd

#else

#define Vec3Add           Vec3AddAsm
#define Vec3AddFloat      Vec3AddFloatAsm
#define Vec3FloatAdd      Vec3FloatAddAsm
#define Vec3Subtract      Vec3SubtractAsm
#define Vec3SubtractFloat Vec3SubtractFloatAsm
#define Vec3FloatSubtract Vec3FloatSubtractAsm
#define Vec3Negate        Vec3NegateAsm
#define Vec3Multiply      Vec3MultiplyAsm
#define Vec3MultiplyFloat Vec3MultiplyFloatAsm
#define Vec3FloatMultiply Vec3FloatMultiplyAsm
#define Vec3Divide        Vec3DivideAsm
#define Vec3DivideFloat   Vec3DivideFloatAsm
#define Vec3Dot           Vec3DotAsm
#define Vec3Lerp          Vec3LerpAsm
#define Vec3Sqr           Vec3SqrAsm
#define Vec3Normalize     Vec3NormalizeAsm
#define Vec3Length        Vec3LengthAsm
#define Vec3Cross         Vec3CrossAsm

#endif

/* ---------------------------------------------------------
 * 4D single-precision floating-point vector
 * --------------------------------------------------------- */

extern void  Vec3AddAsm(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3AddStd(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3AddFloatAsm(vec3& r,const vec3& v,const float s);
extern void  Vec3AddFloatStd(vec3& r,const vec3& v,const float s);
extern void  Vec3FloatAddAsm(vec3& r,const float s,const vec3& v);
extern void  Vec3FloatAddStd(vec3& r,const float s,const vec3& v);
extern void  Vec3SubtractAsm(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3SubtractStd(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3SubtractFloatAsm(vec3& r,const vec3& v,const float s);
extern void  Vec3SubtractFloatStd(vec3& r,const vec3& v,const float s);
extern void  Vec3FloatSubtractAsm(vec3& r,const float s,const vec3& v);
extern void  Vec3FloatSubtractStd(vec3& r,const float s,const vec3& v);
extern void  Vec3MultiplyAsm(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3MultiplyStd(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3MultiplyFloatAsm(vec3& r,const vec3& v,const float s);
extern void  Vec3MultiplyFloatStd(vec3& r,const vec3& u,const float s);
extern void  Vec3FloatMultiplyAsm(vec3& r,const float s,const vec3& v);
extern void  Vec3FloatMultiplyStd(vec3& r,const float s,const vec3& v);
extern void  Vec3DivideAsm(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3DivideStd(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3DivideFloatAsm(vec3& r,const vec3& v,const float s);
extern void  Vec3DivideFloatStd (vec3& r,const vec3& v,const float s);
extern void  Vec3NegateAsm(vec3& r,const vec3& v);
extern void  Vec3NegateStd(vec3& r,const vec3& v);
extern void  Vec3LerpAsm(vec3& r,const vec3& u,const vec3& v,const float step);
extern void  Vec3LerpStd(vec3& r,const vec3& u,const vec3& v,const float x);
extern void  Vec3SqrAsm(vec3& r,const vec3& v);
extern void  Vec3SqrStd(vec3& r,const vec3& v);
extern void  Vec3NormalizeAsm(vec3& r,const vec3& v);
extern void  Vec3NormalizeStd(vec3& r,const vec3& v);
extern float Vec3LengthAsm(const vec3& v);
extern float Vec3LengthStd(const vec3& v);
extern float Vec3DotAsm(const vec3& u,const vec3& v);
extern float Vec3DotStd(const vec3& u,const vec3& v);
extern void  Vec3CrossAsm(vec3& r,const vec3& u,const vec3& v);
extern void  Vec3CrossStd(vec3& r,const vec3& u,const vec3& v);

// Support methods

vec3  operator + (const vec3& u,const vec3& v);
vec3  operator + (const vec3& u,const float s);
vec3  operator - (const vec3& u,const vec3& v);
vec3  operator - (const vec3& u,const float s);
vec3  operator - (const float s,const vec3& v);
vec3  operator - (const vec3& v);
vec3  operator * (const vec3& u,const vec3& v);
vec3  operator * (const vec3& u,const float s);
vec3  operator * (const float s,const vec3& v);
vec3  operator / (const vec3& u,const vec3& v);
vec3  operator / (const vec3& u,const float s);
vec3  lerp       (const vec3& u,const vec3& v,const float x);
vec3  sqr        (const vec3& v);
vec3  normalize  (const vec3& v);
vec3  cross      (const vec3& u,const vec3& v);
float dot        (const vec3& u,const vec3& v);
float length     (const vec3& v);

bool operator == (const vec3 &u, const vec3 &v);
bool operator != (const vec3 &u, const vec3 &v);

/* ---------------------------------------------
 * 4D single-precision floating-point vector
 * --------------------------------------------- */

AlignStruct(16) vec4
{

  float x, y, z, w;

  vec4(){}
  vec4(const float iv) : x(iv),y(iv),z(iv),w(iv) {}
  vec4(const float ix, const float iy, const float iz, const float iw) : x(ix),y(iy),z(iz),w(iw) {}
  vec4(const vec2 &xy, const float iz, const float iw) : x(xy.x),y(xy.y),z(iz),w(iw) {}
  vec4(const vec2 &xy, const vec2 &zw) : x(xy.x),y(xy.y),z(zw.x),w(zw.y) {}
  vec4(const vec3 &xyz, const float iw) : x(xyz.x),y(xyz.y),z(xyz.z),w(iw) {}

  operator const float *() const { return &x; }

  vec3 xyz() const { return vec3(x, y, z); }

  void operator += (const vec4& v);
  void operator += (const float s);
  void operator -= (const vec4& v);
  void operator -= (const float s);
  void operator *= (const vec4& v);
  void operator *= (const float s);
  void operator /= (const vec4& v);
  void operator /= (const float s);
};

#define vec4size 4*sizeof(float)

#if defined(__No_SIMD)

#define Vec4Add             Vec4AddStd
#define Vec4AddFloat        Vec4AddFloatStd
#define Vec4FloatAdd        Vec4FloatAddStd
#define Vec4Subtract        Vec4SubtractStd
#define Vec4SubtractFloat   Vec4SubtractFloatStd
#define Vec4FloatSubtract   Vec4FloatSubtractStd
#define Vec4Negate          Vec4NegateStd
#define Vec4Multiply        Vec4MultiplyStd
#define Vec4MultiplyFloat   Vec4MultiplyFloatStd
#define Vec4FloatMultiply   Vec4FloatMultiplyStd
#define Vec4Divide          Vec4DivideStd
#define Vec4DivideFloat     Vec4DivideFloatStd
#define Vec4Lerp            Vec4LerpStd
#define Vec4Sqr             Vec4SqrStd
#define Vec4Cross           Vec4CrossStd
#define Vec4Normalize       Vec4NormalizeStd
#define Vec4Dot             Vec4DotStd
#define Vec4Length          Vec4LengthStd

#else

#define Vec4Add             Vec4AddAsm
#define Vec4AddFloat        Vec4AddFloatAsm     
#define Vec4FloatAdd        Vec4FloatAddAsm     
#define Vec4Subtract        Vec4SubtractAsm     
#define Vec4SubtractFloat   Vec4SubtractFloatAsm
#define Vec4FloatSubtract   Vec4FloatSubtractAsm
#define Vec4Negate          Vec4NegateAsm
#define Vec4Multiply        Vec4MultiplyAsm
#define Vec4MultiplyFloat   Vec4MultiplyFloatAsm
#define Vec4FloatMultiply   Vec4FloatMultiplyAsm
#define Vec4Divide          Vec4DivideAsm
#define Vec4DivideFloat     Vec4DivideFloatAsm
#define Vec4Lerp            Vec4LerpAsm
#define Vec4Sqr             Vec4SqrAsm
#define Vec4Cross           Vec4CrossAsm
#define Vec4Normalize       Vec4NormalizeAsm
#define Vec4Length          Vec4LengthAsm
#define Vec4Dot             Vec4DotAsm

#endif

extern void  Vec4AddAsm(const vec4& r,const vec4& u,const vec4& v);
extern void  Vec4AddStd(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4AddFloatAsm(const vec4& r,const vec4& v,const float s);
extern void  Vec4AddFloatStd(vec4& r,const vec4& v,const float s);
extern void  Vec4FloatAddAsm(vec4& r,const float s,const vec4& v);
extern void  Vec4FloatAddStd(vec4& r,const float s,const vec4& v);
extern void  Vec4SubtractAsm(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4SubtractStd(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4SubtractFloatAsm(vec4& r,const vec4& v,const float s);
extern void  Vec4SubtractFloatStd(vec4& r,const vec4& v,const float s);
extern void  Vec4FloatSubtractAsm(vec4& r,const float s,const vec4& v);
extern void  Vec4FloatSubtractStd(vec4& r,const float s,const vec4& v);
extern void  Vec4MultiplyAsm(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4MultiplyStd(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4MultiplyFloatAsm(vec4& r,const vec4& v,const float s);
extern void  Vec4MultiplyFloatStd(vec4& r,const vec4& u,const float s);
extern void  Vec4FloatMultiplyAsm(vec4& r,const float s,const vec4& v);
extern void  Vec4FloatMultiplyStd(vec4& r,const float s,const vec4& u);
extern void  Vec4DivideAsm(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4DivideStd(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4DivideFloatAsm(vec4& r,const vec4& v,const float s);
extern void  Vec4DivideFloatStd(vec4& r,const vec4& v,const float s);
extern void  Vec4NegateAsm(vec4& r,const vec4& v);
extern void  Vec4NegateStd(vec4& r,const vec4& v);
extern void  Vec4LerpAsm(vec4& r,const vec4& u,const vec4& v,const float step);
extern void  Vec4LerpStd(vec4& r,const vec4& u,const vec4& v,const float x);
extern void  Vec4SqrAsm(vec4& r,const vec4& v);
extern void  Vec4SqrStd(vec4& r,const vec4& v);
extern void  Vec4NormalizeAsm(vec4& r,const vec4& v);
extern void  Vec4NormalizeStd(vec4& r,const vec4& v);
extern void  Vec4CrossAsm(vec4& r,const vec4& u,const vec4& v);
extern void  Vec4CrossStd(vec4& r,const vec4& u,const vec4& v);
extern float Vec4DotAsm(const vec4& u,const vec4& v);
extern float Vec4DotStd(const vec4& u,const vec4& v);
extern float Vec4LengthAsm(const vec4& v);
extern float Vec4LengthStd(const vec4& v);

// Vec4 operations

vec4  operator + (const vec4& u,const vec4& v);
vec4  operator + (const vec4& u,const float s);
vec4  operator - (const vec4& u,const vec4& v);
vec4  operator - (const vec4& u,const float s);
vec4  operator - (const vec4& v);
vec4  operator - (const float s,const vec4& v);
vec4  operator * (const vec4& u,const vec4& v);
vec4  operator * (const vec4& u,const float s);
vec4  operator / (const vec4& u,const vec4& v);
vec4  operator / (const vec4& u,const float s);
vec4  lerp       (const vec4& u,const vec4& v,const float x);
vec4  sqr        (const vec4& v);
vec4  normalize  (const vec4& v);
vec4  cross      (const vec4& u,const vec4& v);
float dot        (const vec4& u,const vec4& v);
float length     (const vec4& v);

bool operator == (const vec4& u, const vec4& v);
bool operator != (const vec4& u, const vec4& v);

/* ---------------------------------------------
 * 2x2 matrix
 * --------------------------------------------- */

AlignStruct(16) mat2
{
  float e00,e01,e10,e11;
  mat2(){}
  mat2(const float m00,const float m01,const float m10,const float m11) :
    e00(m00),e01(m01),e10(m10),e11(m11) {}

  mat2(const vec2& v0,const vec2& v1)
  {
    memcpy((void*)&e00,(void*)&v0,sizeof(vec2));
    memcpy((void*)&e10,(void*)&v1,sizeof(vec2));
  }

  vec2 &getRow(const unsigned int index) { return *((vec2*)((float*)&e00 + index)); }

  operator const float*() const { return (float*)&e00; }
};

#define mat2size 4*sizeof(float)

#if defined(__No_SIMD)

#define Mat2Add               Mat2AddStd
#define Mat2Subtract          Mat2SubtractStd
#define Mat2Negate            Mat2NegateStd
#define Mat2Multiply          Mat2MultiplyStd
#define Mat2MultiplyVec       Mat2MultiplyVecStd
#define Mat2MultiplyFloat     Mat2MultiplyFloatStd
#define Mat2Identity          Mat2IdentityStd
#define Mat2Transpose         Mat2TransposeStd
#define Mat2Rotate            Mat2RotateStd
#define Mat2Scale             Mat2ScaleStd

#else

#define Mat2Add               Mat2AddAsm
#define Mat2Subtract          Mat2SubtractAsm
#define Mat2Negate            Mat2NegateAsm
#define Mat2Multiply          Mat2MultiplyAsm
#define Mat2MultiplyVec       Mat2MultiplyVecAsm
#define Mat2MultiplyFloat     Mat2MultiplyFloatAsm
#define Mat2Identity          Mat2IdentityAsm
#define Mat2Transpose         Mat2TransposeAsm
#define Mat2Rotate            Mat2RotateAsm
#define Mat2Scale             Mat2ScaleAsm

#endif

/* ---------------------------------------------------------
 * Two dimensional matrix methods
 * --------------------------------------------------------- */

extern void Mat2AddAsm(mat2& r,const mat2& m,const mat2& n);
extern void Mat2AddStd(mat2& r,const mat2& m,const mat2& n);
extern void Mat2SubtractAsm(mat2& r,const mat2& m,const mat2& n);
extern void Mat2SubtractStd(mat2& r,const mat2& m,const mat2& n);
extern void Mat2NegateAsm(mat2& r,const mat2& m);
extern void Mat2NegateStd(mat2& r,const mat2& m);
extern void Mat2MultiplyAsm(mat2& r,const mat2& m,const mat2& n);
extern void Mat2MultiplyStd(mat2& r,const mat2& m,const mat2& n);
extern void Mat2MultiplyVecAsm(vec2& r,const mat2& m,const vec2& v);
extern void Mat2MultiplyVecStd(vec2& r,const mat2& m,const vec2& v);
extern void Mat2MultiplyFloatAsm(mat2& r,const mat2& m,const float s);
extern void Mat2MultiplyFloatStd(mat2& r,const mat2& m,const float s);
extern void Mat2IdentityAsm(mat2& r);
extern void Mat2IdentityStd(mat2& r);
extern void Mat2TransposeAsm(mat2& r,const mat2& m);
extern void Mat2TransposeStd(mat2& r,const mat2& m);
extern void Mat2RotateAsm(mat2& r,const float angle);
extern void Mat2RotateStd(mat2& r,const float angle);
extern void Mat2ScaleAsm(mat2& r,const float x,const float y);
extern void Mat2ScaleStd(mat2& r,const float x,const float y);

// Support methods

mat2 operator + (const mat2 &m, const mat2 &n);
mat2 operator - (const mat2 &m, const mat2 &n);
mat2 operator - (const mat2 &m);
mat2 operator * (const mat2 &m, const mat2 &n);
vec2 operator * (const mat2 &m, const vec2 &v);
mat2 operator * (const mat2 &m, const float x);

mat2 m2_identity ();
mat2 m2_transpose(const mat2 &m);
mat2 m2_rotate   (const float s);
mat2 m2_scale    (const float x,const float y);

/* ---------------------------------------------
 * 3x3 matrix
 * --------------------------------------------- */

AlignStruct(16) mat3
{
  float e00,e01,e02,n03,e10,e11,e12,n13,e20,e21,e22,n23;
  mat3(){}

  mat3(bool) : n03(1.0f),n13(1.0f),n23(1.0f) {}

  mat3(const float m00,
       const float m01,
       const float m02,
       const float m10,
       const float m11,
       const float m12,
       const float m20,
       const float m21,
       const float m22) :
    e00(m00),e01(m01),e02(m02),n03(1.0f),
    e10(m10),e11(m11),e12(m12),n13(1.0f),
    e20(m20),e21(m21),e22(m22),n23(1.0f) {}

    mat3(const float m00,
	 const float m01,
	 const float m02,
	 const float x03,
	 const float m10,
	 const float m11,
	 const float m12,
	 const float x13,
	 const float m20,
	 const float m21,
	 const float m22,
	 const float x23) :
      e00(m00),e01(m01),e02(m02),n03(x03),
      e10(m10),e11(m11),e12(m12),n13(x13),
      e20(m20),e21(m21),e22(m22),n23(x23) {}

    mat3(const vec3 &v0,const vec3 &v1,const vec3 &v2)
      {
	memcpy((void*)&e00,(void*)&v0,sizeof(vec3));
	memcpy((void*)&e10,(void*)&v1,sizeof(vec3));
	memcpy((void*)&e20,(void*)&v2,sizeof(vec3));
      }

    vec3 &getRow(const unsigned int index) { return *((vec3*)((float*)&e00 + index)); }

    void clearW() { n03 = n13 = n23 = 1.0; }

    operator const float*() const { return (float*)&e00; }
};

#define mat3size 9*sizeof(float)

#if defined(__No_SIMD)

#define Mat3Add               Mat3AddStd
#define Mat3Subtract          Mat3SubtractStd
#define Mat3Negate            Mat3NegateStd
#define Mat3Multiply          Mat3MultiplyStd
#define Mat3MultiplyVec       Mat3MultiplyVecStd
#define Mat3MultiplyFloat     Mat3MultiplyFloatStd	
#define Mat3Identity          Mat3IdentityStd
#define Mat3Transpose         Mat3TransposeStd
#define Mat3Inverse           Mat3InverseStd
#define Mat3RotateX           Mat3RotateXStd
#define Mat3RotateY           Mat3RotateYStd
#define Mat3RotateZ           Mat3RotateZStd
#define Mat3RotateXY          Mat3RotateXYStd
#define Mat3RotateXYZ         Mat3RotateXYZStd
#define Mat3Scale             Mat3ScaleStd

#else

#define Mat3Add               Mat3AddAsm
#define Mat3Subtract          Mat3SubtractAsm
#define Mat3Negate            Mat3NegateAsm
#define Mat3MultiplyMMX       Mat3MultiplyAsm
#define Mat3Multiply          Mat3MultiplyFPU_Asm
#define Mat3MultiplyVecMMX    Mat3MultiplyVecAsm
#define Mat3MultiplyVec       Mat3MultiplyVecFPU_Asm
#define Mat3MultiplyFloat     Mat3MultiplyFloatAsm	
#define Mat3Identity          Mat3IdentityAsm
#define Mat3Transpose         Mat3TransposeAsm
#define Mat3InverseMMX        Mat3InverseAsm
#define Mat3Inverse           Mat3InverseFPU_Asm
#define Mat3RotateX           Mat3RotateXAsm
#define Mat3RotateY           Mat3RotateYAsm
#define Mat3RotateZ           Mat3RotateZAsm
#define Mat3RotateXY          Mat3RotateXYAsm
#define Mat3RotateXYZ_MMX     Mat3RotateXYZAsm
#define Mat3RotateXYZ         Mat3RotateXYZFPU_Asm
#define Mat3Scale             Mat3ScaleAsm
#endif

/* ---------------------------------------------------------
 * Three dimensional matrix methods
 * --------------------------------------------------------- */

extern void Mat3AddAsm(mat3& r,const mat3& m,const mat3& n);
extern void Mat3AddStd(mat3& r,const mat3& m,const mat3& n);
extern void Mat3SubtractAsm(mat3& r,const mat3& m,const mat3& v);
extern void Mat3SubtractStd(mat3& r,const mat3& m,const mat3& n);
extern void Mat3NegateAsm(mat3& r,const mat3& m);
extern void Mat3NegateStd(mat3& r,const mat3& m);
extern void Mat3MultiplyAsm(mat3& r,const mat3& m,const mat3& n);
extern void Mat3MultiplyFPU_Asm(mat3& r,const mat3& m,const mat3& n);
extern void Mat3MultiplyStd(mat3& r,const mat3& m,const mat3& n);
extern void Mat3MultiplyVecAsm(vec3& r,const mat3& m,const vec3& v);
extern void Mat3MultiplyVecFPU_Asm(vec3& r,const mat3& m,const vec3& v);
extern void Mat3MultiplyVecStd(vec3& r,const mat3& m,const vec3& v);
extern void Mat3MultiplyFloatAsm(mat3& r,const mat3& m,const float s);
extern void Mat3MultiplyFloatStd(mat3& r,const mat3& m,const float s);
extern void Mat3IdentityAsm(mat3& r);
extern void Mat3IdentityStd(mat3& r);
extern void Mat3TransposeAsm(mat3& r,const mat3& m);
extern void Mat3TransposeStd(mat3& r,const mat3& m);
extern void Mat3InverseAsm(mat3& r,const mat3& m);
extern void Mat3InverseFPU_Asm(mat3& r,const mat3& m);
extern void Mat3InverseStd(mat3& r,const mat3& m);
extern void Mat3RotateXAsm(mat3& r,const float x);
extern void Mat3RotateXStd(mat3& r,const float angle);
extern void Mat3RotateYAsm(mat3& r,const float y);
extern void Mat3RotateYStd(mat3& r,const float angle);
extern void Mat3RotateZAsm(mat3& r,const float z);
extern void Mat3RotateZStd(mat3& r,const float angle);
extern void Mat3RotateXYAsm(mat3& r,const float x,const float y);
extern void Mat3RotateXYStd(mat3& r,const float x,const float y);
extern void Mat3RotateXYZAsm(mat3& r,const float x,const float y,const float z);
extern void Mat3RotateXYZFPU_Asm(mat3& r,const float x,const float y,const float z);
extern void Mat3RotateXYZStd(mat3& r,const float x,const float y,const float z);
extern void Mat3ScaleAsm(mat3& r,const float x,const float y,const float z);
extern void Mat3ScaleStd(mat3& r,const float x,const float y,const float z);

// Support Methods

mat3 operator +  (const mat3 &m, const mat3 &n);
mat3 operator -  (const mat3 &m, const mat3 &n);
mat3 operator -  (const mat3 &m);
mat3 operator *  (const mat3 &m, const mat3 &n);
vec3 operator *  (const mat3 &m, const vec3 &v);
mat3 operator *  (const mat3 &m, const float x);
mat3 operator !  (const mat3 &m);
mat3 m3_identity ();
mat3 m3_transpose(const mat3 &m);
mat3 m3_rotateX  (const float s);
mat3 m3_rotateY  (const float s);
mat3 m3_rotateZ  (const float s);
mat3 m3_rotateXY (const float x,const float y);
mat3 m3_rotateXYZ(const float x,const float y,const float z);
mat3 m3_scale    (const float x,const float y,const float z);

/* ---------------------------------------------
 * 4x4 matrix
 * --------------------------------------------- */

AlignStruct(16) mat4
{
  float e00,e01,e02,e03,e10,e11,e12,e13,e20,e21,e22,e23,e30,e31,e32,e33;

  mat4(){}

  mat4(const float m00, const float m01, const float m02, const float m03,
       const float m10, const float m11, const float m12, const float m13,
       const float m20, const float m21, const float m22, const float m23,
	   const float m30, const float m31, const float m32, const float m33) :
  e00(m00),e01(m01),e02(m02),e03(m03),
  e10(m10),e11(m11),e12(m12),e13(m13),
  e20(m20),e21(m21),e22(m22),e23(m23),
  e30(m30),e31(m31),e32(m32),e33(m33) {}

  mat4(const vec4 &v0, const vec4 &v1, const vec4 &v2, const vec4 &v3)
  {
    memcpy((void*)&e00,(void*)&v0,sizeof(vec4));
	memcpy((void*)&e10,(void*)&v1,sizeof(vec4));
	memcpy((void*)&e20,(void*)&v2,sizeof(vec4));
	memcpy((void*)&e30,(void*)&v3,sizeof(vec4));
  }

  vec3 getRightRec()   const { vec3 t; memcpy((void*)&t,(void*)&e00,sizeof(vec3)); return t; }
  vec3 getUpVec()      const { vec3 t; memcpy((void*)&t,(void*)&e10,sizeof(vec3)); return t; }
  vec3 getForwardVec() const { vec3 t; memcpy((void*)&t,(void*)&e20,sizeof(vec3)); return t; }

  operator const float *() const { return (const float*)&e00; }

  void translate(const vec3 &v);
};

#define mat4size 4*sizeof(float)

AlignStruct(16) orthoMatrix
{
  float left,  right;
  float top,   bottom;
  float z_near,z_far;
  unsigned long d3dtype;

  orthoMatrix() {}
  orthoMatrix(const float lf,const float rt,
	      const float tp,const float bt,
	      const float nr,const float fr,
	      const bool d3d_t) :
    left(lf),  right(rt),
    top(tp),   bottom(bt),
    z_near(nr),z_far(fr),
    d3dtype((d3d_t == true ? 1 : 0)) {}
};

AlignStruct(16) perspectiveMatrix
{
  float fov;
  float width,height;
  float z_near,z_far;
  unsigned long d3dtype;
  perspectiveMatrix() {}
  perspectiveMatrix(const float field_of_view,
		    const float wd, const float ht,
		    const float zn,const float zf,
		    const bool d3d_t) :
    fov(field_of_view),
    width(wd), height(ht),
    z_near(zn),z_far(zf),
    d3dtype((true == d3d_t ? 1 : 0)) {}
};

#if defined(__No_SIMD)

#define Mat4Add                  Mat4AddStd
#define Mat4Subtract             Mat4SubtractStd
#define Mat4Negate               Mat4NegateStd
#define Mat4Multiply             Mat4MultiplyStd
#define Mat4MultiplyVec          Mat4MultiplyVecStd
#define Mat4MultiplyFloat        Mat4MultiplyFloatStd
#define Mat4Identity             Mat4IdentityStd
#define Mat4Transpose            Mat4TransposeStd
#define Mat4Scale                Mat4ScaleStd
#define Mat4RotateX              Mat4RotateXStd
#define Mat4RotateY              Mat4RotateYStd
#define Mat4RotateZ              Mat4RotateZStd
#define Mat4RotateXY             Mat4RotateXYStd
#define Mat4RotateXYZ            Mat4RotateXYZStd
#define Mat4TranslateMatrix      Mat4TranslateMatrixStd
#define Mat4TranslateFloat       Mat4TranslateFloatStd
#define Mat4TranslateVec         Mat4TranslateVecStd
#define Mat4OrthoStruct          Mat4OrthoStructStd
#define Mat4PerspectiveX         Mat4PerspectiveXStd
#define Mat4ShadowMatrix         Mat4ShadowMatrixStd
#define Mat4MirrorMatrix         Mat4MirrorMatrixStd
#define Mat4CubemapMatrix        Mat4CubemapMatrixStd
#define Mat4CubemapProjectionMat Mat4CubemapProjectionMatStd
#define Mat4LookAt               Mat4LookAtStd
#define Mat4GlToD3dProjectionMat Mat4GlToD3dProjectionMatStd

#else

#define Mat4Add                  Mat4AddAsm
#define Mat4Subtract             Mat4SubtractAsm
#define Mat4Negate               Mat4NegateAsm
#define Mat4MultiplyMMX          Mat4MultiplyAsm
#define Mat4Multiply             Mat4MultiplyFPU_Asm
#define Mat4MultiplyVecMMX       Mat4MultiplyVecAsm
#define Mat4MultiplyVec          Mat4MultiplyVecFPU_Asm
#define Mat4MultiplyFloat        Mat4MultiplyFloatAsm
#define Mat4Identity             Mat4IdentityAsm
#define Mat4Transpose            Mat4TransposeAsm
#define Mat4Scale                Mat4ScaleAsm
#define Mat4RotateX              Mat4RotateXAsm
#define Mat4RotateY              Mat4RotateYAsm
#define Mat4RotateZ              Mat4RotateZAsm
#define Mat4RotateXY             Mat4RotateXYAsm
#define Mat4RotateXYZ_MMX        Mat4RotateXYZAsm
#define Mat4RotateXYZ            Mat4RotateXYZFPU_Asm
#define Mat4TranslateMatrix      Mat4TranslateMatrixAsm
#define Mat4TranslateFloat       Mat4TranslateFloatAsm
#define Mat4TranslateVec         Mat4TranslateVecAsm
#define Mat4OrthoStruct          Mat4OrthoStructAsm
#define Mat4PerspectiveX         Mat4PerspectiveXAsm
#define Mat4ShadowMatrix         Mat4ShadowMatrixAsm
#define Mat4MirrorMatrix         Mat4MirrorMatrixAsm
#define Mat4CubemapMatrix        Mat4CubemapMatrixAsm
#define Mat4CubemapProjectionMat Mat4CubemapProjectionMatAsm
#define Mat4LookAt               Mat4LookAtFPU_Asm
#define Mat4GlToD3dProjectionMat Mat4GlToD3dProjectionMatAsm

#endif

/* ---------------------------------------------------------
 * Four dimensional matrix methods
 * --------------------------------------------------------- */

extern void Mat4AddAsm(mat4& r,const mat4& m,const mat4& n);
extern void Mat4AddStd(mat4& r,const mat4& m,const mat4& n);
extern void Mat4SubtractAsm(mat4& r,const mat4& m,const mat4& n);
extern void Mat4SubtractStd(mat4& r,const mat4& m,const mat4& n);
extern void Mat4NegateAsm(mat4& r,const mat4& m);
extern void Mat4NegateStd(mat4& r,const mat4& m);
extern void Mat4MultiplyAsm(mat4& r,const mat4& m,const mat4& n);
extern void Mat4MultiplyFPU_Asm(mat4& r,const mat4& m,const mat4& n);
extern void Mat4MultiplyStd(mat4& r,const mat4& m,const mat4& n);
extern void Mat4MultiplyVecAsm(vec4& r,const mat4& m,const vec4& v);
extern void Mat4MultiplyVecFPU_Asm(vec4& r,const mat4& m,const vec4& v);
extern void Mat4MultiplyVecStd(vec4& r,const mat4& m,const vec4& v);
extern void Mat4MultiplyFloatAsm(mat4& r,const mat4& m,const float s);
extern void Mat4MultiplyFloatStd(mat4& r,const mat4& m,const float s);
extern void Mat4IdentityAsm(mat4& r);
extern void Mat4IdentityStd(mat4& r);
extern void Mat4TransposeAsm(mat4& r,const mat4& m);
extern void Mat4TransposeStd(mat4& r,const mat4& m);
extern void Mat4ScaleAsm(mat4& r,const float x,const float y,const float z);
extern void Mat4ScaleStd(mat4& r,const float x,const float y,const float z);
extern void Mat4RotateXAsm(mat4& r,const float angle);
extern void Mat4RotateXStd(mat4& r,const float angle);
extern void Mat4RotateYAsm(mat4& r,const float angle);
extern void Mat4RotateYStd(mat4& r,const float y);
extern void Mat4RotateZAsm(mat4& r,const float angle);
extern void Mat4RotateZStd(mat4& r,const float z);
extern void Mat4RotateXYAsm(mat4& r,const float x,const float y);
extern void Mat4RotateXYStd(mat4& r,const float x,const float y);
extern void Mat4RotateXYZAsm(mat4& r,const float x,const float y,const float z);
extern void Mat4RotateXYZFPU_Asm(mat4& r,const float x,const float y,const float z);
extern void Mat4RotateXYZStd(mat4& r,const float x,const float y,const float z);
extern void Mat4TranslateMatrixAsm(mat4& r,const mat4& m,const vec3& v);
extern void Mat4TranslateMatrixStd(mat4& r,const mat4& m,const vec3& v);
extern void Mat4TranslateFloatAsm(mat4& r,const float x,const float y,const float z);
extern void Mat4TranslateFloatStd (mat4& r,const float x,const float y,const float z);
extern void Mat4TranslateVecAsm(mat4& r,const vec3& v);
extern void Mat4TranslateVecStd(mat4& r,const vec3& v);
extern void Mat4OrthoStructAsm(mat4& r,const struct orthoMatrix& s);
extern void Mat4OrthoStructStd(mat4& r,const struct orthoMatrix& d);
extern void Mat4PerspectiveXAsm(mat4& r,const struct perspectiveMatrix& s);
extern void Mat4PerspectiveXStd(mat4& r,const struct perspectiveMatrix& s);
extern void Mat4ShadowMatrixAsm(mat4& r,const vec3& planeNormal,const float planeOffset,const vec3& lightPos);
extern void Mat4ShadowMatrixStd(mat4& r,const vec3 &planeNormal, const float planeOffset, const vec3 &lightPos);
extern void Mat4MirrorMatrixAsm(mat4& r,const vec3& planeNormal,const float planeOffset);
extern void Mat4MirrorMatrixStd(mat4& r,const vec3 &planeNormal, const float planeOffset);
extern void Mat4CubemapMatrixAsm(mat4& r,const unsigned int face);
extern void Mat4CubemapMatrixStd(mat4& r,const unsigned int face);
extern void Mat4CubemapProjectionMatAsm(mat4& r,const float zNear,const float zFar,const int d3dtype);
extern void Mat4CubemapProjectionMatStd(mat4& r,const float zNear, const float zFar, const int d3dStyle);
extern void Mat4LookAtFPU_Asm(mat4& r,const vec3& from,const vec3& at);
extern void Mat4LookAtStd(mat4& r,const vec3& from,const vec3& at);
extern void Mat4GlToD3dProjectionMatAsm(mat4& r,const mat4& m);
extern void Mat4GlToD3dProjectionMatStd(mat4& r,const mat4& m);

mat4 operator + (const mat4 &m, const mat4 &n);
mat4 operator - (const mat4 &m, const mat4 &n);
mat4 operator - (const mat4 &m);
mat4 operator * (const mat4 &m, const mat4 &n);
vec4 operator * (const mat4 &m, const vec4 &v);
mat4 operator * (const mat4 &m, const float x);

mat4 m4_identity      ();
mat4 m4_transpose     (const mat4 &m);
mat4 m4_scale         (const float x,const float y,const float z);
mat4 m4_rotateX       (const float angle);
mat4 m4_rotateY       (const float angle);
mat4 m4_rotateZ       (const float angle);
mat4 m4_rotateXY      (const float x_angle,const float y_angle);
mat4 m4_rotateXYZ     (const float x_angle,const float y_angle,const float z_angle);
mat4 m4_translate     (const float x,const float y,const float z);
mat4 m4_translate     (const vec3& v);
mat4 m4_ortho         (const struct orthoMatrix& s);
mat4 m4_perspectiveX  (const struct perspectiveMatrix& s);
mat4 m4_shadowMatrix  (const vec3& planeNormal,const float planeOffset,const vec3& lightPos);
mat4 m4_mirrorMatrix  (const vec3& planeNormal,const float planeOffset);
mat4 m4_cubemapMatrix (const unsigned int faces);
mat4 m4_cubemapProjMat(const float zNear,const float zFar,const int d3dtype);
mat4 m4_lookAt        (const vec3& from, const vec3& at);
mat4 m4_GlToD3dProjMat(const mat4& m);

/* ---------------------------------------------
 * Fit t to an S-Curve ? Should probably dump
 * --------------------------------------------- */

inline float sCurve(const float t){
	return t * t * (3 - 2 * t);
}

/** Compute the distance between two nD vectors, where n is [2-4] XXX: This could be optimized */

#define distance(u, v) length((u) - (v))

/* ---------------------------------------------
 * sqr method for undefined squares
 * --------------------------------------------- */

template <typename DATA_TYPE>
inline DATA_TYPE sqr(const DATA_TYPE x)
{
  return x * x;
}

/* ---------------------------------------------
 * Vector min/max methods
 * --------------------------------------------- */

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

// Returns the lesser of two vectors

template <typename DATA_TYPE>
inline DATA_TYPE min(const DATA_TYPE x, const DATA_TYPE y)
{
  return (x < y)? x : y;
}

// Returns the greater of two vectors

template <typename DATA_TYPE>
inline DATA_TYPE max(const DATA_TYPE x, const DATA_TYPE y)
{
  return (x > y)? x : y;
}

vec2 min(const vec2 &u, const vec2 &v);
vec2 max(const vec2 &u, const vec2 &v);
vec3 min(const vec3 &u, const vec3 &v);
vec3 max(const vec3 &u, const vec3 &v);
vec4 min(const vec4 &u, const vec4 &v);
vec4 max(const vec4 &u, const vec4 &v);

/* ---------------------------------------------
 * Clamping methods
 * --------------------------------------------- */

// Clamps x to [lower-upper]

template <typename DATA_TYPE>
inline DATA_TYPE clamp(const DATA_TYPE x, const float lower, const float upper)
{
  return max(min(x, DATA_TYPE(upper)), DATA_TYPE(lower));
}

// Clamps x to [0-1]

#define saturate(x) clamp(x, 0, 1)

/* ---------------------------------------------
 * Sign methods
 * --------------------------------------------- */

int signP(const int x);     /**< Returns +1 if x > 0, -1 otherwise */
int signN(const int x);     /**< Returns +1 if x < 0, -1 otherwise */
int sign(const int x);      
float sign(const float x);
vec2 sign(const vec2 &v);
vec3 sign(const vec3 &v);
vec4 sign(const vec4 &v);

/* ---------------------------------------------
 * Color management methods
 * --------------------------------------------- */

// Convert RGBE format to RGB format

vec3 rgbeToRGB(unsigned char *rgbe);

// Convert 4 floats into a single DWORD value.

vec3 rgbeToRGB(unsigned char *rgbe);
unsigned int toRGBA(const vec4 &u);
unsigned int toBGRA(const vec4 &u);

#endif
