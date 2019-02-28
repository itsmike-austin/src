/* ==========================================================================
 * This is the home roof bay temperature controller. This module is
 * implemented using a raspberry pi b+ unit running raspberian and is
 * designed to operate three fans based upon temperatures that are
 * contained in an initialization file.
 *
 * Review the command list for the various supported commands. Additional
 * information may be found in the implementation guide. That includes
 * the specifics of the commands and supported command protocols.
 *
 * System auto initialization is used to start this program. The semaphores
 * are used to determine when the child module that actually strobes the
 * temperature sensors and activates the 110v solid state relays activate.
 * This method will fork and exec the child process that manipulates
 * the actual hardware. FanComm stands for Fan Communications module.
 *
 * This system was originally designed as a 3 component element.
 *
 * The system has been simplified to a non-internet super server
 * daemon process that runs continuously using a single network
 * port.
 *
 * Original Design:
 *
 * The system consists of three modules:
 *    1). Communications module: allows externals to talk to the
 *        controller via wi-fi
 *    2). Manipulation module: reads the various temperature sensors
 *        and turn the solid state relays (fans) off and on. There are
 *        three bay and an outside temperature sensor attached to the
 *        system. There are three ssr's which control three fans. One
 *        for each of the roof bays to keep the house roof temperature
 *        within specified limits.
 *    3). Apache server element that reads the IPC data via the comm.
 *        module and creates and sends web pages back to the caller
 *        via the wi-fi interface.
 *
 * --------------------------------------------------------------------------
 * (c) 2014 itsinc (mdb)
 *   Version 1.0
 * ========================================================================== */

#include "Semaphore.h"
#include "SharedMemory.h"
#include "DGramSocket.h"

#include <signal.h>
#include <wait.h>

// This is the parameter map that is contained within the shared memory segment.

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

// These are the parameters used to manage the interprocess communications
// areas used by the system.

typedef struct {
	int       iSemId;
	int       iShmId;
	int       iSocket;
	int       iChildPid;
	pOpsParms pData;
}InitParms,*pInitParms;

// Core system method forward definitions.

int  Init(pInitParms pParms,const char* pDefaultsFile);
void TerminationCleanup(pInitParms pParms);
void WaitForRestart(int iSocket);
int  TalkToFanAgent(int iSocket);

// Location of the initialization file.

const char* pDefaultData = "/usr/share/FanRobot/defaults.inf";

// Control loop operations states.

enum OperatingState { Initializing, Starting, Running, Stopped, Shutdown, Restart, Terminate, Nothing };

enum OperatingState OpState;
enum OperatingState OldOpState;

// System operation parameters including shared memory.

InitParms sParms;

// Externally accessible shutdown variable. XXX: May not be required
// as a global.

pid_t iChildPid  = 0;
int   bKeepGoing = TRUE;

int iStopTime,iStopLoop,iStopCount;

void DoSigTerm(int iSignal)
{
	OpState = Terminate;
}

/* --------------------------------------------------------------------------
 * MAIN ENTRY POINT.
 * -------------------------------------------------------------------------- */

