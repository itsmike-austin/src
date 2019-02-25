#ifndef __C_UNALIGNED_VECTOR_H
#define __C_UNALIGNED_VECTOR_H

#ifndef NULL
#include <stdio.h>
#endif

#include <string.h>
#include <assert.h>

#if defined(_WIN32) || defined(_WIN64)
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif

#if (defined(_WIN32) || defined(_WIN64)) && defined(__BUILD_LIBRARY)
#define InterfaceMethod __declspec(dllexport)
#else
#define InterfaceMethod
#endif

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)
#include <FlatBuffer.h>
#endif

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB) || defined(__ADVANCED_UNALIGNED_LIB) || defined(__UNALIGNED_LIB)
#define __USE_SIMD
#endif

#if defined(__cplusplus)

// XXX: THESE NEED TO BE CENTRALIZED

struct orthoMatrix
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

struct perspectiveMatrix
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

#else

struct orthoMatrix
{
  float left,  right;
  float top,   bottom;
  float z_near,z_far;
  unsigned long d3dtype;
};

struct perspectiveMatrix
{
  float fov;
  float width,height;
  float z_near,z_far;
  unsigned long d3dtype;
};

#endif

InterfaceMethod extern float lerp(float fStart,float fEnd,float fDelta);
InterfaceMethod extern float lerpPtr(float* pfStart,float* pfEnd,float* pfDelta);
InterfaceMethod extern float sqr(float fValue);
InterfaceMethod extern float sqrPtr(float* pfValue);

struct _vector2 {
  float x,y;
};

typedef struct _vector2 vec2;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v2 : public FlatElement {

#else

struct v2 {

#endif

  vec2* vec;
  InterfaceMethod v2();
  InterfaceMethod v2(float x,float y);
  InterfaceMethod v2(const v2&);
  InterfaceMethod ~v2();

  InterfaceMethod void  sqr();
  InterfaceMethod void  sqrt();
  InterfaceMethod void  normalize();
  InterfaceMethod float length();
  InterfaceMethod float dot(const v2& v);
  InterfaceMethod void  lerp(const v2& v,const float step);
  InterfaceMethod bool  equals(const v2& v);
  InterfaceMethod bool  notequals(const v2& v);

  InterfaceMethod void sqr(const v2& v);
  InterfaceMethod void sqrt(const v2& v);
  InterfaceMethod void normalize(const v2& v);
  InterfaceMethod void lerp(const v2& u,const v2& v,const float step);

  InterfaceMethod float dot(const vec2& v);
  InterfaceMethod void  sqr(const vec2& v);
  InterfaceMethod void  sqrt(const vec2& v);
  InterfaceMethod void  normalize(const vec2& v);
  InterfaceMethod bool  equals(const vec2& v);
  InterfaceMethod bool  notequals(const vec2& v);
  InterfaceMethod void  lerp(const vec2& v,const float step);
  InterfaceMethod void  lerp(const vec2& u,const vec2& v,const float step);

  InterfaceMethod void copy(const v2& v);

  InterfaceMethod operator vec2()  { return *vec; }
  InterfaceMethod operator vec2*() { return vec;  }

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v2& v);
  InterfaceMethod void operator -= (const v2& v);
  InterfaceMethod void operator *= (const v2& v);
  InterfaceMethod void operator /= (const v2& v);

  InterfaceMethod void operator += (const vec2& u);
  InterfaceMethod void operator -= (const vec2& u);
  InterfaceMethod void operator *= (const vec2& u);
  InterfaceMethod void operator /= (const vec2& u);

  InterfaceMethod vec2* operator->();
  InterfaceMethod v2& operator=(const v2&);
};

InterfaceMethod extern void copy(v2& r,const v2& v);
InterfaceMethod extern void copy_block(v2& r,const v2& v,int32_t iCount);
InterfaceMethod extern void pack_array(v2& r,const vec2** base,int32_t iCount);

InterfaceMethod extern v2 operator + (const v2 &v, const float s);
InterfaceMethod extern v2 operator - (const v2 &v, const float s);
InterfaceMethod extern v2 operator * (const v2 &v, const float s);
InterfaceMethod extern v2 operator * (const float s, const v2 &v);
InterfaceMethod extern v2 operator / (const v2 &v, const float s);
InterfaceMethod extern v2 operator - (const v2 &v);
InterfaceMethod extern v2 operator + (const v2 &u, const v2 &v);
InterfaceMethod extern v2 operator - (const v2 &u, const v2 &v);
InterfaceMethod extern v2 operator * (const v2 &u, const v2 &v);
InterfaceMethod extern v2 operator / (const v2 &u, const v2 &v);
InterfaceMethod extern v2 lerp(const v2 &u, const v2 &v, const float x);
InterfaceMethod extern v2 sqr(const v2 &v);
InterfaceMethod extern v2 sqrt(const v2 &v);
InterfaceMethod extern v2 normalize(const v2 &v);
InterfaceMethod extern float dot(const v2 &u, const v2 &v);
InterfaceMethod extern float length(const v2 &v);

InterfaceMethod extern vec2 operator + (const vec2& u,const float s);
InterfaceMethod extern vec2 operator - (const vec2& u,const float s);
InterfaceMethod extern vec2 operator * (const vec2& u,const float s);
InterfaceMethod extern vec2 operator * (const float s,const vec2& u);
InterfaceMethod extern vec2 operator / (const vec2 &v, const float s);
InterfaceMethod extern vec2 operator - (const vec2 &v);
InterfaceMethod extern vec2 operator + (const vec2 &u, const vec2 &v);
InterfaceMethod extern vec2 operator - (const vec2 &u, const vec2 &v);
InterfaceMethod extern vec2 operator * (const vec2 &u, const vec2 &v);
InterfaceMethod extern vec2 operator / (const vec2 &u, const vec2 &v);
InterfaceMethod extern vec2 lerp(const vec2 &u, const vec2 &v, const float x);
InterfaceMethod extern vec2 sqr(const vec2 &v);
InterfaceMethod extern vec2 sqrt(const vec2 &v);
InterfaceMethod extern vec2 normalize(const vec2& v);
InterfaceMethod extern float dot(const vec2& u, const vec2& v);
InterfaceMethod extern float length(const vec2& v);

InterfaceMethod extern bool operator == (const v2 &u, const v2 &v);
InterfaceMethod extern bool operator != (const v2 &u, const v2 &v);

InterfaceMethod extern bool operator == (const vec2& u,const vec2& v);
InterfaceMethod extern bool operator != (const vec2& u,const vec2& v);

