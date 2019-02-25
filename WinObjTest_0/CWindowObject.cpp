/* ************************************************************
 * Window is a basic object used to derive all other
 * window objects.
 * ------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005,2006
 * ************************************************************ */

#include <CWindowObject.h>
#include <CWindowApplication.h>

CWindowObject* m_WindowObject = NULL;

// ========================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
// ========================================================================

CWindowObject::CWindowObject() :
  m_WindowClass(UndefinedWindow),
  m_WindowName(NULL),
  m_WindowId(NULL),
  m_Parent(NULL),
  m_ParentId(NULL),
  m_ObjectId(0),
  m_X(0),
  m_Y(0),
  m_Height(0),
  m_Width(0),
  m_CallList(NULL),
  m_CallListSize(0),
#if defined(_WIN32) || defined(_WIN64)
  m_ClassName(NULL),
  m_Style(0),
  m_ExStyle(0),
  m_Inst(0),
  m_MdiParm(NULL),
#endif
  m_WindowStatus(0),
#if defined(_MT)
  m_AppLock(NULL),
#endif
  m_Realize(RealizeRed),
  m_Manage(false),
  m_ControlMethod(NULL),
  m_ShowCommand(0),
  m_CallbackPtr(NULL) {}

CWindowObject::CWindowObject(OCTSTR pWindowName,
			     OCTSTR pClassName,
			     ...) :
  m_WindowClass(UndefinedWindow),
  m_WindowName(NULL),
  m_WindowId(NULL),
  m_Parent(NULL),
  m_ParentId(NULL),
  m_ObjectId(0),
  m_X(0),
  m_Y(0),
  m_Height(0),
  m_Width(0),
  m_CallList(NULL),
  m_CallListSize(0),
#if defined(_WIN32) || defined(_WIN64)
  m_ClassName(NULL),
  m_Style(0),
  m_ExStyle(0),
  m_Inst(0),
  m_MdiParm(NULL),
#endif
  m_WindowStatus(0),
#if defined(_MT)
  m_AppLock(NULL),
#endif
  m_Realize(RealizeRed),
  m_Manage(false),
  m_ControlMethod(NULL),
  m_ShowCommand(0),
  m_CallbackPtr(NULL)
{
  va_list aList;

  va_start(aList,pClassName);
  m_WindowStatus = InitCWindow(pWindowName,pClassName,aList);
  va_end(aList);
}

CWindowObject::CWindowObject(OCTSTR  pWindowName,
			     OCTSTR  pClassName,
			     va_list vaList) :
  m_WindowClass(UndefinedWindow),
  m_WindowName(NULL),
  m_WindowId(NULL),
  m_Parent(NULL),
  m_ParentId(NULL),
  m_ObjectId(0),
  m_X(0),
  m_Y(0),
  m_Height(0),
  m_Width(0),
  m_CallList(NULL),
  m_CallListSize(0),
#if defined(_WIN32) || defined(_WIN64)
  m_ClassName(NULL),
  m_Style(0),
  m_ExStyle(0),
  m_Inst(0),
  m_MdiParm(NULL),
#endif
  m_WindowStatus(0),
#if defined(_MT)
  m_AppLock(NULL),
#endif
  m_Realize(RealizeRed),
  m_Manage(false),
  m_ControlMethod(NULL),
  m_ShowCommand(0),
  m_CallbackPtr(NULL)
{
  if ( NULL != vaList )
    m_WindowStatus = InitCWindow(pWindowName,pClassName,vaList);
}

CWindowObject::~CWindowObject()
{
#if defined(_WIN32) || defined(_WIN64)
  if ( ::IsWindowEnabled(m_WindowId) ) ::PostMessage(m_WindowId,WM_CLOSE,0,0);
#endif

#if defined(_MT)
  m_AppLock = NULL;
#endif
}

// ========================================================================
// MANAGEMENT METHODS
// ========================================================================

// ------------------------------------------------------------------------
// INITIALIZATION METHOD
//
// Build the window initialization parameters and realize the window
// if requested.
// ------------------------------------------------------------------------

