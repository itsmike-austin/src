/* ============================================================================
 Name        : FanRobotControl.c
 Author      : Mike Burnett
 Version     : 0.0
 Copyright   : (c)(p) ITSinc 2015
 Description : Control loop program for a RPi to run 3 internal roof fans.
 ----------------------------------------------------------------------------
 TBD: No additional modifications at this time.
 ============================================================================ */

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#include "SharedMemory.h"
#include "Semaphore.h"
#include "OutputError.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Defines required by the program.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Defines for the 3 110 volt pins
// XXX: THESE PINE REQUIRE VERIFICATION

#define PIN1  7
#define PIN2  8
#define PIN3 17

// Defines required for access to the virtual memory system

#define PAGE_SIZE  (1024*4)
#define BLOCK_SIZE (1024*4)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Definition of the shared memory segment that holds the sensor data and
 * operation parameters.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct {
  float fOutsideShutdownTemp;        // Low temperature to shutdown all fans
  float fBayOneToggleTemp;           // Off/On temperature for fan in bay 1
  float fBayTwoToggleTemp;           // Off/On temperature for fan in bay 2
  float fBayThreeToggleTemp;         // Off/On temperature for fan in bay 3
  float fBayOneTemp;                 // Current bay 1 temperature
  float fBayTwoTemp;                 // Current bay 2 temperature
  float fBayThreeTemp;               // Current bay 3 temperature
  float fOutsideTemp;                // Current outside temperature
  float fBayOneDelta;                // Outside + delta Off/On trigger
  float fBayTwoDelta;                // Outside + delta Off/On trigger
  float fBayThreeDelta;              // Outside + delta Off/On trigger
  int   bBayOneStatus;               // Enable/Disable bay 1 fan
  int   bBayTwoStatus;               // Enable/Disable bay 2 fan
  int   bBayThreeStatus;             // Enable/Disable bay 3 fan
  int   bBayOneRunning;              // Bay 1 is currently running
  int   bBayTwoRunning;              // Bay 2 is currently running
  int   bBayThreeRunning;            // Bay 3 is currently running
  int   iPort;                       // IP port for communications.
}OpsParms,*pOpsParms;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Operational global parameters.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int iShmId;                          // Shared memory identifier
int iSemId;                          // Semaphore identifier
int mem_fd;                          // File descriptor for /dev/mem

void* gpio_map;                      // memory mapping for gpio access

volatile unsigned *gpio;             // the map can be volatile.

int bDoMore;                         // Main control loop boolean

// File descriptors and definitions.

FILE* pBayOneTemp;
FILE* pBayTwoTemp;
FILE* pBayThreeTemp;
FILE* pOutsideTemp;

char* pBayOneFileName   = "/sys/bus/w1/28-00000000000000000";
char* pBayTwoFileName   = "/sys/bus/w1/28-0000000000000000a";
char* pBayThreeFileName = "/sys/bus/w1/28-0000000000000000c";
char* pOutsideFileName  = "/sys/bus/w1/28-0000000000000000d";

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Forward method declarations
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int Init(OpsParms** ppParms);
int Terminate(pOpsParms pData);
void SignalShutdown(int iSignal);

/* ----------------------------------------------------------------------------
 * Method entry point
 * ---------------------------------------------------------------------------- */

