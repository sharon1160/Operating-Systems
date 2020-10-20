#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_attr_t attr;

void* function(void* arg) {
  printf( "This is thread %d, PID \n", (int) pthread_self(),getpid() );
  sleep(5);
  return (void *)99;
}
int main(void) {
  pthread_t t2;
  void *result;
  pthread_attr_init( &attr );
  //pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  pthread_create( &t2, &attr, function, NULL );
  pthread_join(t2,&result);
  printf("Thread t2 returned %d\n", (int) result);
  return 0;
}
