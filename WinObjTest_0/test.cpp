#include <CWindowApplication.h>
#include <CTopLevelWindow.h>
#include <CExitButton.h>

int APIENTRY WinMain(HINSTANCE hInstance,
		     HINSTANCE hPrevInst,
		     LPSTR     pCmdLine,
		     INT       nCmdShow)
{
  CWindowApplication m_App(L"Test Application",L"TestObj",NULL);

  if ( _HEAPOK != _heapchk() )
    {
      MessageBox(NULL,L"Heap Imbalance: 0",L"Heap Imbalance: 0",MB_OK);
      exit( -1 );
    }

  CWindowObject* pTopLevel = new CTopLevelWindow(&m_App,
						 L"Test Object",
						 L"TestObj",
						 WindowBorder,      (UIPTR)EnableStyle,
						 WindowCaption,     (UIPTR)EnableStyle,
						 WindowMinBox,      (UIPTR)EnableStyle,
						 WindowThickFrame,  (UIPTR)EnableStyle,
						 WindowSysMenu,     (UIPTR)EnableStyle,
						 WindowVisible,     (UIPTR)EnableStyle,
						 WindowDragAndDrop, (UIPTR)EnableStyle,
						 WindowX,           (UIVAL)40,
						 WindowY,           (UIVAL)40,
						 WindowWidth,       (UIVAL)400,
						 WindowHeight,      (UIVAL)300,
						 WindowInstance,    (UIPTR)hInstance,
						 WindowManage,      (UIPTR)WindowYes,
						 WindowRealize,     (UIPTR)WindowYes,
						 (ulong)NULL);

  CWindowObject* pExitButton = new CExitButton(&m_App,
					       L"Exit",
					       PushButton,      (UIPTR)EnableStyle,
					       WindowParent,    (UIPTR)pTopLevel,
					       WindowX,         (UIVAL)0,
					       WindowY,         (UIVAL)0,
					       WindowHeight,    (UIVAL)40,
					       WindowWidth,     (UIVAL)80,
					       NULL);
  
  m_App.Go(pTopLevel);

  return 0;
}