#else

struct v2 {
  vec2* vec;
};

#endif

struct _vector3 {
  float x,y,z,n;
};

typedef struct _vector3 vec3;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v3 : public FlatElement {

#else

struct v3 {

#endif

  vec3* vec;
  InterfaceMethod v3();
  InterfaceMethod v3(float x,float y,float z);
  InterfaceMethod v3(const v3&);
  InterfaceMethod ~v3();

  InterfaceMethod void  sqr();
  InterfaceMethod void  sqrt();
  InterfaceMethod void  normalize();
  InterfaceMethod float length();
  InterfaceMethod float dot(const v3& v);
  InterfaceMethod void  cross(const v3& v);
  InterfaceMethod void  lerp(const v3& v,const float step);
  InterfaceMethod bool  equals(const v3& v);
  InterfaceMethod bool  notequals(const v3& v);

  InterfaceMethod void sqr(const v3& v);
  InterfaceMethod void sqrt(const v3& v);
  InterfaceMethod void normalize(const v3& v);
  InterfaceMethod void cross(const v3& u,const v3& v);
  InterfaceMethod void lerp(const v3& u,const v3& v,const float step);

  InterfaceMethod float dot(const vec3& v);
  InterfaceMethod void  sqr(const vec3& v);
  InterfaceMethod void  sqrt(const vec3& v);
  InterfaceMethod void  normalize(const vec3& v);
  InterfaceMethod void  lerp(const vec3& v,const float step);
  InterfaceMethod void  lerp(const vec3& u,const vec3& v,const float step);

  InterfaceMethod void copy(const v3& v); // XXX: Add this

  InterfaceMethod operator vec3()  { return *vec; }
  InterfaceMethod operator vec3*() { return vec;  }

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v3& v);
  InterfaceMethod void operator -= (const v3& v);
  InterfaceMethod void operator *= (const v3& v);
  InterfaceMethod void operator /= (const v3& v);

  InterfaceMethod void operator += (const vec3& u);
  InterfaceMethod void operator -= (const vec3& u);
  InterfaceMethod void operator *= (const vec3& u);
  InterfaceMethod void operator /= (const vec3& u);

  InterfaceMethod vec3* operator->();
  InterfaceMethod v3& operator=(const v3&);
};

InterfaceMethod extern void copy(v3& r,const v3& v);
InterfaceMethod extern void copy_block(v3& r,const v3& v,int32_t iCount);
InterfaceMethod extern void pack_array(v3& r,const vec3** base,int32_t iCount);

InterfaceMethod extern v3 operator + (const v3& v, const float s);
InterfaceMethod extern v3 operator - (const v3& v, const float s);
InterfaceMethod extern v3 operator * (const v3& v, const float s);
InterfaceMethod extern v3 operator * (const float s, const v3& v);
InterfaceMethod extern v3 operator / (const v3& v, const float s);
InterfaceMethod extern v3 operator - (const v3& v);
InterfaceMethod extern v3 operator + (const v3& u, const v3& v);
InterfaceMethod extern v3 operator - (const v3& u, const v3& v);
InterfaceMethod extern v3 operator * (const v3& u, const v3& v);
InterfaceMethod extern v3 operator / (const v3& u, const v3& v);
InterfaceMethod extern v3 lerp(const v3& u, const v3& v, const float x);
InterfaceMethod extern v3 sqr(const v3& v);
InterfaceMethod extern v3 sqrt(const v3& v);
InterfaceMethod extern v3 normalize(const v3& v);
InterfaceMethod extern v3 cross(const v3& u,const v3& v);
InterfaceMethod extern float dot(const v3& u, const v3& v);
InterfaceMethod extern float length(const v3& v);

InterfaceMethod extern vec3 operator + (const vec3& u,const float s);
InterfaceMethod extern vec3 operator - (const vec3& u,const float s);
InterfaceMethod extern vec3 operator * (const vec3& u,const float s);
InterfaceMethod extern vec3 operator * (const float s,const vec3& u);
InterfaceMethod extern vec3 operator / (const vec3& v, const float s);
InterfaceMethod extern vec3 operator - (const vec3& v);
InterfaceMethod extern vec3 operator + (const vec3& u, const vec3& v);
InterfaceMethod extern vec3 operator - (const vec3& u, const vec3& v);
InterfaceMethod extern vec3 operator * (const vec3& u, const vec3& v);
InterfaceMethod extern vec3 operator / (const vec3& u, const vec3& v);
InterfaceMethod extern vec3 lerp(const vec3& u, const vec3& v, const float x);
InterfaceMethod extern vec3 sqr(const vec3& v);
InterfaceMethod extern vec3 sqrt(const vec3& v);
InterfaceMethod extern vec3 normalize(const vec3& v);
InterfaceMethod extern vec3 cross(const vec3& u,const vec3& v);
InterfaceMethod extern float dot(const vec3& u, const vec3& v);
InterfaceMethod extern float length(const vec3& v);

InterfaceMethod extern bool operator == (const v3 &u, const v3 &v);
InterfaceMethod extern bool operator != (const v3 &u, const v3 &v);

InterfaceMethod extern bool operator == (const vec3& u,const vec3& v);
InterfaceMethod extern bool operator != (const vec3& u,const vec3& v);

#endif

struct _vector4 {
  float x,y,z,w;
};

typedef struct _vector4 vec4;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v4 : public FlatElement {

#else

struct v4 {

#endif

  vec4* vec;
  InterfaceMethod v4();
  InterfaceMethod v4(float x,float y,float z,float w);
  InterfaceMethod v4(const v4&);
  InterfaceMethod ~v4();

  InterfaceMethod void  sqr();
  InterfaceMethod void  sqrt();
  InterfaceMethod void  normalize();
  InterfaceMethod float length();
  InterfaceMethod float dot(const v4& v);
  InterfaceMethod void  cross(const v4& v);
  InterfaceMethod void  lerp(const v4& v,const float step);
  InterfaceMethod bool  equals(const v4& v);
  InterfaceMethod bool  notequals(const v4& v);

  InterfaceMethod void sqr(const v4& v);
  InterfaceMethod void sqrt(const v4& v);
  InterfaceMethod void normalize(const v4& v);
  InterfaceMethod void cross(const v4& u,const v4& v);
  InterfaceMethod void lerp(const v4& u,const v4& v,const float step);

  InterfaceMethod float dot(const vec4& v);
  InterfaceMethod void  sqr(const vec4& v);
  InterfaceMethod void  sqrt(const vec4& v);
  InterfaceMethod void  normalize(const vec4& v);
  InterfaceMethod void  lerp(const vec4& v,const float step);
  InterfaceMethod void  lerp(const vec4& u,const vec4& v,const float step);

  InterfaceMethod void copy(const v4& v);

  InterfaceMethod operator vec4()  { return *vec; }
  InterfaceMethod operator vec4*() { return vec;  }

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v4& v);
  InterfaceMethod void operator -= (const v4& v);
  InterfaceMethod void operator *= (const v4& v);
  InterfaceMethod void operator /= (const v4& v);

  InterfaceMethod void operator += (const vec4& u);
  InterfaceMethod void operator -= (const vec4& u);
  InterfaceMethod void operator *= (const vec4& u);
  InterfaceMethod void operator /= (const vec4& u);

  InterfaceMethod vec4* operator->();
  InterfaceMethod v4& operator=(const v4&);
};

