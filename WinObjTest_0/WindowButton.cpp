/* ************************************************************
 * CWindowButton is a collection of various button types.
 * ------------------------------------------------------------
 * (c) ItsInc. (1999,2001,2005,2006)
 * ************************************************************ */

#include <WindowButton.h>

// ------------------------------------------------------------
// Buttons and Button Containers
// ------------------------------------------------------------

const wchar_t* GroupBoxContainer              = L"GroupBox";

const wchar_t* PushButton                     = L"PushButton";
const wchar_t* DefPushButton                  = L"DefPushButton";
const wchar_t* OwnerDrawnButton               = L"OwnerDrawnButton";
const wchar_t* BitmapButton                   = L"BitmapButton";
const wchar_t* IconButton                     = L"IconButton";
const wchar_t* FlatButton                     = L"FlatButton";

const wchar_t* CheckBoxButton                 = L"CheckBoxButton";
const wchar_t* BitmapCheckBox                 = L"BitmapCheckBox";
const wchar_t* IconCheckBox                   = L"IconCheckBox";
const wchar_t* BoxCheckBoxButton              = L"BoxCheckBoxButton";
const wchar_t* BoxBitmapCheckBox              = L"BoxBitmapCheCkBox";
const wchar_t* BoxIconCheckBox                = L"BoxIconCheckBox";
const wchar_t* AutoCheckBox                   = L"AutoCheckBox";
const wchar_t* BitmapAutoCheckBox             = L"BitmapAutoCheckBox";
const wchar_t* IconAutoCheckBox               = L"IconAutoCheckBox";
const wchar_t* BoxAutoCheckBox                = L"BoxAutoCheckBox";
const wchar_t* BoxBitmapAutoCheckBox          = L"BoxBitmapAutoCheckBox";
const wchar_t* BoxIconAutoCheckBox            = L"BoxIconAutoCheckBox";
const wchar_t* ThreeStateCheckBox             = L"ThreeStateCheckBox";
const wchar_t* Bitmap3StateCheckBox           = L"Bitmap3StateCheckBox";
const wchar_t* Icon3StateCheckBox             = L"Icon3StateCheckBox";
const wchar_t* Box3StateCheckBox              = L"Box3StateCheckBox";
const wchar_t* Box3StateBitmapCheckBox        = L"Box3StateBitmapCheckBox";
const wchar_t* Box3StateIconCheckBox          = L"Box3StateIconCheckBox";
const wchar_t* Auto3StateCheckBox             = L"Auto3StateCheckBox";
const wchar_t* Auto3StateBitmapCheckBox       = L"Auto3StateBitmapCheckBox";
const wchar_t* Auto3StateIconCheckBox         = L"Auto3StateIconCheckBox";
const wchar_t* BoxAuto3StateCheckBox          = L"BoxAuto3StateCheckBox";
const wchar_t* BoxAuto3StateBitmapCheckBox    = L"BoxAuto3StateBitmapCheckBox";
const wchar_t* BoxAuto3StateIconCheckBox      = L"BoxAuto3StateIconCheckBox";

const wchar_t* RadioButton                    = L"RadioButton";
const wchar_t* BitmapRadioButton              = L"BitmapRadioButton";
const wchar_t* IconRadioButton                = L"IconRadioButton";
const wchar_t* BoxRadioButton                 = L"BoxRadioButton";
const wchar_t* BoxBitmapRadioButton           = L"BoxBitmapRadioButton";
const wchar_t* BoxIconRadioButton             = L"BoxIconRadioButton";
const wchar_t* AutoRadioButton                = L"AutoRadioButton";
const wchar_t* BitmapAutoRadioButton          = L"BitmapAutoRadioButton";
const wchar_t* IconAutoRadioButton            = L"IconAutoRadioButton";
const wchar_t* BoxAutoRadioButton             = L"BoxAutoRadioButton";
const wchar_t* BoxBitmapAutoRadioButton       = L"BoxBitmapAutoRadioButton";
const wchar_t* BoxIconAutoRadioButton         = L"BoxIconAutoRadioButton";

