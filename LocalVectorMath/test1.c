#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

double dSinCosBase[] = {
  1.6666666666666666e-001,
  7.4999999999999997e-002,
  4.4642857142857144e-002,
  3.0381944444444444e-002
};

double dHalf   = 0.5;
double dPi     = M_PI;
double dHalfPi = M_PI_2;
double dNegOne = -1.0;

double aacos(const double dAngle)
{
  double dr;

  __asm {
    movlpd  xmm0,dAngle   ;
    mulsd   xmm0,dNegOne  ;
    pslldq  xmm0,8        ;
    movlpd  xmm0,dHalfPi  ;
    movlpd  xmm1,[dAngle] ;
    movhpd  xmm1,[dAngle] ;
    movapd  xmm2,xmm1     ;
    mulpd   xmm2,xmm2     ; // x^2
    movapd  xmm3,xmm2     ;
    mulpd   xmm3,xmm3     ; // x^4
    movapd  xmm4,xmm2     ; // x^2 x^2
    shufpd  xmm4,xmm3,0   ; // x^2 x^4
    mulpd   xmm4,xmm1     ; // x^3 x^5
    movupd  xmm5,dSinCosBase ;
    movupd  xmm6,dSinCosBase+16 ;
    mulpd   xmm5,xmm4           ; // 1/6*x^3 3/40*x^5
    mulpd   xmm4,xmm3           ;
    mulpd   xmm6,xmm4           ; // 5/112*x^7 35/1152*x^9
    subpd   xmm0,xmm5           ;
    subpd   xmm0,xmm6           ;
    movapd  xmm1,xmm0           ;
    psrldq  xmm1,8              ;
    addsd   xmm0,xmm1           ;
    movsd   dr,xmm0             ;
  }

#if 0
  __asm {
    movsd   xmm0,[dHalfPi]        ; 1/2*pi
    movsd   xmm1,[dAngle]         ; x
    movsd   xmm2,xmm1             ;
    movsd   xmm3,[dSinCosBase]    ;
    movsd   xmm4,[dSinCosBase+16] ;
    mulsd   xmm2,xmm2             ; x^2                   -9
    subsd   xmm0,xmm1             ; res = pi/2 - x        -7
    mulsd   xmm1,xmm2             ; x^3                   -9
    mulsd   xmm3,xmm1             ; 1/6*x^3               -9
    subsd   xmm0,xmm3             ; res -= (1/6)*(x^3)    -7
    psrldq  xmm3,8                ; 3/40                  -6
    mulsd   xmm1,xmm2             ; x^5                   -9
    mulsd   xmm3,xmm1             ; (3/40)*(x^5)          -9
    subsd   xmm0,xmm3             ; res -= (3/40)*(x^5)   -7
    mulsd   xmm1,xmm2             ; x^7                   -9
    mulsd   xmm4,xmm1             ; (5/112)*(x^7)         -9
    subsd   xmm0,xmm4             ; res -= (5/112)*(x^7)  -7
    mulsd   xmm1,xmm2             ; x^9                   -9
    psrldq  xmm4,8                ; 35/1152               -6
    mulsd   xmm4,xmm1             ; (35/1152)*(x^9)       -9
    subpd   xmm0,xmm4             ;res -= (35/1152)*(x^9) -7 : 81+28+12=121-140
    movsd   dr,xmm0               ; save
  }
#endif

  return dr;
}

double dtcos(double angle)
{
  return log(angle + sqrt(angle + sqrt((angle*angle)-1)));
}

int main()
{
  double angle = M_PI * 30.0 / 180.0;
  double cang  = cos(angle);
  double dCos0 = acos(cang);
  double dCos1 = aacos(cang);

  fprintf(stdout,"%40.38f\n%40.38f\n",dCos0,dCos1);

  fprintf(stdout,"err: %5.2f\n",100.0*(dCos1-dCos0)/dCos1);

  return 0;
}
	  