InterfaceMethod extern void copy(v4& r,const v4& v);
InterfaceMethod extern void copy_block(v4& r,const v4& v,int32_t iCount);
InterfaceMethod extern void pack_array(v4& r,const vec4** base,int32_t iCount);

InterfaceMethod extern v4 operator + (const v4& v, const float s);
InterfaceMethod extern v4 operator - (const v4& v, const float s);
InterfaceMethod extern v4 operator * (const v4& v, const float s);
InterfaceMethod extern v4 operator * (const float s, const v4& v);
InterfaceMethod extern v4 operator / (const v4& v, const float s);
InterfaceMethod extern v4 operator - (const v4& v);
InterfaceMethod extern v4 operator + (const v4& u, const v4& v);
InterfaceMethod extern v4 operator - (const v4& u, const v4& v);
InterfaceMethod extern v4 operator * (const v4& u, const v4& v);
InterfaceMethod extern v4 operator / (const v4& u, const v4& v);
InterfaceMethod extern v4 lerp(const v4& u, const v4& v, const float x);
InterfaceMethod extern v4 sqr(const v4& v);
InterfaceMethod extern v4 sqrt(const v4& v);
InterfaceMethod extern v4 normalize(const v4& v);
InterfaceMethod extern v4 cross(const v4& u,const v4& v);
InterfaceMethod extern float dot(const v4& u, const v4& v);
InterfaceMethod extern float length(const v4& v);

InterfaceMethod extern vec4 operator + (const vec4& u,const float s);
InterfaceMethod extern vec4 operator - (const vec4& u,const float s);
InterfaceMethod extern vec4 operator * (const vec4& u,const float s);
InterfaceMethod extern vec4 operator * (const float s,const vec4& u);
InterfaceMethod extern vec4 operator / (const vec4& v, const float s);
InterfaceMethod extern vec4 operator - (const vec4& v);
InterfaceMethod extern vec4 operator + (const vec4& u, const vec4& v);
InterfaceMethod extern vec4 operator - (const vec4& u, const vec4& v);
InterfaceMethod extern vec4 operator * (const vec4& u, const vec4& v);
InterfaceMethod extern vec4 operator / (const vec4& u, const vec4& v);
InterfaceMethod extern vec4 lerp(const vec4& u, const vec4& v, const float x);
InterfaceMethod extern vec4 sqr(const vec4& v);
InterfaceMethod extern vec4 sqrt(const vec4& v);
InterfaceMethod extern vec4 normalize(const vec4& v);
InterfaceMethod extern vec4 cross(const vec4& u,const vec4& v);
InterfaceMethod extern float dot(const vec4& u, const vec4& v);
InterfaceMethod extern float length(const vec4& v);

InterfaceMethod extern bool operator == (const v4 &u, const v4 &v);
InterfaceMethod extern bool operator != (const v4 &u, const v4 &v);

InterfaceMethod extern bool operator == (const vec4& u,const vec4& v);
InterfaceMethod extern bool operator != (const vec4& u,const vec4& v);

#endif

struct _matrix2D {
  float m00,m01,m10,m11;
};

typedef struct _matrix2D mat2;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct m2 : public FlatElement {

#else

struct m2 {

#endif

  mat2* m;
  InterfaceMethod m2();
  InterfaceMethod m2(float m00,float m01,float m10,float m11);
  InterfaceMethod m2(const m2&);
  InterfaceMethod ~m2();

  InterfaceMethod operator mat2*() { return m;  }
  InterfaceMethod operator mat2()  { return *m; }

  InterfaceMethod void identity();  

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);

  InterfaceMethod void operator += (const m2& m);
  InterfaceMethod void operator -= (const m2& m);
  InterfaceMethod void operator *= (const m2& m);

  InterfaceMethod void operator += (const mat2& m);
  InterfaceMethod void operator -= (const mat2& m);
  InterfaceMethod void operator *= (const mat2& m);

  InterfaceMethod mat2* operator->();
  InterfaceMethod m2& operator=(const m2&);
};

InterfaceMethod extern m2 m2identity();
InterfaceMethod extern m2 m2transpose(const m2& m);
InterfaceMethod extern m2 m2rotate(const float angle);
InterfaceMethod extern m2 m2rotate_lh(const float angle);
InterfaceMethod extern m2 m2rotate_rh(const float angle);
InterfaceMethod extern m2 m2scale(const float x_scale,const float y_scale);

InterfaceMethod extern m2 operator + (const m2& m,const float s);
InterfaceMethod extern m2 operator - (const m2& m,const float s);
InterfaceMethod extern m2 operator * (const m2& m,const float s);

InterfaceMethod extern v2 operator * (const m2& m,const v2& v);
InterfaceMethod extern m2 operator - (const m2& m);

InterfaceMethod extern m2 operator + (const m2& m,const m2& n);
InterfaceMethod extern m2 operator - (const m2& m,const m2& n);
InterfaceMethod extern m2 operator * (const m2& m,const m2& n);

InterfaceMethod extern mat2 mat2identity();
InterfaceMethod extern mat2 mat2transpose(const mat2& m);
InterfaceMethod extern mat2 mat2rotate(const float angle);
InterfaceMethod extern mat2 mat2rotate_lh(const float angle);
InterfaceMethod extern mat2 mat2rotate_rh(const float angle);
InterfaceMethod extern mat2 mat2scale(const float x_scale,const float y_scale);

InterfaceMethod extern mat2 operator + (const mat2& m,const float s);
InterfaceMethod extern mat2 operator - (const mat2& m,const float s);
InterfaceMethod extern mat2 operator * (const mat2& m,const float s);

