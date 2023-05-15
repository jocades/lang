#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
} Node;

void print_list(Node *head) {
  Node *current = head;

  while (current != NULL) {
    printf("%d\n", current->val);
    current = current->next;
  }
}

void print_recursive(Node *head) {
  if (head == NULL)
    return;

  printf("%d\n", head->val);
  print_recursive(head->next);
}

/*
 The best use cases for linked lists are stacks and queues.
A stack is a data structure that stores a collection of elements and follows the
LIFO (last in, first out) principle. The last element added to the stack will be
the first element removed from the stack. A queue is a data structure that
stores a collection of elements and follows the FIFO (first in, first out)
principle. The first element added to the queue will be the first element
removed from the queue. Both stacks and queues can be implemented using linked
lists.
*/

// Add an item to the end of the list
void append(Node *head, int val) {
  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  // now we can add a new variable
  current->next = (Node *)malloc(sizeof(Node));
  current->next->val = val;
  current->next->next = NULL;
}

/* Adding an item to the beginning of the list is a bit more tricky.
To add to the beginning of the list, we will need to do the following:

1- Create a new item and set its value
2- Link the new item to point to the head of the list
3- Set the head of the list to be our new item

This will effectively create a new head to the list with a new value, and keep
the rest of the list linked to it.

Since we use a function to do this operation, we want to be able to modify the
head variable. To do this, we must pass a pointer to the pointer variable (a
double pointer) so we will be able to modify the pointer itself.
*/

void prepend(Node **head, int val) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->val = val;
  new_node->next = *head;
  *head = new_node;
}

/*
Removing the first item
To pop a variable, we will need to reverse this action:

Take the next item that the head points to and save it
Free the head item
Set the head to be the next item that we've stored on the side
*/

int remove_first(Node **head) {
  int retval = -1;
  Node *next_node = NULL;

  if (*head == NULL) {
    return -1;
  }

  next_node = (*head)->next;
  retval = (*head)->val;
  free(*head);
  *head = next_node;

  return retval;
}

/*
Removing the last item
*/

int pop(Node *head) {
  int retval = 0;
  // if there is only one item in the list, remove it
  if (head->next == NULL) {
    retval = head->val;
    free(head);
    return retval;
  }

  // get the second to last node in the list
  Node *current = head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  // now current points to the second to last item of the list, so let's remove
  // current->next
  retval = current->next->val;
  free(current->next);
  current->next = NULL;
  return retval;
}

/*
Removing a specific item
To remove a specific item from the list, either by its index from the beginning
of the list or by its value, we will need to go over all the items, continuously
looking ahead to find out if we've reached the node before the item we wish to
remove. This is because we need to change the location to where the previous
node points to as well.

Here is the algorithm:

1- Iterate to the node before the node we wish to delete
2- Save the node we wish to delete in a temporary pointer
3- Set the previous node's next pointer to point to the node after the node we
wish to delete
4- Delete the node using the temporary pointer

There are a few edge cases we need to take care of, so make sure you understand
the code.
*/

int remove_by_index(Node **head, int n) {
  int retval = -1;
  Node *current = *head;
  Node *temp_node = NULL;

  if (n == 0) {
    return remove_first(head);
  }

  for (int i = 0; i < n - 1; i++) {
    if (current->next == NULL) {
      return -1;
    }
    current = current->next;
  }

  if (current->next == NULL) {
    return -1;
  }

  temp_node = current->next;
  retval = temp_node->val;
  current->next = temp_node->next;
  free(temp_node);

  return retval;
}

int remove_by_value_try(Node **head, int val) {
  int retval = -1;
  Node *current = *head;
  Node *temp = NULL;

  while (current->val != val) {
    if (current->next == NULL) {
      return -1;
    }
    current = current->next;
  }

  temp = current->next;
  retval = temp->val;
  current->next = temp->next;
  free(temp);

  return retval;
}

int remove_by_value(Node **head, int val) {
  Node *prev, *current;

  if (*head == NULL) {
    return -1;
  }

  if ((*head)->val == val) {
    return remove_first(head);
  }

  prev = *head;
  current = (*head)->next;
  while (current) {
    if (current->val == val) {
      prev->next = current->next;
      free(current);
      return val;
    }

    prev = current;
    current = current->next;
  }

  return -1;
}

int main() {
  Node *head = (Node *)malloc(sizeof(Node));
  if (head == NULL)
    return 1;

  head->val = 1;
  head->next = (Node *)malloc(sizeof(Node));
  head->next->val = 2;
  head->next->next = NULL;

  print_list(head);
  print_recursive(head);

  printf("Appending node...\n");
  append(head, 3);
  print_list(head);

  printf("Prepending node...\n");
  prepend(&head, 0);
  print_list(head);

  printf("Removed %d\n", remove_first(&head));
  print_list(head);

  printf("Removed %d\n", pop(head));
  print_list(head);

  // printf("Remove by index, value: %d\n", remove_by_index(&head, 1));
  // print_list(head);

  printf("Remove by value, value: %d\n", remove_by_value(&head, 1));
  print_list(head);

  return 0;
}