// ------------------------------------------------------------
// Buttons and Button Container Style Map
// ------------------------------------------------------------

const wchar_t* PushButtonClass  = L"PushButtonClass";

const NAME_MASK_PAIR PushButtonClasses[] = {
  { PushButton,                  BS_PUSHBUTTON                                },
  { OwnerDrawnButton,            BS_OWNERDRAW                                 },
  { BitmapButton,                BS_PUSHBUTTON      | BS_BITMAP               },
  { IconButton,                  BS_PUSHBUTTON      | BS_ICON                 },
  { FlatButton,                  BS_PUSHBUTTON      | BS_FLAT                 },
  { NULL,                        NULL                                         },
};

const wchar_t* CheckBoxClass    = L"CheckBoxClass";

const NAME_MASK_PAIR CheckBoxClasses[] = {
  { CheckBoxButton,              BS_CHECKBOX                                  },
  { BitmapCheckBox,              BS_CHECKBOX        | BS_BITMAP               },
  { IconCheckBox,                BS_CHECKBOX        | BS_ICON                 },
  { BoxCheckBoxButton,           BS_CHECKBOX        | BS_PUSHLIKE             },
  { BoxIconCheckBox,             BS_CHECKBOX        | BS_PUSHLIKE | BS_ICON   },
  { BoxBitmapCheckBox,           BS_CHECKBOX        | BS_PUSHLIKE | BS_BITMAP },
  { AutoCheckBox,                BS_AUTOCHECKBOX                              },
  { BitmapAutoCheckBox,          BS_AUTOCHECKBOX    | BS_BITMAP               },
  { IconAutoCheckBox,            BS_AUTOCHECKBOX    | BS_ICON                 },
  { BoxAutoCheckBox,             BS_AUTOCHECKBOX    | BS_PUSHLIKE             },
  { BoxBitmapAutoCheckBox,       BS_AUTOCHECKBOX    | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconAutoCheckBox,         BS_AUTOCHECKBOX    | BS_PUSHLIKE | BS_ICON   },
  { ThreeStateCheckBox,          BS_3STATE                                    },
  { Bitmap3StateCheckBox,        BS_3STATE          | BS_BITMAP               },
  { Icon3StateCheckBox,          BS_3STATE          | BS_ICON                 },
  { Box3StateCheckBox,           BS_3STATE          | BS_PUSHLIKE             },
  { Box3StateBitmapCheckBox,     BS_3STATE          | BS_PUSHLIKE | BS_BITMAP },
  { Box3StateIconCheckBox,       BS_3STATE          | BS_PUSHLIKE | BS_ICON   },
  { Auto3StateCheckBox,          BS_AUTO3STATE                                },
  { Auto3StateBitmapCheckBox,    BS_AUTO3STATE      | BS_BITMAP               },
  { Auto3StateIconCheckBox,      BS_AUTO3STATE      | BS_ICON                 },
  { BoxAuto3StateCheckBox,       BS_AUTO3STATE      | BS_PUSHLIKE             }, // Brkn
  { BoxAuto3StateBitmapCheckBox, BS_AUTO3STATE      | BS_PUSHLIKE | BS_BITMAP }, // conventio
  { BoxAuto3StateIconCheckBox,   BS_AUTO3STATE      | BS_PUSHLIKE | BS_ICON   },
  { NULL,                        NULL                                         },
};

const wchar_t* RadioButtonClass = L"RadioButtonClass";