LRESULT CWindowObject::InitCWindow(OCTSTR pWindowName,
				   OCTSTR pClassName,
				   va_list aList)
{
  wchar_t* pItem;
  OCTSTR   pValue;

  m_WindowStatus = S_OK;

  // Initialize local boolean attributes
  //

  bool     bCreateWindow = false;
  bool     bDoMore = true;

  // Save the window name
  //

  if ( NULL == pWindowName || NULL == pClassName )
    return (m_WindowStatus=E_POINTER);

  m_WindowName = pWindowName;
  m_ClassName  = pClassName;

  // Extract an argument from the list
  //

  while ( NULL != (pItem=va_arg(aList,wchar_t*)) )
    {
      if ( 0 == wcscmp(pItem,WindowClassName) )
	{
	  m_ClassName = (OCTSTR)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowX) )
	{
	  m_X = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowY) )
	{
	  m_Y = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowWidth) )
	{
	  m_Width = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowHeight) )
	{
	  m_Height = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowParent) )
	{
	  m_Parent = (CWindowObject*)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowParentId) )
	{
	  m_ParentId = (WindowId)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowInstance) )
	{
	  m_Inst = (HINSTANCE)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowStyle) )
	{
	  m_Style = (DWORD)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowStyleEx) )
	{
	  m_ExStyle = (DWORD)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowObjectId) )
	{
	  m_ObjectId = (ObjectId)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowRealize) )
	{
	  m_Realize = (0 == wcscmp((wchar_t*)va_arg(aList,UIPTR),WindowYes) ?
		       RealizeYellow : RealizeRed );
	}
      else if ( 0 == wcscmp(pItem,WindowManage) )
	{
	  m_Manage = (0 == wcscmp((wchar_t*)va_arg(aList,UIPTR),WindowYes) ?
		      true : false);
	}
      else
	{
	  // The entry is a style request. Check the
	  // Standard Style List first.
	  //

	  STYLE_DATA* pStyle = (STYLE_DATA*)StandardStyleList;

	  while( bDoMore && pStyle->StyleName )
	    {
	      if ( 0 == wcscmp(pItem,pStyle->StyleName) )
		{
		  pValue = (wchar_t*)va_arg(aList,UIPTR);

		  if ( 0 == wcscmp(pValue,EnableStyle) )
		    m_Style |= pStyle->StyleValue;
		  else
		    m_Style &= (((DWORD)-1) ^ pStyle->StyleValue); // A little windy

		  bDoMore = false;
		}
	      ++pStyle;
	    }

	  // Check the extended style list if not in
	  // the standard style list
	  //

	  pStyle = (STYLE_DATA*)ExtendedStyleList;

	  while( bDoMore && pStyle->StyleName )
	    {
	      if ( 0 == wcscmp(pItem,pStyle->StyleName) )
		{
		  pValue = (wchar_t*)va_arg(aList,UIPTR);

		  if ( 0 == wcscmp(pValue,EnableStyle) )
		    m_ExStyle |= pStyle->StyleValue;
		  else
		    m_ExStyle &= (((DWORD)-1) ^ pStyle->StyleValue); // A little windy

		  bDoMore = false;
		}
	      ++pStyle;
	    }

	  // See if this was a show command entry
	  //

	  pStyle = (STYLE_DATA*)ShowWindowOpList;

	  while( bDoMore && pStyle->StyleName )
	    {
	      if ( 0 == wcscmp(pItem,pStyle->StyleName) )
		{
		  pValue = (wchar_t*)va_arg(aList,UIPTR);

		  if ( 0 == wcscmp(pValue,EnableStyle) )
		    m_ShowCommand = pStyle->StyleValue;

		  bDoMore = false;
		}
	      ++pStyle;
	    }
	  // This was an unknown entry. Extract the value
	  // and go on.
	  //

	  if ( bDoMore ) (void)va_arg(aList,UIPTR);

	  bDoMore = true;
	}
    }

  // Assign the object id if required
  //

  if ( NULL != m_WindowApplication && 0 == m_ObjectId )
    {
      (void)m_WindowApplication->get_ObjectIdentifier(&m_ObjectId);
    }

#if defined(_MT)
  if ( NULL != m_WindowApplication && NULL == m_AppLock )
    {
      (void)m_WindowApplication->get_ApplicationLock(&m_AppLock);
    }
