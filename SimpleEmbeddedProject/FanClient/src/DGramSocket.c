/* ==========================================================================
 * DGramSocket:
 *    The stream socket module consists of five primary methods:
 *        ThisHostToIp:             Get the 32 bit IPV4 address of this box
 *        GetDGramListenSocket:     Allocate a datagram socket
 *        LoopForDGram:             Wait for a caller
 *        GetDGramCommand:          Return the passed request
 *        SendTxtMsgToDGram:        Send a simple txt message to a socket
 *        SendDataToDGram:          Send data to a socket
 *        RecvDGramMsg:             Get a message from a socket
 *        DGramClose:               Shutdown and close the socket
 *
 *        All methods log errors to the syslog file for consistency
 *        and convenience
 *
 * --------------------------------------------------------------------------
 *  TBD: Consider adding a passed method to be called after execution
 *       of each pass through the loop (an idle method) for LoopForDGram.
 * --------------------------------------------------------------------------
 * (c) 1999 itsinc (mdb)
 * ========================================================================== */

#include "DGramSocket.h"

static char* pOk  = "OK";
static char* pAck = "ACK";
static char* pEOT = "EOT";

#define OK_LENGTH  3
#define ACK_LENGTH 4
#define EOT_LENGTH 4

#ifndef COMMAND_RESPONSE_LENGTH
#define COMMAND_RESPONSE_LENGTH 256
#endif

/* --------------------------------------------------------------------------
 * Get the IPV4 network order long buffer and return it to the caller.
 * -------------------------------------------------------------------------- */

unsigned long ThisIFaceToIp(char* pIFaceName)
{
	unsigned long iRc = -1;

	struct ifaddrs *ifaddr, *ifa;

	struct sockaddr_in* pSockAddr;

	int family;

	if ( -1 != getifaddrs(&ifaddr) ) {

		for( ifa = ifaddr ; ifa != NULL ; ifa = ifa->ifa_next ) {

			if ( ifa->ifa_addr == NULL ) continue;

			family = ifa->ifa_addr->sa_family;

			if( family == AF_INET && !strcmp(pIFaceName,ifa->ifa_name)) {
				pSockAddr = (struct sockaddr_in*)ifa->ifa_addr;

				iRc = pSockAddr->sin_addr.s_addr;
			}
			freeifaddrs(ifaddr);
		}
	}else{

		OutputError("ThisIFaceToIp: getifaddrs");

	}

	return iRc;
}


/* --------------------------------------------------------------------------
 * Get the IPV4 network order long buffer and return it to the caller.
 * XXX: This should be changed to getifaddrs
 * -------------------------------------------------------------------------- */

unsigned long ThisHostToIp()
{
  char hostname[256];

  unsigned long hostIpAddr = (unsigned long)-1;

  struct addrinfo hints, *servinfo, *pAddrInfo;
  struct sockaddr_in *pSockAddr;

  // Get the hostname for this box

  if ( -1 != gethostname(hostname,sizeof hostname) ) {

    // Setup the hints for acquiring the address info

    memset((void*)&hints,(char)0,sizeof hints);
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    // Get the address info

    if ( 0 == getaddrinfo(hostname,"echo",&hints,&servinfo) ) {

      // Lookup the first address in the list
      // XXX: MAY BE 127.0.0.1: CHECK FOR AN ACTUAL INTERFACE ADDRESS USING
      // XXX: getifaddrs and the inf file. XXX:

      for( pAddrInfo = servinfo ; NULL != pAddrInfo ; pAddrInfo = pAddrInfo->ai_next ) {

	// Found an address, so return the address.

	if ( NULL != pAddrInfo ) {
	  pSockAddr  = (struct sockaddr_in*)pAddrInfo->ai_addr;
	  hostIpAddr = pSockAddr->sin_addr.s_addr;
	  break;
	}
      }
    }else{
      OutputError("ThisHostToIp: getaddrinfo");
    }
  }else{
    OutputError("ThisHostToIp: gethostname");
  }

  return hostIpAddr;
}

