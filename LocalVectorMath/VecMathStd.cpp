#include <VecMath.h>

static mat4 faces[] = {
    mat4( 0,  0, -1, 0,
	  0,  1,  0, 0,
	  1,  0,  0, 0,
	  0,  0,  0, 1),
    mat4( 0,  0,  1, 0,
	  0,  1,  0, 0,
	 -1,  0,  0, 0,
	  0,  0,  0, 1),
    mat4( 1,  0,  0, 0,
	  0,  0, -1, 0,
	  0,  1,  0, 0,
	  0,  0,  0, 1),
    mat4( 1,  0,  0, 0,
	  0,  0,  1, 0,
	  0, -1,  0, 0,
	  0,  0,  0, 1),
    mat4( 1,  0,  0, 0,
	  0,  1,  0, 0,
	  0,  0,  1, 0,
	  0,  0,  0, 1),
    mat4(-1,  0,  0, 0,
	  0,  1,  0, 0,
	  0,  0, -1, 0,
	  0,  0,  0, 1)
};

/* ---------------------------------------------------------
 * One dimensional methods
 * --------------------------------------------------------- */

float FloatLerpStd(const float u,const float v,const float x)
{
  return u * (1 - x) + v * x;
}

float FloatSqrStd (const float x)
{
  return x * x;
}

/* ---------------------------------------------------------
 * Two dimensional methods
 * --------------------------------------------------------- */

void Vec2AddStd(vec2& r,const vec2& u,const vec2& v)
{
  r.x = u.x + v.x;
  r.y = u.y + v.y;
}

void Vec2AddFloatStd(vec2& r,const vec2& v,const float s)
{
  r.x = v.x + s;
  r.y = v.y + s;
}

void Vec2SubtractStd(vec2& r,const vec2& u,const vec2& v)
{
  r.x = u.x - v.x;
  r.y = u.y - v.y;
}

void Vec2SubtractFloatStd(vec2& r,const vec2& v,const float s)
{
  r.x = v.x - s;
  r.y = v.y - s;
}

void Vec2NegateStd(vec2& r,vec2& v)
{
  r.x = -v.x;
  r.y = -v.y;
}

void Vec2MultiplyStd(vec2& r,const vec2& u,const vec2& v)
{
  r.x = u.x * v.x;
  r.y = u.y * v.y;
}

void Vec2MultiplyFloatStd(vec2& r,const vec2& v,const float s)
{
  r.x = v.x * s;
  r.y = v.y * s;
}

void Vec2FloatMultiplyStd(vec2& r,const float s,const vec2& v)
{
  r.x = v.x * s;
  r.y = v.y * s;
}

void Vec2DivideStd(vec2& r,const vec2& u,const vec2& v)
{
  r.x = u.x / v.x;
  r.y = u.y / v.y;
}

void Vec2DivideFloatStd(vec2& r,const vec2& v,const float s)
{
  r.x = v.x / s;
  r.y = v.y / s;
}

void Vec2LerpStd(vec2& r,const vec2& u,const vec2& v,const float x)
{
  float k = 1.0 - x;
  r.x = u.x * k + v.x * x;
  r.y = u.y * k + v.y * x;
}

void Vec2SqrStd(vec2& r,const vec2& v)
{
  r.x = v.x * v.x;
  r.y = v.y * v.y;
}

void Vec2NormalizeStd(vec2& r,const vec2& v)
{
  float base = (float)sqrtf(v.x * v.x + v.y * v.y);
  r.x = v.x / base;
  r.y = v.y / base;
}

float Vec2DotStd(const vec2& u,const vec2& v)
{
  return u.x * v.x + u.y * v.y;
}

float Vec2LengthStd(const vec2& v)
{
  return sqrtf(v.x * v.x + v.y * v.y);
}

/* ---------------------------------------------------------
 * Three dimensional methods
 * --------------------------------------------------------- */

void Vec3AddStd(vec3& r,const vec3& u,const vec3& v)
{
  r.x = u.x + v.x;
  r.y = u.y + v.y;
  r.z = u.z + v.z;
}

void Vec3AddFloatStd(vec3& r,const vec3& v,const float s)
{
  r.x = v.x+s;
  r.y = v.y+s;
  r.z = v.z+s;
}

void Vec3FloatAddStd(vec3& r,const float s,const vec3& v)
{
  r.x = v.x+s;
  r.y = v.y+s;
  r.z = v.z+s;
}

void Vec3SubtractStd(vec3& r,const vec3& u,const vec3& v)
{
  r.x = u.x-v.x;
  r.y = u.y-v.y;
  r.z = u.z-v.z;
}

