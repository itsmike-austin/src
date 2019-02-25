/* ************************************************************
 * Windows Application is used to construct a new application
 *
 * CWindowsApplication maintains the list of windows and
 * callbacks required for event management. All new objects
 * are added to the system using
 * CWindowsApplication::AddObject(OCTSTR pObjectType,...)
 *
 * The default callback handler for windows resides in this
 * module.
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * UNIX SPECIFIC:      REQUIRED
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005)
 * ************************************************************ */

#include <CWindowApplication.h>

// ------------------------------------------------------------
// Global reference for application. This is required for
// callbacks to operate properly on Microsoft systems.
// ------------------------------------------------------------

CWindowApplication* m_WindowApplication = NULL;

#if defined(_WIN32) || defined(_WIN64)

// ------------------------------------------------------------
// Default callback entry point for Microsoft windows.
// ------------------------------------------------------------

LRESULT CALLBACK ItsConfiguredWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  LRESULT lRc = S_OK;

  // Build the callback structure and get the tree element
  //

  CCallBack  aCb(hWnd,uMsg,wParam,lParam);

  CCallBack* pCb = m_WindowApplication->FindCallback(&aCb);

  // A non-null callback pointer means this event has an entry
  //

  if ( NULL != pCb )
    {
      // Execute the requested callback
      //

      lRc = ((CWindowObject*)pCb->m_Window)->DoCallback((void**)&pCb->m_CallbackMethod,
							hWnd,uMsg,wParam,lParam,pCb);
    }
  else
    {
      // Call the default method handler
      //

      lRc = ::DefWindowProc(hWnd,uMsg,wParam,lParam);
    }

  return lRc;
}

LRESULT CALLBACK ItsDefWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  LRESULT lRc = S_OK;

  m_WindowObject->CompleteCallback((WindowId)hWnd);
  m_WindowApplication->CompleteCallback(m_WindowObject);

#pragma warning(disable:4311)

  if ( NULL != m_WindowObject->m_ControlMethod )
    {
#if 0
      void** pVoid = (void**)&(m_WindowObject->m_ControlMethod);
#endif
      // XXX: THIS IS WRONG (OF COURSE)
      //      ADDITIONAL REVIEW TO GET CORRECT LINKAGE
      // (POINTER TO AN OBJECT OF THE TYPE -- RECAST AND THEN
      //      EXECUTED THROUGH A DO ENTRY POINT
      //      WITH UPDATES TO THE WINDOW ATTRIBUTES AND DECODE LOOP
      //      TO PROPERLY IMPLEMENT
      //

      WNDPROC pPtr = m_WindowObject->m_ControlMethod;
      ::SetWindowLong(hWnd,GWL_WNDPROC,(LONG)pPtr);
      lRc = (*pPtr)(hWnd,uMsg,wParam,lParam);
    }
  else
    {
      ::SetWindowLong(hWnd,GWL_WNDPROC,(LONG)ItsConfiguredWndProc);
      lRc = ItsConfiguredWndProc(hWnd,uMsg,wParam,lParam);
    }

#pragma warning(default:4311)

  return lRc;

}
#endif

// ------------------------------------------------------------
// CONSTRUCTOR(S) AND DESTRUCTORS
// ------------------------------------------------------------

CWindowApplication::CWindowApplication() :
  CWindowClass(),
  m_AppLock(NULL),
  m_EventLock(NULL),
  m_Title(NULL),
  m_EventTree(NULL),
  m_WindowList(NULL),
  m_WindowListCount(0),
  m_Id(100)
{
  m_AppLock   = new CApplicationLock();
  m_EventLock = new CApplicationLock();
}

CWindowApplication::CWindowApplication(OCTSTR pAppName,
				       OCTSTR pAppClass,
				       ...) :
  CWindowClass(),
  m_AppLock(NULL),
  m_EventLock(NULL),
  m_Title(NULL),
  m_EventTree(NULL),
  m_WindowList(NULL),
  m_WindowListCount(0),
  m_Id(100)
{
  va_list aList;

  m_AppLock   = new CApplicationLock();
  m_EventLock = new CApplicationLock();

  va_start(aList,pAppClass);
  InitWindowClass(pAppClass,ItsDefWndProc,aList);

  if ( NULL == m_Title ) m_Title = pAppName;

  va_end(aList);
}