/* --------------------------------------------------------------------------
 * Get the network address for the requested computer.
 * -------------------------------------------------------------------------- */

int GetHostAddress(int iProtocol,char* pHostname,struct sockaddr* pAddress,int iAddressLen,int iPort)
{
	int  iRc = -1;

	struct addrinfo hints, *servinfo, *pAddrInfo;

   // Setup the hints for acquiring the address info

	memset((void*)&hints,(char)0,sizeof hints);
    hints.ai_family   = iProtocol;
    hints.ai_socktype = SOCK_DGRAM;

    if ( iProtocol != AF_INET && iProtocol != AF_INET6 ) return iRc;

    // Get the address info

    if ( 0 == getaddrinfo(pHostname,"echo",&hints,&servinfo) ) {

        // Lookup the first address in the list

        for( pAddrInfo = servinfo ; NULL != pAddrInfo ; pAddrInfo = pAddrInfo->ai_next ) {

    		// Found an address, so return the address.

    		if ( NULL != pAddrInfo ) {
    			if ( iProtocol == AF_INET ) {
    				struct sockaddr_in* sout = (struct sockaddr_in*)pAddress;
    				struct sockaddr_in* sin  = (struct sockaddr_in*)pAddrInfo->ai_addr;
    				memcpy((void*)sout,(void*)sin,sizeof(struct sockaddr_in));
    				sout->sin_port = htons(iPort);
    			}else if ( iProtocol == AF_INET6 ) {
    				struct sockaddr_in6* sout = (struct sockaddr_in6*)pAddress;
    				struct sockaddr_in6* sin  = (struct sockaddr_in6*)pAddrInfo->ai_addr;
    				memcpy((void*)sout,(void*)sin,sizeof(struct sockaddr_in6));
    				sout->sin6_port = htons(iPort);
    			}
    			iRc = 0;
    			break;
    		}
        }
        freeaddrinfo(servinfo);

    }else{
      OutputError("ThisHostToIp: getaddrinfo");
    }

    return iRc;
}

/* --------------------------------------------------------------------------
 * Create a new datagram socket (ipv4) using this port.
 * XXX: Additional support for ipv6 is required
 * -------------------------------------------------------------------------- */

int GetDGramListenSocket(int iPort)
{
  struct sockaddr_in sin;

  // Allocate a new socket

  int iSocket = socket(AF_INET,SOCK_DGRAM,0);

  if ( -1 != iSocket ) {
    memset((void*)&sin,(char)0,sizeof sin);

    // Fill in the blanks to build a new socket that will listen for a
    // request for conversaion

    sin.sin_family      = AF_INET;
    sin.sin_port        = htons(iPort);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( -1 == bind(iSocket,(struct sockaddr*)&sin,sizeof sin) ) {
      OutputError("GetDGramListenSocket: bind");
      close(iSocket);
      iSocket = -1;
    }
  }else{
    OutputError("GetDGramListenSocket: socket");
  }

  return iSocket;
}

/* --------------------------------------------------------------------------
 * Wait for a caller on the open datagram socket.
 * -------------------------------------------------------------------------- */

int LoopForDGram(int iSocket,int iSeconds)
{
  int    iRc;
  int    iFdCount;
  fd_set readfds;

  struct timeval delay;

  // Loop until a connection request appears

  int bWaitFor = TRUE;

  iFdCount = 1 + iSocket;

  while( bWaitFor ) {

    // Setup and listen for a connection request

    FD_ZERO(&readfds);
    FD_SET(iSocket,&readfds);

    memset((void*)&delay,(char)0,sizeof delay);

    delay.tv_sec = iSeconds;

    iRc = select(iFdCount,&readfds,(fd_set*)NULL,(fd_set*)NULL,(struct timeval*)&delay);

    // Make sure the connection request is valid and not an error

    switch( iRc ) {
    case -1:
      OutputError("WaitForAnyDGram: select");
      bWaitFor = FALSE;
      break;

    case 1:
      bWaitFor = FALSE;
      break;

    default:
      break;
    }
  }

  // Return the connection request status

  return iRc;
}