const NAME_MASK_PAIR RadioButtonClasses[] = {
  { RadioButton,                 BS_RADIOBUTTON                               },
  { BitmapRadioButton,           BS_RADIOBUTTON     | BS_BITMAP               },
  { IconRadioButton,             BS_RADIOBUTTON     | BS_ICON                 },
  { BoxRadioButton,              BS_RADIOBUTTON     | BS_PUSHLIKE             },
  { BoxBitmapRadioButton,        BS_RADIOBUTTON     | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconRadioButton,          BS_RADIOBUTTON     | BS_PUSHLIKE | BS_ICON   },
  { AutoRadioButton,             BS_AUTORADIOBUTTON                           },
  { BitmapAutoRadioButton,       BS_AUTORADIOBUTTON | BS_BITMAP               },
  { IconAutoRadioButton,         BS_AUTORADIOBUTTON | BS_ICON                 },
  { BoxAutoRadioButton,          BS_AUTORADIOBUTTON | BS_PUSHLIKE             },
  { BoxBitmapAutoRadioButton,    BS_AUTORADIOBUTTON | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconAutoRadioButton,      BS_AUTORADIOBUTTON | BS_PUSHLIKE | BS_ICON   },
  { NULL,                        NULL                                         },
};

#if 0
const wchar_t* ButtonClass      = L"ButtonClass";

BUTTON_CLASS_LIST ButtonClassList[] = {
  { GroupBoxContainer,           BS_GROUPBOX                                  },
  { PushButton,                  BS_PUSHBUTTON                                },
  { OwnerDrawnButton,            BS_OWNERDRAW                                 },
  { BitmapButton,                BS_PUSHBUTTON      | BS_BITMAP               },
  { IconButton,                  BS_PUSHBUTTON      | BS_ICON                 },
  { FlatButton,                  BS_PUSHBUTTON      | BS_FLAT                 },
  { CheckBoxButton,              BS_CHECKBOX                                  },
  { BitmapCheckBox,              BS_CHECKBOX        | BS_BITMAP               },
  { IconCheckBox,                BS_CHECKBOX        | BS_ICON                 },
  { BoxCheckBoxButton,           BS_CHECKBOX        | BS_PUSHLIKE             },
  { BoxIconCheckBox,             BS_CHECKBOX        | BS_PUSHLIKE | BS_ICON   },
  { BoxBitmapCheckBox,           BS_CHECKBOX        | BS_PUSHLIKE | BS_BITMAP },
  { AutoCheckBox,                BS_AUTOCHECKBOX                              },
  { BitmapAutoCheckBox,          BS_AUTOCHECKBOX    | BS_BITMAP               },
  { IconAutoCheckBox,            BS_AUTOCHECKBOX    | BS_ICON                 },
  { BoxAutoCheckBox,             BS_AUTOCHECKBOX    | BS_PUSHLIKE             },
  { BoxBitmapAutoCheckBox,       BS_AUTOCHECKBOX    | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconAutoCheckBox,         BS_AUTOCHECKBOX    | BS_PUSHLIKE | BS_ICON   },
  { ThreeStateCheckBox,          BS_3STATE                                    },
  { Bitmap3StateCheckBox,        BS_3STATE          | BS_BITMAP               },
  { Icon3StateCheckBox,          BS_3STATE          | BS_ICON                 },
  { Box3StateCheckBox,           BS_3STATE          | BS_PUSHLIKE             },
  { Box3StateBitmapCheckBox,     BS_3STATE          | BS_PUSHLIKE | BS_BITMAP },
  { Box3StateIconCheckBox,       BS_3STATE          | BS_PUSHLIKE | BS_ICON   },
  { Auto3StateCheckBox,          BS_AUTO3STATE                                },
  { Auto3StateBitmapCheckBox,    BS_AUTO3STATE      | BS_BITMAP               },
  { Auto3StateIconCheckBox,      BS_AUTO3STATE      | BS_ICON                 },
  { BoxAuto3StateCheckBox,       BS_AUTO3STATE      | BS_PUSHLIKE             }, // Brkn
  { BoxAuto3StateBitmapCheckBox, BS_AUTO3STATE      | BS_PUSHLIKE | BS_BITMAP }, // conventio
  { BoxAuto3StateIconCheckBox,   BS_AUTO3STATE      | BS_PUSHLIKE | BS_ICON   },
  { RadioButton,                 BS_RADIOBUTTON                               },
  { BitmapRadioButton,           BS_RADIOBUTTON     | BS_BITMAP               },
  { IconRadioButton,             BS_RADIOBUTTON     | BS_ICON                 },
  { BoxRadioButton,              BS_RADIOBUTTON     | BS_PUSHLIKE             },
  { BoxBitmapRadioButton,        BS_RADIOBUTTON     | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconRadioButton,          BS_RADIOBUTTON     | BS_PUSHLIKE | BS_ICON   },
  { AutoRadioButton,             BS_AUTORADIOBUTTON                           },
  { BitmapAutoRadioButton,       BS_AUTORADIOBUTTON | BS_BITMAP               },
  { IconAutoRadioButton,         BS_AUTORADIOBUTTON | BS_ICON                 },
  { BoxAutoRadioButton,          BS_AUTORADIOBUTTON | BS_PUSHLIKE             },
  { BoxBitmapAutoRadioButton,    BS_AUTORADIOBUTTON | BS_PUSHLIKE | BS_BITMAP },
  { BoxIconAutoRadioButton,      BS_AUTORADIOBUTTON | BS_PUSHLIKE | BS_ICON   },
  { NULL,                        NULL },
};
#endif

