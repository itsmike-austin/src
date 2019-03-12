#include <FlatBuffer.h>

/* ********************************************************************
 * Package: FlatBuffer
 *
 * Uses:    External 'C' runtime library.
 *
 * Description:
 *   Manage variable block memory allocations. The primary focus
 *   is for use with native processor floating point units such
 *   as the Intel(tm) or Motorola(tm) Gxx.
 *
 *   This manager uses an automated allocation schema that allows the
 *   user to allocate fixed buffers and stuff them on the fly. If the
 *   user requires additional space, it is allocated transparently
 *   for the user.
 *
 *   No provisions have been made to extend this method to use
 *   virtual memory allocation blocks with verification for safety.
 *   
 * --------------------------------------------------------------------
 * (c) 1988,1999-2006 Internet Technology Systems, Inc.
 * ******************************************************************** */

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *                             FlatElement
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

/* --------------------------------------------------------------------
 * Constructor(s)
 * -------------------------------------------------------------------- */

FlatElement::FlatElement() :
  m_Alignment(0),
  m_ElementSize(0),
  m_BaseSize(0),
  m_Buffer(NULL),
  m_AlignPtr(NULL) {}

FlatElement::FlatElement(int iElementSize,
			 int iAlignment) :
  m_Alignment(iAlignment),
  m_ElementSize(iElementSize),
  m_BaseSize(0),
  m_Buffer(NULL),
  m_AlignPtr(NULL)
{
  init(iElementSize,iAlignment);
}

/* --------------------------------------------------------------------
 * Destructor
 * -------------------------------------------------------------------- */

FlatElement::~FlatElement()
{
  if ( m_Buffer ) delete m_Buffer;

  m_Alignment   = 0;
  m_ElementSize = 0;
  m_BaseSize    = 0;
  m_Buffer      = NULL;
  m_AlignPtr    = NULL;
}

/* --------------------------------------------------------------------
 * Init: Initialize accounting and allocate buffer from heap.
 * -------------------------------------------------------------------- */

void* FlatElement::init(int iElementSize,  // Unaligned element size
			int iAlignment)    // Octet alignment
{

  m_ElementSize = (0 == iAlignment || 1 == iAlignment ? iElementSize :
		   2 == iAlignment                    ? iElementSize + 1 :
		   iElementSize + iAlignment);
  m_Alignment   = (0 == iAlignment ? 1 : iAlignment);

  m_BaseSize = iElementSize;
  m_AlignPtr = NULL;

  // Allocate and clear the new buffer
  //

  assert(NULL != (m_Buffer=new char[m_ElementSize]));

  memset((void*)m_Buffer,(char)NULL,m_ElementSize);

  m_AlignPtr = m_Buffer + ((unsigned int)m_Buffer % iAlignment);

  return (void*)m_AlignPtr;
}

/* --------------------------------------------------------------------
 * Management methods
 * -------------------------------------------------------------------- */

void* FlatElement::getAlignedBuffer()
{
  return m_AlignPtr;
}



/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *                             FlatBuffer
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

/* --------------------------------------------------------------------
 * Constructor(s)
 * -------------------------------------------------------------------- */

FlatBuffer::FlatBuffer() :
  m_ElementCount(0),
  m_ElementSize(0),
  m_BaseSize(0),
  m_Alignment(0),
  m_Buffer(NULL),
  m_AlignPtr(NULL) {}

FlatBuffer::FlatBuffer(int iElementSize,
		       int iAlignment,
		       int iElementCount,
		       int iOffset) :
  m_ElementCount(0),
  m_ElementSize(0),
  m_BaseSize(0),
  m_Alignment(0),
  m_Offset(0),
  m_Buffer(NULL),
  m_AlignPtr(NULL)
{
  // Allocate memory for this array
  //

  assert(NULL != alloc(iElementSize,iAlignment,iElementCount,iOffset));
}

FlatBuffer::~FlatBuffer()
{
  if ( m_Buffer ) delete m_Buffer;

  m_ElementSize  = 0;
  m_ElementCount = 0;
  m_BaseSize     = 0;
  m_Alignment    = 0;
  m_Buffer       = NULL;
  m_AlignPtr     = NULL;
}

/* --------------------------------------------------------------------
 * alloc: Allocate memory for the buffer.
 * -------------------------------------------------------------------- */