void Vec3SubtractFloatStd(vec3& r,const vec3& v,const float s)
{
  r.x = v.x-s;
  r.y = v.y-s;
  r.z = v.z-s;
}

void Vec3FloatSubtractStd(vec3& r,const float s,const vec3& v)
{
  r.x = s - v.x;
  r.y = s - v.y;
  r.z = s - v.z;
}

void Vec3NegateStd(vec3& r,const vec3& v)
{
  r.x = -v.x;
  r.y = -v.y;
  r.z = -v.z;
}

void Vec3MultiplyStd(vec3& r,const vec3& u,const vec3& v)
{
  r.x = u.x * v.x;
  r.y = u.y * v.y;
  r.z = u.z *v.z;
}

void Vec3MultiplyFloatStd(vec3& r,const vec3& u,const float s)
{
  r.x = u.x * s;
  r.y = u.y * s;
  r.z = u.z * s;
}

void Vec3FloatMultiplyStd(vec3& r,const float s,const vec3& v)
{
  r.x = v.x * s;
  r.y = v.y * s;
  r.z = v.z * s;
}

void Vec3DivideStd(vec3& r,const vec3& u,const vec3& v)
{
  r.x = u.x / v.x;
  r.y = u.y / v.y;
  r.z = u.z / v.z;
}

void Vec3DivideFloatStd (vec3& r,const vec3& v,const float s)
{
  r.x = v.x / s;
  r.y = v.y / s;
  r.z = v.z / s;
}

void Vec3LerpStd(vec3& r,const vec3& u,const vec3& v,const float x)
{
  float k = 1.0 - x;
  r.x = u.x * k + v.x * x;
  r.y = u.y * k + v.y * x;
  r.z = u.z * k + v.z * x;
}

void Vec3SqrStd(vec3& r,const vec3& v)
{
  r.x = v.x * v.x;
  r.y = v.y * v.y;
  r.z = v.z * v.z;
}

void Vec3NormalizeStd(vec3& r,const vec3& v)
{
  float base = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

  r.x = v.x / base;
  r.y = v.y / base;
  r.z = v.z / base;
}

void Vec3CrossStd(vec3& r,const vec3& u,const vec3& v)
{
  r.x = u.y * v.z - v.y * u.z;
  r.y = u.z * v.x - u.x * v.z;
  r.z = u.x * v.y - u.y * v.x;
}

