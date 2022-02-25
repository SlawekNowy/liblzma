// by Lars Melander
//from http://win32eoposix.sourceforge.net
// with modifications




#define DWORD            unsigned int
#define BOOL             int

#define INFINITE         -1     // usually set to -1
#define WAIT_OBJECT_0    0      // usually set to 0
#define WAIT_TIMEOUT     64     // arbitrary number
#define WAIT_FAILED      96     //       -"-
#define WAIT_ABANDONED_0 128    //       -"-

#define FALSE 0
#define TRUE 1

#define MIL 1000000L            // one million
#define BIL 1000000000L         // one billion
#ifndef ETIMEDOUT
#define ETIMEDOUT 110
#endif

#include <pthread.h>
typedef struct t_list_element
{
  pthread_mutex_t mutex;  // mutex for the conditional wait
  pthread_cond_t cond;
  struct t_list_element *prev, *next;
} *list_element;


typedef struct _event_t
{
  list_element start, end;
  pthread_mutex_t mutex;
  BOOL flag;
} *event_t;

void AddElement(event_t event_object, list_element le);
void RemoveElement(event_t event_object, list_element le);


event_t CreateEvent(void *attribute, BOOL manual_reset, BOOL initial_state, void *name);
BOOL SetEvent(event_t event_object);
BOOL ResetEvent(event_t event_object);
BOOL CloseEvent(event_t event_object);


DWORD WaitForSingleObject(event_t event_object, int timeout_ms);
DWORD WaitForMultipleObjects(DWORD count, event_t *event_object, BOOL wait_all, int timeout_ms);