InterfaceMethod extern mat2 operator - (const mat2& m);

InterfaceMethod extern vec2 operator * (const mat2& m,const vec2& v);

InterfaceMethod extern mat2 operator + (const mat2& m,const mat2& n);
InterfaceMethod extern mat2 operator - (const mat2& m,const mat2& n);
InterfaceMethod extern mat2 operator * (const mat2& m,const mat2& n);

#endif

struct _matrix3D {
  float m00,m01,m02,n03,m10,m11,m12,n13,m20,m21,m22,n23;
};

typedef struct _matrix3D mat3;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct m3 : public FlatElement {

#else

struct m3 {

#endif

  mat3* m;
  InterfaceMethod m3();
  InterfaceMethod m3(float m00,float m01,float m02,
     float m10,float m11,float m12,
     float m20,float m21,float m22);
  InterfaceMethod m3(const m3&);
  InterfaceMethod ~m3();

  InterfaceMethod operator mat3*() { return m;  }
  InterfaceMethod operator mat3()  { return *m; }

  InterfaceMethod void identity();

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);

  InterfaceMethod void operator += (const m3& m);
  InterfaceMethod void operator -= (const m3& m);
  InterfaceMethod void operator *= (const m3& m);

  InterfaceMethod void operator += (const mat3& m);
  InterfaceMethod void operator -= (const mat3& m);
  InterfaceMethod void operator *= (const mat3& m);

  InterfaceMethod mat3* operator->();
  InterfaceMethod m3& operator=(const m3&);
};

InterfaceMethod extern m3 m3identity();
InterfaceMethod extern m3 m3inverse(const m3& m);
InterfaceMethod extern m3 m3transpose(const m3& m);

InterfaceMethod extern m3 operator + (const m3& m,const float s);
InterfaceMethod extern m3 operator - (const m3& m,const float s);
InterfaceMethod extern m3 operator * (const m3& m,const float s);

InterfaceMethod extern v3 operator * (const m3& m,const v3& v);

InterfaceMethod extern m3 operator - (const m3& m);

InterfaceMethod extern m3 operator + (const m3& m,const m3& n);
InterfaceMethod extern m3 operator - (const m3& m,const m3& n);
InterfaceMethod extern m3 operator * (const m3& m,const m3& n);

InterfaceMethod extern m3 m3rotate_rhx(const float angle);
InterfaceMethod extern m3 m3rotate_lhx(const float angle);
InterfaceMethod extern m3 m3rotate_rhy(const float angle);
InterfaceMethod extern m3 m3rotate_lhy(const float angle);
InterfaceMethod extern m3 m3rotate_rhz(const float angle);
InterfaceMethod extern m3 m3rotate_lhz(const float angle);

InterfaceMethod extern m3 m3rotate_rhxy(const float x_angle,const float y_angle);
InterfaceMethod extern m3 m3rotate_lhxy(const float x_angle,const float y_angle);
InterfaceMethod extern m3 m3rotate_rhxz(const float x_angle,const float z_angle);
InterfaceMethod extern m3 m3rotate_lhxz(const float x_angle,const float z_angle);
InterfaceMethod extern m3 m3rotate_rhyz(const float y_angle,const float z_angle);
InterfaceMethod extern m3 m3rotate_lhyz(const float y_angle,const float z_angle);

InterfaceMethod extern m3 m3rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle);
InterfaceMethod extern m3 m3rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle);

InterfaceMethod extern m3 m3scale(const float x_scale,const float y_scale,const float z_scale);
InterfaceMethod extern m3 m3scale(const v3& scale);

InterfaceMethod extern mat3 mat3inverse(const mat3& m);
InterfaceMethod extern mat3 mat3transpose(const mat3& m);

InterfaceMethod extern mat3 operator + (const mat3& m,const float s);
InterfaceMethod extern mat3 operator - (const mat3& m,const float s);
InterfaceMethod extern mat3 operator * (const mat3& m,const float s);

InterfaceMethod extern mat3 operator - (const mat3& m);

InterfaceMethod extern vec3 operator * (const mat3& m,const vec3& v);

InterfaceMethod extern mat3 operator + (const mat3& m,const mat3& n);
InterfaceMethod extern mat3 operator - (const mat3& m,const mat3& n);
InterfaceMethod extern mat3 operator * (const mat3& m,const mat3& n);

InterfaceMethod extern mat3 mat3rotate_rhx(const float angle);
InterfaceMethod extern mat3 mat3rotate_lhx(const float angle);
InterfaceMethod extern mat3 mat3rotate_rhy(const float angle);
InterfaceMethod extern mat3 mat3rotate_lhy(const float angle);
InterfaceMethod extern mat3 mat3rotate_rhz(const float angle);
InterfaceMethod extern mat3 mat3rotate_lhz(const float angle);

InterfaceMethod extern mat3 mat3rotate_rhxy(const float x_angle,const float y_angle);
InterfaceMethod extern mat3 mat3rotate_lhxy(const float x_angle,const float y_angle);
InterfaceMethod extern mat3 mat3rotate_rhxz(const float x_angle,const float z_angle);
InterfaceMethod extern mat3 mat3rotate_lhxz(const float x_angle,const float z_angle);
InterfaceMethod extern mat3 mat3rotate_rhyz(const float y_angle,const float z_angle);
InterfaceMethod extern mat3 mat3rotate_lhyz(const float y_angle,const float z_angle);

InterfaceMethod extern mat3 mat3rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle);
InterfaceMethod extern mat3 mat3rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle);

InterfaceMethod extern mat3 mat3scale(const float x_scale,const float y_scale,const float z_scale);
InterfaceMethod extern mat3 mat3scale(vec3& scale);

#endif

struct _matrix4D {
  float m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33;
};

typedef struct _matrix4D mat4;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct m4 : public FlatElement {

#else

struct m4 {

#endif

  mat4* m;
  InterfaceMethod m4();
  InterfaceMethod m4(float m00,float m01,float m02,float m03,
		     float m10,float m11,float m12,float m13,
		     float m20,float m21,float m22,float m23,
		     float m30,float m31,float m32,float m33);
  InterfaceMethod m4(const m4&);
  InterfaceMethod ~m4();

  InterfaceMethod operator mat4*() { return m;  }
  InterfaceMethod operator mat4()  { return *m; }

  InterfaceMethod void identity();

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);

  InterfaceMethod void operator += (const m4& m);
  InterfaceMethod void operator -= (const m4& m);
  InterfaceMethod void operator *= (const m4& m);

  InterfaceMethod void operator += (const mat4& m);
  InterfaceMethod void operator -= (const mat4& m);
  InterfaceMethod void operator *= (const mat4& m);

  InterfaceMethod mat4* operator->();
  InterfaceMethod m4& operator=(const m4&);
};