float Vec3DotStd(const vec3& u,const vec3& v)
{
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

float Vec3LengthStd(const vec3& v)
{
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/* ---------------------------------------------------------
 * Four dimensional methods
 * --------------------------------------------------------- */

void Vec4AddStd(vec4& r,const vec4& u,const vec4& v)
{
  r.x = u.x + v.x;
  r.y = u.y + v.y;
  r.z = u.z + v.z;
  r.w = u.w + v.w;
}

void Vec4AddFloatStd(vec4& r,const vec4& v,const float s)
{
  r.x = v.x + s;
  r.y = v.y + s;
  r.z = v.z + s;
  r.w = v.w + s;
}

void Vec4FloatAddStd(vec4& r,const float s,const vec4& v)
{
  r.x = v.x + s;
  r.y = v.y + s;
  r.z = v.z + s;
  r.w = v.w + s;
}

void Vec4SubtractStd(vec4& r,const vec4& u,const vec4& v)
{
  r.x = u.x - v.x;
  r.y = u.y - v.y;
  r.z = u.z - v.z;
  r.w = u.w - v.w;
}

void Vec4SubtractFloatStd(vec4& r,const vec4& v,const float s)
{
  r.x = v.x - s;
  r.y = v.y - s;
  r.z = v.z - s;
  r.w = v.w - s;
}

void Vec4FloatSubtractStd(vec4& r,const float s,const vec4& v)
{
  r.x = s - v.x;
  r.y = s - v.y;
  r.z = s - v.z;
  r.w = s - v.w;
}

void Vec4NegateStd(vec4& r,const vec4& v)
{
  r.x = -v.x;
  r.y = -v.y;
  r.z = -v.z;
  r.w = -v.w;
}

void Vec4MultiplyStd(vec4& r,const vec4& u,const vec4& v)
{
  r.x = u.x * v.x;
  r.y = u.y * v.y;
  r.z = u.z * v.z;
  r.w = u.w * v.w;
}

void Vec4MultiplyFloatStd(vec4& r,const vec4& u,const float s)
{
  r.x = u.x * s;
  r.y = u.y * s;
  r.z = u.z * s;
  r.w = u.w * s;
}

void Vec4FloatMultiplyStd(vec4& r,const float s,const vec4& u)
{
  r.x = u.x * s;
  r.y = u.y * s;
  r.z = u.z * s;
  r.w = u.w * s;
}

void Vec4DivideStd(vec4& r,const vec4& u,const vec4& v)
{
  r.x = u.x / v.x;
  r.y = u.y / v.y;
  r.z = u.z / v.z;
  r.w = u.w / v.w;
}

void Vec4DivideFloatStd(vec4& r,const vec4& v,const float s)
{
  r.x = v.x / s;
  r.y = v.y / s;
  r.z = v.z / s;
  r.w = v.w / s;
}

void Vec4LerpStd(vec4& r,const vec4& u,const vec4& v,const float x)
{
  float k = 1.0 - x;
  r.x = u.x * k + v.x * x;
  r.y = u.y * k + v.y * x;
  r.z = u.z * k + v.z * x;
  r.w = u.w * k + v.w * x;
}
  
void Vec4SqrStd(vec4& r,const vec4& v)
{
  r.x = v.x * v.x;
  r.y = v.y * v.y;
  r.z = v.z * v.z;
  r.w = v.w * v.w;
}
  
void Vec4CrossStd(vec4& r,const vec4& u,const vec4& v)
{
  r.x = u.y * v.z - v.y * u.z;
  r.y = u.z * v.x - u.x * v.z;
  r.z = u.x * v.y - u.y * v.x;
  r.w = 0.0f;
}

void Vec4NormalizeStd(vec4& r,const vec4& v)
{
  float base = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
  r.x = v.x / base;
  r.y = v.y / base;
  r.z = v.z / base;
  r.w = v.w / base;
}

float Vec4DotStd(const vec4& u,const vec4& v)
{
  return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

float Vec4LengthStd(const vec4& v)
{
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

/* ---------------------------------------------------------
 * Simple 2-D Matrix operations
 * --------------------------------------------------------- */

void Mat2AddStd(mat2& r,const mat2& m,const mat2& n)
{
  r.e00 = m.e00 + n.e00;
  r.e01 = m.e01 + n.e01;
  r.e10 = m.e10 + n.e10;
  r.e11 = m.e11 + n.e11;
}

void Mat2SubtractStd(mat2& r,const mat2& m,const mat2& n)
{
  r.e00 = m.e00 - n.e00;
  r.e01 = m.e01 - n.e01;
  r.e10 = m.e10 - n.e10;
  r.e11 = m.e11 - n.e11;
}

void Mat2NegateStd(mat2& r,const mat2& m)
{
  r.e00 = -m.e00;
  r.e01 = -m.e01;
  r.e10 = -m.e10;
  r.e11 = -m.e11;
}		   

void Mat2MultiplyStd(mat2& r,const mat2& m,const mat2& n)
{
  r.e00 = m.e00 * n.e00 + m.e01 * n.e10;
  r.e01 = m.e00 * n.e01 + m.e01 * n.e11;
  r.e10 = m.e10 * n.e00 + m.e11 * n.e10;
  r.e11 = m.e10 * n.e01 + m.e11 * n.e11;
}

void Mat2MultiplyVecStd(vec2& r,const mat2& m,const vec2& v)
{
  r.x = m.e00 * v.x + m.e01 * v.y;
  r.y = m.e10 * v.x + m.e11 * v.y ;
}

void Mat2MultiplyFloatStd(mat2& r,const mat2& m,const float s)
{
  r.e00 = m.e00 * s;
  r.e01 = m.e01 * s;
  r.e10 = m.e10 * s;
  r.e11 = m.e11 * s;
}

void Mat2IdentityStd(mat2& r)
{
  r.e00 = 1.0;
  r.e01 = 0.0;
  r.e10 = 0.0;
  r.e11 = 1.0;
}

void Mat2TransposeStd(mat2& r,const mat2& m)
{
  r.e00 = m.e00;
  r.e01 = m.e10;
  r.e10 = m.e01;
  r.e11 = m.e11;
}

void Mat2RotateStd(mat2& r,const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  r.e00 = cosA;
  r.e01 = -sinA;
  r.e10 = sinA;
  r.e11 = cosA;
}

void Mat2ScaleStd(mat2& r,const float x,const float y)
{
  r.e00 = x;
  r.e01 = 0.0;
  r.e10 = 0.0;
  r.e11 = y;
}

/* ---------------------------------------------------------
 * Simple 3-D Matrix operations
 * --------------------------------------------------------- */

void Mat3AddStd(mat3& r,const mat3& m,const mat3& n)
{
  r.e00 = m.e00 + n.e00;
  r.e01 = m.e01 + n.e01;
  r.e02 = m.e02 + n.e02;
  r.e10 = m.e10 + n.e10;
  r.e11 = m.e11 + n.e11;
  r.e12 = m.e12 + n.e12;
  r.e20 = m.e20 + n.e20;
  r.e21 = m.e21 + n.e21;
  r.e22 = m.e22 + n.e22;
  r.n03 = r.n13 = r.n23 = 1.0f;
}

void Mat3SubtractStd(mat3& r,const mat3& m,const mat3& n)
{
  r.e00 = m.e00 - n.e00;
  r.e01 = m.e01 - n.e01;
  r.e02 = m.e02 - n.e02;
  r.e10 = m.e10 - n.e10;
  r.e11 = m.e11 - n.e11;
  r.e12 = m.e12 - n.e12;
  r.e20 = m.e20 - n.e20;
  r.e21 = m.e21 - n.e21;
  r.e22 = m.e22 - n.e22;
}

void Mat3NegateStd(mat3& r,const mat3& m)
{
  r.e00 = -m.e00;
  r.e01 = -m.e01;
  r.e02 = -m.e02;
  r.e10 = -m.e10;
  r.e11 = -m.e11;
  r.e12 = -m.e12;
  r.e20 = -m.e20;
  r.e21 = -m.e21;
  r.e22 = -m.e22;
}

void Mat3MultiplyStd(mat3& r,const mat3& m,const mat3& n)
{
  float *rp,*mp,*col;

  int ipr  = sizeof(mat3) / (3*sizeof(float));
  int ipr2 = 2*ipr;

  for( unsigned int i=0 ; i < 3 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)&r) + offs;
      mp  = ((float*)&m) + offs;
      col = (float*)&n;

      for( unsigned int j=0 ; j < 3 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)     +
	    *(mp+1) * *(col+ipr) +
	    *(mp+2) * *(col+ipr2);
	}
    }

  r.n03 = r.n13 = r.n23 = 1.0f;

}

void Mat3MultiplyFloatStd(mat3& r,const mat3& m,const float s)
{
  float* fResult = (float*)&r;
  float* fBase   = (float*)&m;

  for( unsigned int i=0 ; i < sizeof(mat3)/sizeof(float) ; ++i ) fResult[i] = fBase[i] * s;

  r.n03 = r.n13 = r.n23 = 1.0f;
}

void Mat3MultiplyVecStd(vec3& r,const mat3& m,const vec3& v)
{
  r.x = m.e00 * v.x + m.e01 * v.y + m.e02 * v.z;
  r.y = m.e10 * v.x + m.e11 * v.y + m.e12 * v.z;
  r.z = m.e20 * v.x + m.e21 * v.y + m.e22 * v.z;
}

void Mat3IdentityStd(mat3& r)
{
  r.e00 = 1.0f;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e10 = 0.0f;
  r.e11 = 1.0f;
  r.e12 = 0.0f;
  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = 1.0f;
}

void Mat3TransposeStd(mat3& r,const mat3& m)
{
  r.e00 = m.e00;
  r.e01 = m.e10;
  r.e02 = m.e20;
  r.e10 = m.e01;
  r.e11 = m.e11;
  r.e12 = m.e21;
  r.e20 = m.e02;
  r.e21 = m.e12;
  r.e22 = m.e22;
}

void Mat3InverseStd(mat3& r,const mat3& m)
{
  float p0 = m.e11 * m.e22 - m.e21 * m.e12;
  float p1 = m.e12 * m.e20 - m.e10 * m.e22;
  float p2 = m.e10 * m.e21 - m.e11 * m.e20;

  float invDet = 1.0f / (m.e00 * p0 + m.e01 * p1 + m.e02 * p2);

  r.e00 = p0;
  r.e01 = m.e21 * m.e02 - m.e01 * m.e22;
  r.e02 = m.e01 * m.e12 - m.e11 * m.e02;
  r.e10 = p1;
  r.e11 = m.e00 * m.e22 - m.e20 * m.e02;
  r.e12 = m.e10 * m.e02 - m.e00 * m.e12;
  r.e20 = p2;
  r.e21 = m.e20 * m.e01 - m.e00 * m.e21;
  r.e22 = m.e00 * m.e11 - m.e01 * m.e10;

  Mat3MultiplyFloat(r,r,invDet);
}

void Mat3RotateXStd(mat3& r,const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  r.e00 = 1.0;
  r.e01 = 0.0;
  r.e02 = 0.0;
  r.e10 = 0.0;
  r.e11 = cosA;
  r.e12 = -sinA;
  r.e20 = 0.0;
  r.e21 = sinA;
  r.e22 = cosA;
} 	      
  	      
void Mat3RotateYStd(mat3& r,const float angle)
{
  float cosA = cosf(angle),sinA = sinf(angle);

  r.e00 =   cosA;
  r.e01 =   0;
  r.e02 =   -sinA;
  r.e10 =   0;
  r.e11 =   1;
  r.e12 =   0;
  r.e20 =   sinA;
  r.e21 =   0;
  r.e22 =   cosA;
}

void Mat3RotateZStd(mat3& r,const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  r.e00 = cosA;
  r.e01 = -sinA;
  r.e02 = 0.0;
  r.e10 = sinA;
  r.e11 = cosA;
  r.e12 = 0.0;
  r.e20 = 0.0;
  r.e21 = 0.0;
  r.e22 = 1.0;
}

void Mat3RotateXYStd(mat3& r,const float x,const float y)
{
  float cosX = cosf(x),
        sinX = sinf(x),
        cosY = cosf(y),
        sinY = sinf(y);

  r.e00 =  cosY;
  r.e01 =  0.0;
  r.e02 = -sinY;
  r.e10 = -sinX * sinY;
  r.e11 =  cosX;
  r.e12 = -sinX * cosY;
  r.e20 =  cosX * sinY;
  r.e21 =  sinX;
  r.e22 =  cosX * cosY;
}

void Mat3RotateXYZStd(mat3& r,const float x,const float y,const float z)
{
  float cosX = cosf(x), sinX = sinf(x),
        cosY = cosf(y), sinY = sinf(y),
        cosZ = cosf(z), sinZ = sinf(z);

  r.e00 = cosY * cosZ + sinX * sinY * sinZ;
  r.e01 = -cosX * sinZ;
  r.e02 = sinX * cosY * sinZ - sinY * cosZ;
  r.e10 = cosY * sinZ - sinX * sinY * cosZ;
  r.e11 = cosX * cosZ;
  r.e12 = -sinY * sinZ - sinX * cosY * cosZ;
  r.e20 = cosX * sinY;
  r.e21 = sinX;
  r.e22 = cosX * cosY;
}

void Mat3ScaleStd(mat3& r,const float x,const float y,const float z)
{
  r.e00 = x;
  r.e01 = 0;
  r.e02 = 0;
  r.e10 = 0;
  r.e11 = y;
  r.e12 = 0;
  r.e20 = 0;
  r.e21 = 0;
  r.e22 = z;
}

/* ---------------------------------------------------------
 * Simple 4-D Matrix operations
 * --------------------------------------------------------- */

void Mat4AddStd(mat4& r,const mat4& m,const mat4& n)
{
  float* rp = (float*)&r;
  float* mp = (float*)&m;
  float* np = (float*)&n;

  for( unsigned int i=0 ; i < 16 ; ++i )
    {
      *rp = *mp + *np;
      ++rp;
      ++mp;
      ++np;
    }
}

void Mat4SubtractStd(mat4& r,const mat4& m,const mat4& n)
{
  float *rp = (float*)&r;
  float *mp = (float*)&m;
  float *np = (float*)&n;

  for( unsigned int i=0 ; i < 16 ; ++i )
    {
      *rp = *mp - *np;
      ++rp;
      ++mp;
      ++np;
    }
}

void Mat4NegateStd(mat4& r,const mat4& m)
{
  float *rp = (float*)&r;
  float *mp = (float*)&m;

  for( unsigned int i=0 ; i < 16 ; ++i )
    {
      *rp = -(*mp);
      ++rp;
      ++mp;
    }
}

void Mat4MultiplyStd(mat4& r,const mat4& m,const mat4& n)
{
  float *rp,*mp,*col;

  int ipr  = sizeof(mat4) / (4*sizeof(float));
  int ipr2 = 2*ipr;
  int ipr3 = 3*ipr;

  for( unsigned int i=0 ; i < 4 ; ++i )
    {
      int offs = i * ipr;
      rp  = ((float*)&r) + offs;
      mp  = ((float*)&m) + offs;
      col = (float*)&n;

      for( unsigned int j=0 ; j < 4 ; ++j,++rp,++col )
	{
	  *rp =
	    *(mp)   * *(col)      +
	    *(mp+1) * *(col+ipr)  +
	    *(mp+2) * *(col+ipr2) +
	    *(mp+3) * *(col+ipr3) ;
	}
    }
}

void Mat4MultiplyVecStd(vec4& r,const mat4& m,const vec4& v)
{
  r.x = m.e00 * v.x + m.e01 * v.y + m.e02 * v.z + m.e03 * v.w;
  r.y = m.e10 * v.x + m.e11 * v.y + m.e12 * v.z + m.e13 * v.w;
  r.z = m.e20 * v.x + m.e21 * v.y + m.e22 * v.z + m.e23 * v.w;
  r.w = m.e30 * v.x + m.e31 * v.y + m.e32 * v.z + m.e33 * v.w;
}

void Mat4MultiplyFloatStd(mat4& r,const mat4& m,const float s)
{
  float *rp = (float*)&r;
  float *mp = (float*)&m;
  float *ep = rp + 16;

  for( ; rp < ep ; ++rp,++mp )
    {
      *rp = *mp * s;
    }
}

void Mat4IdentityStd(mat4& r)
{
  r.e00 = 1.0f;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = 0.0f;
  r.e10 = 0.0f;
  r.e11 = 1.0f;
  r.e12 = 0.0f;
  r.e13 = 0.0f;
  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = 1.0f;
  r.e23 = 0.0f;
  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0f;
}

void Mat4TransposeStd(mat4& r,const mat4& m)
{
  r.e00 = m.e00;
  r.e01 = m.e10;
  r.e02 = m.e20;
  r.e03 = m.e30;
  r.e10 = m.e01;
  r.e11 = m.e11;
  r.e12 = m.e21;
  r.e13 = m.e31;
  r.e20 = m.e02;
  r.e21 = m.e12;
  r.e22 = m.e22;
  r.e23 = m.e32;
  r.e30 = m.e03;
  r.e31 = m.e13;
  r.e32 = m.e23;
  r.e33 = m.e33;
}

void Mat4ScaleStd(mat4& r,const float x,const float y,const float z)
{
  r.e00 = x;   
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = 0.0f;
  r.e10 = 0.0f;
  r.e11 = y;   
  r.e12 = 0.0f;
  r.e13 = 0.0f;
  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = z;   
  r.e23 = 0.0f;
  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0;
}

void Mat4RotateXStd(mat4& r,const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);
  
  r.e00 = 1.0f;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = 0.0f;

  r.e10 = 0.0f;
  r.e11 = cosA;
  r.e12 = -sinA;
  r.e13 = 0.0f;

  r.e20 = 0.0f;
  r.e21 = sinA;
  r.e22 = cosA;
  r.e23 = 0.0f;

  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0f;
}

