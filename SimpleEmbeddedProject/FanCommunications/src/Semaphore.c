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
 * --------------------------------------------------------------------------
 *  Refer to the header file for full method descriptions with passed
 *  parameter definitions.
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 * ========================================================================== */

#include "Semaphore.h"

/* --------------------------------------------------------------------------
 * Allocate a semaphore set that consists of a single entry
 * -------------------------------------------------------------------------- */

int GetSemaphore(int iSemVal,int iKeyNum)
{
  key_t semkey;
  int   semid;

  union semun {
	  int              val;
	  struct semid_ds *buf;
	  ushort*          array;
  }argument;

  int iRc = -1;

  // Create the new semaphore key

  semkey = ftok("/var/log/syslog",iKeyNum);

  if ( -1 == semkey )
    {
      OutputError("Semkey");
    }
  else
    {
      // Allocate a new semaphore id for the semget with a single entry

      semid = semget(semkey,1,IPC_CREAT|0600);

      if ( -1 == semid ) {
    		OutputError("Semget");
      }else{

  		// Set the value for the semaphore

  	  argument.val = 1;

  		iRc = semctl(semid,0,SETVAL,argument);

  		if ( -1 == iRc )
  		{
  		  OutputError("Semctl");
  		  semctl(semid,0,IPC_RMID);
  		}
  		else
  		{
  		  // Save the new semaphore data.
  		  iRc = semid;
  		}
      }
    }
  return iRc;
}

/* --------------------------------------------------------------------------
 * Get a semaphore that should already be created
 * -------------------------------------------------------------------------- */

int AccessSemaphore(int iSemVal,int iKeyNum)
{
	key_t semkey;

	// Create the semaphore key

	semkey = ftok("/var/log/syslog",iKeyNum);

	if ( -1 == semkey )
	{
		OutputError("Semkey");
		return semkey;
	}

	return semget(semkey,1,0);
}

/* --------------------------------------------------------------------------
 * Set the value of a semaphore
 * -------------------------------------------------------------------------- */

int SemIncrement(int iSemId,int iSemNumber)
{
	struct sembuf sem;

	sem.sem_num = iSemNumber;
	sem.sem_op  = 1;
	sem.sem_flg = 0;

	return semop(iSemId,&sem,1);
}

/* --------------------------------------------------------------------------
 *
 * Set the value of a semaphore
 * -------------------------------------------------------------------------- */

int SemRelease(int iSemId,int iSemNumber)
{
	struct sembuf sem;

	sem.sem_num = iSemNumber;
	sem.sem_op  = -1;
	sem.sem_flg = 0;

	return semop(iSemId,&sem,1);
}

/* --------------------------------------------------------------------------
 * Wait for a semaphore
 * -------------------------------------------------------------------------- */

int WaitForSem(int iSemId,int iSemNumber)
{
	struct sembuf sem[2];

	sem[0].sem_num = iSemNumber;
	sem[0].sem_op  = 0;
	sem[0].sem_flg = 0;

	sem[1].sem_num = iSemNumber;
	sem[1].sem_op  = 1;
	sem[1].sem_flg = 0;

	return semop(iSemId,sem,2);
}

/* --------------------------------------------------------------------------
 * Remove a semaphore array from the system.
 * -------------------------------------------------------------------------- */

int DelSemaphore(int iSemId)
{
  return semctl(iSemId,0,IPC_RMID);
}

