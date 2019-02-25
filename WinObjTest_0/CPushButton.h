/* ************************************************************
 * CPushButton is used to create various push button types.
 *
 * They are:
 *
 *   PushButton:       3D Push Button
 *   DefPushButton:    3D Push Button with highlights
 *   OwnerDrawnButton: Owner draws the button
 *   BitmapButton:     Place a bitmap in the button
 *   IconButton:       Place an icon in the button
 *   FlatButton:       Basic non-3D button
 *
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * UNIX SPECIFIC:      REQUIRED
 *
 * Note: Refer to the implementors manual for a complete list
 *       of the available styles and methods.
 * 
 * ------------------------------------------------------------
 * EXAMPLE
 *
 * CWindowObject* pButton = new CPushButton(&m_Application,
 *                                          L"ButtonName",
 *                                          WindowControlParent, (UIPTR)pParent,
 *                                          WindowX,             (UIVAL)0,
 *                                          WindowY,             (UIVAL)0,
 *                                          WindowHeight,        (UIVAL)50,
 *                                          WindowWidth,         (UIVAL)100,
 *                                          NULL);
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CPUSH_BUTTON_H
#define _CPUSH_BUTTON_H

#include "StdAfx.h"
#include <CWindowApplication.h>
#include <CWindowObject.h>
#include <WindowButton.h>

extern CWindowApplication* m_WindowApplication;

// ------------------------------------------------------------
// CPushButton
// ------------------------------------------------------------

class CPushButton : public CWindowObject
{
 protected:
  CWindowApplication* m_App;

public:
  // Constructors/Destrutor
  //

  CPushButton();
  CPushButton(OCTSTR pWindowName,...);
  CPushButton(CWindowApplication* pApp,OCTSTR pWindowName,...);
  ~CPushButton();

  // Initialization methods
  //

  LRESULT InitPushButton(OCTSTR pWindowName,va_list);
  LRESULT InitPushButton(OCTSTR pWindowName,...);

  // Accessor methods
  //

  DWORD   GetEventId(const wchar_t* pEventName);
  LRESULT get_EventId(OCTSTR pEventName,DWORD* pEventId);

  LRESULT             put_WindowApplication(CWindowApplication*  pApp);
  LRESULT             get_WindowApplication(CWindowApplication** ppApp);
  CWindowApplication* GetWindowApplication();

};

#endif
