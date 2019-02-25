#include <CPushButton.h>

CPushButton::CPushButton() :CWindowObject(),m_App(NULL) {}

CPushButton::CPushButton(OCTSTR pWindowName,...) :
  m_App(NULL),
  CWindowObject()
{
  va_list vaList;

  va_start(vaList,pWindowName);

  InitPushButton(pWindowName,vaList);

  va_end(vaList);
}

CPushButton::CPushButton(CWindowApplication* pApp,
			 OCTSTR              pWindowName,
			 ...) :
  m_App(pApp),
  CWindowObject()
{
  va_list vaList;

  va_start(vaList,pWindowName);

  InitPushButton(pWindowName,vaList);

  va_end(vaList);
}

CPushButton::~CPushButton() {}

LRESULT CPushButton::InitPushButton(OCTSTR  pWindowName,
				    va_list vaList)
{
  wchar_t* pItem;
  OCTSTR   pValue;

  LIST_DATA*      pAttributeList;
  NAME_MASK_PAIR* pNameValue;

  if( NULL == pWindowName ) return E_POINTER;

  bool     bDoMore = true;

  // Setup the window object class
  //

  CWindowObject::InitCWindow(pWindowName,L"BUTTON",vaList);

  if ( S_OK != m_WindowStatus ) return m_WindowStatus;

  // Set the valid style bits for this type of application
  //
  // THE WS_CHILD AND WS_VISIBLE ATTRIBUTES MUST BE SET FOR
  // WINDOWS APPLICATIONS!
  //

  while( NULL != (pItem = va_arg(vaList,wchar_t*)) )
    {
      bDoMore        = true;
      pAttributeList = (LIST_DATA*)&PushButtonAttributes[0];

      while( NULL != pAttributeList->wListName && bDoMore )
	{
	  pNameValue = (NAME_MASK_PAIR*)pAttributeList->pNameMaskPair;

	  while( NULL != pNameValue->wName && bDoMore )
	    {
	      if ( 0 == wcscmp(pItem,pNameValue->wName) )
		{
		  pValue = (wchar_t*)va_arg(vaList,UIPTR);

		  if ( 0 == wcscmp(pValue,EnableStyle) )
		    {
		      m_Style |= pNameValue->uMask;
		    }
		  else
		    {
		      m_Style &= (((DWORD)-1) ^ pNameValue->uMask); // A little windy
		    }
		  bDoMore  = false;
		}

	      else
		{
		  ++pNameValue;
		}
	    }
	  ++pAttributeList;
	}

      if ( bDoMore ) (void)va_arg(vaList,UIPTR);

    }

#if defined(_WIN32) || defined(_WIN64)
  m_Style |= (WS_CHILD | WS_VISIBLE);
#endif

  return S_OK;
}

LRESULT CPushButton::InitPushButton(OCTSTR pWindowName,
				    ...)
{
  LRESULT lRc;
  va_list vaList;

  va_start(vaList,pWindowName);

  lRc = InitPushButton(pWindowName,vaList);

  va_end(vaList);

  return lRc;
}

DWORD CPushButton::GetEventId(const wchar_t* pEventName)
{
  // XXX: TBD: Review to see if the default callbacks should
  //           be listed with a LIST_DATA object as well
  //

  wchar_t* pName;

#if 0
  NAME_MASK_PAIR* pCallList = (NAME_MASK_PAIR*)ButtonRequestList;
#else
  NAME_MASK_PAIR* pCallList = (NAME_MASK_PAIR*)ButtonActionList;
#endif

  while( NULL != (pName=(wchar_t*)pCallList->wName) )
    {
      if ( 0 == wcscmp(pName,pEventName) ) return pCallList->uMask;
      ++pCallList;
    }

  return (DWORD)0;
}

LRESULT CPushButton::get_EventId(OCTSTR pEventName,DWORD* pMask)
{
  LRESULT lRc = (NULL != pEventName && NULL != pMask ? S_OK : E_POINTER);

  if ( S_OK == lRc )
    {
      *pMask = GetEventId(pEventName);
    }
  else if ( NULL != pMask )
    {
      *pMask = NULL;
    }

  return lRc;
}

LRESULT CPushButton::put_WindowApplication(CWindowApplication* pApp)
{
  LRESULT lRc = (pApp ? S_OK : E_POINTER);
  m_App = pApp;
  return lRc;
}

LRESULT CPushButton::get_WindowApplication(CWindowApplication** ppApp)
{
  LRESULT lRc = (ppApp ? S_OK : E_POINTER);
  *ppApp = m_App;
  return lRc;
}

CWindowApplication* CPushButton::GetWindowApplication()
{
  return m_App;
}
