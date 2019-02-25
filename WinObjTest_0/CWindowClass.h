/* ************************************************************
 * Windows Class is used to construct a windows class.
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * Microsoft class support includes:
 *   System Global Classes,
 *   Application Global Class,
 *   Application Local Class
 *
 * UNIX SPECIFIC:      NOT REQUIRED
 *
 * Returns an empty value. Not required.
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32)
#pragma once
#endif

#ifndef _WINDOW_CLASS_CLASS_H
#define _WINDOW_CLASS_CLASS_H

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wchar.h>
#include <stdarg.h>

#include <ItsStdIncs.h>
#include <ItsStdDefs.h>
#include <WindowAttributes.h>

/* -----------------------------------------------------------------------------
 * Microsoft Windows Class Style Definitions
 * -----------------------------------------------------------------------------
 * WindowGlobalClass:      Application Global Class (~: Application Local Class)
 * WindowDoubleClick:      Enable WM_LBUTTONDBLCLK message
 * WindowHorizRedraw:      Full redraw on horizontal resize
 * WindowVertRedraw:       Full redraw on vertical resize
 * WindowNoClose:          No "Close" button in system menu
 * WindowSaveBits:         Save obscured bits (Use judiciously)
 *     Optionally, One Of:
 * WindowByteAlignClient:  Primarily used with Bitblt
 * WindowByteAlignWindow:  Primarily used with Bitblt
 *     Optionally, One Of:
 * WindowOwnDC:            Window has its own DC (Use judiciously)
 * WindowClassDC:          All windows of this class use same dc
 * WindowParentDC:         Use the parents DC (5 controls max/window for perf.)
 * -----------------------------------------------------------------------------
 * Note: WindowGlobalClass, rf Registry key
 *
 * HKEY_LOCAL_MACHINE\
 *     Software\Microsoft\Windows NT\CurrentVersion\Windows\AppInit_DLLs
 * 
 * ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
 * Microsoft Windows Class Attributes (WNDCLASSEX)
 * -----------------------------------------------------------------------------
 *      Either:
 * WindowClassStyle:        WNDCLASSEX*   (Full structure)
 *      Or:
 * WindowProcedure:         WindowProcPtr (WNDPROC)
 * WindowClassExtraBytes:   UINT          (Extra bytes in window class)
 * WindowExtraBytes:        UINT          (Extra bytes in window)
 * WindowIcon:              HICON         (Default Icon for class)
 * WindowCursor:            HCURSOR       (Default Cursor for class)
 * WindowBackground:        HBRUSH        (Default background for class)
 * WindowMenuName:          HMENU         (Default menu for class)
 * WindowSmallIcon:         HICON         (Default small icon for class)
 * ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
 * Extensions
 * -----------------------------------------------------------------------------
 * WindowAtom:              Substitution for pClassName ... rf: ::GlobalAddAtom
 * ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
 * EXAMPLE
 *
 * NOTE: All values of the name/value pairs are cast to either UIPTR or UIVAL
 *       Failure will result in a stack imbalance and program ACCVIO!
 * -----------------------------------------------------------------------------
 * CWindowClass* pClass = new CWindowClass(L"WinGlobalClass",
 *				           WindowGlobalClass, (UIPTR)EnableStyle,
 *				           WindowHorizRedraw, (UIPTR)EnableStyle,
 *                                         WindowVertRedraw,  (UIPTR)EnableStyle,
 *					   WindowNoClose,     (UIPTR)EnableStyle,
 *					   WindowNoClose,     (UIPTR)DisableStyle,
 *					   WindowParentDC,    (UIPTR)EnableStyle,
 *					   WindowProcedure,   (UIPTR)PtrToProc,
 *					   WindowIcon,        (UIPTR)LoadIcon(NULL,IDI_APPLICATION),
 *					   WindowCursor,      (UIPTR)LoadCursor(NULL,IDC_ARROW),
 *					   WindowBackground,  (UIVAL)COLOR_WINDOW+1,
 *					   NULL);
 * ----------------------------------------------------------------------------- */

class CWindowClass
{
private:
  ATOM      m_WndClass;    // The ATOM for this MS Window Class
  wchar_t*  m_ClassName;   // The class name for this event loop
  HINSTANCE m_Inst;        // The MS Window instance

  LRESULT   m_ClassStatus; // Event loop status

public:

  // Constructors and Destructors
  //

  CWindowClass();
  CWindowClass(wchar_t* pClassName,WindowProcPtr pProc,...);
  ~CWindowClass();

  // Operation Methods
  //

  LRESULT InitWindowClass(wchar_t* pClassName,WindowProcPtr pProc,va_list aList);

  // Accessors
  //

  LRESULT GetClassStatus();
  HRESULT get_ClassStatus(LRESULT* pResult);

  LRESULT GetClassAttributes(LPWNDCLASSEX pWndClass);

  ATOM     GetWindowClass();
  HRESULT  get_WindowClass(ATOM* pClass);

  const wchar_t* GetWindowClassName();
  HRESULT  get_WindowClassName(wchar_t** pName);

  // Conversion Methods
  //

  operator ATOM();
  operator wchar_t*();

};

#endif