// ------------------------------------------------------------
// Button and Button Container Sytle Modifiers
// ------------------------------------------------------------

// Image justification (text, bitmap, icon)
//

const wchar_t* SetButtonImageMultiline        = L"SetButtonImageMultiline";
const wchar_t* SetButtonImageLeft             = L"SetButtonImageLeft";
const wchar_t* SetButtonImageHorizontalCenter = L"SetButtonImageHorizontalCenter";
const wchar_t* SetButtonImageRight            = L"SetButtonImageRight";
const wchar_t* SetButtonImageTop              = L"SetButtonImageTop";
const wchar_t* SetButtonImageVerticalCenter   = L"SetButtonImageVerticalCenter";
const wchar_t* SetButtonImageBottom           = L"SetButtonImageBottom";
const wchar_t* SetButtonTextMultiline         = L"SetButtonTextMultiline";
const wchar_t* SetButtonRight                 = L"SetButtonRight";

// XXX:
// Additional Text Analogues
// XXX: Are the text justifications required?
//      What about standard justifications?
//      Leave them out for now.
// :XXX

const wchar_t* ButtonImageJustify = L"ButtonImageJustify";

const NAME_MASK_PAIR ButtonJustifyList[] = {
  { SetButtonImageMultiline,        BS_MULTILINE    },
  { SetButtonImageLeft,             BS_RIGHTBUTTON  },
  { SetButtonImageHorizontalCenter, BS_CENTER       },
  { SetButtonImageRight,            BS_RIGHT        },
  { SetButtonImageTop,              BS_TOP          },
  { SetButtonImageVerticalCenter,   BS_VCENTER      },
  { SetButtonImageBottom,           BS_BOTTOM       },
  { SetButtonRight,                 BS_RIGHTBUTTON  },
  { NULL,                           0               },
};

// XXX:
// These need to be classed as operations
// XXX:

const wchar_t* SetButtonText                  = L"SetButtonText";
const wchar_t* SetButtonNotify                = L"SetButtonNotify";

const wchar_t* SetButtonFlat                  = L"SetButtonFlat";
const wchar_t* SetButton3D                    = L"SetButton3D";
const wchar_t* SetButtonDefault               = L"SetButtonDefault";
const wchar_t* SetButtonOwnerDrawn            = L"SetButtonOwnerDrawn";

const wchar_t* SetCheckBoxDefault             = L"SetCheckBoxDefault";
const wchar_t* SetCheckBox3State              = L"SetCheckBox3State";
const wchar_t* SetCheckBoxAuto3State          = L"SetCheckBoxAuto3State";
const wchar_t* SetCheckBoxAuto                = L"SetCheckBoxAuto";
const wchar_t* SetCheckBoxButtonRight         = L"SetCheckBoxButtonRight";
const wchar_t* SetCheckBoxButtonLeft          = L"SetCheckBoxButtonLeft";