/* --------------------------------------------------------------------------
 * Retrieve the command data and get a new bound and connected socket
 * for communication. Pass the information back in the datagram connect
 * structure.
 * -------------------------------------------------------------------------- */

int GetDGramCommand(int iSocket,pDGramConnect pConnect)
{
  int    iRc;

  char   bufr[COMMAND_LENGTH];
  int    iPeer;

  struct sockaddr_in sin;
  struct sockaddr_in frm;

  socklen_t iSinSize = sizeof sin;

  // Build a new socket address for connecting to the peer

  sin.sin_family      = AF_INET;
  sin.sin_port        = 0;
  sin.sin_addr.s_addr = ThisHostToIp();

  if ( (unsigned long)-1 != sin.sin_addr.s_addr ) {

    iRc = recvfrom(iSocket,
		   (void*)bufr,
		   COMMAND_LENGTH,
		   MSG_DONTWAIT,
		   (struct sockaddr*)&frm,
		   &iSinSize);

    // Build the new connected socket.

    if ( -1 != iRc && COMMAND_LENGTH >= iRc ) {

      // Build a new socket for talking to the peer

      iPeer = socket(AF_INET,SOCK_DGRAM,0);

      if ( -1 != iPeer ) {

	// Bind the socket to this guy.

	iRc = bind(iPeer,(struct sockaddr*)&sin,iSinSize);

	if ( -1 != iRc ) {

	  // Connect the socket to finish the socket construction.

	  iRc = connect(iPeer,(struct sockaddr*)&frm,iSinSize);

	  // Save the data and newly created socket.

	  if ( -1 != iRc ) {
	    memcpy((void*)pConnect->pCommand,(void*)bufr,sizeof bufr);
	    pConnect->iSocket = iPeer;
	  }else{
	    OutputError("GetDGramCommand: connect");
	  }
	}else{
	  OutputError("GetDGramCommand: bind");
	}
      }else{
	OutputError("GetDGramCommand: socket");
      }
    }else{
      OutputError("GetDGramCommand: recvfrom");
    }
  }else{
    OutputError("GetDGramCommand: getsockname");
  }

  return iRc;
}

/* --------------------------------------------------------------------------
 * Retrieve the command data and get a new bound and connected socket
 * for communication. Pass the information back in the datagram connect
 * structure.
 * -------------------------------------------------------------------------- */

int RecvMsgFrom(int iSocket,
		int* iReadLen,
		char* bufr,
		int   buflen,
		struct sockaddr_in* sPartner)
{
	struct sockaddr_in sin;

	int iPartner = -1;

	socklen_t iAddrSize = (socklen_t)sizeof sin;

	int iRc = recvfrom(iSocket,bufr,buflen,0,(struct sockaddr*)&sPartner,&iAddrSize);

	if ( -1 != iRc ) {
		*iReadLen = iRc;
		iPartner = socket(AF_INET,SOCK_DGRAM,0);
		if ( -1 != iRc ) {
			iRc = getsockname(iSocket,(struct sockaddr*)&sin,(socklen_t*)&iAddrSize);
			if ( -1 != iRc ) {
				sin.sin_port = 0;
				iRc = bind(iPartner,(struct sockaddr*)&sin,iAddrSize);
				if ( -1 != iRc ) {
					iRc = connect(iPartner,(struct sockaddr*)&sPartner,iAddrSize);
					if ( -1 != iRc ) {
						iRc = iPartner;
					}else{
						OutputError("RecvMsgFrom: connect");
					}
				}else{
					OutputError("RecvMsgFrom: bind");
				}
			}else{
				OutputError("RecvMsgFrom: getsockname");
			}
		}else{
			OutputError("RecvMsgFrom: socket");
		}
	}else{
		OutputError("RecvMsgFrom: recvfrom");
	}