CWindowApplication::~CWindowApplication()
{
  if ( m_EventTree ) m_EventTree->DeleteTree();
  if ( m_AppLock   ) delete m_AppLock;
  if ( m_EventLock ) delete m_EventLock;

  m_EventTree = NULL;
  m_AppLock = m_EventLock = NULL;
}

/* ************************************************************
 *                     ACCESSOR METHODS
 * ************************************************************ */

// ------------------------------------------------------------
// GetObjectIdentifier
//
// Pull a new unique object identifier from the deck.
// ------------------------------------------------------------

long CWindowApplication::GetObjectIdentifier()
{
  long id;

  LockApplication();
  id = m_Id++;
  UnlockApplication();

  return id;
}

LRESULT CWindowApplication::get_ObjectIdentifier(ObjectId* pObjectId)
{
  LRESULT lRc = (NULL != pObjectId ? S_OK : E_POINTER);
  if ( S_OK == lRc )
    {
      *pObjectId = GetObjectIdentifier();
    }
  return lRc;
}

// ------------------------------------------------------------
// PutWindow
//
// Add a CWindowObject to the window object list
// ------------------------------------------------------------

LRESULT CWindowApplication::PutWindow(CWindowObject* pWindow)
{
  LRESULT lRc = (NULL != pWindow ? S_OK : E_POINTER);

  if ( S_OK == lRc )
    {
      m_EventLock->Lock();

      CWindowObject** pTemp = new CWindowObject*[1+m_WindowListCount];

      if ( NULL == pTemp ) return E_OUTOFMEMORY;

      for( int i=0 ; i < m_WindowListCount ; ++i ) pTemp[i] = m_WindowList[i];
      pTemp[m_WindowListCount] = pWindow;

      if ( m_WindowList ) delete m_WindowList;
      m_WindowList = pTemp;
      ++ m_WindowListCount;

      m_EventLock->Unlock();
    }

  return lRc;
}

LRESULT CWindowApplication::put_Window(CWindowObject* pWindow)
{
  return (NULL != pWindow ? PutWindow(pWindow) : E_POINTER);
}

// ------------------------------------------------------------
// Lock accessor methods
// ------------------------------------------------------------

CApplicationLock* CWindowApplication::GetApplicationLock()
{
  return m_AppLock;
}

LRESULT CWindowApplication::get_ApplicationLock(CApplicationLock** ppLock)
{
  LRESULT lRc = (NULL != ppLock ? S_OK : E_POINTER);

  if ( S_OK == lRc )
    {
      *ppLock = GetApplicationLock();
    }

  return lRc;
}

CApplicationLock* CWindowApplication::GetEventLock()
{
  return m_EventLock;
}

LRESULT CWindowApplication::get_EventLock(CApplicationLock** ppLock)
{
  LRESULT lRc = (NULL != ppLock ? S_OK : E_POINTER);

  if ( S_OK == lRc )
    {
      *ppLock = GetEventLock();
    }

  return lRc;
}

/* ************************************************************
 *                     MANAGEMENT METHODS
 * ************************************************************ */

// ------------------------------------------------------------
// LockApplication()
//
// Close both the application and event locks
// ------------------------------------------------------------

LRESULT CWindowApplication::LockApplication()
{
  m_AppLock->Lock();
  return m_EventLock->Lock();
}

LRESULT CWindowApplication::UnlockApplication()
{
  m_AppLock->Unlock();
  return m_EventLock->Unlock();
}

// ------------------------------------------------------------
// CompleteCallback(CWindowObject*)
//
// Complete construction of the event tree for a given
// window object
// ------------------------------------------------------------