void Mat4RotateYStd(mat4& r,const float y)
{
  float cosA = cosf(y), sinA = sinf(y);

  r.e00 = cosA;
  r.e01 = 0.0f;
  r.e02 = -sinA;
  r.e03 = 0.0f;

  r.e10 = 0.0f;
  r.e11 = 1.0f;
  r.e12 = 0.0f;
  r.e13 = 0.0f;

  r.e20 = sinA;
  r.e21 = 0.0;
  r.e22 = cosA;
  r.e23 = 0.0f;

  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0f;
}

void Mat4RotateZStd(mat4& r,const float z)
{
  float cosA = cosf(z), sinA = sinf(z);

  r.e00 = cosA;
  r.e01 = -sinA;
  r.e02 = 0.0f;
  r.e03 = 0.0f;

  r.e10 = sinA;
  r.e11 = cosA;
  r.e12 = 0.0f;
  r.e13 = 0.0f;

  r.e20 = 0.0;
  r.e21 = 0.0;
  r.e22 = 1.0;
  r.e23 = 0.0f;

  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0f;
}

void Mat4RotateXYStd(mat4& r,const float x,const float y)
{
  float cosX = cosf(x),
        sinX = sinf(x),
        cosY = cosf(y),
        sinY = sinf(y);

  r.e00 = cosY;
  r.e01 = 0.0;
  r.e02 = -sinX;
  r.e03 = 0.0f;
		 
  r.e10 = -sinX * sinY;
  r.e11 = cosX;
  r.e12 = -sinX * cosY;
  r.e13 = 0.0f;
		 
  r.e20 = cosX * sinY;
  r.e21 = sinX;
  r.e22 = cosX * cosY;
  r.e23 = 0.0f;
		 
  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0f;
}

