#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

extern long double __ieee754_acosl (long double x);

int main()
{
  double a = M_PI * 30.0 / 180.0;
  double b = cos(a);
  long double c = b;

  double d0 = acos(b);
  double d1 = __ieee754_acosl(c);

  return 0;
}