int main(int argc,char* argv[],char* envp[])
{
	int iRc = 0;

	struct sigaction   sa;
	struct sigaction   oldsa;

	char*   pChildProgram = (char*)getenv("FAN_ROBOT_CONTROL");

	if ( NULL == pChildProgram ) return -1;

	// Create the daemon.


	// XXX: Original design was correct... start the child (controller) process
	//      and verify the status of execl for the child

	switch( (sParms.iChildPid=fork()) ) {
	case 0:
		setsid();
		setpgrp();
		break;

	case -1:
	{
		char procError[1024];
		sprintf(procError,"%s fork",argv[0]);
		OutputError(procError);
		return -1;
	}

	default:
		return 0;
	}

	// Intercept the termination signal and try and cleanup on close

	memset((void*)&sa,(char)0,sizeof sa);

	sa.sa_handler = DoSigTerm;

	sigaction(SIGTERM,&sa,&oldsa);

	// Initialize the program.

	OpState    = Starting;
	OldOpState = Nothing;

	if ( -1 == Init(&sParms,pDefaultData) ) {
		return -1;
	}

	// Fork and start the child process. When the child is created,
	// wait for the semaphore to decrement to indicate that the
	// child is running and ready for action.

	switch( (iRc=fork()) ) {
	case -1:
		OutputError("Main: fork");
		TerminationCleanup(&sParms);
		return iRc;

	case 0:
		iRc = setsid();
		{
			FILE* ft = fopen("/tmp/joe.ls","w");
			fprintf(ft,"ssid rc: %d\n",iRc);
			fflush(ft);
			fclose(ft);
		}
		if ( -1 == iRc ) OutputError("Main: setsid");
		iRc = execve(pChildProgram,argv,envp);
		if ( -1 == iRc ) {
			OutputError("Main: execve");
			return iRc;
		}
		break;

	default:
		iChildPid = iRc;
		break;
	}

	iRc = WaitForSem(sParms.iSemId,0);

	if ( -1 == iRc ) {
		OutputError("Main: WaitForSem");
		return iRc;
	}

	// Execute the main loop

	while( bKeepGoing ) {

		switch( OpState ) {
		case Initializing:
		case Nothing:
			break;

		case Starting:

			// Set the initialization state

			OldOpState = OpState;
			OpState    = Running;

			break;

		case Running:

			// Wait for something to on a 60 second delay cycle

			iRc = LoopForDGram(sParms.iSocket,60);  // Wait for a caller

			// Get the command and execute it

			if ( -1 != iRc ) TalkToFanAgent(sParms.iSocket);

			break;

		case Stopped:
			// Execute the requested delay.
			// XXX: Check here to determine if there is a waiting message by using a quick
			//      or short (100ms) select. If a message, check for start; tell the caller
			//      otherwise tell the caller we're stopped.

			// DoStoppedOperation();

			// ???: Maybe this should just be executed in DoStop and remove this as a valid state.

			// If the time period has expired, return state to running.

			if ( iStopCount < iStopLoop ) {
				++iStopCount;
				sleep(iStopTime);
			}else{
				OldOpState = Stopped;
				OpState = Running;
			}
			break;

		case Shutdown:
			// Sleep until the caller says it's ok to resume operations. This should stop all
			// fans until the caller resumes operations.

			WaitForRestart(sParms.iSocket);
			break;

		case Restart:
			// Restart means that the current system socket should be closed and
			// reopened specifying a new listen port.

			if ( -1 != kill(iChildPid,SIGTERM) && -1 != wait(NULL) ) {
				CloseConnection(sParms.iSocket);
				TerminationCleanup(&sParms);

				if ( -1 == Init(&sParms,pDefaultData) ) {
					exit(-1);
				}

				switch( (iRc=fork()) ) {
				case -1:
					OutputError("Main: fork");
					TerminationCleanup(&sParms);
					bKeepGoing = FALSE;
					break;

				case 0:
					setsid();
					iRc = execve(pChildProgram,argv,envp);
					if ( -1 == iRc ) {
						OutputError("Main: execve");
						return iRc;
					}
					break;

				default:
					iChildPid = iRc;
				}
			}

			// If the port switch was successful, switch the state back to operating;
			// otherwise exit the program while cleaning up the system resources
			// in order to allow the operating system to restart the program
			// using the newly saved specified startup information.

			if ( -1 != sParms.iSocket ) {
				OldOpState = Restart;
				OpState    = Running;
			}else{
				bKeepGoing = FALSE;
			}
			break;

		case Terminate:
			kill(iChildPid,SIGTERM);
			CloseConnection(sParms.iSocket);
			bKeepGoing = FALSE;
			break;
		}
	}

	// Remove the semaphore and shared memory segment. The child process should
	// be dinged to let it know that we're shutting down. XXX: Add fork/exec subprocess
	// id save to allow signalling child properly.

	TerminationCleanup(&sParms);

	return iRc;
}

// Definitions for the command list.

typedef int (*CMDPTR)(int iSocket,char* pBufr);

typedef struct {
	char*  pCommand;
	CMDPTR pMethod;
}NetworkCommand,*pNetworkCommand;

// Forward definitions for the commands.

int DoReadAllOnce(int iSocket,char* pBufr);
int DoReadOneOnce(int iSocket,char* pBufr);
int DoReadTwoOnce(int iSocket,char* pBufr);
int DoReadThreeOnce(int iSocket,char* pBufr);
int DoReadOutsideOnce(int iSocket,char* pBufr);
int DoReadToggleOne(int iSocket,char* pBufr);
int DoReadToggleTwo(int iSocket,char* pBufr);
int DoReadToggleThree(int iSocket,char* pBufr);
int DoReadAllLoop(int iSocket,char* pBufr);
int DoReadOneLoop(int iSocket,char* pBufr);
int DoReadTwoLoop(int iSocket,char* pBufr);
int DoReadThreeLoop(int iSocket,char* pBufr);
int DoReadOutsideLoop(int iSocket,char* pBufr);
int DoSetOne(int iSocket,char* pBufr);
int DoSetTwo(int iSocket,char* pBufr);
int DoSetThree(int iSocket,char* pBufr);
int DoSetOutside(int iSocket,char* pBufr);
int DoGetBayOneStatus(int iSocket,char* pBufr);
int DoGetBayTwoStatus(int iSocket,char* pBufr);
int DoGetBayThreeStatus(int iSocket,char* pBufr);
int DoSetBayOneStatus(int iSocket,char* pBufr);
int DoSetBayTwoStatus(int iSocket,char* pBufr);
int DoSetBayThreeStatus(int iSocket,char* pBufr);
int DoBayOneRunStatus(int iSocket,char* pBufr);
int DoBayTwoRunStatus(int iSocket,char* pBufr);
int DoBayThreeRunStatus(int iSocket,char* pBufr);
int DoSetPort(int iSocket,char* pBufr);
int DoWrite(int iSocket,char* pBufr);
int DoStop(int iSocket,char* pBufr);
int DoStart(int iSocket,char* pBufr);
int DoShutdown(int iSocket,char* pBufr);
int DoPingPong(int iSocket,char* pBufr);
int DoRestart(int iSocket,char* pBufr);
int DoTerminate(int iSocket,char* pBufr);

// Full command definitions matching the name of the command to the appropriate method.

