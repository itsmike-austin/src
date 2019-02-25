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
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include <OpenCone.h>

#ifndef __USE_SIMD
#define __USE_SIMD
#endif
#ifndef __UNALIGNED_LIB
#define __UNALIGNED_LIB
#endif
#include <CVector.h>

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

vec3 cube[] = {
  {-1.0f, -1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},

  {-1.0f,  1.0f, -1.0f},
  {-1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f, -1.0f},

  {-1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f,  1.0f},
  {-1.0f, -1.0f,  1.0f},

  { 1.0f, -1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f, -1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f, -1.0f},
};

vec3 rotcube[] = {
  {-1.0f, -1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},

  {-1.0f,  1.0f, -1.0f},
  {-1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f, -1.0f},

  {-1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f,  1.0f},
  {-1.0f, -1.0f,  1.0f},

  { 1.0f, -1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f, -1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f, -1.0f},
};

vec3 transcube[] = {
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },

  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },

  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },

  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },

  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },

  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 0.0f }
};

vec3 dispcube[] = {
  {-1.0f, -1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},

  {-1.0f,  1.0f, -1.0f},
  {-1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f,  1.0f, -1.0f},

  {-1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f, -1.0f},
  { 1.0f, -1.0f,  1.0f},
  {-1.0f, -1.0f,  1.0f},

  { 1.0f, -1.0f, -1.0f},
  { 1.0f,  1.0f, -1.0f},
  { 1.0f,  1.0f,  1.0f},
  { 1.0f, -1.0f,  1.0f},

  {-1.0f, -1.0f, -1.0f},
  {-1.0f, -1.0f,  1.0f},
  {-1.0f,  1.0f,  1.0f},
  {-1.0f,  1.0f, -1.0f},
};

typedef struct {
  float x,y;
}tex2d;

tex2d faces[] = {
  {0.0f, 0.0f},
  {1.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 1.0f},

  {1.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 1.0f},
  {0.0f, 0.0f},

  {0.0f, 1.0f},
  {0.0f, 0.0f},
  {1.0f, 0.0f},
  {1.0f, 1.0f},

  {1.0f, 1.0f},
  {0.0f, 1.0f},
  {0.0f, 0.0f},
  {1.0f, 0.0f},

  {1.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 1.0f},
  {0.0f, 0.0f},

  {0.0f, 0.0f},
  {1.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 1.0f},
};

float* g_TriangleAngles;
vec3*  g_TriangleFan;

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

extern "C" AUX_RGBImageRec* GetDot();

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

float rotx = 0.0f;
float roty = 0.0f;
float rotz = 0.0f;

mat3 rotmat = {
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f
};

vec3 delx = { 0.00f, 0.00f, 0.05f };

SimpleOpenCone aCone(14,0.5,2.0);

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
  glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	// Black Background
  glClearDepth(1.0f);			// Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
  glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

#if 1
  GLfloat global_ambient[4]={0.2f, 0.2f,  0.2f, 1.0f};	// Set Ambient Lighting To Fairly Dark Light (No Color)
  GLfloat light0pos[4]=     {0.0f, 0.0f, 1.0f, 1.0f};	// Set The Light Position
  GLfloat light0ambient[4]= {0.5f, 0.5f,  0.5f, 1.0f};	// More Ambient Light
  GLfloat light0diffuse[4]= {0.3f, 0.3f,  0.3f, 1.0f};	// Set The Diffuse Light A Bit Brighter
  GLfloat light0specular[4]={1.0f, 1.0f,  1.0f, 1.0f};	// Fairly Bright Specular Lighting

  GLfloat lmodel_ambient[]= {0.5f,0.5f,0.5f,1.0f};	// And More Ambient Light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);// Set The Ambient Light Model

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);// Set The Global Ambient Light Model
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);		 // Set The Lights Position
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);	 // Set The Ambient Light
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diffuse);	 // Set The Diffuse Light
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0specular);	 // Set Up Specular Lighting
  glEnable(GL_LIGHTING);				 // Enable Lighting
  glEnable(GL_LIGHT0);					 // Enable Light0

  glMateriali(GL_FRONT, GL_SHININESS, 128);
#else
  GLfloat mat_spec [] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shine[] = { 90.0 };
  GLfloat light_pos[] = { 1.0, 1.0, 20.0, 0.0 };

  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shine);
  // glLightfv(GL_LIGHT0,GL_POSITION,light_pos);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
#endif

  glClearColor(0.0f,0.0f,0.0f,1.0f);

  return TRUE;
}

GLfloat glfMaterialColor[]={0.8f,0.2f,0.8f,1.0f};	// Set The Material Color
GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};		// Sets Up Specular Lighting

int DrawGLScene(GLvoid)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0f,0.0f,translate_z);

#if 0
  GLUquadricObj* pQuadObj;

  // glColor3f(0.0,1.0,0.0);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,glfMaterialColor);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
  pQuadObj = gluNewQuadric();
  gluQuadricDrawStyle(pQuadObj,GLU_FILL);
  gluQuadricNormals(pQuadObj,GLU_SMOOTH);
  gluSphere(pQuadObj,0.5,30,30);
  gluDeleteQuadric(pQuadObj);
  glPopMatrix();
#endif

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

#if 1
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,glfMaterialColor);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
  aCone.Draw();
#endif

  xrot += 0.3f;
  yrot += 0.2f;
  zrot += 0.4f;


#if 0
  

  // Reset the rotation matrix
  //

  // Add 5 degress to the rotation axis
  //

  rotx += 0.003f;
  roty += 0.002f;
  rotz += 0.004f;

  Mat3RotateRHXYZ(&rotmat,rotx,roty,rotz);

  for( int i=0 ; i < 24 ; ++i ) Mat3MultiplyVec(&rotcube[i],&rotmat,&cube[i]);
  for( int i=0 ; i < 24 ; ++i ) Vec3Add(&transcube[i],&transcube[i],&delx);
  for( int i=0 ; i < 24 ; ++i ) Vec3Add(&dispcube[i],&transcube[i],&rotcube[i]);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glEnable(GL_BLEND);
  glColor3ub( 255, 245,13 );
  
#if 0
      glBegin(GL_QUADS);
      for( int i=0 ; i < 24 ; ++i )
	{
	  glTexCoord2d(faces[i].x,faces[i].y);
	  glVertex3f(dispcube[i].x,dispcube[i].y,dispcube[i].z);
	}
      glEnd();

#else
      glBegin(GL_QUADS);
      {
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
      }
      glEnd();
#endif

  xrot+=0.3f;
  yrot+=0.2f;
  zrot+=0.4f;
#endif

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