LRESULT CWindowApplication::CompleteCallback(CWindowObject* pWinObj)
{
  CCallBackIterator ci(pWinObj->GetCallList(),pWinObj->GetCallListSize());
  CCallBack*        cp;

  bool bDoMore = true;

  // If the window already exists in the window tree, just return
  //

  m_AppLock->Lock();

  if ( TRUE == TreeContainsWindow(pWinObj->GetWindowId()) )
    {
      m_AppLock->Unlock();
      return S_OK;
    }

  // Add the events to the tree
  //

  while( (cp=ci()) )
    {
      if ( NULL == m_EventTree )
	{
#if defined(_MT)
	  m_EventTree = new EventTree(cp,(LPCRITICAL_SECTION)m_EventLock->GetLock());
#else
	  m_EventTree = new EventTree(cp);
#endif
	}
      else
	{
	  m_EventTree->Insert(cp);
	}

      m_EventTree = m_EventTree->BalanceTree();
    }


  m_AppLock->Unlock();

  return S_OK;
}

// ------------------------------------------------------------
// FindCallback
//
// Wrapper for finding a callback in the callback tree.
// ------------------------------------------------------------

CCallBack* CWindowApplication::FindCallback(CCallBack* pCb)
{
  return m_EventTree->Find(pCb);
}

// ------------------------------------------------------------
// GetCallbackTreeStatus
//
// Return the status of the existance of the callback tree.
// The tree must have at least one entry before executing
// the primary event loop.
// ------------------------------------------------------------

LRESULT CWindowApplication::GetCallbackTreeStatus()
{
  return (NULL != m_EventTree ? S_OK : E_POINTER);
}

// XXX: THIS METHOD REQUIRES THAT ERROR TRACKS BE CHECKED
// XXX: PRIOR TO RELEASE
// XXX: SEE NOTES IN CODE

// ------------------------------------------------------------
// VaAddCallback
//
// Add a callback to the event tree and the CallList of a
// CWindowObject. CWindowObject must maintain the list of
// callbacks to allow a WindowId to be correctly appended to
// all events scheduled for the window. When the window is
// originally created, there are callbacks (such as MAXMIN)
// that are called with the new window handle before the
// windows parameter handle can be accessed via a xx_xxCREATE
// message in windows.
// ------------------------------------------------------------

LRESULT CWindowApplication::VaAddCallback(CWindowObject* pWindow,
					  ...)
{
  va_list    vaList;
  bool       bDoMore = true;
  CCallBack* pCb;

  // Make sure the required base pointers exist
  //

  LRESULT lRc = (NULL != pWindow ? S_OK : E_POINTER);

  if ( S_OK == lRc )
    {
      // Build the callback
      //

      va_start(vaList,pWindow);

      if ( NULL == (pCb = new CCallBack(pWindow,vaList)) )
	{
	  lRc = E_OUTOFMEMORY;
	}
      else
	{

#if 0
	  // THIS HAPPENS WHEN THE EVENTTREE IS EMPTY AND SHOULD
	  // HAPPEN IN THE GO PROCEDURE IN LIEU OF HERE

	  // If the window identifier is -1, there are no callbacks
	  // for the window.
	  //

	  if ( (CWindowObject*)-1 == pWindow ) return S_OK;
#endif

	  // Add the window to the window list if required
	  //

	  m_AppLock->Lock();

	  for( int i=0 ; i < m_WindowListCount && bDoMore ; ++i )
	    {
	      if ( m_WindowList[i] == pWindow ) bDoMore = false;
	    }

	  if ( bDoMore )
	    {
	      CWindowObject** pTemp = new CWindowObject*[1+m_WindowListCount];

	      if ( NULL == pTemp )
		{
		  lRc = E_OUTOFMEMORY;
		}
	      else
		{
		  for( int i=0 ; i < m_WindowListCount ; ++i ) pTemp[i] = m_WindowList[i];

		  pTemp[m_WindowListCount] = pWindow;

		  if ( m_WindowList ) delete m_WindowList;
		  m_WindowList = pTemp;
		  ++m_WindowListCount;
		}
	    }

	  // Add the callback to the window callback list to
	  // enable adding the window id during realization.
	  //

	  lRc = (S_OK == lRc ? pWindow->AddCallback(pCb) : lRc);

	  m_AppLock->Unlock();
	}

      va_end(vaList);
    }

  return lRc;
}

// ------------------------------------------------------------
// VaAddWindow
//
// Create a new window from a variatic parameter list. Add the
// window to the application window list (for deletion).
// ------------------------------------------------------------

