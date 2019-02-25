#include <CVector.h>

#include <Vecasm.h>

float lerp(float fStart,float fEnd,float fDelta)
{
  return FloatLerp(fStart,fEnd,fDelta);
}

float lerpPtr(float* pfStart,float* pfEnd,float* pfDelta)
{
  float r;

  FloatLerpPtr(&r,pfStart,pfEnd,pfDelta);

  return r;
}

float sqr(float fValue)
{
  return FloatSqr(fValue);
}

float sqrPtr(float* pfValue)
{
  return FloatSqrPtr(pfValue);
}

/* ------------- *
 * v2 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * v2 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 2-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v2::v2() : FlatElement(8,16),vec((vec2*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x =
  vec->y = 0.0f;
}

v2::v2(float x,float y) : FlatElement(8,16),vec((vec2*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = x;
  vec->y = y;
}

v2::v2(const v2& v) : FlatElement(8,16),vec((vec2*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = v.vec->x;
  vec->y = v.vec->y;
}

v2::~v2()
{
  vec = NULL;
}

#else

v2::v2()
{
  assert(NULL != (vec=new vec2()));
  vec->x =
  vec->y = 0.0f;
}

v2::v2(float x,float y)
{
  assert(NULL != (vec=new vec2()));
  vec->x = x;
  vec->y = y;
}

v2::v2(const v2& v)
{
  assert(NULL != (vec=new vec2()));
  vec->x = v.vec->x;
  vec->y = v.vec->y;
}

v2::~v2() {
  if ( NULL != vec ) delete vec;
  vec = NULL;
}

#endif

void v2::sqr()
{
  Vec2Sqr(vec,vec);
}

void v2::sqr(const v2& v)
{
  Vec2Sqr(vec,v.vec);
}

void v2::sqrt()
{
  Vec2Sqrt(vec,vec);
}

void v2::sqrt(const v2& v)
{
  Vec2Sqrt(vec,v.vec);
}

void v2::lerp(const v2& v,const float step)
{
  Vec2Lerp(vec,vec,v.vec,step);
}

void v2::lerp(const v2& u,const v2& v,const float step)
{
  Vec2Lerp(vec,u.vec,v.vec,step);
}

void v2::normalize()
{
  Vec2Normalize(vec,vec);
}

void v2::normalize(const v2& v)
{
  Vec2Normalize(vec,v.vec);
}

float v2::dot(const v2& v)
{
  float r;
  Vec2Dot(&r,vec,v.vec);
  return r;
}

float v2::length()
{
  float r;
  Vec2Length(&r,vec);
  return r;
}

bool v2::equals(const v2& v)
{
  int32_t iFlag;
  Vec2Equals(&iFlag,vec,v.vec);
  return (0 == iFlag ? false : true);
}

bool v2::notequals(const v2& v)
{
  int32_t iFlag;
  Vec2NotEquals(&iFlag,vec,v.vec);
  return (0 != iFlag ? true : false);
}

float v2::dot(const vec2& v)
{
  float r;
  Vec2Dot(&r,vec,&v);
  return r;
}

void v2::sqr(const vec2& v)
{
  Vec2Sqr(vec,&v);
}

void v2::sqrt(const vec2& v)
{
  Vec2Sqrt(vec,&v);
}

void v2::normalize(const vec2& v)
{
  Vec2Normalize(vec,&v);
}

void v2::lerp(const vec2& v,const float step)
{
  Vec2Lerp(vec,vec,&v,step);
}

void v2::lerp(const vec2& u,const vec2& v,const float step)
{
  Vec2Lerp(vec,&u,&v,step);
}

bool v2::equals(const vec2& v)
{
  int32_t iFlag;
  Vec2Equals(&iFlag,vec,&v);
  return (0 == iFlag ? false : true);
}

bool v2::notequals(const vec2& v)
{
  int32_t iFlag;
  Vec2NotEquals(&iFlag,vec,&v);
  return (0 != iFlag ? true : false);
}

void v2::copy(const v2& v)
{
  Vec2Copy(vec,v.vec);
}

void v2::operator += (const float s)
{
  Vec2AddFloat(vec,vec,s);
}

void v2::operator -= (const float s)
{
  Vec2SubtractFloat(vec,vec,s);
}

void v2::operator *= (const float s)
{
  Vec2MultiplyFloat(vec,vec,s);
}

void v2::operator /= (const float s)
{
  Vec2DivideFloat(vec,vec,2);
}

void v2::operator += (const v2& v)
{
  Vec2Add(vec,vec,v.vec);
}

void v2::operator -= (const v2& v)
{
  Vec2Subtract(vec,vec,v.vec);
}

void v2::operator *= (const v2& v)
{
  Vec2Multiply(vec,vec,v.vec);
}

void v2::operator /= (const v2& v)
{
  Vec2Divide(vec,vec,v.vec);
}

void v2::operator += (const vec2& u)
{
  Vec2Add(vec,vec,&u);
}

void v2::operator -= (const vec2& u)
{
  Vec2Subtract(vec,vec,&u);
}

void v2::operator *= (const vec2& u)
{
  Vec2Multiply(vec,vec,&u);
}

void v2::operator /= (const vec2& u)
{
  Vec2Divide(vec,vec,&u);
}

vec2* v2::operator->()
{
  return vec;
}

v2& v2::operator=(const v2& v)
{
  this->vec->x = v.vec->x;
  this->vec->y = v.vec->y;

  return *this;
}

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

v2 operator + (const v2& v,const float s)
{
  v2 r;

  Vec2AddFloat(r.vec,v.vec,s);

  return r;
}

v2 operator - (const v2& v,const float s)
{
  v2 r;

  Vec2SubtractFloat(r.vec,v.vec,s);

  return r;
}

v2 operator * (const v2& v,const float s)
{
  v2 r;

  Vec2MultiplyFloat(r.vec,v.vec,s);

  return r;
}

v2 operator * (const float s,const v2& v)
{
  v2 r;

  Vec2FloatMultiply(r.vec,s,v.vec);

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

v2 sqrt(const v2& v)
{
  v2 r;

  Vec2Sqrt(r.vec,v.vec);

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

/* ------------- *
 * vec2 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * Methods for the simple two-dimensional object. These methods generally  *
 * require either a generic or unaligned method for proper operations.     *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

vec2 operator + (const vec2& u,const float s)
{
  vec2 v;

  Vec2AddFloat(&v,&u,s);

  return v;
}

vec2 operator - (const vec2& u,const float s)
{
  vec2 v;

  Vec2SubtractFloat(&v,&u,s);

  return v;
}

vec2 operator * (const vec2& u,const float s)
{
  vec2 r;

  Vec2MultiplyFloat(&r,&u,s);

  return r;
}

vec2 operator * (const float s,const vec2& u)
{
  vec2 r;

  Vec2FloatMultiply(&r,s,&u);

  return r;
}

vec2 operator / (const vec2& v, const float s)
{
  vec2 r;

  Vec2DivideFloat(&r,&v,s);

  return r;
}

vec2 operator - (const vec2& v)
{
  vec2 r;

  Vec2Negate(&r,&v);

  return r;
}

vec2 operator + (const vec2& u, const vec2& v)
{
  vec2 r;

  Vec2Add(&r,&u,&v);

  return r;
}

vec2 operator - (const vec2& u, const vec2& v)
{
  vec2 r;

  Vec2Subtract(&r,&u,&v);

  return r;
}

vec2 operator * (const vec2& u, const vec2& v)
{
  vec2 r;

  Vec2Multiply(&r,&u,&v);

  return r;
}

vec2 operator / (const vec2& u, const vec2& v)
{
  vec2 r;

  Vec2Divide(&r,&u,&v);

  return r;
}

vec2 lerp(const vec2& u, const vec2& v, const float x)
{
  vec2 r;

  Vec2Lerp(&r,&u,&v,x);

  return r;
}

vec2 sqr(const vec2& v)
{
  vec2 r;

  Vec2Sqr(&r,&v);

  return r;
}

vec2 sqrt(const vec2& v)
{
  vec2 r;

  Vec2Sqrt(&r,&v);

  return r;
}

vec2 normalize(const vec2& v)
{
  vec2 r;

  Vec2Normalize(&r,&v);

  return r;
}

float dot(const vec2& u, const vec2& v)
{
  float r;

  Vec2Dot(&r,&u,&v);

  return r;
}

float length(const vec2& v)
{
  float r;

  Vec2Length(&r,&v);

  return r;
}

bool operator == (const v2& u,const v2& v)
{
  int32_t iFlag;

  Vec2Equals(&iFlag,u.vec,v.vec);

  return (0 == iFlag ? false : true);
}

bool operator != (const v2& u,const v2& v)
{
  int32_t iFlag;

  Vec2NotEquals(&iFlag,u.vec,v.vec);

  return (0 != iFlag ? true : false);
}

bool operator == (const vec2& u,const vec2& v)
{
  int32_t iFlag;

  Vec2Equals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

bool operator != (const vec2& u,const vec2& v)
{
  int32_t iFlag;

  Vec2NotEquals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

/* ------------- *
 * v3 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * v3 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v3::v3() : FlatElement(16,16),vec((vec3*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x =
  vec->y =
  vec->z = 0.0f;
}

v3::v3(float x,float y,float z) : FlatElement(16,16),vec((vec3*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = x;
  vec->y = y;
  vec->z = z;
}

v3::v3(const v3& v) : FlatElement(16,16),vec((vec3*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = v.vec->x;
  vec->y = v.vec->y;
  vec->z = v.vec->z;
}

v3::~v3()
{
  vec = NULL;
}


#else

v3::v3()
{
  assert(NULL != (vec=new vec3()));
  vec->x =
  vec->y =
  vec->z = 0.0f;
}

v3::v3(float x,float y,float z)
{
  assert(NULL != (vec=new vec3()));

  vec->x = x;
  vec->y = y;
  vec->z = z;
}

v3::v3(const v3& v)
{
  assert(NULL != (vec=new vec3()));
  vec->x = v.vec->x;
  vec->y = v.vec->y;
  vec->z = v.vec->z;
}

v3::~v3()
{
  if ( NULL != vec ) delete vec;
  vec = NULL;
}

#endif

void v3::sqr()
{
  Vec3Sqr(vec,vec);
}

void v3::sqrt()
{
  Vec3Sqrt(vec,vec);
}

void v3::normalize()
{
  Vec3Normalize(vec,vec);
}

float v3::length()
{
  float r;
  Vec3Length(&r,vec);
  return r;
}

float v3::dot(const v3& v)
{
  float r;
  Vec3Dot(&r,vec,v.vec);
  return r;
}

void v3::lerp(const v3& v,const float step)
{
  Vec3Lerp(vec,vec,v.vec,step);
}

void v3::cross(const v3& v)
{
  Vec3Cross(vec,vec,v.vec);
}

bool v3::equals(const v3& v)
{
  int32_t iFlag;
  Vec3Equals(&iFlag,vec,v.vec);
  return (0 == iFlag ? false : true);
}

bool v3::notequals(const v3& v)
{
  int32_t iFlag;
  Vec3NotEquals(&iFlag,vec,v.vec);
  return (0 == iFlag ? true : false);
}

void v3::sqr(const v3& v)
{
  Vec3Sqr(vec,v.vec);
}

void v3::sqrt(const v3& v)
{
  Vec3Sqrt(vec,v.vec);
}

void v3::normalize(const v3& v)
{
  Vec3Normalize(vec,v.vec);
}

void v3::lerp(const v3& u,const v3& v,const float step)
{
  Vec3Lerp(vec,u.vec,v.vec,step);
}

void v3::cross(const v3& u,const v3& v)
{
  Vec3Cross(vec,u.vec,v.vec);
}

float v3::dot(const vec3& v)
{
  float r;
  Vec3Dot(&r,vec,&v);
  return r;
}

void v3::sqr(const vec3& v)
{
  Vec3Sqr(vec,&v);
}

void v3::sqrt(const vec3& v)
{
  Vec3Sqrt(vec,&v);
}

void v3::normalize(const vec3& v)
{
  Vec3Normalize(vec,&v);
}

void v3::lerp(const vec3& v,const float step)
{
  Vec3Lerp(vec,vec,&v,step);
}

void v3::lerp(const vec3& u,const vec3& v,const float step)
{
  Vec3Lerp(vec,&u,&v,step);
}

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

void v3::operator += (const vec3& u)
{
  Vec3Add(vec,vec,&u);
}

void v3::operator -= (const vec3& u)
{
  Vec3Subtract(vec,vec,&u);
}

void v3::operator *= (const vec3& u)
{
  Vec3Multiply(vec,vec,&u);
}

void v3::operator /= (const vec3& u)
{
  Vec3Divide(vec,vec,&u);
}

vec3* v3::operator->()
{
  return vec;
}

v3& v3::operator=(const v3& v)
{
  this->vec->x = v.vec->x;
  this->vec->y = v.vec->y;
  this->vec->z = v.vec->z;

  return *this;
}

void copy(v3& r,const v3& v)
{
  Vec3Copy(r.vec,v.vec);
}

void copy_block(v3& r,const v3& v,int32_t iCount)
{
  Vec3CopyBlock(r.vec,v.vec,iCount);
}

void pack_array(v3& r,const vec3** base,int32_t iCount)
{
  BuildVec3PackedArray(r.vec,base,iCount);
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

v3 operator * (const v3& v, const float s)
{
  v3 r;

  Vec3MultiplyFloat(r.vec,v.vec,s);

  return r;
}

v3 operator * (const float s, const v3& v)
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

v3 operator - (const v3& v)
{
  v3 r;

  Vec3Negate(r.vec,v.vec);

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

v3 lerp(const v3& u, const v3& v, const float x)
{
  v3 r;

  Vec3Lerp(r.vec,u.vec,v.vec,x);

  return r;
}

v3 sqr(const v3& v)
{
  v3 r;

  Vec3Sqr(r.vec,v.vec);

  return r;
}

v3 sqrt(const v3& v)
{
  v3 r;

  Vec3Sqrt(r.vec,v.vec);

  return r;
}

v3 normalize(const v3& v)
{
  v3 r;

  Vec3Normalize(r.vec,v.vec);

  return r;
}

v3 cross(const v3& u,const v3& v)
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

float length(const v3& v)
{
  float r;

  Vec3Length(&r,v.vec);

  return r;
}

/* ------------- *
 * vec3 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * Methods for simple 3-dimensional vector operations. These methods       *
 * generally require application of either generic or unaligned methods    *
 * for proper operation.                                                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

vec3 operator + (const vec3& u,const float s)
{
  v3 r;

  Vec3AddFloat(r.vec,&u,s);

  return *(r.vec);
}

vec3 operator - (const vec3& u,const float s)
{
  v3 r;

  Vec3SubtractFloat(r.vec,&u,s);

  return *(r.vec);
}

vec3 operator * (const vec3& u,const float s)
{
  v3 r;

  Vec3MultiplyFloat(r.vec,&u,s);

  return *(r.vec);
}

vec3 operator * (const float s,const vec3& u)
{
  v3 r;

  Vec3MultiplyFloat(r.vec,&u,s);

  return *(r.vec);
}

vec3 operator / (const vec3& v, const float s)
{
  v3 r;

  Vec3DivideFloat(r.vec,&v,s);

  return *(r.vec);
}

vec3 operator - (const vec3& v)
{
  v3 r;

  Vec3Negate(r.vec,&v);

  return *(r.vec);
}

vec3 operator + (const vec3& u, const vec3& v)
{
  v3 r;

  Vec3Add(r.vec,&u,&v);

  return *(r.vec);
}

vec3 operator - (const vec3& u, const vec3& v)
{
  v3 r;

  Vec3Subtract(r.vec,&u,&v);

  return *(r.vec);
}

vec3 operator * (const vec3& u, const vec3& v)
{
  v3 r;

  Vec3Multiply(r.vec,&u,&v);

  return *(r.vec);
}

vec3 operator / (const vec3& u, const vec3& v)
{
  v3 r;

  Vec3Divide(r.vec,&u,&v);

  return *(r.vec);
}

vec3 lerp(const vec3& u, const vec3& v, const float x)
{
  v3 r;

  Vec3Lerp(r.vec,&u,&v,x);

  return *(r.vec);
}

vec3 sqr(const vec3& v)
{
  v3 r;

  Vec3Sqr(r.vec,&v);

  return *(r.vec);
}

vec3 sqrt(const vec3& v)
{
  v3 r;

  Vec3Sqrt(r.vec,&v);

  return *(r.vec);
}

vec3 normalize(const vec3& v)
{
  v3 r;

  Vec3Normalize(r.vec,&v);

  return *(r.vec);
}

vec3 cross(const vec3& u,const vec3& v)
{
  v3 r;

  Vec3Cross(r.vec,&u,&v);

  return *(r.vec);
}

float dot(const vec3& u, const vec3& v)
{
  float r;

  Vec3Dot(&r,&u,&v);

  return r;
}

float length(const vec3& v)
{
  float r;

  Vec3Length(&r,&v);

  return r;
}

bool operator == (const v3& u, const v3& v)
{
  int32_t iFlag;

  Vec3Equals(&iFlag,u.vec,v.vec);

  return (0 == iFlag ? false : true);
}

bool operator != (const v3 &u, const v3 &v)
{
  int32_t iFlag;

  Vec3NotEquals(&iFlag,u.vec,v.vec);

  return (0 == iFlag ? false : true);
}

bool operator == (const vec3& u,const vec3& v)
{
  int32_t iFlag;

  Vec3Equals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

bool operator != (const vec3& u,const vec3& v)
{
  int32_t iFlag;

  Vec3NotEquals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

/* ------------- *
 * v4 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * v4 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 4-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v4::v4() : FlatElement(16,16),vec((vec4*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x =
  vec->y =
  vec->z =
  vec->w = 0.0f;
}

v4::v4(float x,float y,float z,float w) :
  FlatElement(16,16),
  vec((vec4*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}

v4::v4(const v4& v) :
  FlatElement(16,16),
  vec((vec4*)getAlignedBuffer())
{
  assert(NULL != vec);
  vec->x = v.vec->x;
  vec->y = v.vec->y;
  vec->z = v.vec->z;
  vec->w = v.vec->w;
}

v4::~v4()
{
  vec = NULL;
}

#else

v4::v4()
{
  assert(NULL != (vec=new vec4()));
  vec->x =
  vec->y =
  vec->z =
  vec->w = 0.0f;
}

v4::v4(float x,float y,float z,float w)
{
  assert(NULL != (vec=new vec4()));
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}

v4::v4(const v4& v)
{
  assert(NULL != (vec=new vec4()));
  vec->x = v.vec->x;
  vec->y = v.vec->y;
  vec->z = v.vec->z;
  vec->w = v.vec->w;
}

v4::~v4()
{
  if ( NULL != vec ) delete vec;
  vec = NULL;
}

#endif

void v4::sqr()
{
  Vec4Sqr(vec,vec);
}

void v4::sqrt()
{
  Vec4Sqrt(vec,vec);
}

void v4::normalize()
{
  Vec4Normalize(vec,vec);
}

float v4::length()
{
  float r;
  Vec4Length(&r,vec);
  return r;
}

float v4::dot(const v4& v)
{
  float r;
  Vec4Dot(&r,vec,v.vec);
  return r;
}

void v4::cross(const v4& v)
{
  Vec4Cross(vec,vec,v.vec);
}

void v4::lerp(const v4& v,const float step)
{
  Vec4Lerp(vec,vec,v.vec,step);
}

bool v4::equals(const v4& v)
{
  int32_t iFlag;
  Vec4Equals(&iFlag,vec,v.vec);
  return (0 == iFlag ? false : true);
}

bool v4::notequals(const v4& v)
{
  int32_t iFlag;
  Vec4NotEquals(&iFlag,vec,v.vec);
  return (0 == iFlag ? true : false);
}

void v4::sqr(const v4& v)
{
  Vec4Sqr(vec,v.vec);
}

void v4::sqrt(const v4& v)
{
  Vec4Sqrt(vec,v.vec);
}

void v4::normalize(const v4& v)
{
  Vec4Normalize(vec,v.vec);
}

void v4::cross(const v4& u,const v4& v)
{
  Vec4Cross(vec,u.vec,v.vec);
}

void v4::lerp(const v4& u,const v4& v,const float step)
{
  Vec4Lerp(vec,u.vec,v.vec,step);
}

float v4::dot(const vec4& v)
{
  float r;
  Vec4Dot(&r,vec,&v);
  return r;
}

void v4::sqr(const vec4& v)
{
  Vec4Sqr(vec,&v);
}

void v4::sqrt(const vec4& v)
{
  Vec4Sqrt(vec,&v);
}

void v4::normalize(const vec4& v)
{
  Vec4Normalize(vec,&v);
}

void v4::lerp(const vec4& v,const float step)
{
  Vec4Lerp(vec,vec,&v,step);
}

void v4::lerp(const vec4& u,const vec4& v,const float step)
{
  Vec4Lerp(vec,&u,&v,step);
}

void v4::copy(const v4& v)
{
  Vec4Copy(vec,v.vec);
}

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

void v4::operator += (const vec4& u)
{
  Vec4Add(vec,vec,&u);
}

void v4::operator -= (const vec4& u)
{
  Vec4Subtract(vec,vec,&u);
}

void v4::operator *= (const vec4& u)
{
  Vec4Multiply(vec,vec,&u);
}

void v4::operator /= (const vec4& u)
{
  Vec4Divide(vec,vec,&u);
}

vec4* v4::operator->()
{
  return vec;
}

v4& v4::operator=(const v4& v)
{
  this->vec->x = v.vec->x;
  this->vec->y = v.vec->y;
  this->vec->z = v.vec->z;
  this->vec->w = v.vec->w;

  return *this;
}

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

v4 operator + (const v4& v, const float s)
{
  v4 r;

  Vec4AddFloat(r.vec,v.vec,s);

  return r;
}

v4 operator - (const v4& v, const float s)
{
  v4 r;

  Vec4SubtractFloat(r.vec,v.vec,s);

  return r;
}

v4 operator * (const v4& v, const float s)
{
  v4 r;

  Vec4MultiplyFloat(r.vec,v.vec,s);

  return r;
}

v4 operator * (const float s, const v4& v)
{
  v4 r;

  Vec4MultiplyFloat(r.vec,v.vec,s);

  return r;
}

v4 operator / (const v4& v, const float s)
{
  v4 r;

  Vec4DivideFloat(r.vec,v.vec,s);

  return r;
}

v4 operator - (const v4& v)
{
  v4 r;

  Vec4Negate(r.vec,v.vec);

  return r;
}

v4 operator + (const v4& u, const v4& v)
{
  v4 r;

  Vec4Add(r.vec,u.vec,v.vec);

  return r;
}

v4 operator - (const v4& u, const v4& v)
{
  v4 r;

  Vec4Subtract(r.vec,u.vec,v.vec);

  return r;
}

v4 operator * (const v4& u, const v4& v)
{
  v4 r;

  Vec4Multiply(r.vec,u.vec,v.vec);

  return r;
}

v4 operator / (const v4& u, const v4& v)
{
  v4 r;

  Vec4Divide(r.vec,u.vec,v.vec);

  return r;
}

v4 lerp(const v4& u, const v4& v, const float x)
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

v4 sqrt(const v4& v)
{
  v4 r;

  Vec4Sqrt(r.vec,v.vec);

  return r;
}

v4 normalize(const v4& v)
{
  v4 r;

  Vec4Normalize(r.vec,v.vec);

  return r;
}

v4 cross(const v4& u,const v4& v)
{
  v4 r;

  Vec4Cross(r.vec,u.vec,v.vec);

  return r;
}

float dot(const v4& u, const v4& v)
{
  float r;

  Vec4Dot(&r,u.vec,v.vec);

  return r;
}

float length(const v4& v)
{
  float r;

  Vec4Length(&r,v.vec);

  return r;
}

/* ------------- *
 * vec4 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * Methods required for use of the simple 4-D vector operations. These     *
 * methods generally require generic or unaligned operations go assure     *
 * correct operation                                                       *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

vec4 operator + (const vec4& u,const float s)
{
  v4 r;

  Vec4AddFloat(r.vec,&u,s);

  return *(r.vec);
}

vec4 operator - (const vec4& u,const float s)
{
  v4 r;

  Vec4SubtractFloat(r.vec,&u,s);

  return *(r.vec);
}

vec4 operator * (const vec4& u,const float s)
{
  v4 r;

  Vec4MultiplyFloat(r.vec,&u,s);

  return *(r.vec);
}

vec4 operator * (const float s,const vec4& u)
{
  v4 r;

  Vec4MultiplyFloat(r.vec,&u,s);

  return *(r.vec);
}

vec4 operator / (const vec4& v, const float s)
{
  v4 r;

  Vec4DivideFloat(r.vec,&v,s);

  return *(r.vec);
}

vec4 operator - (const vec4& v)
{
  v4 r;

  Vec4Negate(r.vec,&v);

  return *(r.vec);
}

vec4 operator + (const vec4& u, const vec4& v)
{
  v4 r;

  Vec4Add(r.vec,&u,&v);

  return *(r.vec);
}

vec4 operator - (const vec4& u, const vec4& v)
{
  v4 r;

  Vec4Subtract(r.vec,&u,&v);

  return *(r.vec);
}

vec4 operator * (const vec4& u, const vec4& v)
{
  v4 r;

  Vec4Multiply(r.vec,&u,&v);

  return *(r.vec);
}

vec4 operator / (const vec4& u, const vec4& v)
{
  v4 r;

  Vec4Divide(r.vec,&u,&v);

  return *(r.vec);
}


vec4 lerp(const vec4& u, const vec4& v, const float x)
{
  v4 r;

  Vec4Lerp(r.vec,&u,&v,x);

  return *(r.vec);
}

vec4 sqr(const vec4& v)
{
  v4 r;

  Vec4Sqr(r.vec,&v);

  return *(r.vec);
}

vec4 sqrt(const vec4& v)
{
  v4 r;

  Vec4Sqrt(r.vec,&v);

  return *(r.vec);
}

vec4 normalize(const vec4& v)
{
  v4 r;

  Vec4Normalize(r.vec,&v);

  return *(r.vec);
}

vec4 cross(const vec4& u,const vec4& v)
{
  v4 r;

  Vec4Cross(r.vec,&u,&v);

  return *(r.vec);
}

float dot(const vec4& u, const vec4& v)
{
  float r;

  Vec4Dot(&r,&u,&v);

  return r;
}

float length(const vec4& v)
{
  float r;

  Vec4Length(&r,&v);

  return r;
}

bool operator == (const v4 &u, const v4 &v)
{
  int32_t iFlag;

  Vec4Equals(&iFlag,u.vec,v.vec);

  return (0 == iFlag ? false : true);
}

bool operator != (const v4 &u, const v4 &v)
{
  int32_t iFlag;

  Vec4NotEquals(&iFlag,u.vec,v.vec);

  return (0 == iFlag ? false : true);
}

bool operator == (const vec4& u,const vec4& v)
{
  int32_t iFlag;

  Vec4Equals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

bool operator != (const vec4& u,const vec4& v)
{
  int32_t iFlag;

  Vec4NotEquals(&iFlag,&u,&v);

  return (0 == iFlag ? false : true);
}

/* ------------- *
 * m2 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * m2 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 2-dimensional matrix objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

m2::m2() : FlatElement(16,16),m((mat2*)getAlignedBuffer())
{
  assert(NULL != m);
  m->m01 =
  m->m10 = 0.0f;
  m->m00 =
  m->m11 = 1.0f;
}

m2::m2(float m00,float m01,float m10,float m11) :
  FlatElement(16,16),
  m((mat2*)getAlignedBuffer())
{
  assert(NULL != m);
  m->m00 = m00;
  m->m01 = m01;
  m->m10 = m10;
  m->m11 = m11;
}

m2::m2(const m2& n) :
  FlatElement(16,16),
  m((mat2*)getAlignedBuffer())
{
  assert(NULL != m);
  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
}

m2::~m2()
{
  m = NULL;
}

#else

m2::m2()
{
  assert(NULL != (m=new mat2()));
  m->m01 =
  m->m10 = 0.0f;
  m->m00 =
  m->m11 = 1.0f;
}

m2::m2(float m00,float m01,float m10,float m11)
{
  assert(NULL != (m=new mat2()));
  m->m00 = m00;
  m->m01 = m01;
  m->m10 = m10;
  m->m11 = m11;
}

m2::m2(const m2& n)
{
  assert(NULL != (m=new mat2()));
  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
}

m2::~m2()
{
  if ( NULL != m ) delete m;
  m = NULL;
}

#endif

void m2::identity()
{
  m->m01 =
  m->m10 = 0.0f;
  m->m00 =
  m->m11 = 1.0f;
}

void m2::operator += (const float s)
{
  Mat2AddFloat(m,m,s);
}

void m2::operator -= (const float s)
{
  Mat2SubtractFloat(m,m,s);
}

void m2::operator *= (const float s)
{
  Mat2MultiplyFloat(m,m,s);
}

void m2::operator += (const m2& n)
{
  Mat2Add(m,m,n.m);
}

void m2::operator -= (const m2& n)
{
  Mat2Subtract(m,m,n.m);
}

void m2::operator *= (const m2& n)
{
  Mat2Multiply(m,m,n.m);
}

void m2::operator += (const mat2& n)
{
  Mat2Add(m,m,&n);
}

void m2::operator -= (const mat2& n)
{
  Mat2Subtract(m,m,&n);
}

void m2::operator *= (const mat2& n)
{
  Mat2Multiply(m,m,&n);
}

mat2* m2::operator->()
{
  return m;
}

m2& m2::operator=(const m2& n)
{
  this->m->m00 = n.m->m00;
  this->m->m01 = n.m->m01;
  this->m->m10 = n.m->m10;
  this->m->m11 = n.m->m11;
  return *this;
}

m2 m2identity()
{
  m2 r;

  return r;
}

m2 m2transpose(const m2& m)
{
  m2 r;

  Mat2Transpose(r.m,m.m);

  return r;
}

m2 m2rotate(const float angle)
{
  m2 r;

  Mat2Rotate(r.m,angle);

  return r;
}

m2 m2rotate_lh(const float angle)
{
  m2 r;

  Mat2RotateLH(r.m,angle);

  return r;
}

m2 m2rotate_rh(const float angle)
{
  m2 r;

  Mat2RotateRH(r.m,angle);

  return r;
}

m2 m2scale(const float x_scale,const float y_scale)
{
  m2 r;

  Mat2Scale(r.m,x_scale,y_scale);

  return r;
}

m2 operator + (const m2& m,const float s)
{
  m2 r;

  Mat2AddFloat(r.m,m.m,s);

  return r;
}

m2 operator - (const m2& m,const float s)
{
  m2 r;

  Mat2SubtractFloat(r.m,m.m,s);

  return r;
}

m2 operator * (const m2& m,const float s)
{
  m2 r;

  Mat2MultiplyFloat(r.m,m.m,s);

  return r;
}

v2 operator * (const m2& m,const v2& v)
{
  v2 r;

  Mat2MultiplyVec(r.vec,m.m,v.vec);

  return r;
}
  
m2 operator + (const m2& m,const m2& n)
{
  m2 r;

  Mat2Add(r.m,m.m,n.m);

  return r;
}


m2 operator - (const m2& m,const m2& n)
{
  m2 r;

  Mat2Subtract(r.m,m.m,n.m);

  return r;
}

m2 operator * (const m2& m,const m2& n)
{
  m2 r;

  Mat2Multiply(r.m,m.m,n.m);

  return r;
}

m2 operator - (const m2& m)
{
  m2 r;

  Mat2Negate(r.m,m.m);

  return r;
}

/* ------------- *
 * mat2 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * Simple 2-Dimensional vector/matrix operators. These operators generally *
 * require use of generic or unaligned objects in order to operate         *
 * correctly.                                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

mat2 mat2identity()
{
  m2 r;

  Mat2Identity(r.m);

  return *(r.m);
}

mat2 mat2transpose(const mat2& m)
{
  m2 r;

  Mat2Transpose(r.m,&m);

  return *(r.m);
}

mat2 mat2rotate(const float angle)
{
  m2 r;

  Mat2Rotate(r.m,angle);

  return *(r.m);
}

mat2 mat2rotate_lh(const float angle)
{
  m2 r;

  Mat2RotateLH(r.m,angle);

  return *(r.m);
}

mat2 mat2rotate_rh(const float angle)
{
  m2 r;

  Mat2RotateRH(r.m,angle);

  return *(r.m);
}

mat2 mat2scale(const float x_scale,const float y_scale)
{
  m2 r;

  Mat2Scale(r.m,x_scale,y_scale);

  return *(r.m);
}

mat2 operator + (const mat2& m,const float s)
{
  m2 r;

  Mat2AddFloat(r.m,&m,s);

  return *(r.m);
}

mat2 operator - (const mat2& m,const float s)
{
  m2 r;

  Mat2SubtractFloat(r.m,&m,s);

  return *(r.m);
}

mat2 operator * (const mat2& m,const float s)
{
  m2 r;

  Mat2MultiplyFloat(r.m,&m,s);

  return *(r.m);
}

mat2 operator - (const mat2& m)
{
  m2 r;

  Mat2Negate(r.m,&m);

  return *(r.m);
}

vec2 operator * (const mat2& m,const vec2& v)
{
  v2 r;

  Mat2MultiplyVec(r.vec,&m,&v);

  return *(r.vec);
}

mat2 operator + (const mat2& m,const mat2& n)
{
  m2 r;

  Mat2Add(r.m,&m,&n);

  return *(r.m);
}

mat2 operator - (const mat2& m,const mat2& n)
{
  m2 r;

  Mat2Subtract(r.m,&m,&n);

  return *(r.m);
}

mat2 operator * (const mat2& m,const mat2& n)
{
  m2 r;

  Mat2Multiply(r.m,&m,&n);

  return *(r.m);
}

/* ------------- *
 * m3 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * m3 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional matrix objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

m3::m3() : FlatElement(48,16),m((mat3*)getAlignedBuffer())
{
  assert(NULL != m);
  m->m00 =
  m->m11 =
  m->m22 = 1.0f;

  m->m01 =
  m->m02 =
  m->n03 =
  m->m10 =
  m->m12 =
  m->n13 =
  m->m20 =
  m->m21 =
  m->n23 = 0.0f;
}

m3::m3(const float m00,const float m01,const float m02,
       const float m10,const float m11,const float m12,
       const float m20,const float m21,const float m22) :
  FlatElement(48,16),
  m((mat3*)getAlignedBuffer())
{
  assert(NULL != m);

  m->m00 = m00;
  m->m01 = m01;
  m->m02 = m02;

  m->m10 = m10;
  m->m11 = m11;
  m->m12 = m12;

  m->m20 = m20;
  m->m21 = m21;
  m->m22 = m22;

  m->n03 =
  m->n13 =
  m->n23 = 0.0f;
}

m3::m3(const m3& n) :
  FlatElement(48,16),
  m((mat3*)getAlignedBuffer())
{
  assert(NULL != m);

  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m02 = n.m->m02;

  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
  m->m12 = n.m->m12;

  m->m20 = n.m->m20;
  m->m21 = n.m->m21;
  m->m22 = n.m->m22;

  m->n03 =
  m->n13 =
  m->n23 = 0.0f;
}

m3::~m3()
{
  m = NULL;
}

#else

m3::m3()
{
  m = new mat3;

  m->m00 =
  m->m11 =
  m->m22 = 1.0f;

  m->m01 =
  m->m02 =
  m->n03 =
  m->m10 =
  m->m12 =
  m->n13 =
  m->m20 =
  m->m21 =
  m->n23 = 0.0f;
}

m3::m3(const float m00,const float m01,const float m02,
       const float m10,const float m11,const float m12,
       const float m20,const float m21,const float m22)
{
  m = new mat3;

  m->m00 = m00;
  m->m01 = m01;
  m->m02 = m02;

  m->m10 = m10;
  m->m11 = m11;
  m->m12 = m12;

  m->m20 = m20;
  m->m21 = m21;
  m->m22 = m22;

  m->n03 =
  m->n13 =
  m->n23 = 0.0f;
}

m3::m3(const m3& n)
{
  assert(NULL != (m=new mat3()));

  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m02 = n.m->m02;

  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
  m->m12 = n.m->m12;

  m->m20 = n.m->m20;
  m->m21 = n.m->m21;
  m->m22 = n.m->m22;

  m->n03 =
  m->n13 =
  m->n23 = 0.0f;
}
m3::~m3()
{
  if ( NULL != m ) delete m;
  m = NULL;
}

#endif

void m3::identity()
{
  Mat3Identity(m);
}

void m3::operator += (const float s)
{
  Mat3AddFloat(m,m,s);
}

void m3::operator -= (const float s)
{
  Mat3SubtractFloat(m,m,s);
}

void m3::operator *= (const float s)
{
  Mat3MultiplyFloat(m,m,s);
}

void m3::operator += (const m3& n)
{
  Mat3Add(m,m,n.m);
}

void m3::operator -= (const m3& n)
{
  Mat3Subtract(m,m,n.m);
}

void m3::operator *= (const m3& n)
{
  Mat3Multiply(m,m,n.m);
}

void m3::operator += (const mat3& n)
{
  Mat3Add(m,m,&n);
}

void m3::operator -= (const mat3& n)
{
  Mat3Subtract(m,m,&n);
}

void m3::operator *= (const mat3& n)
{
  Mat3Multiply(m,m,&n);
}

mat3* m3::operator->()
{
  return m;
}

m3& m3::operator=(const m3& n)
{
  this->m->m00 = n.m->m00;
  this->m->m01 = n.m->m01;
  this->m->m02 = n.m->m02;

  this->m->m10 = n.m->m10;
  this->m->m11 = n.m->m11;
  this->m->m12 = n.m->m12;

  this->m->m20 = n.m->m20;
  this->m->m21 = n.m->m21;
  this->m->m22 = n.m->m22;

  this->m->n03 =
  this->m->n13 =
  this->m->n23 = 0.0f;

  return *this;
}

m3 m3identity()
{
  m3 r;

  return r;
}

m3 m3inverse(const m3& m)
{
  m3 r;

  Mat3Inverse(r.m,m.m);

  return r;
}

m3 m3transpose(const m3& m)
{
  m3 r;

  Mat3Transpose(r.m,m.m);

  return r;
}

m3 operator + (const m3& n,const float s)
{
  m3 r;

  Mat3AddFloat(r.m,n.m,s);

  return r;
}

m3 operator - (const m3& n,const float s)
{
  m3 r;

  Mat3SubtractFloat(r.m,n.m,s);

  return r;
}

m3 operator * (const m3& n,const float s)
{
  m3 r;

  Mat3MultiplyFloat(r.m,n.m,s);

  return r;
}

v3 operator * (const m3& m,const v3& v)
{
  v3 r;

  Mat3MultiplyVec(r.vec,m.m,v.vec);

  return r;
}

m3 operator - (const m3& m)
{
  m3 r;

  Mat3Negate(r.m,m.m);

  return r;
}

m3 operator + (const m3& m,const m3& n)
{
  m3 r;

  Mat3Add(r.m,m.m,n.m);

  return r;
}

m3 operator - (const m3& m,const m3& n)
{
  m3 r;

  Mat3Subtract(r.m,m.m,n.m);

  return r;
}

m3 operator * (const m3& m,const m3& n)
{
  m3 r;

  Mat3Multiply(r.m,m.m,n.m);

  return r;
}

m3 m3rotate_rhx(const float angle)
{
  m3 r;

  Mat3RotateRHX(r.m,angle);

  return r;
}

m3 m3rotate_lhx(const float angle)
{
  m3 r;

  Mat3RotateLHX(r.m,angle);

  return r;
}

m3 m3rotate_rhy(const float angle)
{
  m3 r;

  Mat3RotateRHY(r.m,angle);

  return r;
}

m3 m3rotate_lhy(const float angle)
{
  m3 r;

  Mat3RotateLHY(r.m,angle);

  return r;
}

m3 m3rotate_rhz(const float angle)
{
  m3 r;

  Mat3RotateRHZ(r.m,angle);

  return r;
}

m3 m3rotate_lhz(const float angle)
{
  m3 r;

  Mat3RotateLHZ(r.m,angle);

  return r;
}

m3 m3rotate_rhxy(const float x_angle,const float y_angle)
{
  m3 r;

  Mat3RotateRHXY(r.m,x_angle,y_angle);

  return r;
}

m3 m3rotate_lhxy(const float x_angle,const float y_angle)
{
  m3 r;

  Mat3RotateLHXY(r.m,x_angle,y_angle);

  return r;
}

m3 m3rotate_rhxz(const float x_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHXZ(r.m,x_angle,z_angle);

  return r;
}

m3 m3rotate_lhxz(const float x_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHXZ(r.m,x_angle,z_angle);

  return r;
}

m3 m3rotate_rhyz(const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHYZ(r.m,y_angle,z_angle);

  return r;
}

m3 m3rotate_lhyz(const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHYZ(r.m,y_angle,z_angle);

  return r;
}

m3 m3rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHXYZ(r.m,x_angle,y_angle,z_angle);

  return r;
}

m3 m3rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHXYZ(r.m,x_angle,y_angle,z_angle);

  return r;
}

m3 m3scale(const float x_scale,const float y_scale,const float z_scale)
{
  m3 r;

  Mat3Scale(r.m,x_scale,y_scale,z_scale);

  return r;
}

m3 m3scale(const v3& v)
{
  m3 r;

  Mat3ScaleByVec3(r.m,v.vec);

  return r;
}

/* ------------- *
 * mat3 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * These methods are simple wrappers for three dimensional matrix          *
 * representation and operations. The methods generally require use of     *
 * either generic or unaligned representation for correct operation.       *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

mat3 mat3inverse(const mat3& m)
{
  m3 r;

  Mat3Inverse(r.m,&m);

  return *(r.m);
}

mat3 mat3transpose(const mat3& m)
{
  m3 r;

  Mat3Transpose(r.m,&m);

  return *(r.m);
}

mat3 operator + (const mat3& m,const float s)
{
  m3 r;

  Mat3AddFloat(r.m,&m,s);

  return *(r.m);
}

mat3 operator - (const mat3& m,const float s)
{
  m3 r;

  Mat3SubtractFloat(r.m,&m,s);

  return *(r.m);
}

mat3 operator * (const mat3& m,const float s)
{
  m3 r;

  Mat3MultiplyFloat(r.m,&m,s);

  return *(r.m);
}

mat3 operator - (const mat3& m)
{
  m3 r;

  Mat3Negate(r.m,&m);

  return *(r.m);
}

vec3 operator * (const mat3& m,const vec3& v)
{
  v3 r;

  Mat3MultiplyVec(r.vec,&m,&v);

  return *(r.vec);
}

mat3 operator + (const mat3& m,const mat3& n)
{
  m3 r;

  Mat3Add(r.m,&m,&n);

  return *(r.m);
}

mat3 operator - (const mat3& m,const mat3& n)
{
  m3 r;

  Mat3Subtract(r.m,&m,&n);

  return *(r.m);
}

mat3 operator * (const mat3& m,const mat3& n)
{
  m3 r;

  Mat3Multiply(r.m,&m,&n);

  return *(r.m);
}

mat3 mat3rotate_rhx(const float angle)
{
  m3 r;

  Mat3RotateRHX(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_lhx(const float angle)
{
  m3 r;

  Mat3RotateLHX(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_rhy(const float angle)
{
  m3 r;

  Mat3RotateRHY(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_lhy(const float angle)
{
  m3 r;

  Mat3RotateLHY(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_rhz(const float angle)
{
  m3 r;

  Mat3RotateRHZ(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_lhz(const float angle)
{
  m3 r;

  Mat3RotateLHZ(r.m,angle);

  return *(r.m);
}

mat3 mat3rotate_rhxy(const float x_angle,const float y_angle)
{
  m3 r;

  Mat3RotateRHXY(r.m,x_angle,y_angle);

  return *(r.m);
}

mat3 mat3rotate_lhxy(const float x_angle,const float y_angle)
{
  m3 r;

  Mat3RotateLHXY(r.m,x_angle,y_angle);

  return *(r.m);
}

mat3 mat3rotate_rhxz(const float x_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHXZ(r.m,x_angle,z_angle);

  return *(r.m);
}

mat3 mat3rotate_lhxz(const float x_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHXZ(r.m,x_angle,z_angle);

  return *(r.m);
}

mat3 mat3rotate_rhyz(const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHYZ(r.m,y_angle,z_angle);

  return *(r.m);
}

mat3 mat3rotate_lhyz(const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHYZ(r.m,y_angle,z_angle);

  return *(r.m);
}

mat3 mat3rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateRHXYZ(r.m,x_angle,y_angle,z_angle);

  return *(r.m);
}

mat3 mat3rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m3 r;

  Mat3RotateLHXYZ(r.m,x_angle,y_angle,z_angle);

  return *(r.m);
}

mat3 mat3scale(const float x_scale,const float y_scale,const float z_scale)
{
  m3 r;

  Mat3Scale(r.m,x_scale,y_scale,z_scale);

  return *(r.m);
}

mat3 mat3scale(vec3& scale)
{
  m3 r;

  Mat3ScaleByVec3(r.m,&scale);

  return *(r.m);
}

/* ------------- *
 * m4 object     *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * m4 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 4-dimensional matrix objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

m4::m4() : FlatElement(64,16),m((mat4*)getAlignedBuffer())
{
  Mat4Identity(m);
}

m4::m4(float m00,float m01,float m02,float m03,
       float m10,float m11,float m12,float m13,
       float m20,float m21,float m22,float m23,
       float m30,float m31,float m32,float m33) :
  FlatElement(64,16),
  m((mat4*)getAlignedBuffer())
{
  m->m00 = m00;
  m->m01 = m01;
  m->m02 = m02;
  m->m03 = m03;
  
  m->m10 = m10;
  m->m11 = m11;
  m->m12 = m12;
  m->m13 = m13;
  
  m->m20 = m20;
  m->m21 = m21;
  m->m22 = m22;
  m->m23 = m23;
  
  m->m30 = m30;
  m->m31 = m31;
  m->m32 = m32;
  m->m33 = m33;
}

m4::m4(const m4& n) :
  FlatElement(64,16),
  m((mat4*)getAlignedBuffer())
{
  assert(NULL != m);
  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m02 = n.m->m02;
  m->m03 = n.m->m03;

  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
  m->m12 = n.m->m12;
  m->m13 = n.m->m13;

  m->m20 = n.m->m20;
  m->m21 = n.m->m21;
  m->m22 = n.m->m22;
  m->m23 = n.m->m23;

  m->m30 = n.m->m30;
  m->m31 = n.m->m31;
  m->m32 = n.m->m32;
  m->m33 = n.m->m33;
}

m4::~m4()
{
  m = NULL;
}

#else

m4::m4()
{
  assert(NULL != (m=new mat4()));
  Mat4Identity(m);
}

m4::m4(float m00,float m01,float m02,float m03,
       float m10,float m11,float m12,float m13,
       float m20,float m21,float m22,float m23,
       float m30,float m31,float m32,float m33)
{
  assert(NULL != (m=new mat4()));

  m->m00 = m00;
  m->m01 = m01;
  m->m02 = m02;
  m->m03 = m03;
  
  m->m10 = m10;
  m->m11 = m11;
  m->m12 = m12;
  m->m13 = m13;
  
  m->m20 = m20;
  m->m21 = m21;
  m->m22 = m22;
  m->m23 = m23;
  
  m->m30 = m30;
  m->m31 = m31;
  m->m32 = m32;
  m->m33 = m33;
}

m4::m4(const m4& n)
{
  assert(NULL != (m=new mat4()));

  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m02 = n.m->m02;
  m->m03 = n.m->m03;

  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
  m->m12 = n.m->m12;
  m->m13 = n.m->m13;

  m->m20 = n.m->m20;
  m->m21 = n.m->m21;
  m->m22 = n.m->m22;
  m->m23 = n.m->m23;

  m->m30 = n.m->m30;
  m->m31 = n.m->m31;
  m->m32 = n.m->m32;
  m->m33 = n.m->m33;
}

m4::~m4()
{
  if ( NULL != m ) delete m;
  m = NULL;
}

#endif

void m4::identity()
{
  Mat4Identity(m);
}

void m4::operator += (const float s)
{
  Mat4AddFloat(m,m,s);
}

void m4::operator -= (const float s)
{
  Mat4SubtractFloat(m,m,s);
}

void m4::operator *= (const float s)
{
  Mat4MultiplyFloat(m,m,s);
}

void m4::operator += (const m4& n)
{
  Mat4Add(m,m,n.m);
}

void m4::operator -= (const m4& n)
{
  Mat4Subtract(m,m,n.m);
}

void m4::operator *= (const m4& n)
{
  Mat4Multiply(m,m,n.m);
}

void m4::operator += (const mat4& n)
{
  Mat4Add(m,m,&n);
}

void m4::operator -= (const mat4& n)
{
  Mat4Subtract(m,m,&n);
}

void m4::operator *= (const mat4& n)
{
  Mat4Multiply(m,m,&n);
}

mat4* m4::operator->()
{
  return m;
}

m4& m4::operator=(const m4& n)
{
  m->m00 = n.m->m00;
  m->m01 = n.m->m01;
  m->m02 = n.m->m02;
  m->m03 = n.m->m03;

  m->m10 = n.m->m10;
  m->m11 = n.m->m11;
  m->m12 = n.m->m12;
  m->m13 = n.m->m13;

  m->m20 = n.m->m20;
  m->m21 = n.m->m21;
  m->m22 = n.m->m22;
  m->m23 = n.m->m23;

  m->m30 = n.m->m30;
  m->m31 = n.m->m31;
  m->m32 = n.m->m32;
  m->m33 = n.m->m33;

  return *this;
}

m4 operator + (const m4& m,const float s)
{
  m4 r;

  Mat4AddFloat(r.m,m.m,s);

  return r;
}

m4 operator - (const m4& m,const float s)
{
  m4 r;

  Mat4SubtractFloat(r.m,m.m,s);

  return r;
}

m4 operator * (const m4& m,const float s)
{
  m4 r;

  Mat4MultiplyFloat(r.m,m.m,s);

  return r;
}

m4 operator - (const m4& m)
{
  m4 r;

  Mat4Negate(r.m,m.m);

  return r;
}

m4 operator + (const m4& m,const m4& n)
{
  m4 r;

  Mat4Add(r.m,m.m,n.m);

  return r;
}

m4 operator - (const m4& m,const m4& n)
{
  m4 r;

  Mat4Subtract(r.m,m.m,n.m);

  return r;
}

m4 operator * (const m4& m,const m4& n)
{
  m4 r;

  Mat4Multiply(r.m,m.m,n.m);

  return r;
}

v4 operator * (const m4& m,const v4& v)
{
  v4 r;

  Mat4MultiplyVec(r.vec,m.m,v.vec);

  return r;
}

m4 m4identity()
{
  m4 r;
  return r;
}

m4 transpose(const m4& m)
{
  m4 r;

  Mat4Transpose(r.m,m.m);

  return r;
}

m4 lookAt(const v3& from,const v3& at)
{
  m4 r;

  Mat4LookAt(r.m,from.vec,at.vec);

  return r;
}

m4 shadow(const v3& planeNormal,const float planeOffset,const v3& lightPos)
{
  m4 r;

  Mat4ShadowMatrix(r.m,planeNormal.vec,planeOffset,lightPos.vec);

  return r;
}

m4 glToD3D(const m4& m)
{
  m4 r;

  Mat4GlToD3DProjMat(r.m,m.m);

  return r;
}

m4 lookAt_lh(const v3& eye,const v3& lookAt,const v3& up)
{
  m4 r;

  Mat4LookAtLH(r.m,eye.vec,lookAt.vec,up.vec);

  return r;
}

m4 m4scale(const float x_scale,const float y_scale,const float z_scale)
{
  m4 r;

  Mat4Scale(r.m,x_scale,y_scale,z_scale);

  return r;
}

m4 m4scale(const v4& v)
{
  m4 r;

  Mat4Scale(r.m,v.vec->x,v.vec->y,v.vec->z);

  return r;
}

m4 m4rotate_rhx(const float angle)
{
  m4 r;

  Mat4RotateRHX(r.m,angle);

  return r;
}

m4 m4rotate_lhx(const float angle)
{
  m4 r;

  Mat4RotateLHX(r.m,angle);

  return r;
}

m4 m4rotate_rhy(const float angle)
{
  m4 r;

  Mat4RotateRHY(r.m,angle);

  return r;
}

m4 m4rotate_lhy(const float angle)
{
  m4 r;

  Mat4RotateLHY(r.m,angle);

  return r;
}

m4 m4rotate_rhz(const float angle)
{
  m4 r;

  Mat4RotateRHZ(r.m,angle);

  return r;
}

m4 m4rotate_lhz(const float angle)
{
  m4 r;

  Mat4RotateLHZ(r.m,angle);

  return r;
}

m4 m4rotate_rhxy(const float x_angle,const float y_angle)
{
  m4 r;

  Mat4RotateRHXY(r.m,x_angle,y_angle);

  return r;
}

m4 m4rotate_lhxy(const float x_angle,const float y_angle)
{
  m4 r;

  Mat4RotateLHXY(r.m,x_angle,y_angle);

  return r;
}

m4 m4rotate_rhxz(const float x_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHXZ(r.m,x_angle,z_angle);

  return r;
}

m4 m4rotate_lhxz(const float x_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHXZ(r.m,x_angle,z_angle);

  return r;
}

m4 m4rotate_rhyz(const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHYZ(r.m,y_angle,z_angle);

  return r;
}

m4 m4rotate_lhyz(const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHYZ(r.m,y_angle,z_angle);

  return r;
}

m4 m4rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHXYZ_Asm(r.m,x_angle,y_angle,z_angle);

  return r;
}

m4 m4rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHXYZ_Asm(r.m,x_angle,y_angle,z_angle);

  return r;
}

m4 m4translate_rh(const float delta_x,const float delta_y,const float delta_z)
{
  m4 r;

  Mat4TranslateRH(r.m,delta_x,delta_y,delta_z);

  return r;
}

m4 m4translate_lh(const float delta_x,const float delta_y,const float delta_z)
{
  m4 r;

  Mat4TranslateLH(r.m,delta_x,delta_y,delta_z);

  return r;
}

m4 translate_rh(const v3& v)
{
  m4 r;

  Mat4TranslateRH_Vec3(r.m,v.vec);

  return r;
}

m4 translate_lh(const v3& v)
{
  m4 r;

  Mat4TranslateLH_Vec3(r.m,v.vec);

  return r;
}


m4 translate_rh(const v4& v)
{
  m4 r;

  Mat4TranslateRH_Vec4(r.m,v.vec);

  return r;
}

m4 translate_lh(const v4& v)
{
  m4 r;

  Mat4TranslateLH_Vec4(r.m,v.vec);

  return r;
}

m4 m4ortho(const float left,
	   const float right,
	   const float top,
	   const float bottom,
	   const float zNear,
	   const float zFar,
	   const int32_t d3dFlag)
{
  m4 r;

  Mat4OrthoMatrix(r.m,
		  left,
		  right,
		  top,
		  bottom,
		  zNear,
		  zFar,
		  d3dFlag);

  return r;
}

m4 m4orthoStruct(const orthoMatrix* s)
{
  m4 r;

  Mat4OrthoStruct(r.m,s);

  return r;
}

m4 m4perspective(const float    fov,
		 const float    width,
		 const float    height,
		 const float    zNear,
		 const float    zFar,
		 const uint32_t d3dflag)
{
  m4 r;

  Mat4Perspective(r.m,
		  fov,
		  width,
		  height,
		  zNear,
		  zFar,
		  d3dflag);

  return r;
}

m4 m4perspective(const struct perspectiveMatrix* s)
{
  m4 r;

  Mat4PerspectiveX(r.m,s);

  return r;
}

m4 m4cubemap(const unsigned int face)
{
  m4 r;

  Mat4CubemapMatrix(r.m,face);

  return r;
}

m4 m4cubemapProjection(const float zNear,
		       const float zFar,
		       const uint32_t d3dflag)
{
  m4 r;

  Mat4CubemapProjectionMat(r.m,zNear,zFar,d3dflag);

  return r;
}

// XXX: THIS REQUIRES REVIEW

m3 m3from_m4(const mat4& m)
{
  m3 r;

  Mat3RotationFromMat4(r.m,&m);

  return r;
}

m4 m4from_m3(const mat3& m)
{
  m4 r;

  Mat4FromMat3(r.m,&m);

  return r;
}

#if 0
XXX: Required method missing ... recheck and insert
m4 m4inverse(const m4& m)
{
  m4 r;

  Mat4Inverse(r.m,m.m);

  return r;
}
#endif

/* ------------- *
 * mat4 object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * mat4 is the simple matrix object that stores and operations on 4-D      *
 * cartesian objects. mat4 generally requires use of unaligned or generic  *
 * methods on most processor families to operate correctly.                *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

mat4 operator + (const mat4& m,const float s)
{
  m4 r;

  Mat4AddFloat(r.m,&m,s);

  return *(r.m);
}

mat4 operator - (const mat4& m,const float s)
{
  m4 r;

  Mat4SubtractFloat(r.m,&m,s);

  return *(r.m);
}

mat4 operator * (const mat4& m,const float s)
{
  m4 r;

  Mat4MultiplyFloat(r.m,&m,s);

  return *(r.m);
}

mat4 operator - (const mat4& m)
{
  m4 r;

  Mat4Negate(r.m,&m);

  return *(r.m);
}

mat4 operator + (const mat4& m,const mat4& n)
{
  m4 r;

  Mat4Add(r.m,&m,&n);

  return *(r.m);
}

mat4 operator - (const mat4& m,const mat4& n)
{
  m4 r;

  Mat4Subtract(r.m,&m,&n);

  return *(r.m);
}

mat4 operator * (const mat4& m,const mat4& n)
{
  m4 r;

  Mat4Multiply(r.m,&m,&n);

  return *(r.m);
}

vec4 operator * (const mat4& m,const vec4& v)
{
  v4 r;

  Mat4MultiplyVec(r.vec,&m,&v);

  return *(r.vec);
}

mat4 mat4identity()
{
  m4 r;

  Mat4Identity(r.m);

  return *(r.m);
}

#if 0
XXX: Required method missing ... recheck and insert
mat4 mat4inverse(const mat4& m)
{
  m4 r;

  Mat4Inverse(r.m,&m);

  return *(r.m);
}
#endif

mat4 transpose(const mat4& m)
{
  m4 r;

  Mat4Transpose(r.m,&m);

  return *(r.m);
}

mat4 lookAt(const vec3& from,const vec3& at)
{
  m4 r;

  Mat4LookAt(r.m,&from,&at);

  return *(r.m);
}

mat4 shadow(const vec3& planeNormal,const float planeOffset,const vec3& lightPos)
{
  m4 r;

  Mat4ShadowMatrix(r.m,&planeNormal,planeOffset,&lightPos);

  return *(r.m);
}

mat4 glToD3D(const mat4& m)
{
  m4 r;

  Mat4GlToD3DProjMat(r.m,&m);

  return *(r.m);
}

mat4 lookAt_lh(const vec3& eye,const vec3& lookAt,const vec3& up)
{
  m4 r;

  Mat4LookAtLH(r.m,&eye,&lookAt,&up);

  return *(r.m);
}

mat4 mat4scale(const float x_scale,const float y_scale,const float z_scale)
{
  m4 r;

  Mat4Scale(r.m,x_scale,y_scale,z_scale);

  return *(r.m);
}

mat4 mat4scale(const vec4& vScale)
{
  m4 r;

  Mat4Scale(r.m,vScale.x,vScale.y,vScale.z);

  return *(r.m);
}

mat4 mat4rotate_rhx(const float angle)
{
  m4 r;

  Mat4RotateRHX(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_lhx(const float angle)
{
  m4 r;

  Mat4RotateLHX(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_rhy(const float angle)
{
  m4 r;

  Mat4RotateRHY(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_lhy(const float angle)
{
  m4 r;

  Mat4RotateLHY(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_rhz(const float angle)
{
  m4 r;

  Mat4RotateRHZ(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_lhz(const float angle)
{
  m4 r;

  Mat4RotateLHZ(r.m,angle);

  return *(r.m);
}

mat4 mat4rotate_rhxy(const float x_angle,const float y_angle)
{
  m4 r;

  Mat4RotateRHXY(r.m,x_angle,y_angle);

  return *(r.m);
}

mat4 mat4rotate_lhxy(const float x_angle,const float y_angle)
{
  m4 r;

  Mat4RotateLHXY(r.m,x_angle,y_angle);

  return *(r.m);
}

mat4 mat4rotate_rhxz(const float x_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHXZ(r.m,x_angle,z_angle);

  return *(r.m);
}

mat4 mat4rotate_lhxz(const float x_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHXZ(r.m,x_angle,z_angle);

  return *(r.m);
}

mat4 mat4rotate_rhyz(const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHYZ(r.m,y_angle,z_angle);

  return *(r.m);
}

mat4 mat4rotate_lhyz(const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHYZ(r.m,y_angle,z_angle);

  return *(r.m);
}

mat4 mat4rotate_rhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateRHXYZ_Asm(r.m,x_angle,y_angle,z_angle);

  return *(r.m);
}

mat4 mat4rotate_lhxyz(const float x_angle,const float y_angle,const float z_angle)
{
  m4 r;

  Mat4RotateLHXYZ_Asm(r.m,x_angle,y_angle,z_angle);

  return *(r.m);
}


mat4 mat4translate_rh(const float delta_x,const float delta_y,const float delta_z)
{
  m4 r;

  Mat4TranslateRH(r.m,delta_x,delta_y,delta_z);

  return *(r.m);
}

mat4 mat4translate_lh(const float delta_x,const float delta_y,const float delta_z)
{
  m4 r;

  Mat4TranslateLH(r.m,delta_x,delta_y,delta_z);

  return *(r.m);
}

mat4 translate_rh(const vec3& v)
{
  m4 r;

  Mat4TranslateRH_Vec3(r.m,&v);

  return *(r.m);
}

mat4 translate_lh(const vec3& v)
{
  m4 r;

  Mat4TranslateLH_Vec3(r.m,&v);

  return *(r.m);
}

mat4 translate_rh(const vec4& v)
{
  m4 r;

  Mat4TranslateRH_Vec4(r.m,&v);

  return *(r.m);
}

mat4 translate_lh(const vec4& v)
{
  m4 r;

  Mat4TranslateLH_Vec4(r.m,&v);

  return *(r.m);
}

mat4 mat4ortho(const float left,
	       const float right,
	       const float top,
	       const float bottom,
	       const float zNear,
	       const float zFar,
	       const int32_t d3dFlag)
{
  m4 r;

  Mat4OrthoMatrix(r.m,
		  left,
		  right,
		  top,
		  bottom,
		  zNear,
		  zFar,
		  d3dFlag);

  return *(r.m);
}

mat4 mat4orthoStruct(const orthoMatrix* s)
{
  m4 r;

  Mat4OrthoStruct(r.m,s);

  return *(r.m);
}

mat4 mat4perspective(const float    fov,
		     const float    width,
		     const float    height,
		     const float    zNear,
		     const float    zFar,
		     const uint32_t d3dflag)
{
  m4 r;

  Mat4Perspective(r.m,
		  fov,
		  width,
		  height,
		  zNear,
		  zFar,
		  d3dflag);

  return *(r.m);
}

mat4 mat4perspective(const struct perspectiveMatrix* s)
{
  m4 r;

  Mat4PerspectiveX(r.m,s);

  return *(r.m);
}

mat4 mat4cubemap(const unsigned int face)
{
  m4 r;

  Mat4CubemapMatrix(r.m,face);

  return *(r.m);
}

mat4 mat4cubemapProjection(const float zNear,
			   const float zFar,
			   const uint32_t d3dflag)
{
  m4 r;

  Mat4CubemapProjectionMat(r.m,zNear,zFar,d3dflag);

  return *(r.m);
}

mat3 mat3from_mat4(const mat4& m)
{
  m3 r;

  Mat3RotationFromMat4(r.m,&m);

  return *(r.m);
}

mat4 mat4from_mat3(const mat3& m)
{
  m4 r;

  Mat4FromMat3(r.m,&m);

  return *(r.m);
}

/* ------------- *
 * quat object   *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * quat is an object designed to hide the complexities of aligned versus   *
 * unaligned management of baycentric vector objects. These calculations   *
 * simplify some polar coordinate operations.                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

quat::quat() : FlatElement(16,16),q((quaternion*)getAlignedBuffer())
{
  assert(NULL != q);
  q->x =
  q->y =
  q->z =
  q->w = 0.0f;
}

quat::quat(float x,float y,float z,float w) :
  FlatElement(16,16),
  q((quaternion*)getAlignedBuffer())
{
  assert(NULL != q);
  q->x = x;
  q->y = y;
  q->z = z;
  q->w = w;
}

quat::quat(vec4& v) :
  FlatElement(16,16),
  q((quaternion*)getAlignedBuffer())
{
  assert(NULL != q);
  q->x = v.x;
  q->y = v.y;
  q->z = v.z;
  q->w = v.w;
}

quat::quat(const quat& qp) :
  FlatElement(16,16),
  q((quaternion*)getAlignedBuffer())
{
  assert(NULL != q);
  *q = *(qp.q);
}

quat::~quat()
{
  q = NULL;
}

#else

quat::quat()
{
  assert(NULL != (q=new quaternion()));
  q->x =
  q->y =
  q->z =
  q->w = 0.0f;
}

quat::quat(float x,float y,float z,float w)
{
  assert(NULL != (q=new quaternion()));
  q->x = x;
  q->y = y;
  q->z = z;
  q->w = w;
}

quat::quat(vec4& v)
{
  assert(NULL != (q=new quaternion()));
  q->x = v.x;
  q->y = v.y;
  q->z = v.z;
  q->w = v.w;
}

quat::quat(const quat& qp)
{
  assert(NULL != (q=new quaternion()));
  *q = *(qp.q);
}

quat::~quat()
{
  if ( NULL != q ) delete q;
  q = NULL;
}

#endif

quat::operator quaternion*()
{
  return q;
}

quat::operator quaternion()
{
  return *q;
}

quat::operator m3()
{
  m3 r;

  QuaternionToMat3(r.m,q);

  return r;
}

quat::operator m4()
{
  m4 r;

  QuaternionToMat4(r.m,q);

  return r;
}

quat::operator mat3()
{
  m3 r;

  QuaternionToMat3(r.m,q);

  return *(r.m);
}

quat::operator mat4()
{
  m4 r;

  QuaternionToMat4(r.m,q);

  return *(r.m);
}

void quat::inverse()
{
  QuaternionInverse(q,q);
}

void quat::normalize()
{
  QuaternionNormalize(q,q);
}

void quat::operator += (const quat& qr)
{
  QuaternionAdd(q,q,qr.q);
}

void quat::operator *= (const quat& qr)
{
  QuaternionMultiply(q,q,qr.q);
}

quaternion* quat::operator->()
{
  return q;
}

quat& quat::operator=(const quat& qp)
{
  *q = *(qp.q);
  return *this;
}

quat operator + (const quat& q,const quat& p)
{
  quat r;

  QuaternionAdd(r.q,q.q,p.q);

  return r;
}

quat operator * (const quat& q,const quat& p)
{
  quat r;

  QuaternionMultiply(r.q,q.q,p.q);

  return r;
}

float dot(const quat& q,const quat& p)
{
  float r;

  QuaternionDot(&r,q.q,p.q);

  return r;
}

quat normalize(const quat& q)
{
  quat r;

  QuaternionNormalize(r.q,q.q);

  return r;
}

quat inverse(const quat& q)
{
  quat r;

  QuaternionInverse(r.q,q.q);

  return r;
}

quat quatFromAxis(const vec3& v,const float angle)
{
  quat r;

  QuaternionFromAxis(r.q,&v,angle);

  return r;
}

m4 quatToM4(const quat& q)
{
  m4 m;

  QuaternionToMat4(m.m,q.q);

  return m;
}

quat quatFromM3(const m3& m)
{
  quat q;

  QuaternionFromMat3(q.q,m.m);

  return q;
}

quat quatFromM4(const m4& m)
{
  quat q;

  QuaternionFromMat4(q.q,m.m);

  return q;
}

quat quatSlerp(const float s,const quat& q,const quat& p)
{
  quat r;

  QuaternionSlerp(r.q,s,q.q,p.q);

  return r;
}

/* ------------- *
 * quaternion    *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 * quaternion is a simple baycentric math object. There is no protection   *
 * from errors that may occur from memory alignment issues. quaternion is  *
 * generally to be paired with either the generic or unaligned methods     *
 * to assure correct operation.                                            *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

quaternion operator + (const quaternion& q,const quaternion& p)
{
  quat r;

  QuaternionAdd(r.q,&q,&p);

  return *(r.q);
}

quaternion operator * (const quaternion& q,const quaternion& p)
{
  quat r;

  QuaternionMultiply(r.q,&q,&p);

  return *(r.q);
}

float dot(const quaternion& q,const quaternion& p)
{
  float r;

  QuaternionDot(&r,&q,&p);

  return r;
}

quaternion inverse(const quaternion& q)
{
  quat r;

  QuaternionInverse(r.q,&q);

  return *(r.q);
}

quaternion normalize(const quaternion& q)
{
  quat r;

  QuaternionNormalize(r.q,&q);

  return *(r.q);
}

quaternion quaternionFromAxis(const vec3* v,const float angle)
{
  quat r;

  QuaternionFromAxis(r.q,v,angle);

  return *(r.q);
}

mat4 quatToMat4(const quaternion& q)
{
  m4 m;

  QuaternionToMat4(m.m,&q);

  return *(m.m);
}

quaternion quatFromMat3(const mat3& m)
{
  quat q;

  QuaternionFromMat3(q.q,&m);

  return *(q.q);
}

quaternion quatFromMat4(const mat4& m)
{
  quat q;

  QuaternionFromMat4(q.q,&m);

  return *(q.q);
}

quaternion quatSlerp(const float s,const quaternion& q,const quaternion& p)
{
  quat r;

  QuaternionSlerp(r.q,s,&q,&p);

  return *(r.q);
}

/* --------------- *
 * v2 array object *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 * v2 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 2-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */


