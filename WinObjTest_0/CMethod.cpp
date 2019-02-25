/* ************************************************************************
 * CMethod is used to encapsulate a pointer to method. This object is
 * primarily used for runtime conversion between 32 and 64 bit method
 * pointers used in primary event loops.
 * ------------------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************************ */

#include <CMethod.h>

/* ------------------------------------------------------------------------
 * CMethod Constructors/Destructor and User-defined conversions.
 * ------------------------------------------------------------------------ */

CMethod::CMethod() : pCallbackMethod(NULL) {}
CMethod::~CMethod() { pCallbackMethod = NULL; }

/* ------------------------------------------------------------------------
 * CErrorMethod Constructors/Destructor and User-defined conversions.
 * ------------------------------------------------------------------------ */

CErrorMethod::CErrorMethod() : pCallbackErrorMethod(NULL) {}
CErrorMethod::~CErrorMethod() { pCallbackErrorMethod = NULL; }

// Empty constructor
//

UIFPTR::UIFPTR()
{
  lp.a.high = 0;
  lp.a.low  = 0;
}

UIFPTR::UIFPTR(CallbackMethod fp)
{
  if ( 4 == sizeof(CallbackMethod) )
    {
      lp.a.high = (unsigned __int32)*((void**)&fp);
      lp.a.low  = 0;
    }
  else
    {
      lp.b = (unsigned __int64)*((void**)&fp);
    }
}

UIFPTR::UIFPTR(CEmptyBase* pBase)
{
  if ( 4 == sizeof(CEmptyBase*) )
    {
      lp.a.high = (unsigned __int32)*((void**)&pBase);
      lp.a.low  = 0;
    }
  else
    {
      lp.b = (unsigned __int64)*((void**)&pBase);
    }
}

UIFPTR::UIFPTR(CallbackErrorMethod fp)
{
  if ( 4 == sizeof(CallbackErrorMethod) )
    {
      lp.a.high = (unsigned __int32)*((void**)&fp);
      lp.a.low  = 0;
    }
  else
    {
      lp.b = (unsigned __int64)*((void**)&fp);
    }
}

UIFPTR::operator CallbackMethod()
{
  CallbackMethod fp      = NULL;
  void**         pOffset = (void**)&fp;

  if ( 4 == sizeof(CallbackMethod) )
    {
      *pOffset = *((void**)&lp.a.high);
    }
  else
    {
      *pOffset = *((void**)&lp.b);
    }
  return fp;
}

UIFPTR::operator CEmptyBase*()
{
  CEmptyBase* pBase = NULL;
  void**      pOffset = (void**)&pBase;

  if ( 4 == sizeof(CEmptyBase*) )
    {
      *pOffset = *((void**)&lp.a.high);
    }
  else
    {
      *pOffset = *((void**)&lp.b);
    }
  return pBase;
}

UIFPTR::operator CallbackErrorMethod()
{
  CallbackErrorMethod fp      = NULL;
  void**              pOffset = (void**)&fp;

  if ( 4 == sizeof(CallbackErrorMethod) )
    {
      *pOffset = *((void**)&lp.a.high);
    }
  else
    {
      *pOffset = *((void**)&lp.b);
    }
  return fp;
}
