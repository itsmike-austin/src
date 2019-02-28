#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "DGramSocket.h"
#include "Semaphore.h"
#include "OutputError.h"

char* pPong              = "PINGPONG";
char* pReadAllOnce       = "READALL_ONCE";
char* pReadOneOnce       = "READONE_ONCE";
char* pReadTwoOnce       = "READTWO_ONCE";
char* pReadThreeOnce     = "READTHREE_ONCE";
char* pReadOutsideOnce   = "READOUTSIDE_ONCE";
char* pReadToggleOne     = "READTOGGLEONE";
char* pReadToggleTwo     = "READTOGGLETWO";
char* pReadToggleThree   = "READTOGGLETHREE";
char* pReadAllLoop       = "READALL_LOOP";
char* pReadOneLoop       = "READONE_LOOP";
char* pReadTwoLoop       = "READTWO_LOOP";
char* pReadThreeLoop     = "READTHREE_LOOP";
char* pReadOutsideLoop   = "READOUTSIDE_LOOP";
char* pSetOneToggle      = "SETONE";
char* pSetTwoToggle      = "SETTWO";
char* pSetThreeToggle    = "SETTHREE";
char* pSetOutsideToggle  = "SETOUTSIDE";

char* pGetBayOneStatus   = "GETBAYONESTATUS";
char* pGetBayTwoStatus   = "GETBAYTWOSTATUS";
char* pGetBayThreeStatus = "GETBAYTHREESTATUS";

char* pSetBayOneStatus   = "SETBAYONESTATUS";
char* pSetBayTwoStatus   = "SETBAYTWOSTATUS";
char* pSetBayThreeStatus = "SETBAYTHREESTATUS";

char* pBayOneRunStatus   = "BAYONERUNSTATUS";
char* pBayTwoRunStatus   = "BAYTWORUNSTATUS";
char* pBayThreeRunStatus = "BAYTHREERUNSTATUS";

char* pSetPort           = "SETPORT";
char* pWrite             = "WRITE";
char* pStop              = "STOP";
char* pShutdown          = "SHUTDOWN";
char* pStart             = "START";
char* pRestart           = "RESTART";
char* pTerm              = "TERMINATE";

char* pOk = "OK";

