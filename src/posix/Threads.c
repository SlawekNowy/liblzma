/* Threads.c -- multithreading library
 *
 *
2017-06-26 : Igor Pavlov : Public domain */





#include "Precomp.h"

#include <errno.h>



#include <pthread.h>
#include "Threads.h"

static WRes GetError()
{
  DWORD res = errno;
  return res ? (WRes)res : 1;
}

static WRes HandleToWRes(void* h) { return (h != NULL) ? 0 : GetError(); }
static WRes BOOLToWRes(BOOL v) { return v ? 0 : GetError(); }

/*
WRes HandlePtr_Close(HANDLE *p)
{
  if (*p != NULL)
  {
    if (!CloseHandle(*p))
      return GetError();
    *p = NULL;
  }
  return 0;
}

WRes Handle_WaitObject(HANDLE h) { return (WRes)WaitForSingleObject(h, INFINITE); }
*/

WRes Thread_Create(CThread *p, THREAD_FUNC_TYPE func, void* param)
{

  return HandleToWRes(*p);
}

WRes Thread_Wait(CThread *p) {

}
WRes Thread_Close(CThread *p) {

}

static WRes Event_Create(CEvent *p, BOOL manualReset, int signaled)
{
  **p = CreateEvent(NULL, manualReset, (signaled ? TRUE : FALSE), NULL);
  return HandleToWRes(*p);
}

WRes Event_Set(CEvent *p) { return BOOLToWRes(SetEvent(**p)); }
WRes Event_Reset(CEvent *p) { return BOOLToWRes(ResetEvent(**p)); }

WRes ManualResetEvent_Create(CManualResetEvent *p, int signaled) { return Event_Create(p, TRUE, signaled); }
WRes AutoResetEvent_Create(CAutoResetEvent *p, int signaled) { return Event_Create(p, FALSE, signaled); }
WRes ManualResetEvent_CreateNotSignaled(CManualResetEvent *p) { return ManualResetEvent_Create(p, 0); }
WRes AutoResetEvent_CreateNotSignaled(CAutoResetEvent *p) { return AutoResetEvent_Create(p, 0); }

WRes Event_Wait(CEvent *p) {

}
WRes Event_Close(CEvent *p) {

}


WRes Semaphore_Create(CSemaphore *p, UInt32 initCount, UInt32 maxCount)
{
  *p = CreateSemaphore(NULL, (UInt32)initCount, (UInt32)maxCount, NULL);
  return HandleToWRes(*p);
}

static WRes Semaphore_Release(CSemaphore *p, UInt32 releaseCount, UInt32 *previousCount)
  { return BOOLToWRes(ReleaseSemaphore(*p, releaseCount, previousCount)); }
WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 num)
  { return Semaphore_Release(p, (UInt32)num, NULL); }
WRes Semaphore_Release1(CSemaphore *p) { return Semaphore_ReleaseN(p, 1); }

WRes Semaphore_Wait(CSemaphore *p) {

}
WRes Semaphore_Close(CSemaphore *p) {

}

WRes CriticalSection_Init(CCriticalSection *p)
{

  return 0;
}

WRes CriticalSection_Delete(CCriticalSection *p)
{

}

WRes CriticalSection_Enter(CCriticalSection *p)
{

}

WRes CriticalSection_Leave(CCriticalSection *p)
{

}
