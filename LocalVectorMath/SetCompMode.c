#include <stdio.h>
#include <string.h>

int main()
{

  char  bel = 0x07;
  char  si  = 0x0f;
  FILE* fp = fopen("lpt1:","w");

  char buf[512];

  /* Setup the compressed print mode */

  buf[0] = si;
  buf[1] = '\0';
  fprintf(fp,buf);

  /* Ding the bell */

  buf[0] = bel;
  fprintf(fp,buf);

  /* This leaves the printer in compressed text mode */

  fclose(fp);

  return 0;
}
