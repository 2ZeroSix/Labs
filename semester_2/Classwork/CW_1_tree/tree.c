#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// дерево
typedef struct _tree{
  int value;
  struct _tree* left;
  struct _tree* right;
}tree;

// очередь
typedef struct _stack {
  tree* value;
  struct _stack* next;
}stack;

// работа с очередью
static stack* temp_stack = NULL;
void add(tree* head) {
  if (temp_stack){
    stack* cur = temp_stack;
    stack* new = (stack*)calloc(1, sizeof(stack));
    new->value = head;
    while(cur->next) {
      cur = cur->next;
    }
    cur->next = new;
  }
  else {
    temp_stack = (stack*)calloc(1, sizeof(stack));
    temp_stack->value = head;
  }
  return;
}
tree* del() {
  tree* temp = temp_stack->value;
  stack* delete = temp_stack;
  temp_stack = temp_stack->next;
  free(delete);
  return temp;
}
char empty() {
  return temp_stack ? 0 : 1;
}

// работа с деревом
tree* push_in_tree(tree* head, int element){
  tree* new = (tree*)calloc(1, sizeof(tree));
  new->value = element;
  if (head) {
    tree* cur = head;
    char go = 1;
    while(go) {
      if (cur->value > element) {
        if (cur->left) {
          cur = cur->left;
        }
        else {
          cur->left = new;
          go = 0;
        }
      }
      else {
        if (cur->right) {
          cur = cur->right;
        }
        else {
          cur->right = new;
          go = 0;
        }
      }
    }
  }
  else {
    head = new;
  }
  return head;
}
void width_print(FILE* output, tree* head) {
    if (!head)
        return;
    add(head);
    while (!empty()) {
        tree *curr = del();
        fprintf(output, "%d ", curr->value);
        if (curr->left)
            add(curr->left);
        if (curr->right)
            add(curr->right);
    }
}
void depth_print(FILE* output, tree* head) {
  if (!head) {
    return;
  }
  fprintf(output, "%d ", head->value);
  depth_print(output, head->left);
  depth_print(output, head->right);
}
void width_free(tree* head) {
    if (!head)
        return;
    add(head);
    while (!empty()) {
        tree *curr = del();
        if (curr->left)
            add(curr->left);
        if (curr->right)
            add(curr->right);
        free(curr);
    }
}
void readtree(FILE* input, tree** head) {
  int numb;
  while(!feof(input)) {
    fscanf(input, "%d", &numb);
    *head = push_in_tree(*head, numb);
  }
}

int main() {
  tree* head = NULL;
  FILE* input = fopen("test_in.txt", "r");
  readtree(input, &head);
  fclose(input);
  printf("Width:\n");
  width_print(stdout, head);
  printf("\nDepth: \n");
  depth_print(stdout, head);
  width_free(head);
  return 0;
}
