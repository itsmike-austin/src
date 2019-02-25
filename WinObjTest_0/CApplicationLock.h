/* ************************************************************
 * CApplicationLock
 *
 * Application locks are used to serialize access to the
 * object and callback lists for threaded methods.
 *
 * All management methods are contained in this object.
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * UNIX SPECIFIC:      REQUIRED
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CAPPLICATION_LOCKS_H
#define _CAPPLICATION_LOCKS_H

#include "stdafx.h"

class CApplicationLock
{
 private:
#if defined(_WIN32) || defined(_WIN64)
  CRITICAL_SECTION m_Lock;
#endif

 public:

  // Constructor/Destructor
  //

  CApplicationLock();
  ~CApplicationLock();

  // Management Methods
  //

  LRESULT Lock();
  LRESULT Unlock();
  LRESULT IsItLocked();

  void*   GetLock();

};

#endif