	if ( -1 == iRc && -1 != iPartner ) close(iPartner);

	return iRc;
}

/* --------------------------------------------------------------------------
 * Send a text message to a datagram socket. The socket should be
 * bound and connected.
 * -------------------------------------------------------------------------- */

int SendTxtMsgToDGram(int iSocket,char* pMsg)
{
  int iRc = send(iSocket,pMsg,1+strlen(pMsg),0);

  if ( -1 == iRc ) OutputError("SendTxtMsgToDGram: send");

  return iRc;
}

/* --------------------------------------------------------------------------
 * Get the random number generator seed for transaction id production.
 * -------------------------------------------------------------------------- */

#include <time.h>
#include <sys/resource.h>

#if 1
unsigned int SeedDGramTransId(void)
{
  struct rusage usage;
  int iRc = getrusage(RUSAGE_SELF,&usage);

  unsigned int uRc;

  if ( -1 != iRc ) {
    uRc = usage.ru_stime.tv_usec + (usage.ru_stime.tv_sec / 1000);
  }else{
    OutputError("SendDGramTransId: getrusage");
    uRc = (unsigned int)iRc;
  }

  return uRc;
}

#else

unsigned int SeedDGramTransId(void)
{
	struct timespec boottime;
	struct timespec proctime;
	struct timespec threadtime;

	unsigned int seed;

	// Get the boot time clock

	int iRc = clock_gettime(CLOCK_BOOTTIME,&boottime);

	if ( -1 != iRc ) {

		// Get the process elapsed cpu time.

		iRc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&proctime);
		if ( -1 != iRc ) {

			// Get the thread elapsed cpu time.

			iRc = clock_gettime(CLOCK_THREAD_CPUTIME_ID,&threadtime);

			if ( -1 != iRc ) {

				// The sum of the components is your new seed.

				seed = (unsigned int)boottime.tv_sec + (unsigned int)boottime.tv_nsec +
						(unsigned int)proctime.tv_sec + (unsigned int)proctime.tv_nsec +
						(unsigned int)threadtime.tv_sec + (unsigned int)threadtime.tv_nsec;
			}else{
				OutputError("SeedDGramTransId: CLOCK_THREAD_CPUTIME");
			}
		}else{
			OutputError("SeedDGramTransId: CLOCK_PROCESS_CPUTIME");
		}
	}else{
		OutputError("SeedDGramsTransId: CLOCK_BOOTTIME");
	}

	// Send back the seed if there was no error.

	return (-1 != iRc ? seed : (unsigned int)iRc);
}

#endif

/* --------------------------------------------------------------------------
 * Get the random transaction id.
 * -------------------------------------------------------------------------- */

int GetTransId(unsigned int* pSeed)
{
	return rand_r(pSeed);
}

/* --------------------------------------------------------------------------
 * Create and send a text message to a fully qualified dgram socket.
 * Full qualification for the peer side of the connection comes from the
 * recvfrom method.
 * -------------------------------------------------------------------------- */

int SendTxtCommandTo(char*            pMsg,
		             int              iFamily,
		             unsigned int*    pTransId,
		             struct sockaddr *pDestAddr,
		             struct sockaddr *pHostAddr,
		             int             *pAddrLen)
{
	return SendDataCommandTo((void*)pMsg,
			                 1+strlen(pMsg),
			                 iFamily,
			                 pTransId,
			                 pDestAddr,
			                 pHostAddr,
			                 pAddrLen);
}

/* --------------------------------------------------------------------------
 * Create and send a data buffer to a fully qualified dgram socket.
 * Full qualification for the peer side of the connection comes from the
 * recvfrom method.
 * -------------------------------------------------------------------------- */

