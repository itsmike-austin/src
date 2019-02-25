/*
 *
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *		Conversion to Visual Studio.NET done by GRANT JAMES(ZEUS)
 */

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

enum DisplayPhase { FlagPhase, ExplosionPhase, CollectionPhase, BlockPhase };
DisplayPhase CurrentPhase = FlagPhase;

HDC       hDC=NULL;
HGLRC     hRC=NULL;
HWND      hWnd=NULL;
HINSTANCE hInstance;
UINT      timer;
bool      keys[256];
bool      active     = TRUE;
bool      fullscreen = TRUE;

int   bump_count = 0;
float translate_z = -5.0f;
float trans_save  = 0.0f;

float points[45][45][3];  // The Array For The Points On The Grid Of Our "Wave"
int wiggle_count = 0;     // Counter Used To Control How Fast Flag Waves

GLfloat	xrot;
GLfloat	yrot;
GLfloat	zrot;
GLfloat hold;

#define TextureCount 2

GLuint texture[1];
GLuint texdot[1];

#define MaxParticles 1000

typedef struct						// Create A Structure For Particle
{
	bool	active;  // Active (Yes/No)
	float	life;    // Particle Life
	float	fade;    // Fade Speed
	float	r;       // Red Value
	float	g;       // Green Value
	float	b;       // Blue Value
	float	x;       // X Position
	float	y;       // Y Position
	float	z;       // Z Position
	float	xi;      // X Direction
	float	yi;      // Y Direction
	float	zi;      // Z Direction
	float	xg;      // X Gravity
	float	yg;      // Y Gravity
	float	zg;      // Z Gravity
}particles;

particles particle[MaxParticles];

static GLfloat colors[12][3]=		// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

float	slowdown=2.0f;  // Slow Down Particles
float	xspeed;         // Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;         // Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom=-40.0f;    // Used To Zoom Out
GLuint	col;            // Current Color Selection

extern "C" AUX_RGBImageRec* GetBounce();
extern "C" AUX_RGBImageRec* GetDot();

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int LoadGLTextures()
{
  int Status = TRUE;			// Status Indicator
  AUX_RGBImageRec *TextureImage[2];

  memset(TextureImage,0,sizeof(void *)*1);

  TextureImage[0] = GetBounce();
  TextureImage[1] = GetDot();

  for( int i=0 ; i < TextureCount ; ++i ) if ( NULL == TextureImage[i] ) Status = FALSE;

  if ( TRUE == Status )
    {
      glGenTextures(1,&texture[0]);
      glBindTexture(GL_TEXTURE_2D,texture[0]);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      glGenTextures(1,&texdot[0]);
      glBindTexture(GL_TEXTURE_2D,texdot[0]);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

  for( int i=0 ; i < TextureCount ; ++i )
    {
      if ( NULL != TextureImage[i] ) free((void*)TextureImage[i]);
    }

  return Status;
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
  height = (0 == height ? 1 : height);

  glViewport(0,0,width,height);		// Reset The Current Viewport

  glMatrixMode(GL_PROJECTION);		// Select The Projection Matrix
  glLoadIdentity();			// Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window
  //

  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);		// Select The Modelview Matrix
  glLoadIdentity();			// Reset The Modelview Matrix
}