#endif

  return (LRESULT)m_WindowStatus;
}

// ----------------------------------------------------------------------------
// AddCallback
//
// Add a new callback to the callback list
// ----------------------------------------------------------------------------

LRESULT CWindowObject::AddCallback(CCallBack* pCb)
{
  CCallBack** pTemp;
  LRESULT     lRc = S_OK;

  if ( S_OK != m_WindowStatus )
    {
      lRc = m_WindowStatus;
    }
  else if ( NULL == pCb )
    {
      lRc = E_POINTER;
    }
#if defined(_MT)
  else if ( NULL != m_AppLock && S_OK != m_AppLock->IsItLocked() )
    {
      lRc = ERROR_NOT_LOCKED;
    }
#endif
  else if ( NULL == (pTemp = new CCallBack*[1+m_CallListSize]) )
    {
      m_WindowStatus = lRc = E_OUTOFMEMORY;
    }
  else
    {
      for( int i=0 ; i < m_CallListSize ; ++i ) pTemp[i] = m_CallList[i];
      pTemp[m_CallListSize] = pCb;
      if ( m_CallList ) delete m_CallList;
      m_CallList = pTemp;
      ++m_CallListSize;
    }

  return S_OK;
}

// ----------------------------------------------------------------------------
// DeleteCallback
//
// Remove a callback from the callback list.
// ----------------------------------------------------------------------------

LRESULT CWindowObject::DeleteCallback(CCallBack* pCallback)
{
  LRESULT     lRc = E_FAIL;
  CCallBack** pTemp;
  int         i       = 0;
  bool        bDoMore = false;

  // Make sure that this operation will succeed
  //

  if ( NULL == m_CallList || NULL == pCallback )
    {
      lRc = S_OK;
    }
#if defined(_MT)
  else if ( NULL != m_AppLock && S_OK != m_AppLock->IsItLocked() )
    {
      lRc = ERROR_NOT_LOCKED;
    }
#endif
  else
    {
      // Is the entry in the list?
      //

      for( i=0 ; i < m_CallListSize ; ++i )
	if ( m_CallList[i] == pCallback )
	  bDoMore = true;

      if ( !bDoMore )
	{
	  lRc = S_OK;
	}
      else if ( 1 == m_CallListSize )
	{
	  delete m_CallList;
	  m_CallListSize = 0;
	  m_CallList    = NULL;
	}
      else if ( NULL == (pTemp = new CCallBack*[m_CallListSize]) )
	{
	  lRc = E_OUTOFMEMORY;
	}
      else
	{
	  for( int i=0,j=0 ; i < m_CallListSize ; ++i )
	    {
	      if ( m_CallList[i] != pCallback )
		{
		  pTemp[j] = m_CallList[i];
		  ++j;
		}
	    }

	  delete m_CallList;
	  m_CallList = pTemp;
	  --m_CallListSize;

	  lRc = S_OK;
	}
    }

  return lRc;
}

// ----------------------------------------------------------------------------
// ManageGeometry
//
// Mark the window to be used in geometry calculations
// ----------------------------------------------------------------------------

LRESULT CWindowObject::ManageGeometry()
{
  m_Manage = true;
  return S_OK;
}

LRESULT CWindowObject::UnmanageGeometry()
{
  m_Manage = false;
  return S_OK;
}

BOOL CWindowObject::IsGeometryManaged()
{
  return (m_Manage ? TRUE : FALSE);
}

// ----------------------------------------------------------------------------
// RealizeWindow
//
// Create the window as specified.
// ----------------------------------------------------------------------------

