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
 *        int  ThisHostToIp(void):
 *                in:  void
 *                out: 32 bit network address in network order
 *
 *        int  GetDGramListenSocket(int iPort):
 *                in:  Requested port number
 *                out: Bound socket for listening
 *
 *        int  LoopForDGram(int iSocket,int Seconds):
 *                in:  Socket to listen to
 *                in:  Number of seconds to wait for data before looping out
 *                out: -1 for error or # of sockets waiting with data
 *
 *        int  GetDGramCommand(int iSocket,pDGramConnect pConnect):
 *                in:  Socket to retrieve data from
 *                in:  Connection and data buffer
 *                out: -1 for error or the number of characters in the buffer
 *
 *        int  SendTxtMsgToDGram(int iSocket,char* pMsg):
 *                in:  Socket to send the data to (bound/connected)
 *                in:  Character string to send
 *                out: -1 for error or number of characters sent
 *
 *        int  SendDataToDGram(int iSocket,void* pOctets,int iOctetLength):
 *                in:  Socket to send the data to (bound/connected)
 *                in:  Octet buffer
 *                in:  Length of the octet buffer
 *                out: -1 for error or the number or characters sent
 *
 *        void DGramClose(int iSocket):
 *                in:  Socket to shutdown and close
 *
 * --------------------------------------------------------------------------
 *  TBD: Consider adding a passed method to be called after execution
 *       of each pass through the loop (an idle method) for LoopForStream.
 * --------------------------------------------------------------------------
 * (c) 1999 itsinc (mdb)
 * ========================================================================== */

#ifndef _DGRAM_SOCKET_H
#define _DGRAM_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "OutputError.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define COMMAND_LENGTH 128
#define COMMAND_RESPONSE_LENGTH 256

typedef struct {
  int iSocket;
  char pCommand[COMMAND_LENGTH];
}DGramConnect,*pDGramConnect;

extern unsigned long ThisIFaceToIp(char* pIFaceName);
extern unsigned long ThisHostToIp();
extern          int  GetHostAddress(int iProtocol,char* pHostname,struct sockaddr* pAddress,int iAddressLen,int iPort);
extern          int  GetTransId(unsigned int* pSeed);
extern unsigned int  SeedDGramTransId(void);
extern          int  GetDGramListenSocket(int iPort);
extern          int  LoopForDGram(int iSocket,int iSeconds);
extern          int  RecvMsgFrom(int iSocket,int* iReadLen,char* bufr,int buflen,struct sockaddr_in* sPartner);
extern          int  GetDGramCommand(int iSocket,pDGramConnect pConnect);
extern          int  SendTxtMsgToDGram(int iSocket,char* pMsg);
extern          int  SendTxtCommandTo(char* pMsg,int iFamily,unsigned int* pTransId,struct sockaddr *pDestAddr,struct sockaddr *pHostAddr,int* pAddrLen);
extern          int  SendDataCommandTo(void* pData,int iLength,int iFamily,unsigned int* pTransId,struct sockaddr* pDestAddr,struct sockaddr* pHostAddr,int* pAddrLen);
extern          int  SendResponseToClient(int iSocket,uint32_t uiTransId,void* pResponse,int iRespLength);
extern          int  SendDGramOK(int iSocket,int iTransID);
extern          int  SendDGramAck(int iSocket,int iTransId);
extern          int  SendDGramEOT(int iSocket,int iTransId);
extern          int  SendDataToDGram(int iSocket,void* pOctets,int iOctetLength);
extern          int  RecvDGramMsg(int iSocket,char* pBuf,int iBufLen);
extern          int  RecvResponseFrom(int iSocket,char* pBufr,int iBufLen,unsigned int iTransId);
extern          void CloseConnection(int iSocket);
#if 0
extern          void DGramClose(int iSocket);
#endif


#endif
