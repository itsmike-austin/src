/* ************************************************************
 * Callbacks are code elements executed in response to
 * various events.
 * ------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************ */

#include <CCallBack.h>

/* ----------------------------------------------------------------------
 * Character strings used to identify the various attributes
 * ---------------------------------------------------------------------- */

const wchar_t* CallbackEventId   = L"EventId";
const wchar_t* CallbackType      = L"CallType";
const wchar_t* CallbackObjectId  = L"ObjectId";
const wchar_t* CallbackWindowId  = L"WindowID";
const wchar_t* CallbackWindow    = L"Window";
const wchar_t* CallbackMethodPtr = L"Method";
const wchar_t* CallbackData      = L"Data";
const wchar_t* CallbackError     = L"Error";

/* ----------------------------------------------------------------------
 * Error management methods when exception handling is compiled into the
 * code base.
 * ---------------------------------------------------------------------- */

#if defined(_DEBUG)
static const wchar_t* m_CallbackError[] = {
  L"Undefined callback pointer",
  L"Unknown argument",
  L"Unknown callback error",
  (wchar_t*)NULL
};

CallBackError::CallBackError(CallBackErrorType nReason) : m_Reason(nReason) {}
CallBackError::~CallBackError() {}
#endif

/* ----------------------------------------------------------------------
 * Constructor/Destructors for callback objects.
 * ---------------------------------------------------------------------- */

CCallBack::CCallBack() :
  m_EventId(0),
  m_ObjectId(0),
  m_Window(NULL),
  m_WindowId(NULL),
  m_Data(NULL),
  m_CallbackMethod(NULL),
  m_ErrorMethod(NULL),
  m_CallbackType(BasicCallback),
  m_CbStatus(S_OK)
 {}

CCallBack::CCallBack(OCTSTR pArgType,...) :
  m_EventId(0),
  m_ObjectId(0),
  m_Window(NULL),
  m_WindowId(NULL),
  m_Data(NULL),
  m_CallbackMethod(NULL),
  m_ErrorMethod(NULL),
  m_CallbackType(BasicCallback),
  m_CbStatus(S_OK)
{
  // Start the variatic list and fill in the callback
  //

  va_list vaList;
  va_start(vaList,pArgType);
  m_CbStatus = VaSetupCallBack(pArgType,vaList);
  va_end(vaList);

  // Throw an appropriate callback if debugging information is required
  //

#if defined(_DEBUG)
  if ( S_OK == m_CbStatus && NULL != m_CallbackMethod )
    {
      return;
    }
  else if ( S_OK == m_CbStatus )
    {
      throw CallBackError(CallBackUndefinedPointer);
    }
  else if ( E_INVALIDARG == m_CbStatus )
    {
      throw CallBackError(CallBackUndefinedArgument);
    }
  else
    {
      throw CallBackError(CallBackUnknownError);
    }
#endif
}

CCallBack::CCallBack(OCTSTR pArgType,va_list vaList) :
  m_EventId(0),
  m_ObjectId(0),
  m_Window(NULL),
  m_WindowId(NULL),
  m_Data(NULL),
  m_CallbackMethod(NULL),
  m_ErrorMethod(NULL),
  m_CallbackType(BasicCallback),
  m_CbStatus(S_OK)
{
  // Fill in the callback data
  //

  m_CbStatus = VaSetupCallBack(pArgType,vaList);

  // Throw an appropriate callback if debugging information is required
  //

#if defined(_DEBUG)
  if ( S_OK == m_CbStatus && NULL != m_CallbackMethod )
    {
      return;
    }
  else if ( S_OK == m_CbStatus )
    {
      throw CallBackError(CallBackUndefinedPointer);
    }
  else if ( E_INVALIDARG == m_CbStatus )
    {
      throw CallBackError(CallBackUndefinedArgument);
    }
  else
    {
      throw CallBackError(CallBackUnknownError);
    }
#endif
}

CCallBack::CCallBack(CEmptyBase* pWindow,va_list vaList) :
  m_EventId(0),
  m_ObjectId(0),
  m_Window(pWindow),
  m_WindowId(NULL),
  m_Data(NULL),
  m_CallbackMethod(NULL),
  m_ErrorMethod(NULL),
  m_CallbackType(BasicCallback),
  m_CbStatus(S_OK)
{
  wchar_t* pArg = va_arg(vaList,wchar_t*);
  m_CbStatus = VaSetupCallBack(pArg,vaList);
}

#if defined(_WIN32) || defined(_WIN64)
CCallBack::CCallBack(HWND   hWnd,
		     UINT   uInt,
		     WPARAM wParam,
		     LPARAM lParam) :
  m_WindowId((WindowId)hWnd),
  m_EventId((ulong)uInt),
  m_ObjectId((ObjectId)wParam),
  m_Data((void*)lParam),
  m_CbStatus(0)
 {}
#endif

CCallBack::~CCallBack() {}

CallbackTypes CCallBack::GetCallbackType() { return m_CallbackType; }

/* ----------------------------------------------------------------------
 * Callback setup method.
 * ---------------------------------------------------------------------- */

LRESULT CCallBack::VaSetupCallBack(wchar_t* pArgType,va_list vaList)
{
  wchar_t* pType   = (wchar_t*)pArgType;
  bool     bDoMore = true;
  
  LRESULT lRc = (NULL != pType && vaList ? S_OK : E_POINTER);

  if ( S_OK != lRc ) return lRc;

  while( NULL != pType && bDoMore )
    {
      if ( 0 == wcscmp(CallbackEventId,pType) )
	{
	  m_EventId = (EventId)va_arg(vaList,UIVAL);
	}
      else if ( 0 == wcscmp(CallbackType,pType) )
	{
	  m_CallbackType = (CallbackTypes)va_arg(vaList,UIVAL);
	}
      else if ( 0 == wcscmp(CallbackObjectId,pType) )
	{
	  m_ObjectId = (ObjectId)va_arg(vaList,UIVAL);
	}
      else if ( 0 == wcscmp(CallbackWindowId,pType) )
	{
	  m_WindowId = (WindowId)va_arg(vaList,UIVAL);
	}
      else if ( 0 == wcscmp(CallbackWindow,pType) )
	{
	  m_Window = (CEmptyBase*)va_arg(vaList,UIPTR);
	}
      else if ( 0 == wcscmp(CallbackMethodPtr,pType) )
	{
	  m_CallbackMethod = (CallbackMethod)va_arg(vaList,UIFPTR);
	}
      else if ( 0 == wcscmp(CallbackData,pType) )
	{
	  m_Data = (void*)va_arg(vaList,UIPTR);
	}
      else if ( 0 == wcscmp(CallbackError,pType) )
	{
	  m_ErrorMethod = (CallbackErrorMethod)va_arg(vaList,UIFPTR);
	}
      else
	{
	  bDoMore = false;
	  lRc = E_INVALIDARG;
	}

      if ( bDoMore ) pType = (wchar_t*)va_arg(vaList,wchar_t*);
    }

#if 0
#if defined(_WIN32) || defined(_WIN64)
  if ( CompositeCallback == m_CallbackType )
    {
      m_ObjectId = HIWORD(m_EventId) | LOWORD(m_ObjectId);
      m_EventId  = WM_COMMAND;
    }
#endif
#endif

  return lRc;
}
