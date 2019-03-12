#ifndef __OPEN_CONE
#define __OPEN_CONE

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <CUnalignedVector.h>

#ifdef __WITH_OPENGL
#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#endif
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#endif

class SimpleOpenCone
{
 public:
  vec3* m_Points;
  vec3* m_Normals;
  vec3* m_BiNormals;
  int   m_Segments;
  float m_Radius;
  float m_Height;

  SimpleOpenCone();
  SimpleOpenCone(const int iSegments,const float fRadius,const float fHeight);
  ~SimpleOpenCone();
  void Draw();
};

#endif