int main(void) {

  int bDoLoop = TRUE;

  pOpsParms pParms = NULL;

  if ( -1 == Init(&pParms) ) return -1;

  // Setup the termination signals

  signal(SIGUSR1,SignalShutdown);
  signal(SIGKILL,SignalShutdown);

  // Main operations loop

  while( bDoMore ) {

    // Read the sensors

    ReadTempFromFile(pBayOneTemp,&pParms->fBayOneTemp);
    ReadTempFromFile(pBayTwoTemp,&pParms->fBayTwoTemp);
    ReadTempFromFile(pBayThreeTemp,&pParms->fBayThreeTemp);
    ReadTempFromFile(pOutsideTemp,&pParms->fOutsideTemp);

    if ( bDoLoop ) {

      // The temperature has fallen below shutdown temp to stop processing

    	if ( pParms->fOutsideShutdownTemp < pParms->fOutsideTemp ) {
    		GPIO_CLR = 1 << PIN1;
    		GPIO_CLR = 1 << PIN2;
    		GPIO_CLR = 1 << PIN3;
        	bDoLoop = FALSE;
        	continue;
        }

      // If all 3 fans are turned off, stop processing

      if ( 0 == pParms->bBayOneStatus && 0 == pParms->bBayTwoStatus && 0 == pParms->bBayThreeStatus ) {
    		bDoLoop = FALSE;
    		continue;
      }

      // Shutdown any fans that are supposed to be turned off.

      if ( 0 == pParms->bBayOneStatus   ) { GPIO_CLR = 1 << PIN1; }
      if ( 0 == pParms->bBayTwoStatus   ) { GPIO_CLR = 1 << PIN2; }
      if ( 0 == pParms->bBayThreeStatus ) { GPIO_CLR = 1 << PIN3; }

      // If the fan is active and temp > outside + delta && not running: start the fan
      // else if the fan is running: stop the fan
      // else the fan needs to keep doing whatever it was doing.

      if ( 0 != pParms->bBayOneStatus && pParms->fBayOneTemp > (pParms->fBayOneToggleTemp + pParms->fBayOneDelta) && 0 == pParms->bBayOneRunning ) {
    	  GPIO_SET = 1 << PIN1;
    	  pParms->bBayOneRunning = 1;
      }else if ( pParms->bBayOneRunning ) {
    	  GPIO_CLR = 1 << PIN1;
    	  pParms->bBayOneRunning = 0;
      }

      if ( 0 != pParms->bBayTwoStatus && pParms->fBayTwoTemp > (pParms->fBayTwoToggleTemp + pParms->fBayTwoDelta) && 0 == pParms->bBayTwoRunning ) {
    	  GPIO_SET = 1 << PIN2;
    	  pParms->bBayTwoRunning = 1;
      }else if ( pParms->bBayTwoRunning ) {
    	  GPIO_CLR = 1 << PIN2;
    	  pParms->bBayTwoRunning = 0;
      }

      if ( 0 != pParms->bBayTwoStatus && pParms->fBayTwoTemp > (pParms->fBayTwoToggleTemp + pParms->fBayTwoDelta) && 0 == pParms->bBayThreeRunning ) {
    	  GPIO_SET = 1 << PIN3;
    	  pParms->bBayThreeRunning = 1;
      }else if ( pParms->bBayThreeRunning ) {
    	  GPIO_CLR = 1 << PIN3;
    	  pParms->bBayThreeRunning = 0;
      }

      // Check to see if the operation status changed when we're not looping.

    }else if ( (pParms->bBayOneStatus != 0 || 0 != pParms->bBayTwoStatus || 0 != pParms->bBayThreeStatus) && (pParms->fOutsideTemp > pParms->fOutsideShutdownTemp) ) {
      bDoLoop = TRUE;
    }

    // Snooze for a while between checks.

    sleep(60);
  }

  return EXIT_SUCCESS;
}

/* ----------------------------------------------------------------------------
 * Terminate program when signaled.
 * ---------------------------------------------------------------------------- */

void SignalShutdown(int iSignal)
{
  Terminate(gpio);
  bDoMore = FALSE;
}

/* ----------------------------------------------------------------------------
 * Read the temperature into the requested variable from the system bus file
 * ---------------------------------------------------------------------------- */

int ReadTempFromFile(FILE* pFile,float* pTemp)
{
  int   iRc = -1;
  int   iTemp;
  float fTemp;

  char  buf[2][256];
  char* cpRc;

  if ( NULL != pFile                          &&
       0    == fseek(pFile,0L,SEEK_SET)       &&
       NULL != (cpRc=fgets(buf[0],256,pFile)) &&
       NULL != (cpRc=fgets(buf[1],256,pFile)) &&
       NULL != (cpRc=strstr(buf[0],"YES"))    &&
       NULL != (cpRc=strstr(buf[1],"t="))     )
    {
      cpRc += 2;
      sscanf(cpRc,"%d",&iTemp);
      fTemp = (float)iTemp;
      *pTemp = (((fTemp / 1000.0f) * 9.0f) / 5.0f) + 32.0f;
      iRc = 0;
    }
  return iRc;
}

/* ----------------------------------------------------------------------------
 * Initialization method
 * ---------------------------------------------------------------------------- */