NetworkCommand pCmdList[] = {
		{"READALL_ONCE",    DoReadAllOnce},         // Print and pass all parameters back to the caller
		{"READONE_ONCE",    DoReadOneOnce},         // Print sensor 1 temp and pass back to the caller
		{"READTWO_ONCE",    DoReadTwoOnce},         // Print sensor 2 temp and pass back to the caller
		{"READTHREE_ONCE",  DoReadThreeOnce},       // Print sensor 3 temp and pass back to the caller
		{"READOUTSIDE_ONCE",DoReadOutsideOnce},     // Print outside temp and pass back to the caller
		{"READTOGGLEONE",   DoReadToggleOne},       // Print bay 1 toggle temperature back to the caller
		{"READTOGGLETWO",   DoReadToggleTwo},       // Print bay 2 toggle temperature back to the caller
		{"READTOGGLETHREE", DoReadToggleThree},     // Print bay 3 toggle temperature back to the caller
		{"READALL_LOOP",    DoReadAllLoop},         // Read loop count and delay time. Pass all data back to the caller each time.
		{"READONE_LOOP",    DoReadOneLoop},         // Read loop count and delay time. Pass sensor 1 back to the caller each time.
		{"READTWO_LOOP",    DoReadTwoLoop},         // Read loop count and delay time. Pass sensor 2 back to the caller each time.
		{"READTHREE_LOOP",  DoReadThreeLoop},       // Read loop count and delay time. Pass sensor 3 back to the caller each time.
		{"READOUTSIDE_LOOP",DoReadOutsideLoop},     // Read loop count and delay time. Pass outside back to the caller each time.
		{"SETONE",          DoSetOne},              // Change the start temperature for sensor 1
		{"SETTWO",          DoSetTwo},              // Change the start temperature for sensor 2
		{"SETTHREE",        DoSetThree},            // Change the start temperature for sensor 3
		{"SETOUTSIDE",      DoSetOutside},          // Change the start temperature for the outside sensor.

		{"GETBAYONESTATUS",   DoGetBayOneStatus},   // Get bay one status (on or off)
		{"GETBAYTWOSTATUS",   DoGetBayTwoStatus},   // Get bay two status (on or off)
		{"GETBAYTHREESTATUS", DoGetBayThreeStatus}, // Get bay three status (on or off)

		{"SETBAYONESTATUS",   DoSetBayOneStatus},   // Set bay one status (on or off)
		{"SETBAYTWOSTATUS",   DoSetBayTwoStatus},   // Set bay two status (on or off)
		{"SETBAYTHREESTATUS", DoSetBayThreeStatus}, // Set bay three status (on or off)

		{"BAYONERUNSTATUS",   DoBayOneRunStatus},   // Find out if bay one is currently running
		{"BAYTWORUNSTATUS",   DoBayTwoRunStatus},   // Find out if bay two is currently running
		{"BAYTHREERUNSTATUS", DoBayThreeRunStatus}, // Find out if bay three is currently running

		{"SETPORT",         DoSetPort},             // Change the listen port.
		{"WRITE",           DoWrite},               // Save the current parameters to the init file.
		{"STOP",            DoStop},                // Stop all fans for a passed number of seconds
		{"START",           DoStart},               // Start the system operations loop
		{"SHUTDOWN",        DoShutdown},            // Shutdown command. Do nothing until receiving a start request.
		{"PINGPONG",        DoPingPong},            // Check status of system.
		{"RESTART",         DoRestart},             // Restart the system.
		{"TERMINATE",       DoTerminate},           // Actual termination program.
		{NULL,NULL}
};

// Simple OK message to tell the caller we got their request. Not always used.

char* pOk = "OK";

/* --------------------------------------------------------------------------
 * Communications method.
 * -------------------------------------------------------------------------- */

int TalkToFanAgent(int iSocket)
{
	int     iRc = 0;
	int     bTalk = TRUE;
	ssize_t iReadLen;
	char    bufr[512];
	char*   cp;
	NetworkCommand *pList;

	struct sockaddr_in sPartner;
	int                iPartner;

	// XXX: While loop may be removed ... check additional for loop execute.

	while( bTalk ) {
		memset((void*)bufr,(char)0,sizeof bufr);

		// Get the message from the caller

		switch( (iPartner=RecvMsgFrom(iSocket,(int*)&iReadLen,bufr,sizeof bufr,&sPartner)) ) {

		case -1: // An error occured. Discard the message and return the error.
			OutputError("TalkToFanAgent: recvfrom");
			iRc = -1;
			bTalk = FALSE;
			break;

		default: // Valid conversaion, so execute
			pList = pCmdList;
			cp    = bufr;
#if 0
			// Check the security status for the remote conversation.
			// XXX: THIS NEEDS TO BE FLESHED OUT WITH A BLOCK COMMAND ABILITY
			//  ie: A LIST OF NETWORK ADDRESSES BY CLASS TO ACCEPT COMMANDS FROM

			iRc = CheckSecurity(AF_INET,&sPartner,sizeof sPartner);
#endif

			if ( -1 != iPartner && 0 < iReadLen ) {

				// Quickly walk through the commands and execute the request

				while( pList->pCommand && strcmp(pList->pCommand,cp) ) ++pList;

				if ( pList->pCommand ) iRc = (*pList->pMethod)(iPartner,bufr);

				CloseConnection(iPartner);

				bTalk = FALSE;

			}else{

				iRc = ( -1 != iPartner ? 0 : -1);

			}

			bTalk = FALSE;

			break;
		}
	}
	return iRc;
}

