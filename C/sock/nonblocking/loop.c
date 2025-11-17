#include <err.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <time.h>

#define MAX_EVENTS 64
#define SHUTDOWN_IDENT 1

typedef struct {
  int kq;
  bool shutdown;
  int active_events;
  pthread_t thread;
  pthread_mutex_t lock;
} loop_t;

typedef enum {
  KIND_TIMER,
  KIND_IO,
} event_kind_t;

typedef struct event_t {
  int ident;
  int flags;

  loop_t* loop;
  void (*handler)(struct event_t* ev);
} event_t;

typedef void (*timer_cb_t)(void* arg);
typedef struct {
  event_t ev;
  timer_cb_t cb;
  void* arg;
} timer_t;

void loop_trigger_shutdown(loop_t* l) {
  printf("register shutdown\n");
  struct kevent ev;
  EV_SET(&ev, SHUTDOWN_IDENT, EVFILT_USER, 0, NOTE_TRIGGER, 0, NULL);
  kevent(l->kq, &ev, 1, NULL, 0, NULL);
}

#define is_shutdown(ev) (ev->filter == EVFILT_USER && ev->ident == SHUTDOWN_IDENT)

void* loop_run(void* arg) {
  loop_t* l = arg;
  struct kevent events[MAX_EVENTS];

  while (!l->shutdown) {
    int nev = kevent(l->kq, NULL, 0, events, MAX_EVENTS, NULL);
    if (nev == -1) err(EXIT_FAILURE, "kevent wait");

    printf("nev = %d\n", nev);

    for (int i = 0; i < nev; i++) {
      struct kevent* kev = &events[i];

      if (is_shutdown(kev)) {
        pthread_mutex_lock(&l->lock);
        l->shutdown = true;
        pthread_mutex_unlock(&l->lock);
        printf("event loop shutting down\n");
        break;
      }

      event_t* ev = kev->udata;
      if (!ev || !ev->handler) continue;

      ev->handler(ev);
      free(ev);

      pthread_mutex_lock(&l->lock);
      int pending = l->active_events -= 1;
      pthread_mutex_unlock(&l->lock);
      if (pending == 0) loop_trigger_shutdown(l);
    }
  }

  return NULL;
}

void loop_init(loop_t* l) {
  if ((l->kq = kqueue()) == -1) err(EXIT_FAILURE, "kq");
  l->shutdown = false;
  l->active_events = 0;
  pthread_mutex_init(&l->lock, NULL);

  struct kevent ev;
  EV_SET(&ev, SHUTDOWN_IDENT, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, NULL);
  kevent(l->kq, &ev, 1, NULL, 0, NULL);

  pthread_create(&l->thread, NULL, loop_run, l);
}

void handle_timer(event_t* ev) {
  timer_t* timer = (timer_t*)ev;
  timer->cb(timer->arg);
}

void start_timer(loop_t* l, int ms, timer_cb_t cb, void* arg) {
  timer_t* timer = malloc(sizeof(timer_t));
  timer->ev.loop = l;
  timer->ev.handler = handle_timer;
  timer->cb = cb;
  timer->arg = arg;

  struct kevent kev = {
    .ident = (uintptr_t)timer,
    .filter = EVFILT_TIMER,
    .flags = EV_ADD | EV_ONESHOT,
    .data = ms,
    .udata = timer,
  };
  /* EV_SET(&ev, ud->ident, EVFILT_TIMER, EV_ADD | EV_ONESHOT, 0, ms, ud); */

  pthread_mutex_lock(&l->lock);
  l->active_events += 1;
  pthread_mutex_unlock(&l->lock);

  printf("register timer(%d)\n", ms);
  if (kevent(l->kq, &kev, 1, NULL, 0, NULL) == -1) {
    err(EXIT_FAILURE, "failed to register timer");
  }
}

void timer_cb(void* arg) {
  printf("Timer fired! Message: %s\n", (char*)arg);
}

void shutdown_after(void* arg) {
  loop_t* l = (loop_t*)arg;
  loop_trigger_shutdown(l);
}

int main() {
  loop_t loop;
  loop_init(&loop);

  start_timer(&loop, 2000, timer_cb, "hello after 2s");
  start_timer(&loop, 4000, timer_cb, "hello after 4s");

  pthread_join(loop.thread, NULL);
  return 0;
}
