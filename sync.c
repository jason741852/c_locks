/*
 * NAME, etc.
 *
 * sync.c
 *
 */

#define _REENTRANT

#include "sync.h"


/*
 * Spinlock routines
 */

int my_spinlock_init(my_spinlock_t *lock)
{
  lock->lock_bit = 0;
  lock->thread_ID = 0;
  lock->recursive_counter = 0;
  return 0;
}

int my_spinlock_destroy(my_spinlock_t *lock)
{
  if(lock->lock_bit == 0)
  {
    return 0;
  }
  else  return -1;
}

int my_spinlock_unlock(my_spinlock_t *lock)
{
  if(lock->recursive_counter == 1 || lock->recursive_counter ==  0){
    lock->lock_bit = 0;
    lock->thread_ID = 0;
    lock->recursive_counter = 0;
  }
  else{
    lock->recursive_counter = lock->recursive_counter - 1;
  }
  return 0;

}

int my_spinlock_lockTAS(my_spinlock_t *lock)
{
    while(tas(&(lock->lock_bit))==1 && lock->thread_ID != pthread_self()){}
    if(lock->thread_ID == pthread_self()) lock->recursive_counter++;
    lock->thread_ID = pthread_self();

  return 0;
}


int my_spinlock_lockTTAS(my_spinlock_t *lock)
{
  // while(1){
  //   while(lock->lock_bit==1){}; // spin until lock_bit == 0
  //   if(tas(&(lock->lock_bit))==0){
  //     lock->thread_ID = pthread_self();
  //     return 0;
  //   }
  //
  // }
  while(1){
    while(lock->lock_bit==1 && lock->thread_ID != pthread_self()){}; // spin until lock_bit == 0
    if(tas(&(lock->lock_bit))==0){
      lock->thread_ID = pthread_self();
      return 0;
    }
    else if(lock->thread_ID == pthread_self()){
      lock->recursive_counter++;
      return 0;
    }
  }
}

int my_spinlock_trylock(my_spinlock_t *lock)
{
  if(tas(&(lock->lock_bit))==0){
    lock->lock_bit = 0;
    lock->thread_ID = pthread_self();
    return 0;
  }
  else return -1;
}


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *lock)
{
  lock->lock_bit = 0;
  lock->thread_ID = 0;
  lock->recursive_counter = 0;
  return 0;
}

int my_mutex_destroy(my_mutex_t *lock)
{
  if(lock->lock_bit == 0)
  {
    return 0;
  }
  else  return -1;
}

int my_mutex_unlock(my_mutex_t *lock)
{
  lock->lock_bit = 0;
  lock->thread_ID = 0;
  lock->recursive_counter = 0;
}

int my_mutex_lock(my_mutex_t *lock)
{
  int delay = MIN_DELAY;
  //printf("%i ",delay);
  while(1){
    while(lock->lock_bit==1){}; // spin until lock_bit == 0
    if(tas(&(lock->lock_bit))==0){
      lock->thread_ID = pthread_self();
      return 0;
    }
    usleep(rand() % delay);
    if(delay < MAX_DELAY) delay = 2*delay;
  }
}

int my_mutex_trylock(my_mutex_t *lock)
{
  if(tas(&(lock->lock_bit))==0){
    lock->lock_bit = 0;
    lock->thread_ID = pthread_self();
    return 0;
  }
  else return -1;
}

/*
 * Queue Lock
 */

int my_queuelock_init(my_queuelock_t *lock)
{
  lock->queue_Num = 0;
  lock->ticket_Num = 0;
  lock->thread_ID = 0;
  return 0;
}

int my_queuelock_destroy(my_queuelock_t *lock)
{
  if(lock->queue_Num == lock->ticket_Num) return 0;
  else return -1;
}

int my_queuelock_unlock(my_queuelock_t *lock)
{
  lock->thread_ID = 0;
  lock->queue_Num = lock->queue_Num+1;
  return 0;
}

int my_queuelock_lock(my_queuelock_t *lock)
{
  unsigned long queue_Pos = fetch_and_add(&(lock->ticket_Num),1);
  while(1){
    while(queue_Pos != lock->queue_Num){}
    lock->thread_ID = pthread_self();
    return 0;
  }
}

int my_queuelock_trylock(my_queuelock_t *lock)
{
  unsigned long queue_Pos = fetch_and_add(&(lock->ticket_Num),1);
  if(queue_Pos == lock->queue_Num){
    lock->thread_ID = pthread_self();
    return 0;
  }
  else return -1;
}
