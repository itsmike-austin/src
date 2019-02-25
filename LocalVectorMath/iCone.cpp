#include <iCone.h>

iCone::iCone() :
  m_VertexArray(NULL),
  m_NormalArray(NULL),
  m_BinormalArray(NULL),
  m_SectionCount(0),
  m_SegmentCount(0),
  m_VertexCount(0),
  m_PaneCount(0) {}

iCone::iCone(float fRadius,float fHeight,int iSections,int iSegments) :
  m_VertexArray(NULL),
  m_NormalArray(NULL),
  m_BinormalArray(NULL),
  m_SectionCount(0),
  m_SegmentCount(0),
  m_VertexCount(0),
  m_PaneCount(0)
{
  Setup(fRadius,fHeight,iSections,iSegments);
}

void iCone::Setup(float fRadius,
		  float fHeight,
		  int   iSections,
		  int   iSegments)
{
  vec4* pVertexArray;    // Temporary vertex storage area
  vec4* pRadiusArray;    // Temporary array of radii
  vec4* pNormalArray;    // Temporary normal array
  vec4* pBinormalArray;  // Temporary binormal array

  vec4* pVec;            // Used to walk through vector lists
  vec4* pRad;            // Used to walk through radii lists
  vec4* pDup;            // Used to walk through vector lists with offset
  vec4* pStart;          // Used to walk through vector lists with offset
  vec4* pOrigin;         // Used to walk through vector lists with offset
  vec4* pNorm;           // Used to walk through normal lists
  vec4* pBinorm;         // Used to walk through binormal lists

  TrigAngle* pAngles;    // Full angle list
  TrigAngle* pHalfAng;   // Half angle list
  TrigAngle* pTrigPtr;   // Used to walk through angle lists
  int        iTrgSel;

  register int i;        // Index and optimization variables
  register int j;
  register int iCounter;

  int      iHalfSegs;    // Half of the segment count

  double   delZ;         // z-displayment for a section of the cone
  double   dLen;         // length of the cone face
  double   delL;         // height of a cone section
  double   delzpt;       // temporary accumulation variable for height
  double   dellpt;       // temporary accumulation variable for length

  double   dAngle;       // Spead angle for triangle base
  double   dHalfAngle;   // Half of the spread angle (top triangle point)

  double   dRadius;      // temporary accumulation variable for radius
  double   dBaseAngle;   // temporary accumulation variable for angle

  // There has to be at least 2 segments for this to work (Maybe 4)
  // and the segment count has to be even.
  //

  if ( iSegments < 2 ) iSegments = 2 ;

  iSegments += iSegments % 2;

  iHalfSegs = iSegments / 2;

  iCounter = iSections * iSegments;

  pVertexArray   = new vec4[3*iCounter];
  pRadiusArray   = new vec4[iSections];
  pNormalArray   = new vec4[iCounter];
  pBinormalArray = new vec4[iCounter];
  pAngles        = new TrigAngle[iHalfSegs];
  pHalfAng       = new TrigAngle[iHalfSegs];

  if ( NULL == pVertexArray   ||
       NULL == pRadiusArray   ||
       NULL == pNormalArray   ||
       NULL == pBinormalArray ||
       NULL == pAngles        ||
       NULL == pHalfAng        )
    {
      if ( pVertexArray   ) delete pVertexArray;
      if ( pRadiusArray   ) delete pRadiusArray;
      if ( pNormalArray   ) delete pNormalArray;
      if ( pBinormalArray ) delete pBinormalArray;
      if ( pAngles        ) delete pAngles;
      if ( pHalfAng       ) delete pHalfAng;
      assert(NULL);
    }

  dAngle     = 2.0 * M_PI / (float)iSegments;
  dHalfAngle = dAngle / 2.0;

  // Generate the radius at each height increment
  //
  // XXX: Note this could fail .... recheck calcs
  //

  delZ   = fHeight / (float)iSections;
  dLen   = sqrt(fHeight*fHeight + fRadius*fRadius);
  delL   = dLen / (float)iSections;
  delzpt = delZ;
  dellpt = delL;

  iCounter = iSections;

  pRadiusArray[0].x        = fRadius;
  pRadiusArray[0].z        = 0.0;

  for( i=1 ; i < iCounter ; ++i )
    {
      // XXX: Note: again .. check this calc
      //
      // ??? sqr(len) = sqr(h) + sqr(r)
      //     sqr(len) - sqr(h) = sqr(r)
      //     r = sqrt(sqr(len) - sqr(h));

      pRadiusArray[i].x = (float)(fRadius - sqrt(dellpt*dellpt - delzpt*delzpt));
      pRadiusArray[i].z = (float)delzpt;
      delzpt += delZ;
      dellpt += delL;
    }

  // Calculate the trig tables
  //

  dBaseAngle = 2.0 * M_PI - dHalfAngle;

  pAngles[0].dcos  = 1.0;
  pAngles[0].dsin  = 0.0;
  pHalfAng[0].dcos = cos(dBaseAngle);
  pHalfAng[0].dsin = sin(dBaseAngle);

  for( i=1 ; i < iHalfSegs ; ++i )
    {
      dBaseAngle -= dHalfAngle;
      pAngles[i].dcos = cos(dBaseAngle);
      pAngles[i].dsin = sin(dBaseAngle);
      dBaseAngle -= dHalfAngle;
      pHalfAng[i].dcos = cos(dBaseAngle);
      pHalfAng[i].dsin = sin(dBaseAngle);
    }

  // Build the core
  //

  pRad     = pRadiusArray;
  pTrigPtr = pHalfAng;
  pVec     = &pVertexArray[1];
  pOrigin  = pVec;
  iTrgSel  = 0;

  for( i=0 ; i < iSections ; ++i )
    {
      // Toggle the trig pointers per section
      //

      if ( 0 == iTrgSel )
	{
	  pTrigPtr = pAngles;
	  iTrgSel  = 1;
	}
      else
	{
	  pTrigPtr = pHalfAng;
	  iTrgSel  = 0;
	}

      dRadius = pRad->x;

      pVec->x = (float)(dRadius * pTrigPtr->dcos);
      pVec->y = (float)(dRadius * pTrigPtr->dsin);
      pVec->z = pRad->z;

      pOrigin = pStart = pVec;        // This point will be reused in the last tri.

      ++pVec;
      ++pTrigPtr;

      pVec->x = (float)(dRadius * pTrigPtr->dcos);
      pVec->y = (float)(dRadius * pTrigPtr->dsin);
      pVec->z = pRad->z;

      pDup = pVec;          // This point will be used in the next tri.

      // Fill out the lower half of the circle (q3/q4)
      //

      for( j=2 ; j < iHalfSegs ; ++j )
	{
	  pVec += 3;
	  ++pTrigPtr;

	  pVec->x = (float)(dRadius * pTrigPtr->dcos);
	  pVec->y = (float)(dRadius * pTrigPtr->dsin);
	  pVec->z = pRad->z;
	}

      // Fill out the upper half (q1/q2)
      //

      pVec += 3;
      pVec->x = -(pStart->x);
      pVec->y = -(pStart->y);
      pVec->z = pStart->z;

      ++pStart;
      pVec += 3;

      pVec->x = -(pStart->x);
      pVec->y = -(pStart->y);
      pVec->z = pStart->z;

      for( j=2 ; j < iHalfSegs ; ++j )
	{
	  pVec   += 3;
	  pStart += 3;
	  pVec->x = -(pStart->x);
	  pVec->y = -(pStart->y);
	  pVec->z = pStart->z;
	}

      // Build the connection for the last triangle
      //

      pVec += 3;
      *pVec = *pOrigin;

      // Rotate the base circle into place
      //

      pVec = pDup + 2;

      for( j=1 ; j < iSegments ; ++ j )
	{
	  *pVec = *pDup;
	  pVec += 3;
	  pDup += 3;
	}

      // Next section
      //

      ++pRad;
    }

  // Fill the starting points from the upper circle
  //

  pVec = pVertexArray;
  pDup = pVertexArray + ((3*iSegments)+1);

  iCounter = (iSections - 1) * iSegments;

  for( i=0 ; i < iCounter ; ++i )
    {
      *pVec = *pDup;
      pVec += 3;
      pDup += 3;
    }

  // Cap the cone
  //

  vec4 cap = { 0.0, 0.0, fHeight,0.0 };

  for( i=0 ; i < iSegments ; ++i )
    {
      *pVec = cap;
      pVec += 3;
    }

  // Calculate the Vector Normals
  //

  pNorm = pNormalArray;
  pVec  = pVertexArray;

  iCounter = iSections * iSegments;

  for( i=0 ; i < iCounter ; ++i )
    {
      vec3 v0,v1;
      Vec3Subtract(&v0,(vec3*)(pVec+1),(vec3*)pVec);
      Vec3Subtract(&v1,(vec3*)(pVec+2),(vec3*)pVec);
      Vec3Cross((vec3*)pNorm,&v1,&v0);
      Vec3Normalize((vec3*)pNorm,(vec3*)pNorm);
      ++pNorm;
      pVec += 3;
    }

  // Calculate the Binormals
  //

  pNorm   = pNormalArray;
  pBinorm = pBinormalArray;

  iCounter = iSegments;

  for( i=0 ; i < iSections ; ++i )
    {
      vec3 v0;
      Vec3Add(&v0,(vec3*)pNorm,(vec3*)(pNorm+(iSegments-1)));
      Vec3Normalize((vec3*)pBinorm,&v0);
      ++pBinorm;
      for( j=1 ; j < iCounter ; ++j )
	{
	  Vec3Add(&v0,(vec3*)pNorm,(vec3*)(pNorm+1));
	  Vec3Normalize((vec3*)pBinorm,&v0);
	  ++pNorm;
	  ++pBinorm;
	}
      ++pNorm;
    }

  if ( m_VertexArray   ) delete m_VertexArray;
  if ( m_NormalArray   ) delete m_NormalArray;
  if ( m_BinormalArray ) delete m_BinormalArray;

  m_VertexArray   = pVertexArray;
  m_NormalArray   = pNormalArray;
  m_BinormalArray = pBinormalArray;

  m_SectionCount = iSections;
  m_SegmentCount = iSegments;
  m_PaneCount    = iSections * iSegments;
  m_VertexCount  = 3 * m_PaneCount;

  // Cleanup the leftover memory
  //

  delete pRadiusArray;
  delete pAngles;
  delete pHalfAng;

  // Set the alpha values to 1.0 to start
  //

  pVec     = pVertexArray;
  iCounter = m_VertexCount;
  for( i=0 ; i < iCounter ; ++i ) (*pVec++).w = 1.0;
}

