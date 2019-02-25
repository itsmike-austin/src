/* ************************************************************
 * Callbacks are code elements executed in response to
 * various events.
 * ------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

/* --------------------------------------------------------------------------
 * EXAMPLE
 * --------------------------------------------------------------------------
 * Empty (NULL) Constructor
 *
 * CCallBack* pCallBack = new CCallBack();
 *
 * General constructor
 *
 * CCallBack* pCallBack = new CCallBack(WinCreateEvent,  (UIVAL) WinCreateEvent,
 *                                      CallbackObjectId,(UIVAL) 101,
 *                                      CallbackWindowId,(UIPTR) hWnd,
 *                                      CallbackWindow,  (UIPTR) pWindow,
 *                                      CallbackData,    (UIPTR) pData,
 *                                      CallbackError,   (UIFPTR)&CDerivedObj::DoError,
 *                                      CallbackMethod,  (UIFPTR)&CDerivedObj::DoCreate,
 *                                      CallbackType,    (UIVAL) BasicCallback,
 *                                      NULL);
 *
 * Inside any class derived from CWindowObject
 *
 * CCallBack* pCallback = new CCallback(this,
 *                                      CallbackEvent,   (UIVAL) WinCreateEvent,
 *                                      CallbackObjectId,(UIVAL) 101,
 *                                      CallbackWindowId,(UIPTR) hWnd,
 *                                      CallbackData,    (UIPTR) pData,
 *                                      CallbackError,   (UIFPTR)&CDerivedObj::DoError,
 *                                      CallbackMethod,  (UIFPTR)&CDerivedObj::DoCreate,
 *                                      CallbackType,    (UIVAL) BasicCallback,
 *                                      NULL);
 *
 * --------------------------------------------------------------------------
 * Notes:
 *   Initial callbacks such as WinCreateEvent,WinNCxxx, etc. happen prior to
 *   knowning what the WindowId will be. These values are automatically
 *   updated during creation. Simply assume that these values will be
 *   inserted automatically.
 *
 *   FAILURE TO CAST PASSED PARAMETERS TO UIVAL, UIPTR OR UIFPTR WILL RESULT
 *   IN AN ACCESS VIOLATION (ACCTIO). REFER TO IMPLEMENTORS MANUAL FOR
 *   THE TABLE OF SPECIFICS. In general, all values are cast to UIVAL, all
 *   general pointer types are cast to UIPTR, and all method pointers are
 *   cast to UIFPTR to create 64 bit passed parameters.
 * -------------------------------------------------------------------------- */

#ifndef _CCALLBACK_H
#define _CCALLBACK_H

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(disable:4530)
#endif

#include <CEmptyBase.h>
#include <BTree.h>
#include <CMethod.h>

/* ------------------------------------------------------------
 * Character strings used to identify the various attributes
 * ------------------------------------------------------------ */

enum CallbackTypes { BasicCallback=0, CompositeCallback=1 };

extern const wchar_t* CallbackEventId;
extern const wchar_t* CallbackType;
extern const wchar_t* CallbackObjectId;
extern const wchar_t* CallbackWindowId;
extern const wchar_t* CallbackWindow;
extern const wchar_t* CallbackMethodPtr;
extern const wchar_t* CallbackData;
extern const wchar_t* CallbackError;

/* ------------------------------------------------------------
 * Use error unwind semantics only when required.
 * Pass -D_DEBUG to the compiler to enable error management.
 * ------------------------------------------------------------ */

#if defined(_DEBUG)

// Error enumeration
//

enum CallBackErrorType { CallBackUndefinedPointer=0,
			 CallBackUndefinedArgument=1,
			 CallBackUnknownError=2 };

// Callback exception object
//

class CallBackError
{
 public:
  CallBackError(CallBackErrorType nReason);
  ~CallBackError();

  const wchar_t* get_Reason();

  CallBackErrorType m_Reason;
};

#endif

/* ------------------------------------------------------------
 * The callback object.
 * ------------------------------------------------------------ */

class CCallBack : public CCallbackClass
{
 public:

  // Attributes
  //

  ulong               m_EventId;          // Message (or event)
  ObjectId            m_ObjectId;         // Specific identifier (eg. Button 101)
  WindowId            m_WindowId;         // WindowId (HWND/XWindow*/etc.)
  CEmptyBase*         m_Window;           // Superclass CWindowObject*
  void*               m_Data;             // User data
  CallbackMethod      m_CallbackMethod;   // Callback method pointer
  CallbackTypes       m_CallbackType;     // Type of callback (Basic/Composite)
  CallbackErrorMethod m_ErrorMethod;      // Callback error method
  ulong               m_CbStatus;         // Creation/Operation status

  // Constructor/Destructor
  //

  CCallBack();
  CCallBack(OCTSTR pArgType,...);
  CCallBack(OCTSTR pArgType,va_list);
  CCallBack(CEmptyBase* pWindow,va_list);
  ~CCallBack();

#if defined(_WIN32) || defined(_WIN64)
  CCallBack(HWND,UINT,WPARAM,LPARAM);
#endif

  // Accessors
  //

  CallbackTypes GetCallbackType();

 private:

  // Initializer
  //

  LRESULT VaSetupCallBack(OCTSTR pArgType,va_list vaList);
};

/* ------------------------------------------------------------
 * Definition (typedef) for an EventTree (Tree of CCallBack)
 * ------------------------------------------------------------ */

typedef BTree<CCallBack> EventTree;

#include <CCallBackIterator.h>

#endif
