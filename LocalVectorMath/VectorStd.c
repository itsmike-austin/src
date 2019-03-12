#include <math.h>
#include <string.h>

/* ----------------------------------------
 * Replace these with a single include
 *
 * XXX TBD: Modify the status cleaup method to have both
 *          self-clearing and standard methods for floating
 *          point error management.
 */

struct _vector2 {
  float x,y;
};

typedef struct _vector2 vec2;

struct _vector3 {
  float x,y,z,n;
};

typedef struct _vector3 vec3;

struct _vector4 {
  float x,y,z,w;
};

typedef struct _vector4 vec4;

struct _matrix2 {
  float m00,m01,m10,m11;
};

typedef struct _matrix2 mat2;

struct _matrix3 {
  float m00,m01,m02,n03;
  float m10,m11,m12,n13;
  float m20,m21,m22,n23;
};

typedef struct _matrix3 mat3;

struct _matrix4 {
  float m00,m01,m02,m03;
  float m10,m11,m12,m13;
  float m20,m21,m22,m23;
  float m30,m31,m32,m33;
};

struct _quaternion {
  float x,y,z,w;
};

typedef struct _quaternion quaternion;

typedef struct _matrix4 mat4;

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

#if defined(_WIN32) || defined(_WIN64)
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uss_t;
#endif

/* --------------------------
 * Methods
 */

void GetFpuStatusStd(unsigned short* uStatus)
{
  __asm {
    fnstsw [uStatus]
  }
}

void ClearFpuStatusStd(unsigned short* uStatus)
{
  unsigned short uStat;
  __asm
    {
      fnstsw uStat
    }

  if ( 0 != uStat )
    {
      __asm {
	fnclex
      }
    }
  *uStatus = uStat;
}

float FloatLerpStd(const float u,const float v,const float x)
{
  uss_t us;

  float   r = (float)(u * (1 - x)) + (v * x);

  ClearFpuStatusStd(&us);

  return r;
}

void FloatLerpPtrStd(float* r,const float* pu,const float* pv,const float* px)
{
  uss_t us;

  *r = ((*pu) * (1-(*px))) + ((*pv) * (*px));

  ClearFpuStatusStd(&us);
}

float FloatSqrStd(float x)
{
  uss_t us;

  float r = (float)x*x;

  ClearFpuStatusStd(&us);

  return r;
}

float FloatSqrPtrStd(float* px)
{
  uss_t us;

  float r = (float)((*px) * (*px));

  ClearFpuStatusStd(&us);

  return r;
}

void Vec2CopyStd(vec2* r,const vec2* v)
{
  memcpy((void*)r,(void*)v,sizeof*r);
}

void Vec2CopyBlockStd(vec2* r,const vec2* v,const int32_t iCount)
{
  int i;
  vec2* pSrc = (vec2*)v;
  vec2* pDst = r;
    

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)pDst,(void*)pSrc++,sizeof*pSrc++);
    }
}

void BuildVec2PackedArrayStd(vec2* r,const vec2** base,int32_t iCount)
{
  int    i;
  vec2*  pDst = r;

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)pDst++,(void*)base[i],sizeof*r);
    }
}

void Vec2AddFloatStd(vec2* r,const vec2* u,const float s)
{
  uss_t us;

  r->x = u->x + s;
  r->y = u->y + s;

  ClearFpuStatusStd(&us);
}

void Vec2SubtractFloatStd(vec2* r,const vec2* u,const float s)
{
  uss_t us;

  r->x = u->x - s;
  r->y = u->y - s;

  ClearFpuStatusStd(&us);
}

void Vec2MultiplyFloatStd(vec2* r,const vec2* u,const float s)
{
  uss_t us;

  r->x = u->x * s;
  r->y = u->y * s;

  ClearFpuStatusStd(&us);
}

void Vec2FloatMultiplyStd(vec2* r,const float s,const vec2* v)
{
  uss_t us;

  r->x = v->x * s;
  r->y = v->y * s;

  ClearFpuStatusStd(&us);
}

void Vec2DivideFloatStd(vec2* r,const vec2* u,const float s)
{
  uss_t us;

  if ( 0 != s )
    {
      r->x = u->x / s;
      r->y = u->y / s;
    }
  else
    {
      r->x = r->y = 0.0f;
    }
  ClearFpuStatusStd(&us);
}

void Vec2AddFloatToBlockStd(vec2* rv,const float s,const int32_t iCount)
{
  int   i;
  vec2* r = rv;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      r->x += s;
      r->y += s;
      ++r;
    }
  ClearFpuStatusStd(&us);
}

void Vec2AddFloatToBlockSizeStd(void*         rv,
				const float   s,
				const int32_t iSize,
				const int32_t iCount)
{
  int   i;
  void* rp = rv;
  vec2* r  = (vec2*)rv;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      r->x += s;
      r->y += s;
      r = (vec2*)((char*)rp+=iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufAddFloatToBlockStd(void*         r,
			       const void*   v,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int  i;
  void* rp = r;
  void* vp = (void*)v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)rp)->x = ((vec2*)vp)->x + s;
      ((vec2*)rp)->y = ((vec2*)vp)->y + s;
      rp = ((char*)rp + iSize);
      vp = ((char*)vp + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufAddFloatToBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   v,
			     const int32_t iVSize,
			     const float   s,
			     const int32_t iCount)
{
  int   i;
  void* rp = r;
  void* vp = (void*)v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)rp)->x = ((vec2*)vp)->x + s;
      ((vec2*)rp)->y = ((vec2*)vp)->y + s;
      rp = ((char*)rp + iRSize);
      vp = ((char*)vp + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2SubtractFloatFromBlockStd(vec2*         rv,
				   const float   s,
				   const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv->x -= s;
      rv->y -= s;
      ++rv;
    }
  ClearFpuStatusStd(&us);
}

void Vec2SubFloatFromBlockSizeStd(void*       rv,
				  const float s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int   i;
  vec2* vp = (vec2*)rv;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      vp->x -= s;
      vp->y -= s;
      rv = (void*)((char*)rv + iSize);
      vp = (vec2*)rv;
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSubFloatFromBlkSizeStd(void*         r,
				   const void*   v,
				   const float   s,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  vec2* vp = (vec2*)v;
  vec2* rp = (vec2*)r;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rp->x = vp->x - s;
      rp->y = vp->y - s;
      r  = (void*)((char*)r + iSize);
      v  = (void*)((char*)v + iSize);
      rp = (vec2*)r;
      vp = (vec2*)v;
    }
  ClearFpuStatusStd(&us);
}

Vec2BufSubFloatFromBufStd(void*         r,
			  const int32_t iDstSize,
			  const void*   v,
			  const int32_t iSrcSize,
			  const float   s,
			  const int32_t iCount)
{
  int   i;
  vec2* rp = (vec2*)r;
  vec2* vp = (vec2*)v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rp->x = vp->x - s;
      rp->y = vp->y - s;
      r  = (void*)((char*)r + iDstSize);
      v  = (void*)((char*)v + iSrcSize);
      rp = (vec2*)r;
      vp = (vec2*)v;
    }
  ClearFpuStatusStd(&us);
}

void Vec2MultiplyBlockByFloatStd(vec2*         rv,
				 const float   s,
				 const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv->x *= s;
      rv->y *= s;
      ++rv;
    }
  ClearFpuStatusStd(&us);
}

void Vec2MultiplyBlkByFloatSizeStd(void*         rv,
				   const float   s,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)rv)->x *= s;
      ((vec2*)rv)->y *= s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufMulBlockByFloatSizeStd(void*         r,
				   const void*   v,
				   const float   s,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)v)->x * s;
      ((vec2*)r)->y = ((vec2*)v)->y * s;
      r = (void*)((char*)r + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}
  
void Vec2BufMulBlockByFloatBufStd(void*         r,
				  const int32_t iDstSize,
				  const void*   v,
				  const int32_t iSrcSize,
				  const float   s,
				  const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)v)->x * s;
      ((vec2*)r)->y = ((vec2*)v)->y * s;
      r = (void*)((char*)r + iDstSize);
      v = (void*)((char*)v + iSrcSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2DivideBlockByFloatStd(vec2*         rv,
			       const float   s,
			       const int32_t iCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      rv->x /= s;
      rv->y /= s;
      ++rv;
    }
  ClearFpuStatusStd(&us);
}

void Vec2DivideBlockByFloatSizeStd(void*         rv,
				   const float   s,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)rv)->x /= s;
      ((vec2*)rv)->y /= s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDivBlockByFloatSizeStd(void*         r,
				   const void*   v,
				   const float   s,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)v)->x / s;
      ((vec2*)r)->y = ((vec2*)v)->y / s;
      r = (void*)((char*)r + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDivBufByFloatStd(void*         r,
			     const int32_t iDstSize,
			     const void*   v,
			     const int32_t iSrcSize,
			     const float   s,
			     const int32_t iCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)v)->x / s;
      ((vec2*)r)->y = ((vec2*)v)->y / s;
      r = (void*)((char*)r + iDstSize);
      v = (void*)((char*)v + iSrcSize);
    }
  ClearFpuStatusStd(&us);
}

// Basic 2-Dimensional Vector Methods
//

void Vec2NegateStd(vec2* r,const vec2* u)
{
  r->x = -(u->x);
  r->y = -(u->y);
}

void Vec2AddStd(vec2* r,const vec2* u,const vec2* v)
{
  uss_t us;

  r->x = u->x + v->x;
  r->y = u->y + v->y;

  ClearFpuStatusStd(&us);
}

void Vec2SubtractStd(vec2* r,const vec2* u,const vec2* v)
{
  uss_t us;

  r->x = u->x - v->x;
  r->y = u->y - v->y;

  ClearFpuStatusStd(&us);
}

void Vec2MultiplyStd(vec2* r,const vec2* u,const vec2* v)
{
  uss_t us;

  r->x = u->x * v->x;
  r->y = u->y * v->y;

  ClearFpuStatusStd(&us);
}

void Vec2DivideStd(vec2* r,const vec2* u,const vec2* v)
{
  uss_t us;

  if ( 0.0f == v->x || 0.0 == v->y ) return;

  r->x = u->x / v->x;
  r->y = u->y / v->y;

  ClearFpuStatusStd(&us);
}

void Vec2EqualsStd(int32_t* iFlag,const vec2* u,const vec2* v)
{
  *iFlag = (int32_t)(u->x == v->x && u->y == v->y);
}

void Vec2NotEqualsStd(int32_t* iFlag,const vec2* u,const vec2* v)
{
  *iFlag = (int32_t)(u->x != v->x || u->y != v->y);
}

// Basic 2-Dimensional Vector - 2-Dimensional Vector Array Methods
//

void Vec2NegateBlockStd(vec2* rv,const int32_t nCount)
{
  int   i;

  for( i=0 ; i < nCount ; ++i )
    {
      rv[i].x = -(rv[i].x);
      rv[i].y = -(rv[i].y);
    }
}

void Vec2NegateBlockBySizeStd(void*         rv,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)rv)->x = -(((vec2*)rv)->x);
      ((vec2*)rv)->y = -(((vec2*)rv)->y);
      rv = (void*)((char*)rv + iSize);
    }
}

void Vec2BufNegateBlockBySizeStd(void*         r,
				 const void*   v,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = -(((vec2*)v)->x);
      ((vec2*)r)->y = -(((vec2*)v)->y);
      r = (void*)((char*)r + iSize);
      v = (void*)((char*)v + iSize);
    }
}

void Vec2BufNegateBufBySizeStd(void*         r,
			       const int32_t iDstSize,
			       const void*   v,
			       const int32_t iSrcSize,
			       const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = -(((vec2*)v)->x);
      ((vec2*)r)->y = -(((vec2*)v)->y);
      r = (void*)((char*)r + iDstSize);
      v = (void*)((char*)v + iSrcSize);
    }
}