int SendDataCommandTo(void*            pData,
		              int              iLength,
		              int              iFamily,
		              unsigned int*    pTransId,
		              struct sockaddr* pDestAddr,
		              struct sockaddr* pHostAddr,
		              int*             pAddrLen)
{
	int iRc;
	int bContinue = TRUE;
	int iSocket   = socket(iFamily,SOCK_DGRAM,0);

	fd_set readfds;
	struct timeval maxdelay;

	char pBufr[COMMAND_RESPONSE_LENGTH];

	// Make sure the socket is valid.

	if ( -1 == iSocket ) {
		OutputError("SendDataCommandTo: socket");
		return iSocket;
	}else if ( iLength + sizeof(uint32_t) > COMMAND_RESPONSE_LENGTH ) {
		OutputError("SendDataComamndTo: Maximum Buffer Size Exceeded");
		return -1;
	}

	// Bind the created socket to build a fully qualified host connection

	iRc = bind(iSocket,pHostAddr,(socklen_t)*pAddrLen);

	// Send the data to the remote host if possible

	if ( -1 != iRc ) {

		// Build the output buffer with transaction id

		unsigned long* up;

		memcpy((void*)pBufr,(void*)pData,iLength);
		up = (unsigned long*)((char*)(pBufr + iLength));
		*up = htonl(*pTransId);
		iLength += sizeof(uint32_t);

		iRc = sendto(iSocket,pBufr,iLength,0,pDestAddr,*pAddrLen);

		// Wait for the ack to build a fully qualified connection.

		if ( -1 != iRc ) {

			// Loop and pitch any invalid transaction data

			while( bContinue ) {
				FD_ZERO(&readfds);
				FD_SET(iSocket,&readfds);
				memset((void*)&maxdelay,(char)0,sizeof maxdelay);
				maxdelay.tv_sec = 2;

				switch( select(1+iSocket,(fd_set*)&readfds,(fd_set*)0,(fd_set*)0,&maxdelay) ) {

				case -1: // Some type of error, so report it
					OutputError("SendDataCommandTo: select");
					shutdown(iSocket,SHUT_RDWR);
					close(iSocket);
					iRc = -1;
					bContinue = FALSE;
					break;

				case 0: // The timer expired without response so just quietly return an error
					shutdown(iSocket,SHUT_RDWR);
					close(iSocket);
					iRc = -1;
					bContinue = FALSE;
					break;

				default: // Got data back from the caller so check for ack and build socket
					{
						char ackbuf[COMMAND_LENGTH];

						// Send the data to the remote host if possible

						char pAckBuffer[COMMAND_LENGTH];

						struct sockaddr* pAckAddr = (struct sockaddr*)(&pAckBuffer[0]);

//						struct sockaddr* pAckAddr = (struct sockaddr*)malloc(*pAddrLen);

						if ( pAckAddr ) {
							memset((void*)ackbuf,(char)0,sizeof ackbuf);

							iRc = recvfrom(iSocket,ackbuf,(size_t)sizeof(ackbuf),0,pAckAddr,(socklen_t*)pAddrLen);

							// Handle a valid ack packet.

							if ( -1 != iRc && iRc == (ACK_LENGTH+sizeof(uint32_t)) && !strcmp(ackbuf,pAck) ) {

								// Verify the transaction data

								unsigned int iTransTmp = ntohl(*((unsigned long*)(ackbuf+ACK_LENGTH)));

								// Make sure that the address of the inbound data and the transaction id
								// match to indicate a valid acknowledgement.

								if ( iFamily == AF_INET ) {
									struct sockaddr_in* pAddr = (struct sockaddr_in*)pAckAddr;
									struct sockaddr_in* pAdin = (struct sockaddr_in*)pDestAddr;
									if ( pAddr->sin_addr.s_addr == pAdin->sin_addr.s_addr && *pTransId == iTransTmp ) {
										bContinue = FALSE;
									}
								}else{
									struct sockaddr_in6* pAddr = (struct sockaddr_in6*)pAckAddr;
									struct sockaddr_in6* pAdin = (struct sockaddr_in6*)pDestAddr;
									if ( !memcmp((void*)&pAddr->sin6_addr,(void*)&pAdin->sin6_addr,sizeof(struct in6_addr)) && *pTransId == iTransTmp ) {
										bContinue = FALSE;
									}
								}

								// For a valid acknoledgement, complete construction of the
								// fully qualified socket.

								if ( FALSE == bContinue ) {
									iRc = connect(iSocket,pAckAddr,*pAddrLen);

									if ( -1 != iRc ) {
										iRc = iSocket;
									}else{
										OutputError("SendDataCommandTo: connect");
										shutdown(iSocket,SHUT_RDWR);
										close(iSocket);
									}
									bContinue = FALSE;
								}

							}else if ( -1 == iRc ){

								// Manage the data retrieval error

								OutputError("SendDataCommandTo: recvfrom");
								shutdown(iSocket,SHUT_RDWR);
								close(iSocket);
								bContinue = FALSE;
							}else{

								// Discard the invalid transaction data.

								iRc = iSocket;
							}
//							free((void*)pAckAddr);

						}else{
							OutputError("SendDataCommandTo: malloc");
							shutdown(iSocket,SHUT_RDWR);
							close(iSocket);
							bContinue = FALSE;
						}
						break;
					}
				}
			}
		}else{
			OutputError("SendDataCommandTo: sendto");
			shutdown(iSocket,SHUT_RDWR);
			close(iSocket);
		}
	}else{
		OutputError("SendDataCommandTo: bind");
		shutdown(iSocket,SHUT_RDWR);
		close(iSocket);
	}
	return iRc;
}