LRESULT CWindowObject::RealizeWindow()
{
  LRESULT lRc = S_OK;

  // If the window is already realized (RealizeInstance?)
  // just return the existing status
  //

  if ( S_OK != m_WindowStatus )
    {
      m_Realize = RealizeYellow;
      lRc       = m_WindowStatus;
    }
  else  if ( NULL != m_WindowId || RealizeGreen == m_Realize )
    {
      lRc = m_WindowStatus;
    }
  else
    {
#if defined(_WIN32) || defined(_WIN64)

      // Create the window (Microsoft Style)
      //

      // Lock the application (if required) and setup the
      // window object pointer to guarantee that the
      // appropriate WindowId is placed inside the object
      // when the first message is received for the window.
      //

#if defined(_MT)
      if ( NULL == m_AppLock &&  NULL != m_WindowApplication )
	{
	  (void)m_WindowApplication->get_ApplicationLock(&m_AppLock);
	  if ( NULL == m_AppLock ) return ERROR_NOT_LOCKED;
	}

      m_AppLock->Lock();
#endif

      m_WindowObject = this;

#if 0

      // Note: This is the required adjustment
      //       especially the menu element!
      //       A menu is a window object, so
      //       hmenu on the create requires
      //       a few simple adjustments beyond
      //       hMenu = m_ObjectId if ObjectId
      //       is to be used as a multiple element
      //
      //       consider:
      //         CWindowObject* m_ObjectId
      //         CCallBack::m_ObjectId to CCallBack::m_EventObject
      //         to differentiate the elements. Have to work through
      //         CMenu to fulfill this adjustment
      //
      // XXX: TBD: MESSAGE ABOVE
      //
      // XXX: Not sure how to determine whether compound/composite
      //      object for event modification ... this mandates
      //      all callbacks for BasicWindowObject(s) be
      //      discovered just prior to the search method. This
      //      may have to be done anyway because the object id
      //      is a combination of the object id and event id
      //      during events on windows.
      //      ... This requires that the search change to
      //          m_ParentId && construct/deconstruct
      //          the event_id/object_id elements.
      // sln:      ... The callback type can be used to determine
      //          when to build this structure ...
      //          CompositeCallback --> build this structure
      //          during the first runtime pass ....
      //          ... PutWindowId can be used for this purpose.
      //      
      //  am i going in circles again ???? sure looks like it
      //   second half of search should use parent for window_id ????
      //   just keep checking.
      //

      // The object id must exist prior to getting here ... recheck construction
      // (CWindowObject::Init) (Redundant ...)
      //

      m_ObjectId = (0 == m_ObjectId && NULL != m_WindowApplication ?
		    m_WindowApplication->GetObjectIdentifier() : m_ObjectId);
#endif

      m_ParentId = (0 == m_ParentId && NULL != m_Parent ? m_Parent->m_WindowId : m_ParentId);

      HWND  hParent = (HWND) m_ParentId;
      HMENU hMenu   = (HMENU)m_ObjectId;

      WindowId pTemp = CreateWindowEx(m_ExStyle,
				      (LPCWSTR)m_ClassName,
				      (LPCWSTR)m_WindowName,
				      m_Style,
				      m_X,
				      m_Y,
				      m_Width,
				      m_Height,
				      hParent,
				      (HMENU)NULL, //hMenu,
				      m_Inst,
				      reinterpret_cast<LPVOID>(this));

      if ( NULL != pTemp )
	{
	  lRc        = m_WindowStatus = S_OK;
	  m_Realize  = RealizeGreen;

	  CompleteCallback(pTemp);
	}
      else
	{
	  LPVOID lpMsgBuf;

	  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);

	  MessageBox(NULL,(LPCWSTR)lpMsgBuf,(LPCWSTR)lpMsgBuf,MB_OK);

	  
	  lRc       = m_WindowStatus = ::GetLastError();
	  m_Realize = RealizeRed;

	}
#if defined(_MT)
      m_AppLock->Unlock();
#endif
    }
#endif

  return lRc;
}

// ----------------------------------------------------------------------------
// UnrealizeWindow
//
// Destory the window as specified.
// ----------------------------------------------------------------------------

LRESULT CWindowObject::UnrealizeWindow()
{
#if defined(_WIN32) || defined(_WIN64)
  // XXX: Finish checking this.
  // ? ::SendMessage(m_Window,WM_CLOSE,NULL,NULL);
  // ? ::DestroyWindow(m_WindowId);
  ::ShowWindow((HWND)m_WindowId,SW_HIDE);
#endif
  m_Realize = RealizeRed;
  return S_OK;
}

BOOL CWindowObject::IsWindowRealized()
{
  return (RealizeRed == m_Realize ? FALSE : TRUE);
}