#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v2array::v2array() :
  FlatBuffer(8,16,1,0),
  m_Vec2Array(NULL),
  m_ArrayCount(0) {}

v2array::v2array(float x,float y) :
  FlatBuffer(8,16,1,0),
  m_Vec2Array((vec2*)getAlignedPtr()),
  m_ArrayCount(1)
{
  m_Vec2Array[0].x = x;
  m_Vec2Array[0].y = y;
}

v2array::v2array(int iCount) :
  FlatBuffer(8,16,iCount,0),
  m_Vec2Array((vec2*)getAlignedPtr()),
  m_ArrayCount(iCount)
{
  vec2  vTemp = {0.0,0.0};
  vec2* vp    = (vec2*)m_Vec2Array;

  for( int i=0 ; i < iCount ; ++i ) *vp++ = vTemp;
}

v2array::v2array(int iCount,vec2* pVecArray) :
  FlatBuffer(8,16,iCount,0),
  m_Vec2Array((vec2*)getAlignedPtr()),
  m_ArrayCount(iCount)
{
  vec2* vp  = m_Vec2Array;
  vec2* vap = pVecArray;

  for( int i=0 ; i < iCount ; ++i ) *vp++ = *vap++;
}

v2array::v2array(const v2array& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_Vec2Array((vec2*)getAlignedPtr()),
  m_ArrayCount(va.m_ArrayCount)
{
  vec2* vp  = (vec2*)m_Vec2Array;
  vec2* vap = (vec2*)va.m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

v2array::v2array(v2buf& pv) :
  FlatBuffer(8,16,pv.m_ArrayCount,0),
  m_Vec2Array((vec2*)getAlignedPtr()),
  m_ArrayCount(pv.length())
{
  vec2* vp = (vec2*)m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v2array::~v2array()
{
  m_Vec2Array = NULL;
}

int v2array::length()
{
  return (m_ArrayCount=getElementCount());
}

int v2array::size()
{
  return (m_ElementSize=getElementSize());
}

void v2array::add(v2& v)
{
  if ( NULL != m_Vec2Array )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      assert(NULL != (m_Vec2Array=(vec2*)getAlignedPtr()));
      FlatBuffer::add(0,v.vec);
    }
}

void v2array::add(vec2& v)
{
  if ( NULL != m_Vec2Array )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      assert(NULL != (m_Vec2Array=(vec2*)getAlignedPtr()));
      FlatBuffer::add(0,&v);
    }
}

void v2array::operator += (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2AddFloatToBlock(m_Vec2Array,s,getElementCount());
}

void v2array::operator -= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractFloatFromBlock(m_Vec2Array,s,getElementCount());
}

