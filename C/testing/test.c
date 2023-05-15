#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
} Node;

void print_list(Node *head) {
  if (head == NULL) {
    return;
  }

  printf("%d\n", head->val);
  print_list(head->next);
}

void append(Node *head, int val) {
  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->val = val;
  new_node->next = NULL;
  current->next = new_node;
}

void prepend(Node **head, int val) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->val = val;
  new_node->next = *head;
  *head = new_node;
}

int rm_first(Node **head) {
  int retval = -1;

  Node *next_node = (*head)->next;
  retval = (*head)->val;
  free(*head);
  *head = next_node;

  return retval;
}

int pop(Node *head) {
  int retval = 0;

  // if only one item remove it
  if (head->next == NULL) {
    retval = head->val;
    free(head);
    return retval;
  }

  // get the second last item (penultimo)
  Node *current = head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  retval = current->next->val;
  free(current->next);
  current->next = NULL;

  return retval;
}

int main() {
  Node *head = NULL;
  int N = 2;
  for (int i = N; i > 0; i--) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->val = i;
    new_node->next = head;
    head = new_node;
  }
  print_list(head);

  printf("Appending..\n");
  append(head, 4);
  print_list(head);

  printf("Preppending..\n");
  prepend(&head, -1);
  print_list(head);

  int first_val = rm_first(&head);
  printf("Rm first, value: %d\n", first_val);
  print_list(head);

  int last_val = pop(head);
  printf("Pop, value: %d\n", last_val);
  print_list(head);

  /* int arr[] = {1, 2, 3};
  printf("Variable &arr%p\n", &arr);
  printf("Variable arr%p\n", arr);
  printf("&arr[0]: %p", &arr[0]);

  for (int i = 0; i < 3; i++) {
    printf("%d\n", arr[i]);
    printf("%d\n", (*arr) + i);
    printf("%p\n", &arr + i);
  } */

  return 0;
}
