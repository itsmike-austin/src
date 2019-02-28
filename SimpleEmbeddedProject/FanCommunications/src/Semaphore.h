/* ==========================================================================
 * Semaphore:
 *    The semaphore module consists of three primary methods:
 *        GetSemaphore: Used to retrieve a semaphore set that has a single
 *                      semaphore in the array.
 *        SetSemValue:  Used to set the value of a semaphore
 *        GetSemValue:  Used to get the value of a semaphore
 *        DelSemaphore: Used to cleanup the semahore set.
 *
 *        All methods log errors to the syslog file for consistency
 *        and convenience
 *
 *        int  GetSemaphore: Returns the semphore id or -1 for all errors
 *        int  GetSemValue:  Retrieve the current value of the semaphore
 *        int  SetSemValue:  Set the current value of the semaphore.
 *        void DelSemaphore: Destroys the semaphore
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *    int GetSemaphore(int iSemVal,int iKeyNum) :
 *                     iSemVal: The value of the semaphore (0 or 1)
 *                     iKeyNum: A number to use for generation of the
 *                              access key
 *        returns:
 *              iSemId (The semaphore identifier) or -1 on error
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *    int DelSemaphore(int iSemId) :
 *                       iSemId: The semaphore identier returned by Get
 *
 *         returns a non-negative number for success or -1 for an error
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 * ========================================================================== */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "OutputError.h"

union semun {
  int val;
  struct semid_ds buf;
  ushort* array;
}semopts;

extern int GetSemaphore(int iSemVal,int iKeyNum);
extern int AccessSemaphore(int iSemVal,int iKeyNum);
extern int SemRelease(int iSemId,int iSemNumber);
extern int SemIncrement(int iSemId,int iSemNumber);
extern int WaitForSem(int iSemId,int iSemNumber);
extern int DelSemaphore(int iSemId);

#endif

