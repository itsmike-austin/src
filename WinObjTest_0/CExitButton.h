/* ************************************************************
 * CExitButton
 *
 * CExitButton is considered to be a basic object. The style


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

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CEXIT_BUTTON_H
#define _CEXIT_BUTTON_H

#include "StdAfx.h"
#include <CPushButton.h>

class CExitButton : public CPushButton
{
 public:
  CExitButton();
  CExitButton(OCTSTR pWindowName,...);
  CExitButton(CWindowApplication* pApp,OCTSTR pWindowName,...);
  ~CExitButton();

  LRESULT Exit(WindowId wId,ObjectId oId,WPARAM wParam,LPARAM lParam,CCallBack* pCb);
};

#endif