void Mat4RotateXYZStd(mat4& r,const float x,const float y,const float z)
{
  float cosX = cosf(x),
        sinX = sinf(x),
        cosY = cosf(y),
        sinY = sinf(y),
        cosZ = cosf(z),
        sinZ = sinf(z);

  r.e00 = cosY * cosZ + sinX * sinY * sinZ;
  r.e01 = -cosX * sinZ;
  r.e02 = sinX * cosY * sinZ - sinY * cosZ;
  r.e03 = 0;

  r.e10 = cosY * sinZ - sinX * sinY * cosZ;
  r.e11 = cosX * cosZ;
  r.e12 = -sinY * sinZ - sinX * cosY * cosZ;
  r.e13 = 0;

  r.e20 = cosX * sinY;
  r.e21 = sinX;
  r.e22 = cosX * cosY;
  r.e23 = 0;

  r.e30 = 0;
  r.e31 = 0;
  r.e32 = 0;
  r.e33 = 1;
}

void Mat4TranslateMatrixStd(mat4& r,const mat4& m,const vec3& v)
{
  r.e03 += (v.x * m.e00 + v.y * m.e01 + v.z * m.e02);
  r.e13 += (v.x * m.e10 + v.y * m.e11 + v.z * m.e12);
  r.e23 += (v.x * m.e20 + v.y * m.e21 + v.z * m.e22);
  r.e33 += (v.x * m.e30 + v.y * m.e31 + v.z * m.e32);
}

