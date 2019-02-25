/* ************************************************************
 * CApplicationLock
 *
 * Application locks are used to serialize access to the
 * object and callback lists for threaded methods.
 *
 * All management methods are contained in this object.
 *
 * MICROSOFT SPECIFIC: REQUIRED
 *
 * UNIX SPECIFIC:      REQUIRED
 * 
 * ------------------------------------------------------------
 * (c) ItsInc (1999,2001,2005,2006)
 * ************************************************************ */

#include <CApplicationLock.h>

CApplicationLock::CApplicationLock()
{
#if defined(_WIN32) || defined(_WIN64)
  InitializeCriticalSection(&m_Lock);
#endif
}

CApplicationLock::~CApplicationLock()
{
#if defined(_WIN32) || defined(_WIN64)
  DeleteCriticalSection(&m_Lock);
#endif
}

// ???: Should I look at LockCount, Recursion Count, and Owning Thread
//      to determine if the thread is already locked?
//      rf: WINNT.H : Shouldn't be required since the ThreadId determines
//      access to the mutex.
//

LRESULT CApplicationLock::Lock()
{
#if defined(_WIN32) || defined(_WIN64)
  EnterCriticalSection(&m_Lock);
#endif
  return S_OK;
}

LRESULT CApplicationLock::Unlock()
{
#if defined(_WIN32) || defined(_WIN64)
  LeaveCriticalSection(&m_Lock);
#endif
  return S_OK;
}

LRESULT CApplicationLock::IsItLocked()
{
  LRESULT lRc;
#if defined(_WIN32) || defined(_WIN64)
#pragma warning(disable:4312)
  lRc = ((HANDLE)::GetCurrentThreadId() == m_Lock.OwningThread &&
	  -1 < m_Lock.LockCount ? S_OK : E_FAIL);
#pragma warning(default:4312)
#endif
  return lRc;
}

void* CApplicationLock::GetLock()
{
  return (void*)&m_Lock;
}
