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

#ifndef _TOPLEVEL_WINDOW_H
#define _TOPLEVEL_WINDOW_H

#include "StdAfx.h"
#include <CWindowApplication.h>
#include <CWindowObject.h>

class CTopLevelWindow : public CWindowObject
{
  friend CWindowObject;

 public:

  // Constructor/Destructors
  //

  CTopLevelWindow();
  CTopLevelWindow(OCTSTR pWindowName,OCTSTR pWindowClass,...);
  CTopLevelWindow(CWindowApplication* pApp,OCTSTR pWindowName,OCTSTR pWindowClass,...);
  ~CTopLevelWindow();

  // Exit method
  //

  LRESULT Quit(WindowId wId,ObjectId oId,WPARAM wParam,LPARAM lParam,CCallBack* pCb);
};

#endif