int SendResponseToClient(int iSocket,uint32_t uiTransId,void* pResponse,int iRespLength)
{
	int  iRc;                                      // Request return code
	char pBufr[COMMAND_RESPONSE_LENGTH];            // Final data transmission buffer
	int  iBufLen = iRespLength + sizeof uiTransId; // Length of final data packet

	uint32_t* pTransId = (uint32_t*)(pBufr + iRespLength);
	memcpy((void*)pBufr,pResponse,iRespLength);
	*pTransId = htonl(uiTransId);

	// Send the packet to the client and wait for a response. Responses exceeding
	// 2 seconds are considered invalid.

	iRc = send(iSocket,pBufr,iBufLen,0);

	if ( -1 != iRc ) {
		fd_set readfds;
		struct timeval maxdelay;
		int    bContinue = TRUE;
		int    iFdCount  = 1 + iSocket;

		while( bContinue ) {

			FD_ZERO(&readfds);
			FD_SET(iSocket,&readfds);

			maxdelay.tv_sec = 2;

			switch( (iRc=select(iFdCount,&readfds,(fd_set*)0,(fd_set*)0,&maxdelay)) ) {
			case -1: // Select error
				OutputError("SendResponseToClient: select");
				bContinue = FALSE;
				break;

			case 0: // Timed out so just quietly quit
				iRc       = -1;
				bContinue = FALSE;
				break;

			default: // The 1 file descriptor has data waiting on it.
				bContinue = FALSE;
				break;
			}
		}

		// If iRc != -1 then there is data waiting in the queue for pickup.

		if ( -1 != iRc ) {

			char eotbuf[56];

			// Receive the inbound data.

			memset((void*)eotbuf,(char)0,sizeof eotbuf);
			iRc = recv(iSocket,eotbuf,sizeof eotbuf,MSG_DONTWAIT);

			// Make sure the packet represents a valid transaction end of transmission request.

			if ( -1 == iRc ) {
				OutputError("SendResponseToClient: recv");
			}else if ( (EOT_LENGTH + sizeof(uint32_t)) != iRc || strcmp(eotbuf,pEOT) ) {
				iRc = -1;
			}else{
				uint32_t* pTransId = (uint32_t*)(eotbuf + EOT_LENGTH);
				if ( ntohl(*pTransId) != uiTransId ) {
					iRc = -1;
				}
			}
		}

	}else{
		OutputError("SendResponseToClient: send");
	}

	return iRc;
}