CWindowObject* CWindowApplication::VaAddWindow(OCTSTR pObjectName,
					       OCTSTR pObjectClass,
					       ...)
{
  va_list         vaList;
  CWindowObject** pTemp;

  // Create an empty window object
  //

  CWindowObject* pNew = new CWindowObject();

  if ( NULL == pNew ) return pNew;

  // Build the new window list
  //

  m_AppLock->Lock();

  pTemp = new CWindowObject*[1+m_WindowListCount];

  if ( NULL == pTemp )
    {
      m_AppLock->Unlock();
      return (CWindowObject*)NULL;
    }

  // Complete building the new window list
  //

  for( int i=0 ; i < m_WindowListCount ; ++i ) pTemp[i] = m_WindowList[i];

  pTemp[m_WindowListCount] = pNew;

  // Access the parameter list for the new window
  //

  va_start(vaList,pObjectClass);

  m_WindowApplication = this;

  // Initialize the new window and adjust the window list
  //

  if ( S_OK == pNew->InitCWindow(pObjectName,pObjectClass,vaList) &&
       S_OK == pNew->AddAppLock(m_AppLock) )
    {
      if ( m_WindowList ) delete m_WindowList;
      m_WindowList = pTemp;
      ++m_WindowListCount;
    }
  else
    {
      delete pTemp;
      delete pNew;
      pNew = NULL;
    }

  m_AppLock->Unlock();

  return pNew;
}

// ------------------------------------------------------------
// AddWindow
//
// Create a new window from a variatic parameter list. Add the
// window to the application window list (for deletion).
// ------------------------------------------------------------

LRESULT CWindowApplication::AddWindow(CWindowObject* pWindow)
{
  LRESULT         lRc = S_OK;
  CWindowObject** pTemp;
  bool            bDoMore = true;

  // Lock the application and search through the window list
  //

  m_AppLock->Lock();

  for( int i=0 ; i < m_WindowListCount && bDoMore ; ++i )
    {
      if ( m_WindowList[i] == pWindow ) bDoMore = false;
    }

  // If the window is not in the list, add it
  //

  if ( bDoMore )
    {
      pTemp = new CWindowObject*[1+m_WindowListCount];

      if ( NULL != pTemp )
	{
	  for( int i=0 ; i < m_WindowListCount ; ++i ) pTemp[i] = m_WindowList[i];
	  pTemp[m_WindowListCount] = pWindow;
	  if ( m_WindowList ) delete m_WindowList;
	  m_WindowList = pTemp;
	  ++m_WindowListCount;
	}
      else
	{
	  lRc = E_OUTOFMEMORY;
	}
    }

  // Unlock the application and return the status
  //

  m_AppLock->Unlock();

  return lRc;
}

// ------------------------------------------------------------
// TreeContainsWindow
//
// See if the event tree contains a specific window.
// ------------------------------------------------------------

int CWindowApplication::TreeContainsWindow(WindowId wId)
{
  CCallBack** ppList;
  int         nListSize;
  bool        bFoundIt = false;

  if ( NULL == m_EventTree ) return FALSE;

  ppList    = m_EventTree->GetSortedItemList();
  nListSize = m_EventTree->GetCount();

  for( int i=0 ; i < nListSize && !bFoundIt ; ++i )
    {
      if ( wId == ppList[i]->m_WindowId )
	{
	  bFoundIt = true;
	}
    }

  if ( ppList ) delete ppList;

  return (int)(bFoundIt ? TRUE : FALSE);
}

// ------------------------------------------------------------
// Go
//
// Primary event pump method.
// Check the callback tree. There must be at least one window
// and one callback before creating the any new windows. All
// windows are created here.
// ------------------------------------------------------------

