/* ************************************************************
 * Windows Application is used to construct a new application
 *
 * CWindowsApplication maintains the list of windows and
 * callbacks required for event management. All new objects
 * are added to the system using
 * CWindowsApplication::AddObject(OCTSTR pObjectType,...)
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

#ifndef _CWINDOW_APPLICATION_H
#define _CWINDOW_APPLICATION_H

#include "StdAfx.h"
#include <WindowAttributes.h>
#include <WindowMessages.h>
#include <CWindowClass.h>
#include <CWindowObject.h>
#include <BTree.h>
#include <CCallBack.h>
#include <CCallbackIterator.h>

// Still need to fix this to handle atomic values
//

class CWindowId
{
 public:
  WindowId m_WindowId;
  CWindowId(WindowId wId) : m_WindowId(wId) {}
};

typedef BTree<CWindowId> WindowTree;

// ------------------------------------------------------------
// CWindowApplication
// ------------------------------------------------------------

class CWindowApplication : public CWindowClass
{
 private:
  OCTSTR          m_Title;               // Title of the application
  EventTree*      m_EventTree;           // Callback event tree
  CWindowObject** m_WindowList;          // List of window objects
  int             m_WindowListCount;
  long            m_Id;                  // Used for ObjectId

 public:

  // Application locks
  //

  CApplicationLock* m_AppLock;
  CApplicationLock* m_EventLock;

  // Constructors/Destructor
  //

  CWindowApplication();
  CWindowApplication(OCTSTR pApplicationName,OCTSTR pApplicationClass,...);
  ~CWindowApplication();

  // Attribute Accessor Methods
  //

  long           GetObjectIdentifier();
  LRESULT        get_ObjectIdentifier(ObjectId* pObjectId);

  LRESULT        PutWindow (CWindowObject* pWindow);
  LRESULT        put_Window(CWindowObject* pWindow);

  CApplicationLock* GetApplicationLock();
  LRESULT           get_ApplicationLock(CApplicationLock** ppAppLock);
  CApplicationLock* GetEventLock();
  LRESULT           get_EventLock(CApplicationLock** ppEventLock);

  // Application Management Methods
  //

  LRESULT        LockApplication();
  LRESULT        UnlockApplication();

  // Callback management methods
  //

  LRESULT        CompleteCallback(CWindowObject* pWinObject);
  CCallBack*     FindCallback(CCallBack* pCallback);
  LRESULT        GetCallbackTreeStatus();

  LRESULT        VaAddCallback(CWindowObject* pWin,...);

  // Window management methods
  //

  CWindowObject* VaAddWindow(OCTSTR pWindowName,OCTSTR pWindowClass,...);
  LRESULT        AddWindow(CWindowObject* pWindow);
  int            TreeContainsWindow(WindowId wWindowIdentifier);

  // Initiate application loop
  //

  LRESULT        Go(CWindowObject* pWindow);

};

// Compare method used to locate callbacks
//

virtual int BTree<class CCallBack>::Compare(class CCallBack*,class CCallBack*);

// Global definition used to aid event loop
//

extern CWindowApplication* m_WindowApplication;

#endif