// ----------------------------------------------------------------------------
// DoCallback
//
// Execute the current callback method pointer
// ----------------------------------------------------------------------------

LRESULT CWindowObject::DoCallback(void**     pMethod,
				  HWND       hWnd,
				  UINT       uMsg,
				  WPARAM     wParam,
				  LPARAM     lParam,
				  CCallBack* pCb)
{
  void** pFcnOffset = (void**)&this->m_CallbackPtr;

  *pFcnOffset = *pMethod;

  return (this->*m_CallbackPtr)(hWnd,uMsg,wParam,lParam,pCb);
}

// ========================================================================
// ACCESSOR METHODS
// ========================================================================

// ------------------------------------------------------------------------
// Window Identifier Accessor
// ------------------------------------------------------------------------

WindowId CWindowObject::GetWindowId() { return m_WindowId; }

WindowId CWindowObject::PutWindowId(WindowId wId)
{
  WindowId pTemp = m_WindowId;
  m_WindowId = wId;

  for( int i=0 ; i < m_CallListSize ; ++i ) m_CallList[i]->m_WindowId = wId;

  return pTemp;
}




// The object id might have to be changed if not defined already with
// a match to the composite object????


LRESULT CWindowObject::CompleteCallback(WindowId wId)
{
  int     i;
  bool    bDoMore = true;
  LRESULT lRc = (NULL != wId ? S_OK : E_INVALIDARG);

  // Verify args and operations
  //

  if ( S_OK != lRc || NULL != m_WindowId ) return lRc;

  // Determine the window class
  //

  for( i=0 ; i < m_CallListSize && bDoMore ; ++i )
    {
      if ( CompositeCallback == m_CallList[i]->m_CallbackType )
	{
	  m_WindowClass = CompositeWindow;
	  bDoMore = false;
	}
    }

  m_WindowClass = (UndefinedWindow == m_WindowClass ? BasicWindow : m_WindowClass);

  // Parent must exist for CompositeWindow
  //

  if ( CompositeWindow == m_WindowClass &&
       (NULL == m_Parent || NULL == m_Parent->m_WindowId) ) return E_FAIL;

  // Setup the attribute list
  //

  if ( BasicWindow == m_WindowClass )
    {
      m_WindowId = wId;

      for( i=0 ; i < m_CallListSize ; ++i )
	{
	  m_CallList[i]->m_ObjectId = m_ObjectId;
	  m_CallList[i]->m_WindowId = m_WindowId;
	}
    }
  else
    {
      m_WindowId = wId;
      m_ParentId = m_Parent->m_WindowId;
      m_ObjectId = ( 0 == m_ObjectId ?
		     m_WindowApplication->GetObjectIdentifier() :
		     m_ObjectId );
      ::SetWindowLong(wId,GWL_ID,(LONG)m_ObjectId);

      m_ControlMethod = NULL;

      for( i=0 ; i < m_CallListSize ; ++i )
	{
	  if ( CompositeCallback == m_CallList[i]->m_CallbackType )
	    {
#if defined(_WIN32) || defined(_WIN64)
	      m_CallList[i]->m_ObjectId =
		HIWORD(m_CallList[i]->m_EventId) | LOWORD(m_ObjectId);
	      m_CallList[i]->m_EventId = WM_COMMAND;
#endif
	      m_CallList[i]->m_WindowId = m_ParentId;
	    }
	  else
	    {
	      m_CallList[i]->m_ObjectId = m_ObjectId;
	      m_CallList[i]->m_WindowId = m_WindowId;
	    }
	}
    }

  return lRc;
}


  

       


