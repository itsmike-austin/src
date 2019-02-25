#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

float fast_cos(const float x)
{
  float x_sqr = x*x;
  float res   = -2.605e-07;

  res *= x_sqr;
  res += (float)2.47609e-05;
  res *= x_sqr;
  res -= (float)1.3888397e-03;
  res *= x_sqr;
  res += (float)4.16666418e-02;
  res *= x_sqr;
  res -= (float)4.999999963e-01;
  res *= x_sqr;
  res += 1.0f;
  return res;
}

float fone = 1.0f;
float fcon = -2.605e-07;
float cosa[4] = {
  2.47609e-05,
  1.3888397e-03,
  4.16666418e-02,
  4.999999963e-01,
};
  
float fqcos(const float angle)
{
  float fr;

  __asm {
    movss  xmm0,fcon     ;
    movups xmm3,cosa     ;
    movss  xmm1,angle    ;
    mulss  xmm1,xmm1     ; xsq = x*x 
    mulss  xmm0,xmm1     ; res *= xsq
    addss  xmm0,xmm3     ; res += cosa[0]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4        ;
    subss  xmm0,xmm3     ; res -= cosa[1]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4
    addss  xmm0,xmm3     ; res += cosa[2]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4
    subss  xmm0,xmm3     ; res -= cosa[3]
    mulss  xmm0,xmm1     ; res *= xsq
    addss  xmm0,fone
    movss  fr,xmm0
  }

  return fr;
}

// sqr(cos(x)) + sqr(sin(x)) = 1
//

float fqsin(const float angle)
{
  float fr;

  __asm {
    movss  xmm0,fcon     ;
    movups xmm3,cosa     ;
    movss  xmm1,angle    ;
    mulss  xmm1,xmm1     ; xsq = x*x 
    mulss  xmm0,xmm1     ; res *= xsq
    addss  xmm0,xmm3     ; res += cosa[0]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4        ;
    subss  xmm0,xmm3     ; res -= cosa[1]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4
    addss  xmm0,xmm3     ; res += cosa[2]
    mulss  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,4
    subss  xmm0,xmm3     ; res -= cosa[3]
    mulss  xmm0,xmm1     ; res *= xsq
    movss  xmm1,fone
    addss  xmm0,xmm1
    mulss  xmm0,xmm0     ; sqr(cos(x))
    subss  xmm1,xmm0     ; sqr(sin(x)) = 1-sqr(cos(x))
    sqrtss xmm1,xmm1     ; sin(x)
    movss  fr,xmm0
  }

  return fr;
}

double done = 1.0f;
double dcon = -2.605e-07;
double dcosa[4] = {
  2.47609e-05,
  1.3888397e-03,
  4.16666418e-02,
  4.999999963e-01,
};

double dfcos(const float angle)
{
  double dr = angle;

  __asm {
    movsd  xmm0,dcon       ;
    movupd xmm2,dcosa      ;
    movupd xmm3,dcosa+16    ;
    movsd  xmm1,dr          ;
    mulsd  xmm1,xmm1       ; xsq = x*x 
    mulsd  xmm0,xmm1       ; res *= xsq
    addsd  xmm0,xmm2       ; res += cosa[0]
    mulsd  xmm0,xmm1       ; res *= xsq
    psrldq xmm2,8          ;
    subsd  xmm0,xmm2       ; res -= cosa[1]
    mulsd  xmm0,xmm1       ; res *= xsq
    addsd  xmm0,xmm3       ; res += cosa[2]
    mulsd  xmm0,xmm1       ; res *= xsq
    psrldq xmm3,8
    subsd  xmm0,xmm3       ; res -= cosa[3]
    mulsd  xmm0,xmm1       ; res *= xsq
    addsd  xmm0,done       ; cos(angle)
    movsd  dr,xmm0
  }
  return dr;
}

double dfsin(const float angle)
{
  double dr = angle;

  __asm {
    movsd  xmm0,dcon     ;
    movupd xmm2,dcosa    ;
    movupd xmm3,dcosa+16 ;
    movsd  xmm1,dr       ;
    pslldq xmm1,4        ; convert to double
    mulsd  xmm1,xmm1     ; xsq = x*x 
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm2     ; res += cosa[0]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm2,8        ;
    subsd  xmm0,xmm2     ; res -= cosa[1]
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm3     ; res += cosa[2]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,8
    subsd  xmm0,xmm3     ; res -= cosa[3]
    mulsd  xmm0,xmm1     ; res *= xsq
    movsd  xmm1,done     ; 1.0
    addsd  xmm0,xmm1     ; cos(angle)
    mulsd  xmm0,xmm0     ; sqr(cos(angle))
    subsd  xmm1,xmm0     ; sqr(sin(angle)) = 1.0 - sqr(cos(angle))
    sqrtsd xmm1,xmm1     ; sin(angle)
    movsd  dr,xmm0
  }
  return dr;
}


