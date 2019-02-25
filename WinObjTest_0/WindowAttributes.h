/* ************************************************************
 * Window Attributes contains external definitions to the
 * static data used to describe various attributes
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32)
#pragma once
#endif

#ifndef _WINDOW_ATTRIBUTES_H
#define _WINDOW_ATTRIBUTES_H

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <ItsStdDefs.h>

// ------------------------------------------------------------
// Global Definitions
// ------------------------------------------------------------

extern const wchar_t* ApplType;

// ------------------------------------------------------------
// Basic structure for style encapsulation
// ------------------------------------------------------------

typedef struct {
  const wchar_t* StyleName;
  DWORD    StyleValue;
}STYLE_DATA;

// ------------------------------------------------------------
// Basic structure for window type encapsulation
// ------------------------------------------------------------

typedef const wchar_t* OBJECT_TYPE;

// ------------------------------------------------------------
// General style attributes
// ------------------------------------------------------------

extern const wchar_t* EnableStyle;
extern const wchar_t* DisableStyle;

extern const wchar_t* WindowYes;
extern const wchar_t* WindowNo;

// ------------------------------------------------------------
// Additional window method request
// ------------------------------------------------------------

extern const wchar_t* WindowRealize;
extern const wchar_t* WindowManage;
extern const wchar_t* WindowObjectId;
extern const wchar_t* WindowType;
extern const wchar_t* WindowCallback;
extern const wchar_t* WindowLock;

// ------------------------------------------------------------
// Window Styles
// ------------------------------------------------------------

extern const wchar_t* TopLevelWindow;
extern const wchar_t* MainWindow;
extern const wchar_t* UserDefinedWindow;
extern const wchar_t* DialogWindow;
extern const wchar_t* WindowlessWindow;
extern const wchar_t* ControlWindow;
extern const wchar_t* UserDefControlWnd;

// Basic object type map.
//

extern const OBJECT_TYPE BasicObjectList[];

// ------------------------------------------------------------
// Microsoft style extended window styles (CreateWindowEx)
// ------------------------------------------------------------

extern const wchar_t* WindowDragAndDrop;
extern const wchar_t* WindowTaskBar;
extern const wchar_t* WindowSunkenEdge;
extern const wchar_t* WindowContextHelp;
extern const wchar_t* WindowControlParent;
extern const wchar_t* WindowDialogModalFrame;
extern const wchar_t* WindowAlignLeft;
extern const wchar_t* WindowScrollbarLeft;
extern const wchar_t* WindowLeftToRightText;
extern const wchar_t* WindowMdiChild;
extern const wchar_t* WindowNoParentNotify;
extern const wchar_t* WindowOverlapped;
extern const wchar_t* WindowPaletteStyle;
extern const wchar_t* WindowAlignRight;
extern const wchar_t* WindowScrollbarRight;
extern const wchar_t* WindowRightToLeftText;
extern const wchar_t* WindowStaticEdge;
extern const wchar_t* WindowTool;
extern const wchar_t* WindowTopmost;
extern const wchar_t* WindowTransparent;
extern const wchar_t* WindowEdge;

// Microsoft Extended Style mappings
//

extern const STYLE_DATA ExtendedStyleList[];

// ------------------------------------------------------------
// Microsoft standard styles (CreateWindow/CreateWindowEx)
// ------------------------------------------------------------

extern const wchar_t* WindowBorder;
extern const wchar_t* WindowCaption;
extern const wchar_t* WindowChild;
extern const wchar_t* WindowClipChildren;
extern const wchar_t* WindowClipSiblings;
extern const wchar_t* WindowDisabled;
extern const wchar_t* WindowDialogFrame;
extern const wchar_t* WindowGroup;
extern const wchar_t* WindowHorizonScroll;
extern const wchar_t* WindowIconic;
extern const wchar_t* WindowMaximize;
extern const wchar_t* WindowMaxBox;
extern const wchar_t* WindowMinimize;
extern const wchar_t* WindowMinBox;
extern const wchar_t* WindowTiled;
extern const wchar_t* WindowOverlapStyle;
extern const wchar_t* WindowPopup;
extern const wchar_t* WindowPopupStyle;
extern const wchar_t* WindowSizebox;
extern const wchar_t* WindowSysMenu;
extern const wchar_t* WindowTabStop;
extern const wchar_t* WindowThickFrame;
extern const wchar_t* WindowVisible;
extern const wchar_t* WindowVertScroll;

// Microsoft standard style mappings
//

extern const STYLE_DATA StandardStyleList[];

// ------------------------------------------------------------
// Microsoft extended window definitions (RegisterClass/Ex)
// ------------------------------------------------------------

extern const wchar_t* WindowClassName;
extern const wchar_t* WindowAtom;
extern const wchar_t* WindowName;
extern const wchar_t* WindowX;
extern const wchar_t* WindowY;
extern const wchar_t* WindowWidth;
extern const wchar_t* WindowHeight;
extern const wchar_t* WindowParent;
extern const wchar_t* WindowParentId;
extern const wchar_t* WindowMenu;
extern const wchar_t* WindowInstance;
extern const wchar_t* WindowStyle;
extern const wchar_t* WindowStyleEx;

/* -----------------------------------------------------------------------------
 * Microsoft Windows Class Style Definitions (RegisterClass/Ex)
 * -----------------------------------------------------------------------------
 * WindowGlobalClass:       Application Global Class (~:Application Local Class)
 * WindowByteAlignClient:   Primarily used with Bitblt
 * WindowByteAlignWindow:   Primarily used with Bitblt 
 * WindowOwnDC:             Window has its own DC (Use judiciously)
 * WindowClassDC:           All windows of this class use same dc
 * WindowParentDC:          Use the parents DC (5 controls max/window for perf.)
 * WindowDoubleClick:       Enable WM_LBUTTONDBLCLK message
 * WindowHorizRedraw:       Full redraw on horizontal resize
 * WindowVertRedraw:        Full redraw on vertical resize
 * WindowNoClose:           No "Close" button in system menu
 * WindowSaveBits:          Save obscured bits (Use judiciously)
 * ----------------------------------------------------------------------------- */

