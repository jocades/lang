#include <stdio.h>
#include <stdlib.h>

#define CAP 3

typedef struct {
  int data[CAP];
  int len;
  int front;
  int back;
} Queue;

void enq(Queue* q, int v) {
  if (q->len >= CAP) {
    printf("out of space\n");
    exit(1);
  }
  q->data[q->back] = v;
  q->back = (q->back + 1) % CAP;
  q->len++;
}

int deq(Queue* q) {
  if (q->len != 0) {
    int v = q->data[q->front];
    q->data[q->front] = 0;
    q->front = (q->front + 1) % CAP;
    q->len--;
    return v;
  }
  return -1;
}

int peek(Queue* q) {
  return q->data[q->front];
}

void debug(Queue* q) {
  printf("Queue(front=%d, back=%d, len=%d)\n", q->front, q->back, q->len);
}

int main() {
  Queue q = {0};

  enq(&q, 1);
  debug(&q);

  enq(&q, 2);
  debug(&q);

  enq(&q, 3);
  debug(&q);

  int a = deq(&q);
  printf("a = %d\n", a);
  debug(&q);

  int b = deq(&q);
  printf("b = %d\n", b);
  debug(&q);

  enq(&q, 4);
  debug(&q);

  enq(&q, 5);
  debug(&q);

  enq(&q, 6);
  debug(&q);

  return 0;
}