int RecvResponseFrom(int iSocket,char* pBufr,int iBufLen,unsigned int iTransId)
{
	int iRc;
	int iFdCount = 1 + iSocket;

	struct timeval tv;
	fd_set readfds;

	int  bContinue = TRUE;
	int  iTmpLen   = iBufLen + sizeof(uint32_t);
	char pTmpBuf[COMMAND_RESPONSE_LENGTH];

	while( bContinue ) {
		FD_ZERO(&readfds);
		FD_SET(iSocket,&readfds);
		memset((void*)&tv,(char)0,sizeof tv);
		tv.tv_sec = 2;

		switch( (iRc=select(iFdCount,&readfds,(fd_set*)0,(fd_set*)0,&tv)) ) {
		case -1: // An error occured so report it and move on.
			OutputError("RecvResponseFrom: select");
			bContinue = FALSE;
			break;

		case 0:  // Timed out without a response so exit
			iRc = -1;
			bContinue = FALSE;
			break;

		default: // XXX: Should the buffer just be truncated if passed buffer was too small?
			iRc = recv(iSocket,pTmpBuf,iTmpLen,0);
			if ( -1 != iRc && iRc < COMMAND_RESPONSE_LENGTH && iRc <= iBufLen ) {
				uint32_t* up = (uint32_t*)(pTmpBuf + iRc - sizeof(uint32_t));
				unsigned int iNetTransId = ntohl(*up);
				if ( iTransId == iNetTransId ) {
					iRc -= sizeof(uint32_t);
					memcpy((void*)pBufr,pTmpBuf,iRc);
					bContinue = FALSE;
				}
			}else if ( iRc > iBufLen ) {
				OutputError("RecvResponseFrom: Passed Buffer Too Small: memcpy");
				iRc = -1;
				bContinue = FALSE;
			}
			break;
		}
	}
	return iRc;
}

