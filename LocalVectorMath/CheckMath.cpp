#define __UNALIGNED_LIB
#include <CVector.h>

vec3 pVecs[] = {
  { 1.5,2.0,1.0 },
  { 2.0,0.0,0.0 },
  { 1.0,0.0,2.0 }
};

vec3 pVec1[] = {
  { 0.0,1.0,0.0 },
  { 1.0,0.0,0.0 },
  { 0.0,0.0,1.0 }
};

int main()
{
  vec3 v0;
  vec3 v1;
  vec3 v3;

  Vec3Subtract(&v0,&pVecs[1],&pVecs[0]);
  Vec3Subtract(&v1,&pVecs[2],&pVecs[0]);
  Vec3Cross(&v3,&v1,&v0);

  Vec3Subtract(&v0,&pVec1[1],&pVec1[0]);
  Vec3Subtract(&v1,&pVec1[2],&pVec1[0]);
  Vec3Cross(&v3,&v1,&v0);

  return 0;
}


  
  

