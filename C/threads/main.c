#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 8
#define ITER 10000000

typedef struct {
  int count;
  pthread_mutex_t mutex;
} State;

void *task(void *arg) {
  pthread_t tid = pthread_self();
  State *state = (State *)arg;

  printf("%p before increment: %d\n", tid, state->count);
  for (int i = 0; i < ITER; i++) {
    state->count++;
  }
  printf("%p after increment: %d\n", tid, state->count);

  return NULL;
}

void *safe_task(void *arg) {
  pthread_t tid = pthread_self();
  State *state = (State *)arg;

  pthread_mutex_lock(&state->mutex);
  printf("%p before increment: %d\n", tid, state->count);
  pthread_mutex_unlock(&state->mutex);

  for (int i = 0; i < ITER; i++) {
    pthread_mutex_lock(&state->mutex);
    state->count++;
    pthread_mutex_unlock(&state->mutex);
  }

  pthread_mutex_lock(&state->mutex);
  printf("%p after increment: %d\n", tid, state->count);
  pthread_mutex_unlock(&state->mutex);

  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];

  State state = {0};
  pthread_mutex_init(&state.mutex, NULL);

  int error;
  for (int i = 0; i < NUM_THREADS; i++) {
    error = pthread_create(&threads[i], NULL, safe_task, &state);
    if (error != 0) {
      printf("failed to create thread %d: %s\n", i, strerror(error));
    }
  }
  printf("spawned %d threads\n", NUM_THREADS);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    printf("%p joined\n", threads[i]);
  }
  pthread_mutex_destroy(&state.mutex);

  int expected = NUM_THREADS * ITER;
  int code = state.count == expected ? 0 : 1;
  printf("expected: %d got: %d\n", expected, state.count);

  return code;
}