int main(int argc,char* argv[])
{
	int iRc = 0;
	int iSocket;

	char bufr[256];

	char* pDestHost = "localhost";

	struct sockaddr_in sHostAddr;
	struct sockaddr_in sDestAddr;
	int                iAddrSize = sizeof sDestAddr;

	unsigned int uiTransSeed;
	int          iTransId;

	int iSemId = AccessSemaphore(1,0x23);

	if ( -1 == iSemId ) {
		OutputError("AccessSemaphore");
		return -1;
	}

	iRc = SemRelease(iSemId,0);

	if ( -1 == iRc ) {
		OutputError("SemRelease");
		return -1;
	}

	// Get the host address in AF_INET format.

	{
		char hostbuf[NI_MAXHOST];
		if ( -1 != gethostname(hostbuf,NI_MAXHOST) ) {
			iRc = GetHostAddress(AF_INET,hostbuf,(struct sockaddr*)&sHostAddr,iAddrSize,0);
			if ( -1 == iRc ) {
				perror("GetHostAddress failed: ");
				return -1;
			}
		}else{
			perror("gethostname failed: ");
			return -1;
		}
	}

	iRc = GetHostAddress(AF_INET,pDestHost,(struct sockaddr*)&sDestAddr,iAddrSize,2018);

	if ( -1 == iRc ) {
		fprintf(stderr,"GetHostAddress failed!"); fflush(stderr);
		return iRc;
	}

	// Get the seed for all transactions in this session.

	uiTransSeed = SeedDGramTransId();

	// Get a transaction id for the ping pong request.

	iTransId = GetTransId(&uiTransSeed);

	// Do the ping pong transaction.

	if ( -1 != (iSocket=SendTxtCommandTo(pPong,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			iRc = SendDGramEOT(iSocket,iTransId);
			fprintf(stdout,"Transaction was: %s\n\n",bufr);fflush(stdout);
		}else{
			fprintf(stderr,"%s: Failed!\n\n",pPong);
		}

		CloseConnection(iSocket);
	}else{
		fprintf(stderr,"Send PingPong Command Failed!");fflush(stderr);
		return -1;
	}

	// Do the READALL_ONCE transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pReadAllOnce,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			char* cp       = bufr;
			char* bayone   = 1 + cp       + strlen(cp);
			char* baytwo   = 1 + bayone   + strlen(bayone);
			char* baythree = 1 + baytwo   + strlen(baytwo);
			char* outside  = 1 + baythree + strlen(baythree);

			fprintf(stdout,"%s\n  Bay 1: %s\n  Bay 2: %s\n  Bay 3:%s\n  Out 1: %s\n\n",cp,bayone,baytwo,baythree,outside);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read All Once Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the READONE_ONCE transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pReadOneOnce,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* bayone = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay 1: %s\n\n",cp,bayone);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read One Once Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the READTWO_ONCE transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pReadTwoOnce,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baytwo = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay 2: %s\n\n",cp,baytwo);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Two Once Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the READTHREE_ONCE transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pReadThreeOnce,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baythree = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay 3: %s\n\n",cp,baythree);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Three Once Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the READOUTSIDE_ONCE transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pReadOutsideOnce,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* bayout = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Outside: %s\n\n",cp,bayout);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Outside Once Failed\n");fflush(stdout);
		return iRc;
	}

	// Read Bay 1 and Toggle Off/On Temperature

	if ( -1 != (iSocket=SendTxtCommandTo(pReadToggleOne,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			char* cp = bufr;
			char* bayone = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n On-Off: %s\n\n",cp,bayone);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Toggle One Failed\n");fflush(stdout);
		return iRc;
	}

	// Read Bay 2 and Toggle Off/On Temperature

	if ( -1 != (iSocket=SendTxtCommandTo(pReadToggleTwo,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			char* cp = bufr;
			char* baytwo = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n On-Off: %s\n\n",cp,baytwo);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Toggle Two Failed\n");fflush(stdout);
		return iRc;
	}

	// Read Bay 3 and Toggle Off/On Temperature

	if ( -1 != (iSocket=SendTxtCommandTo(pReadToggleThree,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			char* cp = bufr;
			char* baythree = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n On-Off: %s\n\n",cp,baythree);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Read Toggle Three Failed\n");fflush(stdout);
		return iRc;
	}

	// Read All Temperature Sensors in a Loop

	{
		int   i;
		char* cp = bufr;
		int   iLength;
		int   bContinue = 1;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pReadAllLoop); cp += 1 + strlen(cp); // Transaction
		sprintf(cp,"%d",5);      cp += 1 + strlen(cp); // Cycle count
		sprintf(cp,"%d",1);      cp += 1 + strlen(cp); // Delay between reads

		// Calculate the length of the output message

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
				                    AF_INET,
				                    (unsigned int*)&iTransId,
				                    (struct sockaddr*)&sDestAddr,
				                    (struct sockaddr*)&sHostAddr,
				                    &iAddrSize);

		if( -1 == iRc ) return -1;

		for( i=0 ; i < 5 && bContinue ; ++i ) {
			memset((void*)bufr,(char)0,sizeof bufr);

			// XXX: If the delay time is greater than about 1.75 seconds, you will smash
			//      into the hard coded 2 second delay here and fall out with an invalid
			//      transaction. Rework required.

			iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				return iRc;
			}else{
				char* cp    = bufr;
				char* pBay1 = cp    + 1 + strlen(cp);
				char* pBay2 = pBay1 + 1 + strlen(pBay1);
				char* pBay3 = pBay2 + 1 + strlen(pBay2);
				char* pOut  = pBay3 + 1 + strlen(pBay3);

				iRc = SendDGramEOT(iSocket,iTransId);

				// XXX: Consider sending the loop number back to the caller
				//      This is not a requirement until DGRAM operations are established

				fprintf(stdout,"%s: (%d)\n  Bay1: %s\n  Bay2: %s\n  Bay3: %s\n  Out: %s\n\n",
						cp,i,pBay1,pBay2,pBay3,pOut);
				fflush(stdout);

				if (  -1 == iRc ) {
					CloseConnection(iSocket);
					bContinue = 0;
				}

				// XXX: Consider sending an OK back to the server to acknowlege the loop
				//      This is not really a priority until DGRAM operations are established.
			}
		}

		// Tell the server we're done. All data has been received so ok to shutdown connection
		// XXX: This part of the protocol can go if using datagram transactions.

		CloseConnection(iSocket);
	}

	// Read Bay One Temperature Sensor in a Loop

	{
		int   i;
		char* cp = bufr;
		int   iLength;
		int   bContinue = 1;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pReadOneLoop); cp += 1 + strlen(cp);
		sprintf(cp,"%d",5);      cp += 1 + strlen(cp);
		sprintf(cp,"%d",1);      cp += 1 + strlen(cp);

		// Calculate the length of the output message

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if( -1 == iRc ) return -1;

		for( i=0 ; i < 5 && bContinue ; ++i ) {
			memset((void*)bufr,(char)0,sizeof bufr);

			iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				return iRc;
			}
			char* cp = bufr;
			char* pBay1 = cp + 1 + strlen(cp);

			iRc = SendDGramEOT(iSocket,iTransId);

			fprintf(stdout,"%s: (%d)\n  Bay1: %s\n\n", cp,i,pBay1);
			fflush(stdout);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				bContinue = 0;
			}
		}
		CloseConnection(iSocket);
	}

	// Read Bay Two Temperature Sensor in a Loop

	{
		int   i;
		char* cp = bufr;
		int   iLength;
		int   bContinue = 1;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pReadTwoLoop); cp += 1 + strlen(cp);
		sprintf(cp,"%d",5);      cp += 1 + strlen(cp);
		sprintf(cp,"%d",1);      cp += 1 + strlen(cp);

		// Calculate the length of the output message

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if( -1 == iRc ) return -1;

		for( i=0 ; i < 5 && bContinue ; ++i ) {
			memset((void*)bufr,(char)0,sizeof bufr);

			iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				return iRc;
			}
			char* cp = bufr;
			char* pBay2 = cp + 1 + strlen(cp);

			iRc = SendDGramEOT(iSocket,iTransId);

			fprintf(stdout,"%s: (%d)\n  Bay2: %s\n\n", cp,i,pBay2);
			fflush(stdout);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				bContinue = 0;
			}
		}
		CloseConnection(iSocket);
	}

	// Read Bay Three Temperature Sensor in a Loop

	{
		int   i;
		char* cp = bufr;
		int   iLength;
		int   bContinue = 1;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pReadThreeLoop); cp += 1 + strlen(cp);
		sprintf(cp,"%d",5);        cp += 1 + strlen(cp);
		sprintf(cp,"%d",1);        cp += 1 + strlen(cp);

		// Calculate the length of the output message

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if( -1 == iRc ) return -1;

		for( i=0 ; i < 5 && bContinue ; ++i ) {
			memset((void*)bufr,(char)0,sizeof bufr);

			iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				return iRc;
			}
			char* cp = bufr;
			char* pBay3 = cp + 1 + strlen(cp);

			iRc = SendDGramEOT(iSocket,iTransId);

			fprintf(stdout,"%s: (%d)\n  Bay3: %s\n\n", cp,i,pBay3);
			fflush(stdout);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				bContinue = 0;
			}
		}
		CloseConnection(iSocket);
	}

	// Read Outside Temperature Sensor in a Loop

	{
		int   i;
		char* cp = bufr;
		int   iLength;
		int   bContinue = 1;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pReadOutsideLoop); cp += 1 + strlen(cp);
		sprintf(cp,"%d",5);          cp += 1 + strlen(cp);
		sprintf(cp,"%d",1);          cp += 1 + strlen(cp);

		// Calculate the length of the output message

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if( -1 == iRc ) return -1;

		for( i=0 ; i < 5 && bContinue ; ++i ) {
			memset((void*)bufr,(char)0,sizeof bufr);

			iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				return iRc;
			}
			char* cp = bufr;
			char* pOutside = cp + 1 + strlen(cp);

			iRc = SendDGramEOT(iSocket,iTransId);

			fprintf(stdout,"%s: (%d)\n  Outside: %s\n\n", cp,i,pOutside);
			fflush(stdout);

			if ( -1 == iRc ) {
				CloseConnection(iSocket);
				bContinue = 0;
			}
		}
		CloseConnection(iSocket);
	}

	// Set the bay one toggle temp

	{
		int   iLength;
		float fTemp = 95.75;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetOneToggle); cp += 1 + strlen(cp);
		sprintf(cp,"%f",fTemp);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Sent new bay1 toggle temperature\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay two toggle temp

	{
		int   iLength;
		float fTemp = 96.75;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetTwoToggle); cp += 1 + strlen(cp);
		sprintf(cp,"%f",fTemp);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Sent new bay2 toggle temperature\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay three toggle temp

	{
		int   iLength;
		float fTemp = 97.75;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetThreeToggle); cp += 1 + strlen(cp);
		sprintf(cp,"%f",fTemp);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Sent new bay3 toggle temperature\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}


	// Set the outside toggle temp

	{
		int   iLength;
		float fTemp = 98.75;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetOutsideToggle); cp += 1 + strlen(cp);
		sprintf(cp,"%f",fTemp);       cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Sent new outside toggle temperature\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Do the GETBAYONESTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayOneStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay One Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay One Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTWOSTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayTwoStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Two Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay Two Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTHREESTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayThreeStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Three Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay Three Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Set the bay one operation status

	{
		int   iLength;
		int   bStatus = 0;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayOneStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 1 operating status off\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay two operation status

	{
		int   iLength;
		int   bStatus = 0;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayTwoStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 2 operating status off\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay three operation status

	{
		int   iLength;
		int   bStatus = 0;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayThreeStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 3 operating status off\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Do the GETBAYONESTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayOneStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay One Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay One Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTWOSTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayTwoStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Two Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay Two Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTHREESTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pGetBayThreeStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Three Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Get Bay Three Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Set the bay one operation status

	{
		int   iLength;
		int   bStatus = 1;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayOneStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 1 operating status on\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay two operation status

	{
		int   iLength;
		int   bStatus = 1;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayTwoStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 2 operating status on\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Set the bay three operation status

	{
		int   iLength;
		int   bStatus = 1;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetBayThreeStatus); cp += 1 + strlen(cp);
		sprintf(cp,"%d",bStatus);   cp += 1 + strlen(cp);

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Set bay 3 operating status on\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}

	// Do the BAYONERUNSTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pBayOneRunStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay One Run Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Bay One Run Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTWOSTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pBayTwoRunStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Two Run Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Bay Two Run Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Do the GETBAYTHREESTATUS transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pBayThreeRunStatus,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {

		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 == iRc ) {
			return iRc;
		}else{
			char* cp = bufr;
			char* baystat = 1 + cp + strlen(cp);

			fprintf(stdout,"%s\n  Bay Three Run Status: %s\n\n",cp,baystat);
			fflush(stdout);

			iRc = SendDGramEOT(iSocket,iTransId);

			CloseConnection(iSocket);
		}
	}

	if ( -1 == iRc ) {
		fprintf(stdout,"Bay Three Run Status Failed\n");fflush(stdout);
		return iRc;
	}

	// Set the port. XXX: SET PORT SHOULD FORCE A RESET FOR THE NEW PORT
	// SO ADDITIONAL CHECKING IS REQUIRED HERE.

	{
		int   iLength;
		int   iPort = 2018;
		char* cp = bufr;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(cp,pSetPort);    cp += 1 + strlen(cp);
		sprintf(cp,"%d",iPort); cp += 1 + strlen(cp);
		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		if ( -1 == iRc ) return iRc;

		fprintf(stdout,"Requested change to new port");
		fflush(stdout);

		CloseConnection(iSocket);
	}

#if defined(_WITH_STOP_TRANSACTION)

	// Put the server into stop mode. This means discontinue transactions
	// in a delay timer loop until the stop execution request expires
	// XXX: This one needs significant additional work since it should
	// actually be executed in the main loop and discard all inbound
	// transactions until the time expires (remove loop timer)

	{
		int iLength;
		char* cp;

		memset((void*)bufr,(char)0,sizeof bufr);

		strcpy(bufr,pStop); cp = bufr + 1 + strlen(bufr);
		sprintf(cp,"%d",5); cp += 1 + strlen(cp);          // 5 times around the loop
		sprintf(cp,"%d",1); cp += 1 + strlen(cp);          // 1 second each time.

		iLength = (int)(cp - bufr);

		iSocket = SendDataCommandTo(bufr,
				                    iLength,
									AF_INET,
									(unsigned int*)&iTransId,
									(struct sockaddr*)&sDestAddr,
									(struct sockaddr*)&sHostAddr,
									&iAddrSize);

		fprintf(stdout,"Requested 5 second stop\n");
		fflush(stdout);

		CloseConnection(iSocket);
	}
#endif

	// Write the defaults to the default file

	if ( -1 != (iSocket=SendTxtCommandTo(pWrite,
			                             AF_INET,
			                             (unsigned int*)&iTransId,
										 (struct sockaddr*)&sDestAddr,
										 (struct sockaddr*)&sHostAddr,
										 &iAddrSize)) ) {
		if ( -1 != iSocket ) {
			fprintf(stdout,"Successfully sent write command\n");
			fflush(stdout);
		}else{
			fprintf(stderr,"Send Write Command Failed\n\n");fflush(stdout);
			return -1;
		}

		CloseConnection(iSocket);
	}

	// Do a shutdown transaction.

	if ( -1 != (iSocket=SendTxtCommandTo(pShutdown,
			                             AF_INET,
										 (unsigned int*)&iTransId,
										 (struct sockaddr*)&sDestAddr,
										 (struct sockaddr*)&sHostAddr,
										 &iAddrSize)) ) {
		if ( -1 != iSocket ) {
			fprintf(stdout,"Successfully sent shutdown command\n\n");
			fflush(stdout);
		}else{
			fprintf(stderr,"Send Shutdown Command failed!\n\n");
			fflush(stderr);
			return -1;
		}
		CloseConnection(iSocket);
	}

	// And a restart transaction.

	if ( -1 != (iSocket=SendTxtCommandTo(pRestart,
			                             AF_INET,
										 (unsigned int*)&iTransId,
										 (struct sockaddr*)&sDestAddr,
										 (struct sockaddr*)&sHostAddr,
										 &iAddrSize)) ) {
		if ( -1 != iSocket ) {
			fprintf(stdout,"Sucessfully restarted server\n\n");
			fflush(stdout);
		}else{
			fprintf(stderr,"Send Restart Command Failed\n\n");
			fflush(stderr);
			return -1;
		}
		CloseConnection(iSocket);
	}

	sleep(1);

	// Do the terminate transaction

	if ( -1 != (iSocket=SendTxtCommandTo(pTerm,
			                            AF_INET,
			                            (unsigned int*)&iTransId,
			                            (struct sockaddr*)&sDestAddr,
			                            (struct sockaddr*)&sHostAddr,
			                            &iAddrSize)) ) {
		memset((void*)bufr,(char)0,sizeof bufr);

		iRc = RecvResponseFrom(iSocket,bufr,sizeof bufr,iTransId);

		if ( -1 != iRc ) {
			iRc = SendDGramEOT(iSocket,iTransId);
			fprintf(stdout,"Transaction was: %s\n\n",bufr);fflush(stdout);
		}else{
			fprintf(stderr,"%s: Failed\n\n",pTerm);fflush(stderr);
		}

		CloseConnection(iSocket);
	}else{
		fprintf(stderr,"Send Terminate Command Failed!\n");fflush(stderr);
		return -1;
	}

	return iRc;
}