InterfaceMethod extern m4 operator + (const m4& m,const float s);
InterfaceMethod extern m4 operator - (const m4& m,const float s);
InterfaceMethod extern m4 operator * (const m4& m,const float s);

InterfaceMethod extern v4 operator * (const m4& m,const v4& v);

InterfaceMethod extern m4 operator - (const m4& m);

InterfaceMethod extern m4 operator + (const m4& m,const m4& n);
InterfaceMethod extern m4 operator - (const m4& m,const m4& n);
InterfaceMethod extern m4 operator * (const m4& m,const m4& n);

InterfaceMethod extern m4 m4identity();
// InterfaceMethod extern m4 inverse(const m4& m); XXX: Required method
InterfaceMethod extern m4 transpose(const m4& m);
InterfaceMethod extern m4 lookAt(const v3& from,const v3& at);
InterfaceMethod extern m4 shadow(const v3& planeNormal,const float planeOffset,const v3& lightPos);
InterfaceMethod extern m4 glToD3D(const m4& m);
InterfaceMethod extern m4 lookAt_lh(const v3& eye,const v3& lookAt,const v3& up);
InterfaceMethod extern m4 m4scale(const float x_scale,const float y_scale,const float z_scale);
InterfaceMethod extern m4 m4scale(const v4& scale);

InterfaceMethod extern m4 m4rotate_rhx(const float angle);
InterfaceMethod extern m4 m4rotate_lhx(const float angle);
InterfaceMethod extern m4 m4rotate_rhy(const float angle);
InterfaceMethod extern m4 m4rotate_lhy(const float angle);
InterfaceMethod extern m4 m4rotate_rhz(const float angle);
InterfaceMethod extern m4 m4rotate_lhz(const float angle);

InterfaceMethod extern m4 m4rotate_rhxy(const float x_angle,const float y_angle);
InterfaceMethod extern m4 m4rotate_lhxy(const float x_angle,const float y_angle);
InterfaceMethod extern m4 m4rotate_rhxz(const float x_angle,const float z_angle);
InterfaceMethod extern m4 m4rotate_lhxz(const float x_angle,const float z_angle);
InterfaceMethod extern m4 m4rotate_rhyz(const float y_angle,const float z_angle);
InterfaceMethod extern m4 m4rotate_lhyz(const float y_angle,const float z_angle);

InterfaceMethod extern m4 m4rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle);
InterfaceMethod extern m4 m4rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle);

InterfaceMethod extern m4 m4translate_rh(const float delta_x,const float delta_y,const float delta_z);
InterfaceMethod extern m4 m4translate_lh(const float delta_x,const float delta_y,const float delta_z);

InterfaceMethod extern m4 translate_rh(const v3& v);
InterfaceMethod extern m4 translate_lh(const v3& v);
InterfaceMethod extern m4 translate_rh(const v4& v);
InterfaceMethod extern m4 translate_lh(const v4& v);

InterfaceMethod extern m4 m4ortho(const float left,
				  const float right,
				  const float top,
				  const float bottom,
				  const float zNear,
				  const float zFar,
				  const int32_t d3dFlag);

InterfaceMethod extern m4 m4orthoStruct(const orthoMatrix* s);

InterfaceMethod extern m4 m4perspective(const float    fov,
					const float    width,
					const float    height,
					const float    zNear,
					const float    zFar,
					const uint32_t d3dflag);
InterfaceMethod extern m4 m4perspective(const struct perspectiveMatrix* s);

InterfaceMethod extern m4 m4cubemap(const unsigned int face);
InterfaceMethod extern m4 m4cubemapProjection(const float zNear,
					      const float zFar,
					      const uint32_t d3dflag);

InterfaceMethod extern m3 m3from_m4(const mat4& m);
InterfaceMethod extern m4 m4from_m3(const mat3& m);

InterfaceMethod extern mat4 operator + (const mat4& m,const float s);
InterfaceMethod extern mat4 operator - (const mat4& m,const float s);
InterfaceMethod extern mat4 operator * (const mat4& m,const float s);

InterfaceMethod extern mat4 operator - (const mat4& m);

InterfaceMethod extern vec4 operator * (const mat4& m,const vec4& v);

InterfaceMethod extern mat4 operator + (const mat4& m,const mat4& n);
InterfaceMethod extern mat4 operator - (const mat4& m,const mat4& n);
InterfaceMethod extern mat4 operator * (const mat4& m,const mat4& n);

InterfaceMethod extern mat4 mat4identity();
InterfaceMethod extern mat4 transpose(const mat4& m);
// InterfaceMethod extern mat4 inverse(const mat4& m); XXX: Required method
InterfaceMethod extern mat4 lookAt(const vec3& from,const vec3& at);
InterfaceMethod extern mat4 shadow(const vec3& planeNormal,const float planeOffset,const vec3& lightPos);
InterfaceMethod extern mat4 glToD3D(const mat4& m);
InterfaceMethod extern mat4 lookAt_lh(const vec3& eye,const vec3& lookAt,const vec3& up);
InterfaceMethod extern mat4 mat4scale(const float x_scale,const float y_scale,const float z_scale);
InterfaceMethod extern mat4 mat4scale(const vec4& vScale);

InterfaceMethod extern mat4 mat4rotate_rhx(const float angle);
InterfaceMethod extern mat4 mat4rotate_lhx(const float angle);
InterfaceMethod extern mat4 mat4rotate_rhy(const float angle);
InterfaceMethod extern mat4 mat4rotate_lhy(const float angle);
InterfaceMethod extern mat4 mat4rotate_rhz(const float angle);
InterfaceMethod extern mat4 mat4rotate_lhz(const float angle);

InterfaceMethod extern mat4 mat4rotate_rhxy(const float x_angle,const float y_angle);
InterfaceMethod extern mat4 mat4rotate_lhxy(const float x_angle,const float y_angle);
InterfaceMethod extern mat4 mat4rotate_rhxz(const float x_angle,const float z_angle);
InterfaceMethod extern mat4 mat4rotate_lhxz(const float x_angle,const float z_angle);
InterfaceMethod extern mat4 mat4rotate_rhyz(const float y_angle,const float z_angle);
InterfaceMethod extern mat4 mat4rotate_lhyz(const float y_angle,const float z_angle);

