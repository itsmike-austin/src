#include <stdio.h>
#include <math.h>
#include <d3dx9.h>

int main()
{
  D3DXMATRIX dxmat;

#if 0
  float angle = 0.785398163397448309616f;
#else
  float angle = 0.0f;
#endif
  D3DXVECTOR3 eye(1.0f,2.0f,3.0f);
  D3DXVECTOR3 center(4.0f,5.0f,6.0f);
  D3DXVECTOR3 up(7.0f,8.0f,9.0f);

  D3DXMatrixLookAtLH(&dxmat,&eye,&center,&up);

  // D3DXMatrixRotationX(&dxmat,angle);

  fprintf(stdout,
	  "m00: %40.38f\n"
	  "m01: %40.38f\n"
	  "m02: %40.38f\n"
	  "m03: %40.38f\n"
	  "m10: %40.38f\n"
	  "m11: %40.38f\n"
	  "m12: %40.38f\n"
	  "m13: %40.38f\n"
	  "m20: %40.38f\n"
	  "m21: %40.38f\n"
	  "m22: %40.38f\n"
	  "m23: %40.38f\n"
	  "m30: %40.38f\n"
	  "m31: %40.38f\n"
	  "m32: %40.38f\n"
	  "m33: %40.38f\n\n",
	  dxmat._11,
	  dxmat._12,
	  dxmat._13,
	  dxmat._14,
	  dxmat._21,
	  dxmat._22,
	  dxmat._23,
	  dxmat._24,
	  dxmat._31,
	  dxmat._32,
	  dxmat._33,
	  dxmat._34,
	  dxmat._41,
	  dxmat._42,
	  dxmat._43,
	  dxmat._44);

  fprintf(stdout,"sin(angle): %40.38f\n",sin(angle));
  fprintf(stdout,"cos(angle): %40.38f\n",cos(angle));
  

  return 0;
}