double dqcos(const double angle)
{
  double dr;

  __asm {
    movsd  xmm0,dcon     ;
    movupd xmm2,dcosa    ;
    movupd xmm3,dcosa+16 ;
    movsd  xmm1,angle    ;
    mulsd  xmm1,xmm1     ; xsq = x*x 
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm2     ; res += cosa[0]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm2,8        ;
    subsd  xmm0,xmm2     ; res -= cosa[1]
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm3     ; res += cosa[2]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,8
    subsd  xmm0,xmm3     ; res -= cosa[3]
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,done     ; cos(angle)
    movsd  dr,xmm0
  }
  return dr;
}

double dqsin(const double angle)
{
  double dr;

  __asm {
    movsd  xmm0,dcon     ;
    movupd xmm2,dcosa    ;
    movupd xmm3,dcosa+16 ;
    movsd  xmm1,angle    ;
    mulsd  xmm1,xmm1     ; xsq = x*x 
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm2     ; res += cosa[0]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm2,8        ;
    subsd  xmm0,xmm2     ; res -= cosa[1]
    mulsd  xmm0,xmm1     ; res *= xsq
    addsd  xmm0,xmm3     ; res += cosa[2]
    mulsd  xmm0,xmm1     ; res *= xsq
    psrldq xmm3,8
    subsd  xmm0,xmm3     ; res -= cosa[3]
    mulsd  xmm0,xmm1     ; res *= xsq
    movsd  xmm1,done     ; 1.0
    addsd  xmm0,xmm1     ; cos(angle)
    mulsd  xmm0,xmm0     ; sqr(cos(angle))
    subsd  xmm1,xmm0     ; sqr(sin(angle)) = 1.0 - sqr(cos(angle))
    sqrtsd xmm1,xmm1     ; sin(angle)
    movsd  dr,xmm0
  }
  return dr;
}

float fpdcos(float x,float y)
{
  float fr;
  __asm {
    movss xmm0,x     ;
    movss xmm1,xmm0  ;
    movss xmm2,y     ;
    movss xmm3,xmm1  ;
    mulss xmm1,xmm1  ; sqr(x)
    mulss xmm3,xmm3  ; sqr(y)
    addss  xmm1,xmm3 ;
    sqrtss xmm1,xmm1 ;
    divss  xmm0,xmm1 ;
    movss  fr,xmm0   ;
  }
  return fr;
}

float fpdsin(float x,float y)
{
  float fr;
  __asm {
    movss  xmm0,y    ;
    movss  xmm1,xmm0 ;
    movss  xmm2,x    ;
    mulss  xmm1,xmm1 ;
    mulss  xmm2,xmm2 ;
    addss  xmm1,xmm2 ;
    sqrtss xmm1,xmm1 ;
    divss  xmm0,xmm1 ;
    movss  fr,xmm0   ;
  }
  return fr;
}

float fpcos(const float x)
{
  __asm {
    fld x
    fcos
  }
}

float fpangle(float x,float y)
{
  float r = sqrt(x*x+y*y);

  float fasin = y / r;
  float facos = x / r;

  __asm {
    fld x
    fld st(0)
    fmul  st(0),st(1)
    fdivp st(1),st(0)
    fld y        
    fld st(0)      
    fmul  st(0),st(1)
    fdivp st(1),st(0)
    fpatan
  }
}

int main()
{
  float angle = M_PI * 30.0 / 180.0;
  float fangle = fpangle(cos(angle),sin(angle));

  float fbngle = fqcos(angle);

  float f0 = cos(angle);
  float f1 = fast_cos(angle);
  float f2 = fqcos(angle);
  float f3 = dfcos(angle);

  fprintf(stdout,"angle:  %40.38f\n",f0);
  fprintf(stdout,"qangle: %40.38f\n",f2);

  fprintf(stdout,"an-fan: %40.38f\n",angle-fangle);
  fprintf(stdout,"delta:  %40.38f\n",f0-f1);

  fprintf(stdout,"fpcos:  %40.38f\n",fpcos(angle)-f0);
  fprintf(stdout,"actual: %40.38f\n",fpcos(angle)-f1);

  fprintf(stdout,"ferr:   %40.38f\n",(f0-f1)/f0);
  fprintf(stdout,"ferr1:  %40.38f\n",(fpcos(angle)-f0)/f0);

  return 0;
}
