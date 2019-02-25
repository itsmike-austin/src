/* ************************************************************
 * Window is a basic object used to derive all other
 * window objects.
 * ------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005,2006
 * ************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CWINDOW_OBJECT_H
#define _CWINDOW_OBJECT_H

#include <WindowAttributes.h>
#include <WindowMessages.h>
#include <CCallBack.h>
#include <CApplicationLock.h>

/* -------------------------------------------------------------------------
 * Creation method indicator levels.
 * ------------------------------------------------------------------------- */

enum WindowClass { UndefinedWindow=0, BasicWindow=1, CompositeWindow=2 };
enum WindowRealizeAttribute { RealizeGreen=0, RealizeYellow=1, RealizeRed=2 };

/* -------------------------------------------------------------------------
 * A Window Object
 * ------------------------------------------------------------------------- */

class CWindowObject : public CEmptyBase
{
 protected:
  WindowClass            m_WindowClass;        // Type of window
  OCTSTR                 m_WindowName;         // Name(Title) of this window
  WindowId               m_WindowId;           // Identifier of this window
  WindowId               m_ParentId;           // Identifier of window parent (NULLOK)
  CWindowObject*         m_Parent;             // Identifier of window parent
  ObjectId               m_ObjectId;           // Event object identifier
  long                   m_X;                  // X-Position
  long                   m_Y;                  // Y-Position
  long                   m_Height;             // Height
  long                   m_Width;              // Width

  int                    m_CallListSize;       // Array size for the callback list
  CCallBack**            m_CallList;           // Callback array

  CApplicationLock*      m_AppLock;            // Application level lock

#if defined(_WIN32) || defined(_WIN64)
  OCTSTR                 m_ClassName;          // Window class
  DWORD                  m_Style;              // Window style
  DWORD                  m_ExStyle;            // Window extended style
  HINSTANCE              m_Inst;               // Window instance

  // This belongs in its own area in a subclass
  //

  LPVOID                 m_MdiParm;           // Multi-document Window Parms
                                              // (Belongs in TopLevelMDIWindow)
#endif

  int                    m_ShowCommand;       // How to show this window
  LRESULT                m_WindowStatus;      // Current window status

  WindowRealizeAttribute m_Realize;           // Realize Condition
  bool                   m_Manage;            // Management Condition

 public:

  // Callback method pointers
  //

#if defined(_WIN32) || defined(_WIN64)

  // Control (Event) Loop pointer method (should be name/value pair)
  //

  WNDPROC m_ControlMethod;

  LRESULT (CWindowObject::*m_CallbackPtr)(WindowId        wId,
					  ObjectId        oId,
					  WPARAM          wParam,
					  LPARAM          lParam,
					  CCallbackClass* pData);
#endif

  LRESULT (CWindowObject::*m_ErrorMethodPtr)(CCallbackClass* pData);
  
  // Constructors and Destructors
  //

  CWindowObject();
  CWindowObject(OCTSTR pWindowName,OCTSTR pWindowClass,...);
  CWindowObject(OCTSTR pWindowName,OCTSTR pWindowClass,va_list vaList);
  ~CWindowObject();

  // Initialization calls thread through the class initialization method
  //

  LRESULT InitCWindow(OCTSTR pWindowName,OCTSTR pWindowClass,va_list vaList);

  // Callbacks are stored here to enable dynamic window assignment
  // during creation.
  //

  LRESULT AddCallback(CCallBack* pCallback);
  LRESULT DeleteCallback(CCallBack* pCallback);
  LRESULT CompleteCallback(WindowId pWindowId);

  CCallBack** GetCallList();
  int         GetCallListSize();

  // Geometry management indicator
  //

  LRESULT ManageGeometry();
  LRESULT UnmanageGeometry();
  BOOL    IsGeometryManaged();

  // Window Creation Methods
  //

  LRESULT RealizeWindow();
  LRESULT UnrealizeWindow();
  BOOL    IsWindowRealized();

  // Executes the current callback method pointer
  //

  LRESULT DoCallback(void**,HWND,UINT,WPARAM,LPARAM,CCallBack*);
  
  // Post creation methods for updating the callback list
  //

  WindowId GetWindowId();
  WindowId PutWindowId(WindowId pId);

#if defined(_COM_MODULE)
  LRESULT get_WindowId(WindowId* pWindowId);
  LRESULT put_WindowId(WindowId  wId);
  LRESULT get_HWND(HWND* pHwnd);
  LRESULT put_HWND(HWND  hWnd);
#endif

  // Event Accessor
  //

  DWORD   GetEventId(const wchar_t* pEventName);
  LRESULT get_EventId(OCTSTR pEventName,DWORD* pEventId);

  // Accessor for application level locking
  //

  LRESULT  AddAppLock(CApplicationLock* pLock);

  LRESULT  get_AppName(OCTSTR* pAppName);

  // Conversion operators
  //

  operator HWND();
  operator CCallBack**();

};

extern CWindowObject*      m_WindowObject;

#endif