int InitGL(GLvoid)
{
  int iRc;

  if ( (iRc = LoadGLTextures()) )
    {
      glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
      glShadeModel(GL_SMOOTH);			// Enable Smooth Shading
      glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	// Black Background
      glClearDepth(1.0f);			// Depth Buffer Setup
      glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
      glDepthFunc(GL_LEQUAL);			// The Type Of Depth Testing To Do

      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

      glPolygonMode(GL_BACK,GL_FILL);            // All faces are  solid
      glPolygonMode(GL_FRONT,GL_FILL);

      for( int x=0 ; x < 45 ; ++x )
	{
	  for( int y=0 ; y < 45 ; ++y )
	    {
	      points[x][y][0] = float(((float)x/5.0f) - 4.5f);
	      points[x][y][1] = float(((float)y/5.0f) - 4.5f);
	      points[x][y][2] = float(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f));
	    }
	}

      for( int i=0 ; i < MaxParticles ; ++i )
	{
	  particle[i].active = true;
	  particle[i].life   = 1.0f;
	  particle[i].fade   = float(rand()%100)/1000.0f+0.003f; // Random Fade Speed
	  particle[i].r      = colors[i*(12/MaxParticles)][0];   // Select Red Rainbow Color
	  particle[i].g      = colors[i*(12/MaxParticles)][1];   // Select Red Rainbow Color
	  particle[i].b      = colors[i*(12/MaxParticles)][2];   // Select Red Rainbow Color
	  particle[i].xi     = float((rand()%50)-26.0f)*10.0f;   // Random Speed On X Axis
	  particle[i].yi     = float((rand()%50)-25.0f)*10.0f;   // Random Speed On Y Axis
	  particle[i].zi     = float((rand()%50)-25.0f)*10.0f;   // Random Speed On Z Axis
	  particle[i].xg     = 0.0f;                             // Set Horizontal Pull To Zero
	  particle[i].yg     =-0.8f;                             // Set Vertical Pull Downward
	  particle[i].zg     = 0.0f;                             // Set Pull On Z Axis To Zero
	}
    }

  return iRc;
}

int DrawGLScene(GLvoid)
{
  int x,y;
  float float_x,float_y,float_z,float_xb,float_yb;

  static int loopstop = 0;

  // Clear the depth buffer and reload the view matrix
  //

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,translate_z);

  if ( FlagPhase == CurrentPhase )
    {
      // Reset the rotation matrix
      //

      glRotatef(xrot,1.0f,0.0f,0.0f);
      glRotatef(yrot,0.0f,1.0f,0.0f);
      glRotatef(zrot,0.0f,0.0f,1.0f);

      // Bind the texture and start painting
      //

      glBindTexture(GL_TEXTURE_2D, texture[0]);

      glBegin(GL_QUADS);
      {
	for( x = 0; x < 44; x++ )
	  {
	    for( y = 0; y < 44; y++ )
	      {
		float_x = float(x)/44.0f;
		float_y = float(y)/44.0f;
		float_xb = float(x+1)/44.0f;
		float_yb = float(y+1)/44.0f;

		glTexCoord2f( float_x, float_y);
		glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );

		glTexCoord2f( float_x, float_yb );
		glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );

		glTexCoord2f( float_xb, float_yb );
		glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );

		glTexCoord2f( float_xb, float_y );
		glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
	      }
	  }
      }
      glEnd();

      if( wiggle_count == 2 )
	{
	  for( y = 0; y < 45; y++ )
	    {
	      hold=points[0][y][2];
	      for( x = 0; x < 44; x++)
		{
		  points[x][y][2] = points[x+1][y][2];
		}
	      points[44][y][2]=hold;
	    }
	  wiggle_count = 0;
	}

      wiggle_count++;
    }
  else if (ExplosionPhase == CurrentPhase )
    {

      glBindTexture(GL_TEXTURE_2D, texture[1]);

      for (int loop=0 ; loop<MaxParticles ; ++loop)                      // Loop Through All The Particles
	{
	  if (particle[loop].active)	                                // If The Particle Is Active
	    {
	      float x=particle[loop].x;	                                // Grab Our Particle X Position
	      float y=particle[loop].y;	                                // Grab Our Particle Y Position
	      float z=particle[loop].z+zoom;                             // Particle Z Pos + Zoom

	      // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
	      //

	      glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

	      glBegin(GL_TRIANGLE_STRIP);                                // Build Quad From A Triangle Strip
	      glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z);            // Top Right
	      glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z);            // Top Left
	      glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z);            // Bottom Right
	      glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z);            // Bottom Left
	      glEnd();

	      particle[loop].x+=particle[loop].xi/(slowdown*1000);       // Move On The X Axis By X Speed
	      particle[loop].y+=particle[loop].yi/(slowdown*1000);       // Move On The Y Axis By Y Speed
	      particle[loop].z+=particle[loop].zi/(slowdown*1000);       // Move On The Z Axis By Z Speed

	      particle[loop].xi+=particle[loop].xg;                      // Take Pull On X Axis Into Account
	      particle[loop].yi+=particle[loop].yg;                      // Take Pull On Y Axis Into Account
	      particle[loop].zi+=particle[loop].zg;                      // Take Pull On Z Axis Into Account
	      particle[loop].life-=particle[loop].fade;                  // Reduce Particles Life By 'Fade'

	      glFlush();

	      if (particle[loop].life<0.0f)                              // If Particle Is Burned Out
		{
		  particle[loop].life=1.0f;                              // Give It New Life
		  particle[loop].fade=float(rand()%100)/1000.0f+0.003f;  // Random Fade Value
		  particle[loop].x=0.0f;                                 // Center On X Axis
		  particle[loop].y=0.0f;                                 // Center On Y Axis
		  particle[loop].z=0.0f;                                 // Center On Z Axis
		  particle[loop].xi=xspeed+float((rand()%60)-32.0f);     // X Axis Speed And Direction
		  particle[loop].yi=yspeed+float((rand()%60)-30.0f);     // Y Axis Speed And Direction
		  particle[loop].zi=float((rand()%60)-30.0f);            // Z Axis Speed And Direction
		  particle[loop].r=colors[col][0];                       // Select Red From Color Table
		  particle[loop].g=colors[col][1];                       // Select Green From Color Table
		  particle[loop].b=colors[col][2];                       // Select Blue From Color Table
		}
	    }
	}
    }
  else if (BlockPhase == CurrentPhase )
    {
      // Reset the rotation matrix
      //

      glRotatef(xrot,1.0f,0.0f,0.0f);
      glRotatef(yrot,0.0f,1.0f,0.0f);
      glRotatef(zrot,0.0f,0.0f,1.0f);

      glBegin(GL_QUADS);
      {
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
      }
      glEnd();
    }

  xrot+=0.3f;
  yrot+=0.2f;
  zrot+=0.4f;

  return TRUE;
}

