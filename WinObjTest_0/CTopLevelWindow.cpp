/* ************************************************************
 * CTopLevelWindow
 *
 * CTopLevelWindow is considered to be a basic object. Every
 * window based application requires a top level window to
 * appear in.
 *
 * CTopLevelWindow adds a quit callback for the close window
 * decoration used in standard top level windows.
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * UNIX SPECIFIC:      REQUIRED
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#include <CTopLevelWindow.h>

// ------------------------------------------------------------
// CONSTRUCTOR(S) AND DESTRUCTORS
// ------------------------------------------------------------

CTopLevelWindow::CTopLevelWindow() : CWindowObject() {}

// Constructor used to build a top level window and
// connect it to the appropriate window class (event loop)
//

CTopLevelWindow::CTopLevelWindow(OCTSTR pWindowName,
				 OCTSTR pWindowClass,
				 ...) :
  CWindowObject()
{
  va_list vaList;

  va_start(vaList,pWindowClass);

  CWindowObject::InitCWindow(pWindowName,pWindowClass,vaList);

  va_end(vaList);
}

// Constructor used to build and initialize the window
// and connect it to the primary event loop. This
// constructor adds the exit procedure to the callback
// list.
//

CTopLevelWindow::CTopLevelWindow(CWindowApplication* pApp,
				 OCTSTR              pWindowName,
				 OCTSTR              pWindowClass,
				 ...) :
  CWindowObject()
{
  va_list vaList;
  va_start(vaList,pWindowClass);

  CWindowObject::InitCWindow(pWindowName,pWindowClass,vaList);

  pApp->AddWindow(this);

  CallbackMethod pMethod = (CallbackMethod)&CTopLevelWindow::Quit;

  pApp->VaAddCallback(this,
		      CallbackEventId,  (UIVAL)GetEventId(WinDestroyEvent),
		      CallbackType,     (UIVAL)BasicCallback,
		      CallbackObjectId, (UIVAL)m_ObjectId,
		      CallbackWindowId, (UIVAL)m_WindowId,
		      CallbackMethodPtr,(UIFPTR)pMethod,
		      NULL);

  va_end(vaList);
}

// Standard Destructor
//

CTopLevelWindow::~CTopLevelWindow() {}

// Close/Exit method
//

LRESULT CTopLevelWindow::Quit(WindowId wId,
			      ObjectId oId,
			      WPARAM wParam,
			      LPARAM lParam,
			      CCallBack* pCb)
{
#if defined(_WIN32) || defined(_WIN64)
  ::PostQuitMessage(0);
#endif
  return S_OK;
}