void v2array::operator *= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByFloat(m_Vec2Array,s,getElementCount());
}

void v2array::operator /= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByFloat(m_Vec2Array,s,getElementCount());
}

void v2array::operator += (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2AddVec2ToBlock(m_Vec2Array,v.vec,getElementCount());
}

void v2array::operator -= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractVec2FromBlock(m_Vec2Array,v.vec,getElementCount());
}

void v2array::operator *= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByVec2(m_Vec2Array,v.vec,getElementCount());
}

void v2array::operator /= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByVec2(m_Vec2Array,v.vec,getElementCount());
}

void v2array::operator += (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2AddVec2ToBlock(m_Vec2Array,&v,getElementCount());
}

void v2array::operator -= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractVec2FromBlock(m_Vec2Array,&v,getElementCount());
}

void v2array::operator *= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByVec2(m_Vec2Array,&v,getElementCount());
}

void v2array::operator /= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByVec2(m_Vec2Array,&v,getElementCount());
}

void v2array::operator += (struct v2array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2AddBlockToBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator -= (struct v2array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2SubtractBlockFromBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator *= (struct v2array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2MultiplyBlockByBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator /= (struct v2array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2DivideBlockByBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator *= (m2& m)
{
  if ( NULL != m_Vec2Array )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat2MultiplyVec(&m_Vec2Array[i],m.m,&m_Vec2Array[i]);
	}
    }
}

void v2array::operator *= (mat2& m)
{
  if ( NULL != m_Vec2Array )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat2MultiplyVec(&m_Vec2Array[i],&m,&m_Vec2Array[i]);
	}
    }
}

