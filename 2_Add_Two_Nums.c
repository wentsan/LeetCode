#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 20

struct ListNode{
  int val;
  struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{  
  int overDigit = 0;
  struct ListNode *first = NULL;
  struct ListNode *pre = NULL;

  while (l1 != NULL || l2 != NULL){
    int digit = 0;
    struct ListNode *result = malloc(sizeof(struct ListNode));
    
    if (l1 != NULL){
      digit += l1->val;
      l1 = l1->next;
    }
    if (l2 != NULL){
      digit += l2->val;
      l2 = l2->next;
    }

    digit += overDigit;
    overDigit = digit / 10;
    result->val = digit % 10;
    result->next = NULL;
    if (first == NULL)
      first = result;
    if (pre != NULL)
      pre->next = result;
    pre = result;
  }
  if (overDigit == 1){
    struct ListNode *o = malloc(sizeof(struct ListNode));
    o->val = 1;
    o->next = NULL;
    pre->next = o;
  }
  return first;
}

struct ListNode * input(struct ListNode *l, char c[]){
  int v = atoi(c);
  struct ListNode *pre = NULL;
  while (v) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = v % 10;
    node->next = NULL;
    if (pre != NULL)
      pre->next = node;
    pre = node;
    if (l == NULL)
      l = node;
    v /= 10;
  }
  return l;
}

void printList(struct ListNode *l, char *name){
  int i = 0;
  printf ("%s: ", name);
  while (l != NULL){
    if (i != 0)
      printf (" -> ");
    printf("%d", l->val);
    i++;
    l = l->next;
  }
  printf ("\n");
}

int main(int argc, char *argv[])
{
  struct ListNode *l1 = NULL;
  struct ListNode *l2 = NULL;
  
  for (int i = 0; i < 2; i++){
    char *s = (i == 0) ? "first" : "second";
    char c[MAXWORDS];
    
    printf ("Please enter the %s list:\n", s);
    fgets(c, MAXWORDS, stdin);
    if (i == 0)
      l1 = input(l1, c);
    else
      l2 = input(l2, c);
  }
  
  struct ListNode *p;
  p = addTwoNumbers(l1, l2);  

  printList(l1, "List_1");
  printList(l2, "List_2");
  printList(p,  "Result");
  
  return 0;
}
