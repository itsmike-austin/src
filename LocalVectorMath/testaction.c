#include <windows.h>
#include <msi.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
}UnixRGB;

#define InterfaceMethod __declspec(dllexport)

static HINSTANCE g_hInst;
static ATOM      g_Class;
static HWND      g_Window;
static UINT      g_Timer;
static HANDLE    g_Thread;
static BOOL      g_Active = TRUE;
static BOOL      fullscreen = TRUE;

static HDC       hDC=NULL;    // Private GDI Device Context
static HGLRC     hRC=NULL;    // Permanent Rendering Context

GLfloat xrot = 0.0f;
GLfloat yrot = 0.0f;
GLfloat zrot = 0.0f;
GLuint  texture[1];           // Texture storage area

extern AUX_RGBImageRec* GetImageRec();

// Stuff data into this area
//

int LoadGLTextures()
{
  int iStatus = FALSE;

  AUX_RGBImageRec* TextureImage[1];

  memset((void*)TextureImage,0,sizeof(void*));

  // Load the bitmap and check for errors
  //

  if ( TextureImage[0]=GetImageRec() )
    {
      iStatus = TRUE;

      glGenTextures(1,&texture[0]);     // Create a texture

      glBindTexture(GL_TEXTURE_2D,texture[0]);
      glTexImage2D(GL_TEXTURE_2D,0,3,TextureImage[0]->sizeX,TextureImage[0]->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,TextureImage[0]->data);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

  if ( TextureImage[0] ) free(TextureImage[0]);

  return iStatus;
}

GLvoid ResizeGlScene(GLsizei width,GLsizei height)
{
  if ( 0 == height ) height = 1;

  glViewport(0,0,width,height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Calculate The Aspect Ratio Of The Window
  //

  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int InitGL(GLvoid)
{
#if 0
  int iRc = LoadGLTextures();
#else
  int iRc = TRUE;
#endif

  // Make sure that the textures loaded
  //

  if ( FALSE != iRc )
    {
#if 0
      glEnable(GL_TEXTURE_2D);           // Activate texture mode
#endif
      glShadeModel(GL_SMOOTH);           // Smooth shading
      glClearColor(0.0f,0.0f,0.0f,0.5f); // Set the clear color
      glClearDepth(1.0);
      glDepthFunc(GL_LEQUAL);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // Nice perspective calcs
    }

  return iRc;
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
  glLoadIdentity();									// Reset The View
  glTranslatef(0.0f,0.0f,-5.0f);

  glRotatef(xrot,1.0f,0.0f,0.0f);
  glRotatef(yrot,0.0f,1.0f,0.0f);
  glRotatef(zrot,0.0f,0.0f,1.0f);

#if 0
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glBegin(GL_QUADS);
  // Front Face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // Back Face
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // Top Face
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // Bottom Face
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // Right face
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // Left Face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glEnd();
#else
  glBegin(GL_QUADS);
  // Front Face
  glColor4f(1.0f,0.0f,0.0f,1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glColor4f(1.0f,0.0f,0.0f,1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glColor4f(1.0f,0.0f,0.0f,1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glColor4f(1.0f,0.0f,0.0f,1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // Back Face
  glColor4f(1.0f,1.0f,0.0f,1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glColor4f(1.0f,1.0f,0.0f,1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glColor4f(1.0f,1.0f,0.0f,1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glColor4f(1.0f,1.0f,0.0f,1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // Top Face
  glColor4f(1.0f,0.0f,1.0f,1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glColor4f(1.0f,0.0f,1.0f,1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glColor4f(1.0f,0.0f,1.0f,1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glColor4f(1.0f,0.0f,1.0f,1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // Bottom Face
  glColor4f(0.0f,1.0f,0.0f,1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glColor4f(0.0f,1.0f,0.0f,1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glColor4f(0.0f,1.0f,0.0f,1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glColor4f(0.0f,1.0f,0.0f,1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // Right face
  glColor4f(0.0f,1.0f,1.0f,1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glColor4f(0.0f,1.0f,1.0f,1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glColor4f(0.0f,1.0f,1.0f,1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glColor4f(0.0f,1.0f,1.0f,1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // Left Face
  glColor4f(1.0f,1.0f,1.0f,1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glColor4f(1.0f,1.0f,1.0f,1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glColor4f(1.0f,1.0f,1.0f,1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glColor4f(1.0f,1.0f,1.0f,1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glEnd();
#endif

  xrot+=0.3f;
  yrot+=0.2f;
  zrot+=0.4f;
  return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)			// Properly Kill The Window
{
  if (hRC)					// Do We Have A Rendering Context?
    {
      if (!wglMakeCurrent(NULL,NULL))		// Are We Able To Release The DC And RC Contexts?
	{
	  MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	}

      if (!wglDeleteContext(hRC))		// Are We Able To Delete The RC?
	{
	  MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	}
      hRC=NULL;					// Set RC To NULL
    }

  if (hDC && !ReleaseDC(g_Window,hDC))        hDC=NULL;
  if (g_Window && !DestroyWindow(g_Window))   g_Window=NULL;
  if (!UnregisterClass("GoofyClass",g_hInst)) g_hInst=NULL;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  switch (uMsg)
    {
    case WM_ACTIVATE:
      {
	if (!HIWORD(wParam))
	  {
	    g_Active = TRUE;			// Program Is Active
	  }
	else
	  {
	    g_Active = FALSE;			// Program Is No Longer Active
	  }
	return 0;
      }

    case WM_TIMER:
      PostQuitMessage(0);
      return 0;

    case WM_SYSCOMMAND:				// Intercept System Commands
      {
	switch (wParam)				// Check System Calls
	  {
	  case SC_SCREENSAVE:			// Screensaver Trying To Start?
	  case SC_MONITORPOWER:			// Monitor Trying To Enter Powersave?
	    return 0;				// Prevent From Happening
	  }
	break;					// Exit
      }

    case WM_CLOSE:				// Did We Receive A Close Message?
      {
	PostQuitMessage(0);			// Send A Quit Message
	return 0;
      }

    case WM_SIZE:				// Resize The OpenGL Window
      {
	ResizeGlScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
	return 0;
      }
    }

  // Pass All Unhandled Messages To DefWindowProc

  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

#if 0
BOOL CreateGLWindow(char* title, int width, int height, const int bits)
{
  GLuint PixelFormat;	// Holds The Results After Searching For A Match

  DWORD  dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD  dwStyle   = WS_OVERLAPPEDWINDOW;
  RECT   WindowRect = { (long)0,(long)0,(long)width,(long)height };
  
  WNDCLASSEX wex =
    { sizeof(WNDCLASSEX),CS_HREDRAW|CS_VREDRAW|CS_OWNDC,(WNDPROC)WndProc,0,0,g_hInst,
      (HICON)LoadIcon(NULL,IDI_WINLOGO),LoadCursor(NULL,IDC_ARROW),(HBRUSH)COLOR_BACKGROUND,
      NULL,"GoofyClass",(HICON)NULL
    };

  static PIXELFORMATDESCRIPTOR pfd =
    {
      sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
      1,				// Version Number
      PFD_DRAW_TO_WINDOW |		// Format Must Support Window
      PFD_SUPPORT_OPENGL |		// Format Must Support OpenGL
      PFD_DOUBLEBUFFER,			// Must Support Double Buffering
      PFD_TYPE_RGBA,			// Request An RGBA Format
      16,			 // Select Our Color Depth
      0, 0, 0, 0, 0, 0,			// Color Bits Ignored
      0,				// No Alpha Buffer
      0,				// Shift Bit Ignored
      0,				// No Accumulation Buffer
      0, 0, 0, 0,			// Accumulation Bits Ignored
      16,				// 16Bit Z-Buffer (Depth Buffer)
      0,				// No Stencil Buffer
      0,				// No Auxiliary Buffer
      PFD_MAIN_PLANE,			// Main Drawing Layer
      0,				// Reserved
      0, 0, 0				// Layer Masks Ignored
    };

  if ( !RegisterClassEx(&wex) ) return 0;

  AdjustWindowRectEx(&WindowRect,dwStyle,FALSE,dwExStyle); // Adjust Window To True Requested Size

  // Create The Window
  //

  if (!(g_Window = CreateWindowEx(dwExStyle,
				  "GoofyClass",
				  title,
				  dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
				  0, 0,
				  WindowRect.right-WindowRect.left,
				  WindowRect.bottom-WindowRect.top,
				  NULL,
				  NULL,
				  g_hInst,
				  NULL)))
    {
      KillGLWindow();
      return FALSE;
    }

  // Did We Get A Device Context?
  //

  if (!(hDC=GetDC(g_Window)))
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  // Did Windows Find A Matching Pixel Format?
  //

  pfd.cColorBits = (BYTE)bits;

  if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  // Are We Able To Set The Pixel Format?
  //

  if(!SetPixelFormat(hDC,PixelFormat,&pfd))
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  // Are We Able To Get A Rendering Context?
  //

  if (!(hRC=wglCreateContext(hDC)))
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  // Try To Activate The Rendering Context
  //

  if(!wglMakeCurrent(hDC,hRC))
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  ShowWindow(g_Window,SW_SHOW);   // Show The Window
  SetForegroundWindow(g_Window);  // Slightly Higher Priority
  SetFocus(g_Window);
  ResizeGlScene(width, height);   // Set Up Our Perspective GL Screen

  // Initialize Our Newly Created GL Window
  //

  if (!InitGL())
    {
      KillGLWindow();	// Reset The Display
      return FALSE;	// Return FALSE
    }

  return TRUE;
}
#endif

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		16,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	


	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	g_hInst			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= g_hInst;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(g_Window=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								g_hInst,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hDC=GetDC(g_Window)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(g_Window,SW_SHOW);						// Show The Window
	SetForegroundWindow(g_Window);						// Slightly Higher Priority
	SetFocus(g_Window);									// Sets Keyboard Focus To The Window
	ResizeGlScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


DWORD WINAPI DoSplashMethod(LPVOID lpParameter)
{
  MSG  msg;
  BOOL bDone = FALSE;

  if ( FALSE == CreateGLWindow("ITSinc Libraries",500,500,16,TRUE) ) return 0;

  while( !bDone )
    {
      if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
	{
	  if ( WM_QUIT != msg.message )
	    {
	      TranslateMessage(&msg);
	      DispatchMessage(&msg);
	    }
	  else
	    {
	      bDone = TRUE;
	    }
	}
      else if ( FALSE == DrawGLScene() && g_Active )
	{
	  bDone = TRUE;
	}
      else
	{
	  SwapBuffers(hDC);
	}
    }

  KillGLWindow();

  return msg.wParam;
}

InterfaceMethod UINT WINAPI TestAction(MSIHANDLE hInstall)
{
  DWORD dThreadId;
  DWORD dThreadRc;

  if ( (HANDLE)NULL == (g_Thread= CreateThread(NULL,0,
					       (LPTHREAD_START_ROUTINE)DoSplashMethod,
					       NULL,0,&dThreadId)) )
    {
      MessageBox(NULL,"CreateThreadFailed","CreateThreadFailed",MB_OK);
      return ERROR_SUCCESS;
    }

  switch( WaitForSingleObject(g_Thread,20000) )
    {
    case WAIT_TIMEOUT:
      TerminateThread(g_Thread,0);

    case WAIT_ABANDONED:
    case WAIT_OBJECT_0:
      break;
    }

  GetExitCodeThread(g_Thread,&dThreadRc);

  CloseHandle(g_Thread);

  return ERROR_SUCCESS;
}

  
InterfaceMethod BOOL WINAPI DllMain(HANDLE hModule,
		    DWORD  dwReason,
		    LPVOID lpReserved)
{
  switch( dwReason )
    {
    case DLL_PROCESS_ATTACH:
      g_hInst  = (HINSTANCE)hModule;
      g_Class  = (ATOM)NULL;
      g_Window = (HWND)NULL;
      g_Active = TRUE;
      hDC      = NULL;
      hRC      = NULL;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
    }

  return TRUE;
}

