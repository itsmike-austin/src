#include <Vector.h>

// ---------------------------------------------------------------
// General floating point functions
// ---------------------------------------------------------------

float lerp(const float u, const float v, const float x)
{
  return FloatLerp(u,v,x);
}

float lerp_ptr(const float *pu,const float *pv,const float *px)
{
  return FloatLerpPtr(pu,pv,px);
}

float sqr(const float x)
{
  return FloatSqr(x);
}

float sqr_ptr(const float* px)
{
  return FloatSqrPtr(px);
}

// ---------------------------------------------------------------
// V2 Constructor Methods
// ---------------------------------------------------------------

v2::v2() : FlatElement(8,16),vec((vec2*)getAlignedBuffer()) {}

v2::v2(float x,float y) : FlatElement(8,16),vec((vec2*)getAlignedBuffer())
{
  vec->x = x;
  vec->y = y;
}

#if 0
operator v2::vec2()  { return *vec; }
operator v2::vec2*() { return  vec; }
#endif

// ---------------------------------------------------------------
// Internal V2 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

void v2::operator += (const float s) { Vec2AddFloat(vec,vec,s);      }
void v2::operator -= (const float s) { Vec2SubtractFloat(vec,vec,s); }
void v2::operator *= (const float s) { Vec2MultiplyFloat(vec,vec,s); }
void v2::operator /= (const float s) { Vec2DivideFloat(vec,vec,s);   }

void v2::operator += (const v2 &v) { Vec2Add(vec,vec,v.vec);      }
void v2::operator -= (const v2 &v) { Vec2Subtract(vec,vec,v.vec); }
void v2::operator *= (const v2 &v) { Vec2Multiply(vec,vec,v.vec); }
void v2::operator /= (const v2 &v) { Vec2Divide(vec,vec,v.vec);   }

void v2::copy(const v2& v) { Vec2Copy(vec,v.vec); }

// ---------------------------------------------------------------
// External V2 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

// Simple Array Wrapper Methods
//

void copy(v2& r,const v2& v)
{
  Vec2Copy(r.vec,v.vec);
}

void copy_block(v2& r,const v2& v,int32_t iCount)
{
  Vec2CopyBlock(r.vec,v.vec,iCount);
}

void pack_array(v2& r,const vec2** base,int32_t iCount)
{
  BuildVec2PackedArray(r.vec,base,iCount);
}

// Arithmetic Operations
//

v2 operator + (const v2 &v, const float s)
{
  v2 r;
  Vec2AddFloat(r.vec,v.vec,s);
  return r;
}

v2 operator - (const v2 &v, const float s)
{
  v2 r;
  Vec2SubtractFloat(r.vec,v.vec,s);
  return r;
}

v2 operator * (const v2 &v, const float s)
{
  v2 r;
  Vec2MultiplyFloat(r.vec,v.vec,s);
  return r;
}

v2 operator * (const float s, const v2 &v)
{
  v2 r;
  Vec2MultiplyFloat(r.vec,v.vec,s);
  return r;
}

v2 operator / (const v2 &v, const float s)
{
  v2 r;
  Vec2DivideFloat(r.vec,v.vec,s);
  return r;
}

v2 operator - (const v2 &v)
{
  v2 r;
  Vec2Negate(r.vec,v.vec);
  return r;
}

v2 operator + (const v2 &u, const v2 &v)
{
  v2 r;
  Vec2Add(r.vec,u.vec,v.vec);
  return r;
}

v2 operator - (const v2 &u, const v2 &v)
{
  v2 r;
  Vec2Subtract(r.vec,u.vec,v.vec);
  return r;
}

v2 operator * (const v2 &u, const v2 &v)
{
  v2 r;
  Vec2Multiply(r.vec,u.vec,v.vec);
  return r;
}

v2 operator / (const v2 &u, const v2 &v)
{
  v2 r;
  Vec2Divide(r.vec,u.vec,v.vec);
  return r;
}