InterfaceMethod extern mat4 mat4rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle);
InterfaceMethod extern mat4 mat4rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle);

InterfaceMethod extern mat4 mat4scale(const float x_scale,const float y_scale,const float z_scale);
InterfaceMethod extern mat4 mat4scale(const vec4& scale);

InterfaceMethod extern mat4 mat4translate_rh(const float delta_x,const float delta_y,const float delta_z);
InterfaceMethod extern mat4 mat4translate_lh(const float delta_x,const float delta_y,const float delta_z);

InterfaceMethod extern mat4 translate_rh(const vec3& v);
InterfaceMethod extern mat4 translate_lh(const vec3& v);
InterfaceMethod extern mat4 translate_rh(const vec4& v);
InterfaceMethod extern mat4 translate_lh(const vec4& v);

InterfaceMethod extern mat4 mat4ortho(const float left,
				      const float right,
				      const float top,
				      const float bottom,
				      const float zNear,
				      const float zFar,
				      const int32_t d3dFlag);

InterfaceMethod extern mat4 mat4orthoStruct(const orthoMatrix* s);

InterfaceMethod extern mat4 mat4perspective(const float    fov,
					    const float    width,
					    const float    height,
					    const float    zNear,
					    const float    zFar,
					    const uint32_t d3dflag);
InterfaceMethod extern mat4 mat4perspective(const struct perspectiveMatrix* s);

InterfaceMethod extern mat4 mat4cubemap(const unsigned int face);
InterfaceMethod extern mat4 mat4cubemapProjection(const float zNear,
						  const float zFar,
						  const uint32_t d3dflag);

InterfaceMethod mat3 mat3from_mat4(const mat4& m);
InterfaceMethod mat4 mat4from_mat3(const mat3& m);

#endif

struct _quaternion {
  float x,y,z,w;
};

