#include <stdio.h>
#include <stdlib.h>

/*
 Linked lists are the best simplest example of  a dynamic data structure that
 uses pointers for its implementation. A linked list is a collection of elements
 called nodes, where each node contains a value and a pointer to the next node
 in the list. Unlike arrays, linked lists do not store their elements
 contiguously in memory, but rather each node can be located anywhere in memory.
 This makes them more flexible than arrays because you can add or remove nodes
 from the list at runtime without having to reallocate memory for the entire
 list.
*/

// A node is a data structure that contains a value and a pointer to the next
// node in the list. The first node in the list is called the head and the last
// node is called the tail. The tail node points to NULL, which indicates the
// end of the list. The head node is used to locate the list in memory. To
// access the other nodes in the list, you need to start at the head and follow
// the pointers to the next node until you reach the end of the list.

typedef struct node {
  int value;
  struct node *next;
} Node;

// Keywords:
// - typedef: allows you to create a new name for a type
// - struct: allows you to create a new data type that is a collection of other
// data types
// - struct node: defines a new data type called node
// - struct node* next: defines a new data type called node pointer that points
// to a node struct
// - Node: defines a new name for the data type struct node

int main() {
  Node *head = NULL;

  // add nodes to the list
  for (int i = 0; i < 5; i++) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = i;
    new_node->next = head;
    head = new_node;
  }

  // print the values in the list
  Node *current = head;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }

  // free the memory allocated for the nodes
  current = head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