GLvoid KillGLWindow(GLvoid)
{
  // If fullscreen, switch to desktop and show pointer
  //

  if (fullscreen)
    {
      ChangeDisplaySettings(NULL,0);
      ShowCursor(TRUE);
    }

  // Release the DC & RC contexts
  //

  if (hRC)
    {
      wglMakeCurrent(NULL,NULL);
      wglDeleteContext(hRC);
      hRC = NULL;
    }

  if (hDC)
    {
      ReleaseDC(hWnd,hDC);
      hDC = NULL;
    }

  // Destroy the window
  //

  if (hWnd)
    {
      DestroyWindow(hWnd);
      hWnd =NULL ;
    }

  // Cleanup the class registration
  //

  UnregisterClass("OpenGL",hInstance);
  hInstance = NULL;
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:			*
 *	title			- Title To Appear At The Top Of The Window	*
 *	width			- Width Of The GL Window Or Fullscreen Mode	*
 *	height			- Height Of The GL Window Or Fullscreen Mode	*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)	*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
  GLuint PixelFormat;
  DWORD  dwExStyle;
  DWORD  dwStyle;
  int    iStartX = 0;
  int    iStartY = 0;

  RECT WindowRect = {
    (long)0,
    (long)0,
    (long)width,
    (long)height
  };

  hInstance  = GetModuleHandle(NULL);

  WNDCLASS wc = {
    CS_HREDRAW | CS_VREDRAW | CS_OWNDC,   // Redraw On Size, And Own DC For Window.
    (WNDPROC)WndProc,                     // WndProc Handles Messages
    0,                                    // No Extra Window Data
    0,                                    // No Extra Window Data
    hInstance,                            // Set The Instance
    LoadIcon(NULL, IDI_WINLOGO),          // Load The Default Icon
    LoadCursor(NULL, IDC_ARROW),          // Load The Arrow Pointer
    NULL,                                 // No Background Required For GL
    NULL,                                 // We Don't Want A Menu
    "OpenGL"                              // Set The Class Name
  };
  
  fullscreen = fullscreenflag;

  // Register the class structure to build the callback interface
  //

  if (!RegisterClass(&wc)) return FALSE;

  // Change to fullscreen mode if required
  //

  if (fullscreen)
    {
      DEVMODE dmScreenSettings;
      memset(&dmScreenSettings,0,sizeof(dmScreenSettings));

      dmScreenSettings.dmSize=sizeof(dmScreenSettings); // Size Of The Devmode Structure
      dmScreenSettings.dmPelsWidth	= width;        // Selected Screen Width
      dmScreenSettings.dmPelsHeight	= height;       // Selected Screen Height
      dmScreenSettings.dmBitsPerPel	= bits;         // Selected Bits Per Pixel
      dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

      // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
      //

      if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
	{
	  // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
	  //

	  if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
	    {
	      fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
	    }
	  else
	    {
	      return FALSE;
	    }
	}
    }

  if (fullscreen)
    {
      dwExStyle = WS_EX_APPWINDOW;   // Window Extended Style
      dwStyle   = WS_POPUP;          // Windows Style
      ShowCursor(FALSE);             // Hide Mouse Pointer
    }
  else
    {
      dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;  // Window Extended Style
      dwStyle=WS_OVERLAPPEDWINDOW;                   // Windows Style
    }

  AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

  // Get the work area for the primary monitor
  //

  {
    RECT rMonInfo;

    if ( SystemParametersInfo(SPI_GETWORKAREA,0,(LPVOID)&rMonInfo,0) )
      {
	int iCenterX = (rMonInfo.right  - rMonInfo.left)/2;
	int iCenterY = (rMonInfo.bottom - rMonInfo.top)/2;

	iStartX = iCenterX - (width/2);
	iStartY = iCenterY - (height/2);
      }
  }
 

  // Create The Window
  //

  if (!(hWnd=CreateWindowEx(dwExStyle,                                  // Extended Style For The Window
			    "OpenGL",                                   // Class Name
			    title,                                      // Window Title
			    dwStyle | WS_CLIPSIBLINGS |WS_CLIPCHILDREN, // Required Window Style
			    iStartX,iStartY,                            // Window Position
			    WindowRect.right-WindowRect.left,           // Calculate Window Width
			    WindowRect.bottom-WindowRect.top,           // Calculate Window Height
			    NULL,                                       // No Parent Window
			    NULL,                                       // No Menu
			    hInstance,                                  // Instance
			    NULL)))                                     // Dont Pass Anything To WM_CREATE
    {
      KillGLWindow();
      return FALSE;
    }

  static PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
    1,                             // Version Number
    PFD_DRAW_TO_WINDOW |           // Format Must Support Window
    PFD_SUPPORT_OPENGL |           // Format Must Support OpenGL
    PFD_DOUBLEBUFFER,              // Must Support Double Buffering
    PFD_TYPE_RGBA,                 // Request An RGBA Format
    bits,                          // Select Our Color Depth
    0, 0, 0, 0, 0, 0,              // Color Bits Ignored
    0,                             // No Alpha Buffer
    0,                             // Shift Bit Ignored
    0,                             // No Accumulation Buffer
    0, 0, 0, 0,                    // Accumulation Bits Ignored
    16,                            // 16Bit Z-Buffer (Depth Buffer)
    0,                             // No Stencil Buffer
    0,                             // No Auxiliary Buffer
    PFD_MAIN_PLANE,                // Main Drawing Layer
    0,                             // Reserved
    0, 0, 0                        // Layer Masks Ignored
  };

  if (!(hDC=GetDC(hWnd)))
    {
      KillGLWindow();
      return FALSE;
    }

  if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
    {
      KillGLWindow();
      return FALSE;
    }

  if(!SetPixelFormat(hDC,PixelFormat,&pfd))
    {
      KillGLWindow();
      return FALSE;
    }

  if (!(hRC=wglCreateContext(hDC)))
    {
      KillGLWindow();
      return FALSE;
    }

  if(!wglMakeCurrent(hDC,hRC))
    {
      KillGLWindow();
      return FALSE;
    }

  ShowWindow(hWnd,SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
  ReSizeGLScene(width, height);

  if (!InitGL())
    {
      KillGLWindow();
      return FALSE;
    }

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  switch (uMsg)
    {
    case WM_ACTIVATE:           // Watch For Window Activate Message
      {
	if (!HIWORD(wParam))    // Check Minimization State
	  {
	    active=TRUE;        // Program Is Active
	  }
	else
	  {
	    active=FALSE;       // Program Is No Longer Active
	  }
	return 0;
      }

    case WM_SYSCOMMAND:         // Intercept System Commands
      {
	switch (wParam)         // Check System Calls
	  {
	  case SC_SCREENSAVE:   // Screensaver Trying To Start?
	  case SC_MONITORPOWER: // Monitor Trying To Enter Powersave?
	    return 0;           // Prevent From Happening
	  }
	break;
      }

    case WM_CLOSE:              // Did We Receive A Close Message?
      {
	PostQuitMessage(0);
	return 0;
      }

    case WM_SIZE:
      {
	ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); // LoWord=Width, HiWord=Height
	return 0;
      }

    case WM_TIMER:
      if ( bump_count <= 180 )
	{
	  ++bump_count;
	  timer = SetTimer(hWnd,1,10,NULL);
	  translate_z -= 0.5f;
	}
      else if ( bump_count <= 250 )
	{
	  if ( 181 == bump_count )
	    {
	      CurrentPhase = ExplosionPhase;
	      glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	      glDisable(GL_DEPTH_TEST);
	      glEnable(GL_BLEND);
	      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	      glBindTexture(GL_TEXTURE_2D,texture[1]);
	      trans_save  = translate_z;
	      translate_z = -5.0;
	    }

	  ++bump_count;
	  // translate_z += 0.5f;
	  translate_z = -5.0;
	  timer = SetTimer(hWnd,1,10,NULL);
	}
      else if ( bump_count <= 540 )
	{
	  if ( 251 == bump_count )
	    {
	      CurrentPhase = BlockPhase;
	      glDisable(GL_BLEND);
	      glEnable(GL_DEPTH_TEST);
	      glDepthFunc(GL_LEQUAL);
	      glBindTexture(GL_TEXTURE_2D, texture[0]);
	      glColor4f(1.0f,1.0f,1.0f,1.0f);
	      translate_z = trans_save;
	    }

	  if ( translate_z < -5.0f ) translate_z += 0.5f;
	  ++bump_count;
	  timer = SetTimer(hWnd,1,10,NULL);
	}
      else
	{
	  PostQuitMessage(0);
	  return 0;
	}
    }

  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG		msg;
  BOOL	done = FALSE;

  fullscreen = FALSE;

  // Create Our OpenGL Window
  //

  if (!CreateGLWindow("ITSinc Vector Library Installer",640,480,16,fullscreen)) return 0;

  timer = SetTimer(hWnd,1,1000,NULL);

  while(!done)
    {
      if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // Is There A Message Waiting?
	{
	  if (msg.message==WM_QUIT)
	    {
	      done=TRUE;
	    }
	  else
	    {
	      TranslateMessage(&msg);				// Translate The Message
	      DispatchMessage(&msg);				// Dispatch The Message
	    }
	}
      else										// If There Are No Messages
	{
	  // Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
	  //
	  
	  if ((active && !DrawGLScene()) || keys[VK_ESCAPE])
	    {
	      done=TRUE;
	    }
	  else
	    {
	      SwapBuffers(hDC);
	    }
	}
    }

  KillGLWindow();
  return (msg.wParam);
}
