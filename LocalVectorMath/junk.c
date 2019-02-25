#include <stdio.h>
#include <math.h>

int main()
{
  fprintf(stdout,"sin(0): %5.3f\n",sin(0.0f));
  fprintf(stdout,"cos(0): %5.3f\n",cos(0.0f));

  fprintf(stdout,"a%1: %d\n",24 % 1);

  return 0;
}