bool operator == (const v2 &u, const v2 &v)
{
  int32_t iFlag;
  Vec2Equals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

bool operator != (const v2 &u, const v2 &v)
{
  int32_t iFlag;
  Vec2NotEquals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

v2 lerp(const v2 &u, const v2 &v, const float x)
{
  v2 r;
  Vec2Lerp(r.vec,u.vec,v.vec,x);
  return r;
}

v2 sqr(const v2 &v)
{
  v2 r;
  Vec2Sqr(r.vec,v.vec);
  return r;
}

v2 normalize(const v2 &v)
{
  v2 r;
  Vec2Normalize(r.vec,v.vec);
  return r;
}

float dot(const v2 &u, const v2 &v)
{
  float r;
  Vec2Dot(&r,u.vec,v.vec);
  return r;
}

float length(const v2 &v)
{
  float r;
  Vec2Length(&r,v.vec);
  return r;
}

// ---------------------------------------------------------------
// vec2Array Methods
// ---------------------------------------------------------------

vec2array::vec2array() : FlatBuffer(8,16,1),v2arr((v2*)getAlignedPtr()),iCount(1)
{
  assert(NULL != v2arr);
}

vec2array::vec2array(float x,float y) : FlatBuffer(8,16,1),v2arr((v2*)getAlignedPtr()),iCount(1)
{
  assert(NULL != v2arr);
  v2arr[0].vec->x = x;
  v2arr[0].vec->y = y;
}

vec2array::vec2array(int iElements) : FlatBuffer(8,16,iElements),v2arr((v2*)getAlignedPtr()),iCount(iElements)
{
  assert(NULL != v2arr);
}

vec2array::vec2array(vec2& v) : FlatBuffer(8,16,1),v2arr((v2*)getAlignedPtr()),iCount(1)
{
  assert(NULL != v2arr);
  v2arr[0].vec->x = v.x;
  v2arr[0].vec->y = v.y;
}

vec2array::~vec2array()
{
  if ( iCount > 1 )
    delete [] v2arr;
  else
    delete v2arr;

  v2arr = NULL;
  iCount = 0;
}

void vec2array::put(vec2& v)
{
  add(m_ElementCount,(char*)&v);
}

void vec2array::put(int iPosition,vec2& v)
{
  add(iPosition,(char*)&v);
}

void* vec2array::get(int iElement)
{
  return FlatBuffer::get(iElement);
}

vec2& vec2array::operator[](int iElement)
{
  vec2* v;
  v = (vec2*)FlatBuffer::get(iElement);
  return *v;
}

// ---------------------------------------------------------------
// V3 Contructor and Internal Methods
// ---------------------------------------------------------------

v3::v3() : FlatElement(16,16),vec((vec3*)getAlignedBuffer()) {}

v3::v3(vec2& v,float z) : FlatElement(16,16),vec((vec3*)getAlignedBuffer())
{
  vec->x = v.x;
  vec->y = v.y;
  vec->z = z;
}

v3::v3(float x,float y,float z) : FlatElement(16,16),vec((vec3*)getAlignedBuffer())
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->n = 0.0f;
}

// ---------------------------------------------------------------
// Internal V3 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

void v3::operator += (const float s)
{
  Vec3AddFloat(vec,vec,s);
}

void v3::operator -= (const float s)
{
  Vec3SubtractFloat(vec,vec,s);
}

void v3::operator *= (const float s)
{
  Vec3MultiplyFloat(vec,vec,s);
}

void v3::operator /= (const float s)
{
  Vec3DivideFloat(vec,vec,s);
}

void v3::operator += (const v3& v)
{
  Vec3Add(vec,vec,v.vec);
}

void v3::operator -= (const v3& v)
{
  Vec3Subtract(vec,vec,v.vec);
}

void v3::operator *= (const v3& v)
{
  Vec3Multiply(vec,vec,v.vec);
}

void v3::operator /= (const v3& v)
{
  Vec3Divide(vec,vec,v.vec);
}

// ---------------------------------------------------------------
// External V3 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

// Simple Array Wrapper Methods
//

void copy(v3& r,const v3& v)
{
  Vec3Copy(r.vec,v.vec);
}

void copy_block(v3& r,v3& v,int32_t iCount)
{
  Vec3CopyBlock(r.vec,v.vec,iCount);
}

void pack_array(v3& r,const vec3** pSrc,int32_t iCount)
{
  BuildVec3PackedArray(r.vec,pSrc,iCount);
}

// External operator methods
//

v3 operator + (const float s, const v3& v)
{
  v3 r;
  Vec3AddFloat(r.vec,v.vec,s);
  return r;
}

v3 operator + (const v3& v, const float s)
{
  v3 r;
  Vec3AddFloat(r.vec,v.vec,s);
  return r;
}

v3 operator - (const v3& v, const float s)
{
  v3 r;
  Vec3SubtractFloat(r.vec,v.vec,s);
  return r;
}

v3 operator - (const float s, const v3& v)
{
  v3 r;
  Vec3SubtractFloat(r.vec,v.vec,s);
  return r;
}

v3 operator * (const float s, const v3& v)
{
  v3 r;
  Vec3MultiplyFloat(r.vec,v.vec,s);
  return r;
}

v3 operator * (const v3& v, const float s)
{
  v3 r;
  Vec3MultiplyFloat(r.vec,v.vec,s);
  return r;
}

v3 operator / (const v3& v, const float s)
{
  v3 r;
  Vec3DivideFloat(r.vec,v.vec,s);
  return r;
}

v3 operator + (const v3& u, const v3& v)
{
  v3 r;
  Vec3Add(r.vec,u.vec,v.vec);
  return r;
}

v3 operator - (const v3& u, const v3& v)
{
  v3 r;
  Vec3Subtract(r.vec,u.vec,v.vec);
  return r;
}

v3 operator - (const v3& v)
{
  v3 r;
  Vec3Negate(r.vec,v.vec);
  return r;
}

v3 operator * (const v3& u, const v3& v)
{
  v3 r;
  Vec3Multiply(r.vec,u.vec,v.vec);
  return r;
}

v3 operator / (const v3& u, const v3& v)
{
  v3 r;
  Vec3Divide(r.vec,u.vec,v.vec);
  return r;
}

bool operator == (const v3& u,const v3& v)
{
  int32_t iFlag;
  Vec3Equals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

bool operator != (const v3& u,const v3& v)
{
  int32_t iFlag;
  Vec3NotEquals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

v3 lerp(const v3 &u, const v3 &v, const float x)
{
  v3 r;
  Vec3Lerp(r.vec,u.vec,v.vec,x);
  return r;
}

v3 sqr(const v3 &v)
{
  v3 r;
  Vec3Sqr(r.vec,v.vec);
  return r;
}

v3 normalize(const v3 &v)
{
  v3 r;
  Vec3Normalize(r.vec,v.vec);
  return r;
}

v3 cross(const v3 &u, const v3 &v)
{
  v3 r;
  Vec3Cross(r.vec,u.vec,v.vec);
  return r;
}

float dot(const v3& u, const v3& v)
{
  float r;
  Vec3Dot(&r,u.vec,v.vec);
  return r;
}

float length(const v3 &v)
{
  float r;
  Vec3Length(&r,v.vec);
  return r;
}

// ---------------------------------------------------------------
// V4 Constructor and internal management methods
// ---------------------------------------------------------------

v4::v4() : FlatElement(16,16),vec((vec4*)getAlignedBuffer())
{
  vec->x = 0.0f;
  vec->y = 0.0f;
  vec->z = 0.0f;
  vec->w = 0.0f;
}

v4::v4(vec2& v0,vec2& v1) : FlatElement(16,16),vec((vec4*)getAlignedBuffer())
{
  vec->x = v0.x;
  vec->y = v0.y;
  vec->z = v1.x;
  vec->w = v1.y;
}

v4::v4(vec3& v,float w) : FlatElement(16,16),vec((vec4*)getAlignedBuffer())
{
  vec->x = v.x;
  vec->y = v.y;
  vec->z = v.z;
  vec->w = w;
}

v4::v4(float x,float y,float z,float w) : FlatElement(16,16),vec((vec4*)getAlignedBuffer())
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}

// ---------------------------------------------------------------
// Internal V4 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

void v4::operator += (const float s)
{
  Vec4AddFloat(vec,vec,s);
}

void v4::operator -= (const float s)
{
  Vec4SubtractFloat(vec,vec,s);
}

void v4::operator *= (const float s)
{
  Vec4MultiplyFloat(vec,vec,s);
}

void v4::operator /= (const float s)
{
  Vec4DivideFloat(vec,vec,s);
}

void v4::operator += (const v4& v)
{
  Vec4Add(vec,vec,v.vec);
}

void v4::operator -= (const v4& v)
{
  Vec4Subtract(vec,vec,v.vec);
}

void v4::operator *= (const v4& v)
{
  Vec4Multiply(vec,vec,v.vec);
}

void v4::operator /= (const v4& v)
{
  Vec4Divide(vec,vec,v.vec);
}

// ---------------------------------------------------------------
// External V2 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

// Simple Array Wrapper Methods
//

void copy(v4& r,const v4& v)
{
  Vec4Copy(r.vec,v.vec);
}

void copy_block(v4& r,const v4& v,int32_t iCount)
{
  Vec4CopyBlock(r.vec,v.vec,iCount);
}

void pack_array(v4& r,const vec4** base,int32_t iCount)
{
  BuildVec4PackedArray(r.vec,base,iCount);
}

// Arithmetic Operations
//

v4 operator + (const v4& v,const float s)
{
  v4 r;
  Vec4AddFloat(r.vec,v.vec,s);
  return r;
}

v4 operator + (const float s,const v4& v)
{
  v4 r;
  Vec4AddFloat(r.vec,v.vec,s);
  return r;
}

v4 operator - (const v4& v,const float s)
{
  v4 r;
  Vec4SubtractFloat(r.vec,v.vec,s);
  return r;
}

v4 operator - (const float s,const v4& v)
{
  v4 r;
  Vec4SubtractFloat(r.vec,v.vec,s);
  return r;
}

v4 operator * (const v4& u,const float s)
{
  v4 r;
  Vec4MultiplyFloat(r.vec,u.vec,s);
  return r;
}

v4 operator * (const float s,const v4& v)
{
  v4 r;
  Vec4MultiplyFloat(r.vec,v.vec,s);
  return r;
}

v4 operator / (const v4& v,const float s)
{
  v4 r;
  Vec4DivideFloat(r.vec,v.vec,s);
  return r;
}

v4 operator + (const v4& u,const v4& v)
{
  v4 r;
  Vec4Add(r.vec,u.vec,v.vec);
  return r;
}

v4 operator - (const v4& u,const v4& v)
{
  v4 r;
  Vec4Subtract(r.vec,u.vec,v.vec);
  return r;
}

v4 operator - (const v4& v)
{
  v4 r;
  Vec4Negate(r.vec,v.vec);
  return r;
}

v4 operator * (const v4& u,const v4& v)
{
  v4 r;
  Vec4Multiply(r.vec,u.vec,v.vec);
  return r;
}

v4 operator / (const v4& u,const v4& v)
{
  v4 r;
  Vec4Divide(r.vec,u.vec,v.vec);
  return r;
}

bool operator == (const v4 &u, const v4 &v)
{
  int32_t iFlag;
  Vec4Equals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

bool operator != (const v4 &u, const v4 &v)
{
  int32_t iFlag;
  Vec4NotEquals(&iFlag,u.vec,v.vec);
  return (iFlag ? true : false);
}

v4 lerp(const v4& u, const v4 &v, const float x)
{
  v4 r;
  Vec4Lerp(r.vec,u.vec,v.vec,x);
  return r;
}

v4 sqr(const v4& v)
{
  v4 r;
  Vec4Sqr(r.vec,v.vec);
  return r;
}

v4 normalize(const v4& v)
{
  v4 r;
  Vec4Normalize(r.vec,v.vec);
  return r;
}

v4 cross(const v4 &u,const v4 &v)
{
  v4 r;
  Vec4Cross(r.vec,u.vec,v.vec);
  return r;
}

float dot(const v4 &u, const v4 &v)
{
  float r;
  Vec4Dot(&r,u.vec,v.vec);
  return r;
}

float length(const v4 &v)
{
  float r;
  Vec4Length(&r,v.vec);
  return r;
}

// ---------------------------------------------------------------
// M2 Constructor and internal management methods
// ---------------------------------------------------------------

m2::m2() :
  FlatElement(16,16),
  mat((mat2*)getAlignedBuffer()),
  hand(LeftHand),
  Rotate(Mat2RotateLH)
{
  mat->m00 = 1.0f;
  mat->m01 = 0.0f;
  mat->m10 = 0.0f;
  mat->m11 = 1.0f;
}

m2::m2(vec2& row0,vec2& row1) :
  FlatElement(16,16),
  mat((mat2*)getAlignedBuffer()),
  hand(LeftHand),
  Rotate(Mat2RotateLH)
{
  mat->m00 = row0.x;
  mat->m01 = row0.y;
  mat->m10 = row1.x;
  mat->m11 = row1.y;
}

m2::m2(float m00,float m01,float m10,float m11) :
  FlatElement(16,16),
  mat((mat2*)getAlignedBuffer()),
  hand(LeftHand),
  Rotate(Mat2RotateLH)
{
  mat->m00 = m00;
  mat->m01 = m01;
  mat->m10 = m10;
  mat->m11 = m11;
}

void m2::SetLHCS()
{
  if ( LeftHand != hand )
    {
      hand   = LeftHand;
      Rotate = Mat2RotateLH;
    }
}

void m2::SetRHCS()
{
  if ( RightHand != hand )
    {
      hand   = RightHand;
      Rotate = Mat2RotateRH;
    }
}

// ---------------------------------------------------------------
// External M2 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

m2 operator + (const m2& m, const m2& n)
{
  m2 r;
  Mat2Add(r.mat,m.mat,n.mat);
  return r;
}

m2 operator - (const m2& m, const m2& n)
{
  m2 r;
  Mat2Subtract(r.mat,m.mat,n.mat);
  return r;
}

m2 operator - (const m2& m)
{
  m2 r;
  Mat2Negate(r.mat,m.mat);
  return r;
}

m2 operator * (const m2& m, const m2& n)
{
  m2 r;
  Mat2Multiply(r.mat,m.mat,n.mat);
  return r;
}

v2 operator * (const m2& m, const v2& v)
{
  v2 r;
  Mat2MultiplyVec(r.vec,m.mat,v.vec);
  return r;
}

m2 operator * (const m2& m, const float s)
{
  m2 r;
  Mat2MultiplyFloat(r.mat,m.mat,s);
  return r;
}

m2 m2_identity()
{
  m2 r;
  Mat2Identity(r.mat);
  return r;
}

m2 m2_transpose(const m2& m)
{
  m2 r;
  Mat2Transpose(r.mat,m.mat);
  return r;
}

m2 m2_rotateLH(const float s)
{
  m2 r;
  Mat2RotateLH(r.mat,s);
  return r;
}

m2 m2_rotateRH(const float s)
{
  m2 r;
  Mat2RotateRH(r.mat,s);
  return r;
}

m2 m2_rotate(const float s)
{
  m2 r;
  Mat2Rotate(r.mat,s);
  return r;
}

m2 m2_scale(const float x,const float y)
{
  m2 r;
  Mat2Scale(r.mat,x,y);
  return r;
}

// ---------------------------------------------------------------
// M3 Constructor and internal management methods
// ---------------------------------------------------------------

m3::m3() : FlatElement(48,16),mat((mat3*)getAlignedBuffer())
{
  mat->m00 = mat->m11 = mat->m22 = 1.0f;
  mat->m01 = mat->m02 = mat->n03 = 0.0f;
  mat->m10 = mat->m12 = mat->n13 = 0.0f;
  mat->m20 = mat->m21 = mat->n23 = 0.0f;
}

m3::m3(vec3& row0,vec3& row1,vec3& row2) : FlatElement(48,16),mat((mat3*)getAlignedBuffer())
{
  mat->m00 = row0.x;
  mat->m01 = row0.y;
  mat->m02 = row0.z;
  mat->n03 = 0.0f;
  mat->m10 = row1.x;
  mat->m11 = row1.y;
  mat->m12 = row1.z;
  mat->n13 = 0.0f;
  mat->m20 = row2.x;
  mat->m21 = row2.y;
  mat->m22 = row2.z;
  mat->n23 = 0.0f;
}

m3::m3(float m00,float m01,float m02,
       float m10,float m11,float m12,
       float m20,float m21,float m22) : FlatElement(48,16),mat((mat3*)getAlignedBuffer())
{
  mat->m00 = m00;
  mat->m01 = m01;
  mat->m02 = m02;
  mat->n03 = 0.0f;
  mat->m10 = m10;
  mat->m11 = m11;
  mat->m12 = m12;
  mat->n13 = 0.0f;
  mat->m20 = m20;
  mat->m21 = m21;
  mat->m22 = m22;
  mat->n23 = 0.0f;
}

// ---------------------------------------------------------------
// External M3 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

m3 operator + (const m3 &m, const m3 &n)
{
  m3 r;
  Mat3Add(r.mat,m.mat,n.mat);
  return r;
}

m3 operator - (const m3 &m, const m3 &n)
{
  m3 r;
  Mat3Subtract(r.mat,m.mat,n.mat);
  return r;
}

m3 operator - (const m3 &m)
{
  m3 r;
  Mat3Negate(r.mat,m.mat);
  return r;
}

m3 operator * (const m3 &m, const m3 &n)
{
  m3 r;
  Mat3Multiply(r.mat,m.mat,n.mat);
  return r;
}

v3 operator * (const m3 &m, const v3 &v)
{
  v3 r;
  Mat3MultiplyVec(r.vec,m.mat,v.vec);
  return r;
}

m3 operator * (const m3 &m, const float x)
{
  m3 r;
  Mat3MultiplyFloat(r.mat,m.mat,x);
  return r;
}

m3 operator ! (const m3 &m)
{
  m3 r;
  Mat3Inverse(r.mat,m.mat);
  return r;
}

m3 m3_identity ()
{
  m3 r;
  Mat3Identity(r.mat);
  return r;
}

m3 m3_transpose(const m3 &m)
{
  m3 r;
  Mat3Transpose(r.mat,m.mat);
  return r;
}

m3 m3_rotateX(const float s)
{
  m3 r;
  Mat3RotateRHX(r.mat,s);
  return r;
}

m3 m3_rotateY(const float s)
{
  m3 r;
  Mat3RotateRHY(r.mat,s);
  return r;
}

m3 m3_rotateZ(const float s)
{
  m3 r;
  Mat3RotateRHZ(r.mat,s);
  return r;
}

m3 m3_rotateXY(const float x,const float y)
{
  m3 r;
  Mat3RotateRHXY(r.mat,x,y);
  return r;
}

m3 m3_rotateXYZ(const float x,const float y,const float z)
{
  m3 r;
  Mat3RotateRHXYZ(r.mat,x,y,z);
  return r;
}

m3 m3_scale(const float x,const float y,const float z)
{
  m3 r;
  Mat3Scale(r.mat,x,y,z);
  return r;
}

// ---------------------------------------------------------------
// Internal M4 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

#if _FIX_ME
void m4::translate  (const v3& v)
{
  // XXX: This requires both right and left handed methods
  //

  Mat4TranslateVec3(mat,v.vec);
}
#endif

// ---------------------------------------------------------------
// M4 Constructor and Internal Management Methods
// ---------------------------------------------------------------

m4::m4() : FlatElement(64,16),mat((mat4*)getAlignedBuffer())
{
  mat->m00 = mat->m11 = mat->m22 = mat->m33 = 1.0f;
  mat->m01 = mat->m02 = mat->m03 = 0.0f;
  mat->m11 = mat->m12 = mat->m13 = 0.0f;
  mat->m20 = mat->m21 = mat->m23 = 0.0f;
  mat->m30 = mat->m31 = mat->m32 = 0.0f;
}

m4::m4(float a00,float a01,float a02,float a03,
       float a10,float a11,float a12,float a13,
       float a20,float a21,float a22,float a23,
       float a30,float a31,float a32,float a33) :
  FlatElement(64,16),mat((mat4*)getAlignedBuffer())
{
  mat->m00 = a00; mat->m01 = a01; mat->m02 = a02; mat->m03 = a03;
  mat->m10 = a10; mat->m11 = a11; mat->m12 = a12; mat->m13 = a13;
  mat->m20 = a20; mat->m21 = a21; mat->m22 = a22; mat->m23 = a23;
  mat->m30 = a30; mat->m31 = a31; mat->m32 = a32; mat->m33 = a33;
}

// ---------------------------------------------------------------
// External M4 Management Methods (Arithmetic Operations)
// ---------------------------------------------------------------

m4 operator + (const m4& m, const m4& n)
{
  m4 r;
  Mat4Add(r.mat,m.mat,n.mat);
  return r;
}

m4 operator - (const m4& m, const m4& n)
{
  m4 r;
  Mat4Subtract(r.mat,m.mat,n.mat);
  return r;
}

m4 operator - (const m4& m)
{
  m4 r;
  Mat4Negate(r.mat,m.mat);
  return r;
}

m4 operator * (const m4& m, const m4& n)
{
  m4 r;
  MatMultiply4x4(r.mat,m.mat,n.mat);
  return r;
}

v4 operator * (const m4& m, const v4& v)
{
  v4 r;
  MatMultiplyVec4x4(r.vec,m.mat,v.vec);
  return r;
}

m4 operator * (const m4& m, const float x)
{
  m4 r;
  Mat4MultiplyFloat(r.mat,m.mat,x);
  return r;
}

m4 m4_identity()
{
  m4 r;
  Mat4Identity(r.mat);
  return r;
}

m4 m4_transpose(const m4 &m)
{
  m4 r;
  Mat4Transpose(r.mat,m.mat);
  return r;
}

m4 m4_scale(const float x,const float y,const float z)
{
  m4 r;
  Mat4Scale(r.mat,x,y,z);
  return r;
}

m4 m4_rotateRHX(const float x)
{
  m4 r;
  Mat4RotateRHX(r.mat,x);
  return r;
}

m4 m4_rotateRHY(const float y)
{
  m4 r;
  Mat4RotateRHY(r.mat,y);
  return r;
}

m4 m4_rotateRHZ(const float z)
{
  m4 r;
  Mat4RotateRHZ(r.mat,z);
  return r;
}

m4 m4_rotateXY(const float x,const float y)
{
  m4 r;
  Mat4RotateRHXY(r.mat,x,y);
  return r;
}

m4 m4_rotateXYZ(const float x,const float y,const float z)
{
  m4 r;
  Mat4RotateRHXYZ(r.mat,x,y,z);
  return r;
}

m4 m4_translate(const float x,const float y,const float z)
{
  m4 r;
  Mat4TranslateRH(r.mat,x,y,z);
  return r;
}

#if _FIXME
m4 m4_translate(const v3& v)
{
  // XXX: This requires both right and left handed implementations
  //

  m4 r;
  Mat4TranslateVec3(r.mat,v.vec);
  return r;
}
#endif

m4 m4_ortho(const struct orthoMatrix& s)
{
  // XXX: This requires both right and left handed implementations
  //

  m4 r;
  Mat4OrthoStruct(r.mat,&s);
  return r;
}

m4 m4_perspectiveX(const struct perspectiveMatrix& s)
{
  // This requires both right and left handed implementations
  //

  m4 r;
  Mat4PerspectiveX(r.mat,&s);
  return r;
}

m4 m4_cubemapMatrix(const unsigned int face)
{
  // XXX: Review this for both right and left handed
  // matrices.

  m4 r;
  Mat4CubemapMatrix(r.mat,face);
  return r;
}

m4 m4_lookAt(const v3& from,const v3& at)
{
  // XXX: This has both right and left handed implmenations
  //

  m4 r;
  Mat4LookAt(r.mat,from.vec,at.vec);
  return r;
}

#if 0
XXX: Come back for rename
m4 m4_GlToD3dProjMat(const m4& m)
{
  m4 r;
  Mat4GlToD3dProjectionMat(r.mat,m.mat);
  return r;
}
#endif

m4 m4_mirrorMatrix(const v3& planeNormal,const float planeOffset)
{
  // XXX: Review this for enantiomeric behavior
  //

  m4 r;
  Mat4MirrorMatrix(r.mat,planeNormal.vec,planeOffset);
  return r;
}

m4 m4_shadowMatrix(const v3& planeNormal,const float planeOffset,const v3& lightPos)
{
  // XXX: Review this for enantiomeric behavior
  //

  m4 r;
  Mat4ShadowMatrix(r.mat,planeNormal.vec,planeOffset,lightPos.vec);
  return r;
}

m4 m4_cubemapProjMat(const float zNear,const float zFar,const int d3dtype)
{
  // XXX: Review this for enantiomeric behavior
  //

  m4 r;
  Mat4CubemapProjectionMat(r,zNear,zFar,d3dtype);
  return r;
}

// ---------------------------------------------------------------
// Quaternion Constructor and internal management methods
// ---------------------------------------------------------------

quat::quat() : FlatElement(16,16),q((quaternion*)getAlignedBuffer()) {}

quat::quat(vec4& u) : FlatElement(16,16),q((quaternion*)getAlignedBuffer())
{
  q->x = u.x;
  q->y = u.y;
  q->z = u.z;
  q->w = u.w;
}

quat::quat(quat& q0) : FlatElement(16,16),q((quaternion*)getAlignedBuffer())
{
  q->x = q0.q->x;
  q->y = q0.q->y;
  q->z = q0.q->z;
  q->w = q0.q->w;
}





struct _RotationInterface LeftRotationInterface = {
  Mat2RotateLH,
  Mat3RotateLHX,
  Mat3RotateLHY,
  Mat3RotateLHZ,
  Mat3RotateLHXY,
  Mat3RotateLHXZ,
  Mat3RotateLHYZ,
  Mat3RotateLHXYZ,
  Mat4RotateLHX,
  Mat4RotateLHY,
  Mat4RotateLHZ,
  Mat4RotateLHXY,
  Mat4RotateLHXZ,
  Mat4RotateLHYZ,
  Mat4RotateLHXYZ,
  Mat4TranslateLH,
  Mat4TranslateLH_Vec3,
  Mat4TranslateLH_Vec4,
};

// Add the basic projection matrices here later
//

struct _RotationInterface RightRotationInterface = {
  Mat2RotateRH,
  Mat3RotateRHX,
  Mat3RotateRHY,
  Mat3RotateRHZ,
  Mat3RotateRHXY,
  Mat3RotateRHXZ,
  Mat3RotateRHYZ,
  Mat3RotateRHXYZ,
  Mat4RotateRHX,
  Mat4RotateRHY,
  Mat4RotateRHZ,
  Mat4RotateRHXY,
  Mat4RotateRHXZ,
  Mat4RotateRHYZ,
  Mat4RotateRHXYZ,
  Mat4TranslateRH,
  Mat4TranslateLH_Vec3,
  Mat4TranslateRH_Vec4, 
};