extern const wchar_t* WindowByteAlignClient;
extern const wchar_t* WindowByteAlignWindow;
extern const wchar_t* WindowClassDC;
extern const wchar_t* WindowDoubleClick;
extern const wchar_t* WindowGlobalClass;
extern const wchar_t* WindowHorizRedraw;
extern const wchar_t* WindowNoClose;
extern const wchar_t* WindowOwnDC;
extern const wchar_t* WindowParentDC;
extern const wchar_t* WindowSaveBits;
extern const wchar_t* WindowVertRedraw;

extern const STYLE_DATA ClassStyleList[];

/* -----------------------------------------------------------------------------
 * Microsoft Windows Class Attributes (WNDCLASSEX)
 * -----------------------------------------------------------------------------
 * WindowClassStyle:        WNDCLASSEX*   (Full structure)
 * WindowProcedure:         WindowProcPtr (WNDPROC)
 * WindowClassExtraBytes:   UINT          (Extra bytes in window class)
 * WindowExtraBytes:        UINT          (Extra bytes in window)
 * WindowIcon:              HICON         (Default Icon for class)
 * WindowCursor:            HCURSOR       (Default Cursor for class)
 * WindowBackground:        HBRUSH        (Default background for class)
 * WindowMenuName:          HMENU         (Default menu for class)
 * WindowSmallIcon:         HICON         (Default small icon for class)
 * ----------------------------------------------------------------------------- */

extern const wchar_t* WindowClassStyle;
extern const wchar_t* WindowProcedure;
extern const wchar_t* WindowClassExtraBytes;
extern const wchar_t* WindowExtraBytes;
extern const wchar_t* WindowIcon;
extern const wchar_t* WindowCursor;
extern const wchar_t* WindowBackground;
extern const wchar_t* WindowMenuName;
extern const wchar_t* WindowSmallIcon;

// ------------------------------------------------------------
// Microsoft Management Operations (ShowWindow)
// ------------------------------------------------------------

extern const wchar_t* WndOpForceMinimize;
extern const wchar_t* WndOpHide;
extern const wchar_t* WndOpMaximize;
extern const wchar_t* WndOpMinimize;
extern const wchar_t* WndOpRetore;
extern const wchar_t* WndOpShow;
extern const wchar_t* WndOpShowDefault;
extern const wchar_t* WndOpShowMaximized;
extern const wchar_t* WndOpShowMinimized;
extern const wchar_t* WndOpShowMinNoActive;
extern const wchar_t* WndOpShowNA;
extern const wchar_t* WndOpShowNoActive;
extern const wchar_t* WndShowNormal;

extern const STYLE_DATA ShowWindowOpList[];

// ------------------------------------------------------------
// Definition for window callback procedure
// ------------------------------------------------------------

typedef LRESULT (CALLBACK *WindowProcPtr)(HWND hWnd,UINT uMsg,WPARAM wParm,LPARAM lParam);

#endif