/* ==========================================================================
 * METHOD FOR EXECUTING THE VARIOUS COMMAND REQUESTS.
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Read and return all four of the temperature sensors once.
 * -------------------------------------------------------------------------- */

int DoReadAllOnce(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;

		char  buf[128];
		char* cp = pBufr;

		strcpy(pBufr,"READALL_ONCE");
		cp += 1 + strlen(cp);

		sprintf(buf,"BAYONE_TEMP: %f",sParms.pData->fBayOneTemp);
		strcpy(cp,buf);
		cp += 1 + strlen(cp);

		sprintf(buf,"BAYTWO_TEMP: %f",sParms.pData->fBayTwoTemp);
		strcpy(cp,buf);
		cp += 1 + strlen(cp);

		sprintf(buf,"BAYTHREE_TEMP: %f",sParms.pData->fBayThreeTemp);
		strcpy(cp,buf);
		cp += 1 + strlen(cp);

		sprintf(buf,"OUTSIDE_TEMP: %f",sParms.pData->fOutsideTemp);
		strcpy(cp,buf);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadAllOnce: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay one temperature sensor once.
 * -------------------------------------------------------------------------- */

int DoReadOneOnce(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READONE_ONCE:");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayOneTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadOneOnce: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay two temperature sensor once.
 * -------------------------------------------------------------------------- */

int DoReadTwoOnce(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READTWO_ONCE");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayTwoTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadTwoOnce: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay three temperature sensor once.
 * -------------------------------------------------------------------------- */

int DoReadThreeOnce(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READTHREE_ONCE");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayThreeTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadThreeOnce: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the outside temperature sensor once.
 * -------------------------------------------------------------------------- */

int DoReadOutsideOnce(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READOUTSIDE_ONCE");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fOutsideTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadOutsideOnce: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the value for the bay one off/on temperature.
 * -------------------------------------------------------------------------- */

int DoReadToggleOne(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READTOGGLEONE");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayOneToggleTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadToggleOne: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the value for the bay two off/on temperature.
 * -------------------------------------------------------------------------- */

int DoReadToggleTwo(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READTOGGLETWO");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayTwoToggleTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadToggleTwo: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the value for the bay three off/on temperature.
 * -------------------------------------------------------------------------- */

int DoReadToggleThree(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int   iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"READTOGGLETHREE");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%f",sParms.pData->fBayThreeToggleTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoReadToggleThree: send");
	}
	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return all of the temperature sensors multiple times.
 *
 * XXX: The main loop should be modified with states for reading
 *      the various sensors since this method will lock things up.
 *      A check should be added to insure that the maximum delay
 *      time for this is 30 seconds.
 * -------------------------------------------------------------------------- */

int DoReadAllLoop(int iSocket,char* pBufr)
{
	char*     dp;
	uint32_t* up;
	uint32_t  ulTransId;
	int   i;
	int   iLength;
	int   bContinue;
	char* pName = pBufr;
	char  bufr[128];
	char* cp = pBufr;

	char* pCycleCount;
	int   iCycleCount;

	char* pDelay;
	int   iDelay;


	dp = pBufr;

	dp += 1 + strlen(dp);   // Step past the command name
	dp += 1 + strlen(dp);   // Step past the cycle count
	dp += 1 + strlen(dp);   // Step past the delay between reads

	up = (uint32_t*)dp;     // Convert from char* to uint32_t*
	ulTransId = ntohl(*up); // Read the transaction id

	int   iRc = SendDGramAck(iSocket,ulTransId);

	pCycleCount = pName + 1 + strlen(pName);
	sscanf(pCycleCount,"%d",&iCycleCount);

	pDelay = pCycleCount + 1 + strlen(pCycleCount);
	sscanf(pDelay,"%d",&iDelay);

	// This is a huge oversimplification which belonged as a state in the main loop
	// for distribution of the data. XXX: Make sure that the combination of the
	// delay and loop count do not exceed 30 seconds until you have time to
	// repair this stupidity. (mdb)

	bContinue = TRUE;

	for( i=0 ; i < iCycleCount && bContinue ; ++i ) {

		memset((void*)bufr,(char)0,sizeof bufr);
		cp = bufr;

		sprintf(cp,"READALL_LOOP %d : %d",i+1,iCycleCount);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayOneTemp);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayTwoTemp);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayThreeTemp);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fOutsideTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iRc = SendResponseToClient(iSocket,ulTransId,bufr,iLength);

		if ( -1 == iRc ) {
			OutputError("DoReadAllLoop: send");
			bContinue = FALSE;
		}else{
			sleep(iDelay);
		}
	}

	if ( -1 == iRc ) OutputError("DoReadAllLoop: recv");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay one temperature sensor multiple times.
 *
 * XXX: The main loop should be modified with states for reading
 *      the various sensors since this method will lock things up.
 *      A check should be added to insure that the maximum delay
 *      time for this is 30 seconds.
 * -------------------------------------------------------------------------- */

int DoReadOneLoop(int iSocket,char* pBufr)
{
	char*     dp;
	uint32_t* up;
	uint32_t  ulTransId;

	int       i;
	int       iRc;
	int       iLength;
	int       bContinue;
	char*     pName = pBufr;
	char      bufr[128];
	char*     cp = pBufr;

	char*     pCycleCount;
	int       iCycleCount;

	char*     pDelay;
	int       iDelay;

	dp = pBufr;

	dp += 1 + strlen(dp);    // Step past the command name
	dp += 1 + strlen(dp);    // Step past the cycle count
	dp += 1 + strlen(dp);    // Step past the delay between reads

	up = (uint32_t*)dp;      // Convert the char* to uint32_t*
	ulTransId = ntohl(*up);

	iRc = SendDGramAck(iSocket,ulTransId);

	pCycleCount = pName + 1 + strlen(pName);
	sscanf(pCycleCount,"%d",&iCycleCount);

	pDelay = pCycleCount + 1 + strlen(pCycleCount);
	sscanf(pDelay,"%d",&iDelay);

	bContinue = TRUE;

	for( i=0 ; i < iCycleCount && bContinue ; ++i ) {

		memset((void*)bufr,(char)0,sizeof bufr);
		cp = bufr;

		sprintf(cp,"READ_BAY_1_LOOP: %d, %d",i+1,iCycleCount);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayOneTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iRc = SendResponseToClient(iSocket,ulTransId,bufr,iLength);

		if ( -1 == iRc ) {
			OutputError("DoReadOneLoop: send");
			bContinue = FALSE;
		}else{
			sleep(iDelay);
		}
	}

	if ( -1 == iRc ) OutputError("DoReadOneLoop: recv");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay two temperature sensor multiple times.
 *
 * XXX: The main loop should be modified with states for reading
 *      the various sensors since this method will lock things up.
 *      A check should be added to insure that the maximum delay
 *      time for this is 30 seconds.
 * -------------------------------------------------------------------------- */

int DoReadTwoLoop(int iSocket,char* pBufr)
{
	char*     dp;
	uint32_t* up;
	uint32_t  ulTransId;

	int       i;
	int       iRc;
	int       iLength;
	int       bContinue;
	char*     pName = pBufr;
	char      bufr[128];
	char*     cp = pBufr;

	char*     pCycleCount;
	int       iCycleCount;

	char*     pDelay;
	int       iDelay;

	dp = pBufr;

	dp += 1 + strlen(dp);    // Step past the command name
	dp += 1 + strlen(dp);    // Step past the cycle count
	dp += 1 + strlen(dp);    // Step past the delay between reads

	up = (uint32_t*)dp;      // Convert the char* to uint32_t*
	ulTransId = ntohl(*up);

	iRc = SendDGramAck(iSocket,ulTransId);

	pCycleCount = pName + 1 + strlen(pName);
	sscanf(pCycleCount,"%d",&iCycleCount);

	pDelay = pCycleCount + 1 + strlen(pCycleCount);
	sscanf(pDelay,"%d",&iDelay);

	bContinue = TRUE;

	for( i=0 ; i < iCycleCount && bContinue ; ++i ) {

		memset((void*)bufr,(char)0,sizeof bufr);
		cp = bufr;

		sprintf(cp,"READ_BAY_2_LOOP: %d, %d",i+1,iCycleCount);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayTwoTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iRc = SendResponseToClient(iSocket,ulTransId,bufr,iLength);

		if ( -1 == iRc ) {
			OutputError("DoReadTwoLoop: send");
			bContinue = FALSE;
		}else{
			sleep(iDelay);
		}
	}

	if ( -1 == iRc ) OutputError("DoReadTwoLoop: recv");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay three temperature sensor multiple times.
 *
 * XXX: The main loop should be modified with states for reading
 *      the various sensors since this method will lock things up.
 *      A check should be added to insure that the maximum delay
 *      time for this is 30 seconds.
 * -------------------------------------------------------------------------- */

int DoReadThreeLoop(int iSocket,char* pBufr)
{
	char*     dp;
	uint32_t* up;
	uint32_t  ulTransId;

	int       i;
	int       iRc;
	int       iLength;
	int       bContinue;
	char*     pName = pBufr;
	char      bufr[128];
	char*     cp = pBufr;

	char*     pCycleCount;
	int       iCycleCount;

	char*     pDelay;
	int       iDelay;

	dp = pBufr;

	dp += 1 + strlen(dp);    // Step past the command name
	dp += 1 + strlen(dp);    // Step past the cycle count
	dp += 1 + strlen(dp);    // Step past the delay between reads

	up = (uint32_t*)dp;      // Convert the char* to uint32_t*
	ulTransId = ntohl(*up);

	iRc = SendDGramAck(iSocket,ulTransId);

	pCycleCount = pName + 1 + strlen(pName);
	sscanf(pCycleCount,"%d",&iCycleCount);

	pDelay = pCycleCount + 1 + strlen(pCycleCount);
	sscanf(pDelay,"%d",&iDelay);

	bContinue = TRUE;

	for( i=0 ; i < iCycleCount && bContinue ; ++i ) {

		memset((void*)bufr,(char)0,sizeof bufr);
		cp = bufr;

		sprintf(cp,"READ_BAY_3_LOOP: %d, %d",i+1,iCycleCount);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fBayThreeTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iRc = SendResponseToClient(iSocket,ulTransId,bufr,iLength);

		if ( -1 == iRc ) {
			OutputError("DoReadThreeLoop: send");
			bContinue = FALSE;
		}else{
			sleep(iDelay);
		}
	}

	if ( -1 == iRc ) OutputError("DoReadThreeLoop: recv");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay one temperature sensor multiple times.
 *
 * XXX: The main loop should be modified with states for reading
 *      the various sensors since this method will lock things up.
 *      A check should be added to insure that the maximum delay
 *      time for this is 30 seconds.
 * -------------------------------------------------------------------------- */

int DoReadOutsideLoop(int iSocket,char* pBufr)
{
	char*     dp;
	uint32_t* up;
	uint32_t  ulTransId;

	int       i;
	int       iRc;
	int       iLength;
	int       bContinue;
	char*     pName = pBufr;
	char      bufr[128];
	char*     cp = pBufr;

	char*     pCycleCount;
	int       iCycleCount;

	char*     pDelay;
	int       iDelay;

	dp = pBufr;

	dp += 1 + strlen(dp);    // Step past the command name
	dp += 1 + strlen(dp);    // Step past the cycle count
	dp += 1 + strlen(dp);    // Step past the delay between reads

	up = (uint32_t*)dp;      // Convert the char* to uint32_t*
	ulTransId = ntohl(*up);

	iRc = SendDGramAck(iSocket,ulTransId);

	pCycleCount = pName + 1 + strlen(pName);
	sscanf(pCycleCount,"%d",&iCycleCount);

	pDelay = pCycleCount + 1 + strlen(pCycleCount);
	sscanf(pDelay,"%d",&iDelay);

	bContinue = TRUE;

	for( i=0 ; i < iCycleCount && bContinue ; ++i ) {

		memset((void*)bufr,(char)0,sizeof bufr);
		cp = bufr;

		sprintf(cp,"READ_OUTSIDE_LOOP: %d, %d",i+1,iCycleCount);
		cp += 1 + strlen(cp);

		sprintf(cp,"%f",sParms.pData->fOutsideTemp);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iRc = SendResponseToClient(iSocket,ulTransId,bufr,iLength);

		if ( -1 == iRc ) {
			OutputError("DoReadOutsideLoop: send");
			bContinue = FALSE;
		}else{
			sleep(iDelay);
		}
	}

	if ( -1 == iRc ) OutputError("DoReadOutsideLoop: recv");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Set the off/on temperature for the fan in bay 1.
 * -------------------------------------------------------------------------- */

int DoSetOne(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	float     fBayOneToggleTemp;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%f",&fBayOneToggleTemp);

	sParms.pData->fBayOneToggleTemp = fBayOneToggleTemp;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Set the off/on temperature for the fan in bay 2.
 * -------------------------------------------------------------------------- */

int DoSetTwo(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	float     fBayTwoToggleTemp;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%f",&fBayTwoToggleTemp);

	sParms.pData->fBayTwoToggleTemp = fBayTwoToggleTemp;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Set the off/on temperature for the fan in bay 3.
 * -------------------------------------------------------------------------- */

int DoSetThree(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	float     fBayThreeToggleTemp;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%f",&fBayThreeToggleTemp);

	sParms.pData->fBayThreeToggleTemp = fBayThreeToggleTemp;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Set the off/on temperature for the fan system.
 *
 * When the outside thermometer reads below this temperature all fans are
 * shut off and the system is effectively disabled.
 * -------------------------------------------------------------------------- */

int DoSetOutside(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	float     fOutside;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%f",&fOutside);

	sParms.pData->fOutsideTemp = fOutside;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Read and return the bay one operation status.
 * -------------------------------------------------------------------------- */

int DoGetBayOneStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"GETBAYONESTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayOneStatus);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DGetBayOneStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay two operation status.
 * -------------------------------------------------------------------------- */

int DoGetBayTwoStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"GETBAYTWOSTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayTwoStatus);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DGetBayTwoStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Read and return the bay three operation status.
 * -------------------------------------------------------------------------- */

int DoGetBayThreeStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"GETBAYTHREESTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayThreeStatus);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DGetBayThreeStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Enable or disable bay one
 * -------------------------------------------------------------------------- */

int DoSetBayOneStatus(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	int       bBayOneStatus;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%d",&bBayOneStatus);

	sParms.pData->bBayOneStatus = bBayOneStatus;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Enable or disable bay two
 * -------------------------------------------------------------------------- */

int DoSetBayTwoStatus(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	int       bBayTwoStatus;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%d",&bBayTwoStatus);

	sParms.pData->bBayTwoStatus = bBayTwoStatus;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Enable or disable bay three
 * -------------------------------------------------------------------------- */

int DoSetBayThreeStatus(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	int       bBayThreeStatus;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%d",&bBayThreeStatus);

	sParms.pData->bBayThreeStatus = bBayThreeStatus;

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Is bay one currently running.
 * -------------------------------------------------------------------------- */

int DoBayOneRunStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"BAYONERUNSTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayOneRunning);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoBayOneRunStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Is bay two currently running.
 * -------------------------------------------------------------------------- */

int DoBayTwoRunStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"BAYTWORUNSTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayTwoRunning);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoBayTwoRunStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Is bay three currently running.
 * -------------------------------------------------------------------------- */

int DoBayThreeRunStatus(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int   iLength;
		char* cp;

		strcpy(pBufr,"BAYTHREERUNSTATUS");
		cp = pBufr + 1 + strlen(pBufr);

		sprintf(cp,"%d",sParms.pData->bBayThreeRunning);
		cp += 1 + strlen(cp);

		iLength = (int)(cp - pBufr);

		iRc = SendResponseToClient(iSocket,ulTransId,pBufr,iLength);

		if ( -1 == iRc ) OutputError("DoBayThreeRunStatus: send");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Change the communications port that the system is currently using.
 * -------------------------------------------------------------------------- */

int DoSetPort(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     pName  = pBufr;
	char*     pValue = pName + 1 + strlen(pName);
	int       iPort;

	up = (uint32_t*)(pValue + 1 + strlen(pValue));
	ulTransId = ntohl(*up);

	sscanf(pValue,"%d",&iPort);

	sParms.pData->iPort = iPort;

	// XXX: Should set the operation state to Reset or Restart!

	return SendDGramAck(iSocket,ulTransId);
}

/* --------------------------------------------------------------------------
 * Stop the system for a given period of time.
 *
 * This should shutdown all fans for a short period of time.
 * -------------------------------------------------------------------------- */

int DoStop(int iSocket,char* pBufr)
{
	uint32_t* up;
	uint32_t  ulTransId;

	char*     cp = pBufr + 1 + strlen(pBufr);

	sscanf(cp,"%d",&iStopLoop); cp += 1 + strlen(cp);
	sscanf(cp,"%d",&iStopTime); cp += 1 + strlen(cp);

	up = (uint32_t*)cp;
	ulTransId = ntohl(*up);

	iStopCount = 0;

	OpState = Stopped;

	return SendDGramAck(iSocket,ulTransId);
}

int DoStart(int iSocket,char* pBufr)
{
	if ( OpState != Stopped ) OpState = Running;

	return 0;
}

/* --------------------------------------------------------------------------
 * Write the current parameters to the initialization file.
 * -------------------------------------------------------------------------- */

int DoWrite(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	FILE*     fout   = fopen(pDefaultData,"w");
	pOpsParms pParms = sParms.pData;

	if ( NULL != fout ) {
		fprintf(fout,
				"StopImage: %f\n"
				"BayOneTemp: %f\n"
				"BayTwoTemp: %f\n"
				"BayThreeTemp: %f\n"
				"Port: %d",
				pParms->fOutsideShutdownTemp,
				pParms->fBayOneToggleTemp,
				pParms->fBayTwoToggleTemp,
				pParms->fBayThreeToggleTemp,
				pParms->iPort);
		fclose(fout);
	}else{
		OutputError("Do0Write: fopen");
	}

	return SendDGramAck(iSocket,ulTransId);
}

/* -----------------------------------------------------------------------------
 * Send back the signal to tell the caller that the system is alive.
 * ----------------------------------------------------------------------------- */

int DoShutdown(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	OpState = Shutdown;

	return SendDGramAck(iSocket,ulTransId);
}

/* -----------------------------------------------------------------------------
 * Effectively sleep waiting for a restart command.
 * ----------------------------------------------------------------------------- */

static char* pRestart = "RESTART";

void WaitForRestart(int iSocket)
{
	int  iRc;
	int  iSock;
	int  iReadLen;
	int  bDoMore = TRUE;
	char pBufr[256];
	int  iBufLen = sizeof(pBufr);

	uint32_t* up;
	uint32_t  ulTransId;

	struct sockaddr_in sin;

	while( bDoMore ) {
		iRc = LoopForDGram(iSocket,5);
		if ( -1 == iRc ) {
			bDoMore = FALSE;
		}else{
			memset((void*)pBufr,(char)0,iBufLen);

			iSock = RecvMsgFrom(iSocket,&iReadLen,pBufr,iBufLen,&sin);

			if ( -1 != iSock && !strcmp(pBufr,pRestart) ) {
				up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
				ulTransId = ntohl(*up);

				iRc = SendDGramAck(iSock,ulTransId);

				if ( -1 != iRc ) {
					OpState = Restart;
					bDoMore = FALSE;
					CloseConnection(iSock);
				}
			}else if ( -1 != iSock ) {
				CloseConnection(iSock);
			}
		}
	}
}

/* -----------------------------------------------------------------------------
 * Send back the signal to tell the caller that the system is alive.
 * ----------------------------------------------------------------------------- */

int DoPingPong(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  uiTransId = ntohl(*up);

	char* pResponse = "DINGDONG";

	int iRc = SendDGramAck(iSocket,uiTransId);

	if ( -1 != iRc ) {
		iRc = SendResponseToClient(iSocket,uiTransId,pResponse,1+strlen(pResponse));
		if ( -1 == iRc ) OutputError("DoPingPong: send");
	}
	return iRc;
}

/* -----------------------------------------------------------------------------
 * XXX: Complete this guy
 * ----------------------------------------------------------------------------- */

int DoRestart(int iSocket,char* pBufr)
{
	OpState = Restart;

	return 0;
}

int DoTerminate(int iSocket,char* pBufr)
{
	uint32_t* up = (uint32_t*)(pBufr + 1 + strlen(pBufr));
	uint32_t  ulTransId = ntohl(*up);

	char* pResponse = "Terminate";

	int iRc = SendDGramAck(iSocket,ulTransId);

	if ( -1 != iRc ) {
		int iLength = 1 + strlen(pResponse);
		iRc = SendResponseToClient(iSocket,ulTransId,pResponse,iLength);
		if ( -1 == iRc ) OutputError("DoTerminate: send");
	}

	OpState = Terminate;

	return iRc;
}

/* ==========================================================================
 * PRIMARY SYSTEM OPERATIONS METHODS.
 * ========================================================================== */

/* -----------------------------------------------------------------------------
 * Initialization method
 * ----------------------------------------------------------------------------- */

OpsParms sDefs = {
		90.0f,   // fOutsideShutdownTemp
		100.0f,  // fBayOneToggleTemp
		100.0f,  // fBayTwoToggleTemp
		100.0f,  // fBayThreeToggleTemp
		0.0f,    // fBayOneTemp
		0.0f,    // fBayTwoTemp
		0.0f,    // fBayThreeTemp
		30.0f,   // fOutsideTemp
		3.0f,    // fBayOneDelta
		3.0f,    // fBayTwoDelta
		3.0f,    // fBayThreeDelta
		1,       // bBayOneStatus    (active)
		1,       // bBayTwoStatus    (active)
		1,       // bBayThreeStatus  (active)
		0,       // bBayOneRunning   (off)
		0,       // bBayTwoRunning   (off)
		0,       // bBayThreeRunning (off)
		2018 };

#define DEFAULT_STR_MIN_LENGTH 5

int Init(pInitParms pParms,const char* pDefaultsFile)
{
	int      iRc = 0;
	OpsParms sDefaults;

	// Make sure that pParms exists to pass the location of the data segment back to the caller

	if ( NULL == pParms ) return -1;

	// Start by copying the program backup default values into the defaults structure

	memcpy((void*)&sDefaults,(void*)&sDefs,sizeof sDefaults);

	// Open the defaults initialization file. Read and adjust the values.

	if ( NULL != pDefaultsFile ) {

		char  pBaseBufr[1024];
		FILE* pFile = fopen(pDefaultsFile,"r");

		if ( NULL != pFile ) {

			char* pDataString;

			while( (pDataString=fgets(pBaseBufr,1024,pFile)) ) {

				if ( strlen(pDataString) > DEFAULT_STR_MIN_LENGTH ) {

					char* pName = pBaseBufr;
					char* pValue;

					while ( *pName == ' ' ) ++pName;

					pValue = strpbrk(pName,":");
					*pValue = (char)0;
					++pValue;

					while( *pValue == ' ' ) ++pValue;

					if ( strstr(pName,"StopImage") ) {
						sscanf(pValue,"%f",&sDefaults.fOutsideShutdownTemp);
					}else if ( strstr(pName,"BayOneTemp") ) {
						sscanf(pValue,"%f",&sDefaults.fBayOneToggleTemp);
					}else if ( strstr(pName,"BayTwoTemp") ) {
						sscanf(pValue,"%f",&sDefaults.fBayTwoToggleTemp);
					}else if ( strstr(pName,"BayThreeTemp") ) {
						sscanf(pValue,"%f",&sDefaults.fBayThreeToggleTemp);
					}else if ( strstr(pName,"Port") ) {
						sscanf(pValue,"%d",&sDefaults.iPort);
					}
				}
			}
			fclose(pFile);
		}
	}

	// Get the semaphore and set the value to 1 for blocking.

	memset((void*)pParms,(char)0,sizeof*pParms);
	pParms->iSemId = GetSemaphore(1,0x23);

	if ( -1 != pParms->iSemId ) {

		// Get the shared memory segment

		pParms->iShmId = GetSharedMemory((char**)&pParms->pData,sizeof*pParms,0x32);
		if ( -1 != pParms->iShmId && (void*)-1 != pParms->pData ) {

			// Get the socket to listen on

			pParms->iSocket = GetDGramListenSocket(sDefaults.iPort);

			if ( -1 != pParms->iSocket ) {

				// The initialization succeeded so initialize the shared memory with operating values

				memcpy((void*)pParms->pData,(void*)&sDefaults,sizeof sDefaults);
			}
		}
	}

	// Cleanup if there was an error

	if ( (void*)-1 == pParms->pData   ||
		        -1 == pParms->iShmId  ||
		        -1 == pParms->iSemId  ||
		        -1 == pParms->iSocket ) {
		if ( -1 != pParms->iSocket ) CloseConnection(pParms->iSocket);
		if ( -1 != pParms->iShmId  ) DelSharedMemory((char*)pParms->pData,pParms->iShmId);
		if ( -1 != pParms->iSemId  ) DelSemaphore(pParms->iSemId);
		iRc = -1;
	}

	// Completed, notify the caller of our status

	return iRc;
}

/* -----------------------------------------------------------------------------
 * Clean up the allocated system resources.
 * ----------------------------------------------------------------------------- */

void TerminationCleanup(pInitParms pParms)
{
	CloseConnection(pParms->iSocket);
	DelSharedMemory((char*)pParms->pData,pParms->iShmId);
	DelSemaphore(pParms->iSemId);
}