void Vec2AddVec2ToBlockStd(vec2* ru,const vec2* v,const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x += v->x;
      ru[i].y += v->y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2AddBlockToBlockStd(vec2* ru,const vec2* v,const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x += v[i].x;
      ru[i].y += v[i].y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufAddVec2ToBlockBySizeStd(void*         r,
				    const void*   u,
				    const vec2*   v,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x + v->x;
      ((vec2*)r)->y = ((vec2*)u)->y + v->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufAddBlockBySizeStd(vec2*         r,
			      const vec2*   u,
			      const vec2*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x + ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y + ((vec2*)v)->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufAddBufBySizeStd(vec2*         r,
			    const int32_t iSaveSize,
			    const vec2*   u,
			    const int32_t iSrcSize0,
			    const vec2*   v,
			    const int32_t iSrcSize1,
			    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x + ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y + ((vec2*)v)->y;
      r = (void*)((char*)r + iSaveSize);
      u = (void*)((char*)u + iSrcSize0);
      v = (void*)((char*)v + iSrcSize1);
    }
  ClearFpuStatusStd(&us);
}

void Vec2SubtractVec2FromBlockStd(vec2* pDest,vec2* pVector,int32_t nCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      pDest[i].x -= pVector->x;
      pDest[i].y -= pVector->y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2SubtractBlockFromBlockStd(vec2* pDest,vec2* pSource,int32_t nCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      pDest[i].x -= pSource[i].x;
      pDest[i].y -= pSource[i].y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSubVec2FromBlkBySizeStd(void*         r,
				    const void*   u,
				    const vec2*   v,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x - v->x;
      ((vec2*)r)->y = ((vec2*)u)->y - v->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSubBlockBySizeStd(void*         r,
			      const void*   u,
			      const void*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x - ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y - ((vec2*)v)->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSubBufBySizeStd(vec2* r,
			    const int32_t iSaveSize,
			    const vec2* u,
			    const int32_t iSrcSize0,
			    const vec2* v,
			    const int32_t iSrcSize1,
			    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x - ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y - ((vec2*)v)->y;
      r = (void*)((char*)r + iSaveSize);
      u = (void*)((char*)u + iSrcSize0);
      v = (void*)((char*)v + iSrcSize1);
    }
  ClearFpuStatusStd(&us);
}

// Basic 2-Dimensional Vector Array - 2-Dimensional Vector Array Methods
//

void Vec2MultiplyBlockByVec2Std(vec2* pDest,vec2* pVector,int32_t nCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      pDest[i].x *= pVector->x;
      pDest[i].y *= pVector->y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2MultiplyBlockByBlockStd(vec2* pDest,vec2* pSource,int32_t nCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      pDest[i].x *= pSource[i].x;
      pDest[i].y *= pSource[i].y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufMulVec2ByBlockSizeStd(void*         r,
				  const void*   u,
				  const vec2*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x * v->x;
      ((vec2*)r)->y = ((vec2*)u)->y * v->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufMulBlockBySizeStd(vec2*         r,
			      const vec2*   u,
			      const vec2*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x * ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y * ((vec2*)v)->y;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufMulBufBySizeStd(vec2*         r,
			    const int32_t iDstSize,
			    const vec2*   u,
			    const int32_t iSrcSize0,
			    const vec2*   v,
			    const int32_t iSrcSize1,
			    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = ((vec2*)u)->x * ((vec2*)v)->x;
      ((vec2*)r)->y = ((vec2*)u)->y * ((vec2*)v)->y;
      r = (void*)((char*)r + iDstSize);
      u = (void*)((char*)u + iSrcSize0);
      v = (void*)((char*)v + iSrcSize1);
    }
  ClearFpuStatusStd(&us);
}

// Basic 2-Dimensional Vector Array - 2-Dimensional Vector Array Methods
//

void Vec2DivideBlockByVec2Std(vec2* pDest,vec2* pVector,int32_t nCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == pVector->x )
    {
      for( i=0 ; i < nCount ; ++i )
	{
	  pDest[i].x = 0.0f;
	}
    }
  else
    {
      for( i=0 ; i < nCount ; ++i )
	{
	  pDest[i].x /= pVector->x;
	}
    }

  if ( 0.0f == pVector->y )
    {
      for( i=0 ; i < nCount ; ++i )
	{
	  pDest[i].y = 0.0f;
	}
    }
  else
    {
      for( i=0 ; i < nCount ; ++i )
	{
	  pDest[i].y /= pVector->y;
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec2DivideBlockByBlockStd(vec2* pDest,vec2* pSource,int32_t nCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      pDest[i].x = (0.0f != pSource[i].x ? pDest[i].x/pSource[i].x : 0.0f);
      pDest[i].y = (0.0f != pSource[i].y ? pDest[i].y/pSource[i].y : 0.0f);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDivVec2ByBlockSizeStd(void*         r,
				  const void*   u,
				  const vec2*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int   i;
  uss_t us;

  if ( 0.0f == v->x )
    {
      void* rp = r;

      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec2*)rp)->x = 0.0f;
	  rp = (void*)((char*)rp + iSize);
	}
    }
  else
    {
      void* rp = (void*)r;
      void* up = (void*)u;

      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec2*)rp)->x = ((vec2*)up)->x / v->x;
	  rp = (void*)((char*)rp + iSize);
	  up = (void*)((char*)up + iSize);
	}
    }

  if ( 0.0f == v->y )
    {
      void* rp = r;

      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec2*)rp)->y = 0.0f;
	  rp = (void*)((char*)rp + iSize);
	}
    }
  else
    {
      void* rp = (void*)r;
      void* up = (void*)u;

      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec2*)rp)->y = ((vec2*)up)->y / v->y;
	  rp = (void*)((char*)rp + iSize);
	  up = (void*)((char*)up + iSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDivBlockBySizeStd(void*       r,
			      const void* u,
			      const void* v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = (0.0f != ((vec2*)v)->x ? ((vec2*)u)->x / ((vec2*)v)->x : 0.0f);
      ((vec2*)r)->y = (0.0f != ((vec2*)v)->y ? ((vec2*)u)->y / ((vec2*)v)->y : 0.0f);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDivBufBySizeStd(void*         r,
			    const int32_t iDstSize,
			    const void*   u,
			    const int32_t iUSize,
			    const void*   v,
			    const int32_t iVSize,
			    const int32_t iCount)
{
  int   i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec2*)r)->x = (0.0f != ((vec2*)v)->x ? ((vec2*)u)->x / ((vec2*)v)->x : 0.0f);
      ((vec2*)r)->y = (0.0f != ((vec2*)v)->y ? ((vec2*)u)->y / ((vec2*)v)->y : 0.0f);
      r = (void*)((char*)r + iDstSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}


// Fundamental 2-Dimensional Vector Methods
//

void Vec2LerpStd(vec2* r,const vec2* u,const vec2* v,const float step)
{
  uss_t us;

  r->x = u->x * (1-step) + v->x * step;
  r->y = u->y * (1-step) + v->y * step;

  ClearFpuStatusStd(&us);
}

void Vec2SqrStd(vec2* r,const vec2* u)
{
  uss_t us;

  r->x = u->x * u->x;
  r->y = u->y * u->y;

  ClearFpuStatusStd(&us);
}

void Vec2SqrtStd(vec2* r,const vec2* u)
{
  uss_t us;

  r->x = (float)sqrt(u->x);
  r->y = (float)sqrt(u->y);

  ClearFpuStatusStd(&us);
}

void Vec2NormalizeStd(vec2* r,const vec2* v)
{
  uss_t  us;
  double fBase = sqrt(v->x*v->x + v->y*v->y);

  if ( 0.0f == fBase )
    {
      r->x = 0.0f;
      r->y = 0.0f;
    }
  else
    {
      r->x = (float)(v->x / fBase);
      r->y = (float)(v->y / fBase);
    }
  ClearFpuStatusStd(&us);
}

void Vec2DotStd(float* r,const vec2* u,const vec2* v)
{
  uss_t us;
  
  *r = (float)(u->x * v->x + u->y * v->y);

  ClearFpuStatusStd(&us);
}

void Vec2LengthStd(float* r,const vec2* v)
{
  uss_t us;

  *r = (float)sqrt(v->x*v->x + v->y*v->y);

  ClearFpuStatusStd(&us);
}

// Fundamental 2-Dimensional Vector Array Methods
//

void Vec2LerpBlockStd(vec2*         r,
		      const vec2*   u,
		      const vec2*   v,
		      const float   step,
		      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r,++u,++v )
    {
      r->x = u->x * (1 - step) + v->x * step;
      r->y = u->y * (1 - step) + v->y * step;
    }
  ClearFpuStatusStd(&us);
}

void Vec2SqrBlockStd(vec2* r,const vec2* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r,++v )
    {
      r->x = v->x * v->x;
      r->y = v->y * v->y;
    }
  ClearFpuStatusStd(&us);
}

void Vec2SqrtBlockStd(vec2* r,const vec2* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r,++v )
    {
      r->x = (float)sqrt(v->x);
      r->y = (float)sqrt(v->y);
    }
  ClearFpuStatusStd(&us);
}

void Vec2NormalizeBlockStd(vec2* r,const vec2* v,const int32_t iCount)
{
  int i;
  float fBase;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      fBase = (float)sqrt((double)(v[i].x*v[i].x + v[i].y*v[i].y));

      if ( 0.0f == fBase )
	{
	  r[i].x = 0.0f;
	  r[i].y = 0.0f;
	}
      else
	{
	  r[i].x = v[i].x / fBase;
	  r[i].y = v[i].y / fBase;
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec2DotBlockStd(float* r,const vec2* u,const vec2* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r,++u,++v )
    {
      *r = (u->x*v->x + u->y*v->y);
    }
  ClearFpuStatusStd(&us);
}

void Vec2LengthBlockStd(float* r,const vec2* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r,++v )
    {
      *r = (float)sqrt(v->x*v->x + v->y*v->y);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufLerpBufStd(void*         r,
		       const int32_t iRSize,
		       const void*   u,
		       const int32_t iUSize,
		       const void*   v,
		       const int32_t iVSize,
		       const float   s,
		       const int32_t iCount)
{
  int    i;
  uss_t  us;
  double dBase = 1.0 - s;
  vec2*  rp = (vec2*)r;
  vec2*  up = (vec2*)u;
  vec2*  vp = (vec2*)v;

  for( i=0 ; i < iCount ; ++i )
    {
      rp->x = (float)(dBase * up->x + vp->x * s);
      rp->y = (float)(dBase * up->y + vp->y * s);

      rp = (vec2*)((char*)rp + iRSize);
      up = (vec2*)((char*)up + iUSize);
      vp = (vec2*)((char*)vp + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSqrBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const int32_t iCount)
{
  int   i;
  uss_t us;
  vec2* rp = (vec2*)r;
  vec2* up = (vec2*)u;

  for( i=0 ; i < iCount ; ++i )
    {
      rp->x = up->x * up->x;
      rp->y = up->y * up->y;

      rp = (vec2*)((char*)rp + iRSize);
      up = (vec2*)((char*)up + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufSqrtBufStd(void*         r,
		       const int32_t iRSize,
		       const void*   u,
		       const int32_t iUSize,
		       const int32_t iCount)
{
  int   i;
  uss_t us;
  vec2* rp = (vec2*)r;
  vec2* up = (vec2*)u;

  for( i=0 ; i < iCount ; ++i )
    {
      rp->x = (float)sqrt(up->x);
      rp->y = (float)sqrt(up->y);

      rp = (vec2*)((char*)rp + iRSize);
      up = (vec2*)((char*)up + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufNormalizeBufStd(void*         r,
			    const int32_t iRSize,
			    const void*   u,
			    const int32_t iUSize,
			    const int32_t iCount)
{
  int   i;
  uss_t us;
  vec2* rp = (vec2*)r;
  vec2* up = (vec2*)u;

  double dBase;

  for( i=0 ; i < iCount ; ++i )
    {
      dBase  =  up->x * up->x;
      dBase += (up->y * up->y);
      if ( 0.0 != dBase )
	{
	  rp->x = (float)(up->x / dBase);
	  rp->y = (float)(up->y / dBase);
	}
      else
	{
	  rp->x = up->x;
	  rp->y = up->y;
	}

      rp = (vec2*)((char*)rp + iRSize);
      up = (vec2*)((char*)up + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufDotBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const void*   v,
		      const int32_t iVSize,
		      const int32_t iCount)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  vec2*  up = (vec2*) u;
  vec2*  vp = (vec2*) v;

  for( i=0 ; i < iCount ; ++i )
    {
      *rp = (float)(up->x*vp->x + up->y*vp->y);

      rp = (float*)((char*)rp + iRSize);
      up = (vec2*) ((char*)up + iUSize);
      vp = (vec2*) ((char*)vp + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec2BufLengthBufStd(void* r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const int32_t iCount)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  vec2*  up = (vec2*) u;

  for( i=0 ; i < iCount ; ++i )
    {
      *rp = (float)sqrt(up->x*up->x + up->y*up->y);

      rp = (float*)((char*)rp + iRSize);
      up = (vec2*) ((char*)up + iUSize);
    }
  ClearFpuStatusStd(&us);
}

// Fundamental 3-Dimensional Vector Scalar Methods 
//

void Vec3CopyStd(vec3* pDest,const vec3* pSource)
{
  memcpy((void*)pDest,(void*)pSource,sizeof(vec3));
}

void Vec3CopyBlockStd(vec3* pDest,const vec3* pSource,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)&pDest[i],(void*)&pSource[i],sizeof(vec3));
    }
}

void BuildVec3PackedArrayStd(vec3* r,const vec3** pSrc,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)&r[i],(void*)pSrc[i],sizeof(vec3));
    }
}

void Vec3AddFloatStd(vec3*  r,const vec3* u,const float s )
{
  uss_t us;

  r->x = u->x + s;
  r->y = u->y + s;
  r->z = u->z + s;

  ClearFpuStatusStd(&us);
}

void Vec3AddFloatToBlockStd(vec3* rv,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv[i].x += s;
      rv[i].y += s;
      rv[i].z += s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3AddFloatToBlockBySizeStd(void*         rv,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)rv)->x += s;
      ((vec3*)rv)->y += s;
      ((vec3*)rv)->z += s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddFloatToBlockStd(void*         r,
			       const void*   u,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + s;
      ((vec3*)r)->y = ((vec3*)u)->y + s;
      ((vec3*)r)->z = ((vec3*)u)->z + s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddFloatToBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + s;
      ((vec3*)r)->y = ((vec3*)u)->y + s;
      ((vec3*)r)->z = ((vec3*)u)->z + s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubtractFloatStd(vec3*  r,const vec3* u,const float s)
{
  uss_t us;

  r->x = u->x - s;
  r->y = u->y - s;
  r->z = u->z - s;

  ClearFpuStatusStd(&us);
}

void Vec3SubtractFloatFromBlockStd(vec3* rv,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv[i].x -= s;
      rv[i].y -= s;
      rv[i].z -= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubFloatFromBlockBySizeStd(void*         rv,
				    const float   s,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)rv)->x -= s;
      ((vec3*)rv)->y -= s;
      ((vec3*)rv)->z -= s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubFloatFromBlockStd(void*         r,
				 const void*   u,
				 const float   s,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - s;
      ((vec3*)r)->y = ((vec3*)u)->y - s;
      ((vec3*)r)->z = ((vec3*)u)->z - s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubFloatFromBufStd(void*  r,
			       const int32_t iRSize,
			       const void* u,
			       const int32_t iUSize,
			       const float s,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - s;
      ((vec3*)r)->y = ((vec3*)u)->y - s;
      ((vec3*)r)->z = ((vec3*)u)->z - s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3MultiplyFloatStd(vec3*  r,const vec3* u,const float s)
{
  uss_t us;

  r->x = u->x * s;
  r->y = u->y * s;
  r->z = u->z * s;

  ClearFpuStatusStd(&us);
}

void Vec3MultiplyFloatToBlockStd(vec3* ru,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= s;
      ru[i].y *= s;
      ru[i].z *= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3MulFloatToBlockBySizeStd(void*         ru,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x *= s;
      ((vec3*)ru)->y *= s;
      ((vec3*)ru)->z *= s;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulFloatToBlockStd(void*         r,
			       const void*   u,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * s;
      ((vec3*)r)->y = ((vec3*)u)->y * s;
      ((vec3*)r)->z = ((vec3*)u)->z * s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulFloatToBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * s;
      ((vec3*)r)->y = ((vec3*)u)->y * s;
      ((vec3*)r)->z = ((vec3*)u)->z * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivideFloatStd(vec3*  r,const vec3* u,const float s)
{
  uss_t us;

  if ( 0.0f == s )
    {
      r->x = 0.0f;
      r->y = 0.0f;
      r->z = 0.0f;
    }
  else
    {
      r->x = u->x / s;
      r->y = u->y / s;
      r->z = u->z / s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivideBlockByFloatStd(vec3* ru,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x /= s;
      ru[i].y /= s;
      ru[i].z /= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivBlockByFloatBySizeStd(void*         ru,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x /= s;
      ((vec3*)ru)->y /= s;
      ((vec3*)ru)->z /= s;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBlockByFloatStd(void*         r,
			       const void*   u,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s )
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec3*)r)->x = 0.0f;
	  ((vec3*)r)->y = 0.0f;
	  ((vec3*)r)->z = 0.0f;
	  r = (void*)((char*)r + iSize);
	}
    }
  else
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec3*)r)->x = ((vec3*)u)->x / s;
	  ((vec3*)r)->y = ((vec3*)u)->y / s;
	  ((vec3*)r)->z = ((vec3*)u)->z / s;
	  r = (void*)((char*)r + iSize);
	  u = (void*)((char*)u + iSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBufByFloatStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s )
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec3*)r)->x = 0.0f;
	  ((vec3*)r)->y = 0.0f;
	  ((vec3*)r)->z = 0.0f;
	  r = (void*)((char*)r + iRSize);
	}
    }
  else
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec3*)r)->x = ((vec3*)u)->x / s;
	  ((vec3*)r)->y = ((vec3*)u)->y / s;
	  ((vec3*)r)->z = ((vec3*)u)->z / s;
	  r = (void*)((char*)r + iRSize);
	  u = (void*)((char*)u + iUSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3EqualsStd(int32_t* iFlag,const vec3* u,const vec3* v)
{
  *iFlag = (int32_t)(u->x == v->x && u->y == v->y && u->z == v->z);
}

void Vec3NotEqualsStd(int32_t* iFlag,const vec3* u,const vec3* v)
{
  *iFlag = (int32_t)(u->x != v->x || u->y != v->y || u->z != v->z);
}

// Fundamental 3-Dimensional Vector-Scalar Array Methods

void Vec3NegateStd(vec3*  r,const vec3* v)
{
  r->x = -(v->x);
  r->y = -(v->y);
  r->z = -(v->z);
}

void Vec3NegateBlockStd(vec3* ru,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = -ru[i].x;
      ru[i].y = -ru[i].y;
      ru[i].z = -ru[i].z;
    }
}

void Vec3NegateBlockBySizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x = -(((vec3*)ru)->x);
      ((vec3*)ru)->y = -(((vec3*)ru)->y);
      ((vec3*)ru)->z = -(((vec3*)ru)->z);
      ru = (void*)((char*)ru + iSize);
    }
}

void Vec3BufNegateBlockStd(void*         r,
			   const void*   u,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = -(((vec3*)u)->x);
      ((vec3*)r)->y = -(((vec3*)u)->y);
      ((vec3*)r)->z = -(((vec3*)u)->z);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
}

void Vec3BufNegateBufStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = -(((vec3*)u)->x);
      ((vec3*)r)->y = -(((vec3*)u)->y);
      ((vec3*)r)->z = -(((vec3*)u)->z);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }  
}

void Vec3AddStd(vec3*  r,const vec3* u,const vec3* v)
{
  uss_t us;

  r->x = u->x + v->x;
  r->y = u->y + v->y;
  r->z = u->z + v->z;

  ClearFpuStatusStd(&us);
}

void Vec3AddVecToBlockStd(vec3* ru,const vec3* v,const int32_t nCount)
{
  int i;
  uss_t us;

  vec3 vd = *v;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x += vd.x;
      ru[i].y += vd.y;
      ru[i].z += vd.z;
      ru[i].n  = 0.0f;
    }
  ClearFpuStatusStd(&us);
}

void Vec3AddVecToBlockBySizeStd(void*         ru,
				const vec3*   v,
				const int32_t iSize,
				const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x += vd.x;
      ((vec3*)ru)->y += vd.y;
      ((vec3*)ru)->z += vd.z;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddVecToBlockStd(void*         r,
			     const void*   u,
			     const vec3*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + v->x;
      ((vec3*)r)->y = ((vec3*)u)->y + v->y;
      ((vec3*)r)->z = ((vec3*)u)->z + v->z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddVecToBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const vec3*   v,
			   const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + vd.x;
      ((vec3*)r)->y = ((vec3*)u)->y + vd.y;
      ((vec3*)r)->z = ((vec3*)u)->z + vd.z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3AddBlockToBlockStd(vec3* ru,const vec3* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x += v[i].x;
      ru[i].y += v[i].y;
      ru[i].z += v[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3AddBlockToBlockBySizeStd(void*         ru,
				  const void*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x += ((vec3*)v)->x;
      ((vec3*)ru)->y += ((vec3*)v)->y;
      ((vec3*)ru)->z += ((vec3*)v)->z;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddBlockToBufStd(void*         r,
			     const void*   u,
			     const void*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y + ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z + ((vec3*)v)->z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufAddBufToBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const void*   v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x + ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y + ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z + ((vec3*)v)->z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubtractStd(vec3*  r,const vec3* u,const vec3* v)
{
  uss_t us;

  r->x = u->x - v->x;
  r->y = u->y - v->y;
  r->z = u->z - v->z;

  ClearFpuStatusStd(&us);
}

void Vec3SubVecFromBlockStd(vec3* ru,const vec3* v,const int32_t nCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x -= vd.x;
      ru[i].y -= vd.y;
      ru[i].z -= vd.z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubVecFromBlockBySizeStd(void*         ru,
				  const vec3*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x -= vd.x;
      ((vec3*)ru)->y -= vd.y;
      ((vec3*)ru)->z -= vd.z;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubVecFromBlockStd(void*         r,
			       const void*   u,
			       const vec3*   v,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - vd.x;
      ((vec3*)r)->y = ((vec3*)u)->y - vd.y;
      ((vec3*)r)->z = ((vec3*)u)->z - vd.z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubVecFromBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const vec3*   v,
			     const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - vd.x;
      ((vec3*)r)->y = ((vec3*)u)->y - vd.y;
      ((vec3*)r)->z = ((vec3*)u)->z - vd.z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubBlockFromBlockStd(vec3* ru,const vec3* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x -= v[i].x;
      ru[i].y -= v[i].y;
      ru[i].z -= v[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3SubBlockFromBlockBySizeStd(void*         ru,
				    const void*   v,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x -= ((vec3*)v)->x;
      ((vec3*)ru)->y -= ((vec3*)v)->y;
      ((vec3*)ru)->z -= ((vec3*)v)->z;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubBlockFromBufStd(void*         r,
			       const void*   u,
			       const void*   v,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y - ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z - ((vec3*)v)->z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSubBufFromBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const void*   v,
			     const int32_t iVSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x - ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y - ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z - ((vec3*)v)->z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3MultiplyStd(vec3*  r,const vec3* u,const vec3* v)
{
  uss_t us;

  r->x = u->x * v->x;
  r->y = u->y * v->y;
  r->z = u->z * v->z;

  ClearFpuStatusStd(&us);
}

void Vec3MulBlockByVecStd(vec3* ru,const vec3* v,const int32_t nCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x *= vd.x;
      ru[i].y *= vd.y;
      ru[i].z *= vd.z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3MulBlockByVecUseSizeStd(void*         ru,
				 const vec3*   v,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x *= vd.x;
      ((vec3*)ru)->y *= vd.y;
      ((vec3*)ru)->z *= vd.z;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulBufByVecStd(void*         r,
			   const void*   u,
			   const vec3*   v,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * vd.x;
      ((vec3*)r)->y = ((vec3*)u)->y * vd.y;
      ((vec3*)r)->z = ((vec3*)u)->z * vd.z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulBufByVecUseSizeStd (void*         r,
				   const int32_t iRSize,
				   const void*   u,
				   const int32_t iUSize,
				   const vec3*   v,
				   const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * vd.x;
      ((vec3*)r)->y = ((vec3*)u)->y * vd.y;
      ((vec3*)r)->z = ((vec3*)u)->z * vd.z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3MulBlockByBlockStd(vec3* ru,const vec3* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= v[i].x;
      ru[i].y *= v[i].y;
      ru[i].z *= v[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3MulBlockByBlockUseSizeStd(void*         ru,
				   const void*   v,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x *= ((vec3*)v)->x;
      ((vec3*)ru)->y *= ((vec3*)v)->y;
      ((vec3*)ru)->z *= ((vec3*)v)->z;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulBufByBlockStd(void*  r,
			     const void* u,
			     const void* v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y * ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z * ((vec3*)v)->z;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufMulBufByBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const void*   v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * ((vec3*)v)->x;
      ((vec3*)r)->y = ((vec3*)u)->y * ((vec3*)v)->y;
      ((vec3*)r)->z = ((vec3*)u)->z * ((vec3*)v)->z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivideStd(vec3*  r,const vec3* u,const vec3* v)
{
  uss_t us;

  r->x = (0.0f == v->x ? 0.0f : u->x / v->x);
  r->y = (0.0f == v->y ? 0.0f : u->y / v->y);
  r->z = (0.0f == v->z ? 0.0f : u->z / v->z);

  ClearFpuStatusStd(&us);
}

void Vec3DivBlockByVecStd(vec3* ru,const vec3* v,const int32_t nCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x = (0.0f == vd.x ? 0.0f : ru[i].x / vd.x);
      ru[i].y = (0.0f == vd.y ? 0.0f : ru[i].y / vd.y);
      ru[i].z = (0.0f == vd.z ? 0.0f : ru[i].z / vd.z);
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivBlockByVecUseSizeStd(void* ru,
				 const vec3* v,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x = (0.0f == vd.x ? 0.0f : ((vec3*)ru)->x / vd.x);
      ((vec3*)ru)->y = (0.0f == vd.y ? 0.0f : ((vec3*)ru)->y / vd.y);
      ((vec3*)ru)->z = (0.0f == vd.z ? 0.0f : ((vec3*)ru)->z / vd.z);
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBufByVecStd(void*  r,
			   const void* u,
			   const vec3* v,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = (0.0f == vd.x ? 0.0f : ((vec3*)u)->x / vd.x);
      ((vec3*)r)->y = (0.0f == vd.y ? 0.0f : ((vec3*)u)->y / vd.y);
      ((vec3*)r)->z = (0.0f == vd.z ? 0.0f : ((vec3*)u)->z / vd.z);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBufByVecUseSizeStd (void*  r,
				   const int32_t iRSize,
				   const void* u,
				   const int32_t iUSize,
				   const vec3* v,
				   const int32_t iCount)
{
  int   i;
  vec3  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = (0.0f == vd.x ? 0.0f : ((vec3*)u)->x / vd.x);
      ((vec3*)r)->y = (0.0f == vd.y ? 0.0f : ((vec3*)u)->y / vd.y);
      ((vec3*)r)->z = (0.0f == vd.z ? 0.0f : ((vec3*)u)->z / vd.z);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivBlockByBlockStd(vec3* ru,const vec3* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != v[i].x && 0.0f != v[i].y && 0.0f != v[i].z )
	{
	  ru[i].x /= v[i].x;
	  ru[i].y /= v[i].y;
	  ru[i].z /= v[i].z;
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3DivBlockByBlockUseSizeStd(void*         ru,
				   const void*   v,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != ((vec3*)v)->x && 0.0f != ((vec3*)v)->y && 0.0f != ((vec3*)v)->z )
	{
	  ((vec3*)ru)->x /= ((vec3*)v)->x;
	  ((vec3*)ru)->y /= ((vec3*)v)->y;
	  ((vec3*)ru)->z /= ((vec3*)v)->z;
	  ru = (void*)((char*)ru + iSize);
	  v  = (void*)((char*)v  + iSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBufByBlockStd(void*         r,
			     const void*   u,
			     const void*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != ((vec3*)v)->x && 0.0f != ((vec3*)v)->y && 0.0f != ((vec3*)v)->z )
	{
	  ((vec3*)r)->x = ((vec3*)u)->x / ((vec3*)v)->x;
	  ((vec3*)r)->y = ((vec3*)u)->y / ((vec3*)v)->y;
	  ((vec3*)r)->z = ((vec3*)u)->z / ((vec3*)v)->z;
	  r = (void*)((char*)r + iSize);
	  u = (void*)((char*)u + iSize);
	  v = (void*)((char*)v + iSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDivBufByBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const void*   v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != ((vec3*)v)->x && 0.0f != ((vec3*)v)->y && 0.0f != ((vec3*)v)->z )
	{
	  ((vec3*)r)->x = ((vec3*)u)->x / ((vec3*)v)->x;
	  ((vec3*)r)->y = ((vec3*)u)->y / ((vec3*)v)->y;
	  ((vec3*)r)->z = ((vec3*)u)->z / ((vec3*)v)->z;
	  r = (void*)((char*)r + iRSize);
	  u = (void*)((char*)u + iUSize);
	  v = (void*)((char*)v + iVSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3LerpStd(vec3*  r,const vec3* u,const vec3* v,const float s)
{
  uss_t us;
  float fStep = 1.0f - s;

  r->x = u->x * fStep + v->x * s;
  r->y = u->y * fStep + v->y * s;
  r->z = u->z * fStep + v->z * s;

  ClearFpuStatusStd(&us);
}

void Vec3LerpBlockStd(vec3* ru,const vec3* v,const float s,const int32_t iCount)
{
  int   i;
  float fStep = 1.0f - s;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = ru[i].x * fStep + v[i].x * s;
      ru[i].y = ru[i].y * fStep + v[i].y * s;
      ru[i].z = ru[i].z * fStep + v[i].z * s;
    }
  ClearFpuStatusStd(&us);
}

void Vec3LerpBlockUseSizeStd(void*         ru,
			     const void*   v,
			     const float   s,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int   i;
  float fStep = 1.0f - s;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x = ((vec3*)ru)->x * fStep + ((vec3*)v)->x * s;
      ((vec3*)ru)->y = ((vec3*)ru)->y * fStep + ((vec3*)v)->y * s;
      ((vec3*)ru)->z = ((vec3*)ru)->z * fStep + ((vec3*)v)->z * s;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufLerpBlockStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const vec3*   v,
			 const float   s,
			 const int32_t iCount)
{
  int   i;
  float fStep = 1.0f - s;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * fStep + v[i].x * s;
      ((vec3*)r)->y = ((vec3*)u)->y * fStep + v[i].y * s;
      ((vec3*)r)->z = ((vec3*)u)->z * fStep + v[i].z * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufLerpBufStd(void* r,
		       const int32_t iRSize,
		       const void* u,
		       const int32_t iUSize,
		       const void* v,
		       const int32_t iVSize,
		       const float s,
		       const int32_t iCount)
{
  int   i;
  float fStep = 1.0f - s;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * fStep + ((vec3*)v)->x * s;
      ((vec3*)r)->y = ((vec3*)u)->y * fStep + ((vec3*)v)->y * s;
      ((vec3*)r)->z = ((vec3*)u)->z * fStep + ((vec3*)v)->z * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3DotStd(float* r,const vec3* u,const vec3* v)
{
  uss_t us;

  *r = u->x*v->x + u->y*v->y + u->z*v->z;

  ClearFpuStatusStd(&us);
}

void Vec3DotBlockStd(float* r,const vec3* u,const vec3* v,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r )
    {
      *r = u[i].x*v[i].x + u[i].y*v[i].y + u[i].z*v[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3DotBlockUseSizeStd(float*        r,
			    const void*   u,
			    const void*   v,
			    const int32_t iSize,
			    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r )
    {
      *r = ((vec3*)u)->x*((vec3*)v)->x +
	   ((vec3*)u)->y*((vec3*)v)->y +
	   ((vec3*)u)->z*((vec3*)v)->z;

      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufDotBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const void*   v,
		      const int32_t iVSize,
		      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      *((float*)r) = ((vec3*)u)->x*((vec3*)v)->x +
	             ((vec3*)u)->y*((vec3*)v)->y +
	             ((vec3*)u)->z*((vec3*)v)->z;

      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SqrStd(vec3*  r,const vec3* v)
{
  uss_t us;

  r->x = v->x * v->x;
  r->y = v->y * v->y;
  r->z = v->z * v->z;

  ClearFpuStatusStd(&us);
}

void Vec3SqrBlockStd(vec3* ru,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= ru[i].x;
      ru[i].y *= ru[i].y;
      ru[i].z *= ru[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Vec3SqrBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x *= ((vec3*)ru)->x;
      ((vec3*)ru)->y *= ((vec3*)ru)->y;
      ((vec3*)ru)->z *= ((vec3*)ru)->z;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSqrBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = ((vec3*)u)->x * ((vec3*)u)->x;
      ((vec3*)r)->y = ((vec3*)u)->y * ((vec3*)u)->y;
      ((vec3*)r)->z = ((vec3*)u)->z * ((vec3*)u)->z;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SqrtStd(vec3*  r,const vec3* v)
{
  uss_t us;

  r->x = (float)sqrt(v->x);
  r->y = (float)sqrt(v->y);
  r->z = (float)sqrt(v->z);

  ClearFpuStatusStd(&us);
}

void Vec3SqrtBlockStd(vec3* ru,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = (float)sqrt(ru[i].x);
      ru[i].y = (float)sqrt(ru[i].y);
      ru[i].z = (float)sqrt(ru[i].z);
    }
  ClearFpuStatusStd(&us);
}

void Vec3SqrtBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)ru)->x = (float)sqrt(((vec3*)ru)->x);
      ((vec3*)ru)->y = (float)sqrt(((vec3*)ru)->y);
      ((vec3*)ru)->z = (float)sqrt(((vec3*)ru)->z);
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufSqrtBufStd(void*         r,
		       const int32_t iRSize,
		       const void*   u,
		       const int32_t iUSize,
		       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = (float)sqrt(((vec3*)u)->x);
      ((vec3*)r)->y = (float)sqrt(((vec3*)u)->y);
      ((vec3*)r)->z = (float)sqrt(((vec3*)u)->z);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3NormalizeStd(vec3*  r,const vec3* u)
{
  uss_t us;
  double fBase = sqrt(u->x*u->x + u->y*u->y + u->z*u->z);

  if ( 0.0f == fBase )
    {
      r->x = 0.0f;
      r->y = 0.0f;
      r->z = 0.0f;
    }
  else
    {
      r->x = (float)(u->x / fBase);
      r->y = (float)(u->y / fBase);
      r->z = (float)(u->z / fBase);
    }
  r->n = 0.0f;
  ClearFpuStatusStd(&us);
}

void Vec3NormalizeBlockStd(vec3* ru,const int32_t iCount)
{
  int   i;
  float fBase;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != (fBase=(float)sqrt(ru[i].x*ru[i].x + ru[i].y*ru[i].y + ru[i].z*ru[i].z)) )
	{
	  ru[i].x /= fBase;
	  ru[i].y /= fBase;
	  ru[i].z /= fBase;
	  ru[i].n  = 0.0f;
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3NormalizeBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int   i;
  float fBase;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != (fBase=(float)sqrt(((vec3*)ru)->x*((vec3*)ru)->x +
			              ((vec3*)ru)->y*((vec3*)ru)->y +
			              ((vec3*)ru)->z*((vec3*)ru)->z)) )
	{
	  ((vec3*)ru)->x /= fBase;
	  ((vec3*)ru)->y /= fBase;
	  ((vec3*)ru)->z /= fBase;
	}
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufNormalizeBufStd(void*          r,
			    const int32_t iRSize,
			    const void*    u,
			    const int32_t iUSize,
			    const int32_t iCount)
{
  int    i;
  double fBase;
  uss_t  us;

  for( i=0 ; i < iCount ; ++i )
    {
      if ( 0.0f != (fBase=sqrt(((vec3*)u)->x*((vec3*)u)->x +
			       ((vec3*)u)->y*((vec3*)u)->y +
			       ((vec3*)u)->z*((vec3*)u)->z)) )
	{
	  ((vec3*)r)->x = (float)(((vec3*)u)->x / fBase);
	  ((vec3*)r)->y = (float)(((vec3*)u)->y / fBase);
	  ((vec3*)r)->z = (float)(((vec3*)u)->z / fBase);
	  r = (void*)((char*)r + iRSize);
	  u = (void*)((char*)u + iUSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec3LengthStd(float* r,const vec3* v)
{
  uss_t us;

  *r = (float)sqrt(v->x*v->x + v->y*v->y + v->z*v->z);

  ClearFpuStatusStd(&us);
}

void Vec3LengthBlockStd(float* r,const vec3* u,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r )
    {
      *r = (float)sqrt(u[i].x*u[i].x + u[i].y*u[i].y + u[i].z*u[i].z);
    }
  ClearFpuStatusStd(&us);
}

void Vec3LengthBlockUseSizeStd(float*        r,
			       const void*   u,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r )
    {
      *r = (float)sqrt(((vec3*)u)->x*((vec3*)u)->x +
		       ((vec3*)u)->y*((vec3*)u)->y +
		       ((vec3*)u)->z*((vec3*)u)->z);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufLengthBufStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      *((float*)r) = (float)sqrt(((vec3*)u)->x*((vec3*)u)->x +
			         ((vec3*)u)->y*((vec3*)u)->y +
			         ((vec3*)u)->z*((vec3*)u)->z);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3CrossStd(vec3*  r,const vec3* u,const vec3* v)
{
  uss_t us;
  vec3  ud = *u;
  vec3  vd = *v;

  r->x = ud.y * vd.z - ud.z * vd.y;
  r->y = ud.z * vd.x - ud.x * vd.z;
  r->z = ud.x * vd.y - ud.y * vd.x;

  ClearFpuStatusStd(&us);
}

void Vec3CrossBlockStd(vec3* ru,const vec3* v,const int32_t iCount)
{
  int   i;
  vec3  rd;
  vec3  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rd = ru[i];
      vd = v[i];

      ru[i].x = rd.y * vd.z - rd.z * vd.y;
      ru[i].y = rd.z * vd.x - rd.x * vd.z;
      ru[i].z = rd.x * vd.y - rd.y * vd.x;
    }
  ClearFpuStatusStd(&us);
}

void Vec3CrossBlockUseSizeStd(void*         ru,
			      const void*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  vec3* rp;
  vec3  rd;
  vec3  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rp = (vec3*)ru;
      rd = *rp;
      vd = *((vec3*)v);
      
      rp->x = rd.y * vd.z - rd.z * vd.y;
      rp->y = rd.z * vd.x - rd.x * vd.z;
      rp->z = rd.x * vd.y - rd.y * vd.x;

      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec3BufCrossBufStd(void*         r,
			const int32_t iRSize,
			const void*   u,
			const int32_t iUSize,
			const void*   v,
			const int32_t iVSize,
			const int32_t iCount)
{
  int   i;
  vec3* rp;
  vec3  ud;
  vec3  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rp = (vec3*)r;
      ud = *((vec3*)u);
      vd = *((vec3*)v);

      rp->x = ud.y * vd.z - ud.z * vd.y;
      rp->y = ud.z * vd.x - ud.x * vd.z;
      rp->z = ud.x * vd.y - ud.y * vd.x;

      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

// XXX: This needs a little more work

void Vec3ReflectStd(vec3* r,const vec3* u,const vec3* v)
{
  float dotuv;
  vec3  uNorm;
  vec3  vNorm;
  vec3  negv;
  uss_t us;

  // Normalize u and v
  //

  Vec3NormalizeStd(&uNorm,u);
  Vec3NormalizeStd(&vNorm,v);

  // delta = 2.0f * dot(u,v)
  //

  Vec3DotStd(&dotuv,&uNorm,&vNorm);
  dotuv *= 2.0f;

  // Calculate negative v (reflectance axis
  //

  Vec3NegateStd(&negv,&vNorm);

  // Calculate the reflected point
  //

  r->x = u->x * dotuv + negv.x;
  r->y = u->y * dotuv + negv.y;
  r->z = u->z * dotuv + negv.z;

  ClearFpuStatusStd(&us);
}

// Fundamental 4-Dimensional Vector Scalar Methods 
//

void Vec4CopyStd(vec4* pDest,const vec4* pSource)
{
  memcpy((void*)pDest,(void*)pSource,sizeof(vec4));
}

void Vec4CopyBlockStd(vec4* pDest,const vec4* pSource,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)&pDest[i],(void*)&pSource[i],sizeof(vec4));
    }
}

void BuildVec4PackedArrayStd(vec4* r,const vec4** pSrc,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      memcpy((void*)&r[i],(void*)pSrc[i],sizeof(vec4));
    }
}

void Vec4AddFloatStd(vec4*  r,const vec4* u,const float s)
{
  uss_t us;

  r->x = u->x + s;
  r->y = u->y + s;
  r->z = u->z + s;
  r->w = u->w + s;

  ClearFpuStatusStd(&us);
}

void Vec4AddFloatToBlockStd(vec4* rv,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv[i].x += s;
      rv[i].y += s;
      rv[i].z += s;
      rv[i].w += s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4AddFloatToBlockBySizeStd(void*         rv,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)rv)->x += s;
      ((vec4*)rv)->y += s;
      ((vec4*)rv)->z += s;
      ((vec4*)rv)->w += s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddFloatToBlockStd(void*       r,
			       const void* u,
			       const float s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + s;
      ((vec4*)r)->y = ((vec4*)u)->y + s;
      ((vec4*)r)->z = ((vec4*)u)->z + s;
      ((vec4*)r)->w = ((vec4*)u)->w + s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddFloatToBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + s;
      ((vec4*)r)->y = ((vec4*)u)->y + s;
      ((vec4*)r)->z = ((vec4*)u)->z + s;
      ((vec4*)r)->w = ((vec4*)u)->w + s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubtractFloatStd(vec4*  r,const vec4* u,const float s)
{
  uss_t us;

  r->x = u->x - s;
  r->y = u->y - s;
  r->z = u->z - s;
  r->w = u->w - s;

  ClearFpuStatusStd(&us);
}

void Vec4SubtractFloatFromBlockStd(vec4* rv,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rv[i].x -= s;
      rv[i].y -= s;
      rv[i].z -= s;
      rv[i].w -= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubFloatFromBlockBySizeStd(void*         rv,
				    const float   s,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)rv)->x -= s;
      ((vec4*)rv)->y -= s;
      ((vec4*)rv)->z -= s;
      ((vec4*)rv)->w -= s;
      rv = (void*)((char*)rv + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubFloatFromBlockStd(void*         r,
				 const void*   u,
				 const float   s,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - s;
      ((vec4*)r)->y = ((vec4*)u)->y - s;
      ((vec4*)r)->z = ((vec4*)u)->z - s;
      ((vec4*)r)->w = ((vec4*)u)->w - s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubFloatFromBufStd(void*         r,
			       const int32_t iRSize,
			       const void*   u,
			       const int32_t iUSize,
			       const float   s,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - s;
      ((vec4*)r)->y = ((vec4*)u)->y - s;
      ((vec4*)r)->z = ((vec4*)u)->z - s;
      ((vec4*)r)->w = ((vec4*)u)->w - s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4MultiplyFloatStd(vec4*  r,const vec4* u,const float s)
{
  uss_t us;

  r->x = u->x * s;
  r->y = u->y * s;
  r->z = u->z * s;
  r->w = u->w * s;

  ClearFpuStatusStd(&us);
}

void Vec4MultiplyFloatToBlockStd(vec4* ru,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= s;
      ru[i].y *= s;
      ru[i].z *= s;
      ru[i].w *= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4MulFloatToBlockBySizeStd(void*         ru,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x *= s;
      ((vec4*)ru)->y *= s;
      ((vec4*)ru)->z *= s;
      ((vec4*)ru)->w *= s;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulFloatToBlockStd(void*         r,
			       const void*   u,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * s;
      ((vec4*)r)->y = ((vec4*)u)->y * s;
      ((vec4*)r)->z = ((vec4*)u)->z * s;
      ((vec4*)r)->w = ((vec4*)u)->w * s;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulFloatToBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * s;
      ((vec4*)r)->y = ((vec4*)u)->y * s;
      ((vec4*)r)->z = ((vec4*)u)->z * s;
      ((vec4*)r)->w = ((vec4*)u)->w * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivideFloatStd(vec4*  r,const vec4* u,const float s)
{
  uss_t us;

  if ( 0.0f == s )
    {
      r->x = 0.0f;
      r->y = 0.0f;
      r->z = 0.0f;
      r->w = 0.0f;
    }
  else
    {
      r->x = u->x / s;
      r->y = u->y / s;
      r->z = u->z / s;
      r->w = u->w / s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivideBlockByFloatStd(vec4* ru,const float s,const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x /= s;
      ru[i].y /= s;
      ru[i].z /= s;
      ru[i].w /= s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivBlockByFloatBySizeStd(void*         ru,
				  const float   s,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s ) return;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x /= s;
      ((vec4*)ru)->y /= s;
      ((vec4*)ru)->z /= s;
      ((vec4*)ru)->w /= s;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBlockByFloatStd(void*         r,
			       const void*   u,
			       const float   s,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s )
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec4*)r)->x = 0.0f;
	  ((vec4*)r)->y = 0.0f;
	  ((vec4*)r)->z = 0.0f;
	  ((vec4*)r)->w = 0.0f;
	  r = (void*)((char*)r + iSize);
	}
    }
  else
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec4*)r)->x = ((vec4*)u)->x / s;
	  ((vec4*)r)->y = ((vec4*)u)->y / s;
	  ((vec4*)r)->z = ((vec4*)u)->z / s;
	  ((vec4*)r)->w = ((vec4*)u)->w / s;
	  r = (void*)((char*)r + iSize);
	  u = (void*)((char*)u + iSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBufByFloatStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const float   s,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  if ( 0.0f == s )
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec4*)r)->x = 0.0f;
	  ((vec4*)r)->y = 0.0f;
	  ((vec4*)r)->z = 0.0f;
	  ((vec4*)r)->w = 0.0f;
	  r = (void*)((char*)r + iRSize);
	}
    }
  else
    {
      for( i=0 ; i < iCount ; ++i )
	{
	  ((vec4*)r)->x = ((vec4*)u)->x / s;
	  ((vec4*)r)->y = ((vec4*)u)->y / s;
	  ((vec4*)r)->z = ((vec4*)u)->z / s;
	  ((vec4*)r)->w = ((vec4*)u)->w / s;
	  r = (void*)((char*)r + iRSize);
	  u = (void*)((char*)u + iUSize);
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec4EqualsStd(int32_t* iFlag,const vec4* u,const vec4* v)
{
  *iFlag = (int32_t)(u->x == v->x && u->y == v->y && u->z == v->z && u->w == v->w);
}

void Vec4NotEqualsStd(int32_t* iFlag,const vec4* u,const vec4* v)
{
  *iFlag = (int32_t)(u->x != v->x || u->y != v->y || u->z != v->z || u->w != v->w);
}

void Vec4NegateStd(vec4*  r,const vec4* v)
{
  r->x = -(v->x);
  r->y = -(v->y);
  r->z = -(v->z);
  r->w = -(v->w);
}

void Vec4NegateBlockStd(vec4* ru,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = -ru[i].x;
      ru[i].y = -ru[i].y;
      ru[i].z = -ru[i].z;
      ru[i].w = -ru[i].w;
    }
}

void Vec4NegateBlockBySizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x = -(((vec4*)ru)->x);
      ((vec4*)ru)->y = -(((vec4*)ru)->y);
      ((vec4*)ru)->z = -(((vec4*)ru)->z);
      ((vec4*)ru)->w = -(((vec4*)ru)->w);
      ru = (void*)((char*)ru + iSize);
    }
}

void Vec4BufNegateBlockStd(void*  r,
			   const void* u,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = -(((vec4*)u)->x);
      ((vec4*)r)->y = -(((vec4*)u)->y);
      ((vec4*)r)->z = -(((vec4*)u)->z);
      ((vec4*)r)->w = -(((vec4*)u)->w);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
}

void Vec4BufNegateBufStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const int32_t iCount)
{
  int i;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = -(((vec4*)u)->x);
      ((vec4*)r)->y = -(((vec4*)u)->y);
      ((vec4*)r)->z = -(((vec4*)u)->z);
      ((vec4*)r)->w = -(((vec4*)u)->w);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }  
}

void Vec4AddStd(vec4*  r,const vec4* u,const vec4* v)
{
  uss_t us;

  r->x = u->x + v->x;
  r->y = u->y + v->y;
  r->z = u->z + v->z;
  r->w = u->w + v->w;

  ClearFpuStatusStd(&us);
}

void Vec4AddVecToBlockStd(vec4* ru,const vec4* v,const int32_t nCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x += vd.x;
      ru[i].y += vd.y;
      ru[i].z += vd.z;
      ru[i].w += vd.w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4AddVecToBlockBySizeStd(void*         ru,
				const vec4*   v,
				const int32_t iSize,
				const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x += vd.x;
      ((vec4*)ru)->y += vd.y;
      ((vec4*)ru)->z += vd.z;
      ((vec4*)ru)->w += vd.w;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddVecToBlockStd(void*         r,
			     const void*   u,
			     const vec4*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y + vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z + vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w + vd.w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddVecToBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const vec4*   v,
			   const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y + vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z + vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w + vd.w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4AddBlockToBlockStd(vec4*         ru,
			    const vec4*   v,
			    const int32_t iCount)
{
  int  i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x += v[i].x;
      ru[i].y += v[i].y;
      ru[i].z += v[i].z;
      ru[i].w += v[i].w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4AddBlockToBlockBySizeStd(void*         ru,
				  const void*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x += ((vec4*)v)->x;
      ((vec4*)ru)->y += ((vec4*)v)->y;
      ((vec4*)ru)->z += ((vec4*)v)->z;
      ((vec4*)ru)->w += ((vec4*)v)->w;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddBlockToBufStd(void*         r,
			     const void*   u,
			     const void*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y + ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z + ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w + ((vec4*)v)->w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufAddBufToBufStd(void*  r,
			   const int32_t iRSize,
			   const void* u,
			   const int32_t iUSize,
			   const void* v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x + ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y + ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z + ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w + ((vec4*)v)->w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubtractStd(vec4*  r,const vec4* u,const vec4* v)
{
  uss_t us;

  r->x = u->x - v->x;
  r->y = u->y - v->y;
  r->z = u->z - v->z;
  r->w = u->w - v->w;

  ClearFpuStatusStd(&us);
}

void Vec4SubVecFromBlockStd(vec4* ru,const vec4* v,const int32_t nCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x -= vd.x;
      ru[i].y -= vd.y;
      ru[i].z -= vd.z;
      ru[i].w -= vd.w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubVecFromBlockBySizeStd(void*         ru,
				  const vec4*   v,
				  const int32_t iSize,
				  const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x -= vd.x;
      ((vec4*)ru)->y -= vd.y;
      ((vec4*)ru)->z -= vd.z;
      ((vec4*)ru)->w -= vd.w;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubVecFromBlockStd(void*         r,
			       const void*   u,
			       const vec4*   v,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y - vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z - vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w - vd.w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubVecFromBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const vec4*   v,
			     const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y - vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z - vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w - vd.w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubBlockFromBlockStd(vec4* ru,const vec4* v,const int32_t iCount)
{
  int  i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x -= v[i].x;
      ru[i].y -= v[i].y;
      ru[i].z -= v[i].z;
      ru[i].w -= v[i].w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4SubBlockFromBlockBySizeStd(void*         ru,
				    const void*   v,
				    const int32_t iSize,
				    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x -= ((vec4*)v)->x;
      ((vec4*)ru)->y -= ((vec4*)v)->y;
      ((vec4*)ru)->z -= ((vec4*)v)->z;
      ((vec4*)ru)->w -= ((vec4*)v)->w;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubBlockFromBufStd(void*         r,
			       const void*   u,
			       const void*   v,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y - ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z - ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w - ((vec4*)v)->w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSubBufFromBufStd(void*         r,
			     const int32_t iRSize,
			     const void*   u,
			     const int32_t iUSize,
			     const void*   v,
			     const int32_t iVSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x - ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y - ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z - ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w - ((vec4*)v)->w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4MultiplyStd(vec4*  r,const vec4* u,const vec4* v)
{
  uss_t us;

  r->x = u->x * v->x;
  r->y = u->y * v->y;
  r->z = u->z * v->z;
  r->w = u->w * v->w;

  ClearFpuStatusStd(&us);
}

void Vec4MulBlockByVecStd(vec4* ru,const vec4* v,const int32_t nCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x *= vd.x;
      ru[i].y *= vd.y;
      ru[i].z *= vd.z;
      ru[i].w *= vd.w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4MulBlockByVecUseSizeStd(void*         ru,
				 const vec4*   v,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x *= vd.x;
      ((vec4*)ru)->y *= vd.y;
      ((vec4*)ru)->z *= vd.z;
      ((vec4*)ru)->w *= vd.w;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulBufByVecStd(void*         r,
			   const void*   u,
			   const vec4*   v,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y * vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z * vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w * vd.w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulBufByVecUseSizeStd(void*         r,
				  const int32_t iRSize,
				  const void*   u,
				  const int32_t iUSize,
				  const vec4*   v,
				  const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * vd.x;
      ((vec4*)r)->y = ((vec4*)u)->y * vd.y;
      ((vec4*)r)->z = ((vec4*)u)->z * vd.z;
      ((vec4*)r)->w = ((vec4*)u)->w * vd.w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4MulBlockByBlockStd(vec4* ru,const vec4* v,const int32_t iCount)
{
  int  i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= v[i].x;
      ru[i].y *= v[i].y;
      ru[i].z *= v[i].z;
      ru[i].w *= v[i].w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4MulBlockByBlockUseSizeStd(void*         ru,
				   const void*   v,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x *= ((vec4*)v)->x;
      ((vec4*)ru)->y *= ((vec4*)v)->y;
      ((vec4*)ru)->z *= ((vec4*)v)->z;
      ((vec4*)ru)->w *= ((vec4*)v)->w;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulBufByBlockStd(void*         r,
			     const void*   u,
			     const void*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y * ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z * ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w * ((vec4*)v)->w;
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufMulBufByBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const void*   v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * ((vec4*)v)->x;
      ((vec4*)r)->y = ((vec4*)u)->y * ((vec4*)v)->y;
      ((vec4*)r)->z = ((vec4*)u)->z * ((vec4*)v)->z;
      ((vec4*)r)->w = ((vec4*)u)->w * ((vec4*)v)->w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivideStd(vec4*  r,const vec4* u,const vec4* v)
{
  uss_t us;

  r->x = (0.0f == v->x ? 0.0f : u->x / v->x);
  r->y = (0.0f == v->y ? 0.0f : u->y / v->y);
  r->z = (0.0f == v->z ? 0.0f : u->z / v->z);
  r->w = (0.0f == v->w ? 0.0f : u->w / v->w);

  ClearFpuStatusStd(&us);
}

void Vec4DivBlockByVecStd(vec4* ru,const vec4* v,const int32_t nCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      ru[i].x = (0.0f == vd.x ? 0.0f : ru[i].x / vd.x);
      ru[i].y = (0.0f == vd.y ? 0.0f : ru[i].y / vd.y);
      ru[i].z = (0.0f == vd.z ? 0.0f : ru[i].z / vd.z);
      ru[i].w = (0.0f == vd.w ? 0.0f : ru[i].w / vd.w);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivBlockByVecUseSizeStd(void*         ru,
				 const vec4*   v,
				 const int32_t iSize,
				 const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x = (0.0f == vd.x ? 0.0f : ((vec4*)ru)->x / vd.x);
      ((vec4*)ru)->y = (0.0f == vd.y ? 0.0f : ((vec4*)ru)->y / vd.y);
      ((vec4*)ru)->z = (0.0f == vd.z ? 0.0f : ((vec4*)ru)->z / vd.z);
      ((vec4*)ru)->w = (0.0f == vd.w ? 0.0f : ((vec4*)ru)->w / vd.w);
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBufByVecStd(void*         r,
			   const void*   u,
			   const vec4*   v,
			   const int32_t iSize,
			   const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = (0.0f == vd.x ? 0.0f : ((vec4*)u)->x / vd.x);
      ((vec4*)r)->y = (0.0f == vd.y ? 0.0f : ((vec4*)u)->y / vd.y);
      ((vec4*)r)->z = (0.0f == vd.z ? 0.0f : ((vec4*)u)->z / vd.z);
      ((vec4*)r)->w = (0.0f == vd.w ? 0.0f : ((vec4*)u)->w / vd.w);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBufByVecUseSizeStd (void*         r,
				   const int32_t iRSize,
				   const void*   u,
				   const int32_t iUSize,
				   const vec4*   v,
				   const int32_t iCount)
{
  int   i;
  vec4  vd = *v;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = (0.0f == vd.x ? 0.0f : ((vec4*)u)->x / vd.x);
      ((vec4*)r)->y = (0.0f == vd.y ? 0.0f : ((vec4*)u)->y / vd.y);
      ((vec4*)r)->z = (0.0f == vd.z ? 0.0f : ((vec4*)u)->z / vd.z);
      ((vec4*)r)->w = (0.0f == vd.w ? 0.0f : ((vec4*)u)->w / vd.w);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivBlockByBlockStd(vec4* ru,const vec4* v,const int32_t iCount)
{
  int   i;
  vec4  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      vd = v[i];
      ru[i].x = (0.0f == vd.x ? 0.0f : ru[i].x / vd.x);
      ru[i].y = (0.0f == vd.y ? 0.0f : ru[i].y / vd.y);
      ru[i].z = (0.0f == vd.z ? 0.0f : ru[i].z / vd.z);
      ru[i].w = (0.0f == vd.w ? 0.0f : ru[i].w / vd.w);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DivBlockByBlockUseSizeStd(void*         ru,
				   const void*   v,
				   const int32_t iSize,
				   const int32_t iCount)
{
  int   i;
  vec4  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      vd = *((vec4*)v);
      ((vec4*)ru)->x = (0.0f == vd.x ? 0.0f : ((vec4*)ru)->x / vd.x);
      ((vec4*)ru)->y = (0.0f == vd.y ? 0.0f : ((vec4*)ru)->y / vd.y);
      ((vec4*)ru)->z = (0.0f == vd.z ? 0.0f : ((vec4*)ru)->z / vd.z);
      ((vec4*)ru)->w = (0.0f == vd.w ? 0.0f : ((vec4*)ru)->w / vd.w);
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBufByBlockStd(void*         r,
			     const void*   u,
			     const void*   v,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int   i;
  vec4  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      vd = *((vec4*)v);
      ((vec4*)r)->x = (0.0f == vd.x ? 0.0f : ((vec4*)u)->x / vd.x);
      ((vec4*)r)->y = (0.0f == vd.y ? 0.0f : ((vec4*)u)->y / vd.y);
      ((vec4*)r)->z = (0.0f == vd.z ? 0.0f : ((vec4*)u)->z / vd.z);
      ((vec4*)r)->w = (0.0f == vd.w ? 0.0f : ((vec4*)u)->w / vd.w);
      r = (void*)((char*)r + iSize);
      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDivBufByBufStd(void*         r,
			   const int32_t iRSize,
			   const void*   u,
			   const int32_t iUSize,
			   const void*   v,
			   const int32_t iVSize,
			   const int32_t iCount)
{
  int   i;
  vec4  vd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      vd = *((vec4*)v);
      ((vec4*)r)->x = (0.0f == vd.x ? 0.0f : ((vec4*)u)->x / vd.x);
      ((vec4*)r)->y = (0.0f == vd.y ? 0.0f : ((vec4*)u)->y / vd.y);
      ((vec4*)r)->z = (0.0f == vd.z ? 0.0f : ((vec4*)u)->z / vd.z);
      ((vec4*)r)->w = (0.0f == vd.w ? 0.0f : ((vec4*)u)->w / vd.w);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4LerpStd(vec4*  r,const vec4* u,const vec4* v,const float s)
{
  uss_t us;
  float fStep = 1.0f - s;

  r->x = u->x * fStep + v->x * s;
  r->y = u->y * fStep + v->y * s;
  r->z = u->z * fStep + v->z * s;
  r->w = u->w * fStep + v->w * s;

  ClearFpuStatusStd(&us);
}

void Vec4LerpBlockStd(vec4* ru,const vec4* v,const float s,const int32_t iCount)
{
  int   i;
  uss_t us;
  float fStep = 1.0f - s;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = ru[i].x * fStep + v[i].x * s;
      ru[i].y = ru[i].y * fStep + v[i].y * s;
      ru[i].z = ru[i].z * fStep + v[i].z * s;
      ru[i].w = ru[i].w * fStep + v[i].w * s;
    }
  ClearFpuStatusStd(&us);
}

void Vec4LerpBlockUseSizeStd(void*         ru,
			     const void*   v,
			     const float   s,
			     const int32_t iSize,
			     const int32_t iCount)
{
  int   i;
  uss_t us;
  float fStep = 1.0f - s;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x = ((vec4*)ru)->x * fStep + ((vec4*)v)->x * s;
      ((vec4*)ru)->y = ((vec4*)ru)->y * fStep + ((vec4*)v)->y * s;
      ((vec4*)ru)->z = ((vec4*)ru)->z * fStep + ((vec4*)v)->z * s;
      ((vec4*)ru)->w = ((vec4*)ru)->w * fStep + ((vec4*)v)->w * s;
      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufLerpBlockStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const vec4*   v,
			 const float   s,
			 const int32_t iCount)
{
  int   i;
  uss_t us;
  float fStep = 1.0f - s;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * fStep + v[i].x * s;
      ((vec4*)r)->y = ((vec4*)u)->y * fStep + v[i].y * s;
      ((vec4*)r)->z = ((vec4*)u)->z * fStep + v[i].z * s;
      ((vec4*)r)->w = ((vec4*)u)->w * fStep + v[i].w * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufLerpBufStd(void*         r,
		       const int32_t iRSize,
		       const void*   u,
		       const int32_t iUSize,
		       const void*   v,
		       const int32_t iVSize,
		       const float   s,
		       const int32_t iCount)
{
  int   i;
  uss_t us;
  float fStep = 1.0f - s;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * fStep + ((vec4*)v)->x * s;
      ((vec4*)r)->y = ((vec4*)u)->y * fStep + ((vec4*)v)->y * s;
      ((vec4*)r)->z = ((vec4*)u)->z * fStep + ((vec4*)v)->z * s;
      ((vec4*)r)->w = ((vec4*)u)->w * fStep + ((vec4*)v)->w * s;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4DotStd(float* r,const vec4* u,const vec4* v)
{
  uss_t us;

  *r = u->x*v->x + u->y*v->y + u->z*v->z + u->w*v->w;

  ClearFpuStatusStd(&us);
}

void Vec4DotBlockStd(float* r,const vec4* u,const vec4* v,const int32_t iCount)
{
  int i;
  uss_t us;
  
  for( i=0 ; i < iCount ; ++i )
    {
      r[i] = u[i].x*v[i].x + u[i].y*v[i].y + u[i].z*v[i].z + u[i].w*v[i].w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4DotBlockUseSizeStd(float*        r,
			    const void*   u,
			    const void*   v,
			    const int32_t iSize,
			    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      r[i] =
	((vec4*)u)->x*((vec4*)v)->x +
	((vec4*)u)->y*((vec4*)v)->y +
	((vec4*)u)->z*((vec4*)v)->z +
	((vec4*)u)->w*((vec4*)v)->w;

      u = (void*)((char*)u + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufDotBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const void*   v,
		      const int32_t iVSize,
		      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      *((float*)r) =
	((vec4*)u)->x*((vec4*)v)->x +
	((vec4*)u)->y*((vec4*)v)->y +
	((vec4*)u)->z*((vec4*)v)->z +
	((vec4*)u)->w*((vec4*)v)->w;

      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SqrStd(vec4*  r,const vec4* v)
{
  uss_t us;

  r->x = v->x * v->x;
  r->y = v->y * v->y;
  r->z = v->z * v->z;
  r->w = v->w * v->w;

  ClearFpuStatusStd(&us);
}

void Vec4SqrBlockStd(vec4* ru,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x *= ru[i].x;
      ru[i].y *= ru[i].y;
      ru[i].z *= ru[i].z;
      ru[i].w *= ru[i].w;
    }
  ClearFpuStatusStd(&us);
}

void Vec4SqrBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x *= ((vec4*)ru)->x;
      ((vec4*)ru)->y *= ((vec4*)ru)->y;
      ((vec4*)ru)->z *= ((vec4*)ru)->z;
      ((vec4*)ru)->w *= ((vec4*)ru)->w;
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSqrBufStd(void*         r,
		      const int32_t iRSize,
		      const void*   u,
		      const int32_t iUSize,
		      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = ((vec4*)u)->x * ((vec4*)u)->x;
      ((vec4*)r)->y = ((vec4*)u)->y * ((vec4*)u)->y;
      ((vec4*)r)->z = ((vec4*)u)->z * ((vec4*)u)->z;
      ((vec4*)r)->w = ((vec4*)u)->w * ((vec4*)u)->w;
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SqrtStd(vec4*  r,const vec4* v)
{
  uss_t us;

  r->x = (float)sqrt(v->x);
  r->y = (float)sqrt(v->y);
  r->z = (float)sqrt(v->z);
  r->w = (float)sqrt(v->w);

  ClearFpuStatusStd(&us);
}

void Vec4SqrtBlockStd(vec4* ru,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ru[i].x = (float)sqrt(ru[i].x);
      ru[i].y = (float)sqrt(ru[i].y);
      ru[i].z = (float)sqrt(ru[i].z);
      ru[i].w = (float)sqrt(ru[i].w);
    }
  ClearFpuStatusStd(&us);
}

void Vec4SqrtBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)ru)->x = (float)sqrt(((vec4*)ru)->x);
      ((vec4*)ru)->y = (float)sqrt(((vec4*)ru)->y);
      ((vec4*)ru)->z = (float)sqrt(((vec4*)ru)->z);
      ((vec4*)ru)->w = (float)sqrt(((vec4*)ru)->w);
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufSqrtBufStd(void*         r,
		       const int32_t iRSize,
		       const void*   u,
		       const int32_t iUSize,
		       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec4*)r)->x = (float)sqrt(((vec4*)u)->x);
      ((vec4*)r)->y = (float)sqrt(((vec4*)u)->y);
      ((vec4*)r)->z = (float)sqrt(((vec4*)u)->z);
      ((vec4*)r)->w = (float)sqrt(((vec4*)u)->w);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4NormalizeStd(vec4*  r,const vec4* u)
{
  uss_t  us;
  double fBase = sqrt(u->x*u->x + u->y*u->y + u->z*u->z + u->w*u->w);

  if ( 0.0f == fBase )
    {
      r->x = 0.0f;
      r->y = 0.0f;
      r->z = 0.0f;
      r->w = 0.0f;
    }
  else
    {
      r->x = (float)(u->x / fBase);
      r->y = (float)(u->y / fBase);
      r->z = (float)(u->z / fBase);
      r->w = (float)(u->w / fBase);
    }
  ClearFpuStatusStd(&us);
}

void Vec4NormalizeBlockStd(vec4* ru,const int32_t iCount)
{
  int   i;
  float fBase;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      fBase = (float)sqrt(ru[i].x*ru[i].x + ru[i].y*ru[i].y + ru[i].z*ru[i].z + ru[i].w*ru[i].w);
      if ( 0.0f == fBase )
	{
	  ru[i].x = 0.0f;
	  ru[i].y = 0.0f;
	  ru[i].z = 0.0f;
	  ru[i].w = 0.0f;
	}
      else
	{
	  ru[i].x /= fBase;
	  ru[i].y /= fBase;
	  ru[i].z /= fBase;
	  ru[i].w /= fBase;
	}
    }
  ClearFpuStatusStd(&us);
}

void Vec4NormalizeBlockUseSizeStd(vec4* ru,const int32_t iSize,const int32_t iCount)
{
  int   i;
  float fBase;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      fBase = (float)sqrt(((vec4*)ru)->x*((vec4*)ru)->x +
		          ((vec4*)ru)->y*((vec4*)ru)->y +
		          ((vec4*)ru)->z*((vec4*)ru)->z +
		          ((vec4*)ru)->w*((vec4*)ru)->w);
      if ( 0.0f == fBase )
	{
	  ((vec4*)ru)->x = 0.0f;
	  ((vec4*)ru)->y = 0.0f;
	  ((vec4*)ru)->z = 0.0f;
	  ((vec4*)ru)->w = 0.0f;
	}
      else
	{
	  ((vec4*)ru)->x /= fBase;
	  ((vec4*)ru)->y /= fBase;
	  ((vec4*)ru)->z /= fBase;
	  ((vec4*)ru)->w /= fBase;
	}
      ru = (void*)((char*)ru + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufNormalizeBufStd(void*         r,
			    const int32_t iRSize,
			    const void*   u,
			    const int32_t iUSize,
			    const int32_t iCount)
{
  int    i;
  double fBase;
  uss_t  us;

  for( i=0 ; i < iCount ; ++i )
    {
      fBase = sqrt(((vec4*)u)->x*((vec4*)u)->x +
		   ((vec4*)u)->y*((vec4*)u)->y +
		   ((vec4*)u)->z*((vec4*)u)->z +
		   ((vec4*)u)->w*((vec4*)u)->w);

      if ( 0.0f == fBase )
	{
	  ((vec4*)r)->x = 0.0f;
	  ((vec4*)r)->y = 0.0f;
	  ((vec4*)r)->z = 0.0f;
	  ((vec4*)r)->w = 0.0f;
	}
      else
	{
	  ((vec4*)r)->x = (float)(((vec4*)u)->x / fBase);
	  ((vec4*)r)->y = (float)(((vec4*)u)->y / fBase);
	  ((vec4*)r)->z = (float)(((vec4*)u)->z / fBase);
	  ((vec4*)r)->w = (float)(((vec4*)u)->w / fBase);
	}
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4LengthStd(float* r,const vec4* v)
{
  uss_t us;

  *r = (float)sqrt(v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w);

  ClearFpuStatusStd(&us);
}

void Vec4LengthBlockStd(float* r,const vec4* u,const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      r[i] = (float)sqrt(u[i].x*u[i].x + u[i].y*u[i].y + u[i].z*u[i].z + u[i].w*u[i].w);
    }
  ClearFpuStatusStd(&us);
}

void Vec4LengthBlockUseSizeStd(float*        r,
			       const void*   u,
			       const int32_t iSize,
			       const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i,++r )
    {
      *r = (float)sqrt(((vec4*)u)->x*((vec4*)u)->x +
		       ((vec4*)u)->y*((vec4*)u)->y +
		       ((vec4*)u)->z*((vec4*)u)->z +
		       ((vec4*)u)->w*((vec4*)u)->w);
      u = (void*)((char*)u + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufLengthBufStd(void*         r,
			 const int32_t iRSize,
			 const void*   u,
			 const int32_t iUSize,
			 const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      *((float*)r) = (float)sqrt(((vec4*)u)->x*((vec4*)u)->x +
			         ((vec4*)u)->y*((vec4*)u)->y +
			         ((vec4*)u)->z*((vec4*)u)->z +
			         ((vec4*)u)->w*((vec4*)u)->w);
      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4CrossStd(vec4*  r,const vec4* u,const vec4* v)
{
  uss_t us;
  vec4  ud = *u;
  vec4  vd = *v;

  r->x = ud.y * vd.z - ud.z * vd.y;
  r->y = ud.z * vd.x - ud.x * vd.z;
  r->z = ud.x * vd.y - ud.y * vd.x;
  r->w = 0.0f;

  ClearFpuStatusStd(&us);
}

void Vec4CrossBlockStd(vec4* ru,const vec4* v,const int32_t iCount)
{
  int   i;
  vec4  rd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rd.x = ru[i].y * v[i].z - ru[i].z * v[i].y;
      rd.y = ru[i].z * v[i].x - ru[i].x * v[i].z;
      rd.z = ru[i].x * v[i].y - ru[i].y * v[i].x;
      rd.w = 0.0f;

      ru[i] = rd;
    }
  ClearFpuStatusStd(&us);
}

void Vec4CrossBlockUseSizeStd(void*         ru,
			      const void*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int   i;
  vec4  rd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rd.x = ((vec4*)ru)->y * ((vec4*)v)->z - ((vec4*)ru)->z * ((vec4*)v)->y;
      rd.y = ((vec4*)ru)->z * ((vec4*)v)->x - ((vec4*)ru)->x * ((vec4*)v)->z;
      rd.z = ((vec4*)ru)->x * ((vec4*)v)->y - ((vec4*)ru)->y * ((vec4*)v)->x;
      rd.w = 0.0f;

      *((vec4*)ru) = rd;

      ru = (void*)((char*)ru + iSize);
      v  = (void*)((char*)v  + iSize);
    }
  ClearFpuStatusStd(&us);
}

void Vec4BufCrossBufStd(void* r,
			const int32_t iRSize,
			const void* u,
			const int32_t iUSize,
			const void* v,
			const int32_t iVSize,
			const int32_t iCount)
{
  int   i;
  vec4  rd;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      rd.x = ((vec4*)u)->y * ((vec4*)v)->z - ((vec4*)u)->z * ((vec4*)v)->y;
      rd.y = ((vec4*)u)->z * ((vec4*)v)->x - ((vec4*)u)->x * ((vec4*)v)->z;
      rd.z = ((vec4*)u)->x * ((vec4*)v)->y - ((vec4*)u)->y * ((vec4*)v)->x;
      rd.w = 0.0f;

      *((vec4*)r) = rd;

      r = (void*)((char*)r + iRSize);
      u = (void*)((char*)u + iUSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

mat2 m2Ident = {
  1.0f, 0.0f,
  0.0f, 1.0f
};

static int mat2Size = sizeof(mat2)/sizeof(float);

void Mat2IdentityStd(mat2*  r)
{
  memcpy((void*)r,(void*)&m2Ident,sizeof(mat2));
}

void Mat2NegateStd(mat2*  r,const mat2* m)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* fp = (float*)m;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = -fp[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat2AddStd(mat2*  r,const mat2* m,const mat2* n)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = mp[i] + np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat2AddFloatStd(mat2*  r,const mat2* m,const float s)
{
  int    i;
  uss_t  us;
  float *rp = (float*)r;
  float *mp = (float*)m;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = mp[i] + s;
    }
  ClearFpuStatusStd(&us);
}

void Mat2SubtractStd(mat2*  r,const mat2* m,const mat2* n)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = mp[i] - np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat2SubtractFloatStd(mat2*  r,const mat2* m,const float s)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = mp[i] - s;
    }
  ClearFpuStatusStd(&us);
}

void Mat2MultiplyStd(mat2*  r,const mat2* m,const mat2* n)
{
  uss_t us;

  r->m00 = m->m00 * n->m00 + m->m01 * n->m10;
  r->m01 = m->m00 * n->m01 + m->m01 * n->m11;
  r->m10 = m->m10 * n->m00 + m->m11 * n->m10;
  r->m11 = m->m10 * n->m01 + m->m11 * n->m11;

  ClearFpuStatusStd(&us);
}

void Mat2MultiplyVecStd(vec2*  r,const mat2* m,const vec2* v)
{
  uss_t us;

  r->x = m->m00 * v->x + m->m01 * v->y;
  r->y = m->m10 * v->x + m->m11 * v->y;

  ClearFpuStatusStd(&us);
}

void Mat2MultiplyFloatStd(mat2*  r,const mat2* m,const float s)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat2Size ; ++i )
    {
      rp[i] = mp[i] * s;
    }
  ClearFpuStatusStd(&us);
}
    
void Mat2TransposeStd(mat2*  r,const mat2* m)
{
  float ft0 = m->m01;

  r->m00 = m->m00;
  r->m01 = m->m10;
  r->m10 = ft0;
  r->m11 = m->m11;
}

void Mat2RotateLHStd(mat2* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = sinAngle;
  r->m10 = -sinAngle;
  r->m11 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat2RotateRHStd(mat2* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = -sinAngle;
  r->m10 = sinAngle;
  r->m11 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat2RotateStd(mat2*  r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = -sinAngle;
  r->m10 = sinAngle;
  r->m11 = cosAngle;

  ClearFpuStatusStd(&us);
}

// XXX: This change needs to be integrated into the header
//

#if 0
#define Mat2RotateRH Mat2RotateStd

void Mat2RotateLHStd(mat2* r,const float angle)
{
  float cosAngle = cos(angle);
  float sinAngle = sin(angle);

  r->m00 = cosAngle;
  r->m01 = sinAngle;
  r->m10 = -sinAngle;
  r->m11 = cosAngle;
}
#endif
  
void Mat2ScaleStd(mat2*  r,const float x_scale,const float y_scale)
{
  r->m00 = x_scale;
  r->m01 = 0.0f;
  r->m10 = 0.0f;
  r->m11 = y_scale;
}

void Mat2MultiplyVecBlockStd(vec2*  r,const mat2* m,const vec2* v,const int32_t nCount)
{
  int    i;
  uss_t  us;

  for( i=0 ; i < nCount ; ++i )
    {
      r[i].x = m->m00 * v[i].x + m->m01 * v[i].y;
      r[i].y = m->m10 * v[i].x + m->m11 * v[i].y;
    }
  ClearFpuStatusStd(&us);
}

// Mat3Operations

void Mat3CopyStd(mat3* r,const mat3* m)
{
  memcpy((void*)r,(void*)m,sizeof(mat3));
}

vec3 v3Id0 = { 1.0f, 0.0f, 0.0f };
vec3 v3Id1 = { 0.0f, 1.0f, 0.0f };
vec3 v3Id2 = { 0.0f, 0.0f, 1.0f };

void Mat3IdentityStd(mat3* r)
{
  memcpy((void*)&r->m00,(void*)&v3Id0,sizeof(vec3));
  memcpy((void*)&r->m10,(void*)&v3Id1,sizeof(vec3));
  memcpy((void*)&r->m20,(void*)&v3Id2,sizeof(vec3));
}

static int mat3Size = sizeof(mat3)/sizeof(float);

void Mat3NegateStd(mat3* r,const mat3* m)
{
  int i;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = -mp[i];
    }

  r->n03 =
  r->n13 =
  r->n23 = 0.0f;
}

void Mat3AddStd(mat3* r,const mat3* m,const mat3* n)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = mp[i] + np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat3AddFloatStd(mat3* r,const mat3* m,const float s)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = mp[i] + s;
    }

  r->n03 =
  r->n13 =
  r->n23 = 0.0f;

  ClearFpuStatusStd(&us);
}

void Mat3SubtractStd(mat3* r,const mat3* m,const mat3* n)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = mp[i] - np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat3SubtractFloatStd(mat3* r,const mat3* m,const float s)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = mp[i] - s;
    }

  r->n03 =
  r->n13 =
  r->n23 = 0.0f;

  ClearFpuStatusStd(&us);
}

void Mat3MultiplyStd(mat3* r,const mat3* m,const mat3* n)
{
  int i,j;
  uss_t  us;
  float *rp,*mp,*col;

  int ipr  = sizeof(mat3) / (3*sizeof(float));
  int ipr2 = 2*ipr;

  for( i=0 ; i < 3 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)r) + offs;
      mp  = ((float*)m) + offs;
      col = (float*)n;

      for( j=0 ; j < 3 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)     +
	    *(mp+1) * *(col+ipr) +
	    *(mp+2) * *(col+ipr2);
	}
    }
  ClearFpuStatusStd(&us);
}

void Mat3MultiplyIdentityByBlocksStd(mat3* r,const mat3** m,int32_t nCount)
{
  int  i;
  mat3 mb;

  Mat3IdentityStd(r);

  for( i=0 ; i < nCount ; ++i )
    {
      mb = *r;
      Mat3MultiplyStd(r,&mb,m[i]);
    }
}

void Mat3MultiplyVecStd(vec3* r,const mat3* m,const vec3* v)
{
  uss_t us;

  r->x = m->m00 * v->x + m->m01 * v->y + m->m02 * v->z;
  r->y = m->m10 * v->x + m->m11 * v->y + m->m12 * v->z;
  r->z = m->m20 * v->x + m->m21 * v->y + m->m22 * v->z;

  ClearFpuStatusStd(&us);
}

void Mat3MultiplyVecBlockStd(vec3* r,const mat3* m,const vec3* v,int32_t nCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < nCount ; ++i )
    {
      r[i].x = m->m00 * v[i].x + m->m01 * v[i].y + m->m02 * v[i].z;
      r[i].y = m->m10 * v[i].x + m->m11 * v[i].y + m->m12 * v[i].z;
      r[i].z = m->m20 * v[i].x + m->m21 * v[i].y + m->m22 * v[i].z;
    }
  ClearFpuStatusStd(&us);
}

void Mat3MulVecBlockBySizeStd(void*         r,
			      const mat3*   m,
			      const void*   v,
			      const int32_t iSize,
			      const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = m->m00 * ((vec3*)v)->x + m->m01 * ((vec3*)v)->y + m->m02 * ((vec3*)v)->z;
      ((vec3*)r)->y = m->m10 * ((vec3*)v)->x + m->m11 * ((vec3*)v)->y + m->m12 * ((vec3*)v)->z;
      ((vec3*)r)->z = m->m20 * ((vec3*)v)->x + m->m21 * ((vec3*)v)->y + m->m22 * ((vec3*)v)->z;
      r = (void*)((char*)r + iSize);
      v = (void*)((char*)v + iSize);
    }
  ClearFpuStatusStd(&us);
}
  
void Mat3MulVec3BufByBufStd(void*         r,
			    const int32_t iRSize,
			    const mat3*   m,
			    const void*   v,
			    const int32_t iVSize,
			    const int32_t iCount)
{
  int i;
  uss_t us;

  for( i=0 ; i < iCount ; ++i )
    {
      ((vec3*)r)->x = m->m00 * ((vec3*)v)->x + m->m01 * ((vec3*)v)->y + m->m02 * ((vec3*)v)->z;
      ((vec3*)r)->y = m->m10 * ((vec3*)v)->x + m->m11 * ((vec3*)v)->y + m->m12 * ((vec3*)v)->z;
      ((vec3*)r)->z = m->m20 * ((vec3*)v)->x + m->m21 * ((vec3*)v)->y + m->m22 * ((vec3*)v)->z;
      r = (void*)((char*)r + iRSize);
      v = (void*)((char*)v + iVSize);
    }
  ClearFpuStatusStd(&us);
}

void Mat3MultiplyFloatStd(mat3* r,const mat3* m,const float x)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] = mp[i] * x;
    }
  ClearFpuStatusStd(&us);
}

void Mat3InverseStd(mat3* r,const mat3* m)
{
  int    i;
  uss_t  us;
  float  det;
  float  inverse;
  float* rp = (float*)r;
  float  a0 = m->m11 * m->m22 - m->m21 * m->m12;
  float  a1 = m->m12 * m->m20 - m->m10 * m->m22;
  float  a2 = m->m10 * m->m21 - m->m11 * m->m20;

  if ( 0.0f == (det=m->m00 * a0 + m->m01 * a1 + m->m02 * a2) )
    {
      int i;
      float* fp = (float*)r;
      for( i=0 ; i < sizeof(mat3) ; ++i ) *fp++ = 0.0f;
      ClearFpuStatusStd(&us);
      return;
    }

  inverse = 1.0f / det;

  r->m00 = a0;
  r->m01 = m->m21 * m->m02 - m->m01 * m->m22;
  r->m02 = m->m01 * m->m12 - m->m11 * m->m02;

  r->m10 = a1;
  r->m11 = m->m00 * m->m22 - m->m20 * m->m02;
  r->m12 = m->m10 * m->m02 - m->m00 * m->m12;

  r->m20 = a2;
  r->m21 = m->m20 * m->m01 - m->m00 * m->m21;
  r->m22 = m->m00 * m->m11 - m->m01 * m->m10;

  for( i=0 ; i < mat3Size ; ++i )
    {
      rp[i] *= inverse;
    }
  ClearFpuStatusStd(&us);
}

void Mat3TransposeStd(mat3* r,const mat3*m)
{
  float ft0 = m->m01;
  float ft1 = m->m02;
  float ft2 = m->m12;

  r->m00 = m->m00;
  r->m01 = m->m10;
  r->m02 = m->m20;
  r->n03 = 0.0f;

  r->m10 = ft0;
  r->m11 = m->m11;
  r->m12 = m->m21;
  r->n13 = 0.0f;

  r->m20 = ft1;
  r->m21 = ft2;
  r->m22 = m->m22;
  r->n23 = 0.0f;
}

void Mat3RotateRHX_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = cosAngle;
  r->m12 = -sinAngle;

  r->m20 = 0.0f;
  r->m21 = sinAngle;
  r->m22 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHX_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = cosAngle;
  r->m12 = sinAngle;

  r->m20 = 0.0f;
  r->m21 = -sinAngle;
  r->m22 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHY_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = 0.0f;
  r->m02 = sinAngle;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;

  r->m20 = -sinAngle;
  r->m21 = 0.0f;
  r->m22 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHY_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = 0.0f;
  r->m02 = -sinAngle;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;

  r->m20 = sinAngle;
  r->m21 = 0.0f;
  r->m22 = cosAngle;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHZ_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = -sinAngle;
  r->m02 = 0.0f;

  r->m10 = sinAngle;
  r->m11 = cosAngle;
  r->m12 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHZ_Std(mat3* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = sinAngle;
  r->m02 = 0.0f;

  r->m10 = -sinAngle;
  r->m11 = cosAngle;
  r->m12 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHXY_Std(mat3* r,const float x_angle,const float y_angle)
{
  uss_t us;
  float cosx = (float)cos(x_angle);
  float sinx = (float)sin(x_angle);
  float cosy = (float)cos(y_angle);
  float siny = (float)sin(y_angle);

  r->m00 = cosy;
  r->m01 = 0.0f;
  r->m02 = siny;

  r->m10 = sinx * siny;
  r->m11 = cosx;
  r->m12 = -sinx * cosy;

  r->m20 = -siny * cosx;
  r->m21 = sinx;
  r->m22 = cosx * cosy;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHXY_Std(mat3* r,const float x_angle,const float y_angle)
{
  uss_t us;
  float cosX = (float)cos(x_angle);
  float sinX = (float)sin(x_angle);
  float cosY = (float)cos(y_angle);
  float sinY = (float)sin(y_angle);

  r->m00 = cosY;
  r->m01 = 0.0f;
  r->m02 = -sinY;

  r->m10 = sinX * sinY;
  r->m11 = cosX;
  r->m12 = sinX * cosY;

  r->m20 = cosX * sinY;
  r->m21 = -sinX;
  r->m22 = cosX * cosY;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHXZ_Std(mat3* r,const float x_angle,const float z_angle)
{
  uss_t us;
  float cosX = (float)cos(x_angle);
  float sinX = (float)sin(x_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosZ;
  r->m01 = -sinZ;
  r->m02 = 0.0f;

  r->m10 = cosX * sinZ;
  r->m11 = cosX * cosZ;
  r->m12 = -sinX;

  r->m20 = sinX * sinZ;
  r->m21 = sinX * cosZ;
  r->m22 = cosX;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHXZ_Std(mat3* r,const float x_angle,const float z_angle)
{
  uss_t us;
  float cosX = (float)cos(x_angle);
  float sinX = (float)sin(x_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosZ;
  r->m01 = sinZ;
  r->m02 = 0.0f;

  r->m10 = -sinZ * cosX;
  r->m11 = cosX * cosZ;
  r->m12 = sinX;

  r->m20 = sinX * sinZ;
  r->m21 = -sinX * cosZ;
  r->m22 = cosX;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHYZ_Std(mat3* r,const float y_angle,const float z_angle)
{
  uss_t us;
  float cosY = (float)cos(y_angle);
  float sinY = (float)sin(y_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosY * cosZ;
  r->m01 = -sinZ * cosY;
  r->m02 = sinY;

  r->m10 = sinZ;
  r->m11 = cosZ;
  r->m12 = 0.0f;

  r->m20 = -sinY * cosZ;
  r->m21 = sinY * sinZ;
  r->m22 = cosY;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHYZ_Std(mat3* r,const float y_angle,const float z_angle)
{
  uss_t us;

  float cosY = (float)cos(y_angle);
  float sinY = (float)sin(y_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosY * cosZ;
  r->m01 = cosY * sinZ;
  r->m02 = -sinY;

  r->m10 = -sinZ;
  r->m11 = cosZ;
  r->m12 = 0.0f;

  r->m20 = sinY * cosZ;
  r->m21 = sinY * sinZ;
  r->m22 = cosY;

  ClearFpuStatusStd(&us);
}

void Mat3RotateRHXYZ_Std(mat3* r,const float x,const float y,const float z)
{
  uss_t us;
  float cosX = (float)cos(x);
  float sinX = (float)sin(x);
  float cosY = (float)cos(y);
  float sinY = (float)sin(y);
  float cosZ = (float)cos(z);
  float sinZ = (float)sin(z);

  r->m00 = cosY * cosZ;
  r->m01 = -sinZ * cosY;
  r->m02 = sinY;

  r->m10 = sinX * sinY * cosZ + cosX * sinZ;
  r->m11 = -sinZ * sinX * sinY + cosX * cosZ;
  r->m12 = -sinX * cosY;

  r->m20 = -sinY * cosX * cosZ + sinX * sinZ;
  r->m21 = cosX * sinY * sinZ + sinX * cosZ;
  r->m22 = cosX * cosY;

  ClearFpuStatusStd(&us);
}

void Mat3RotateLHXYZ_Std(mat3* r,const float x,const float y,const float z)
{
  uss_t us;

  float cosX = (float)cos(x);
  float sinX = (float)sin(x);
  float cosY = (float)cos(y);
  float sinY = (float)sin(y);
  float cosZ = (float)cos(z);
  float sinZ = (float)sin(z);

  r->m00 = cosY * cosZ;
  r->m01 = cosY * sinZ;
  r->m02 = -sinY;

  r->m10 = -sinZ * cosX + sinX * sinY * cosZ;
  r->m11 = sinX * sinY * sinZ + cosX * cosZ;
  r->m12 = sinX * cosY;

  r->m20 = cosX * sinY * cosZ + sinX * sinZ;
  r->m21 = -sinX * cosZ + cosX * sinY * sinZ;
  r->m22 = cosX * cosY;

  ClearFpuStatusStd(&us);
}

void Mat3ScaleStd(mat3* r,const float x_scale,const float y_scale,const float z_scale)
{
  r->m00 = x_scale;
  r->m01 = 0.0f;
  r->m02 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = y_scale;
  r->m12 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = z_scale;
}

void Mat3ScaleByVec3Std(mat3* r,const vec3* v)
{
  r->m00 = v->x;
  r->m01 =
  r->m02 = 0.0f;

  r->m10 =
  r->m12 = 0.0f;
  r->m11 = v->y;

  r->m20 =
  r->m21 = 0.0f;
  r->m22 = v->z;
}

// Mat4 Operations

void Mat4CopyStd(mat4* r,const mat4* m)
{
  memcpy((void*)r,(void*)m,sizeof(mat4));
}

mat4 mat4Ident = {
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f };

int mat4Size = sizeof(mat4)/sizeof(float);

void Mat4IdentityStd(mat4* r)
{
  memcpy((void*)r,(void*)&mat4Ident.m00,sizeof(mat4));
}

void Mat4NegateStd(mat4* r,const mat4* m)
{
  int i;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = -(mp[i]);
    }
}

void Mat4NegateMatrixStd(mat4* r)
{
  int i;
  float* rp = (float*)r;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = -rp[i];
    }
}

void Mat4AddStd(mat4* r,const mat4* m,const mat4* n)
{
  int i;
  uss_t  us;
  float* rp = (float*)r;
  float* np = (float*)n;
  float* mp = (float*)m;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = mp[i] + np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat4AddFloatStd(mat4* r,const mat4* m,const float s)
{
  int i;
  uss_t  us;
  float *rp = (float*)r;
  float *mp = (float*)m;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = mp[i] + s;
    }
  ClearFpuStatusStd(&us);
}

void Mat4AddMatrixStd(mat4* m,const mat4* n)
{
  int i;
  uss_t  us;
  float* rp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] += np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat4SubtractStd(mat4* r,const mat4* m,const mat4* n)
{
  int i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = mp[i] - np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat4SubtractFloatStd(mat4* r,const mat4* m,const float s)
{
  int i;
  uss_t  us;
  float* rp = (float*)r;
  float *mp = (float*)m;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = mp[i] - s;
    }
  ClearFpuStatusStd(&us);
}

void Mat4SubtractMatrixStd(mat4* m,const mat4* n)
{
  int i;
  uss_t  us;
  float* rp = (float*)m;
  float* np = (float*)n;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] -= np[i];
    }
  ClearFpuStatusStd(&us);
}

void Mat4MultiplyStd(mat4* r,const mat4* m,const mat4* n)
{
  int   i,j;
  uss_t  us;
  float *rp,*mp,*col;

  int ipr  = sizeof(mat4) / (4*sizeof(float));
  int ipr2 = 2*ipr;
  int ipr3 = 3*ipr;

  for( i=0 ; i < 4 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)r)  + offs;
      mp  = ((float*)m) + offs;
      col = (float*)n;

      for( j=0 ; j < 4 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)      +
	    *(mp+1) * *(col+ipr)  +
	    *(mp+2) * *(col+ipr2) +
	    *(mp+3) * *(col+ipr3) ;
	}
    }
  ClearFpuStatusStd(&us);
}

void MatMultiply4x4Std(mat4* r,const mat4* m,const mat4* n)
{
  int    i,j;
  uss_t  us;
  float *rp,*mp,*col;

  int ipr  = sizeof(mat4) / (4*sizeof(float));
  int ipr2 = 2*ipr;
  int ipr3 = 3*ipr;

  for( i=0 ; i < 4 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)r) + offs;
      mp  = ((float*)m) + offs;
      col = (float*)n;

      for( j=0 ; j < 4 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)      +
	    *(mp+1) * *(col+ipr)  +
	    *(mp+2) * *(col+ipr2) +
	    *(mp+3) * *(col+ipr3) ;
	}
    }
  ClearFpuStatusStd(&us);
}


void MatMultiply4x4MatrixStd(const mat4* m,const mat4* n)
{
  int   i,j;
  uss_t us;
  mat4  r;

  float *rp,*mp,*col;

  int ipr  = sizeof(mat4) / (4*sizeof(float));
  int ipr2 = 2*ipr;
  int ipr3 = 3*ipr;

  for( i=0 ; i < 4 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)&r) + offs;
      mp  = ((float*)m) + offs;
      col = (float*)n;

      for( j=0 ; j < 4 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)      +
	    *(mp+1) * *(col+ipr)  +
	    *(mp+2) * *(col+ipr2) +
	    *(mp+3) * *(col+ipr3) ;
	}
    }
  memcpy((void*)m,(void*)&r,sizeof(mat4));
  ClearFpuStatusStd(&us);
}

void MatMultiplyVec4x4Std(vec4* r,const mat4* m,const vec4* v)
{
  uss_t us;

  r->x = m->m00 * v->x + m->m01 * v->y + m->m02 * v->z + m->m03 * v->w;
  r->y = m->m10 * v->x + m->m11 * v->y + m->m12 * v->z + m->m13 * v->w;
  r->z = m->m20 * v->x + m->m21 * v->y + m->m22 * v->z + m->m23 * v->w;
  r->w = m->m30 * v->x + m->m31 * v->y + m->m32 * v->z + m->m33 * v->w;

  ClearFpuStatusStd(&us);
}

void Mat4MultiplyVecStd(vec4* r,const mat4* m,const vec4* v)
{
  uss_t us;

  r->x = m->m00 * v->x + m->m01 * v->y + m->m02 * v->z + m->m03 * v->w;
  r->y = m->m10 * v->x + m->m11 * v->y + m->m12 * v->z + m->m13 * v->w;
  r->z = m->m20 * v->x + m->m21 * v->y + m->m22 * v->z + m->m23 * v->w;
  r->w = m->m30 * v->x + m->m31 * v->y + m->m32 * v->z + m->m33 * v->w;

  ClearFpuStatusStd(&us);
}

void Mat4MultiplyFloatStd(mat4* r,const mat4* m,const float x)
{
  int    i;
  uss_t  us;
  float* rp = (float*)r;
  float* mp = (float*)m;

  for( i=0 ; i < mat4Size ; ++i )
    {
      rp[i] = mp[i] * x;
    }
  ClearFpuStatusStd(&us);
}

void Mat4TransposeStd(mat4* r,const mat4* m)
{
  float ft0 = m->m01;
  float ft1 = m->m02;
  float ft2 = m->m03;

  float ft3 = m->m12;
  float ft4 = m->m13;

  float ft5 = m->m23;

  r->m00 = m->m00;
  r->m01 = m->m10;
  r->m02 = m->m20;
  r->m03 = m->m30;

  r->m10 = ft0;
  r->m11 = m->m11;
  r->m12 = m->m21;
  r->m13 = m->m31;

  r->m20 = ft1;
  r->m21 = ft3;
  r->m22 = m->m22;
  r->m23 = m->m32;

  r->m30 = ft2;
  r->m31 = ft4;
  r->m32 = ft5;
  r->m33 = m->m33;
}

void Mat4ScaleStd(mat4* r,const float x_scale,const float y_scale,const float z_scale)
{
  r->m00 = x_scale;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = y_scale;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = z_scale;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;
}

void Mat4RotateRHX_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = cosAngle;
  r->m12 = -sinAngle;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = sinAngle;
  r->m22 = cosAngle;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHX_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = cosAngle;
  r->m12 = sinAngle;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = -sinAngle;
  r->m22 = cosAngle;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHY_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = 0.0f;
  r->m02 = sinAngle;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = -sinAngle;
  r->m21 = 0.0f;
  r->m22 = cosAngle;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHY_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = 0.0f;
  r->m02 = -sinAngle;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = sinAngle;
  r->m21 = 0.0f;
  r->m22 = cosAngle;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHZ_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = -sinAngle;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = sinAngle;
  r->m11 = cosAngle;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHZ_Std(mat4* r,const float angle)
{
  uss_t us;
  float cosAngle = (float)cos(angle);
  float sinAngle = (float)sin(angle);

  r->m00 = cosAngle;
  r->m01 = sinAngle;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = -sinAngle;
  r->m11 = cosAngle;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHXY_Std(mat4* r,const float x_angle,const float y_angle)
{
  uss_t us;
  float cosx = (float)cos(x_angle);
  float sinx = (float)sin(x_angle);
  float cosy = (float)cos(y_angle);
  float siny = (float)sin(y_angle);

  r->m00 = cosy;
  r->m01 = 0.0f;
  r->m02 = siny;
  r->m03 = 0.0f;

  r->m10 = sinx * siny;
  r->m11 = cosx;
  r->m12 = -sinx * cosy;
  r->m13 = 0.0f;

  r->m20 = -siny * cosx;
  r->m21 = sinx;
  r->m22 = cosx * cosy;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHXY_Std(mat4* r,const float x_angle,const float y_angle)
{
  uss_t us;
  float cosx = (float)cos(x_angle);
  float sinx = (float)sin(x_angle);
  float cosy = (float)cos(y_angle);
  float siny = (float)sin(y_angle);

  r->m00 = cosy;
  r->m01 = 0.0f;
  r->m02 = -siny;
  r->m03 = 0.0f;

  r->m10 = sinx * siny;
  r->m11 = cosx;
  r->m12 = sinx * cosy;
  r->m13 = 0.0f;

  r->m20 = cosx * siny;
  r->m21 = -sinx;
  r->m22 = cosx * cosy;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHXZ_Std(mat4* r,const float x_angle,const float z_angle)
{
  uss_t us;
  float cosX = (float)cos(x_angle);
  float sinX = (float)sin(x_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosZ;
  r->m01 = -sinZ;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = cosX * sinZ;
  r->m11 = cosX * cosZ;
  r->m12 = -sinX;
  r->m13 = 0.0f;

  r->m20 = sinX * sinZ;
  r->m21 = sinX * cosZ;
  r->m22 = cosX;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHXZ_Std(mat4* r,const float x_angle,const float z_angle)
{
  uss_t us;
  float cosX = (float)cos(x_angle);
  float sinX = (float)sin(x_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosZ;
  r->m01 = sinZ;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = -sinZ * cosX;
  r->m11 = cosX * cosZ;
  r->m12 = sinX;
  r->m13 = 0.0f;

  r->m20 = sinX * sinZ;
  r->m21 = -sinX * cosZ;
  r->m22 = cosX;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHYZ_Std(mat4* r,const float y_angle,const float z_angle)
{
  uss_t us;
  float cosY = (float)cos(y_angle);
  float sinY = (float)sin(y_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosY * cosZ;
  r->m01 = -sinZ * cosY;
  r->m02 = sinY;
  r->m03 = 0.0f;

  r->m10 = sinZ;
  r->m11 = cosZ;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = -sinY * cosZ;
  r->m21 = sinY * sinZ;
  r->m22 = cosY;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHYZ_Std(mat4* r,const float y_angle,const float z_angle)
{
  uss_t us;
  float cosY = (float)cos(y_angle);
  float sinY = (float)sin(y_angle);
  float cosZ = (float)cos(z_angle);
  float sinZ = (float)sin(z_angle);

  r->m00 = cosY * cosZ;
  r->m01 = cosY * sinZ;
  r->m02 = -sinY;
  r->m03 = 0.0f;

  r->m10 = -sinZ;
  r->m11 = cosZ;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = sinY * cosZ;
  r->m21 = sinY * sinZ;
  r->m22 = cosY;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateRHXYZ_Std(mat4* r,const float x,const float y,const float z)
{
  uss_t us;
  float cosX = (float)cos(x);
  float sinX = (float)sin(x);
  float cosY = (float)cos(y);
  float sinY = (float)sin(y);
  float cosZ = (float)cos(z);
  float sinZ = (float)sin(z);

  r->m00 = cosY * cosZ;
  r->m01 = -sinZ * cosY;
  r->m02 = sinY;
  r->m03 = 0.0f;

  r->m10 = sinX * sinY * cosZ + cosX * sinZ;
  r->m11 = -sinZ * sinX * sinY + cosX * cosZ;
  r->m12 = -sinX * cosY;
  r->m13 = 0.0f;

  r->m20 = -sinY * cosX * cosZ + sinX * sinZ;
  r->m21 = cosX * sinY * sinZ + sinX * cosZ;
  r->m22 = cosX * cosY;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4RotateLHXYZ_Std(mat4* r,const float x,const float y,const float z)
{
  uss_t us;
  float cosX = (float)cos(x);
  float sinX = (float)sin(x);
  float cosY = (float)cos(y);
  float sinY = (float)sin(y);
  float cosZ = (float)cos(z);
  float sinZ = (float)sin(z);

  r->m00 = cosY * cosZ;
  r->m01 = cosY * sinZ;
  r->m02 = -sinY;
  r->m03 = 0.0f;

  r->m10 = -sinZ * cosX + sinX * sinY * cosZ;
  r->m11 = sinX * sinY * sinZ + cosX * cosZ;
  r->m12 = sinX * cosY;
  r->m13 = 0.0f;

  r->m20 = cosX * sinY * cosZ + sinX * sinZ;
  r->m21 = -sinX * cosZ + cosX * sinY * sinZ;
  r->m22 = cosX * cosY;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4TranslateRH_Std(mat4* r,const float x,const float y,const float z)
{
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = x;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = y;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = z;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;
}

void Mat4TranslateLH_Std(mat4* r,const float x,const float y,const float z)
{
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = 0.0f;

  r->m30 = x;
  r->m31 = y;
  r->m32 = z;
  r->m33 = 1.0f;
}

void Mat4TranslateRH_Vec3Std(mat4* r,const vec3* v)
{  
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = v->x;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = v->y;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = v->z;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;
}

void Mat4TranslateLH_Vec3Std(mat4* r,const vec3* v)
{
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = 0.0f;

  r->m30 = v->x;
  r->m31 = v->y;
  r->m32 = v->z;
  r->m33 = 1.0f;
}

void Mat4TranslateRH_Vec4Std(mat4* r,const vec4* v)
{
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = v->x;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = v->y;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = v->z;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;
}

void Mat4TranslateLH_Vec4Std(mat4* r,const vec4* v)
{
  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = 1.0f;
  r->m23 = 0.0f;

  r->m30 = v->x;
  r->m31 = v->y;
  r->m32 = v->z;
  r->m33 = 1.0f;
}

void Mat4OrthoMatrixStd(mat4* r,
			const float left,
			const float right,
			const float top,
			const float bottom,
			const float z_near,
			const float z_far,
			const int32_t d3dFlag)
{
  uss_t us;
  float rl = right - left;
  float tb = top - bottom;
  float fn = z_far - z_near;

  r->m00 = 2.0f / rl;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = -(right+left)/rl;

  r->m10 = 0.0f;
  r->m11 = 2.0f / tb;
  r->m12 = 0.0f;
  r->m13 = -(top+bottom)/tb;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = -2.0f / fn;
  r->m23 = -(z_far + z_near) / fn;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  if (d3dFlag) {
    r->m22 = 0.5f * (r->m22 + r->m32);
    r->m23 = 0.5f * (r->m23 + r->m33);
  }
  ClearFpuStatusStd(&us);
}

void Mat4OrthoStructStd(mat4* r,const struct orthoMatrix* s)
{
  Mat4OrthoMatrixStd(r,
		     s->left,
		     s->right,
		     s->top,
		     s->bottom,
		     s->z_near,
		     s->z_far,
		     s->d3dtype);
}

void Mat4PerspectiveStd(mat4*          r,
			const float    fov,
			const float    width,
			const float    height,
			const float    z_near,
			const float    z_far,
			const uint32_t d3dflag)
{
  uss_t us;
  float w = (float)tan(0.5f * fov);
  float h = (w * height) / width;

  r->m00 = 1.0f / w;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f / h;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = (z_near + z_far) / (z_far - z_near);
  r->m23 = -(2.0f * z_far * z_near) / (z_far - z_near);

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 1.0f;
  r->m33 = 0.0f;

  if ( d3dflag )
    {
      r->m22 = 0.5f * (r->m22 + r->m32);
      r->m23 = 0.5f * (r->m23 + r->m33);
    }
  ClearFpuStatusStd(&us);
}

void Mat4PerspectiveXStd(mat4* r,const struct perspectiveMatrix* s)
{
  Mat4PerspectiveStd(r,
		     s->fov,
		     s->width,  s->height,
		     s->z_near, s->z_far,
		     s->d3dtype);
}

void Mat4ShadowMatrixStd(mat4*       r,
			 const vec3* planeNormal,
			 const float planeOffset,
			 const vec3* lightPos)
{
  uss_t us;
  float dist;

  Vec3DotStd(&dist,lightPos,planeNormal);
  dist += planeOffset;

  r->m00 = dist - lightPos->x * planeNormal->x;
  r->m01 =      - lightPos->x * planeNormal->y;
  r->m02 =      - lightPos->x * planeNormal->z;
  r->m03 =      - lightPos->x * planeOffset;

  r->m10 =      - lightPos->y * planeNormal->x;
  r->m11 = dist - lightPos->y * planeNormal->y;
  r->m12 =      - lightPos->y * planeNormal->z;
  r->m13 =      - lightPos->y * planeOffset;

  r->m20 =      - lightPos->z * planeNormal->x;
  r->m21 =      - lightPos->z * planeNormal->y;
  r->m22 = dist - lightPos->z * planeNormal->z;
  r->m23 =      - lightPos->z * planeOffset;

  r->m30 =      - planeNormal->x;
  r->m31 =      - planeNormal->y;
  r->m32 =      - planeNormal->z;
  r->m33 = dist - planeOffset;

  ClearFpuStatusStd(&us);
}

void Mat4MirrorMatrixStd(mat4* r,const vec3* planeNormal,const float planeOffset)
{
  uss_t us;

  r->m00 = 1 - 2 * planeNormal->x * planeNormal->x;
  r->m01 =   - 2 * planeNormal->x * planeNormal->y;
  r->m02 =   - 2 * planeNormal->x * planeNormal->z;
  r->m03 =   - 2 * planeNormal->x * planeOffset;

  r->m10 =   - 2 * planeNormal->y * planeNormal->x;
  r->m11 = 1 - 2 * planeNormal->y * planeNormal->y;
  r->m12 =   - 2 * planeNormal->y * planeNormal->z;
  r->m13 =   - 2 * planeNormal->y * planeOffset;

  r->m20 =   - 2 * planeNormal->z * planeNormal->x;
  r->m21 =   - 2 * planeNormal->z * planeNormal->y;
  r->m22 = 1 - 2 * planeNormal->z * planeNormal->z;
  r->m23 =   - 2 * planeNormal->z * planeOffset;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

mat4 face0 = { 0.0f, 0.0f, -1.0f, 0.0f,
	       0.0f, 1.0f,  0.0f, 0.0f,
	       1.0f, 0.0f,  0.0f, 0.0f,
	       0.0f, 0.0f,  0.0f, 1.0f };

mat4 face1 = { 0.0f, 0.0f,  1.0f, 0.0f,
	       0.0f, 1.0f,  0.0f, 0.0f,
	      -1.0f, 0.0f,  0.0f, 0.0f,
	       0.0f, 0.0f,  0.0f, 1.0f };

mat4 face2 = { 1.0f, 0.0f,  0.0f, 0.0f,
	       0.0f, 0.0f, -1.0f, 0.0f,
	       0.0f, 1.0f,  0.0f, 0.0f,
	       0.0f, 0.0f,  0.0f, 1.0f };

mat4 face3 = { 1.0f, 0.0f, 0.0f, 0.0f,
	       0.0f, 0.0f, 1.0f, 0.0f,
	       0.0f,-1.0f, 0.0f, 0.0f,
	       0.0f, 0.0f, 0.0f, 1.0f };

mat4 face4 = { 1.0f, 0.0f,  0.0f, 0.0f,
	       0.0f, 1.0f,  0.0f, 0.0f,
	       0.0f, 0.0f,  1.0f, 0.0f,
	       0.0f, 0.0f,  0.0f, 1.0f };

mat4 face5 = { -1.0f, 0.0f,  0.0f, 0.0f,
	        0.0f, 1.0f,  0.0f, 0.0f,
	        0.0f, 0.0f, -1.0f, 0.0f,
	        0.0f, 0.0f,  0.0f, 1.0f };

void Mat4CubemapMatrixStd(mat4* r,const unsigned int face)
{
  switch (face){
  case 0:
    memcpy((void*)r,(void*)&face0.m00,sizeof(mat4));
    break;

  case 1:
    memcpy((void*)r,(void*)&face1.m00,sizeof(mat4));
    break;

  case 2:
    memcpy((void*)r,(void*)&face2.m00,sizeof(mat4));
    break;

  case 3:
    memcpy((void*)r,(void*)&face3.m00,sizeof(mat4));
    break;

  case 4:
    memcpy((void*)r,(void*)&face4.m00,sizeof(mat4));
    break;

  default:
    memcpy((void*)r,(void*)&face5.m00,sizeof(mat4));
    break;
  }
}

void Mat4CubemapProjectionMatStd(mat4* r,
				 const float z_near,
				 const float z_far,
				 const uint32_t d3dflag)
{
  uss_t us;
  float z_delta = z_far - z_near;

  r->m00 = 1.0f;
  r->m01 = 0.0f;
  r->m02 = 0.0f;
  r->m03 = 0.0f;

  r->m10 = 0.0f;
  r->m11 = 1.0f;
  r->m12 = 0.0f;
  r->m13 = 0.0f;

  r->m20 = 0.0f;
  r->m21 = 0.0f;
  r->m22 = (z_near + z_far) / z_delta;
  r->m23 = -(2.0f * z_far * z_near) / z_delta;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 1.0f;
  r->m33 = 0.0f;

  if ( d3dflag )
    {
      r->m22 = 0.5f * (r->m22 + r->m32);
      r->m23 = 0.5f * (r->m23 + r->m33);
    }
  else
    {
      r->m11 = -1.0f;
    }
  ClearFpuStatusStd(&us);
}

#if 0
void Mat3RotationFromMat4Std(mat3* r,const mat4* m)
{
  r->m00 = m->m00;
  r->m01 = m->m01;
  r->m02 = m->m02;

  r->m10 = m->m10;
  r->m11 = m->m11;
  r->m12 = m->m12;

  r->m20 = m->m20;
  r->m21 = m->m21;
  r->m22 = m->m22;
}

void Mat4FromMat3Std(mat4* r,const mat3* m)
{
  r->m00 = m->m00;
  r->m01 = m->m01;
  r->m02 = m->m02;

  r->m10 = m->m10;
  r->m11 = m->m11;
  r->m12 = m->m12;

  r->m20 = m->m20;
  r->m21 = m->m21;
  r->m22 = m->m22;

  r->m03 =
  r->m13 =
  r->m23 =
  r->m30 =
  r->m31 =
  r->m32 = 0.0f;

  r->m33 = 1.0f;
}
#endif

void Mat4LookAtStd(mat4* r,const vec3* from,const vec3* at)
{
  vec3  x;
  vec3  y;
  vec3  z;
  vec3  negFrom;
  uss_t us;

  Vec3SubtractStd(&z,at,from);
  Vec3NormalizeStd(&z,&z);

  x.x = z.z;
  x.y = 0.0f;
  x.z = -z.x;

  Vec3NormalizeStd(&x,&x);

  Vec3CrossStd(&y,&z,&x);
  Vec3NormalizeStd(&y,&y);

  memcpy((void*)&r->m00,(void*)&x,3*sizeof(float));
  memcpy((void*)&r->m10,(void*)&y,3*sizeof(float));
  memcpy((void*)&r->m20,(void*)&z,3*sizeof(float));

  r->m03 = 0.0f;
  r->m13 = 0.0f;
  r->m23 = 0.0f;
  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 0.0f;

  Vec3NegateStd(&negFrom,from);

  r->m03 += (negFrom.x * r->m00 + negFrom.y * r->m01 + negFrom.z * r->m02);
  r->m13 += (negFrom.x * r->m10 + negFrom.y * r->m11 + negFrom.z * r->m12);
  r->m23 += (negFrom.x * r->m20 + negFrom.y * r->m21 + negFrom.z * r->m22);
  r->m33 += (negFrom.x * r->m30 + negFrom.y * r->m31 + negFrom.z * r->m32);

  ClearFpuStatusStd(&us);
}

void Mat4LookAtLHStd(mat4* r,vec3* pEye,vec3* pCenter,vec3* pUp)
{
  vec3  x;
  vec3  y;
  vec3  z;
  vec3  w;
  uss_t us;

  Vec3SubtractStd(&z,pCenter,pEye);
  Vec3NormalizeStd(&z,&z);

  Vec3CrossStd(&x,pUp,&z);
  Vec3NormalizeStd(&x,&x);

  Vec3CrossStd(&y,&z,&x);
  Vec3NormalizeStd(&y,&y);

  Vec3DotStd(&w.x,&x,pEye);
  Vec3DotStd(&w.y,&y,pEye);
  Vec3DotStd(&w.z,&z,pEye);

  Vec3NegateStd(&w,&w);

  r->m00 = x.x;
  r->m10 = x.y;
  r->m20 = x.z;
  r->m30 = w.x;

  r->m01 = y.x;
  r->m11 = y.y;
  r->m21 = y.z;
  r->m31 = w.y;

  r->m02 = z.x;
  r->m12 = z.y;
  r->m22 = z.z;
  r->m32 = w.z;

  r->m03 = 0.0f;
  r->m13 = 0.0f;
  r->m23 = 0.0f;
  r->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void Mat4GlToD3DProjMatStd(mat4* r,const mat4* m)
{
  uss_t us;

  r->m00 = m->m00;
  r->m01 = m->m01;
  r->m02 = m->m02;
  r->m03 = m->m03;

  r->m10 = m->m10;
  r->m11 = m->m11;
  r->m12 = m->m12;
  r->m13 = m->m13;

  r->m20 = 0.5f * (m->m20 + m->m30);
  r->m21 = 0.5f * (m->m21 + m->m31);
  r->m22 = 0.5f * (m->m22 + m->m32);
  r->m23 = 0.5f * (m->m23 + m->m33);

  r->m30 = m->m30;
  r->m31 = m->m31;
  r->m32 = m->m32;
  r->m33 = m->m33;

  ClearFpuStatusStd(&us);
}

void Mat3RotationFromMat4Std(mat3* r,const mat4* m)
{
  r->m00 = m->m00;
  r->m01 = m->m01;
  r->m02 = m->m02;

  r->m10 = m->m10;
  r->m11 = m->m11;
  r->m12 = m->m12;

  r->m20 = m->m20;
  r->m21 = m->m21;
  r->m22 = m->m22;
}

void Mat4FromMat3Std(mat4* r,const mat3* m)
{
  r->m00 = m->m00;
  r->m01 = m->m01;
  r->m02 = m->m02;
  r->m03 = 0.0f;

  r->m10 = m->m10;
  r->m11 = m->m11;
  r->m12 = m->m12;
  r->m13 = 0.0f;

  r->m20 = m->m20;
  r->m21 = m->m21;
  r->m22 = m->m22;
  r->m23 = 0.0f;

  r->m30 = 0.0f;
  r->m31 = 0.0f;
  r->m32 = 0.0f;
  r->m33 = 1.0f;
}

void QuaternionAddStd(quaternion* r,const quaternion* q,const quaternion* v)
{
  uss_t us;

  quaternion qtmp = *q;
  quaternion vtmp = *v;

  qtmp.x *= vtmp.w;
  qtmp.y *= vtmp.w;
  qtmp.z *= vtmp.w;

  vtmp.x *= qtmp.w;
  vtmp.y *= qtmp.w;
  vtmp.z *= qtmp.w;

  r->x = (v->y * q->z) - (v->z * q->y) + qtmp.x + vtmp.x;
  r->y = (v->z * q->x) - (v->x * q->z) + qtmp.y + vtmp.y;
  r->z = (v->x * q->y) - (v->y * q->x) + qtmp.z + vtmp.z;
  r->w = q->w * q->w - (q->x * v->x + q->y * v->y + q->z * v->z);

  ClearFpuStatusStd(&us);
}

void QuaternionMultiplyStd(quaternion* r,const quaternion* q,const quaternion* v)
{
  uss_t us;
  float qx = q->x;
  float qy = q->y;
  float qz = q->z;
  float qw = q->w;
  float vx = v->x;
  float vy = v->y;
  float vz = v->z;
  float vw = v->w;

  r->x = qw * vx + qx * vw + qy * vz - qz * vy;
  r->y = qw * vy + qy * vw + qz * vx - qx * vz;
  r->z = qw * vz + qz * vw + qx * vy - qy * vx;
  r->w = qw * vw - qx * vx - qy * vy - qz * vz;

  ClearFpuStatusStd(&us);
}

void QuaternionInverseStd(quaternion* q,quaternion* u)
{
  q->x = -u->x;
  q->y = -u->y;
  q->z = -u->z;
  q->w =  u->w;
}

void QuaternionNormalizeStd(quaternion* r,quaternion* q)
{
  uss_t us;
  float fNorm;

  if ( 0.0f != (fNorm=(float)sqrt((q->x*q->x) +
			          (q->y*q->y) +
			          (q->z*q->z))) )
    {
      float fInvLength = 1.0f/fNorm;

      r->x = q->x * fInvLength;
      r->y = q->y * fInvLength;
      r->z = q->z * fInvLength;
      r->w = q->w * fInvLength;
    }
  else
    {
      r->x = r->y = r->z = r->w = 0.0f;
    }
  ClearFpuStatusStd(&us);
}

void QuaternionDotStd(float* r,const quaternion* q,const quaternion* v)
{
  uss_t us;

  *r = q->x*v->x + q->y*v->y + q->z*v->z + q->w*v->w;

  ClearFpuStatusStd(&us);
}

void QuaternionFromAxisStd(quaternion* q,const vec3* axis,const float angle)
{
  uss_t us;
  float fLength;

  if ( 0.0f != (fLength=(float)sqrt((axis->x*axis->x) +
			            (axis->y*axis->y) +
			            (axis->z*axis->z))) )
    {
      float angle2 = angle/2.0f;
      float scale  = (float)sin(angle2)/fLength;

      q->x = scale * axis->x;
      q->y = scale * axis->y;
      q->z = scale * axis->z;
      q->w = (float)cos(angle2);
    }
  ClearFpuStatusStd(&us);
}

static int nMat3RowSize = (sizeof(mat3)/sizeof(float))/3;

void QuaternionFromMat3Std(quaternion* q,const mat3* m)
{
  uss_t us;
  float fTrace;

  if ( (fTrace=m->m00+m->m11+m->m22) > 0.0f )
    {
      float scale = (float)sqrt(1.0f + fTrace);

      q->w  = scale * 0.5f;
      scale = 0.5f / scale;

      q->x = scale * (m->m21 - m->m12);
      q->y = scale * (m->m02 - m->m20);
      q->z = scale * (m->m10 - m->m01);
    }
  else
    {
      int    i,j,k;
      float  scale;
      
      float* fptr = (float*)m;
      float* qp[] = { &q->x, &q->y, &q->z };

      i = (m->m11 > m->m00 ? 1 : 0);
      i = (m->m22 > fptr[(nMat3RowSize*i)+i] ? 2 : i);

      j = (i+1 > 2 ? 0 : i+1);
      k = (j+1 > 2 ? 0 : j+1);

      scale = (float)sqrt(fptr[(nMat3RowSize*i)+i] -
		          fptr[(nMat3RowSize*j)+j] -
		          fptr[(nMat3RowSize*k)+k] + 1.0f);

      *qp[i] = (float)(scale * 0.5);
      scale  = (float)(0.5 / scale);
      *qp[j] = scale * (fptr[(nMat3RowSize*j)+i] + fptr[(nMat3RowSize*i)+j]);
      *qp[k] = scale * (fptr[(nMat3RowSize*k)+i] + fptr[(nMat3RowSize*i)+k]);
      q->w   = scale * (fptr[(nMat3RowSize*k)+j] - fptr[(nMat3RowSize*j)+k]);
    }
  ClearFpuStatusStd(&us);
}

static int nMat4RowSize = (sizeof(mat4)/sizeof(float))/4;

QuaternionFromMat4Std(quaternion* q,const mat4* m)
{
  uss_t us;
  float fTrace;

  if ( (fTrace=m->m00+m->m11+m->m22) > 0.0f )
    {
      float scale = (float)sqrt(1.0f + fTrace);

      q->w  = scale * 0.5f;
      scale = 0.5f / scale;

      q->x = scale * (m->m21 - m->m12);
      q->y = scale * (m->m02 - m->m20);
      q->z = scale * (m->m10 - m->m01);
    }
  else
    {
      int    i,j,k;
      float  scale;

      float* fptr = (float*)m;
      float* qp[] = { &q->x, &q->y, &q->z };

      i = (m->m11 > m->m00 ? 1 : 0);
      i = (m->m22 > fptr[(nMat4RowSize*i)+i] ? 2 : i);

      j = (i+1 > 2 ? 0 : i+1);
      k = (j+1 > 2 ? 0 : j+1);

      scale = (float)sqrt(fptr[(nMat4RowSize*i)+i] -
		          fptr[(nMat4RowSize*j)+j] -
		          fptr[(nMat4RowSize*k)+k] + 1.0f);

      *qp[i] = scale * 0.5f;
      scale = (float)(0.5 / scale);
      *qp[j] = scale * (fptr[(nMat4RowSize*j)+i] + fptr[(nMat4RowSize*i)+j]);
      *qp[k] = scale * (fptr[(nMat4RowSize*k)+i] + fptr[(nMat4RowSize*k)+k]);
      q->w   = scale * (fptr[(nMat4RowSize*k)+j] - fptr[(nMat4RowSize*j)+k]);
    }
  ClearFpuStatusStd(&us);
}

void QuaternionToMat3Std(mat3* m,const quaternion* q)
{
  uss_t us;
  float x = q->x;
  float y = q->y;
  float z = q->z;
  float w = q->w;

  m->m00 = 1.0f - (2.0f*((y*y) + (z*z)));
  m->m01 = 2.0f*((x*y) - (z*w));
  m->m02 = 2.0f*((x*z) + (y*w));

  m->m10 = 2.0f*((x*y) + (z*w));
  m->m11 = 1.0f - (2.0f*((x*x) + (z*z)));
  m->m12 = 2.0f*((y*z) - (x*w));

  m->m20 = 2.0f*((x*z) - (y*w));
  m->m21 = 2.0f*((y*z) + (x*w));
  m->m22 = 1.0f - (2.0f*((x*x) + (y*y)));

  ClearFpuStatusStd(&us);
}

void QuaternionToMat4Std(mat4* m,const quaternion* q)
{
  uss_t us;
  float x = q->x;
  float y = q->y;
  float z = q->z;
  float w = q->w;

  m->m00 = 1.0f - (2.0f*((y*y) + (z*z)));
  m->m01 = 2.0f*((x*y) - (z*w));
  m->m02 = 2.0f*((x*z) + (y*w));
  m->m03 = 0.0f;

  m->m10 = 2.0f*((x*y) + (z*w));
  m->m11 = 1.0f - (2.0f*((x*x) + (z*z)));
  m->m12 = 2.0f*((y*z) - (x*w));
  m->m13 = 0.0f;

  m->m20 = 2.0f*((x*z) - (y*w));
  m->m21 = 2.0f*((y*z) + (x*w));
  m->m22 = 1.0f - (2.0f*((x*x) + (y*y)));
  m->m23 = 0.0f;

  m->m30 = 0.0f;
  m->m31 = 0.0f;
  m->m32 = 0.0f;
  m->m33 = 1.0f;

  ClearFpuStatusStd(&us);
}

void QuaternionSlerpStd(quaternion* r,const float s,const quaternion* q,const quaternion* v)
{
  uss_t us;
  float cosAngle;
  float angle;

  QuaternionDotStd(&cosAngle,q,v);

  cosAngle = (cosAngle < -1.0f ? -1.0f :
	      cosAngle > 1.0f  ?  1.0f :
	      cosAngle);

  angle = (float)acos(cosAngle);

  if ( fabs(angle) < 10e-6 )
    {
      *r = *q;
    }
  else
    {
      // Clamp the sine to 0/-1 to eliminate infinity
      //

      float sine = (float)sin(angle);
      float invs = 1.0f / (10e-6 < fabs(sine) ? sine : 1.0f);
      float c1   = (float)(sin((1.0f-s)*angle) * invs);
      float c2   = (float)(sin((s*angle)) * invs);

      r->x = (c1*q->x) + (c2*v->x);
      r->y = (c1*q->y) + (c2*v->y);
      r->z = (c1*q->z) + (c2*v->z);
      r->w = (c1*q->w) + (c2*v->w);
    }
  ClearFpuStatusStd(&us);
}

void QuaternionCosStd(float* r,const quaternion* q,const quaternion* p)
{
  float fDot;

  QuaternionDotStd(&fDot,q,p);

  fDot = (fDot < -1 ? -1 : fDot > 1 ? 1 : fDot);

  *r = fDot;
}

void QuaternionSinStd(float* r,const quaternion* q,const quaternion* p)
{
  uss_t us;
  float fDot;

  // cos = dot(q,p)

  QuaternionCosStd(&fDot,q,p);

  *r = (float)sqrt(1.0f-(fDot*fDot));

  ClearFpuStatusStd(&us);
}