#if 0
LRESULT CWindowObject::CompleteCallbacks(WindowId pWindowId)
{
  LRESULT lRc = S_OK;

  m_WindowId = pWindowId;

  // Make sure that the object identifier is valid
  //

  if ( 0 == m_ObjectId && NULL != m_WindowApplication )
    {
      m_ObjectId = m_WindowApplication->GetObjectIdentifier();
    }

  for( int i=0 ; i < m_CallListSize ; ++i )
    {
      if ( CompositeCallback == m_CallList[i]->m_CallbackType && m_Parent )
	{
	  lRc = (0 != m_CallList[i]->m_ObjectId && S_OK == lRc ? S_OK : E_INVALIDARG);

#if defined(_WIN32) || defined (_WIN64)

	  m_CallList[i]->m_ObjectId =
	    HIWORD(m_CallList[i]->m_EventId) |
	    LOWORD(m_CallList[i]->m_ObjectId);

	  m_CallList[i]->m_WindowId = m_ParentId = m_Parent->m_WindowId;
	  m_CallList[i]->m_EventId  = WM_COMMAND;
#endif
	}
      else if ( CompositeCallback == m_CallList[i]->m_CallbackType )
	{
	  m_CallList[i]->m_WindowId = m_WindowId;
	  m_CallList[i]->m_ObjectId = m_ObjectId;
	  lRc = (S_OK == lRc ? E_INVALIDARG : S_OK);
	}
      else
	{
	  m_CallList[i]->m_WindowId = m_WindowId;
	  m_CallList[i]->m_ObjectId = m_ObjectId;
	}
    }
  return lRc;
}
#endif


	  
	  

#if defined(_COM_MODULE)
LRESULT CWindowObject::get_WindowId(HWND* pWindowId)
{
  LRESULT lr = (pWindowId ? S_OK : E_POINTER);

  if ( pWindowId ) *pWindowId = m_WindowId;

  return lr;
}

LRESULT CWindowObject::put_WindowId(HWND hWndId)
{
  m_WindowId = hWndId;
  for( unsigned int i=0 ; i < m_CallListSize ; ++i )
    m_CallList[i]->m_WindowId = hWndId;
  return S_OK;
}

LRESULT CWindowObject::put_HWND(HWND hWnd)
{
  m_WindowId = hWnd;
  for( unsigned int i=0 ; i < m_CallListSize ; ++i )
    pCallList[i]->m_WindowId = hWnd;
  return S_OK;
}

LRESULT CWindowObject::get_HWND(HWND* pHwnd)
{
  LRESULT lRc = (NULL != pHwnd ? S_OK : E_POINTER);

  if ( NULL != pHwnd ) *pHwnd = m_WindowId;

  return lRc;
}
#endif

// ------------------------------------------------------------------------
// Event accessor methods
// ------------------------------------------------------------------------

DWORD CWindowObject::GetEventId(const wchar_t* pEventName)
{
  NAME_MASK_PAIR* pEvent  = (NAME_MASK_PAIR*)&WinEventList[0];

  while( NULL != pEvent->wName )
    {
      if ( 0 == wcscmp(pEvent->wName,pEventName) )
	{
	  return (DWORD)pEvent->uMask;
	}
      ++pEvent;
    }

  return (DWORD)0;
}

LRESULT CWindowObject::get_EventId(OCTSTR pEventName,DWORD* pEventId)
{
  LRESULT lRc = (NULL != pEventName && NULL != pEventId ? S_OK : E_POINTER);

  if ( S_OK != lRc ) return lRc;

  *pEventId = GetEventId((const wchar_t*)pEventName);

  return lRc;
}

// ------------------------------------------------------------------------
// Lock accessor methods
// ------------------------------------------------------------------------

LRESULT CWindowObject::AddAppLock(CApplicationLock* pLock)
{
  m_AppLock = pLock;
  return S_OK;
}

LRESULT CWindowObject::get_AppName(OCTSTR* pAppName)
{
  LRESULT lRc;

  if ( S_OK == (lRc = (pAppName ? S_OK : E_POINTER)) ) *pAppName = m_WindowName;
  return lRc;
}

// ------------------------------------------------------------------------
// Callback list accessor methods
//
// TBD:
// Should callbackiterator be embedded here as a new pointer?
// probably!
// ------------------------------------------------------------------------

CCallBack** CWindowObject::GetCallList()     { return m_CallList;     }
int         CWindowObject::GetCallListSize() { return m_CallListSize; }

// ----------------------------------------------------------------------------
// Conversion operators
// ----------------------------------------------------------------------------

CWindowObject::operator HWND() { return (HWND)m_WindowId; }

CWindowObject::operator CCallBack**() { return m_CallList; }
