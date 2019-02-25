#include <OpenCone.h>

SimpleOpenCone::SimpleOpenCone() :
  m_Points(NULL),
  m_Normals(NULL),
  m_BiNormals(NULL),
  m_Segments(0),
  m_Radius(0.0),
  m_Height(0.0) {}

SimpleOpenCone::SimpleOpenCone(const int iSegments,const float fRadius,const float fHeight) :
  m_Points(NULL),
  m_Normals(NULL),
  m_BiNormals(NULL),
  m_Segments(iSegments),
  m_Radius(fRadius),
  m_Height(fHeight)
{
  int   i;
  int   iSegCount;
  float fBaseAngle;
  float fAngle;

  m_Segments += (m_Segments % 2 ? 1 : 0);
  iSegCount  = 1 + m_Segments;

  fAngle = (float)((2.0 * M_PI)/m_Segments);

  assert(NULL != (m_Points   =new vec3[1+iSegCount]));
  assert(NULL != (m_Normals  =new vec3[1+iSegCount]));
  assert(NULL != (m_BiNormals=new vec3[1+iSegCount]));

  // The first two points are effectively pre-defined
  //

  m_Points[0].x = m_Points[0].y = 0.0f;
  m_Points[0].z = m_Height;

  m_Points[1].x = m_Radius;
  m_Points[1].y = 0.0f;

  // Calculate the half segment point
  //

  int iHalfSeg = m_Segments / 2 + 1;

  // Calculate q1 & q2 positions (1/2 to avoid 90 degree issue)
  //
  // XXX: Should use a (can use a) sincos method for most of this.
  //

  fBaseAngle = (float)(2.0 * M_PI - fAngle);

  for( i=2 ; i < iHalfSeg ; ++i )
    {
      m_Points[i].x = (float)(m_Radius * cos(fBaseAngle));
      m_Points[i].y = (float)(m_Radius * sin(fBaseAngle));
      fBaseAngle   -= fAngle;
    }

  // Reflect the first half points
  //

  --iHalfSeg;

  for( ; i < iSegCount ; ++i ) Vec3Negate(&m_Points[i],&m_Points[i-iHalfSeg]);

  // Close the figure
  //

  m_Points[iSegCount] = m_Points[1];
  

  // Generate the two vectors for normal calculatiosn
  //

  for( i=1 ; i < iSegCount ; ++i ) m_Points[i].z = m_Height;

  // Calculate the normals
  //

  m_Normals[0].x = m_Normals[0].y = 0.0f;
  m_Normals[0].z = -1.0f;

  for( i=1 ; i < iSegCount ; ++i )
    {
      int iEnd = 1 + i;
      iEnd = (iEnd < m_Segments ? iEnd : 1);
      Vec3Cross(&m_Normals[i],&m_Points[i],&m_Points[iEnd]);
      Vec3Normalize(&m_Normals[i],&m_Normals[i]);
    }

  // Calculate the binormals
  //

  m_BiNormals[0].x = m_BiNormals[0].y = 0.0f;
  m_BiNormals[0].z = -1.0f;

  for( i=1 ; i < iSegCount ; ++i )
    {
      int iEnd = 1 + i;
      iEnd = (iEnd < m_Segments ? iEnd : 1);
      Vec3Add(&m_BiNormals[i],&m_Normals[i],&m_Normals[iEnd]);
      Vec3Normalize(&m_BiNormals[i],&m_BiNormals[i]);
    }

  // Cleanup the z-components of the points
  //

  for( i=1 ; i < 1+iSegCount ; ++i ) m_Points[i].z = 0.0f;

  m_Segments = 1+iSegCount;
}

SimpleOpenCone::~SimpleOpenCone()
{
  if ( NULL != m_Points    ) delete m_Points;
  if ( NULL != m_Normals   ) delete m_Normals;
  if ( NULL != m_BiNormals ) delete m_BiNormals;

  m_Points   = m_Normals = m_BiNormals = NULL;
  m_Segments = 0;
  m_Radius   = m_Height = 0.0f;
}

// XXX: Check to see if single normal, or multiple normals
//      etc. (along with bi-normal being better)
//      for the draw.
//
// eg. OpenCone::RawDraw
//


void SimpleOpenCone::Draw()
{
  glBegin(GL_TRIANGLE_FAN);
  for( int i=0 ; i < m_Segments ; ++i )
    {
      glNormal3f(0.0,0.0,1.0);
      glVertex3f(m_Points[i].x,m_Points[i].y,m_Points[i].z);
    }
  glEnd();
}
