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
  return 0;
}

int my_spinlock_destroy(my_spinlock_t *lock)
{
  
}

int my_spinlock_unlock(my_spinlock_t *lock)
{
  lock->lock_bit = 0;
  return 0;
}

int my_spinlock_lockTAS(my_spinlock_t *lock)
{
  while(1){
    printf("before lock bit is %lu \n",lock->lock_bit);
    if(tas(lock->lock_bit)==0){
      lock->lock_bit = 1;
      printf("after lock bit is %lu \n",lock->lock_bit);
      lock->thread_ID = pthread_self();
      break;
    }
  }
  return 0;
}


int my_spinlock_lockTTAS(my_spinlock_t *lock)
{
}

int my_spinlock_trylock(my_spinlock_t *lock)
{
}


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *lock)
{
}

int my_mutex_destroy(my_mutex_t *lock)
{
}

int my_mutex_unlock(my_mutex_t *lock)
{
}

int my_mutex_lock(my_mutex_t *lock)
{
}

int my_mutex_trylock(my_mutex_t *lock)
{
}

/*
 * Queue Lock
 */

int my_queuelock_init(my_queuelock_t *lock)
{
}

int my_queuelock_destroy(my_queuelock_t *lock)
{
}

int my_queuelock_unlock(my_queuelock_t *lock)
{
}

int my_queuelock_lock(my_queuelock_t *lock)
{
}

int my_queuelock_trylock(my_queuelock_t *lock)
{
}
