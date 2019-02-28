/* ==========================================================================
 * SharedMemory:
 *    The shared memory module consists of two primary methods:
 *        GetSharedMemory: Used to allocate shared memory
 *        DelSharedMemory: Used to deallocate shared memory
 *
 *        int GetSharedMemory: Returns the shared memory id or -1 for error
 *        int DelSharedMemory: Returns non-zero for valid or -1 for error
 *
 * --------------------------------------------------------------------------
 *  Refer to the header file for full method descriptions with passed
 *  parameter definitions.
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 * ========================================================================== */

#include "SharedMemory.h"

/* --------------------------------------------------------------------------
 * Allocate a locked shared memory segment
 * -------------------------------------------------------------------------- */

int GetSharedMemory(char** pSharedSegment,
		    int    iSegmentSize,
		    int    iShmKey)
{
  int   shmid;
  char* pSharedMem;

  // Make sure that the shared segment is not null
  // (About the best you can do)

  if ( NULL == pSharedSegment ) return -1;

  // Create the shared memory key

  key_t shmkey = ftok("/var/log/syslog",iShmKey);

  if ( -1 == shmkey ) {
    OutputError("Shmkey");
    return -1;
  }

  //  Get the shared memory identifier

  shmid = shmget(shmkey,iSegmentSize,IPC_CREAT|0600);

  if ( -1 == shmid ) {
    OutputError("Shmget");
    return -1;
  }

  // Attach the requested memory segment

  pSharedMem = (char*)shmat(shmid,NULL,SHM_R|SHM_W|SHM_LOCK);

  if ( pSharedMem == (char*)-1 ) {
    OutputError("Shmat");
    shmctl(shmid,IPC_RMID,NULL);
    return -1;
  }

  // Return the freshly allocated segment.

  *pSharedSegment = pSharedMem;

  return shmid;
}

/* --------------------------------------------------------------------------
 * Access a shared memory segment
 * -------------------------------------------------------------------------- */

int AccessSharedMemory(int iShmKey,char** pSharedMemory)
{
	int   iRc = -1;
	int   shmid;
	key_t shmkey = ftok("/var/log/syslog",iShmKey);

	if ( NULL != pSharedMemory ) {
		unsigned int compvar = (unsigned int)shmkey;
		*pSharedMemory = NULL;
		if ( compvar != 0 ) {
			shmid = shmget(shmkey,0,0);
			if ( -1 != (int)shmid ) {
				*pSharedMemory = shmat(shmid,NULL,SHM_R);
				if ( NULL != *pSharedMemory ) {
					iRc = 0;
				}else{
					OutputError("AccessSharedMemory: shmat");
				}
			}else{
				OutputError("AccessSharedMemory: shmget");
			}
		}else{
			OutputError("AccessSharedMemory: ftok");
		}
	}

	return iRc;
}

/* --------------------------------------------------------------------------
 * Detach a shared memory segment.
 * -------------------------------------------------------------------------- */

int DetachSharedMemory(void* pSharedMemory) {
	int iRc = (NULL != pSharedMemory ? 0 : -1);

	if ( -1 != iRc ) {
		iRc = shmdt(pSharedMemory);
		if ( -1 == iRc ) OutputError("DetachSharedMemory: shmdt");
	}
	return iRc;
}

/* --------------------------------------------------------------------------
 * Deallocate and clear a shared memory segment.
 * -------------------------------------------------------------------------- */

int DelSharedMemory(char* pSharedSegment,
		    int   iShmId)
{
  // Detach the requested memory segment so it can be removed.

  int iRc = shmdt(pSharedSegment);

  // Remove the memory segment from the system.

  if ( -1 != iRc ) {
    iRc = shmctl(iShmId,IPC_RMID,NULL);
  }else{
    shmctl(iShmId,IPC_RMID,NULL);
  }

  return iRc;
}