void Mat4TranslateFloatStd (mat4& r,const float x,const float y,const float z)
{
  r.e00 = 1.0f;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = x;

  r.e10 = 0.0f;
  r.e11 = 1.0f;
  r.e12 = 0.0f;
  r.e13 = y;

  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = 1.0f;
  r.e23 = z;

  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0;
}

void Mat4TranslateVecStd(mat4& r,const vec3& v)
{
  r.e00 = 1.0f;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = v.x;
		 
  r.e10 = 0.0f;
  r.e11 = 1.0f;
  r.e12 = 0.0f;
  r.e13 = v.y;
		 
  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = 1.0f;
  r.e23 = v.z;
		 
  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 0.0f;
  r.e33 = 1.0;
}

void Mat4OrthoStructStd(mat4& r,const struct orthoMatrix& d)
{
  float rl = d.right - d.left;
  float tb = d.top   - d.bottom;
  float fn = d.z_far - d.z_near;

  r.e00 =   2.0f / rl;
  r.e01 =   0.0;
  r.e02 =   0.0;
  r.e03 =   -(d.right + d.left) / rl;
		   
  r.e10 =   0.0;
  r.e11 =   2.0f / tb;
  r.e12 =   0.0;
  r.e13 =   -(d.top + d.bottom) / tb;
		   
  r.e20 =   0.0;
  r.e21 =   0.0;
  r.e22 =   -2.0f / fn;
  r.e23 =   -(d.z_far + d.z_near) / fn;
		   
  r.e30 =   0.0;
  r.e31 =   0.0;
  r.e32 =   0.0;
  r.e33 =   1.0;

  if (d.d3dtype){
    r.e22 = 0.5f * (r.e22 + r.e32);
    r.e23 = 0.5f * (r.e23 + r.e33);
  }
}

