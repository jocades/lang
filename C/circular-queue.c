#include <stdio.h>
#include <stdlib.h>

#define CAP 3

typedef struct {
  int data[CAP];
  int* front;
  int* back;
} Queue;

void init(Queue* q) {
  q->front = q->back = q->data;
}

void enq(Queue* q, int v) {
  *q->back++ = v;
}

int deq(Queue* q) {
  return *q->front++;
}

int peek(Queue* q) {
  return *q->front;
}

void debug(Queue* q) {
  printf("Queue(front=%p, back=%p, len=%zu)\n", q->front, q->back, q->back - q->front);
}

int main() {
  int buf[3] = {2, 4, 8};
  int* p = buf;
  printf("p = %d %p\n", *p, p);

  p = (p + 1);
  printf("p = %d %p\n", *p, p);

  /* for (int i = 0; i < 3; i++) { */
  /*   printf("%d = %d %p\n", i, buf[i], &buf[i]); */
  /* } */

  /* Queue q;
  init(&q);

  enq(&q, 1);
  enq(&q, 2);
  debug(&q);
  printf("len=%ld\n", labs(q.front - q.back));

  printf("peek = %d\n", peek(&q));

  int a = deq(&q);
  printf("a = %d\n", a);
  debug(&q);

  int b = deq(&q);
  printf("b = %d\n", b);
  debug(&q); */

  return 0;
}