iCone::~iCone()
{
  if ( NULL != m_VertexArray   ) delete m_VertexArray;
  if ( NULL != m_NormalArray   ) delete m_NormalArray;
  if ( NULL != m_BinormalArray ) delete m_BinormalArray;

  m_SectionCount = m_SegmentCount = m_PaneCount = 0;

  m_VertexArray = m_NormalArray = m_BinormalArray = NULL;
}

void iCone::Alpha(float fAlpha)
{
  m_Alpha = fAlpha;

  register vec4* pVec = m_VertexArray;
  register int   i;
  register int   iCounter = 3*m_PaneCount;

  for( i=0 ; i < iCounter ; ++i ) (*m_VertexArray++).w = fAlpha;
}

void iCone::Project(mat4* pTransMatrix)
{
  // This is a block calculation. (Check in a minute)
}

// XXX: Lighting Model Required?
//

void iCone::DrawColor()
{
  register int   i;
  register vec4* pVec     = m_VertexArray;
  register vec4* pNorm    = (Normals == m_NormalAtrribute ? m_NormalArray : m_BinormalArray);
  register int   iCounter = m_PaneCount;

  glBegin(GL_TRIANGLES);
  {
    for( i=0 ; i < iCounter ; ++i )
      {
	// XXX: Should be 3f?
	glNormal4fv(pNorm)
	glVertex4fv(pVec++);
	glVertex4fv(pVec++);
	glVertex4fv(pVec++);
	++pNorm;
      }
  }
  glEnd();
}

// XXX: Linestyle model required?
//

void iCone::DrawOutline()
{
  register       int       i;
  register vec4* pVec     = m_VertexArray;
  register int   iCounter = m_VertexCount;

  glBegin(GL_TRIANGLES);
  {
    for( i=0 ; i < m_VertexCount ; ++i ) glVertex4fv(pVec++);
  }
  glEnd();
}

  
      




      

  