void Mat4PerspectiveXStd(mat4& r,const struct perspectiveMatrix& s)
{
  float w = tanf(0.5f * s.fov);
  float h = (w * s.height) / s.width;

  r.e00 = 1.0f / w;
  r.e01 = 0.0f;
  r.e02 = 0.0f;
  r.e03 = 0.0f;
  r.e10 = 0.0f;
  r.e11 = 1.0f / h;
  r.e12 = 0.0f;
  r.e13 = 0.0f;
  r.e20 = 0.0f;
  r.e21 = 0.0f;
  r.e22 = (s.z_far + s.z_near) / (s.z_far - s.z_near);
  r.e23 = -(2 * s.z_far * s.z_near) / (s.z_far - s.z_near);
  r.e30 = 0.0f;
  r.e31 = 0.0f;
  r.e32 = 1.0f;
  r.e33 = 0.0f;

  if (s.d3dtype){
    r.e22 = 0.5f * (r.e22 + r.e32);
    r.e23 = 0.5f * (r.e23 + r.e33);
  }
}

void Mat4ShadowMatrixStd(mat4& r,const vec3 &planeNormal, const float planeOffset, const vec3 &lightPos)
{
  float dist = dot(lightPos, planeNormal) + planeOffset;

  r.e00 = dist - lightPos.x * planeNormal.x;
  r.e01 = - lightPos.x * planeNormal.y;
  r.e02 = - lightPos.x * planeNormal.z;
  r.e03 = - lightPos.x * planeOffset;

  r.e10 = - lightPos.y * planeNormal.x;
  r.e11 = dist - lightPos.y * planeNormal.y;
  r.e12 = - lightPos.y * planeNormal.z;
  r.e13 = - lightPos.y * planeOffset;

  r.e20 = - lightPos.z * planeNormal.x;
  r.e21 = - lightPos.z * planeNormal.y;
  r.e22 = dist - lightPos.z * planeNormal.z;
  r.e23 = - lightPos.z * planeOffset;

  r.e30 = - planeNormal.x;
  r.e31 = - planeNormal.y;
  r.e32 = - planeNormal.z;
  r.e33 = dist - planeOffset;
}

