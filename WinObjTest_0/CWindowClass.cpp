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

#include "stdafx.h"
#include <CWindowClass.h>

// ------------------------------------------------------------
// CONSTRUCTORS
//
// Note: The constructors are simple aids for accessing the
//       public initialization method. This simplifies
//       sub/super classing.
// ------------------------------------------------------------

// Default (NULL) Constructor
//

CWindowClass::CWindowClass() :
  m_WndClass(0),
  m_ClassName(NULL),
  m_Inst(NULL) {}

// Variatic constructor
//

CWindowClass::CWindowClass(wchar_t*      pClassName,
			   WindowProcPtr pWndProc,
			   ...) :
  m_WndClass(0),
  m_ClassName(pClassName),
  m_Inst(NULL)
 {
  va_list aList;
  va_start(aList,pClassName);
  InitWindowClass(pClassName,pWndProc,aList);
  va_end(aList);
}

CWindowClass::~CWindowClass() {}

/* ************************************************************ *
 *                    MANAGEMENT METHODS
 *
 * Note: The initialization method is the primary element for
 *       constructing window classes
 * ************************************************************ */

// ------------------------------------------------------------
// Class Initializer
// ------------------------------------------------------------

LRESULT CWindowClass::InitWindowClass(wchar_t*      pClassName,
				      WindowProcPtr pWndProc,
				      va_list       aList)
{
  wchar_t*      pItem;
  wchar_t*      pValue;
  STYLE_DATA*   pStyle;
  bool          bDoMore = true;

  // Initialize the class variables
  //

  WindowProcPtr m_WndProc          = pWndProc;
  unsigned int  m_ClassStyle       = 0;
  int           m_ClassExtraBytes  = 0;
  int           m_WindowExtraBytes = 0;
  HICON         m_Icon             = NULL;
  HCURSOR       m_Cursor           = NULL;
  HBRUSH        m_Background       = NULL;
  wchar_t*      m_MenuName         = NULL;
  HICON         m_SmallIcon        = NULL;

  if ( NULL == pWndProc ) return E_POINTER;

  // Save the window class if required
  //

  m_ClassName = (m_ClassName ? m_ClassName : pClassName);

  // Extract an argument from the list
  //

  while ( bDoMore && NULL != (pItem=va_arg(aList,wchar_t*)) )
    {
      if ( 0 == wcscmp(pItem,WindowAtom) )
	{
	  m_ClassName = (wchar_t*)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowInstance) )
	{
	  m_Inst = (HINSTANCE)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowClassStyle) )
	{
	  WNDCLASSEX* pEx = (WNDCLASSEX*)va_arg(aList,UIPTR);
	  m_WndProc          = pEx->lpfnWndProc;
	  m_ClassStyle       = pEx->style;
	  m_ClassExtraBytes  = pEx->cbClsExtra;
	  m_WindowExtraBytes = pEx->cbWndExtra;
	  m_Icon             = pEx->hIcon;
	  m_Cursor           = pEx->hCursor;
	  m_Background       = pEx->hbrBackground;
	  m_MenuName         = (wchar_t*)pEx->lpszMenuName;
	  m_ClassName        = (wchar_t*)pEx->lpszClassName;
	  m_SmallIcon        = pEx->hIconSm;
	  m_ClassName        = (wchar_t*)pEx->lpszClassName;
	  if ( NULL != m_Inst ) bDoMore = false;
	}
      else if ( 0 == wcscmp(pItem,WindowProcedure) )
	{
	  m_WndProc = (WindowProcPtr)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowClassExtraBytes) )
	{
	  m_ClassExtraBytes = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowExtraBytes) )
	{
	  m_WindowExtraBytes = (int)va_arg(aList,UIVAL);
	}
      else if ( 0 == wcscmp(pItem,WindowIcon) )
	{
	  m_Icon = (HICON)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowCursor) )
	{
	  m_Cursor = (HCURSOR)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowBackground) )
	{
	  m_Background = (HBRUSH)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowMenuName) )
	{
	  m_MenuName = (wchar_t*)va_arg(aList,UIPTR);
	}
      else if ( 0 == wcscmp(pItem,WindowSmallIcon) )
	{
	  m_SmallIcon = (HICON)va_arg(aList,UIPTR);
	}
      else
	{
	  // Check the class style list if not in the
	  // extended style list.
	  //

	  pStyle = (STYLE_DATA*)ClassStyleList;

	  while( bDoMore && pStyle->StyleName )
	    {
	      if ( 0 == wcscmp(pItem,pStyle->StyleName) )
		{
		  pValue = (wchar_t*)va_arg(aList,UIPTR);

		  if ( 0 == wcscmp(pValue,EnableStyle) )
		    m_ClassStyle |= pStyle->StyleValue;
		  else
		    m_ClassStyle &= (((DWORD)-1) ^ pStyle->StyleValue); // Little windy!

		  bDoMore = false;
		}
	      ++pStyle;
	    }

	  // This was an unknown entry. Extract the value
	  // and go on.
	  //

	  if ( bDoMore ) (void)va_arg(aList,UIPTR);

	  bDoMore = true;
	}
    }

  // Allocate heap for the new registration structure
  //

  LPWNDCLASSEX pWc = new WNDCLASSEX;
  memset((void*)pWc,(char)NULL,sizeof*pWc);

  // Build a few default values
  //

  m_Icon       = (m_Icon       ? m_Icon       : LoadIcon(NULL,IDI_APPLICATION));
  m_Cursor     = (m_Cursor     ? m_Cursor     : LoadCursor(NULL,IDC_ARROW));
  m_Background = (m_Background ? m_Background : (HBRUSH)(COLOR_WINDOW+1));

  // Register the class
  //

  pWc->cbSize        = sizeof(WNDCLASSEX); // XXX: Check to see if adjustments rqd for extra bytes
  pWc->style         = m_ClassStyle;
  pWc->lpfnWndProc   = m_WndProc;
  pWc->cbClsExtra    = m_ClassStyle;
  pWc->cbWndExtra    = m_WindowExtraBytes;
  pWc->hInstance     = m_Inst;
  pWc->hIcon         = m_Icon;
  pWc->hCursor       = m_Cursor;
  pWc->hbrBackground = m_Background;
  pWc->lpszMenuName  = (LPCWSTR)m_MenuName;
  pWc->lpszClassName = (LPCWSTR)m_ClassName;
  pWc->hIconSm       = m_SmallIcon;

  m_WndClass = ::RegisterClassEx(pWc);

  delete pWc;

  m_ClassStatus = (0 != m_WndClass ? 0 : GetLastError());

  return m_ClassStatus;
}