int Init(OpsParms** ppParms)
{
  pid_t ppid;

  int iRc = -1;

  iShmId = -1;
  iSemId = -1;

  pBayOneTemp   = (FILE*)NULL;
  pBayTwoTemp   = (FILE*)NULL;
  pBayThreeTemp = (FILE*)NULL;
  pOutsideTemp  = (FILE*)NULL;

  // Open /dev/mem

  if ( (mem_fd=open("/dev/mem",O_RDWR|O_SYNC)) < 0 ) {
    OutputError("FanRobotControl: open /dev/mem failed");
    ppid = getppid();
    if ( 1 != ppid ) kill(ppid,SIGCHLD);
    return -1;
  }

  // mmap gpio

  gpio_map = mmap(NULL,                    // Any address in our space will do.
		  BLOCK_SIZE,              // Map length
		  PROT_READ|PROT_WRITE,    // Enable reading and writing
		  MAP_SHARED,              // Shared with other processes
		  mem_fd,                  // File to map
		  GPIO_BASE);              // Offset to gpio peripheral

  // Close the memory file descriptor that is no longer required

  close(mem_fd);

  if ( gpio_map == MAP_FAILED ) {
    close(mem_fd);
    return -1;
  }

  // Assume this pointer is volatile due to paging

  gpio = (volatile unsigned *)gpio_map;

  // Setup the gpio pins to enable the fan motors

  INP_GPIO(PIN1);
  OUT_GPIO(PIN1);
  GPIO_CLR = 1 << PIN1;

  INP_GPIO(PIN2);
  OUT_GPIO(PIN2);
  GPIO_CLR = 1 << PIN2;

  INP_GPIO(PIN3);
  OUT_GPIO(PIN3);
  GPIO_CLR = 1 << PIN3;

  // Setup the io streams to read the temperature sensors

  if ( -1   != (iShmId=AccessSharedMemory(0x32,(char**)ppParms)) &&
       -1   != (iSemId=AccessSemaphore(1,0x23))                  &&
       NULL != (pBayOneTemp=fopen(pBayOneFileName,"r"))          &&
       NULL != (pBayTwoTemp=fopen(pBayTwoFileName,"r"))          &&
       NULL != (pBayThreeTemp=fopen(pBayThreeFileName,"r"))      &&
       NULL != (pOutsideTemp=fopen(pOutsideFileName,"r"))        ) {
    iRc = 0;
  }

  // If something failed during the setup, cleanup the aftermath.

  if ( -1 == iRc ) {
    fclose(pBayOneTemp);
    fclose(pBayTwoTemp);
    fclose(pBayThreeTemp);
    fclose(pOutsideTemp);

    if ( NULL == pBayOneTemp || NULL == pBayTwoTemp || NULL == pBayThreeTemp || NULL == pOutsideTemp ) {
      OutputError("FanRobotControl: fopen(/sys/bus/w1/xxx)");
    }

    if ( -1 != iShmId ) DetachSharedMemory((void*)*ppParms);
  }

  return iRc;
}

/* ----------------------------------------------------------------------------
 * Termination method
 * ---------------------------------------------------------------------------- */

int Terminate(pOpsParms pData)
{
  // Shut all of the fans off

	GPIO_CLR = 1 << PIN1;
	GPIO_CLR = 1 << PIN2;
	GPIO_CLR = 1 << PIN3;

  // Close the system files.

  fclose(pBayOneTemp);
  fclose(pBayTwoTemp);
  fclose(pBayThreeTemp);
  fclose(pOutsideTemp);

  // Unmap the gpio access blocks and release the shared memory

  munmap(gpio,BLOCK_SIZE);
  return DetachSharedMemory((void*)pData);
}




#if 0
#include <stdio.h>
#include <stdlib.h>

#include "SharedMemory.h"
#include "Semaphore.h"

typedef struct {
  float fOutsideShutdownTemp;        // Low temperature to shutdown all fans
  float fBayOneToggleTemp;           // Off/On temperature for fan in bay 1
  float fBayTwoToggleTemp;           // Off/On temperature for fan in bay 2
  float fBayThreeToggleTemp;         // Off/On temperature for fan in bay 3
  float fBayOneTemp;                 // Current bay 1 temperature
  float fBayTwoTemp;                 // Current bay 2 temperature
  float fBayThreeTemp;               // Current bay 3 temperature
  float fOutsideTemp;                // Current outside temperature
  float fBayOneDelta;                // Outside + delta Off/On trigger
  float fBayTwoDelta;                // Outside + delta Off/On trigger
  float fBayThreeDelta;              // Outside + delta Off/On trigger
  int   bBayOneStatus;               // Enable/Disable bay 1 fan
  int   bBayTwoStatus;               // Enable/Disable bay 2 fan
  int   bBayThreeStatus;             // Enable/Disable bay 3 fan
  int   bBayOneRunning;              // Bay 1 is currently running
  int   bBayTwoRunning;              // Bay 2 is currently running
  int   bBayThreeRunning;            // Bay 3 is currently running
  int   iPort;                       // IP port for communications.
}OpsParms,*pOpsParms;

int iShmId;
int iSemId;

int Init(OpsParms** ppParms)
{
	int iRc = -1;

	if ( NULL != ppParms ) {
		iShmId = AccessSharedMemory(0x32,(char**)ppParms);
		if ( -1 != iShmId ) {
			iSemId = AccessSemaphore(1,0x23);
			iRc = (iSemId != -1 ? 0 : -1);
		}
	}
	return iRc;
}

int Terminate(pOpsParms pData)
{
	return DetachSharedMemory((void*)pData);

}

int main(void) {

	int iRc = 0;

	// Connect to the shared memory segment allocated by the parent

	pOpsParms pParms = NULL;

	iRc = Init(&pParms);

	if ( -1 != iRc  && NULL != pParms ) {
		Terminate(pParms);
	}

	// This is where the operations loop should take place. The rest is strictly

	return (0 == iRc ? -1 : EXIT_SUCCESS);
}
#endif
