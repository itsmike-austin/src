/* ************************************************************
 * Window Messages contains external definitions to the
 * various events a window must be able to support.
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32)
#pragma once
#endif

#ifndef _WINDOWS_MESSAGES_H
#define _WINDOWS_MESSAGES_H

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <ItsStdIncs.h>
#include <ItsStdDefs.h>

// ------------------------------------------------------------
// Event mappings
// ------------------------------------------------------------

extern const wchar_t* WinNullEvent;
extern const wchar_t* WinActivateEvent;
extern const wchar_t* WinAppActivateEvent;
extern const wchar_t* WinCancelModeEvent;
extern const wchar_t* WinCloseEvent;
extern const wchar_t* WinCompacingEvent;
extern const wchar_t* WinCreateEvent;
extern const wchar_t* WinDestroyEvent;
extern const wchar_t* WinEnableEvent;
extern const wchar_t* WinEnterSizeMoveEvent;
extern const wchar_t* WinExitSizeMoveEvent;
extern const wchar_t* WinGetIconEvent;
extern const wchar_t* WinGetMinMaxInfoEvent;
extern const wchar_t* WinGetTextEvent;
extern const wchar_t* WinGetTextLengthEvent;
extern const wchar_t* WinInputLangChgEvent;
extern const wchar_t* WinLangChangeRqstEvent;
extern const wchar_t* WinMoveEvent;
extern const wchar_t* WinMovingEvent;
extern const wchar_t* WinNCActivateEvent;
extern const wchar_t* WinNCCalcSizeEvent;
extern const wchar_t* WinNCCreateEvent;
extern const wchar_t* WinNCDestroyEvent;
extern const wchar_t* WinParentNotifyEvent;
extern const wchar_t* WinQueryDragIconEvent;
extern const wchar_t* WinQueryOpenEvent;
extern const wchar_t* WinQuitEvent;
extern const wchar_t* WinSetIconEvent;
extern const wchar_t* WinSetTextEvent;
extern const wchar_t* WinSettingChangeEvent;
extern const wchar_t* WinShowWindowEvent;
extern const wchar_t* WinSizeEvent;
extern const wchar_t* WinSizingEvent;
extern const wchar_t* WinStyleChangedEvent;
extern const wchar_t* WinStyleChgingingEvent;
extern const wchar_t* WinUserChangedEvent;
extern const wchar_t* WinPosChangedEvent;
extern const wchar_t* WinPosChangingEvent;
extern const wchar_t* WinIniChangeEvent;

extern const NAME_MASK_PAIR WinEventList[];

#endif