typedef struct _quaternion quaternion;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct quat : public FlatElement {

#else

struct quat {

#endif

  quaternion* q;
  InterfaceMethod quat();
  InterfaceMethod quat(float x,float y,float z,float w);
  InterfaceMethod quat(const quat&);
  InterfaceMethod quat(vec4& qp);
  InterfaceMethod ~quat();

  InterfaceMethod operator quaternion*();
  InterfaceMethod operator quaternion();

  InterfaceMethod operator m3();
  InterfaceMethod operator m4();

  InterfaceMethod operator mat3(); // XXX: Needs to return m3&m4 ...
  InterfaceMethod operator mat4();

  InterfaceMethod void inverse();
  InterfaceMethod void normalize();

  InterfaceMethod void operator += (const quat& qr);
  InterfaceMethod void operator *= (const quat& qr);

  InterfaceMethod quaternion* operator->();
  InterfaceMethod quat& operator=(const quat&);
};

InterfaceMethod extern quat operator + (const quat& q,const quat& p);
InterfaceMethod extern quat operator * (const quat& q,const quat& p);

InterfaceMethod extern float dot(const quat& q,const quat& p);
InterfaceMethod extern quat  normalize(const quat& q);
InterfaceMethod extern quat  inverse(const quat& q);
InterfaceMethod extern quat  quatFromAxis(const vec3& v,const float angle);
InterfaceMethod extern m4    quatToM4(const quat& q);
InterfaceMethod extern quat  quatFromM3(const m3& m);
InterfaceMethod extern quat  quatFromM4(const m4& m);
InterfaceMethod extern quat  quatSlerp(const float s,const quat& q,const quat& p);

#if 0
InterfaceMethod extern quaternion operator ! (const quaternion& q);
InterfaceMethod extern quaternion operator ~ (const quaternion& q);
#endif

InterfaceMethod extern quaternion operator + (const quaternion& q,const quaternion& p);
InterfaceMethod extern quaternion operator * (const quaternion& q,const quaternion& p);

InterfaceMethod extern float dot(const quaternion& q,const quaternion& p);
InterfaceMethod extern quaternion normalize(const quaternion& q);
InterfaceMethod extern quaternion inverse(const quaternion& q);
InterfaceMethod extern quaternion quaternionFromAxis(const vec3* v,const float angle);
InterfaceMethod extern mat4       quatToMat4(const quaternion& q);
InterfaceMethod extern quaternion quatFromMat3(const mat3& m);
InterfaceMethod extern quaternion quatFromMat4(const mat4& m);
InterfaceMethod extern quaternion quatSlerp(const float s,const quaternion& q,const quaternion& p);

#endif

#if defined(__USE_SIMD)
#include <Vecasm.h>
#else
#include <Vecstd.h>
#endif

typedef void (*Rotate_2D )(mat2* r,const float angle);
typedef void (*Rotate1_3D)(mat3* r,const float angle);
typedef void (*Rotate2_3D)(mat3* r,const float angle1,const float angle2);
typedef void (*Rotate3_3D)(mat3* r,const float angle1,const float angle2,const float angle3);
typedef void (*Rotate1_4D)(mat4* r,const float angle);
typedef void (*Rotate2_4D)(mat4* r,const float angle1,const float angle2);
typedef void (*Rotate3_4D)(mat4* r,const float angle1,const float angle2,const float angle3);
typedef void (*Trans3_4D) (mat4* r,const float delX,const float delY,const float delZ);
typedef void (*Trans3_v3) (mat4* r,const vec3* u);
typedef void (*Trans3_v4) (mat4* r,const vec4* u);

struct _RotationInterface {
  Rotate_2D  rotate;
  Rotate1_3D rotate3X;
  Rotate1_3D rotate3Y;
  Rotate1_3D rotate3Z;
  Rotate2_3D rotate3XY;
  Rotate2_3D rotate3XZ;
  Rotate2_3D rotate3YZ;
  Rotate3_3D rotate3XYZ;
  Rotate1_4D rotate4X;
  Rotate1_4D rotate4Y;
  Rotate1_4D rotate4Z;
  Rotate2_4D rotate4XY;
  Rotate2_4D rotate4XZ;
  Rotate2_4D rotate4YZ;
  Rotate3_4D rotate4XYZ;
  Trans3_4D  translateXYZ;
  Trans3_v3  translateVec3;
  Trans3_v4  translateVec4;
};

struct v2buf;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v2array : public FlatBuffer {

#else

struct v2array {

#endif

  vec2* m_Vec2Array;
  int   m_ArrayCount;

  InterfaceMethod v2array();
  InterfaceMethod v2array(int iCount);
  InterfaceMethod v2array(float x,float y);
  InterfaceMethod v2array(int iCount,vec2* pVecArray);
  InterfaceMethod v2array(const v2array&);
  InterfaceMethod v2array(v2buf&);
  InterfaceMethod ~v2array();

  InterfaceMethod operator vec2*() { return m_Vec2Array; }

  InterfaceMethod int length();
  InterfaceMethod int size();

  InterfaceMethod void add(v2& v);
  InterfaceMethod void add(vec2& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v2& v);
  InterfaceMethod void operator -= (const v2& v);
  InterfaceMethod void operator *= (const v2& v);
  InterfaceMethod void operator /= (const v2& v);

  InterfaceMethod void operator += (const vec2& u);
  InterfaceMethod void operator -= (const vec2& u);
  InterfaceMethod void operator *= (const vec2& u);
  InterfaceMethod void operator /= (const vec2& u);

  InterfaceMethod void operator += (struct v2array& va);
  InterfaceMethod void operator -= (struct v2array& va);
  InterfaceMethod void operator *= (struct v2array& va);
  InterfaceMethod void operator /= (struct v2array& va);

  InterfaceMethod void operator *= (m2& m);
  InterfaceMethod void operator *= (mat2& m);

  InterfaceMethod vec2& operator[](int iItem);
  InterfaceMethod v2array& operator=(v2buf& v);

  InterfaceMethod v2array& operator=(const v2array&);

  InterfaceMethod void sqr();
  InterfaceMethod void sqr(const v2array& va);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(const v2array& va);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(const v2array&);

  InterfaceMethod void lerp(const v2array& va,const float step);
  InterfaceMethod void lerp(const v2array& va,const v2array& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v2array& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
};

#endif

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v2buf : public FlatBuffer {

#else

struct v2buf {

#endif

  // Reconstruct this with void* m_Vec2Array
  // and calculate the offset in the various methods
  // This should require no changes to the assembler
  // or 'c' methods. XXX: (In the morning ... too tired right now).
  //

  void* m_VecArray;
  int   m_ArrayCount;
  int   m_VecOffset;
  int   m_ElementSize;

  InterfaceMethod v2buf(int iVecOffset);
  InterfaceMethod v2buf(int iVecOffset,float x,float y);
  InterfaceMethod v2buf(int iCount,int iSize,int iVecOffset,vec2* pVecArray);
  InterfaceMethod v2buf(const v2buf&);
  InterfaceMethod ~v2buf();

  InterfaceMethod operator vec2*() { return (vec2*)m_VecArray; }

  InterfaceMethod int   length();
  InterfaceMethod int   size();
  InterfaceMethod int   offset();
  InterfaceMethod void* vptr();

  InterfaceMethod void add(v2& v);
  InterfaceMethod void add(vec2& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v2& v);
  InterfaceMethod void operator -= (const v2& v);
  InterfaceMethod void operator *= (const v2& v);
  InterfaceMethod void operator /= (const v2& v);

  InterfaceMethod void operator += (const vec2& u);
  InterfaceMethod void operator -= (const vec2& u);
  InterfaceMethod void operator *= (const vec2& u);
  InterfaceMethod void operator /= (const vec2& u);

  InterfaceMethod void operator += (struct v2buf& va);
  InterfaceMethod void operator -= (struct v2buf& va);
  InterfaceMethod void operator *= (struct v2buf& va);
  InterfaceMethod void operator /= (struct v2buf& va);

  InterfaceMethod void operator *= (m2& m);
  InterfaceMethod void operator *= (mat2& m);

  InterfaceMethod vec2& operator[](int iItem);
  InterfaceMethod v2buf& operator=(const v2buf&);

  InterfaceMethod void sqr();
  InterfaceMethod void sqr(const v2buf& va);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(const v2buf& va);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(const v2buf&);

  InterfaceMethod void lerp(const v2buf& va,const float step);
  InterfaceMethod void lerp(const v2buf& va,const v2buf& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v2buf& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
};

#endif

struct v3buf;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v3array : public FlatBuffer {

#else

struct v3array {

#endif

  void* m_VecArray;
  int   m_ArrayCount;

  InterfaceMethod v3array();
  InterfaceMethod v3array(int iCount);
  InterfaceMethod v3array(float x,float y,float z);
  InterfaceMethod v3array(int iCount,vec3* pVecArray);
  InterfaceMethod v3array(v3buf&);
  InterfaceMethod v3array(const v3array&);
  InterfaceMethod ~v3array();

  InterfaceMethod operator vec3*() { return (vec3*)m_VecArray; }

  InterfaceMethod int   length();
  InterfaceMethod int   size();

  InterfaceMethod void add(v3& v);
  InterfaceMethod void add(vec3& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v3& v);
  InterfaceMethod void operator -= (const v3& v);
  InterfaceMethod void operator *= (const v3& v);
  InterfaceMethod void operator /= (const v3& v);

  InterfaceMethod void operator += (const vec3& u);
  InterfaceMethod void operator -= (const vec3& u);
  InterfaceMethod void operator *= (const vec3& u);
  InterfaceMethod void operator /= (const vec3& u);

  InterfaceMethod void operator += (struct v3array& va);
  InterfaceMethod void operator -= (struct v3array& va);
  InterfaceMethod void operator *= (struct v3array& va);
  InterfaceMethod void operator /= (struct v3array& va);

  InterfaceMethod void operator *= (m3& m);
  InterfaceMethod void operator *= (mat3& m);

  InterfaceMethod vec3& operator[](int iItem);
  InterfaceMethod v3array& operator=(v3buf& v);

  InterfaceMethod v3array& operator=(const v3array&);

  InterfaceMethod void cross(const v3array&);
  InterfaceMethod void sqr();
  InterfaceMethod void sqr(v3array& va);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(v3array& va);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(v3array& va);

  InterfaceMethod void lerp(const v3array& va,const float step);
  InterfaceMethod void lerp(const v3array& va,const v3array& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v3array& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
#if 0
  InterfaceMethod void dot(float** fppArray,int32_t* ipArrayLength,const v3array& va);
  InterfaceMethod void length(float** fppArray,int32_t* ipArrayLength);
#endif
};

#endif

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v3buf : public FlatBuffer {

#else

struct v3buf {

#endif

  void* m_VecArray;
  int   m_ArrayCount;
  int   m_VecOffset;
  int   m_ElementSize;

  InterfaceMethod v3buf(int iVecOffset);
  InterfaceMethod v3buf(int iVecOffset,float x,float y,float z);
  InterfaceMethod v3buf(int iCount,int iSize,int iVecOffset,vec3* pVecArray);
  InterfaceMethod v3buf(const v3buf&);
  InterfaceMethod ~v3buf();

  InterfaceMethod operator vec3*() { return (vec3*)((char*)m_VecArray + m_VecOffset); }

  InterfaceMethod int   length();
  InterfaceMethod int   size();
  InterfaceMethod int   offset();
  InterfaceMethod void* vptr();

  InterfaceMethod void add(v3& v);
  InterfaceMethod void add(vec3& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v3& v);
  InterfaceMethod void operator -= (const v3& v);
  InterfaceMethod void operator *= (const v3& v);
  InterfaceMethod void operator /= (const v3& v);

  InterfaceMethod void operator += (const vec3& u);
  InterfaceMethod void operator -= (const vec3& u);
  InterfaceMethod void operator *= (const vec3& u);
  InterfaceMethod void operator /= (const vec3& u);

  InterfaceMethod void operator += (struct v3buf& va);
  InterfaceMethod void operator -= (struct v3buf& va);
  InterfaceMethod void operator *= (struct v3buf& va);
  InterfaceMethod void operator /= (struct v3buf& va);

  InterfaceMethod void operator *= (m3& m);
  InterfaceMethod void operator *= (mat3& m);

  InterfaceMethod vec3& operator[](int iItem);
  InterfaceMethod v3buf& operator=(const v3buf&);

  InterfaceMethod void cross(const v3buf&);
  InterfaceMethod void sqr();
  InterfaceMethod void sqr(v3buf&);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(v3buf&);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(v3buf&);

  InterfaceMethod void lerp(const v3buf& va,const float step);
  InterfaceMethod void lerp(const v3buf& va,const v3buf& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v3buf& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
};

#endif

struct v4buf;

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v4array : public FlatBuffer {

#else

struct v4array {

#endif

  void* m_VecArray;
  int   m_ArrayCount;

  InterfaceMethod v4array();
  InterfaceMethod v4array(int iCount);
  InterfaceMethod v4array(float x,float y,float z,float w);
  InterfaceMethod v4array(int iCount,vec4* pVecArray);
  InterfaceMethod v4array(v4buf&);
  InterfaceMethod v4array(const v4array&);
  InterfaceMethod ~v4array();

  InterfaceMethod operator vec4*() { return (vec4*)m_VecArray; }

  InterfaceMethod int   length();
  InterfaceMethod int   size();

  InterfaceMethod void add(v4& v);
  InterfaceMethod void add(vec4& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v4& v);
  InterfaceMethod void operator -= (const v4& v);
  InterfaceMethod void operator *= (const v4& v);
  InterfaceMethod void operator /= (const v4& v);

  InterfaceMethod void operator += (const vec4& u);
  InterfaceMethod void operator -= (const vec4& u);
  InterfaceMethod void operator *= (const vec4& u);
  InterfaceMethod void operator /= (const vec4& u);

  InterfaceMethod void operator += (struct v4array& va);
  InterfaceMethod void operator -= (struct v4array& va);
  InterfaceMethod void operator *= (struct v4array& va);
  InterfaceMethod void operator /= (struct v4array& va);

  InterfaceMethod void operator *= (m4& m);
  InterfaceMethod void operator *= (mat4& m);

  InterfaceMethod vec4& operator[](int iItem);
  InterfaceMethod v4array& operator=(v4buf& v);
  InterfaceMethod v4array& operator=(const v4array&);

  InterfaceMethod void cross(const v4array&);
  InterfaceMethod void sqr();
  InterfaceMethod void sqr(v4array& va);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(v4array& va);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(v4array& va);

  InterfaceMethod void lerp(const v4array& va,const float step);
  InterfaceMethod void lerp(const v4array& va,const v4array& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v4array& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
};

#endif

#if defined(__cplusplus)

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

struct v4buf : public FlatBuffer {

#else

struct v4buf {

#endif

  void* m_VecArray;
  int   m_ArrayCount;
  int   m_VecOffset;
  int   m_ElementSize;

  InterfaceMethod v4buf(int iSize,int iVec2Offset);
  InterfaceMethod v4buf(int iSize,int iVec2Offset,float x,float y,float z,float w);
  InterfaceMethod v4buf(int iCount,int iVec2Offset,int iSize,vec4* pVecArray);
  InterfaceMethod v4buf(const v4buf&);
  InterfaceMethod ~v4buf();

  InterfaceMethod operator vec4*() { return (vec4*)((char*)m_VecArray + m_VecOffset); }

  InterfaceMethod int   length();
  InterfaceMethod int   size();
  InterfaceMethod int   offset();
  InterfaceMethod void* vptr();

  InterfaceMethod void add(v4& v);
  InterfaceMethod void add(vec4& v);

  InterfaceMethod void operator += (const float s);
  InterfaceMethod void operator -= (const float s);
  InterfaceMethod void operator *= (const float s);
  InterfaceMethod void operator /= (const float s);

  InterfaceMethod void operator += (const v4& v);
  InterfaceMethod void operator -= (const v4& v);
  InterfaceMethod void operator *= (const v4& v);
  InterfaceMethod void operator /= (const v4& v);

  InterfaceMethod void operator += (const vec4& u);
  InterfaceMethod void operator -= (const vec4& u);
  InterfaceMethod void operator *= (const vec4& u);
  InterfaceMethod void operator /= (const vec4& u);

  InterfaceMethod void operator += (struct v4buf& va);
  InterfaceMethod void operator -= (struct v4buf& va);
  InterfaceMethod void operator *= (struct v4buf& va);
  InterfaceMethod void operator /= (struct v4buf& va);

  InterfaceMethod void operator *= (m4& m);
  InterfaceMethod void operator *= (mat4& m);

  InterfaceMethod vec4& operator[](int iItem);
  InterfaceMethod v4buf& operator=(const v4buf&);

  InterfaceMethod void cross(const v4buf& va);
  InterfaceMethod void sqr();
  InterfaceMethod void sqr(v4buf& va);
  InterfaceMethod void sqrt();
  InterfaceMethod void sqrt(v4buf& va);
  InterfaceMethod void normalize();
  InterfaceMethod void normalize(v4buf& va);

  InterfaceMethod void lerp(const v4buf& va,const float step);
  InterfaceMethod void lerp(const v4buf& va,const v4buf& vb,const float step);

  InterfaceMethod void dot(float* fpArray,const int32_t iArrayLength,const v4buf& va);
  InterfaceMethod void length(float* fpArray,const int32_t iArrayLength);
};

#endif

#endif