LRESULT CWindowApplication::Go(CWindowObject* pWindow)
{
#if defined(_WIN32) || defined(_WIN64)
  MSG msg;
  HWND hWnd = (HWND)*pWindow;

  // Check to make sure that the event loop has at least one
  // entry in it. Add a default entry if none exists.
  //

#if defined(_MT)
  LockApplication();
#endif

  m_WindowApplication = this;

  // Realize the windows now the callback structure is in place.
  //

  for( int i=0 ; i < m_WindowListCount ; ++i )
    {
      m_WindowObject = m_WindowList[i];
      m_WindowObject->RealizeWindow();
      CompleteCallback(m_WindowObject);
    }

#if defined(_MT)
  UnlockApplication();
#endif

  // Pop the requested window up and start the event loop
  //

  ::UpdateWindow(hWnd);
  ::ShowWindow(hWnd,SW_SHOW);

  int nRc;

  while( (nRc = ::GetMessage(&msg,NULL,0,0)) )
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }

  return msg.wParam;
#endif
}

// ------------------------------------------------------------
// EventTree::Compare
//
// Method to determine equality of two callback objects.
// This method is used to create the proper placement for
// each of the callback objects and determine if there is
// a match for a specific window/event combination.
// ------------------------------------------------------------

int BTree<class CCallBack>::Compare(class CCallBack* pVal,class CCallBack* pExtVal)
{
  int nRc;

  if ( !pExtVal && !pVal )
    {
      nRc = 0;
    }
  else if ( (pExtVal && !pVal) || (!pExtVal && pVal) )
    {
      nRc = -1;
    }
  else
    {
      // If match, we're done. Sense may appear backwards,
      // so this will actually build an enantiomeric tree.
      //

      nRc = (pExtVal->m_WindowId     == pVal->m_WindowId &&
	     pExtVal->m_EventId      == pVal->m_EventId  &&
	     pExtVal->m_ObjectId     == pVal->m_ObjectId  ?  0 :
	     (pExtVal->m_WindowId     < pVal->m_WindowId  ? -1 :
	      (pExtVal->m_WindowId    > pVal->m_WindowId  ?  1 :
	       (pExtVal->m_EventId    < pVal->m_EventId   ? -1 :
		(pExtVal->m_EventId   > pVal->m_EventId   ?  1 :
		 (pExtVal->m_ObjectId < pVal->m_ObjectId  ? -1 : 1))))));
    }

  return nRc;
}

#if 0
static const CallbackTypes cBase = BasicCallback;

int BTree<class CCallBack>::Compare(class CCallBack* pVal,class CCallBack* pExtVal)
{
  int nRc;

  if ( !pExtVal && !pVal )
    {
      nRc = 0;
    }
  else if ( (pExtVal && !pVal) || (!pExtVal && pVal) )
    {
      nRc = -1;
    }
  else if ( BasicCallback == pVal->m_CallbackType )
    {
      // XXX: A computed goto might be quicker.
      // XXX: Check using windiff, eventdiff (and objectdiff) with
      //      a single catch at the end (smallest value)

      // If match, we're done
      //

      nRc = (pExtVal->m_WindowId == pVal->m_WindowId &&
	     pExtVal->m_EventId  == pVal->m_EventId   ? 0  : 1);

      // Setup return value
      //

      nRc = (0 != nRc                                  ?
	     (pExtVal->m_WindowId   < pVal->m_WindowId ? -1 :
	      (pExtVal->m_WindowId  > pVal->m_WindowId ?  1 :
	       (pExtVal->m_EventId  < pVal->m_EventId  ? -1 :
		(pExtVal->m_EventId > pVal->m_EventId  ?  1 : 0)))) : 0);
    }
  else
    {
      // If match, we're done
      //

      nRc = (pExtVal->m_WindowId == pVal->m_WindowId &&
	     pExtVal->m_EventId  == pVal->m_EventId  &&
	     pExtVal->m_ObjectId == pVal->m_ObjectId ? 0 : 1);

      // Setup return value
      //

      nRc = (0 != nRc                                     ?
	     (pExtVal->m_WindowId      < pVal->m_WindowId ? -1 :
	      (pExtVal->m_WindowId     > pVal->m_WindowId ?  1 :
	       (pExtVal->m_EventId     < pVal->m_EventId  ? -1 :
		(pExtVal->m_EventId    > pVal->m_EventId  ?  1 :
		 (pExtVal->m_ObjectId  < pVal->m_ObjectId ? -1 :
		  (pExtVal->m_ObjectId > pVal->m_ObjectId ?  1 : 0)))))) : 0);
    }

  return nRc;
}

#endif
