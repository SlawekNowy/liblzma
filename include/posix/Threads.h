/* Threads.h -- multithreading library
2017-06-18 : Igor Pavlov : Public domain */

#ifndef __7Z_THREADS_H
#define __7Z_THREADS_H


#include <pthread.h>
#include <semaphore.h>
#include "event_objects_posix.h"

#include "7zTypes.h"

#ifdef __unix__


#endif

EXTERN_C_BEGIN

/*
WRes HandlePtr_Close(HANDLE *h);
WRes Handle_WaitObject(HANDLE h);
*/

typedef pthread_t* CThread;
#define Thread_Construct(p) *(p) = NULL
#define Thread_WasCreated(p) (*(p) != NULL)
/*
#define Thread_Close(p) HandlePtr_Close(p)
#define Thread_Wait(p) Handle_WaitObject(*(p))
*/

typedef
  unsigned
  THREAD_FUNC_RET_TYPE;

#define THREAD_FUNC_CALL_TYPE MY_STD_CALL
#define THREAD_FUNC_DECL THREAD_FUNC_RET_TYPE THREAD_FUNC_CALL_TYPE
typedef THREAD_FUNC_RET_TYPE (THREAD_FUNC_CALL_TYPE * THREAD_FUNC_TYPE)(void *);
WRes Thread_Create(CThread *p, THREAD_FUNC_TYPE func, void* param);
WRes Thread_Close(CThread *p);
WRes Thread_Wait(CThread *p);

typedef event_t* CEvent;
typedef CEvent CAutoResetEvent;
typedef CEvent CManualResetEvent;
#define Event_Construct(p) *(p) = NULL
#define Event_IsCreated(p) (*(p) != NULL)
/*
#define Event_Close(p) HandlePtr_Close(p)
#define Event_Wait(p) Handle_WaitObject(*(p))
*/
WRes Event_Set(CEvent *p);
WRes Event_Reset(CEvent *p);
WRes ManualResetEvent_Create(CManualResetEvent *p, int signaled);
WRes ManualResetEvent_CreateNotSignaled(CManualResetEvent *p);
WRes AutoResetEvent_Create(CAutoResetEvent *p, int signaled);
WRes AutoResetEvent_CreateNotSignaled(CAutoResetEvent *p);
WRes Event_Close(CEvent *p);
WRes Event_Wait(CEvent *p);

typedef sem_t* CSemaphore;
#define Semaphore_Construct(p) *(p) = NULL
#define Semaphore_IsCreated(p) (*(p) != NULL)
/*
#define Semaphore_Close(p) HandlePtr_Close(p)
#define Semaphore_Wait(p) Handle_WaitObject(*(p))
*/
WRes Semaphore_Create(CSemaphore *p, UInt32 initCount, UInt32 maxCount);
WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 num);
WRes Semaphore_Release1(CSemaphore *p);
WRes Semaphore_Close(CSemaphore *p);
WRes Semaphore_Wait(CSemaphore *p);

typedef pthread_mutex_t* CCriticalSection;
WRes CriticalSection_Init(CCriticalSection *p);
/*
#define CriticalSection_Delete(p) DeleteCriticalSection(p)
#define CriticalSection_Enter(p) EnterCriticalSection(p)
#define CriticalSection_Leave(p) LeaveCriticalSection(p)
*/

WRes CriticalSection_Delete(CCriticalSection *p);
WRes CriticalSection_Enter(CCriticalSection *p);
WRes CriticalSection_Leave(CCriticalSection *p);

EXTERN_C_END

#endif