const wchar_t* SetRadioButtonDefault          = L"SetRadioButtonDefault";
const wchar_t* SetRadioButtonAuto             = L"SetRadioButtonAuto";
const wchar_t* SetRadioButtonRight            = L"SetRadioButtonRight";
const wchar_t* SetRadioButtonLeft             = L"SetRadioButtonLeft";

const wchar_t* SetButtonBitmap                = L"SetButtonBitmap";
const wchar_t* SetButtonIcon                  = L"SetButtonIcon";

// ------------------------------------------------------------
// Button and Button Container Operations
//
// These are generally not used directly, but through member
// attributes. They are included for completeness.
// ------------------------------------------------------------

const wchar_t* ButtonClicked                  = L"ButtonClicked";
const wchar_t* ButtonDoubleClick              = L"ButtonDoubleClick";
const wchar_t* ButtonDisable                  = L"ButtonDisable";
const wchar_t* ButtonPushed                   = L"ButtonPushed";
const wchar_t* ButtonLostFocus                = L"ButtonLostFocus";
#if 0
const wchar_t* ButtonPaint                    = L"ButtonPaint";
#endif
const wchar_t* ButtonGainFocus                = L"ButtonGainFocus";
const wchar_t* ButtonUnpushed                 = L"ButtonUnpushed";

const wchar_t* ButtonColor                    = L"ButtonColor";

const wchar_t* ButtonCallback = L"Callback";

const NAME_MASK_PAIR ButtonRequestList[] = {
  { ButtonClicked,     BN_CLICKED     },
  { ButtonDoubleClick, BN_DBLCLK      },
  { ButtonDisable,     BN_DISABLE     },
  { ButtonPushed,      BN_PUSHED      },
  { ButtonLostFocus,   BN_KILLFOCUS   },
  { ButtonPaint,       BN_PAINT       },
  { ButtonGainFocus,   BN_SETFOCUS    },
  { ButtonUnpushed,    BN_UNPUSHED    },
  { ButtonColor,       WM_CTLCOLORBTN },
  { NULL, 0 },
};

const wchar_t* ButtonClick                    = L"ButtonClick";
const wchar_t* ButtonKbdChange                = L"ButtonKbdChange";
const wchar_t* ButtonPaint                    = L"ButtonPaint";
const wchar_t* ButtonEraseOwnerDrawn          = L"ButtonEraseOwnerDrawn";
const wchar_t* ButtonSetCheck                 = L"ButtonSetCheck";
const wchar_t* ButtonGetCheck                 = L"ButtonGetCheck";
const wchar_t* ButtonSetState                 = L"ButtonSetState";
const wchar_t* ButtonGetState                 = L"ButtonGetState";
const wchar_t* ButtonSetStyle                 = L"ButtonSetStyle";

const wchar_t* ButtonSetImage                 = L"ButtonSetImage";
const wchar_t* ButtonGetImage                 = L"ButtonGetImage";
const wchar_t* ButtonSetDefaultId             = L"ButtonSetDefaultId";
const wchar_t* ButtonGetDefaultId             = L"ButtonGetDefaultId";

const wchar_t* ButtonGetDlgCode               = L"ButtonGetDlgCode";

const wchar_t* ButtonGetFont                  = L"ButtonGetFont";
const wchar_t* ButtonKeyDown                  = L"ButtonKeyDown";

const wchar_t* ButtonKeyUp                    = L"ButtonKeyUp";
const wchar_t* ButtonKillFocus                = L"ButtonKillFocus";
const wchar_t* ButtonLeftDblClick             = L"ButtonLeftDblClick";
const wchar_t* ButtonLeftMouseDown            = L"ButtonLeftMouseDown";
const wchar_t* ButtonLeftMouseUp              = L"ButtonLeftMouseUp";
const wchar_t* ButtonMouseMove                = L"ButtonMouseMove";
const wchar_t* ButtonOwnerDrawnToDef          = L"ButtonOwnerDrawnToDef";
const wchar_t* ButtonHitTest                  = L"ButtonHitTest";

