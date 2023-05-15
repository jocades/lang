#include <stdio.h>
#include <stdlib.h>

// a struct is just a collection of data types that are grouped together under
// one name (like a class in OOP)

typedef struct node {
  int value;
  struct node *next;
} Node;

Node *create_node(int value) {
  // allocate mem for the node on the heap
  // malloc returns a void pointer (void*) which is a generic pointer type
  // (Node*) is a type cast (converts the return value of malloc to a Node
  // pointer
  Node *new_node = (Node *)malloc(sizeof(Node));
  // new_node->value is the same as (*new_node).value
  // which accesses the 'value' field of the node struct and assigns it the
  // value passed to the function
  new_node->value = value;
  // set the 'next' field to NULL
  new_node->next = NULL;

  return new_node;
}

// (Node**) is a pointer to a pointer to a Node which means that it is a pointer
// to a memory address that stores a pointer to a Node
//
void insert_node(Node **head_ref, int value) {
  // create a new node
  Node *new_node = create_node(value);

  // insert the new node at the beginning of the list
  new_node->next = *head_ref;
  // set the head pointer to the new node
  *head_ref = new_node;
}

void print_list(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("\n");
}

int main() {
  Node *head = NULL;

  // add nodes to the list
  insert_node(&head, 2);
  insert_node(&head, 3);
  insert_node(&head, 1);

  // for (int i = 0; i < 5; i++) {
  //   insert_node(&head, i);
  // }

  // print the values in the list
  print_list(head);

  // free the memory allocated for the nodes
  Node *current = head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
