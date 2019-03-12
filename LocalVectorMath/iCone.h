#ifndef __ICONE_H
#define __ICONE_H

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define _USE_MATH_DEFINES
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>

#include <CVector.h>

// XXX: Requires centralization
//

typedef struct {
  double dcos;
  double dsin;
}TrigAngle;

class iCone {
 public:
  vec4* m_VertexArray;
  vec4* m_NormalArray;
  vec4* m_BinormalArray;

  int   m_SectionCount;
  int   m_SegmentCount;
  int   m_PaneCount;
  int   m_VertexCount;
  float m_Alpha;

  // XXX: Draw style should be considered later
  //

  iCone();
  iCone(float fRadius,float fHeight,int iSections,int iSegments);
  ~iCone();

  void Project(mat4*);
  void Alpha(float fAlpha);
  void Draw();

  void Setup(float fRadius,float fHeight,int iSections,int iSegments);

};

#endif

  

  
