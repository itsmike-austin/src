#ifndef __FLAT_BUFFER_H
#define __FLAT_BUFFER_H

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

/* --------------------------------------------------------------------
 * A few weird elements required for UNIX
 * -------------------------------------------------------------------- */

#if defined(_WIN32) || defined(_WIN64)
#define __WINDOWS_PLATFORM
#endif

#if !defined(__WINDOWS_PLATFORM)
#include <stdint.h>
typedef uint32_t LRESULT;
#define S_OK 0x00000000
#define E_OUTOFMEMORY 0x00000001
#else
#include <windows.h>
#endif

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>
#if defined(__WINDOWS_PLATFORM)
#include <memory.h>
#endif

#undef __WINDOWS_PLATFORM

#if (defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)) && defined (__BUILD_LIBRARY) && !defined(InterfaceMethod)
#define InterfaceMethod __declspec(dllexport)
#elif defined(__BUILD_LIBRARY) && !defined(InterfaceMethod)
#define InterfaceMethod
#endif
  
#if defined(__ADVANCED_ALIGNED_LIB) || defined(__ALIGNED_LIB)
#include <FlatBuffer.h>
#endif

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Member: FlatElement
 *
 * Description: Allocate and initialize a single item with specified
 *              alignment.
 *
 * Methods:
 *  getAlignedBuffer()                : Inform caller of aligned buffer
 *                                    : Note: This may not be base buffer
 *
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

class FlatElement
{
 protected:
  int   m_Alignment;                // Byte alignment
  int   m_ElementSize;              // Size of an aligned element
  int   m_BaseSize;                 // Size of an unaligned element
  char* m_Buffer;                   // Base buffer
  char* m_AlignPtr;                 // Adjusted alignment element

 public:
  // Constructors
  //

  InterfaceMethod FlatElement();                    // NULL buffer (no allocations)

  InterfaceMethod FlatElement(int iElementSize,     // Unaligned element size
	                      int iAlignment);      // Octet alignment

  InterfaceMethod ~FlatElement();                   // Destructor

  // Accessor Methods
  //

  InterfaceMethod void* init(int iElementSize,int iAlignment);
  InterfaceMethod void* getAlignedBuffer();
};

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Member: FlatBuffer
 *
 * Description: Allocate a large buffer of aligned elements
 *
 * Methods:
 *  getAlignedBuffer()                : Inform caller of aligned buffer
 *                                    : Note: This may not be base buffer
 *
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

class FlatBuffer
{
 protected:
  int   m_ElementCount;              // Elements in the buffer
  int   m_ElementSize;               // Aligned size of an element
  int   m_BaseSize;                  // External size of an element
  int   m_Alignment;                 // Byte alignment
  int   m_Offset;                    // Offset from beginning of buffer
  char* m_Buffer;                    // Base buffer pointer
  char* m_AlignPtr;                  // Aligned buffer pointer

 public:

  // Constructors
  //

  InterfaceMethod FlatBuffer();

  InterfaceMethod FlatBuffer(int iElementSize,       // External element size
			     int iAlignment,         // Byte alignment
			     int iElementCount,      // Elements in the buffer
			     int iOffset);           // Buffer offset
  
  InterfaceMethod ~FlatBuffer();

  // Accessors
  //

  InterfaceMethod void* getAlignedPtr();
  InterfaceMethod void* getBasePtr();
  InterfaceMethod int   getElementCount();
  InterfaceMethod int   getAlignment();
  InterfaceMethod int   getElementSize();
  InterfaceMethod int   getBaseSize();
  InterfaceMethod int   getOffset();

  // Management Methods
  //

  InterfaceMethod void* alloc(int iElementSize,
			      int iAlignment,
			      int iElementCount,
			      int iOffset);

  InterfaceMethod void* resize(int iElementSize,
			       int iAlignment,
			       int iElementCount,
			       int iOffset);

  InterfaceMethod void* add(int iPosition,void* pElement);
  InterfaceMethod void* get(int iPosition);

  // Operators
  //

  InterfaceMethod void* operator[](int iPosition);
};

#endif