void Mat4MirrorMatrixStd(mat4& r,const vec3 &planeNormal, const float planeOffset)
{
  r.e00 = 1 - 2 * planeNormal.x * planeNormal.x;
  r.e01 =   - 2 * planeNormal.x * planeNormal.y;
  r.e02 =   - 2 * planeNormal.x * planeNormal.z;
  r.e03 =   - 2 * planeNormal.x * planeOffset;

  r.e10 =   - 2 * planeNormal.y * planeNormal.x;
  r.e11 = 1 - 2 * planeNormal.y * planeNormal.y;
  r.e12 =   - 2 * planeNormal.y * planeNormal.z;
  r.e13 =   - 2 * planeNormal.y * planeOffset;

  r.e20 =   - 2 * planeNormal.z * planeNormal.x;
  r.e21 =   - 2 * planeNormal.z * planeNormal.y;
  r.e22 = 1 - 2 * planeNormal.z * planeNormal.z;
  r.e23 =   - 2 * planeNormal.z * planeOffset;

  r.e30 = 0.0;
  r.e31 = 0.0;
  r.e32 = 0.0;
  r.e33 = 1.0;
}

void Mat4CubemapMatrixStd(mat4& r,const unsigned int face)
{
  switch (face){
  case 0:
    memcpy((void*)&r,(void*)&faces[0],sizeof(mat4));
    break;

  case 1:
    memcpy((void*)&r,(void*)&faces[1],sizeof(mat4));
    break;

  case 2:
    memcpy((void*)&r,(void*)&faces[2],sizeof(mat4));
    break;

  case 3:
    memcpy((void*)&r,(void*)&faces[3],sizeof(mat4));
    break;

  case 4:
    memcpy((void*)&r,(void*)&faces[4],sizeof(mat4));
    break;

  default:
    memcpy((void*)&r,(void*)&faces[5],sizeof(mat4));
    break;
  }
}

void Mat4CubemapProjectionMatStd(mat4& r,const float zNear, const float zFar, const int d3dStyle)
{
  r.e00 = 1.0;
  r.e01 = 0.0;
  r.e02 = 0.0;
  r.e03 = 0.0;

  r.e10 = 0.0;
  r.e11 = 1.0;
  r.e12 = 0.0;
  r.e13 = 0.0;

  r.e20 = 0.0;
  r.e21 = 0.0;
  r.e22 = (zFar + zNear) / (zFar - zNear);
  r.e23 = -(2 * zFar * zNear) / (zFar - zNear);

  r.e30 = 0.0;
  r.e31 = 0.0;
  r.e32 = 1.0;
  r.e33 = 0.0;

  if (d3dStyle){
    r.e22 = 0.5f * (r.e22 + r.e32);
    r.e23 = 0.5f * (r.e23 + r.e33);
  } else {
    r.e11 = -1;
  }
}

void Mat4LookAtStd(mat4& r,const vec3& from,const vec3& at)
{
  vec3 z = normalize(at - from);
  vec3 x = normalize(vec3(z.z, 0, -z.x));
  vec3 y = normalize(cross(z, x));

  r.e00 = x.x;
  r.e01 = x.y;
  r.e02 = x.z;
  r.e03 = 0.0;

  r.e10 = y.x;
  r.e11 = y.y;
  r.e12 = y.z;
  r.e13 = 0.0;

  r.e20 = z.x;
  r.e21 = z.y;
  r.e22 = z.z;
  r.e23 = 0.0;

  r.e30 = 0.0;
  r.e31 = 0.0;
  r.e32 = 0.0;
  r.e33 = 1.0;

  r.translate(-from);
}

void Mat4GlToD3dProjectionMatStd(mat4& r,const mat4& m)
{
  r = m;

  r.e20 = 0.5f * (m.e20 + m.e30);
  r.e21 = 0.5f * (m.e21 + m.e31);
  r.e22 = 0.5f * (m.e22 + m.e32);
  r.e23 = 0.5f * (m.e23 + m.e33);
}