/* ************************************************************ *
 *                    ACCESSORS
 *
 * XXX: TBD: Should be standardized as well (UIVAR/UIPTR)
 * ************************************************************ */

// ------------------------------------------------------------
// GetClassStatus
//
// Return the status of the operation
// ------------------------------------------------------------

LRESULT CWindowClass::GetClassStatus()
{
  return m_ClassStatus;
}

// ------------------------------------------------------------
// get_ClassStatus()
//
// COM Style status accessor
// ------------------------------------------------------------

HRESULT CWindowClass::get_ClassStatus(LRESULT* pResult)
{
  HRESULT hr = (pResult ? S_OK : E_POINTER);

  if ( pResult ) *pResult = m_ClassStatus;

  return hr;
}

// ------------------------------------------------------------
// GetWindowClass()
//
// Get the window class
// ------------------------------------------------------------

ATOM CWindowClass::GetWindowClass()
{
  return m_WndClass;
}

// ------------------------------------------------------------
// get_WindowClass()
//
// COM Style window class accessor
// ------------------------------------------------------------

HRESULT CWindowClass::get_WindowClass(ATOM* pClass)
{
  HRESULT hr = (pClass ? S_OK : E_POINTER);

  if ( pClass ) *pClass = GetWindowClass();

  return hr;
}

// ------------------------------------------------------------
// GetWindowClassName()
//
// Get the window class name
// ------------------------------------------------------------

const wchar_t* CWindowClass::GetWindowClassName()
{
  return m_ClassName;
}

// ------------------------------------------------------------
// get_GetWindowClassName()
//
// COM Style window name accessor
// NOTE: SHOULD BE BSTR (OCTSTR) to fix the marshaller
// ------------------------------------------------------------

HRESULT CWindowClass::get_WindowClassName(wchar_t** pName)
{
  HRESULT hr = (pName && m_ClassName ? S_OK : E_POINTER);

  if ( pName && m_ClassName ) *pName = m_ClassName;

  return hr;
}

// ------------------------------------------------------------
// GetClassAttributes()
//
// Get the WNDCLASSEX structure
// ------------------------------------------------------------

LRESULT CWindowClass::GetClassAttributes(LPWNDCLASSEX pWndClass)
{
  LRESULT lr = (pWndClass ? S_OK : E_POINTER);

  if ( pWndClass )
    {
      lr = (false != ::GetClassInfoEx(m_Inst,(LPCWSTR)m_ClassName,pWndClass) ? S_OK : E_INVALIDARG);
    }

  return lr;
}

/* ************************************************************ *
 *                    CONVERSION METHODS
 * ************************************************************ */

// ------------------------------------------------------------
// operator ATOM()
//
// Convert to an ATOM to simplify window creation
// ------------------------------------------------------------

CWindowClass::operator ATOM() { return m_WndClass; }

// ------------------------------------------------------------
// operator wchar_t*()
//
// Convert to a wide character string simplify window creation
// ------------------------------------------------------------

CWindowClass::operator wchar_t*() { return m_ClassName; }

// NOTE: OCTSTR(BSTR) conversion operators required to
//       complete this class
