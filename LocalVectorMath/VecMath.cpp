#include <VecMath.h>

// XXX: could be changed back to keeping all classes online
//      with compile section if desired????? --> probably should be
//      eg. fcn_vec
//          fcn_asm
//          fcn_asmchk
//    Requires one last pass through the file.
// XXX: Tan/Binorm calc additions required
// XXX: Check for multi-threaded implementation activities (should be handled by OS)

/* -----------------------------------------------------------
 * Global Variables
 * ----------------------------------------------------------- */

const float fZero  = 0.0f;
const float fOne   = 1.0f;

/* -----------------------------------------------------------
 * Local Variables
 * ----------------------------------------------------------- */

static unsigned int _except_code;

#if defined(_x86) && defined(_USE_SIMD) && defined(_MS)

/* -----------------------------------------------------------
 * Microsoft floating point exception method
 * ----------------------------------------------------------- */

static int fpieee_handler(_FPIEEE_RECORD* pieee)
{
	if ( pieee->Cause.InvalidOperation && _FpCodeDivide == pieee->Operation && 0.0f == pieee->Operand2.Value.Fp32Value )
	{
		pieee->Result.Value.Fp32Value = 0.0f;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

  _except_code = 0 |
    (pieee->Cause.Inexact          ? (unsigned int)fpInexact          : 0) |
    (pieee->Cause.Underflow        ? (unsigned int)fpUnderflow        : 0) |
    (pieee->Cause.Overflow         ? (unsigned int)fpOverflow         : 0) |
    (pieee->Cause.ZeroDivide       ? (unsigned int)fpZeroDivide       : 0) |
    (pieee->Cause.InvalidOperation ? (unsigned int)fpInvalidOperation : 0);

  return EXCEPTION_EXECUTE_HANDLER;
}

// Error handler for Microsoft IEEE error management

enum FpErrorClass { fpInexact=1,fpUnderflow,fpOverflow,fpZeroDivide,fpInvalidOperation };

#endif

/* -----------------------------------------------------------
 * 16-bit float as fixed-point integer format
 * ----------------------------------------------------------- */

half::half(const float x)
{
  unsigned int i = *((unsigned int *) &x);
  int e = ((i >> 23) & 0xFF) - 112;
  int m =  i & 0x007FFFFF;

  sh = (i >> 16) & 0x8000;
  if (e <= 0)
    {
      // Denormed half
      m = ((m | 0x00800000) >> (1 - e)) + 0x1000;
      sh |= (m >> 13);
    }
  else if (e == 255 - 112)
    {
      sh |= 0x7C00;
      if (m != 0){
	// NAN
	m >>= 13;
	sh |= m | (m == 0);
      }
    }
  else
    {
      m += 0x1000;
      if (m & 0x00800000){
	// Mantissa overflow
	m = 0;
	e++;
      }
      if (e >= 31)
	{
	  // Exponent overflow
	  sh |= 0x7C00;
	}
      else
	{
	  sh |= (e << 10) | (m >> 13);
	}
    }
}

half::operator float () const
{
  unsigned int s = (sh & 0x8000) << 16;
  unsigned int e = (sh >> 10) & 0x1F;
  unsigned int m = sh & 0x03FF;

  if (e == 0)
    {
      // +/- 0
      if (m == 0) return *((float *) &s);

      // Denorm
      while ((m & 0x0400) == 0){
	m += m;
	e--;
      }
      e++;
      m &= ~0x0400;
    }
  else if (e == 31)
    {
      // INF / NAN
      s |= 0x7F800000 | (m << 13);
      return *((float *) &s);
    }

  s |= ((e + 112) << 23) | (m << 13);
  return *((float *) &s);
}

/* -----------------------------------------------------------
 * Floating point support methods
 * ----------------------------------------------------------- */

#if defined(__No_SIMD)

float lerp(const float u, const float v, const float x) { return u * (1 - x) + v * x; }
float sqr(float x) { return x * x; }

#else

// Wrapper methods

float lerp(const float u,const float v,const float step) { return FloatLerpAsm(u,v,step); }
float sqr (const float u)                                { return FloatSqrAsm(u);         }

#endif

/* -----------------------------------------------------------
 * 2D single-precision floating-point vector
 * ----------------------------------------------------------- */

#if defined(__No_SIMD)

void vec2::operator += (const vec2 &v) { x += v.x; y += v.y; }
void vec2::operator += (const float s) { x += s; y += s;     }
void vec2::operator -= (const vec2 &v) { x -= v.x; y -= v.y; }
void vec2::operator -= (const float s) { x -= s; y -= s;     }
void vec2::operator *= (const vec2 &v) { x *= v.x; y *= v.y; }
void vec2::operator *= (const float s) { x *= s;   y *= s;   }
void vec2::operator /= (const vec2 &v) { x /= v.x; y /= v.y; }
void vec2::operator /= (const float s) { x /= s;   y /= s;   }

vec2 operator + (const vec2 &u, const vec2 &v) { return vec2(u.x + v.x, u.y + v.y); }
vec2 operator + (const vec2 &v, const float s) { return vec2(v.x + s, v.y + s);     }
vec2 operator - (const vec2 &u, const vec2 &v) { return vec2(u.x - v.x, u.y - v.y); }
vec2 operator - (const vec2 &v, const float s) { return vec2(v.x - s, v.y - s);     }
vec2 operator - (const vec2 &v)                { return vec2(-v.x, -v.y);           }
vec2 operator * (const vec2 &u, const vec2 &v) { return vec2(u.x * v.x, u.y * v.y); }
vec2 operator * (const float s, const vec2 &v) { return vec2(v.x * s, v.y * s);     }
vec2 operator * (const vec2 &v, const float s) { return vec2(v.x * s, v.y * s);     }
vec2 operator / (const vec2 &u, const vec2 &v) { return vec2(u.x / v.x, u.y / v.y); }
vec2 operator / (const vec2 &v, const float s) { return vec2(v.x / s, v.y / s);     }

vec2  lerp     (const vec2 &u, const vec2 &v, const float x) { return u * (1 - x) + v * x;                     }
vec2  sqr      (const vec2 &v)                               { return v * v;                                   }
vec2  normalize(const vec2 &v)                               { return v / (float)sqrtf(v.x * v.x + v.y * v.y); }
float dot      (const vec2 &u, const vec2 &v)                { return u.x * v.x + u.y * v.y;                   }
float length   (const vec2 &v)                               { return sqrtf(v.x * v.x + v.y * v.y);            }

#else

void vec2::operator += (const vec2& v) { Vec2AddAsm(*this,*this,v);           }
void vec2::operator += (const float s) { Vec2AddFloatAsm(*this,*this,s);      }
void vec2::operator -= (const vec2& v) { Vec2SubtractAsm(*this,*this,v);      }
void vec2::operator -= (const float s) { Vec2SubtractFloatAsm(*this,*this,s); }
void vec2::operator *= (const vec2& v) { Vec2MultiplyAsm(*this,*this,v);      }
void vec2::operator *= (const float s) { Vec2MultiplyFloatAsm(*this,*this,s); }
void vec2::operator /= (const vec2& v) { Vec2DivideAsm(*this,*this,v);        }
void vec2::operator /= (const float s) { Vec2DivideFloatAsm(*this,*this,s);   }

vec2  operator + (const vec2& u,const vec2& v) { vec2 r; Vec2AddAsm(r,u,v);           return r; }
vec2  operator + (const vec2& u,const float s) { vec2 r; Vec2AddFloatAsm(r,u,s);      return r; }
vec2  operator - (const vec2& u,const vec2& v) { vec2 r; Vec2SubtractAsm(r,u,v);      return r; }
vec2  operator - (const vec2& u,const float s) { vec2 r; Vec2SubtractFloatAsm(r,u,s); return r; }
vec2  operator - (const vec2& u)               { vec2 r; Vec2NegateAsm(r,u);          return r; }
vec2  operator * (const vec2& u,const vec2& v) { vec2 r; Vec2MultiplyAsm(r,u,v);      return r; }
vec2  operator * (const vec2& u,const float s) { vec2 r; Vec2MultiplyFloatAsm(r,u,s); return r; }
vec2  operator * (const float s,const vec2& v) { vec2 r; Vec2FloatMultiplyAsm(r,s,v); return r; }
vec2  operator / (const vec2& u,const vec2& v) { vec2 r; Vec2DivideAsm(r,u,v);        return r; }
vec2  operator / (const vec2& u,const float s) { vec2 r; Vec2DivideFloatAsm(r,u,s);   return r; }

vec2  lerp       (const vec2& u,const vec2& v,const float step) { vec2 r; Vec2LerpAsm(r,u,v,step); return r; }
vec2  sqr        (const vec2& u)                                { vec2 r; Vec2SqrAsm(r,u);         return r; }
vec2  normalize  (const vec2& v)                                { vec2 r; Vec2NormalizeAsm(r,v);   return r; }
float dot        (const vec2& u,const vec2& v)                  { return Vec2DotAsm(u,v);                    }
float length     (const vec2& u)                                { return Vec2LengthAsm(u);                   }

#endif

bool operator == (const vec2 &u, const vec2 &v){ return (u.x == v.x && u.y == v.y); }
bool operator != (const vec2 &u, const vec2 &v){ return (u.x != v.x || u.y != v.y); }

/* -----------------------------------------------------------
 * 3D single-precision floating-point vector
 * ----------------------------------------------------------- */

#if defined(__No_SIMD)

void vec3::operator += (const vec3& v) { x += v.x; y += v.y; z += v.z; }
void vec3::operator += (const float s) { x += s;   y += y;   z += z;   }
void vec3::operator -= (const vec3& v) { x -= v.x; y -= v.y; z -= v.z; }
void vec3::operator -= (const float s) { x -= s;   y -= s;   z -= s;   }
void vec3::operator *= (const vec3& v) { x *= v.x; y *= v.y; z *= v.z; }
void vec3::operator *= (const float s) { x *= s;   y *= s;   z *= z;   }
void vec3::operator /= (const vec3& v) { x /= v.x; y /= v.y; z /= v.z; }
void vec3::operator /= (const float s) { x /= s;   y /= s;   z /= s;   }

vec3 operator + (const vec3& u, const vec3& v) { return vec3(u.x + v.x,u.y + v.y,u.z + v.z); }
vec3 operator + (const vec3& v, const float s) { return vec3(v.x+s,v.y+s,v.z+s);             }
vec3 operator + (const float s, const vec3& v) { return vec3(v.x+s,v.y+s,v.z+s);             }
vec3 operator - (const vec3& u, const vec3& v) { return vec3(u.x-v.x,u.y-v.y,u.z-v.z);       }
vec3 operator - (const vec3& v, const float s) { return vec3(v.x-s,v.y-s,v.z-s);             }
vec3 operator - (const vec3& v)                { return vec3(-v.x,-v.y,-v.z);                }
vec3 operator - (const float s, const vec3& v) { return vec3(s-v.x,s-v.y,s-v.z);             }
vec3 operator * (const vec3& u, const vec3& v) { return vec3(u.x*v.x,u.y*v.y,u.z*v.z);       }
vec3 operator * (const float s, const vec3& v) { return vec3(v.x*s,v.y*s,v.z*s);             }
vec3 operator * (const vec3& v, const float s) { return vec3(v.x*s,v.y*s,v.z*s);             }
vec3 operator / (const vec3& u, const vec3& v) { return vec3(u.x/v.x,u.y/v.y,u.z/v.z);       }
vec3 operator / (const vec3& v, const float s) { return vec3(v.x/s,v.y/s,v.z/s);             }

vec3  lerp     (const vec3 &u, const vec3 &v, const float x) { return u * (1 - x) + v * x; }
vec3  sqr      (const vec3 &v) { return v * v; }
vec3  normalize(const vec3 &v) { return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
vec3  cross    (const vec3 &u, const vec3 &v)
  { return vec3(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x); }

float dot      (const vec3& u, const vec3& v) { return u.x * v.x + u.y * v.y + u.z * v.z;       }
float length   (const vec3 &v)                { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);}

#else

void vec3::operator += (const vec3& v) { Vec3AddAsm(*this,*this,v);           }
void vec3::operator += (const float s) { Vec3AddFloatAsm(*this,*this,s);      }
void vec3::operator -= (const vec3& v) { Vec3SubtractAsm(*this,*this,v);      }
void vec3::operator -= (const float s) { Vec3SubtractFloatAsm(*this,*this,s); }
void vec3::operator *= (const vec3& v) { Vec3MultiplyAsm(*this,*this,v);      }
void vec3::operator *= (const float s) { Vec3MultiplyFloatAsm(*this,*this,s); }
void vec3::operator /= (const vec3& v) { Vec3DivideAsm(*this,*this,v);        }
void vec3::operator /= (const float s) { Vec3DivideFloatAsm(*this,*this,s);   }

vec3  operator + (const vec3& u,const vec3& v) { vec3 r; Vec3AddAsm(r,u,v);           return r; }
vec3  operator + (const vec3& u,const float s) { vec3 r; Vec3AddFloatAsm(r,u,s);      return r; }
vec3  operator + (const float s,const vec3& v) { vec3 r; Vec3FloatAddAsm(r,s,v);      return r; }
vec3  operator - (const vec3& u,const vec3& v) { vec3 r; Vec3SubtractAsm(r,u,v);      return r; }
vec3  operator - (const vec3& u,const float s) { vec3 r; Vec3SubtractFloatAsm(r,u,s); return r; }
vec3  operator - (const vec3& v)               { vec3 r; Vec3NegateAsm(r,v);          return r; }
vec3  operator - (const float s,const vec3& v) { vec3 r; Vec3FloatSubtractAsm(r,s,v); return r; }
vec3  operator * (const vec3& u,const vec3& v) { vec3 r; Vec3MultiplyAsm(r,u,v);      return r; }
vec3  operator * (const vec3& u,const float s) { vec3 r; Vec3MultiplyFloatAsm(r,u,s); return r; }
vec3  operator * (const float s,const vec3& v) { vec3 r; Vec3FloatMultiplyAsm(r,s,v); return r; }
vec3  operator / (const vec3& u,const vec3& v) { vec3 r; Vec3DivideAsm(r,u,v);        return r; }
vec3  operator / (const vec3& u,const float s) { vec3 r; Vec3DivideFloatAsm(r,u,s);   return r; }

vec3  lerp       (const vec3& u,const vec3& v,const float x) { vec3 r; Vec3LerpAsm(r,u,v,x);    return r; }
vec3  sqr        (const vec3& v)                             { vec3 r; Vec3SqrAsm(r,v);         return r; }
vec3  normalize  (const vec3& v)                             { vec3 r; Vec3NormalizeAsm(r,v);   return r; }
vec3  cross      (const vec3& u,const vec3& v)               { vec3 r; Vec3CrossAsm(r,u,v);     return r; }
float dot        (const vec3& u,const vec3& v)               { return Vec3DotAsm(u,v);                    }
float length     (const vec3& v)                             { return Vec3LengthAsm(v);                   }

#endif

bool operator == (const vec3 &u, const vec3 &v) {return (u.x == v.x && u.y == v.y && u.z == v.z);}
bool operator != (const vec3 &u, const vec3 &v) {return (u.x != v.x || u.y != v.y || u.z != v.z);}

/* ---------------------------------------------
 * 4D single-precision floating-point vector
 * --------------------------------------------- */

#if defined(__No_SIMD)

void vec4::operator += (const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
void vec4::operator += (const float s) { x += s;   y += y;   z += z;   w += s;   }
void vec4::operator -= (const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w += v.w; }
void vec4::operator -= (const float s) { x -= s;   y -= s;   z -= s;   w += s;   }
void vec4::operator *= (const vec4& v) { x *= v.x; y *= v.y; z *= v.z; w += v.w; }
void vec4::operator *= (const float s) { x *= s;   y *= s;   z *= z;   w += w;   }
void vec4::operator /= (const vec4& v) { x /= v.x; y /= v.y; z /= v.z; w += v.w; }
void vec4::operator /= (const float s) { x /= s;   y /= s;   z /= s;   w += w;   }

vec4 operator + (const vec4& u,const vec4& v) { return vec4(u.x+v.x,u.y+v.y,u.z+v.z,u.w+v.w); }
vec4 operator + (const vec4& v,const float s) { return vec4(v.x+s,v.y+s,v.z+s,v.w+s);         }
vec4 operator + (const float s,const vec4& v) { return vec4(v.x+s,v.y+s,v.z+s,v.w+s);         }
vec4 operator - (const vec4& u,const vec4& v) { return vec4(u.x-v.x,u.y-v.y,u.z-v.z,u.w-v.w); }
vec4 operator - (const vec4& v,const float s) { return vec4(v.x-s,v.y-s,v.z-s,v.w-s);         }
vec4 operator - (const vec4& v)               { return vec4(-v.x,-v.y,-v.z,-v.w);             }
vec4 operator - (const float s,const vec4& v) { return vec4(s-v.x,s-v.y,s-v.z,s-v.w);         }
vec4 operator * (const vec4& u,const vec4& v) { return vec4(u.x*v.x,u.y*v.y,u.z*v.z,u.w*v.w); }
vec4 operator * (const vec4& u,const float s) { return vec4(u.x*s,u.y*s,u.z*s,u.w*s);         }
vec4 operator * (const float s,const vec4& v) { return vec4(v.x*s,v.y*s,v.z*s,v.w*s);         }
vec4 operator / (const vec4& u,const vec4& v) { return vec4(u.x/v.x,u.y/v.y,u.z/v.z,u.w/v.w); }
vec4 operator / (const vec4& v,const float s) { return vec4(v.x/s,v.y/s,v.z/s,v.w/s);         }

vec4 lerp(const vec4& u, const vec4 &v, const float x) { return u * (1 - x) + v * x; }
vec4 sqr (const vec4& v) { return v * v; }
vec4 normalize(const vec4& v) { return (v / sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w)); }
vec4 cross(const vec4 &u,const vec4 &v)
  { return vec4(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x,0.0f); }

float dot(const vec4 &u, const vec4 &v){ return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;}
float length(const vec4 &v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }

#else

void vec4::operator += (const vec4& v) { Vec4AddAsm(*this,*this,v);           }
void vec4::operator += (const float s) { Vec4AddFloatAsm(*this,*this,s);      }
void vec4::operator -= (const vec4& v) { Vec4SubtractAsm(*this,*this,v);      }
void vec4::operator -= (const float s) { Vec4SubtractFloatAsm(*this,*this,s); }
void vec4::operator *= (const vec4& v) { Vec4MultiplyAsm(*this,*this,v);      }
void vec4::operator *= (const float s) { Vec4MultiplyFloatAsm(*this,*this,s); }
void vec4::operator /= (const vec4& v) { Vec4DivideAsm(*this,*this,v);        }
void vec4::operator /= (const float s) { Vec4DivideFloatAsm(*this,*this,s);   }

vec4  operator + (const vec4& u,const vec4& v) { vec4 r; Vec4AddAsm(r,u,v);           return r; }
vec4  operator + (const vec4& u,const float s) { vec4 r; Vec4AddFloatAsm(r,u,s);      return r; }
vec4  operator - (const vec4& u,const vec4& v) { vec4 r; Vec4SubtractAsm(r,u,v);      return r; }
vec4  operator - (const vec4& u,const float s) { vec4 r; Vec4SubtractFloatAsm(r,u,s); return r; }
vec4  operator - (const vec4& v)               { vec4 r; Vec4NegateAsm(r,v);          return r; }
vec4  operator - (const float s,const vec4& v) { vec4 r; Vec4FloatSubtractAsm(r,s,v); return r; }
vec4  operator * (const vec4& u,const vec4& v) { vec4 r; Vec4MultiplyAsm(r,u,v);      return r; }
vec4  operator * (const vec4& u,const float s) { vec4 r; Vec4MultiplyFloatAsm(r,u,s); return r; }
vec4  operator * (const float s,const vec4& v) { vec4 r; Vec4FloatMultiplyAsm(r,s,v); return r; }
vec4  operator / (const vec4& u,const vec4& v) { vec4 r; Vec4DivideAsm(r,u,v);        return r; }
vec4  operator / (const vec4& u,const float s) { vec4 r; Vec4DivideFloatAsm(r,u,s);   return r; }

vec4  lerp       (const vec4& u,const vec4& v,const float x) { vec4 r; Vec4LerpAsm(r,u,v,x);  return r; }
vec4  sqr        (const vec4& v)                             { vec4 r; Vec4SqrAsm(r,v);       return r; }
vec4  normalize  (const vec4& v)                             { vec4 r; Vec4NormalizeAsm(r,v); return r; }
vec4  cross      (const vec4& u,const vec4& v)               { vec4 r; Vec4CrossAsm(r,u,v);   return r; }
float dot        (const vec4& u,const vec4& v)               { return Vec4DotAsm(u,v);                  }
float length     (const vec4& v)                             { return Vec4LengthAsm(v);                 }

#endif

bool operator == (const vec4 &u, const vec4 &v) {return (u.x == v.x && u.y == v.y && u.z == v.z && u.w == v.w);}
bool operator != (const vec4 &u, const vec4 &v) {return (u.x != v.x || u.y != v.y || u.z != v.z || u.w != v.w);}

/* ---------------------------------------------
 * 2x2 matrix
 * --------------------------------------------- */

#if defined(__No_SIMD)

mat2 operator + (const mat2 &m, const mat2 &n)
{
  return mat2(m.e00 + n.e00,
	      m.e01 + n.e01,
	      m.e10 + n.e10,
	      m.e11 + n.e11);
}

mat2 operator - (const mat2 &m, const mat2 &n)
{
  return mat2(m.e00 - n.e00,
	      m.e01 - n.e01,
	      m.e10 - n.e10,
	      m.e11 - n.e11);
}

mat2 operator - (const mat2 &m)
{
  return mat2(-m.e00, -m.e01, -m.e10, -m.e11);
}

mat2 operator * (const mat2 &m, const mat2 &n)
{
  return mat2(m.e00 * n.e00 + m.e01 * n.e10,
	      m.e00 * n.e01 + m.e01 * n.e11,
	      m.e10 * n.e00 + m.e11 * n.e10,
	      m.e10 * n.e01 + m.e11 * n.e11);
}

vec2 operator * (const mat2 &m, const vec2 &v)
{
  return vec2(m.e00 * v.x + m.e01 * v.y,
	      m.e10 * v.x + m.e11 * v.y);
}

mat2 operator * (const mat2 &m, const float x)
{
  mat2 mat;
  mat.e00 = m.e00 * x;
  mat.e01 = m.e01 * x;
  mat.e10 = m.e10 * x;
  mat.e11 = m.e11 * x;
  return mat;
}

mat2 m2_identity()
{
  return mat2(1,0, 0,1);
}

mat2 m2_transpose(const mat2 &m)
{
  return mat2(m.e00, m.e10,
	      m.e01, m.e11);
}

mat2 m2_rotate(const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  return mat2(cosA, -sinA,
	      sinA,  cosA);
}

mat2 m2_scale(const float x, const float y)
{
  return mat2(x,0, 0,y);
}

#else

mat2 operator +  (const mat2& m, const mat2& n) { mat2 r; Mat2AddAsm(r,m,n);           return r; }
mat2 operator -  (const mat2& m, const mat2& n) { mat2 r; Mat2SubtractAsm(r,m,n);      return r; }
mat2 operator -  (const mat2& m)                { mat2 r; Mat2NegateAsm(r,m);          return r; }
mat2 operator *  (const mat2& m, const mat2& n) { mat2 r; Mat2MultiplyAsm(r,m,n);      return r; }
vec2 operator *  (const mat2& m, const vec2& v) { vec2 r; Mat2MultiplyVecAsm(r,m,v);   return r; }
mat2 operator *  (const mat2& m, const float s) { mat2 r; Mat2MultiplyFloatAsm(r,m,s); return r; }
mat2 m2_identity ()                             { mat2 r; Mat2IdentityAsm(r);          return r; }
mat2 m2_transpose(const mat2& m)                { mat2 r; Mat2TransposeAsm(r,m);       return r; }
mat2 m2_rotate   (const float s)                { mat2 r; Mat2RotateAsm(r,s);          return r; }
mat2 m2_scale    (const float x,const float y)  { mat2 r; Mat2ScaleAsm(r,x,y);         return r; }

#endif

/* ---------------------------------------------
 * 3x3 matrix
 * --------------------------------------------- */

#if defined(__No_SIMD)

mat3 operator + (const mat3 &m, const mat3 &n)
{
  return mat3(m.e00 + n.e00, m.e01 + n.e01, m.e02 + n.e02,
	      m.e10 + n.e10, m.e11 + n.e11, m.e12 + n.e12,
	      m.e20 + n.e20, m.e21 + n.e21, m.e22 + n.e22);
}

mat3 operator - (const mat3 &m, const mat3 &n)
{
  return mat3(m.e00 - n.e00, m.e01 - n.e01, m.e02 - n.e02,
	      m.e10 - n.e10, m.e11 - n.e11, m.e12 - n.e12,
	      m.e20 - n.e20, m.e21 - n.e21, m.e22 - n.e22);
}

mat3 operator - (const mat3 &m)
{
  return mat3(-m.e00, -m.e01, -m.e02,
	      -m.e10, -m.e11, -m.e12,
	      -m.e20, -m.e21, -m.e22);
}

mat3 operator * (const mat3& m, const mat3& n)
{
  mat3 r;
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

  return r;
}

vec3 operator * (const mat3 &m, const vec3 &v)
{
  return vec3(m.e00 * v.x + m.e01 * v.y + m.e02 * v.z,
	      m.e10 * v.x + m.e11 * v.y + m.e12 * v.z,
	      m.e20 * v.x + m.e21 * v.y + m.e22 * v.z);
}

mat3 operator * (const mat3 &m, const float x)
{
  mat3 r;

  float* fResult = (float*)&r;
  float* fBase   = (float*)&m;

  for( unsigned int i=0 ; i < sizeof(mat3)/sizeof(float) ; ++i ) fResult[i] = fBase[i] * x;

  r.n03 = r.n13 = r.n23 = 1.0f;

  return r;

}

mat3 operator ! (const mat3 &m)
{
  float p0 = m.e11 * m.e22 - m.e21 * m.e12;
  float p1 = m.e12 * m.e20 - m.e10 * m.e22;
  float p2 = m.e10 * m.e21 - m.e11 * m.e20;

  float invDet = 1.0f / (m.e00 * p0 + m.e01 * p1 + m.e02 * p2);

  return mat3(p0,
	      m.e21 * m.e02 - m.e01 * m.e22,
	      m.e01 * m.e12 - m.e11 * m.e02,
	      p1,
	      m.e00 * m.e22 - m.e20 * m.e02,
	      m.e10 * m.e02 - m.e00 * m.e12,
	      p2,
	      m.e20 * m.e01 - m.e00 * m.e21,
	      m.e00 * m.e11 - m.e01 * m.e10) * invDet;
}

mat3 m3_identity()
{
  return mat3(1,0,0, 0,1,0, 0,0,1);
}

mat3 m3_transpose(const mat3& m)
{
  return mat3(m.e00, m.e10, m.e20,
	      m.e01, m.e11, m.e21,
	      m.e02, m.e12, m.e22);
}

mat3 m3_rotateX(const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  return mat3(1, 0,     0,
	      0, cosA, -sinA,
	      0, sinA,  cosA);
}

mat3 m3_rotateY(const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  return mat3(cosA, 0, -sinA,
	      0,    1,  0,
	      sinA, 0,  cosA);
}

mat3 m3_rotateZ(const float angle)
{
  float cosA = cosf(angle), sinA = sinf(angle);

  return mat3(cosA, -sinA, 0,
	      sinA,  cosA, 0,
	      0,     0,    1);
}

mat3 m3_rotateXY(const float angleX, const float angleY)
{
  float cosX = cosf(angleX),
        sinX = sinf(angleX),
        cosY = cosf(angleY),
        sinY = sinf(angleY);

  return mat3( cosY,        0,    -sinY,
	      -sinX * sinY, cosX, -sinX * cosY,
	       cosX * sinY, sinX,  cosX * cosY);
}

mat3 m3_rotateXYZ(const float angleX, const float angleY, const float angleZ)
{
  float cosX = cosf(angleX), sinX = sinf(angleX),
        cosY = cosf(angleY), sinY = sinf(angleY),
        cosZ = cosf(angleZ), sinZ = sinf(angleZ);

  return mat3(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,
	      cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,
	      cosX * sinY,                         sinX,           cosX * cosY);
}

mat3 m3_scale(const float x, const float y, const float z)
{
  return mat3(x,0,0, 0,y,0, 0,0,z);
}

#else

mat3 operator + (const mat3 &m, const mat3 &n) { mat3 r; Mat3AddAsm(r,m,n);             return r; }
mat3 operator - (const mat3 &m, const mat3 &n) { mat3 r; Mat3SubtractAsm(r,m,n);        return r; }
mat3 operator - (const mat3 &m)                { mat3 r; Mat3NegateAsm(r,m);            return r; }
mat3 operator * (const mat3 &m, const mat3 &n) { mat3 r; Mat3MultiplyFPU_Asm(r,m,n);    return r; }
vec3 operator * (const mat3 &m, const vec3 &v) { vec3 r; Mat3MultiplyVecFPU_Asm(r,m,v); return r; }
mat3 operator * (const mat3 &m, const float x) { mat3 r; Mat3MultiplyFloatAsm(r,m,x);   return r; }
mat3 operator ! (const mat3 &m)                { mat3 r; Mat3InverseFPU_Asm(r,m);       return r; }

mat3 m3_identity ()              { mat3 r; Mat3IdentityAsm(r);    return r; }
mat3 m3_transpose(const mat3 &m) { mat3 r; Mat3TransposeAsm(r,m); return r; }
mat3 m3_rotateX  (const float s) { mat3 r; Mat3RotateXAsm(r,s);   return r; }
mat3 m3_rotateY  (const float s) { mat3 r; Mat3RotateYAsm(r,s);   return r; }
mat3 m3_rotateZ  (const float s) { mat3 r; Mat3RotateZAsm(r,s);   return r; }

mat3 m3_rotateXY (const float x,const float y)               { mat3 r; Mat3RotateXYAsm(r,x,y);        return r; }
mat3 m3_rotateXYZ(const float x,const float y,const float z) { mat3 r; Mat3RotateXYZFPU_Asm(r,x,y,z); return r; }
mat3 m3_scale    (const float x,const float y,const float z) { mat3 r; Mat3ScaleAsm(r,x,y,z);         return r; }

#endif

/* ---------------------------------------------
 * 4x4 matrix
 * --------------------------------------------- */

#if defined(__No_SIMD)

void mat4::translate(const vec3& v)
{
  e03 += (v.x * e00 + v.y * e01 + v.z * e02);
  e13 += (v.x * e10 + v.y * e11 + v.z * e12);
  e23 += (v.x * e20 + v.y * e21 + v.z * e22);
  e33 += (v.x * e30 + v.y * e31 + v.z * e32);
}

mat4 operator + (const mat4& m,const mat4& n)
{
  mat4 r;
  float* mp = (float*)&m;
  float* np = (float*)&n;
  float* rp = (float*)&r;

  for( unsigned int i=0 ; i < 16 ; ++i ) rp[i] = mp[i] + np[i];

  return r;
}

mat4 operator - (const mat4& m,const mat4& n)
{
  mat4 r;
  float* mp = (float*)&m;
  float* np = (float*)&n;
  float* rp = (float*)&r;

  for( unsigned int i=0 ; i < 16 ; ++i ) rp[i] = mp[i] - np[i];

  return r;
}

mat4 operator - (const mat4& m)
{
  mat4 r;
  float* mp = (float*)&m;
  float* rp = (float*)&r;

  for( unsigned int i=0 ; i < 16 ; ++i ) rp[i] = -(mp[i]);

  return r;
}

mat4 operator * (const mat4& m,const mat4& n)
{
  mat4 r;
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
  return r;
}

vec4 operator * (const mat4 &m, const vec4 &v)
{
  return vec4(m.e00 * v.x + m.e01 * v.y + m.e02 * v.z + m.e03 * v.w,
	      m.e10 * v.x + m.e11 * v.y + m.e12 * v.z + m.e13 * v.w,
	      m.e20 * v.x + m.e21 * v.y + m.e22 * v.z + m.e23 * v.w,
	      m.e30 * v.x + m.e31 * v.y + m.e32 * v.z + m.e33 * v.w);
}

mat4 operator * (const mat4& m,const float x)
{
  mat4 r;
  float* mp = (float*)&m;
  float* rp = (float*)&r;

  for( unsigned int i=0 ; i < 16 ; ++i ) rp[i] = mp[i] * x;

  return r;
}

mat4 m4_identity()
{
  return mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}

mat4 m4_transpose(const mat4 &m)
{
  return mat4(m.e00, m.e10, m.e20, m.e30,
	      m.e01, m.e11, m.e21, m.e31,
	      m.e02, m.e12, m.e22, m.e32,
	      m.e03, m.e13, m.e23, m.e33);
}

mat4 m4_scale(const float x, const float y, const float z)
{
  return mat4(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
}

// XXX: Implementors note: These matrices need to
//      be visually verified prior to a production release
//

mat4 m4_rotateX(const float angle)
{
  float cosA = cosf(angle),
        sinA = sinf(angle);

  return mat4(1, 0,     0,    0,
	      0, cosA, -sinA, 0,
	      0, sinA,  cosA, 0,
	      0, 0,     0,    1);
}

mat4 m4_rotateY(const float angle)
{
  float cosA = cosf(angle),
        sinA = sinf(angle);

  return mat4(cosA, 0, -sinA, 0,
	      0,    1,  0,    0,
	      sinA, 0,  cosA, 0,
	      0,    0,  0,    1);
}

mat4 m4_rotateZ(const float angle)
{
  float cosA = cosf(angle),
        sinA = sinf(angle);

  return mat4(cosA, -sinA, 0, 0,
	      sinA,  cosA, 0, 0,
	      0,     0,    1, 0,
	      0,     0,    0, 1);
}

mat4 m4_rotateXY(const float angleX, const float angleY)
{
  float cosX = cosf(angleX),
        sinX = sinf(angleX),
        cosY = cosf(angleY),
        sinY = sinf(angleY);

  return mat4(        cosY,    0,        -sinY, 0,
	      -sinX * sinY, cosX, -sinX * cosY, 0,
	       cosX * sinY, sinX,  cosX * cosY, 0,
	                 0,    0,            0, 1);
}

mat4 m4_rotateXYZ(const float angleX, const float angleY, const float angleZ)
{
  float cosX = cosf(angleX),
        sinX = sinf(angleX),
        cosY = cosf(angleY),
        sinY = sinf(angleY),
        cosZ = cosf(angleZ),
        sinZ = sinf(angleZ);

  return mat4(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,  0,
	      cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,  0,
	      cosX * sinY,                         sinX,           cosX * cosY,                       0,
	      0,                                   0,              0,                                 1);
}

mat4 m4_translate(const float x, const float y, const float z)
{
  return mat4(1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1);
}

mat4 m4_translate(const vec3 &v)
{
  return mat4(1,0,0,v.x, 0,1,0,v.y, 0,0,1,v.z, 0,0,0,1);
}

/* Creates an orthographic projection matrix */

mat4 m4_ortho(const float left,
	      const float right,
	      const float top,
	      const float bottom,
	      const float zNear,
	      const float zFar,
	      const bool d3dtype)
{
  float rl = right - left;
  float tb = top - bottom;
  float fn = zFar - zNear;

  mat4 mat(2.0f / rl, 0,         0,         -(right + left) / rl,
	   0,         2.0f / tb, 0,         -(top + bottom) / tb,
	   0,         0,        -2.0f / fn, -(zFar + zNear) / fn,
	   0,         0,         0,         1);

  if (d3dtype){
    mat.e22 = 0.5f * (mat.e22 + mat.e32);
    mat.e23 = 0.5f * (mat.e23 + mat.e33);
  }
  return mat;
}

mat4 m4_ortho(const struct orthoMatrix& s)
{
  return m4_ortho(s.left,s.right,s.top,s.bottom,s.z_near,s.z_far,(bool)s.d3dtype);
}

mat4 m4_perspective(const struct perspectiveMatrix& s)
{
  float w = tanf(0.5f * s.fov);
  float h = (w * s.height) / s.width;

  mat4 mat(1.0f / w, 0,        0, 0,
	   0,        1.0f / h, 0, 0,
	   0,        0,        (s.z_far + s.z_near) / (s.z_far - s.z_near), -(2 * s.z_far * s.z_near) / (s.z_far - s.z_near),
	   0,        0,        1, 0);

  if (s.d3dtype){
    mat.e22 = 0.5f * (mat.e22 + mat.e32);
    mat.e23 = 0.5f * (mat.e23 + mat.e33);
  }
  return mat;
}

mat4 m4_perspectiveX(const float fov,
		     const int width,
		     const int height,
		     const float zNear,
		     const float zFar,
		     const bool d3dStyle)
{
  float w = tanf(0.5f * fov);
  float h = (w * height) / width;

  mat4 mat(1.0f / w, 0,        0, 0,
	   0,        1.0f / h, 0, 0,
	   0,        0,        (zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
	   0,        0,        1, 0);

  if (d3dStyle){
    mat.e22 = 0.5f * (mat.e22 + mat.e32);
    mat.e23 = 0.5f * (mat.e23 + mat.e33);
  }
  return mat;
}

mat4 m4_perspectiveX(const struct perspectiveMatrix& s)
{
  float w = tanf(0.5f * s.fov);
  float h = (w * s.height) / s.width;

  mat4 mat(1.0f / w, 0,        0, 0,
	   0,        1.0f / h, 0, 0,
	   0,        0,        (s.z_far + s.z_near) / (s.z_far - s.z_near), -(2 * s.z_far * s.z_near) / (s.z_far - s.z_near),
	   0,        0,        1, 0);

  if (s.d3dtype){
    mat.e22 = 0.5f * (mat.e22 + mat.e32);
    mat.e23 = 0.5f * (mat.e23 + mat.e33);
  }
  return mat;
}

mat4 m4_shadowMatrix(const vec3 &planeNormal, const float planeOffset, const vec3 &lightPos)
{
  float dist = dot(lightPos, planeNormal) + planeOffset;

  return mat4(dist - lightPos.x * planeNormal.x,
	      - lightPos.x * planeNormal.y,
	      - lightPos.x * planeNormal.z,
	      - lightPos.x * planeOffset,

	      - lightPos.y * planeNormal.x,
	      dist - lightPos.y * planeNormal.y,
	      - lightPos.y * planeNormal.z,
	      - lightPos.y * planeOffset,

	      - lightPos.z * planeNormal.x,
	      - lightPos.z * planeNormal.y,
	      dist - lightPos.z * planeNormal.z,
	      - lightPos.z * planeOffset,

	      - planeNormal.x,
	      - planeNormal.y,
	      - planeNormal.z,
	      dist - planeOffset);
}

mat4 m4_mirrorMatrix(const vec3 &planeNormal, const float planeOffset)
{
  return mat4(1 - 2 * planeNormal.x * planeNormal.x,
	      - 2 * planeNormal.x * planeNormal.y,
	      - 2 * planeNormal.x * planeNormal.z,
	      - 2 * planeNormal.x * planeOffset,

	      - 2 * planeNormal.y * planeNormal.x,
	      1 - 2 * planeNormal.y * planeNormal.y,
	      - 2 * planeNormal.y * planeNormal.z,
	      - 2 * planeNormal.y * planeOffset,

	      - 2 * planeNormal.z * planeNormal.x,
	      - 2 * planeNormal.z * planeNormal.y,
	      1 - 2 * planeNormal.z * planeNormal.z,
	      - 2 * planeNormal.z * planeOffset,

	      0, 0, 0, 1);
}

mat4 m4_cubemapMatrix(const unsigned int face)
{
  switch (face){
  case 0:
    return mat4(0, 0, -1, 0,
		0, 1,  0, 0,
		1, 0,  0, 0,
		0, 0,  0, 1);
  case 1:
    return mat4(0, 0, 1, 0,
		0, 1, 0, 0,
		-1, 0, 0, 0,
		0, 0, 0, 1);
  case 2:
    return mat4(1, 0,  0, 0,
		0, 0, -1, 0,
		0, 1,  0, 0,
		0, 0,  0, 1);
  case 3:
    return mat4(1,  0, 0, 0,
		0,  0, 1, 0,
		0, -1, 0, 0,
		0,  0, 0, 1);
  case 4:
    return mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
  default:
    return mat4(-1, 0,  0, 0,
		0, 1,  0, 0,
		0, 0, -1, 0,
		0, 0,  0, 1);
  }
}

mat4 m4_cubemapProjMat(const float zNear,const float zFar,const int d3dtype)
{
  mat4 mat(1, 0, 0, 0,
	   0, 1, 0, 0,
	   0, 0, (zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
	   0, 0, 1, 0);

  if (d3dtype){
    mat.e22 = 0.5f * (mat.e22 + mat.e32);
    mat.e23 = 0.5f * (mat.e23 + mat.e33);
  } else {
    mat.e11 = -1;
  }

  return mat;
}

mat4 m4_lookAt(const vec3 &from, const vec3 &at)
{
  vec3 z = normalize(at - from);
  vec3 x = normalize(vec3(z.z, 0, -z.x));
  vec3 y = normalize(cross(z, x));
  mat4 mat(x.x, x.y, x.z, 0,
	   y.x, y.y, y.z, 0,
	   z.x, z.y, z.z, 0,
	   0,   0,   0,   1);
  mat.translate(-from);

  return mat;
}

mat4 m4_GlToD3dProjMat(const mat4 &m)
{
  mat4 mat = m;

  mat.e20 = 0.5f * (m.e20 + m.e30);
  mat.e21 = 0.5f * (m.e21 + m.e31);
  mat.e22 = 0.5f * (m.e22 + m.e32);
  mat.e23 = 0.5f * (m.e23 + m.e33);

  return mat;
}

#else

void mat4::translate  (const vec3& v)                             { Mat4TranslateMatrixAsm(*this,*this,v);   }

mat4 operator +       (const mat4& m, const mat4& n)              { mat4 r; Mat4AddAsm(r,m,n);                return r; }
mat4 operator -       (const mat4& m, const mat4& n)              { mat4 r; Mat4SubtractAsm(r,m,n);           return r; }
mat4 operator -       (const mat4& m)                             { mat4 r; Mat4NegateAsm(r,m);               return r; }
mat4 operator *       (const mat4& m, const mat4& n)              { mat4 r; Mat4MultiplyFPU_Asm(r,m,n);       return r; }
vec4 operator *       (const mat4& m, const vec4& v)              { vec4 r; Mat4MultiplyVecFPU_Asm(r,m,v);    return r; }
mat4 operator *       (const mat4& m, const float x)              { mat4 r; Mat4MultiplyFloatAsm(r,m,x);      return r; }

mat4 m4_identity ()                                               { mat4 r; Mat4IdentityAsm(r);               return r; }
mat4 m4_transpose     (const mat4 &m)                             { mat4 r; Mat4TransposeAsm(r,m);            return r; }
mat4 m4_scale         (const float x,const float y,const float z) { mat4 r; Mat4ScaleAsm(r,x,y,z);            return r; }
mat4 m4_rotateX       (const float x)                             { mat4 r; Mat4RotateXAsm(r,x);              return r; }
mat4 m4_rotateY       (const float y)                             { mat4 r; Mat4RotateYAsm(r,y);              return r; }
mat4 m4_rotateZ       (const float z)                             { mat4 r; Mat4RotateZAsm(r,z);              return r; }
mat4 m4_rotateXY      (const float x,const float y)               { mat4 r; Mat4RotateXYAsm(r,x,y);           return r; }
mat4 m4_rotateXYZ     (const float x,const float y,const float z) { mat4 r; Mat4RotateXYZFPU_Asm(r,x,y,z);    return r; }
mat4 m4_translate     (const float x,const float y,const float z) { mat4 r; Mat4TranslateFloatAsm(r,x,y,z);   return r; }
mat4 m4_translate     (const vec3& v)                             { mat4 r; Mat4TranslateVecAsm(r,v);         return r; }
mat4 m4_ortho         (const struct orthoMatrix& s)               { mat4 r; Mat4OrthoStructAsm(r,s);          return r; }
mat4 m4_perspectiveX  (const struct perspectiveMatrix& s)         { mat4 r; Mat4PerspectiveXAsm(r,s);         return r; }
mat4 m4_cubemapMatrix (const unsigned int face)                   { mat4 r; Mat4CubemapMatrixAsm(r,face);     return r; }
mat4 m4_lookAt        (const vec3& from,const vec3& at)           { mat4 r; Mat4LookAtFPU_Asm(r,from,at);     return r; }
mat4 m4_GlToD3dProjMat(const mat4& m)                             { mat4 r; Mat4GlToD3dProjectionMatAsm(r,m); return r; }

mat4 m4_mirrorMatrix(const vec3& planeNormal,const float planeOffset)                     { mat4 r; Mat4MirrorMatrixAsm(r,planeNormal,planeOffset);          return r; }
mat4 m4_shadowMatrix(const vec3& planeNormal,const float planeOffset,const vec3& lightPos){ mat4 r; Mat4ShadowMatrixAsm(r,planeNormal,planeOffset,lightPos); return r; }
mat4 m4_cubemapProjMat(const float zNear,const float zFar,const int d3dtype)              { mat4 r; Mat4CubemapProjectionMatAsm(r,zNear,zFar,d3dtype);       return r; }
#endif

/* ---------------------------------------------
 * Vector min/max methods
 * --------------------------------------------- */

vec2 min(const vec2 &u, const vec2 &v)
{
  return vec2((u.x < v.x)? u.x : v.x, (u.y < v.y)? u.y : v.y);
}

vec2 max(const vec2 &u, const vec2 &v)
{
  return vec2((u.x > v.x)? u.x : v.x, (u.y > v.y)? u.y : v.y);
}

vec3 min(const vec3 &u, const vec3 &v)
{
  return vec3((u.x < v.x)? u.x : v.x, (u.y < v.y)? u.y : v.y, (u.z < v.z)? u.z : v.z);
}

vec3 max(const vec3 &u, const vec3 &v)
{
  return vec3((u.x > v.x)? u.x : v.x, (u.y > v.y)? u.y : v.y, (u.z > v.z)? u.z : v.z);
}

vec4 min(const vec4 &u, const vec4 &v)
{
  return vec4((u.x < v.x)? u.x : v.x, (u.y < v.y)? u.y : v.y, (u.z < v.z)? u.z : v.z, (u.w < v.w)? u.w : v.w);
}

vec4 max(const vec4 &u, const vec4 &v)
{
  return vec4((u.x > v.x)? u.x : v.x, (u.y > v.y)? u.y : v.y, (u.z > v.z)? u.z : v.z, (u.w > v.w)? u.w : v.w);
}

/* ---------------------------------------------
 * Sign methods
 * --------------------------------------------- */

int signP(const int x)
{
  return 1 - 2 * (x < 0);
}

int signN(const int x)
{
  return 2 * (x > 0) - 1;
}

int sign(const int x)
{
  return (x > 0) - (x < 0);
}

float sign(const float x)
{
  return (x < 0)? -1.0f : 1.0f;
}

vec2 sign(const vec2 &v)
{
  return vec2((v.x < 0)? -1.0f : 1.0f, (v.y < 0)? -1.0f : 1.0f);
}

vec3 sign(const vec3 &v)
{
  return vec3((v.x < 0)? -1.0f : 1.0f, (v.y < 0)? -1.0f : 1.0f, (v.z < 0)? -1.0f : 1.0f);
}

vec4 sign(const vec4 &v)
{
  return vec4((v.x < 0)? -1.0f : 1.0f, (v.y < 0)? -1.0f : 1.0f, (v.z < 0)? -1.0f : 1.0f, (v.w < 0)? -1.0f : 1.0f);
}

/* ---------------------------------------------
 * Color management methods
 * --------------------------------------------- */

vec3 rgbeToRGB(unsigned char *rgbe)
{
  if (rgbe[3])
    return vec3(rgbe[0], rgbe[1], rgbe[2]) * ldexpf(1.0f, rgbe[3] - (int) (128 + 8));
  else
    return vec3(0,0,0);
}

unsigned int toRGBA(const vec4 &u)
{
  return (int(u.x * 255) | (int(u.y * 255) << 8) | (int(u.z * 255) << 16) | (int(u.w * 255) << 24));
}

unsigned int toBGRA(const vec4 &u)
{
  return (int(u.z * 255) | (int(u.y * 255) << 8) | (int(u.x * 255) << 16) | (int(u.w * 255) << 24));
}