#if 0
const wchar_t* ButtonPaint                    = L"ButtonPaint";
#endif
const wchar_t* ButtonSetFocus                 = L"ButtonSetFocus";
const wchar_t* ButtonSetFont                  = L"ButtonSetFont";
const wchar_t* ButtonSetText                  = L"ButtonSetText";
const wchar_t* ButtonSysKeyUp                 = L"ButtonSysKeyUp";

const wchar_t* ButtonFaceColor                = L"ButtonFaceColor";
const wchar_t* ButtonHighLight                = L"ButtonHighLight";
const wchar_t* ButtonShadow                   = L"ButtonShadow";
const wchar_t* ButtonTextColor                = L"ButtonTextColor";
const wchar_t* ButtonGrayText                 = L"ButtonGrayText";
const wchar_t* ButtonBackgroundColor          = L"ButtonBackgroundColor";
const wchar_t* ButtonFrameColor               = L"ButtonFrameColor";
const wchar_t* ButtonWindowText               = L"ButtonWindowText";

const wchar_t* ButtonOperation = L"Operation";

const NAME_MASK_PAIR ButtonOperationList[] = {
  { ButtonClick,           BM_CLICK         },
  { ButtonKbdChange,       WM_CHAR          },
  { ButtonPaint,           WM_ENABLE        },
  { ButtonEraseOwnerDrawn, WM_ERASEBKGND    },
  { ButtonSetCheck,        BM_SETCHECK      },
  { ButtonGetCheck,        BM_GETCHECK      },
  { ButtonSetState,        BM_SETSTATE      },
  { ButtonGetState,        BM_GETSTATE      },
  { ButtonSetStyle,        BM_SETSTYLE      },
  { ButtonSetImage,        BM_SETIMAGE      },
  { ButtonGetImage,        BM_GETIMAGE      },
  { ButtonSetDefaultId,    DM_SETDEFID      },
  { ButtonGetDefaultId,    DM_GETDEFID      },
  { ButtonGetDlgCode,      WM_GETDLGCODE    },
  { ButtonGetFont,         WM_GETFONT       },
  { ButtonKeyDown,         WM_KEYDOWN       },
  { ButtonKeyUp,           WM_KEYUP         },
  { ButtonKillFocus,       WM_KILLFOCUS     },
  { ButtonLeftDblClick,    WM_LBUTTONDBLCLK },
  { ButtonLeftMouseDown,   WM_LBUTTONDOWN   },
  { ButtonLeftMouseUp,     WM_LBUTTONUP     },
  { ButtonMouseMove,       WM_MOUSEMOVE     },
  { ButtonOwnerDrawnToDef, WM_NCCREATE      },
  { ButtonHitTest,         WM_NCHITTEST     },
  { ButtonPaint,           WM_PAINT         },
  { ButtonSetFocus,        WM_SETFOCUS      },
  { ButtonSetFont,         WM_SETFONT       },
  { ButtonSetText,         WM_SETTEXT       },
  { ButtonSysKeyUp,        WM_SYSKEYUP      },
  { NULL,                  0                },
};

const wchar_t* ButtonActions = L"ButtonActions";

