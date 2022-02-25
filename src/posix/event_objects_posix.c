#include "event_objects_posix.h"
#include <stdlib.h>
#include <sys/time.h>

void __attribute__((visibility ("hidden"))) AddElement(event_t event_object, list_element le)
{
  if (event_object->start == NULL)
    event_object->start = event_object->end = le;
  else
    {
      event_object->end->next = le;
      le->prev = event_object->end;
      event_object->end = le;
    }
}

void __attribute__((visibility ("hidden"))) RemoveElement(event_t event_object, list_element le)
{
  list_element ptr;

  if (event_object->start == event_object->end)
    event_object->start = event_object->end = NULL;
  else if (le == event_object->start)
    event_object->start = event_object->start->next;
  else if (le == event_object->end)
    event_object->end = event_object->end->prev;
  else
    for (ptr = event_object->start->next; ; ptr = ptr->next)
      if (ptr == le)
    {
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
      break;
    }
}


// attribute not used, name not used
// manual_reset is ignored, always treated as true
event_t __attribute__((visibility ("hidden"))) CreateEvent(void *attribute, BOOL manual_reset, BOOL initial_state, void *name)
{
  event_t event_object = malloc(sizeof (struct event_t));
  event_object->start = event_object->end = NULL;
  pthread_mutex_init(&event_object->mutex, NULL);
  event_object->flag = initial_state;
  return event_object;
}

BOOL __attribute__((visibility ("hidden"))) SetEvent(event_t event_object)
{
  list_element ptr;

  pthread_mutex_lock(&event_object->mutex);
  event_object->flag = TRUE;
  for (ptr = event_object->start; ptr != NULL; ptr = ptr->next)
    {
      pthread_mutex_lock(&ptr->mutex);
      pthread_cond_signal(&ptr->cond);
      pthread_mutex_unlock(&ptr->mutex);
      if (ptr == event_object->end)
    break;
    }
  pthread_mutex_unlock(&event_object->mutex);
  return TRUE;
}

BOOL __attribute__((visibility ("hidden"))) ResetEvent(event_t event_object)
{
  pthread_mutex_lock(&event_object->mutex);
  event_object->flag = FALSE;
  pthread_mutex_unlock(&event_object->mutex);
  return TRUE;
}

BOOL __attribute__((visibility ("hidden"))) CloseEvent(event_t event_object)
{
  if (event_object->start != NULL)
    return FALSE;
  pthread_mutex_destroy(&event_object->mutex);
  free(event_object);
  return TRUE;
}


DWORD __attribute__((visibility ("hidden"))) WaitForSingleObject(event_t event_object, int timeout_ms)
{
  return WaitForMultipleObjects(1, &event_object, FALSE, timeout_ms);
}

DWORD __attribute__((visibility ("hidden"))) WaitForMultipleObjects(DWORD count, event_t *event_object, BOOL wait_all, int timeout_ms)
{
  struct t_list_element le;
  DWORD i, return_value=0;
  int check_value = -1;
  struct timespec t;
  struct timeval tv;

  if (count == 0)
    return WAIT_FAILED;

  for (i = 0; i < count; ++i)
    pthread_mutex_lock(&event_object[i]->mutex);

  pthread_mutex_init(&le.mutex, NULL);
  pthread_cond_init(&le.cond, NULL);

  for (i = 0; i < count; ++i)
    {
      AddElement(event_object[i], &le);
      if (event_object[i]->flag)
        check_value = 1;
    }

  if (check_value == -1)
    {
      pthread_mutex_lock(&le.mutex);

      if (timeout_ms != INFINITE)
        {
          gettimeofday(&tv,NULL); //tell me here if some systems have 1 arg gettimeofday
          t.tv_nsec = tv.tv_usec * 1000  + ((long) timeout_ms) * MIL;
          t.tv_sec = tv.tv_sec;
          if (t.tv_nsec >= BIL)
            {
              t.tv_sec += t.tv_nsec / BIL;
              t.tv_nsec %= BIL;
            }
        }

      for (i = 0; i < count; ++i)
        pthread_mutex_unlock(&event_object[i]->mutex);

      if (timeout_ms == INFINITE)
        check_value = pthread_cond_wait(&le.cond, &le.mutex);
      else
        check_value = pthread_cond_timedwait(&le.cond, &le.mutex, &t);
      if (check_value == ETIMEDOUT)
        return_value = WAIT_TIMEOUT;
      else if (check_value != 0)
        return_value = WAIT_FAILED;

      pthread_mutex_unlock(&le.mutex);

      for (i = 0; i < count; ++i)
        pthread_mutex_lock(&event_object[i]->mutex);
    }

  for (i = 0; i < count; ++i)
    {
      RemoveElement(event_object[i], &le);
      if (event_object[i]->flag)
        return_value = i;
    }

  for (i = 0; i < count; ++i)
    pthread_mutex_unlock(&event_object[i]->mutex);

  pthread_mutex_destroy(&le.mutex);
  pthread_cond_destroy(&le.cond);

  return return_value;
}