vec2& v2array::operator[](int iItem)
{
  int iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec2 vTemp = {0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItem;

  return m_Vec2Array[iItem];
}

v2array& v2array::operator=(v2buf& v)
{
  m_Vec2Array  = (vec2*)resize(8,16,v.m_ArrayCount,0);
  m_ArrayCount = v.length();
  vec2* vp     = (vec2*)m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = v[i];

  return *this;
}

v2array& v2array::operator=(const v2array& va)
{
  m_Vec2Array = (vec2*)resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,0);
  m_ArrayCount = va.m_ArrayCount;

  vec2* vap = va.m_Vec2Array;
  vec2* vp  = m_Vec2Array;

  for( int i=0 ; i < va.m_ArrayCount ; ++i ) *vp++ = *vap++;

  return *this;
}

void v2array::sqr()
{
  Vec2SqrBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::sqr(const v2array& va)
{
  Vec2SqrBlock(m_Vec2Array,
	       va.m_Vec2Array,
	       (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::sqrt()
{
  Vec2SqrtBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::sqrt(const v2array& va)
{
  Vec2SqrtBlock(m_Vec2Array,
		va.m_Vec2Array,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::normalize()
{
  Vec2NormalizeBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::normalize(const v2array& va)
{
  Vec2NormalizeBlock(m_Vec2Array,
		     va.m_Vec2Array,
		     (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::lerp(const v2array& va,const float step)
{
  Vec2LerpBlock(m_Vec2Array,
		m_Vec2Array,
		va.m_Vec2Array,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::lerp(const v2array& va,const v2array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= vb.m_ArrayCount ? iCount : vb.m_ArrayCount);

  Vec2LerpBlock(m_Vec2Array,
		va.m_Vec2Array,
		vb.m_Vec2Array,
		step,
		iCount);
}

void v2array::dot(float* fpArray,const int32_t iArrayLength,const v2array& va)
{
  if ( NULL == fpArray ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= iArrayLength ? iCount : iArrayLength);

  Vec2DotBlock(fpArray,
	       m_Vec2Array,
	       va.m_Vec2Array,
	       iCount);
}

void v2array::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray ) return;

  Vec2LengthBlock(fpArray,
		  m_Vec2Array,
		  (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#else

v2array::v2array() :
  m_Vec2Array(NULL),
  m_ArrayCount(0) {}

v2array::v2array(float x,float y)
{
  assert(NULL != (m_Vec2Array=new vec2()));
  m_Vec2Array[0].x = x;
  m_Vec2Array[0].y = y;
  m_ArrayCount = 1;
}

v2array::v2array(int iCount) :
  m_ArrayCount(0)
{
  assert(NULL != (m_Vec2Array=new vec2[iCount]));
  m_ArrayCount = iCount;

  vec2  vTemp = {0.0,0.0};
  vec2* vp    = (vec2*)m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = vTemp;
}

v2array::v2array(int iCount,vec2* pVecArray) :
  m_ArrayCount(0)
{
  assert(NULL != (m_Vec2Array=new vec2[iCount]));
  m_ArrayCount = iCount;

  vec2* vp = (vec2*)m_Vec2Array;

  for( int i=0 ; i < iCount ; ++i ) *vp++ = *pVecArray++;
}

v2array::v2array(const v2array& va) :
  m_ArrayCount(va.m_ArrayCount)
{
  assert(NULL != (m_Vec2Array=new vec2[m_ArrayCount]));

  vec2* vap = va.m_Vec2Array;
  vec2* vp  = m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

// XXX: Check for memory leak
//

v2array::v2array(v2buf& pv) :
  m_ArrayCount(pv.length())
{
  assert(NULL != (m_Vec2Array=new vec2[m_ArrayCount]));

  vec2* vp = (vec2*)m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v2array::~v2array()
{
  if ( NULL != m_Vec2Array ) delete m_Vec2Array;
  m_Vec2Array  = NULL;
  m_ArrayCount = 0;
}

int v2array::length()
{
  return m_ArrayCount;
}

int v2array::size()
{
  return sizeof(vec2);
}

void v2array::add(v2& v)
{
  vec2* vec;

  assert(NULL != (vec=new vec2[1+m_ArrayCount]));

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      vec[i].x = m_Vec2Array[i].x;
      vec[i].y = m_Vec2Array[i].y;
    }
  vec[m_ArrayCount].x = v.vec->x;
  vec[m_ArrayCount].y = v.vec->y;

  ++m_ArrayCount;

  if ( m_Vec2Array ) delete m_Vec2Array;

  m_Vec2Array = vec;
}

void v2array::add(vec2& v)
{
  vec2* vec;

  assert(NULL != (vec=new vec2[1+m_ArrayCount]));

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      vec[i].x = m_Vec2Array[i].x;
      vec[i].y = m_Vec2Array[i].y;
    }

  vec[m_ArrayCount].x = v.x;
  vec[m_ArrayCount].y = v.y;

  ++m_ArrayCount;

  if ( NULL != m_Vec2Array ) delete m_Vec2Array;

  m_Vec2Array = vec;
}

void v2array::operator += (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2AddFloatToBlock(m_Vec2Array,s,m_ArrayCount);
}

void v2array::operator -= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractFloatFromBlock(m_Vec2Array,s,m_ArrayCount);
}

void v2array::operator *= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByFloat(m_Vec2Array,s,m_ArrayCount);
}

void v2array::operator /= (const float s)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByFloat(m_Vec2Array,s,m_ArrayCount);
}

void v2array::operator += (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2AddVec2ToBlock(m_Vec2Array,v.vec,m_ArrayCount);
}

void v2array::operator -= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractVec2FromBlock(m_Vec2Array,v.vec,m_ArrayCount);
}

void v2array::operator *= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByVec2(m_Vec2Array,v.vec,m_ArrayCount);
}

void v2array::operator /= (const v2& v)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByVec2(m_Vec2Array,v.vec,m_ArrayCount);
}

void v2array::operator += (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2AddVec2ToBlock(m_Vec2Array,&v,m_ArrayCount);
}

void v2array::operator -= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2SubtractVec2FromBlock(m_Vec2Array,&v,m_ArrayCount);
}

void v2array::operator *= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2MultiplyBlockByVec2(m_Vec2Array,&v,m_ArrayCount);
}

void v2array::operator /= (const vec2& v)
{
  if ( NULL != m_Vec2Array ) Vec2DivideBlockByVec2(m_Vec2Array,&v,m_ArrayCount);
}

void v2array::operator += (struct v2array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2AddBlockToBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator -= (struct v2array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2SubtractBlockFromBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator *= (struct v2array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2MultiplyBlockByBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator /= (struct v2array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_Vec2Array )
    {
      Vec2DivideBlockByBlock(m_Vec2Array,va.m_Vec2Array,iElementCount);
    }
}

void v2array::operator *= (m2& m)
{
  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat2MultiplyVec(&m_Vec2Array[i],m.m,&m_Vec2Array[i]);
    }
}

void v2array::operator *= (mat2& m)
{
  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat2MultiplyVec(&m_Vec2Array[i],&m,&m_Vec2Array[i]);
    }
}

vec2& v2array::operator[](int iItem)
{
  if ( iItem < m_ArrayCount )
    {
      ;
    }
  else if ( iItem == m_ArrayCount )
    {
      vec2 vTemp = {0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  return m_Vec2Array[iItem];
}

v2array& v2array::operator=(v2buf& v)
{
  vec2* vec = new vec2[v.length()];

  assert(NULL != vec);

  if ( NULL != m_Vec2Array ) delete m_Vec2Array;

  m_ArrayCount = v.length();
  m_Vec2Array  = vec;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vec++ = v[i];

  return *this;
}

v2array& v2array::operator=(const v2array& va)
{
  vec2* vec = new vec2[va.m_ArrayCount];

  assert(NULL != vec);

  if ( NULL != m_Vec2Array ) delete m_Vec2Array;

  m_ArrayCount = va.m_ArrayCount;
  m_Vec2Array  = vec;

  vec2* vap = va.m_Vec2Array;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vec++ = *vap++;

  return *this;
}

void v2array::sqr()
{
  Vec2SqrBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::sqr(const v2array& va)
{
  Vec2SqrBlock(m_Vec2Array,
	       va.m_Vec2Array,
	       (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::sqrt()
{
  Vec2SqrtBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::sqrt(const v2array& va)
{
  Vec2SqrBlock(m_Vec2Array,
	       va.m_Vec2Array,
	       (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::normalize()
{
  Vec2NormalizeBlock(m_Vec2Array,m_Vec2Array,m_ArrayCount);
}

void v2array::normalize(const v2array& va)
{
  Vec2NormalizeBlock(m_Vec2Array,
		     va.m_Vec2Array,
		     (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::lerp(const v2array& va,const float step)
{
  Vec2LerpBlock(m_Vec2Array,
		m_Vec2Array,
		va.m_Vec2Array,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2array::lerp(const v2array& va,const v2array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= vb.m_ArrayCount ? iCount : vb.m_ArrayCount);

  Vec2LerpBlock(m_Vec2Array,
		va.m_Vec2Array,
		vb.m_Vec2Array,
		step,
		iCount);
}

void v2array::dot(float* fpArray,const int32_t iArrayLength,const v2array& va)
{
  if ( NULL == fpArray ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= iArrayLength ? iCount : iArrayLength);

  Vec2DotBlock(fpArray,
	       m_Vec2Array,
	       va.m_Vec2Array,
	       iCount);
}

void v2array::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray ) return;

  Vec2LengthBlock(fpArray,
		  m_Vec2Array,
		  (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#endif

/* ---------------- *
 * v2 buffer object *
 * -----------------*----------------------------------------------------- *
 *                                                                         *
 * v2 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 2-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

// XXX: iVecOffset MUST BE EVEN! CANNOT BE ODD!

v2buf::v2buf(int iVecOffset) :
  FlatBuffer(8,8,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(getElementSize()) {}

v2buf::v2buf(int iVecOffset,float x,float y) :
  FlatBuffer(8,8,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(1),
  m_ElementSize(getElementSize())
{
  vec2* vp = (vec2*)((char*)m_VecArray + iVecOffset);
  vp->x = x;
  vp->y = y;
}

v2buf::v2buf(int iCount,int iSize,int iVecOffset,vec2* pVecArray) :
  FlatBuffer(iSize,8,iCount,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(iCount),
  m_ElementSize(getElementSize())
{
  vec2* pv = (vec2*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = *pVecArray++;
      pv  = (vec2*)((char*)pv + m_ElementSize);
    }
}

v2buf::v2buf(const v2buf& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(va.m_VecOffset),
  m_ArrayCount(va.m_ArrayCount),
  m_ElementSize(getElementSize())
{
  vec2* vap = (vec2*)((char*)va.m_VecArray + va.m_VecOffset);
  vec2* vp  = (vec2*)((char*)m_VecArray    + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vap = (vec2*)((char*)vap + m_ElementSize);
      vp  = (vec2*)((char*)vp  + m_ElementSize);
    }
}

v2buf::~v2buf()
{
  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v2buf::length()
{
  return m_ArrayCount;
}

int v2buf::size()
{
  return m_ElementSize;
}

int v2buf::offset()
{
  return m_VecOffset;
}

void* v2buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v2buf::add(v2& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,v.vec);
    }
}

void v2buf::add(vec2& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,&v);
    }
}

void v2buf::operator += (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator -= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator *= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulBlockByFloatBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator /= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator += (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddVec2ToBlockBySize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator -= (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubVec2FromBlkBySize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator *= (const v2& v)
{
  void* pv    = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulVec2ByBlockSize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator /= (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivVec2ByBlockSize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator += (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddVec2ToBlockBySize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator -= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubVec2FromBlkBySize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator *= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulVec2ByBlockSize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator /= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivVec2ByBlockSize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator += (struct v2buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = getElementCount();
  int   iThatCount = va.getElementCount();

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufAddBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator -= (struct v2buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = getElementCount();
  int   iThatCount = va.getElementCount();

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufSubBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator *= (struct v2buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = getElementCount();
  int   iThatCount = va.getElementCount();

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufMulBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator /= (struct v2buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = getElementCount();
  int   iThatCount = va.getElementCount();

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufDivBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator *= (m2& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat2MultiplyVec((vec2*)pv,m.m,(vec2*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

void v2buf::operator *= (mat2& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat2MultiplyVec((vec2*)pv,&m,(vec2*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

vec2& v2buf::operator[](int iItem)
{
  int   iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec2 vTemp = {0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItemCount;

  return *((vec2*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset));
}

v2buf& v2buf::operator=(const v2buf& va)
{
  m_VecArray    = resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_VecOffset);
  m_VecOffset   = va.m_VecOffset;
  m_ArrayCount  = va.m_ArrayCount;
  m_ElementSize = va.m_ElementSize;

  vec2* vap = (vec2*)((char*)va.m_VecArray + va.m_VecOffset);
  vec2* vp  = (vec2*)((char*)m_VecArray    + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec2*)((char*)vp  + m_ElementSize);
      vap = (vec2*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v2buf::sqr()
{
  Vec2BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v2buf::sqr(const v2buf& va)
{
  Vec2BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::sqrt()
{
  Vec2BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v2buf::sqrt(const v2buf& va)
{
  Vec2BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::normalize()
{
  Vec2BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v2buf::normalize(const v2buf& va)
{
  Vec2BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		     (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::lerp(const v2buf& va,const float step)
{
  Vec2BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::lerp(const v2buf& va,const v2buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec2BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v2buf::dot(float* fpArray,const int32_t iArrayLength,const v2buf& va)
{
  if ( NULL == fpArray ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= iArrayLength ? iCount : iArrayLength);

  Vec2BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		iCount);
}

void v2buf::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray ) return;

  Vec2BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#else

v2buf::v2buf(int iVecOffset) :
  m_VecArray(NULL),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(0) {}

v2buf::v2buf(int iVecOffset,float x,float y) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  assert(NULL != (m_VecArray=(void*)new char[sizeof(vec2)+iVecOffset]));

  m_ArrayCount  = 1;
  m_VecOffset   = iVecOffset;
  m_ElementSize = sizeof(vec2);

  ((vec2*)((char*)m_VecArray + iVecOffset))->x = x;
  ((vec2*)((char*)m_VecArray + iVecOffset))->y = y;
}

v2buf::v2buf(int iCount,int iSize,int iVecOffset,vec2* pVecArray) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  vec2* pv;

  assert(NULL != (m_VecArray=(void*)new char[iCount*iSize+iVecOffset]));

  m_ArrayCount  = iCount;
  m_ElementSize = iSize;
  m_VecOffset   = iVecOffset;

  pv = (vec2*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = *pVecArray++;
      pv  = (vec2*)(((char*)pv) + iSize);
    }
}

v2buf::v2buf(const v2buf& va) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  assert(NULL != (m_VecArray=(void*)new char[va.m_ArrayCount*va.m_ElementSize+va.m_VecOffset]));

  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec2* vap = (vec2*)((char*)va.m_VecArray + va.m_VecOffset);
  vec2* vp  = (vec2*)((char*)m_VecArray    + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec2*)((char*)vp  + m_ElementSize);
      vap = (vec2*)((char*)vap + m_ElementSize);
    }
}

v2buf::~v2buf()
{
  if ( NULL != m_VecArray ) delete m_VecArray;
  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v2buf::length()
{
  return m_ArrayCount;
}

int v2buf::size()
{
  return m_ElementSize;
}

int v2buf::offset()
{
  return m_VecOffset;
}

void* v2buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v2buf::add(v2& v)
{
  void* vp;
  vec2* pv;

  int   iCurSize = m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 )
    {
      memcpy(vp,(void*)m_VecArray,iCurSize);
    }

  pv = (vec2*)(((char*)vp) + (iCurSize + m_VecOffset));

  pv->x = v.vec->x;
  pv->y = v.vec->y;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec2*)vp;
  ++m_ArrayCount;
}

void v2buf::add(vec2& v)
{
  void* vp;
  vec2* pv;

  int iCurSize = m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 )
    {
      memcpy(vp,(void*)m_VecArray,iCurSize);
    }

  pv = (vec2*)(((char*)vp) + (iCurSize + m_VecOffset));

  pv->x = v.x;
  pv->y = v.y;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec2*)vp;
  ++m_ArrayCount;
}

void v2buf::operator += (const float s)
{
  void* pv    = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator -= (const float s)
{
  void* pv    = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator *= (const float s)
{
  void* pv    = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulBlockByFloatBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator /= (const float s)
{
  void* pv    = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v2buf::operator += (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddVec2ToBlockBySize((vec2*)pv,(const vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator -= (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubVec2FromBlkBySize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator *= (const v2& v)
{
  void* pv  = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulVec2ByBlockSize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator /= (const v2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivVec2ByBlockSize((vec2*)pv,(vec2*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v2buf::operator += (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufAddVec2ToBlockBySize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator -= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufSubVec2FromBlkBySize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator *= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufMulVec2ByBlockSize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator /= (const vec2& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec2BufDivVec2ByBlockSize((vec2*)pv,(vec2*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v2buf::operator += (struct v2buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = m_ArrayCount;
  int   iThatCount = va.m_ArrayCount;

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufAddBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator -= (struct v2buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = m_ArrayCount;
  int   iThatCount = va.m_ArrayCount;

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufSubBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator *= (struct v2buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = m_ArrayCount;
  int   iThatCount = va.m_ArrayCount;

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufMulBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator /= (struct v2buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int   iThisCount = m_ArrayCount;
  int   iThatCount = va.m_ArrayCount;

  int   iCount     = (iThisCount == iThatCount ? iThisCount :
		      iThisCount <  iThatCount ? iThisCount :
		      iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec2BufDivBufBySize((vec2*)pv,iThisSize,
			  (vec2*)pv,iThisSize,
			  (vec2*)pu,iThatSize,
			  iCount);
    }
}

void v2buf::operator *= (m2& m)
{
  vec2* pv = (vec2*)(((char*)m_VecArray) + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat2MultiplyVec(pv,m.m,pv);
      pv = (vec2*)(((char*)pv) + m_ElementSize);
    }
}

void v2buf::operator *= (mat2& m)
{
  vec2* pv = (vec2*)(((char*)m_VecArray) + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat2MultiplyVec(pv,&m,pv);
      pv = (vec2*)(((char*)pv) + m_ElementSize);
    }
}

vec2& v2buf::operator[](int iItem)
{
  vec2* pv;

  if ( iItem < m_ArrayCount )
    {
      ;
    }
  else if ( iItem == m_ArrayCount )
    {
      vec2 vTemp = {0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  pv = (vec2*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset);

  return *pv;
}

v2buf& v2buf::operator=(const v2buf& va)
{
  void* vdp;

  assert(NULL != (vdp=(void*)new char[va.m_ArrayCount*va.m_ElementSize+va.m_VecOffset]));

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray    = vdp;
  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec2* vap = (vec2*)((char*)va.m_VecArray + va.m_VecOffset);
  vec2* vp  = (vec2*)((char*)m_VecArray    + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec2*)((char*)vp  + m_ElementSize);
      vap = (vec2*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v2buf::sqr()
{
  Vec2BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v2buf::sqr(const v2buf& va)
{
  Vec2BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::sqrt()
{
  Vec2BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v2buf::sqrt(const v2buf& va)
{
  Vec2BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::normalize()
{
  Vec2BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v2buf::normalize(const v2buf& va)
{
  Vec2BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		     (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::lerp(const v2buf& va,const float step)
{
  Vec2BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v2buf::lerp(const v2buf& va,const v2buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec2BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v2buf::dot(float* fpArray,const int32_t iArrayLength,const v2buf& va)
{
  if ( NULL == fpArray ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
  iCount = (iCount <= iArrayLength ? iCount : iArrayLength);

  Vec2BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		iCount);
}

void v2buf::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray ) return;

  Vec2BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#endif

/* --------------- *
 * v3 array object *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 * v3 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v3array::v3array() :
  FlatBuffer(16,16,1,0),
  m_VecArray(NULL),
  m_ArrayCount(0) {}

v3array::v3array(float x,float y,float z) :
  FlatBuffer(16,16,1,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(1)
{
  assert(NULL != m_VecArray);

  vec3* pv = (vec3*)m_VecArray;

  pv->x = x;
  pv->y = y;
  pv->z = z;
}

v3array::v3array(int iCount) :
  FlatBuffer(16,16,iCount,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(iCount)
{
  vec3* vp           = (vec3*)m_VecArray;
  vec3  vTemp        = {0.0,0.0,0.0};

  for( int i=0 ; i < iCount ; ++i ) *vp++ = vTemp;
}

v3array::v3array(int iCount,vec3* pVecArray) :
  FlatBuffer(16,16,iCount,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(iCount)
{
  vec3* vp = (vec3*)m_VecArray;

  for( int i=0 ; i < iCount ; ++i ) *vp++ = *pVecArray++;
}

v3array::v3array(v3buf& pv) :
  FlatBuffer(16,16,pv.length(),0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(pv.length())
{
  vec3* vp           = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v3array::v3array(const v3array& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(va.m_ArrayCount)
{
  vec3* vp           = (vec3*)m_VecArray;
  vec3* vap          = (vec3*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

v3array::~v3array()
{
  m_VecArray = NULL;
}

int v3array::length()
{
  return (m_ArrayCount=getElementCount());
}

int v3array::size()
{
  return getElementSize();
}

void v3array::add(v3& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      assert(NULL != (m_VecArray=(void*)getAlignedPtr()));
      FlatBuffer::add(0,v.vec);
    }
}

void v3array::add(vec3& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      assert(NULL != (m_VecArray=(vec3*)getAlignedPtr()));
      FlatBuffer::add(0,&v);
    }
}

void v3array::operator += (const float s)
{
  if ( NULL != m_VecArray ) Vec3AddFloatToBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v3array::operator -= (const float s)
{
  if ( NULL != m_VecArray ) Vec3SubFloatFromBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v3array::operator *= (const float s)
{
  if ( NULL != m_VecArray ) Vec3MulFloatToBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v3array::operator /= (const float s)
{
  if ( NULL != m_VecArray ) Vec3DivBlockByFloatBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v3array::operator += (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3AddVecToBlockBySize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v3array::operator -= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3SubVecFromBlockBySize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v3array::operator *= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3MulBlockByVecUseSize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v3array::operator /= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3DivBlockByVecUseSize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v3array::operator += (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3AddVecToBlockBySize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v3array::operator -= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3SubVecFromBlockBySize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v3array::operator *= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3MulBlockByVecUseSize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v3array::operator /= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3DivBlockByVecUseSize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v3array::operator += (struct v3array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3AddBlockToBlockBySize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v3array::operator -= (struct v3array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3SubBlockFromBlockBySize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v3array::operator *= (struct v3array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3MulBlockByBlockUseSize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v3array::operator /= (struct v3array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3DivBlockByBlockUseSize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v3array::operator *= (m3& m)
{
  vec3* vp    = (vec3*)m_VecArray;
  int   iSize = getElementSize();

  if ( NULL != m_VecArray )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat3MultiplyVec(vp,m.m,vp);
	  vp = (vec3*)((char*)vp + iSize);
	}
    }
}

void v3array::operator *= (mat3& m)
{
  vec3* vp    = (vec3*)m_VecArray;
  int   iSize = getElementSize();

  if ( NULL != m_VecArray )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat3MultiplyVec(vp,&m,vp);
	  vp = (vec3*)((char*)vp + iSize);
	}
    }
}

vec3& v3array::operator[](int iItem)
{
  int iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec3 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  return *((vec3*)((char*)m_VecArray + (iItem*getElementSize())));
}

v3array& v3array::operator=(v3buf& v)
{
  m_VecArray   = resize(16,16,v.length(),0);
  m_ArrayCount = v.length();
  vec3* vp     = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = v[i];

  return *this;
}

v3array& v3array::operator=(const v3array& va)
{
  m_VecArray   = resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,0);
  m_ArrayCount = va.m_ArrayCount;

  vec3* vp  = (vec3*)m_VecArray;
  vec3* vap = (vec3*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;

  return *this;
}

void v3array::cross(const v3array& va)
{
  Vec3CrossBlock((vec3*)m_VecArray,
		 (vec3*)va.m_VecArray,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::sqr()
{
  Vec3SqrBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::sqr(v3array& va)
{
  Vec3BufSqrBuf(m_VecArray,
		sizeof(vec3),
		va.m_VecArray,
		sizeof(vec3),
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::sqrt()
{
  Vec3SqrtBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::sqrt(v3array& va)
{
  Vec3BufSqrtBuf(m_VecArray,
		 sizeof(vec3),
		 va.m_VecArray,
		 sizeof(vec3),
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::normalize()
{
  Vec3NormalizeBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::normalize(v3array& va)
{
  Vec3BufNormalizeBuf(m_VecArray,
		      sizeof(vec3),
		      va.m_VecArray,
		      sizeof(vec3),
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::lerp(const v3array& va,const float step)
{
  Vec3LerpBlock((vec3*)m_VecArray,
		(vec3*)va.m_VecArray,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::lerp(const v3array& va,const v3array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec3BufLerpBuf(m_VecArray,
		 sizeof(vec3),
		 va.m_VecArray,
		 sizeof(vec3),
		 vb.m_VecArray,
		 sizeof(vec3),
		 step,
		 iCount);
}

void v3array::dot(float* fpArray,const int32_t iArrayLength,const v3array& va)
{
  if ( NULL == fpArray ) return;

  Vec3DotBlock(fpArray,
	       (vec3*)m_VecArray,
	       (vec3*)va.m_VecArray,
	       (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

void v3array::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  Vec3LengthBlock(fpArray,
		  (vec3*)m_VecArray,
		  (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#else

v3array::v3array() :
  m_VecArray(NULL),
  m_ArrayCount(0) {}

v3array::v3array(float x,float y,float z)
{
  assert(NULL != (m_VecArray=(void*)new vec3()));

  vec3* pv = (vec3*)m_VecArray;

  pv->x = x;
  pv->y = y;
  pv->z = z;

  m_ArrayCount = 1;
}

v3array::v3array(int iCount)
{
  assert(NULL != (m_VecArray=(void*)new vec3[iCount]));

  m_ArrayCount = iCount;

  vec3  vTemp = {0.0,0.0,0.0};
  vec3* pv    = (vec3*)m_VecArray;
  
  for( int i=0 ; i < iCount ; ++i ) *pv++ = vTemp;
}

v3array::v3array(int iCount,vec3* pVecArray)
{
  assert(NULL != (m_VecArray=(void*)new vec3[iCount]));

  vec3* vp = (vec3*)pVecArray;
  vec3* pv = (vec3*)m_VecArray;

  m_ArrayCount = iCount;

  for( int i=0 ; i < iCount ; ++i ) *pv++ = *vp++;
}

v3array::v3array(v3buf& pv)
{
  assert(NULL != (m_VecArray=(void*)new vec3[pv.length()]));

  m_ArrayCount = pv.length();

  vec3* vp = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v3array::v3array(const v3array& va)
{
  assert(NULL != (m_VecArray=(void*)new vec3[va.m_ArrayCount]));

  m_ArrayCount = va.m_ArrayCount;

  vec3* vap = (vec3*)va.m_VecArray;
  vec3* vp  = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

v3array::~v3array()
{
  if ( NULL != m_VecArray ) delete (vec3*)m_VecArray;
  m_VecArray  = NULL;
  m_ArrayCount = 0;
}

int v3array::length()
{
  return m_ArrayCount;
}

int v3array::size()
{
  return sizeof(vec3);
}

void v3array::add(v3& v)
{
  vec3* vec;

  assert(NULL != (vec=new vec3[1+m_ArrayCount]));

  vec3* pv = (vec3*)m_VecArray;
  vec3* vp = vec;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *pv++;

  *vp = *(v.vec);

  if ( NULL != m_VecArray ) delete (vec3*)m_VecArray;

  m_VecArray = vec;

  ++m_ArrayCount;
}

void v3array::add(vec3& v)
{
  vec3* vec;

  assert(NULL != (vec=new vec3[1+m_ArrayCount]));

  vec3* pv = (vec3*)m_VecArray;
  vec3* vp = vec;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *pv++;

  *vp = v;

  if ( NULL != m_VecArray ) delete (vec3*)m_VecArray;

  m_VecArray = vec;
  ++m_ArrayCount;
}

void v3array::operator += (const float s)
{
  if ( NULL != m_VecArray ) Vec3AddFloatToBlock((vec3*)m_VecArray,s,m_ArrayCount);
}

void v3array::operator -= (const float s)
{
  if ( NULL != m_VecArray ) Vec3SubtractFloatFromBlock((vec3*)m_VecArray,s,m_ArrayCount);
}

void v3array::operator *= (const float s)
{
  if ( NULL != m_VecArray ) Vec3MultiplyFloatToBlock((vec3*)m_VecArray,s,m_ArrayCount);
}

void v3array::operator /= (const float s)
{
  if ( NULL != m_VecArray ) Vec3DivideBlockByFloat((vec3*)m_VecArray,s,m_ArrayCount);
}

void v3array::operator += (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3AddVecToBlock((vec3*)m_VecArray,v.vec,m_ArrayCount);
}

void v3array::operator -= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3SubVecFromBlock((vec3*)m_VecArray,v.vec,m_ArrayCount);
}

void v3array::operator *= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3MulBlockByVec((vec3*)m_VecArray,v.vec,m_ArrayCount);
}

void v3array::operator /= (const v3& v)
{
  if ( NULL != m_VecArray ) Vec3DivBlockByVec((vec3*)m_VecArray,v.vec,m_ArrayCount);
}

void v3array::operator += (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3AddVecToBlock((vec3*)m_VecArray,&v,m_ArrayCount);
}

void v3array::operator -= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3SubVecFromBlock((vec3*)m_VecArray,&v,m_ArrayCount);
}

void v3array::operator *= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3MulBlockByVec((vec3*)m_VecArray,&v,m_ArrayCount);
}

void v3array::operator /= (const vec3& v)
{
  if ( NULL != m_VecArray ) Vec3DivBlockByVec((vec3*)m_VecArray,&v,m_ArrayCount);
}

void v3array::operator += (struct v3array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3AddBlockToBlock((vec3*)m_VecArray,(vec3*)va.m_VecArray,iElementCount);
}

void v3array::operator -= (struct v3array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3SubBlockFromBlock((vec3*)m_VecArray,(vec3*)va.m_VecArray,iElementCount);
}

void v3array::operator *= (struct v3array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3MulBlockByBlock((vec3*)m_VecArray,(vec3*)va.m_VecArray,iElementCount);
}

void v3array::operator /= (struct v3array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec3DivBlockByBlock((vec3*)m_VecArray,(vec3*)va.m_VecArray,iElementCount);
}

void v3array::operator *= (m3& m)
{
  vec3* pv = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat3MultiplyVec(pv,m.m,pv);
      ++pv;
    }
}

void v3array::operator *= (mat3& m)
{
  vec3* pv = (vec3*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat3MultiplyVec(pv,&m,pv);
      ++pv;
    }
}

vec3& v3array::operator[](int iItem)
{
  if ( iItem < m_ArrayCount )
    {
      ;
    }
  else if ( iItem == m_ArrayCount )
    {
      vec3 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  return *(((vec3*)m_VecArray) + iItem);
}

v3array& v3array::operator=(v3buf& v)
{
  vec3* vec;

  assert(NULL != (vec=new vec3[v.length()]));

  if ( NULL != m_VecArray ) delete (vec3*)m_VecArray;

  m_VecArray   = (void*)vec;
  m_ArrayCount = v.length();

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vec++ = v[i];

  return *this;
}

v3array& v3array::operator=(const v3array& va)
{
  vec3* vp;
  vec3* vap;

  assert( NULL != (vp=new vec3[va.m_ArrayCount]));

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_ArrayCount = va.m_ArrayCount;
  m_VecArray   = (void*)vp;

  vap          = (vec3*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;

  return *this;
}

void v3array::cross(const v3array& va)
{
  Vec3CrossBlock((vec3*)m_VecArray,
		 (vec3*)va.m_VecArray,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::sqr()
{
  Vec3SqrBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::sqr(v3array& va)
{
  Vec3BufSqrBuf(m_VecArray,
		sizeof(vec3),
		va.m_VecArray,
		sizeof(vec3),
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::sqrt()
{
  Vec3SqrtBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::sqrt(v3array& va)
{
  Vec3BufSqrtBuf(m_VecArray,
		 sizeof(vec3),
		 va.m_VecArray,
		 sizeof(vec3),
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::normalize()
{
  Vec3NormalizeBlock((vec3*)m_VecArray,m_ArrayCount);
}

void v3array::normalize(v3array& va)
{
  Vec3BufNormalizeBuf(m_VecArray,
		      sizeof(vec3),
		      va.m_VecArray,
		      sizeof(vec3),
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::lerp(const v3array& va,const float step)
{
  Vec3LerpBlock((vec3*)m_VecArray,
		(vec3*)va.m_VecArray,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3array::lerp(const v3array& va,const v3array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec3BufLerpBuf(m_VecArray,
		 sizeof(vec3),
		 va.m_VecArray,
		 sizeof(vec3),
		 vb.m_VecArray,
		 sizeof(vec3),
		 step,
		 iCount);
}

void v3array::dot(float* fpArray,const int32_t iArrayLength,const v3array& va)
{
  if ( NULL == fpArray ) return;

  Vec3DotBlock(fpArray,
	       (vec3*)m_VecArray,
	       (vec3*)va.m_VecArray,
	       (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

void v3array::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  Vec3LengthBlock(fpArray,
		  (vec3*)m_VecArray,
		  (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#endif

/* --------------- *
 * v3buf object    *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 * v3 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v3buf::v3buf(int iVecOffset) :
  FlatBuffer(16,16,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(getElementSize()) {}

v3buf::v3buf(int iVecOffset,float x,float y,float z) :
  FlatBuffer(16,16,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(1),
  m_ElementSize(getElementSize())
{
  vec3* vp = (vec3*)((char*)m_VecArray + iVecOffset);
  vp->x = x;
  vp->y = y;
  vp->z = z;
}

v3buf::v3buf(int iCount,int iSize,int iVecOffset,vec3* pVecArray) :
  FlatBuffer(iSize,16,iCount,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(iCount),
  m_ElementSize(getElementSize())
{
  vec3* pv;

  assert(NULL != m_VecArray);

  pv = (vec3*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = pVecArray[i];
      pv = (vec3*)(((char*)pv) + m_ElementSize);
    }
}

v3buf::v3buf(const v3buf& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(va.m_VecOffset),
  m_ArrayCount(va.m_ArrayCount),
  m_ElementSize(getElementSize())
{
  vec3* vp;
  vec3* vap;

  assert(NULL != m_VecArray);

  vp  = (vec3*)((char*)m_VecArray    + m_VecOffset);
  vap = (vec3*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec3*)((char*)vp  + m_ElementSize);
      vap = (vec3*)((char*)vap + m_ElementSize);
    }
}

v3buf::~v3buf()
{
  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v3buf::length()
{
  return m_ArrayCount;
}

int v3buf::size()
{
  return m_ElementSize;
}

int v3buf::offset()
{
  return m_VecOffset;
}

void* v3buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v3buf::add(v3& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,v.vec);
    }
}

void v3buf::add(vec3& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,&v);
    }
}

void v3buf::operator += (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator -= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator *= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator /= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator += (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddVecToBlock(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator -= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubVecFromBlock(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator *= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulBufByVec(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator /= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByVec(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator += (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddVecToBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator -= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubVecFromBlock(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator *= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulBufByVec(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator /= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByVec(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator += (struct v3buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufAddBufToBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v3buf::operator -= (struct v3buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufSubBufFromBuf(pv,iThisSize,
			   pv,iThisSize,
			   pu,iThatSize,
			   iCount);
    }
}

void v3buf::operator *= (struct v3buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufMulBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v3buf::operator /= (struct v3buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufDivBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v3buf::operator *= (m3& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat3MultiplyVec((vec3*)pv,m.m,(vec3*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

void v3buf::operator *= (mat3& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat3MultiplyVec((vec3*)pv,&m,(vec3*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

vec3& v3buf::operator[](int iItem)
{
  int iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec3 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItemCount;

  return *((vec3*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset));
}

v3buf& v3buf::operator=(const v3buf& va)
{
  m_VecArray    = resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_VecOffset);
  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec3* vp  = (vec3*)((char*)m_VecArray    + m_VecOffset);
  vec3* vap = (vec3*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec3*)((char*)vp  + m_ElementSize);
      vap = (vec3*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v3buf::cross(const v3buf& va)
{
  Vec3BufCrossBuf((void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)va.m_VecArray + va.m_VecOffset),
		  va.m_ElementSize,
		  (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::sqr()
{
  Vec3BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v3buf::sqr(v3buf& va)
{
  Vec3BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::sqrt()
{
  Vec3BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v3buf::sqrt(v3buf& va)
{
  Vec3BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::normalize()
{
  Vec3BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v3buf::normalize(v3buf& va)
{
  Vec3BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::lerp(const v3buf& va,const float step)
{
  Vec3BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::lerp(const v3buf& va,const v3buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec3BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v3buf::dot(float* fpArray,const int32_t iArrayLength,const v3buf& va)
{
  if ( NULL == fpArray ) return;

  Vec3BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  Vec3BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#else

v3buf::v3buf(int iVecOffset) :
  m_VecArray(NULL),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(16)
{
  assert(NULL != (m_VecArray=(void*)new char[16+iVecOffset]));
}

v3buf::v3buf(int iVecOffset,float x,float y,float z) :
  m_VecArray(NULL),
  m_VecOffset(iVecOffset),
  m_ArrayCount(1),
  m_ElementSize(16)
{
  assert(NULL != (m_VecArray=(void*)new char[16+iVecOffset]));

  vec3* vp = (vec3*)((char*)m_VecArray + m_VecOffset);
  vp->x = x;
  vp->y = y;
  vp->z = z;
}

v3buf::v3buf(int iCount,int iSize,int iVecOffset,vec3* pVecArray) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  vec3* pv;

  assert(NULL != (m_VecArray=new char[iSize*iCount]));

  m_ArrayCount  = iCount;
  m_ElementSize = iSize;
  m_VecOffset   = iVecOffset;

  pv = (vec3*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = pVecArray[i];
      pv = (vec3*)(((char*)pv) + iSize);
    }
}

v3buf::v3buf(const v3buf& va) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  assert(NULL != (m_VecArray=new char[va.m_ArrayCount*va.m_ElementSize+va.m_VecOffset]));

  m_ElementSize = va.m_ElementSize;
  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;

  vec3* vp  = (vec3*)((char*)m_VecArray    + m_VecOffset);
  vec3* vap = (vec3*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec3*)((char*)vp  + m_ElementSize);
      vap = (vec3*)((char*)vap + m_ElementSize);
    }
}

v3buf::~v3buf()
{
  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v3buf::length()
{
  return m_ArrayCount;
}

int v3buf::size()
{
  return m_ElementSize;
}

int v3buf::offset()
{
  return m_VecOffset;
}

void* v3buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v3buf::add(v3& v)
{
  void* vp;
  vec3* pv;

  int iCurSize= m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 ) memcpy(vp,(void*)m_VecArray,iCurSize);

  pv = (vec3*)(((char*)vp) + (iCurSize + m_VecOffset));

  *pv = *v.vec;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec3*)vp;
  ++m_ArrayCount;
}

void v3buf::add(vec3& v)
{
  void* vp;
  vec3* pv;

  int iCurSize = m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 ) memcpy(vp,(void*)m_VecArray,iCurSize);

  pv = (vec3*)(((char*)vp) + (iCurSize + m_VecOffset));

  *pv = v;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec3*)vp;
  ++m_ArrayCount;
}

void v3buf::operator += (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator -= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator *= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator /= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v3buf::operator += (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddVecToBlock((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator -= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubVecFromBlock((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator *= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulBufByVec((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator /= (const v3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByVec((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v3buf::operator += (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufAddVecToBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator -= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufSubVecFromBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator *= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufMulBufByVec((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator /= (const vec3& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec3BufDivBufByVec((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v3buf::operator += (struct v3buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufAddBufToBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v3buf::operator -= (struct v3buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufSubBufFromBuf(pv,iThisSize,
			   pv,iThisSize,
			   pu,iThatSize,
			   iCount);
    }
}

void v3buf::operator *= (struct v3buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufMulBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}
  
void v3buf::operator /= (struct v3buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec3BufDivBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v3buf::operator *= (m3& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < m_ArrayCount ; ++i )
	{
	  Mat3MultiplyVec((vec3*)pv,m.m,(vec3*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

void v3buf::operator *= (mat3& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < m_ArrayCount ; ++i )
	{
	  Mat3MultiplyVec((vec3*)pv,&m,(vec3*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

vec3& v3buf::operator[](int iItem)
{
  int iItemCount = m_ArrayCount;

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec3 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItemCount;

  return *((vec3*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset));
}

v3buf& v3buf::operator=(const v3buf& va)
{
  void* vec;

  assert(NULL != (vec=new char[va.m_ArrayCount*va.m_ElementSize+va.m_VecOffset]));

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_ArrayCount  = va.m_ArrayCount;
  m_ElementSize = va.m_ElementSize;
  m_VecOffset   = va.m_VecOffset;
  m_VecArray    = vec;

  vec3* vp  = (vec3*)((char*)vec           + m_VecOffset);
  vec3* vap = (vec3*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec3*)((char*)vp  + m_ElementSize);
      vap = (vec3*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v3buf::cross(const v3buf& va)
{
  Vec3BufCrossBuf((void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)va.m_VecArray + va.m_VecOffset),
		  va.m_ElementSize,
		  (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::sqr()
{
  Vec3BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v3buf::sqr(v3buf& va)
{
  Vec3BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::sqrt()
{
  Vec3BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v3buf::sqrt(v3buf& va)
{
  Vec3BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::normalize()
{
  Vec3BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v3buf::normalize(v3buf& va)
{
  Vec3BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::lerp(const v3buf& va,const float step)
{
  Vec3BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::lerp(const v3buf& va,const v3buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec3BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v3buf::dot(float* fpArray,const int32_t iArrayLength,const v3buf& va)
{
  if ( NULL == fpArray ) return;

  Vec3BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v3buf::length(float* fpArray,const int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  Vec3BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength));
}

#endif

/* --------------- *
 * v4 array object *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 * v4 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v4array::v4array() :
  FlatBuffer(16,16,1,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(0) {}

v4array::v4array(float x,float y,float z,float w) :
  FlatBuffer(16,16,1,0),
  m_VecArray((void*)getAlignedPtr())
{
  vec4* pv = (vec4*)m_VecArray;

  pv->x = x;
  pv->y = y;
  pv->z = z;
  pv->w = w;

  m_ArrayCount = 1;
}

v4array::v4array(int iCount) :
  FlatBuffer(16,16,iCount,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(0)
{
  vec4* vp           = (vec4*)m_VecArray;
  vec4  vTemp        = {0.0,0.0,0.0};

  for( int i=0 ; i < iCount ; ++i ) *vp++ = vTemp;
}

v4array::v4array(int iCount,vec4* pVecArray) :
  FlatBuffer(16,16,iCount,0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(iCount)
{
  vec4* vp = (vec4*)m_VecArray;

  for( int i=0 ; i < iCount ; ++i ) *vp++ = *pVecArray++;
}

v4array::v4array(v4buf& pv) :
  FlatBuffer(16,16,pv.length(),0),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(pv.length())
{
  vec4* vp     = (vec4*)m_VecArray;
  m_ArrayCount = pv.length();

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v4array::v4array(const v4array& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_VecArray((void*)getAlignedPtr()),
  m_ArrayCount(va.m_ArrayCount)
{
  vec4* vp  = (vec4*)m_VecArray;
  vec4* vap = (vec4*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

v4array::~v4array()
{
  m_VecArray = NULL;
}

int v4array::length()
{
  return (m_ArrayCount=getElementCount());
}

int v4array::size()
{
  return getElementSize();
}

void v4array::add(v4& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      assert(NULL != (m_VecArray=(void*)getAlignedPtr()));
      FlatBuffer::add(0,v.vec);
    }
}

void v4array::add(vec4& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      assert(NULL != (m_VecArray=(vec4*)getAlignedPtr()));
      FlatBuffer::add(0,&v);
    }
}

void v4array::operator += (const float s)
{
  if ( NULL != m_VecArray ) Vec4AddFloatToBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v4array::operator -= (const float s)
{
  if ( NULL != m_VecArray ) Vec4SubFloatFromBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v4array::operator *= (const float s)
{
  if ( NULL != m_VecArray ) Vec4MulFloatToBlockBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v4array::operator /= (const float s)
{
  if ( NULL != m_VecArray ) Vec4DivBlockByFloatBySize(m_VecArray,s,getElementSize(),getElementCount());
}

void v4array::operator += (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4AddVecToBlockBySize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v4array::operator -= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4SubVecFromBlockBySize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v4array::operator *= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4MulBlockByVecUseSize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v4array::operator /= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4DivBlockByVecUseSize(m_VecArray,v.vec,getElementSize(),getElementCount());
}

void v4array::operator += (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4AddVecToBlockBySize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v4array::operator -= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4SubVecFromBlockBySize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v4array::operator *= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4MulBlockByVecUseSize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v4array::operator /= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4DivBlockByVecUseSize(m_VecArray,&v,getElementSize(),getElementCount());
}

void v4array::operator += (struct v4array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec4AddBlockToBlockBySize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v4array::operator -= (struct v4array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec4SubBlockFromBlockBySize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v4array::operator *= (struct v4array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec4MulBlockByBlockUseSize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v4array::operator /= (struct v4array& va)
{
  int lElementCount = getElementCount();
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray ) Vec4DivBlockByBlockUseSize(m_VecArray,va.m_VecArray,getElementSize(),iElementCount);
}

void v4array::operator *= (m4& m)
{
  vec4* vp    = (vec4*)m_VecArray;
  int   iSize = getElementSize();

  if ( NULL != m_VecArray )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat4MultiplyVec(vp,m.m,vp);
	  vp = (vec4*)((char*)vp + iSize);
	}
    }
}

void v4array::operator *= (mat4& m)
{
  vec4* vp    = (vec4*)m_VecArray;
  int   iSize = getElementSize();

  if ( NULL != m_VecArray )
    {
      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat4MultiplyVec(vp,&m,vp);
	  vp = (vec4*)((char*)vp + iSize);
	}
    }
}

vec4& v4array::operator[](int iItem)
{
  int iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec4 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  return *((vec4*)((char*)m_VecArray + (iItem*getElementSize())));
}

v4array& v4array::operator=(v4buf& v)
{
  m_VecArray   = resize(16,16,v.length(),0);
  m_ArrayCount = v.length();
  vec4* vp     = (vec4*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = v[i];

  return *this;
}

v4array& v4array::operator=(const v4array& va)
{
  m_VecArray   = resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,0);
  m_ArrayCount = va.m_ArrayCount;

  vec4* vp  = (vec4*)m_VecArray;
  vec4* vap = (vec4*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;

  return *this;
}

void v4array::cross(const v4array& va)
{
  Vec4CrossBlock((vec4*)m_VecArray,
		 (vec4*)va.m_VecArray,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::sqr()
{
  Vec4SqrBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::sqr(v4array& va)
{
  Vec4BufSqrBuf(m_VecArray,
		m_ElementSize,
		va.m_VecArray,
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::sqrt()
{
  Vec4SqrtBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::sqrt(v4array& va)
{
  Vec4BufSqrtBuf(m_VecArray,
		 m_ElementSize,
		 va.m_VecArray,
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::normalize()
{
  Vec4NormalizeBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::normalize(v4array& va)
{
  Vec4BufNormalizeBuf(m_VecArray,
		      m_ElementSize,
		      va.m_VecArray,
		      va.m_ElementSize,
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::lerp(const v4array& va,const float step)
{
  Vec4LerpBlock((vec4*)m_VecArray,
		(vec4*)va.m_VecArray,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::lerp(const v4array& va,const v4array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec4BufLerpBuf(m_VecArray,
		 m_ElementSize,
		 va.m_VecArray,
		 va.m_ElementSize,
		 vb.m_VecArray,
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v4array::dot(float* fpArray,const int32_t iArrayLength,const v4array& va)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iArrayLength <= iCount          ? iArrayLength : iCount);

  Vec4DotBlock(fpArray,(vec4*)m_VecArray,(vec4*)va.m_VecArray,iCount);
}

void v4array::length(float* fpArray,int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength);

  Vec4LengthBlock(fpArray,(vec4*)m_VecArray,iCount);
}

#else

v4array::v4array() :
  m_VecArray(NULL),
  m_ArrayCount(0) {}

v4array::v4array(float x,float y,float z,float w)
{
  assert(NULL != (m_VecArray=(void*)new vec4()));

  vec4* pv = (vec4*)m_VecArray;

  pv->x = x;
  pv->y = y;
  pv->z = z;
  pv->w = w;

  m_ArrayCount = 1;
}

v4array::v4array(int iCount)
{
  assert(NULL != (m_VecArray=(void*)new vec4[iCount]));

  m_ArrayCount = iCount;

  vec4  vTemp = {0.0,0.0,0.0};
  vec4* pv    = (vec4*)m_VecArray;
  
  for( int i=0 ; i < iCount ; ++i ) *pv++ = vTemp;
}

v4array::v4array(int iCount,vec4* pVecArray)
{
  assert(NULL != (m_VecArray=(void*)new vec4[iCount]));

  vec4* vp = (vec4*)pVecArray;
  vec4* pv = (vec4*)m_VecArray;

  m_ArrayCount = iCount;

  for( int i=0 ; i < iCount ; ++i ) *pv++ = *vp++;
}

v4array::v4array(v4buf& pv)
{
  assert(NULL != (m_VecArray=(void*)new vec4[pv.length()]));

  m_ArrayCount = pv.length();

  vec4* vp = (vec4*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = pv[i];
}

v4array::v4array(const v4array& va)
{
  assert(NULL != (m_VecArray=(void*)new vec4[va.m_ArrayCount]));

  m_ArrayCount = va.m_ArrayCount;

  vec4* vp  = (vec4*)m_VecArray;
  vec4* vap = (vec4*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *vap++;
}

v4array::~v4array()
{
  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;
  m_VecArray  = NULL;
  m_ArrayCount = 0;
}

int v4array::length()
{
  return m_ArrayCount;
}

int v4array::size()
{
  return sizeof(vec4);
}

void v4array::add(v4& v)
{
  vec4* vec;

  assert(NULL != (vec=new vec4[1+m_ArrayCount]));

  vec4* pv = (vec4*)m_VecArray;
  vec4* vp = vec;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *pv++;

  *vp = *(v.vec);

  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;

  m_VecArray = vec;

  ++m_ArrayCount;
}

void v4array::add(vec4& v)
{
  vec4* vec;

  assert(NULL != (vec=new vec4[1+m_ArrayCount]));

  vec4* pv = (vec4*)m_VecArray;
  vec4* vp = vec;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vp++ = *pv++;

  *vp = v;

  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;

  m_VecArray = vec;
  ++m_ArrayCount;
}

void v4array::operator += (const float s)
{
  if ( NULL != m_VecArray ) Vec4AddFloatToBlock((vec4*)m_VecArray,s,m_ArrayCount);
}

void v4array::operator -= (const float s)
{
  if ( NULL != m_VecArray ) Vec4SubtractFloatFromBlock((vec4*)m_VecArray,s,m_ArrayCount);
}

void v4array::operator *= (const float s)
{
  if ( NULL != m_VecArray ) Vec4MultiplyFloatToBlock((vec4*)m_VecArray,s,m_ArrayCount);
}

void v4array::operator /= (const float s)
{
  if ( NULL != m_VecArray ) Vec4DivideBlockByFloat((vec4*)m_VecArray,s,m_ArrayCount);
}

void v4array::operator += (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4AddVecToBlock((vec4*)m_VecArray,v.vec,m_ArrayCount);
}

void v4array::operator -= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4SubVecFromBlock((vec4*)m_VecArray,v.vec,m_ArrayCount);
}

void v4array::operator *= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4MulBlockByVec((vec4*)m_VecArray,v.vec,m_ArrayCount);
}

void v4array::operator /= (const v4& v)
{
  if ( NULL != m_VecArray ) Vec4DivBlockByVec((vec4*)m_VecArray,v.vec,m_ArrayCount);
}

void v4array::operator += (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4AddVecToBlock((vec4*)m_VecArray,&v,m_ArrayCount);
}

void v4array::operator -= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4SubVecFromBlock((vec4*)m_VecArray,&v,m_ArrayCount);
}

void v4array::operator *= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4MulBlockByVec((vec4*)m_VecArray,&v,m_ArrayCount);
}

void v4array::operator /= (const vec4& v)
{
  if ( NULL != m_VecArray ) Vec4DivBlockByVec((vec4*)m_VecArray,&v,m_ArrayCount);
}

void v4array::operator += (struct v4array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray )
    {
      Vec4AddBlockToBlock((vec4*)m_VecArray,(vec4*)va.m_VecArray,iElementCount);
    }
}

void v4array::operator -= (struct v4array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray )
    {
      Vec4SubBlockFromBlock((vec4*)m_VecArray,(vec4*)va.m_VecArray,iElementCount);
    }
}

void v4array::operator *= (struct v4array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray )
    {
      Vec4MulBlockByBlock((vec4*)m_VecArray,(vec4*)va.m_VecArray,iElementCount);
    }
}

void v4array::operator /= (struct v4array& va)
{
  int lElementCount = m_ArrayCount;
  int vElementCount = va.length();
  int iElementCount = (lElementCount == vElementCount ? lElementCount :
		       lElementCount <  vElementCount ? lElementCount :
		       vElementCount);

  if ( NULL != m_VecArray )
    {
      Vec4DivBlockByBlock((vec4*)m_VecArray,(vec4*)va.m_VecArray,iElementCount);
    }
}

void v4array::operator *= (m4& m)
{
  vec4* pv = (vec4*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat4MultiplyVec(pv,m.m,pv);
      ++pv;
    }
}

void v4array::operator *= (mat4& m)
{
  vec4* pv = (vec4*)m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      Mat4MultiplyVec(pv,&m,pv);
      ++pv;
    }
}

vec4& v4array::operator[](int iItem)
{
  if ( iItem < m_ArrayCount )
    {
      ;
    }
  else if ( iItem == m_ArrayCount )
    {
      vec4 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  return *(((vec4*)m_VecArray) + iItem);
}

v4array& v4array::operator=(v4buf& v)
{
  vec4* vec;

  assert(NULL != (vec=new vec4[v.length()]));

  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;

  m_VecArray   = (void*)vec;
  m_ArrayCount = v.length();

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vec++ = v[i];

  return *this;
}

v4array& v4array::operator=(const v4array& va)
{
  vec4* vec;

  assert(NULL != (vec=new vec4[va.m_ArrayCount]));

  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;

  m_VecArray   = (void*)vec;
  m_ArrayCount = va.m_ArrayCount;

  vec4* vap = (vec4*)va.m_VecArray;

  for( int i=0 ; i < m_ArrayCount ; ++i ) *vec++ = *vap++;

  return *this;
}

void v4array::cross(const v4array& va)
{
  Vec4CrossBlock((vec4*)m_VecArray,
		 (vec4*)m_VecArray,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::sqr()
{
  Vec4SqrBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::sqr(v4array& va)
{
  Vec4BufSqrBuf(m_VecArray,
		sizeof(vec4),
		va.m_VecArray,
		sizeof(vec4),
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::sqrt()
{
  Vec4SqrtBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::sqrt(v4array& va)
{
  Vec4BufSqrtBuf(m_VecArray,
		 sizeof(vec4),
		 va.m_VecArray,
		 sizeof(vec4),
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::normalize()
{
  Vec4NormalizeBlock((vec4*)m_VecArray,m_ArrayCount);
}

void v4array::normalize(v4array& va)
{
  Vec4BufNormalizeBuf(m_VecArray,
		      sizeof(vec4),
		      va.m_VecArray,
		      sizeof(vec4),
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::lerp(const v4array& va,const float step)
{
  Vec4LerpBlock((vec4*)m_VecArray,
		(vec4*)va.m_VecArray,
		step,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4array::lerp(const v4array& va,const v4array& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec4BufLerpBuf(m_VecArray,
		 sizeof(vec4),
		 va.m_VecArray,
		 sizeof(vec4),
		 vb.m_VecArray,
		 sizeof(vec4),
		 step,
		 iCount);
}

void v4array::dot(float* fpArray,const int32_t iArrayLength,const v4array& va)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iArrayLength <= iCount          ? iArrayLength : iCount);

  Vec4DotBlock(fpArray,(vec4*)m_VecArray,(vec4*)va.m_VecArray,iCount);
}

void v4array::length(float* fpArray,int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength);

  Vec4LengthBlock(fpArray,(vec4*)m_VecArray,iCount);
}

#endif

/* --------------- *
 * v4buf object    *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 * v4 is an object designed to hide the complexities of aligned versus     *
 * unaligned management of 3-dimensional vector objects.                   *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)

v4buf::v4buf(int iSize,int iVecOffset) :
  FlatBuffer(iSize,16,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(getElementSize()) {}

v4buf::v4buf(int iSize,int iVecOffset,float x,float y,float z,float w) :
  FlatBuffer(iSize,16,1,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ElementSize(getElementSize())
{
  vec4* pv;

  assert(NULL != m_VecArray);

  pv = (vec4*)(((char*)m_VecArray) + iVecOffset);
  pv->x = x;
  pv->y = y;
  pv->z = z;
  pv->w = w;
}

v4buf::v4buf(int iCount,int iSize,int iVecOffset,vec4* pVecArray) :
  FlatBuffer(iSize,16,iCount,iVecOffset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(iVecOffset),
  m_ArrayCount(iCount),
  m_ElementSize(getElementSize())
{
  vec4* pv = (vec4*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = pVecArray[i];
      pv = (vec4*)(((char*)pv) + m_ElementSize);
    }
}

v4buf::v4buf(const v4buf& va) :
  FlatBuffer(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_Offset),
  m_VecArray((void*)getAlignedPtr()),
  m_VecOffset(va.m_VecOffset),
  m_ArrayCount(va.m_ArrayCount),
  m_ElementSize(getElementSize())
{
  vec4* vp  = (vec4*)((char*)m_VecArray    + m_VecOffset);
  vec4* vap = (vec4*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec4*)((char*)vp  + m_ElementSize);
      vap = (vec4*)((char*)vap + m_ElementSize);
    }
}

v4buf::~v4buf()
{
  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v4buf::length()
{
  return m_ArrayCount;
}

int v4buf::size()
{
  return m_ElementSize;
}

int v4buf::offset()
{
  return m_VecOffset;
}

void* v4buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v4buf::add(v4& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),v.vec);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,v.vec);
    }
}

void v4buf::add(vec4& v)
{
  if ( NULL != m_VecArray )
    {
      FlatBuffer::add(getElementCount(),&v);
    }
  else
    {
      m_VecArray = (void*)getAlignedPtr();
      FlatBuffer::add(0,&v);
    }
}

void v4buf::operator += (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator -= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator *= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator /= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator += (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddVecToBlock(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator -= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubVecFromBlock(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator *= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulBufByVec(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator /= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByVec(pv,pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator += (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddVecToBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator -= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubVecFromBlock(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator *= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulBufByVec(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator /= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByVec(pv,pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator += (struct v4buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufAddBufToBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v4buf::operator -= (struct v4buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufSubBufFromBuf(pv,iThisSize,
			   pv,iThisSize,
			   pu,iThatSize,
			   iCount);
    }
}

void v4buf::operator *= (struct v4buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufMulBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v4buf::operator /= (struct v4buf& va)
{
  int   iThisSize = getElementSize();
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.getElementSize();
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = getElementCount();
  int iThatCount = va.getElementCount();

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufDivBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v4buf::operator *= (m4& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat4MultiplyVec((vec4*)pv,m.m,(vec4*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

void v4buf::operator *= (mat4& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < getElementCount() ; ++i )
	{
	  Mat4MultiplyVec((vec4*)pv,&m,(vec4*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

vec4& v4buf::operator[](int iItem)
{
  int iItemCount = getElementCount();

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec4 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItemCount;

  return *((vec4*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset));
}

v4buf& v4buf::operator=(const v4buf& va)
{
  m_VecArray    = resize(va.m_BaseSize,va.m_Alignment,va.m_ArrayCount,va.m_VecOffset);
  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec4* vp  = (vec4*)((char*)m_VecArray    + m_VecOffset);
  vec4* vap = (vec4*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec4*)((char*)vp  + m_ElementSize);
      vap = (vec4*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v4buf::cross(const v4buf& va)
{
  Vec4BufCrossBuf((void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)va.m_VecArray + va.m_VecOffset),
		  va.m_ElementSize,
		  (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::sqr()
{
  Vec4BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v4buf::sqr(v4buf& va)
{
  Vec4BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::sqrt()
{
  Vec4BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v4buf::sqrt(v4buf& va)
{
  Vec4BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::normalize()
{
  Vec4BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v4buf::normalize(v4buf& va)
{
  Vec4BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::lerp(const v4buf& va,const float step)
{
  Vec4BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::lerp(const v4buf& va,const v4buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec4BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v4buf::dot(float* fpArray,const int32_t iArrayLength,const v4buf& va)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iArrayLength <= iCount          ? iArrayLength : iCount);

  Vec4BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		iCount);
}

void v4buf::length(float* fpArray,int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength);

  Vec4BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   iCount);
}

#else

v4buf::v4buf(int iSize,int iVecOffset) :
  m_VecArray(NULL),
  m_VecOffset(iVecOffset),
  m_ArrayCount(0),
  m_ElementSize(iSize) {}

v4buf::v4buf(int iSize,int iVecOffset,float x,float y,float z,float w) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  vec4* pv;

  assert(NULL != (m_VecArray=(void*)new char[iSize]));

  m_ArrayCount  = 1;
  m_ElementSize = iSize;
  m_VecOffset   = iVecOffset;

  pv = (vec4*)(((char*)m_VecArray) + m_VecOffset);

  pv->x = x;
  pv->y = y;
  pv->z = z;
  pv->w = w;
}

v4buf::v4buf(int iCount,int iSize,int iVecOffset,vec4* pVecArray) :
  m_VecArray(NULL),
  m_VecOffset(0),
  m_ArrayCount(0),
  m_ElementSize(0)
{
  vec4* pv;

  assert(NULL != (m_VecArray=new char[iSize*iCount]));

  m_ArrayCount  = iCount;
  m_ElementSize = iSize;
  m_VecOffset   = iVecOffset;

  pv = (vec4*)(((char*)m_VecArray) + iVecOffset);

  for( int i=0 ; i < iCount ; ++i )
    {
      *pv = pVecArray[i];
      pv = (vec4*)(((char*)pv) + iSize);
    }
}

v4buf::v4buf(const v4buf& va)
{
  assert(NULL != (m_VecArray=(void*)new char[va.m_ElementSize*va.m_ArrayCount]));

  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec4* vp  = (vec4*)((char*)m_VecArray    + m_VecOffset);
  vec4* vap = (vec4*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec4*)((char*)vp  + m_ElementSize);
      vap = (vec4*)((char*)vap + m_ElementSize);
    }
}

v4buf::~v4buf()
{
  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray    = NULL;
  m_ArrayCount  = 0;
  m_VecOffset   = 0;
  m_ElementSize = 0;
}

int v4buf::length()
{
  return m_ArrayCount;
}

int v4buf::size()
{
  return m_ElementSize;
}

int v4buf::offset()
{
  return m_VecOffset;
}

void* v4buf::vptr()
{
  return (void*)((char*)m_VecArray + m_VecOffset);
}

void v4buf::add(v4& v)
{
  void* vp;
  vec4* pv;

  int iCurSize= m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 ) memcpy(vp,(void*)m_VecArray,iCurSize);

  pv = (vec4*)(((char*)vp) + (iCurSize + m_VecOffset));

  *pv = *v.vec;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec4*)vp;
  ++m_ArrayCount;
}

void v4buf::add(vec4& v)
{
  void* vp;
  vec4* pv;

  int iCurSize = m_ArrayCount * m_ElementSize;

  assert(NULL != (vp=(void*)new char[m_ElementSize*(1+m_ArrayCount)]));

  if ( iCurSize > 0 ) memcpy(vp,(void*)m_VecArray,iCurSize);

  pv = (vec4*)(((char*)vp) + (iCurSize + m_VecOffset));

  *pv = v;

  if ( NULL != m_VecArray ) delete m_VecArray;

  m_VecArray = (vec4*)vp;
  ++m_ArrayCount;
}

void v4buf::operator += (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator -= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubFloatFromBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator *= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulFloatToBuf(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator /= (const float s)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByFloat(pv,m_ElementSize,pv,m_ElementSize,s,m_ArrayCount);
}

void v4buf::operator += (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddVecToBlock((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator -= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubVecFromBlock((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator *= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulBufByVec((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator /= (const v4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByVec((void*)pv,(void*)pv,v.vec,m_ElementSize,m_ArrayCount);
}

void v4buf::operator += (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufAddVecToBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator -= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufSubVecFromBlock((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator *= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufMulBufByVec((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator /= (const vec4& v)
{
  void* pv = (void*)(((char*)m_VecArray) + m_VecOffset);

  if ( NULL != m_VecArray ) Vec4BufDivBufByVec((void*)pv,(void*)pv,&v,m_ElementSize,m_ArrayCount);
}

void v4buf::operator += (struct v4buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufAddBufToBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v4buf::operator -= (struct v4buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufSubBufFromBuf(pv,iThisSize,
			   pv,iThisSize,
			   pu,iThatSize,
			   iCount);
    }
}

void v4buf::operator *= (struct v4buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufMulBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}
  
void v4buf::operator /= (struct v4buf& va)
{
  int   iThisSize = m_ElementSize;
  void* pv        = (void*)(((char*)m_VecArray) + m_VecOffset);
  int   iThatSize = va.m_ElementSize;
  void* pu        = (void*)(((char*)va.m_VecArray) + va.m_VecOffset);

  int iThisCount = m_ArrayCount;
  int iThatCount = va.m_ArrayCount;

  int iCount     = (iThisCount == iThatCount ? iThisCount :
		    iThisCount <  iThatCount ? iThisCount :
		    iThatCount);

  if ( NULL != m_VecArray )
    {
      Vec4BufDivBufByBuf(pv,iThisSize,
			 pv,iThisSize,
			 pu,iThatSize,
			 iCount);
    }
}

void v4buf::operator *= (m4& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < m_ArrayCount ; ++i )
	{
	  Mat4MultiplyVec((vec4*)pv,m.m,(vec4*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

void v4buf::operator *= (mat4& m)
{
  void* pv;

  if ( NULL != m_VecArray )
    {
      pv = (void*)(((char*)m_VecArray) + m_VecOffset);

      for( int i=0 ; i < m_ArrayCount ; ++i )
	{
	  Mat4MultiplyVec((vec4*)pv,&m,(vec4*)pv);
	  pv = (void*)(((char*)pv) + m_ElementSize);
	}
    }
}

vec4& v4buf::operator[](int iItem)
{
  int iItemCount = m_ArrayCount;

  if ( iItem < iItemCount )
    {
      ;
    }
  else if ( iItem == iItemCount )
    {
      vec4 vTemp = {0.0,0.0,0.0};
      add(vTemp);
    }
  else
    {
      assert(0);
    }

  m_ArrayCount = iItemCount;

  return *((vec4*)(((char*)m_VecArray) + (m_ElementSize*iItem) + m_VecOffset));
}

v4buf& v4buf::operator=(const v4buf& va)
{
  void* vec;

  assert(NULL != (vec=(void*)new char[va.m_ElementSize*va.m_ArrayCount]));

  if ( NULL != m_VecArray ) delete (vec4*)m_VecArray;

  m_VecArray    = vec;
  m_ArrayCount  = va.m_ArrayCount;
  m_VecOffset   = va.m_VecOffset;
  m_ElementSize = va.m_ElementSize;

  vec4* vp  = (vec4*)((char*)vec + m_VecOffset);
  vec4* vap = (vec4*)((char*)va.m_VecArray + m_VecOffset);

  for( int i=0 ; i < m_ArrayCount ; ++i )
    {
      *vp = *vap;
      vp  = (vec4*)((char*)vp  + m_ElementSize);
      vap = (vec4*)((char*)vap + m_ElementSize);
    }

  return *this;
}

void v4buf::cross(const v4buf& va)
{
  Vec4BufCrossBuf((void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)m_VecArray + m_VecOffset),
		  m_ElementSize,
		  (void*)((char*)va.m_VecArray + va.m_VecOffset),
		  va.m_ElementSize,
		  (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::sqr()
{
  Vec4BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		m_ArrayCount);
}

void v4buf::sqr(v4buf& va)
{
  Vec4BufSqrBuf((void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		(m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::sqrt()
{
  Vec4BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 m_ArrayCount);
}

void v4buf::sqrt(v4buf& va)
{
  Vec4BufSqrtBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::normalize()
{
  Vec4BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      m_ArrayCount);
}

void v4buf::normalize(v4buf& va)
{
  Vec4BufNormalizeBuf((void*)((char*)m_VecArray + m_VecOffset),
		      m_ElementSize,
		      (void*)((char*)va.m_VecArray + va.m_VecOffset),
		      va.m_ElementSize,
		      (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::lerp(const v4buf& va,const float step)
{
  Vec4BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 step,
		 (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount));
}

void v4buf::lerp(const v4buf& va,const v4buf& vb,const float step)
{
  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iCount       <= vb.m_ArrayCount ? iCount       : vb.m_ArrayCount);

  Vec4BufLerpBuf((void*)((char*)m_VecArray + m_VecOffset),
		 m_ElementSize,
		 (void*)((char*)va.m_VecArray + va.m_VecOffset),
		 va.m_ElementSize,
		 (void*)((char*)vb.m_VecArray + vb.m_VecOffset),
		 vb.m_ElementSize,
		 step,
		 iCount);
}

void v4buf::dot(float* fpArray,const int32_t iArrayLength,const v4buf& va)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= va.m_ArrayCount ? m_ArrayCount : va.m_ArrayCount);
      iCount = (iArrayLength <= iCount          ? iArrayLength : iCount);

  Vec4BufDotBuf(fpArray,
		sizeof(float),
		(void*)((char*)m_VecArray + m_VecOffset),
		m_ElementSize,
		(void*)((char*)va.m_VecArray + va.m_VecOffset),
		va.m_ElementSize,
		iCount);
}

void v4buf::length(float* fpArray,int32_t iArrayLength)
{
  if ( NULL == fpArray || 0 == iArrayLength ) return;

  int iCount = (m_ArrayCount <= iArrayLength ? m_ArrayCount : iArrayLength);

  Vec4BufLengthBuf(fpArray,
		   sizeof(float),
		   (void*)((char*)m_VecArray + m_VecOffset),
		   m_ElementSize,
		   iCount);
}

#endif
