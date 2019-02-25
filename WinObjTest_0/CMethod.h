/* ************************************************************************
 * CMethod is used to encapsulate a pointer to method. This object is
 * primarily used for runtime conversion between 32 and 64 bit method
 * pointers used in primary event loops.
 * ------------------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CMETHOD_H
#define _CMETHOD_H

#include <ItsStdDefs.h>
#include <CEmptyBase.h>

// Type definition used to simplify method pointer signatures
//

class CMethod;

typedef LRESULT (CMethod::*CallbackMethod)(WindowId        wId,
					   ObjectId        oId,
					   WPARAM          wParam,
					   LPARAM          lParam,
					   CCallbackClass* pData);

class CMethod
{
 public:
  LRESULT (CMethod::*pCallbackMethod)(WindowId        wId,
				      ObjectId        oId,
				      WPARAM          wParam,
				      LPARAM          lParam,
				      CCallbackClass* pData);
  CMethod();
  ~CMethod();
};

// typedef used to simplify error method pointer signatures
//

class CErrorMethod;

typedef LRESULT (CErrorMethod::*CallbackErrorMethod)(CCallbackClass* pData);

class CErrorMethod
{
 public:
  LRESULT (CErrorMethod::*pCallbackErrorMethod)(CCallbackClass* pData);
  CErrorMethod();
  ~CErrorMethod();
};

// User-defined conversions for 32/64 bit parameter passing
//

class UIFPTR
{
 private:
  UIPtrUnion lp;

 public:
  UIFPTR();
  UIFPTR(CallbackMethod);
  UIFPTR(CEmptyBase*);
  UIFPTR(CallbackErrorMethod);
  operator CallbackMethod();
  operator CEmptyBase*();
  operator CallbackErrorMethod();
};

#include <LocalMethodDefs.h>

#endif