const NAME_MASK_PAIR ButtonActionList[] = {
  { ButtonClicked,         BN_CLICKED       },
  { ButtonDoubleClick,     BN_DBLCLK        },
  { ButtonDisable,         BN_DISABLE       },
  { ButtonPushed,          BN_PUSHED        },
  { ButtonLostFocus,       BN_KILLFOCUS     },
  { ButtonPaint,           BN_PAINT         },
  { ButtonGainFocus,       BN_SETFOCUS      },
  { ButtonUnpushed,        BN_UNPUSHED      },
  { ButtonColor,           WM_CTLCOLORBTN   },
  { ButtonClick,           BM_CLICK         },
  { ButtonKbdChange,       WM_CHAR          },
  { ButtonPaint,           WM_ENABLE        },
  { ButtonEraseOwnerDrawn, WM_ERASEBKGND    },
  { ButtonSetCheck,        BM_SETCHECK      },
  { ButtonGetCheck,        BM_GETCHECK      },
  { ButtonSetState,        BM_SETSTATE      },
  { ButtonGetState,        BM_GETSTATE      },
  { ButtonSetStyle,        BM_SETSTYLE      },
  { ButtonSetImage,        BM_SETIMAGE      },
  { ButtonGetImage,        BM_GETIMAGE      },
  { ButtonSetDefaultId,    DM_SETDEFID      },
  { ButtonGetDefaultId,    DM_GETDEFID      },
  { ButtonGetDlgCode,      WM_GETDLGCODE    },
  { ButtonGetFont,         WM_GETFONT       },
  { ButtonKeyDown,         WM_KEYDOWN       },
  { ButtonKeyUp,           WM_KEYUP         },
  { ButtonKillFocus,       WM_KILLFOCUS     },
  { ButtonLeftDblClick,    WM_LBUTTONDBLCLK },
  { ButtonLeftMouseDown,   WM_LBUTTONDOWN   },
  { ButtonLeftMouseUp,     WM_LBUTTONUP     },
  { ButtonMouseMove,       WM_MOUSEMOVE     },
  { ButtonOwnerDrawnToDef, WM_NCCREATE      },
  { ButtonHitTest,         WM_NCHITTEST     },
  { ButtonPaint,           WM_PAINT         },
  { ButtonSetFocus,        WM_SETFOCUS      },
  { ButtonSetFont,         WM_SETFONT       },
  { ButtonSetText,         WM_SETTEXT       },
  { ButtonSysKeyUp,        WM_SYSKEYUP      },
  { NULL,                  0                },
};
  

// ------------------------------------------------------------
// Button and Button Container Color Attributes
// ------------------------------------------------------------

const wchar_t* ButtonColorType = L"ButtonColorType";

const NAME_MASK_PAIR ButtonColorAttributes[] = {
  { ButtonFaceColor,       COLOR_BTNFACE      },
  { ButtonHighLight,       COLOR_BTNHIGHLIGHT },
  { ButtonShadow,          COLOR_BTNSHADOW    },
  { ButtonTextColor,       COLOR_BTNTEXT      },
  { ButtonGrayText,        COLOR_GRAYTEXT     },
  { ButtonBackgroundColor, COLOR_WINDOW       },
  { ButtonFrameColor,      COLOR_WINDOWFRAME  },
  { ButtonWindowText,      COLOR_WINDOWTEXT   },
  { NULL,                  0                  },
};

const LIST_DATA ButtonAttributeLists[] = {
  { PushButtonClass,    PushButtonClasses   },
  { CheckBoxClass,      CheckBoxClasses     },
  { RadioButtonClass,   RadioButtonClasses  },
  { ButtonImageJustify, ButtonJustifyList   },
  { ButtonCallback,     ButtonRequestList   },
  { ButtonOperation,    ButtonOperationList },
  { NULL,               NULL                }
};

const LIST_DATA PushButtonAttributes[] = {
  { PushButtonClass,    PushButtonClasses   },
  { ButtonImageJustify, ButtonJustifyList   },
  { ButtonCallback,     ButtonRequestList   },
  { ButtonOperation,    ButtonOperationList },
  { NULL,               NULL                },
};

const LIST_DATA CheckBoxAttributes[] = {
  { CheckBoxClass,      CheckBoxClasses     },
  { ButtonImageJustify, ButtonJustifyList   },
  { ButtonCallback,     ButtonRequestList   },
  { ButtonOperation,    ButtonOperationList },
  { NULL,               NULL                },
};

const LIST_DATA RadioButtonAttributes[] = {
  { RadioButtonClass,   RadioButtonClasses  },
  { ButtonImageJustify, ButtonJustifyList   },
  { ButtonCallback,     ButtonRequestList   },
  { ButtonOperation,    ButtonOperationList },
  { NULL,               NULL                },
};
