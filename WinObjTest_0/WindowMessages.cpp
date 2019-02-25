/* ************************************************************
 * Window Messages contains external definitions to the
 * various events a window must be able to support.
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#include "stdafx.h"
#include <WindowMessages.h>

const wchar_t* WinNullEvent           = L"WinNullEvt";
const wchar_t* WinActivateEvent       = L"WinActivateEvt";
const wchar_t* WinAppActivateEvent    = L"WinAppActivateEvt";
const wchar_t* WinCancelModeEvent     = L"WinCancelModeEvt";
const wchar_t* WinCloseEvent          = L"WinCloseEvt";
const wchar_t* WinCompacingEvent      = L"WinCompactingEvt";
const wchar_t* WinCreateEvent         = L"WinCreateEvt";
const wchar_t* WinDestroyEvent        = L"WinDestroyEvt";
const wchar_t* WinEnableEvent         = L"WinEnableEvt";
const wchar_t* WinEnterSizeMoveEvent  = L"WinEntSizeMoveEvt";
const wchar_t* WinExitSizeMoveEvent   = L"WinExitSizeMoveEvt";
const wchar_t* WinGetIconEvent        = L"WinGetIconEvt";
const wchar_t* WinGetMinMaxInfoEvent  = L"WinGetMinMaxEvt";
const wchar_t* WinGetTextEvent        = L"WinGetTextEvt";
const wchar_t* WinGetTextLengthEvent  = L"WinGetTextLengthEvt";
const wchar_t* WinInputLangChgEvent   = L"WinInputLangChgEvt";
const wchar_t* WinLangChangeRqstEvent = L"WinInputLangChgRqstEvt";
const wchar_t* WinMoveEvent           = L"WinMoveEvt";
const wchar_t* WinMovingEvent         = L"WinMovingEvt";
const wchar_t* WinNCActivateEvent     = L"WinNcActivateEvt";
const wchar_t* WinNCCalcSizeEvent     = L"WinNcCalcSizeEvt";
const wchar_t* WinNCCreateEvent       = L"WinNcCreateEvt";
const wchar_t* WinNCDestroyEvent      = L"WinNcDestroyEvt";
const wchar_t* WinParentNotifyEvent   = L"WinParentNotifyEvt";
const wchar_t* WinQueryDragIconEvent  = L"WinQueryDragIconEvt";
const wchar_t* WinQueryOpenEvent      = L"WinQueryOpenEvt";
const wchar_t* WinQuitEvent           = L"WinQuitEvt";
const wchar_t* WinSetIconEvent        = L"WinSetIconEvt";
const wchar_t* WinSetTextEvent        = L"WinSetTextEvt";
const wchar_t* WinSettingChangeEvent  = L"WinSettingChangeEvt";
const wchar_t* WinShowWindowEvent     = L"WinShowWindowEvt";
const wchar_t* WinSizeEvent           = L"WinSizeEvt";
const wchar_t* WinSizingEvent         = L"WinSizingEvt";
const wchar_t* WinStyleChangedEvent   = L"WinStyleChangedEvt";
const wchar_t* WinStyleChgingingEvent = L"WinStyleChangingEvt";
const wchar_t* WinUserChangedEvent    = L"WinUserChangedEvt";
const wchar_t* WinPosChangedEvent     = L"WinPosChangedEvt";
const wchar_t* WinPosChangingEvent    = L"WinPosChangingEvt";
const wchar_t* WinIniChangeEvent      = L"WinIniChangeEvt";

const NAME_MASK_PAIR WinEventList[] = {
  { WinNullEvent,           WM_GETMINMAXINFO },
  { WinActivateEvent,       WM_ACTIVATE },
  { WinAppActivateEvent,    WM_ACTIVATEAPP },
  { WinCancelModeEvent,     WM_CANCELMODE },
  { WinCloseEvent,          WM_CLOSE },
  { WinCompacingEvent,      WM_COMPACTING },
  { WinCreateEvent,         WM_CREATE },
  { WinDestroyEvent,        WM_DESTROY },
  { WinEnableEvent,         WM_ENABLE },
  { WinEnterSizeMoveEvent,  WM_ENTERSIZEMOVE },
  { WinExitSizeMoveEvent,   WM_EXITSIZEMOVE },
  { WinGetIconEvent,        WM_GETICON },
  { WinGetMinMaxInfoEvent,  WM_GETMINMAXINFO },
  { WinGetTextEvent,        WM_GETTEXT },
  { WinGetTextLengthEvent,  WM_GETTEXTLENGTH },
  { WinInputLangChgEvent,   WM_INPUTLANGCHANGE },
  { WinLangChangeRqstEvent, WM_INPUTLANGCHANGEREQUEST },
  { WinMoveEvent,           WM_MOVE },
  { WinMovingEvent,         WM_MOVING },
  { WinNCActivateEvent,     WM_NCACTIVATE },
  { WinNCCalcSizeEvent,     WM_NCCALCSIZE },
  { WinNCCreateEvent,       WM_NCCREATE },
  { WinNCDestroyEvent,      WM_NCDESTROY },
  { WinParentNotifyEvent,   WM_PARENTNOTIFY },
  { WinQueryDragIconEvent,  WM_QUERYDRAGICON },
  { WinQueryOpenEvent,      WM_QUERYOPEN },
  { WinQuitEvent,           WM_QUIT },
  { WinSetIconEvent,        WM_SETICON },
  { WinSetTextEvent,        WM_SETTEXT },
  { WinSettingChangeEvent,  WM_SETTINGCHANGE },
  { WinShowWindowEvent,     WM_SHOWWINDOW },
  { WinSizeEvent,           WM_SIZE },
  { WinSizingEvent,         WM_SIZING },
  { WinStyleChangedEvent,   WM_STYLECHANGED },
  { WinStyleChgingingEvent, WM_STYLECHANGING },
  { WinUserChangedEvent,    WM_USERCHANGED },
  { WinPosChangedEvent,     WM_WINDOWPOSCHANGED },
  { WinPosChangingEvent,    WM_WINDOWPOSCHANGING },
  { WinIniChangeEvent,      WM_WININICHANGE },
  { NULL,                   NULL}
};


