/* *************************************************************************
 * These defines are used to generate the appropriate code.
 * -------------------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************************* */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _ITS_STD_DEFS_H
#define _ITS_STD_DEFS_H

// Wide characters are required
//

#if !defined(_UNICODE)
#define _UNICODE
#define UNICODE
#endif

// Get the standard includes
//

#include <ItsStdIncs.h>

typedef unsigned long ulong;

typedef ulong ObjectId;
typedef ulong EventId;

// Structures used to manipulate bitmask values
//

typedef struct {
  const wchar_t* wName;
  unsigned long  uMask;
}NAME_MASK_PAIR;

typedef struct {
  const wchar_t*        wListName;
  const NAME_MASK_PAIR* pNameMaskPair;
}LIST_DATA;

#if defined(_WIN32) || defined(_WIN64)

// Windows specific definitions
//

typedef HWND WindowId;

// Conversion factors (uniform variatic data passing)
//

typedef __int64 IVAR;
typedef unsigned __int64 UIVAL;
typedef unsigned __int64 UIPTR;

// String conversion factors (will require additional work for COM/+)
//

#if defined(_COM_MODULE)
typedef BSTR OCTSTR;
#else
typedef wchar_t* OCTSTR;
#endif

// Structures used by user-defined conversions
//

typedef struct {
  unsigned __int32 high;
  unsigned __int32 low;
}Split64;

typedef union {
  Split64 a;
  UIPTR   b;
}UIPtrUnion;

#else

typedef ulong    WindowId;
typedef ulong    LRESULT;
typedef wchar_t* OCTSTR;

#endif

#endif
