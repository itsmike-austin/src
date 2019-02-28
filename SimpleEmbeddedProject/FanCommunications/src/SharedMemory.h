#ifndef _SHARED_MEMORY_H
#define _SHARED_MEMORY_H

/* ==========================================================================
 * SharedMemory:
 *    The shared memory module consists of two primary methods:
 *        GetSharedMemory: Used to allocate shared memory
 *        DelSharedMemory: Used to deallocate shared memory
 *
 *        int GetSharedMemory: Returns the shared memory id or -1 for error
 *        int DelSharedMemory: Returns non-zero for valid or -1 for error
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *    int GetSharedMemory(char** pSharedSegment,int iSegmentSize,int ShmKey):
 *             pSharedSegment: address of the char* that holds the address
 *             iSegmentSize:   byte count of the memory
 *             ShmKey:         unique number for creating the segment key
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *    int DelSharedMemory(char* pSharedSegment,int iShmId):
 *             pSharedSegment: address that holds the address
 *             iShmId:         segment identifier created by GetSharedMemory
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 * ========================================================================== */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "OutputError.h"

extern int GetSharedMemory(char** pSharedSegment,int iSegmentSize,int iShmKey);
extern int AccessSharedMemory(int iShmKey,char** pSharedMemory);
extern int DetachSharedMemory(void* pSharedMemory);
extern int DelSharedMemory(char* pSharedSegment,int iShmId);

#endif

