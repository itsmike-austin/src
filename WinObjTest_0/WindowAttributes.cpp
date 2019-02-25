/* ************************************************************
 * Window Attributes contains definitions to the
 * static data used to describe various attributes
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#include "stdafx.h"
#include <WindowAttributes.h>

// ------------------------------------------------------------
// Global Definitions
// ------------------------------------------------------------

const wchar_t* ApplType = L"Application";

// ------------------------------------------------------------
// General style attributes
// ------------------------------------------------------------

const wchar_t* EnableStyle  = L"Enable";
const wchar_t* DisableStyle = L"Disable";

const wchar_t* WindowYes    = L"Yes";
const wchar_t* WindowNo     = L"No";

// ------------------------------------------------------------
// Additional window attributes
// ------------------------------------------------------------

const wchar_t* WindowRealize    = L"Realize";
const wchar_t* WindowManage     = L"Manage";
const wchar_t* WindowObjectId   = L"ObjectId";
const wchar_t* WindowType       = L"WindowType";
const wchar_t* WindowCallback   = L"CallBack";
const wchar_t* WindowLock       = L"Lock";

// ------------------------------------------------------------
// Window Styles
// ------------------------------------------------------------

const wchar_t* TopLevelWindow    = L"TopLevel";
const wchar_t* MainWindow        = L"MainWindow";
const wchar_t* UserDefinedWindow = L"UserDefined";
const wchar_t* DialogWindow      = L"DialogWindow";
const wchar_t* WindowlessWindow  = L"Windowless";
const wchar_t* ControlWindow     = L"Control";
const wchar_t* UserDefControlWnd = L"UserControl";

// Basic object type map.
//

const OBJECT_TYPE BasicObjectList[] = {
  TopLevelWindow,
  MainWindow,
  UserDefinedWindow,
  DialogWindow,
  WindowlessWindow,
  ControlWindow,
  UserDefControlWnd,
  NULL
};

// ------------------------------------------------------------
// Microsoft style extended window styles (CreateWindowEx)
// ------------------------------------------------------------

const wchar_t* WindowDragAndDrop      = L"DragAndDrop";
const wchar_t* WindowTaskBar          = L"TaskBar";
const wchar_t* WindowSunkenEdge       = L"SunkenEdge";
const wchar_t* WindowContextHelp      = L"ContextHelp";
const wchar_t* WindowControlParent    = L"ControlParent";
const wchar_t* WindowDialogModalFrame = L"DialogModalFrame";
const wchar_t* WindowAlignLeft        = L"LeftAlign";
const wchar_t* WindowScrollbarLeft    = L"ScrollBarLeft";
const wchar_t* WindowLeftToRightText  = L"LeftToRight";
const wchar_t* WindowMdiChild         = L"MdiChild";
const wchar_t* WindowNoParentNotify   = L"NoParentNotify";
const wchar_t* WindowOverlapped       = L"Overlapped";
const wchar_t* WindowPaletteStyle     = L"PaletteStyle";
const wchar_t* WindowAlignRight       = L"AlignRight";
const wchar_t* WindowScrollbarRight   = L"ScrollBarRight";
const wchar_t* WindowRightToLeftText  = L"RightToLeft";
const wchar_t* WindowStaticEdge       = L"StaticEdge";
const wchar_t* WindowTool             = L"ToolWindow";
const wchar_t* WindowTopmost          = L"WindowTopmost";
const wchar_t* WindowTransparent      = L"Transparent";
const wchar_t* WindowEdge             = L"Edge";

// Microsoft Extended Style mappings
//

const STYLE_DATA ExtendedStyleList[] = {
  { WindowDragAndDrop,      WS_EX_ACCEPTFILES },
  { WindowTaskBar,          WS_EX_APPWINDOW },
  { WindowSunkenEdge,       WS_EX_CLIENTEDGE },
  { WindowContextHelp,      WS_EX_CONTEXTHELP },
  { WindowControlParent,    WS_EX_CONTROLPARENT },
  { WindowDialogModalFrame, WS_EX_DLGMODALFRAME },
  { WindowAlignLeft,        WS_EX_LEFT },
  { WindowScrollbarLeft,    WS_EX_LEFTSCROLLBAR },
  { WindowLeftToRightText,  WS_EX_LTRREADING },
  { WindowMdiChild,         WS_EX_MDICHILD },
  { WindowNoParentNotify,   WS_EX_NOPARENTNOTIFY },
  { WindowOverlapped,       WS_EX_OVERLAPPEDWINDOW },
  { WindowPaletteStyle,     WS_EX_PALETTEWINDOW },
  { WindowAlignRight,       WS_EX_RIGHT },
  { WindowScrollbarRight,   WS_EX_RIGHTSCROLLBAR },
  { WindowRightToLeftText,  WS_EX_RTLREADING },
  { WindowStaticEdge,       WS_EX_STATICEDGE },
  { WindowTool,             WS_EX_TOOLWINDOW },
  { WindowTopmost,          WS_EX_TOPMOST },
  { WindowTransparent,      WS_EX_TRANSPARENT },
  { WindowEdge,             WS_EX_WINDOWEDGE },
  { NULL,                   NULL }
};

// ------------------------------------------------------------
// Microsoft standard styles (CreateWindow/CreateWindowEx)
// ------------------------------------------------------------

const wchar_t* WindowBorder        = L"Border";
const wchar_t* WindowCaption       = L"Caption";
const wchar_t* WindowChild         = L"Child";
const wchar_t* WindowClipChildren  = L"ClipChildren";
const wchar_t* WindowClipSiblings  = L"ClipSiblings";
const wchar_t* WindowDisabled      = L"Disabled";
const wchar_t* WindowDialogFrame   = L"DialogFrame";
const wchar_t* WindowGroup         = L"Group";
const wchar_t* WindowHorizonScroll = L"HScroll";
const wchar_t* WindowIconic        = L"Iconic";
const wchar_t* WindowMaximize      = L"Maximize";
const wchar_t* WindowMaxBox        = L"MaxBox";
const wchar_t* WindowMinimize      = L"Miminize";
const wchar_t* WindowMinBox        = L"MinBox";
const wchar_t* WindowTiled         = L"Tiled";
const wchar_t* WindowOverlapStyle  = L"OverlapStyle";
const wchar_t* WindowPopup         = L"Popup";
const wchar_t* WindowPopupStyle    = L"PopupStyle";
const wchar_t* WindowSizebox       = L"SizeBox";
const wchar_t* WindowSysMenu       = L"SysMenu";
const wchar_t* WindowTabStop       = L"TabStop";
const wchar_t* WindowThickFrame    = L"ThickFrame";
const wchar_t* WindowVisible       = L"Visible";
const wchar_t* WindowVertScroll    = L"VertScroll";

// Microsoft standard style mappings
//

const STYLE_DATA StandardStyleList[] = {
  { WindowBorder,        WS_BORDER },
  { WindowCaption,       WS_CAPTION },
  { WindowChild,         WS_CHILD },
  { WindowClipChildren,  WS_CLIPCHILDREN },
  { WindowClipSiblings,  WS_CLIPSIBLINGS },
  { WindowDisabled,      WS_DISABLED },
  { WindowDialogFrame,   WS_DLGFRAME },
  { WindowGroup,         WS_GROUP },
  { WindowHorizonScroll, WS_HSCROLL },
  { WindowIconic,        WS_ICONIC },
  { WindowMaximize,      WS_MAXIMIZE },
  { WindowMaxBox,        WS_MAXIMIZEBOX },
  { WindowMinimize,      WS_MINIMIZE },
  { WindowMinBox,        WS_MINIMIZEBOX },
  { WindowOverlapStyle,  WS_OVERLAPPEDWINDOW },
  { WindowPopup,         WS_POPUP },
  { WindowPopupStyle,    WS_POPUPWINDOW },
  { WindowSizebox,       WS_SIZEBOX },
  { WindowSysMenu,       WS_SYSMENU },
  { WindowTabStop,       WS_TABSTOP },
  { WindowThickFrame,    WS_THICKFRAME },
  { WindowTiled,         WS_TILED },
  { WindowVisible,       WS_VISIBLE },
  { WindowVertScroll,    WS_VSCROLL },
  { NULL,                NULL }
};

// ------------------------------------------------------------
// Microsoft extended window definitions (RegisterClass/Ex)
// ------------------------------------------------------------

const wchar_t* WindowClassName     = L"ClassName";
const wchar_t* WindowAtom          = L"WindowAtom";
const wchar_t* WindowName          = L"WindowName";
const wchar_t* WindowX             = L"XPos";
const wchar_t* WindowY             = L"YPos";
const wchar_t* WindowWidth         = L"Width";
const wchar_t* WindowHeight        = L"Height";
const wchar_t* WindowParent        = L"Parent";
const wchar_t* WindowParentId      = L"ParentId";
const wchar_t* WindowMenu          = L"Menu";
const wchar_t* WindowInstance      = L"Instance";
const wchar_t* WindowStyle         = L"Style";
const wchar_t* WindowStyleEx       = L"StyleEx";

// Microsoft windows class style definitions
//

const wchar_t* WindowByteAlignClient = L"ByteAlignClient";
const wchar_t* WindowByteAlignWindow = L"ByteAlignWindow";
const wchar_t* WindowClassDC         = L"ClassDC";
const wchar_t* WindowDoubleClick     = L"DoubleClick";
const wchar_t* WindowGlobalClass     = L"GlobalClass";
const wchar_t* WindowHorizRedraw     = L"HRedraw";
const wchar_t* WindowNoClose         = L"NoClose";
const wchar_t* WindowOwnDC           = L"OwnDC";
const wchar_t* WindowParentDC        = L"ParentDC";
const wchar_t* WindowSaveBits        = L"SaveBits";
const wchar_t* WindowVertRedraw      = L"VRedraw";

// Microsoft windows class style mappings
//

const STYLE_DATA ClassStyleList[] = {
  { WindowByteAlignClient, CS_BYTEALIGNCLIENT },
  { WindowByteAlignWindow, CS_BYTEALIGNWINDOW },
  { WindowClassDC,         CS_CLASSDC },
  { WindowDoubleClick,     CS_DBLCLKS },
  { WindowGlobalClass,     CS_GLOBALCLASS },
  { WindowHorizRedraw,     CS_HREDRAW },
  { WindowNoClose,         CS_NOCLOSE },
  { WindowOwnDC,           CS_OWNDC },
  { WindowParentDC,        CS_PARENTDC },
  { WindowSaveBits,        CS_SAVEBITS },
  { WindowVertRedraw,      CS_VREDRAW },
  { NULL,                  NULL }
};

// ------------------------------------------------------------
// Microsoft windows class definitions
// ------------------------------------------------------------

const wchar_t* WindowClassStyle      = L"ClassStyle";
const wchar_t* WindowProcedure       = L"WndProc";
const wchar_t* WindowClassExtraBytes = L"ClassExtra";
const wchar_t* WindowExtraBytes      = L"ExtraBytes";
const wchar_t* WindowIcon            = L"Icon";
const wchar_t* WindowCursor          = L"Cursor";
const wchar_t* WindowBackground      = L"Background";
const wchar_t* WindowMenuName        = L"MenuName";
const wchar_t* WindowSmallIcon       = L"SmallIcon";

// ------------------------------------------------------------
// Microsoft Management Operations (ShowWindow)
// ------------------------------------------------------------

const wchar_t* WndOpForceMinimize   = L"ForceMinimize";
const wchar_t* WndOpHide            = L"Hide";
const wchar_t* WndOpMaximize        = L"Maximize";
const wchar_t* WndOpMinimize        = L"Minimize";
const wchar_t* WndOpRetore          = L"Restore";
const wchar_t* WndOpShow            = L"Show";
const wchar_t* WndOpShowDefault     = L"DefaultShow";
const wchar_t* WndOpShowMaximized   = L"ShowMaximize";
const wchar_t* WndOpShowMinimized   = L"ShowMinimize";
const wchar_t* WndOpShowMinNoActive = L"ShowMinNoActive";
const wchar_t* WndOpShowNA          = L"ShowNA";
const wchar_t* WndOpShowNoActive    = L"ShowNoActive";
const wchar_t* WndShowNormal        = L"ShowNormal";

const STYLE_DATA ShowWindowOpList[] = {
  { WndOpForceMinimize,   SW_FORCEMINIMIZE },
  { WndOpHide,            SW_HIDE },
  { WndOpMaximize,        SW_MAXIMIZE },
  { WndOpMinimize,        SW_MINIMIZE },
  { WndOpRetore,          SW_RESTORE },
  { WndOpShow,            SW_SHOW },
  { WndOpShowDefault,     SW_SHOWDEFAULT },
  { WndOpShowMaximized,   SW_SHOWMAXIMIZED },
  { WndOpShowMinimized,   SW_SHOWMINIMIZED },
  { WndOpShowMinNoActive, SW_SHOWMINNOACTIVE },
  { WndOpShowNA,          SW_SHOWNA },
  { WndOpShowNoActive,    SW_SHOWNOACTIVATE },
  { WndShowNormal,        SW_SHOWNORMAL },
  { NULL,                 NULL }
};
