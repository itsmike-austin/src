/* ************************************************************
 * ButtonAttributes
 *
 * The class definition for various types of buttons.
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#if defined(_WIN32)
#pragma once
#endif

#ifndef _WINDOW_BUTTON_H
#define _WINDOW_BUTTON_H

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include "StdAfx.h"
#include <ItsStdIncs.h>
#include <ItsStdDefs.h>

// ------------------------------------------------------------
// Global Definitions
// ------------------------------------------------------------

// Microsoft Basic Button Styles
//

// Container for groups of radio, check box and push buttons
//

extern const wchar_t* GroupBoxContainer;

// ------------------------------------------------------------
// Button Class Definitions
// ------------------------------------------------------------

// Class definition to use various push button classes
// eg. CWindowObject* pButton0 =
//        new CPushButton(L"Exit",
//                        PushButtonClass,DefPushButton,
//                        ...,
//                        NULL);
//

extern const wchar_t* PushButtonClass;

// PushButtonClass members
//
// Standard push button:            PushButton
// Push button with dark border:    DefPushButton
// Owner drawn push button:         OwnerDrawnButton
// Push button with bitmap:         BitmapButton
// Push button with icon:           IconButton
// Flat push button:                FlatButton
//

extern const wchar_t* PushButton;
extern const wchar_t* DefPushButton;
extern const wchar_t* OwnerDrawnButton;
extern const wchar_t* BitmapButton;
extern const wchar_t* IconButton;
extern const wchar_t* FlatButton;

extern const NAME_MASK_PAIR  PushButtonClasses[];

// ------------------------------------------------------------
// CheckBox Class Definitions
// ------------------------------------------------------------

// Class definition to use various push button classes
// eg. CWindowObject* pCheckBox0 =
//        new CCheckBox(L"Exit",
//                      CheckBoxClass,CheckBoxButton,
//                      ...,
//                      NULL);
//

extern const wchar_t* CheckBoxClass;

// CheckBoxClass members
//
// Empty check box w/right text:    CheckBoxButton
// Autocycle check box (on/off):    AutoCheckBoxButton
// Check,unchk or gray chkbox:      ThreeStateCheckBoxButton
// Autocycle through 3State chkbox: Auto3StateCheckBoxButton
//
// Bitmap, Icon and Box attributes are added to the
// basic objects as a convenience. Rf. attributes section
// following basic object definitions for additional
// combinations.
// 

extern const wchar_t* CheckBoxButton;
extern const wchar_t* BitmapCheckBox;
extern const wchar_t* IconCheckBox;
extern const wchar_t* BoxCheckBoxButton;
extern const wchar_t* BoxBitmapCheckBox;
extern const wchar_t* BoxIconCheckBox;
extern const wchar_t* AutoCheckBox;
extern const wchar_t* BitmapAutoCheckBox;
extern const wchar_t* IconAutoCheckBox;
extern const wchar_t* BoxAutoCheckBox;
extern const wchar_t* BoxBitmapAutoCheckBox;
extern const wchar_t* BoxIconAutoCheckBox;
extern const wchar_t* ThreeStateCheckBox;
extern const wchar_t* Bitmap3StateCheckBox;
extern const wchar_t* Icon3StateCheckBox;
extern const wchar_t* Box3StateCheckBox;
extern const wchar_t* Box3StateBitmapCheckBox;
extern const wchar_t* Box3StateIconCheckBox;
extern const wchar_t* Auto3StateCheckBox;
extern const wchar_t* BitmapAuto3StateCheckBox;
extern const wchar_t* IconAuto3StateCheckBox;
extern const wchar_t* BoxAuto3StateCheckBox;
extern const wchar_t* BoxAutoBitmap3StateCheckBox;
extern const wchar_t* BoxAutoIcon3StateCheckBox;

extern const NAME_MASK_PAIR CheckBoxClasses[];


// ------------------------------------------------------------
// RadioButton Class Definitions
// ------------------------------------------------------------

// Class definition to use various push button classes
// eg. CWindowObject* pRadioButton0 =
//        new CRadioButton(L"Exit",
//                         RadioButtonClass,RadioButton,
//                         ...,
//                         NULL);
//

extern const wchar_t* RadioButtonClass;

// Small circle with right text:    RadioButton
// Auto select/cancel in group box: AutoRadioButton
//
// Additional box, bitmap and icon attributes have
// been applied as a convenience. Other attributes
// may be selected from the other attributes.
//

extern const wchar_t* RadioButton;
extern const wchar_t* BitmapRadioButton;
extern const wchar_t* IconRadioButton;
extern const wchar_t* BoxRadioButton;
extern const wchar_t* BoxBitmapRadioButton;
extern const wchar_t* BoxIconRadioButton;
extern const wchar_t* AutoRadioButton;
extern const wchar_t* BitmapAutoRadioButton;
extern const wchar_t* IconAutoRadioButton;
extern const wchar_t* BoxAutoRadioButton;
extern const wchar_t* BoxBitmapAutoRadioButton;
extern const wchar_t* BoxIconAutoRadioButton;

extern const NAME_MASK_PAIR RadioButtonClasses[];

// ------------------------------------------------------------
// Button Image Justifications
// ------------------------------------------------------------

// Other attributes.
// These attributes may be used to modify the basic
// classes (PushButton...,RadioButton...,CheckBox...)
//

// Image Justification
// eg. CWindowObject* pButton0 =
//        new CPushButton(L"Exit",
//                        ButtonImageJustify,SetButtonImageLeft,
//                        ...,
//                        NULL);

extern const wchar_t* ButtonImageJustify;

// Images attributes may be text, bitmap or icon
//

extern const wchar_t* SetButtonImageMultiline;
extern const wchar_t* SetButtonImageLeft;
extern const wchar_t* SetButtonImageHorizontalCenter;
extern const wchar_t* SetButtonImageRight;
extern const wchar_t* SetButtonImageTop;
extern const wchar_t* SetButtonImageVerticalCenter;
extern const wchar_t* SetButtonImageBottom;

extern const NAME_MASK_PAIR ButtonJustifyList[];

// ------------------------------------------------------------
// Messages from buttons
// ------------------------------------------------------------

// Standard Button Callback
//
// XXX: ADJUST CALLBACK TO THIS PATTERN
//
// class ExitButton : public PushButton
// {
//  public:
//   LRESULT Quit(WindowId,ObjectId,WPARAM,LPARAM,CCallBack*);
// };
//
// CWindowObject* pButton0 =
//     new ExitButton(L"Exit",
//                    PushButtonClass,DefPushButton,
//                    ...);
// 
// pApp->VaAddCallback(pButton0,
//                     CallbackObjectId,pApp->GetObjectIdentifier(),
//                     CallbackEventId, pButton->GetEventId(ButtonClicked),
//                     CallbackData,    (void*)pData,
//                     CallbackType,    CompositeCallback,
//                     CallbackMethod,  &ExitButton::Quit,
//                     NULL);
//


// Identifier for the ButtonCallbacks
//

extern const wchar_t* ButtonCallback;

// Button Callbacks
//

extern const wchar_t* ButtonClicked;            // BN_CLICKED
extern const wchar_t* ButtonDoubleClick;        // BN_DBLCLICK
extern const wchar_t* ButtonDisable;            // BN_DISABLE
extern const wchar_t* ButtonPushed;             // BN_PUSHED
extern const wchar_t* ButtonLostFocus;          // BN_KILLFOCUS
extern const wchar_t* ButtonPaint;              // BN_PAINT
extern const wchar_t* ButtonGainFocus;          // BN_SETFOCUS
extern const wchar_t* ButtonUnpushed;           // BN_UNPUSHED
extern const wchar_t* ButtonColor;              // WM_CTLCOLORBTN

extern const NAME_MASK_PAIR ButtonRequestList[];

// ------------------------------------------------------------
// Button Drawing Attributes
// ------------------------------------------------------------

// Attributes may be set when a button color callback has been
// defined for the system. These elements are used to aid
// in constructing the color style
//
// For Windows, use ::GetSysColor or ::SetSysColor to get/set
// the default values from/for the system.
//

extern const wchar_t* ButtonColorType;

extern const wchar_t* ButtonFaceColor;          // COLOR_BTNFACE
extern const wchar_t* ButtonHighLight;          // COLOR_BTNHIGHLIGHT
extern const wchar_t* ButtonShadow;             // COLOR_BTNSHADOW
extern const wchar_t* ButtonTextColor;          // COLOR_BTNTEXT
extern const wchar_t* ButtonGrayText;           // COLOR_GRAYTEXT
extern const wchar_t* ButtonBackgroundColor;    // COLOR_WINDOW
extern const wchar_t* ButtonFrameColor;         // COLOR_WINDOWFRAME
extern const wchar_t* ButtonWindowText;         // COLOR_WINDOWTEXT

extern const NAME_MASK_PAIR ButtonColorAttributes[];

// ------------------------------------------------------------
// Messages to buttons (Actions)
//
// These actions have default values in the class loop.
// Buttons have composite methods. An additional search for
// a default (or false return when not found for composites)
// will create the default processing model passthrough.
// ------------------------------------------------------------

extern const wchar_t* ButtonOperation;

extern const wchar_t* ButtonClick;              // BM_CLICK
extern const wchar_t* ButtonKbdChange;          // WM_CHAR (kbd: check(+=), uncheck (-) (change radio/ckbox)
extern const wchar_t* ButtonPaint;              // WM_ENABLE
extern const wchar_t* ButtonEraseOwnerDrawn;    // WM_ERASEBKGND
extern const wchar_t* ButtonSetCheck;           // BM_SETCHECK
extern const wchar_t* ButtonGetCheck;           // BM_GETCHECK
extern const wchar_t* ButtonSetState;           // BM_SETSTATE
extern const wchar_t* ButtonGetState;           // BM_GETSTATE
extern const wchar_t* ButtonSetStyle;           // BM_SETSTYLE
extern const wchar_t* ButtonSetImage;           // BM_SETIMAGE
extern const wchar_t* ButtonGetImage;           // BM_GETIMAGE
extern const wchar_t* ButtonSetDefaultId;       // DM_SETDEFID
extern const wchar_t* ButtonGetDefaultId;       // DM_GETDEFID
extern const wchar_t* ButtonGetFont;            // WM_GETFONT
extern const wchar_t* ButtonKeyDown;            // WM_KEYDOWN (push button if user presses spacebar
extern const wchar_t* ButtonKeyUp;              // WM_KEYUP   (release mouse capture)
extern const wchar_t* ButtonKillFocus;          // WM_KILLFOCUS
extern const wchar_t* ButtonLeftDblClick;       // WM_LBUTTONDBLCLK
extern const wchar_t* ButtonLeftMouseDown;      // WM_LBUTTONDOWN
extern const wchar_t* ButtonLeftMouseUp;        // WM_LBUTTONUP
extern const wchar_t* ButtonMouseMove;          // WM_MOUSEMOVE
extern const wchar_t* ButtonOwnerDrawnToDef;    // WM_NCCREATE
extern const wchar_t* ButtonHitTest;            // WM_NCHITTEST (return HTTRANSPARENT if in group)
extern const wchar_t* ButtonPaint;              // WM_PAINT     (Draw button)
extern const wchar_t* ButtonSetFocus;           // WM_SETFOCUS  (Send BN_CLICKED to parent)
extern const wchar_t* ButtonSetFont;            // WM_SETFONT
extern const wchar_t* ButtonSetText;            // WM_SETTEXT
extern const wchar_t* ButtonSysKeyUp;           // WM_SYSKEYUP  (Release mouse capture)

// ------------------------------------------------------------
// ButtonGetDlgCode: Executes the following table (MS)
//
// Windows sends a WM_GETDLGCODE message to controls in a 
// dialog box or in a window where the IsDialogMessage function
// handles keyboard input. Generally, an application processes 
// the WM_GETDLGCODE message to prevent Windows from performing
// default processing in response to keyboard messages. The
// WM_KEYDOWN, WM_SYSCHAR, and WM_CHAR messages are 
// examples of keyboard messages. 
//
// The WM_GETDLGCODE message is sent to the window procedure
// associated with a control. By default, the system handles all
// keyboard input to the control; the system interprets certain
// types of keyboard input as dialog box navigation keys. To
// override this default behavior, the control can respond
// to the WM_GETDLGCODE message to indicate the types of input
// it wants to process itself.
//
// StyleName(BaseClass)  ButtonStyle          Returns
// ------------------------------------------------------------
// AutoCheckBox          BS_AUTOCHECKBOX      DLGC_WANTCHARS|DLGC_BUTTON
// AutoRadioButton       BS_AUTORADIOBUTTON   DLGC_RADIOBUTTON
// DefPushButton         BS_DEFPUSHBUTTON     DLGC_DEFPUSHBUTTON
// GroupBoxContainer     BS_GROUPBOX          DLGC_STATIC
// PushButton            BS_PUSHBUTTON        DLGC_UNDEFPUSHBUTTON
// RadioButton           BS_RADIOBUTTON       DLGC_RADIOBUTTON
// ------------------------------------------------------------

extern const wchar_t* ButtonGetDlgCode;         // WM_GETDLGCODE

// List of button callback actions (eg. ButtonClicked)
//

extern const NAME_MASK_PAIR ButtonOperationList[];

// Full list of callbacks (including default callbacks for overrides)
//

extern const wchar_t* ButtonActions;
extern const NAME_MASK_PAIR ButtonActionList[];

// Full list of attribute lists
//

extern const LIST_DATA ButtonAttributeLists[];

// Object attributes lists
//

extern const LIST_DATA PushButtonAttributes[];
extern const LIST_DATA CheckBoxAttributes[];
extern const LIST_DATA RadioButtonAttributes[];

// Text Attributes
//

extern const wchar_t* SetButtonText;

// Radio/CheckBox Attributes
//

extern const wchar_t* SetButtonRight;

// Style Attributes (for BM_SETSTYLE)
//

extern const wchar_t* SetButtonFlat;            // BS_FLAT
extern const wchar_t* SetButton3D;              // BS_PUSHBUTTON
extern const wchar_t* SetButtonDefault;         // BS_DEFPUSHBUTTON
extern const wchar_t* SetButtonOwnerDrawn;      // BS_OWNERDRAWN

extern const wchar_t* SetCheckBoxDefault;       // BS_CHECKBOX
extern const wchar_t* SetCheckBox3State;        // BS_3STATE
extern const wchar_t* SetCheckBoxAuto3State;    // BS_AUTO3STATE
extern const wchar_t* SetCheckBoxAuto;          // BS_AUTOCHECKBOX
extern const wchar_t* SetCheckBoxButtonRight;   // BS_RIGHTBUTTON
extern const wchar_t* SetCheckBoxButtonLeft;    // ~BS_RIGHTBUTTON or BS_LEFTTEXT ??

extern const wchar_t* SetRadioButtonDefault;    // BS_RADIOBUTTON
extern const wchar_t* SetRadioButtonAuto;       // BS_AUTORADIOBUTTON
extern const wchar_t* SetRadioButtonRight;      // BS_RIGHTBUTTON
extern const wchar_t* SetRadioButtonLeft;       // ~BS_RIGHTBUTTON or BS_LEFTTEXT ??

extern const wchar_t* SetButtonBitmap;          // BS_BITMAP
extern const wchar_t* SetButtonIcon;            // BS_ICON

#endif