int SendDGramDataTo(int iSocket,int iTransId,void* pData,int iLength)
{
	int   iRc = -1;

	// Calculate the buffer size and allocate memory for the full buffer

	int   iDataLength = iLength + sizeof(uint32_t);
	char* pBufr       = (char*)malloc(iDataLength);

	if ( pBufr ) {

		// Add the transaction id to the buffer

		uint32_t* up = (uint32_t*)pBufr;
		*up = htonl(iTransId);
		up += sizeof(uint32_t);

		// Copy the data into the buffer and send the data out.

		memcpy((void*)up,pData,iLength);
		iRc = send(iSocket,pBufr,iDataLength,0);

		// If there was an error, report it.

		if ( -1 == iRc ) OutputError("SendDGramDataToL send");

		// Clean up

		free((void*)pBufr);

	}else{

		// Report the memory allocation error.

		OutputError("SendDGramDataTo: malloc");
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Send OK to caller.
 * -------------------------------------------------------------------------- */

int SendDGramOK(int iSocket,int iTransID)
{
	int  iRc;
	int  iLength;
	char bufr[56];

	unsigned long* up;

	strcpy(bufr,pOk);
	 up = (unsigned long*)bufr + OK_LENGTH;
	*up = htonl(iTransID);
	iLength = (int)((char*)up + sizeof(uint32_t) - bufr);

	iRc = send(iSocket,bufr,iLength,0);

	if ( -1 == iRc ) OutputError("SendDGramOK: send");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Send ACK to caller.
 * -------------------------------------------------------------------------- */

int SendDGramAck(int iSocket,int iTransId)
{
	int iRc;
	int iLength;
	char bufr[56];

	unsigned long *up;

	strcpy(bufr,pAck);
	 up = (unsigned long*)(bufr + ACK_LENGTH);
	*up = htonl(iTransId);
	iLength = (int)((char*)up + sizeof(uint32_t) - bufr);

	iRc = send(iSocket,bufr,iLength,0);

	if ( -1 == iRc ) OutputError("SendDGramAck: send");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Recv ACK from caller.
 * Returns 0 for ACK or -1 for something else.
 * -------------------------------------------------------------------------- */

int GetDGramAck(int iSocket,int iTransId)
{
	int iRc;
	char bufr[56];

	uint32_t* up;

	fd_set readfds;
	struct timeval delay;

	int bWaitFor = TRUE;

	int iFdCount = 1 + iSocket;

	while( bWaitFor ) {
		FD_ZERO(&readfds);
		FD_SET(iSocket,&readfds);
		memset((void*)&delay,(char)0,sizeof delay);

		delay.tv_sec = 1;

		iRc = select(iFdCount,&readfds,(fd_set*)NULL,(fd_set*)NULL,(struct timeval*)&delay);

		switch( iRc ) {
		case -1:
			OutputError("GetDGramAck: select");
			bWaitFor = FALSE;
			break;

		case 1:
			iRc = 0;
			bWaitFor = FALSE;
			break;

		default:
			iRc = -1;
			bWaitFor = FALSE;
			break;
		}
	}

	if ( -1 != iRc ) {
		int iCount = recv(iSocket,bufr,sizeof bufr,MSG_DONTWAIT);
		switch( iCount ) {
		case  0:
		case -1:
			iRc = -1;
			OutputError("GetDGramAck: recv");
			break;

		default:
			up = (uint32_t*)(bufr + ACK_LENGTH);
			iRc = (iCount == (ACK_LENGTH + sizeof(uint32_t)) &&
					!strcmp(pAck,bufr)                       &&
					iTransId == ntohl(*up)                    ? 0 : -1);
			break;
		}
	}
	return iRc;
}

/* --------------------------------------------------------------------------
 * Send EOT to caller.
 * -------------------------------------------------------------------------- */

int SendDGramEOT(int iSocket,int iTransId)
{
	int  iRc;
	int  iLength;
	char bufr[56];

	uint32_t* up;

	strcpy(bufr,pEOT);
	 up = (uint32_t*)((char*)bufr + EOT_LENGTH);
	*up = htonl(iTransId);
	iLength = EOT_LENGTH + sizeof(uint32_t);

	iRc = send(iSocket,bufr,iLength,0);

	if ( -1 == iRc ) OutputError("SendDGramEOT: send");

	return iRc;
}

/* --------------------------------------------------------------------------
 * Send a data stream to a datagram socket. The socket should be
 * bound and connected.
 * -------------------------------------------------------------------------- */

int SendDataToDGram(int iSocket,void* pOctets,int iOctetLength)
{
  int iRc = send(iSocket,pOctets,iOctetLength,0);

  if ( -1 == iRc ) OutputError("SendDataToDGram: send");

  return iRc;
}

/* --------------------------------------------------------------------------
 * Receive data from a datagram socket. The socket should be
 * bound and connected.
 * -------------------------------------------------------------------------- */

int RecvDGramMsg(int iSocket,char* pBuf,int iBufLen)
{
  int iRc = recv(iSocket,pBuf,iBufLen,0);

  if ( -1 == iRc ) OutputError("RecvDGramMsg: recv");

  return iRc;
}

/* --------------------------------------------------------------------------
 * Shutdown and close the passed socket.
 * -------------------------------------------------------------------------- */

void CloseConnection(int iSocket)
{
	if ( -1 != iSocket ) {
		shutdown(iSocket,SHUT_RDWR);
		close(iSocket);
	}
}
