#include <CExitButton.h>

CExitButton::CExitButton() : CPushButton() {}

CExitButton::CExitButton(OCTSTR pWindowName,...) :
  CPushButton()
{
  va_list vaList;

  va_start(vaList,pWindowName);

  CPushButton::InitPushButton(pWindowName,vaList);

  va_end(vaList);

}

CExitButton::CExitButton(CWindowApplication* pApp,
			 OCTSTR              pWindowName,
			 ...) :
  CPushButton()
{
  // Should throw an error here for debug
  //

  if ( NULL == pApp || NULL == pWindowName ) return;

  // Build the argument list and initialize the base class
  //

  va_list vaList;

  va_start(vaList,pWindowName);

  CPushButton::InitPushButton(pWindowName,vaList);

  va_end(vaList);

  // Save the application pointer and save this
  // window object in Application's object list
  //

  m_App = pApp;

  pApp->AddWindow(this);

  // Add the default callback for this control
  //

  m_App->VaAddCallback(this,
		       CallbackEventId,  (UIVAL) GetEventId(ButtonClicked),
		       CallbackType,     (UIVAL) CompositeCallback,
		       CallbackWindowId, (UIVAL) GetWindowId(),
		       CallbackMethodPtr,(UIFPTR)(CallbackMethod)&CExitButton::Exit,
		       NULL);
}

LRESULT CExitButton::Exit(WindowId   wId,
			  ObjectId   oId,
			  WPARAM     wParam,
			  LPARAM     lParam,
			  CCallBack* pCb)
{
#if defined(_WIN32) || defined(_WIN64)
  ::PostQuitMessage(0);
#endif
  return S_OK;
}