void* FlatBuffer::alloc(int iElementSize,
			int iAlignment,
			int iElementCount,
			int iOffset)
{
  int nElementSize;
  int nAlignment;
  int nBufSize;
  int nCurBufSize;

  // Calculate the aligned element size, buffer size and current size
  // if the buffer is to be expanded.
  //

  if ( iElementSize == m_ElementSize && (0 == iAlignment ? 1 : iAlignment) == m_Alignment && m_Offset == iOffset)
    {
      nElementSize = m_ElementSize;
      nAlignment   = m_Alignment;
      nBufSize     = m_ElementSize * iElementCount + m_Alignment + m_Offset;
    }
  else
    {
      nElementSize = (0 == iAlignment || 1 == iAlignment ? iElementSize :
		      2 == iAlignment                    ? iElementSize + 1 :
		      iElementSize <= iAlignment ? iElementSize : iElementSize + iAlignment);

      nAlignment  = (0 == iAlignment ? 1 : iAlignment);

      nBufSize    = nElementSize  * iElementCount  + (iElementSize  <= iAlignment  ? iAlignment  : 0) + iOffset;
    }

  nCurBufSize = m_ElementSize * m_ElementCount + (m_ElementSize <= m_Alignment ? m_Alignment : 0) + m_Offset;

  // Check to see if the buffer allocation is to be changed.
  //

  if( NULL          != m_Buffer     &&
      m_ElementSize == nElementSize &&
      m_Alignment   == nAlignment   &&
      m_BaseSize    == iElementSize &&
      m_Offset      == iOffset      &&
      nBufSize - iAlignment - 1 < nCurBufSize ) return m_AlignPtr;

  // Allocate the new buffer and calculate the alignment base
  //

  char* pBuffer = new char[nBufSize];
  assert(NULL != pBuffer);
  char* pAlignPtr = pBuffer + ((unsigned int)pBuffer % nAlignment);

  // Clear the new allocation
  //

  memset((void*)pBuffer,(char)NULL,nBufSize);

  // Copy the existing data into the new buffer if required
  //

  if ( NULL != m_Buffer && m_ElementCount <= iElementCount && m_ElementSize == iElementSize )
    {
      void* psrc = (void*)((char*)m_AlignPtr + m_Offset);
      void* pdst = (void*)((char*)pAlignPtr  + iOffset);
      for( int i=0 ; i < m_ElementCount ; ++i )
	{
	  memcpy(pdst,psrc,m_ElementSize);
	  pdst = (void*)((char*)pdst + m_ElementSize);
	  psrc = (void*)((char*)psrc + m_ElementSize);
	}
    }

  // Delete the existing buffer if required
  //

  if ( NULL != m_Buffer ) delete m_Buffer;

  // Save the operational parameters
  //

  m_ElementCount = iElementCount;
  m_Alignment    = iAlignment;
  m_BaseSize     = iElementSize;
  m_ElementSize  = nElementSize;
  m_Offset       = iOffset;
  m_Buffer       = pBuffer;
  m_AlignPtr     = pAlignPtr;

  return pAlignPtr;
}

void* FlatBuffer::resize(int iElementSize,
			 int iAlignment,
			 int iElementCount,
			 int iOffset)
{
  if ( NULL != m_Buffer ) delete m_Buffer;

  m_Buffer = NULL;

  return alloc(iElementSize,iAlignment,iElementCount,iOffset);
}

/* --------------------------------------------------------------------
 * add: Add a new element to the buffer
 * -------------------------------------------------------------------- */

void* FlatBuffer::add(int   iPosition,
		      void* pElement)
{
  // Make sure the requested element is always in range
  //

  if ( m_ElementCount <= iPosition )
    {
      assert(NULL != alloc(m_BaseSize,m_Alignment,1+iPosition,m_Offset));
    }

  // Calculate the pointer and save the passed parameter
  //

  char* pPosition = m_AlignPtr+(m_ElementSize*iPosition)+m_Offset;

  memcpy((void*)pPosition,(void*)pElement,m_BaseSize);

  return pPosition;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the aligned pointer
 * -------------------------------------------------------------------- */

void* FlatBuffer::getAlignedPtr()
{
  return (void*)m_AlignPtr;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the actual buffer pointer
 * -------------------------------------------------------------------- */

void* FlatBuffer::getBasePtr()
{
  return (void*)m_Buffer;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the number of elements
 * -------------------------------------------------------------------- */

int FlatBuffer::getElementCount()
{
  return m_ElementCount;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the alignment of the array
 * -------------------------------------------------------------------- */

int FlatBuffer::getAlignment()
{
  return m_Alignment;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the size of an aligned element
 * -------------------------------------------------------------------- */

int FlatBuffer::getElementSize()
{
  return m_ElementSize;
}

/* --------------------------------------------------------------------
 * getAlignedPtr: Return the base size required to store an element
 * -------------------------------------------------------------------- */

int FlatBuffer::getBaseSize()
{
  return m_BaseSize;
}

/* --------------------------------------------------------------------
 * getOffset: Return the starting offset for an element.
 * -------------------------------------------------------------------- */

int FlatBuffer::getOffset()
{
  return m_Offset;
}

/* --------------------------------------------------------------------
 * get: Retrieve the requested element pointer.
 * -------------------------------------------------------------------- */

void* FlatBuffer::get(int iPosition)
{
  return (iPosition < m_ElementCount ?
	  m_AlignPtr + m_Offset + (iPosition*m_ElementSize) :
	  alloc(m_ElementSize,m_Alignment,1+iPosition,m_Offset));
}

/* --------------------------------------------------------------------
 * operator[]: Retrieve the requested element pointer.
 * -------------------------------------------------------------------- */

void* FlatBuffer::operator[](int iPosition)
{
  return (iPosition < m_ElementCount ?
	  m_AlignPtr + m_Offset + (iPosition*m_ElementSize) :
	  alloc(m_ElementSize,m_Alignment,1+iPosition,m_Offset));
}
