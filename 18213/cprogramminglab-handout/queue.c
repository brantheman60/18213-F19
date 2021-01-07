/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL) return NULL;
    q->head = NULL;
    q->tail = q->head;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q==NULL) return;
    list_ele_t *h1 = q->head;
    if(h1==NULL)
    {
      free(q);
      return;
    }

    list_ele_t *h2 = q->head->next;
    while(h2!=NULL) // for(int i=0; i<q->size; i++)
    {
      free(h1->value);
      free(h1);
      h1 = h2;
      h2 = h2->next;
    }
    //for last element
    free(h1->value);
    free(h1);
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if(q==NULL) return false;

    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL) return false;

    int count = 1, index = 0;
    while(s[index]!='\0')
    {
      count++; index++;
    }

    char *str = malloc(count);
    if(str == NULL) {free(newh); return false;}
    index = 0;
    while(s[index]!='\0')
    {
      str[index] = s[index];
      index++;
    }

    str[index] = '\0';
    newh->value = str;

    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if(q->size == 1) q->tail = newh;

    //printf("Current head: %s\n", q->head->value);
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;

    if(q==NULL) return false;
    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL) return false;

    int count = 1, index = 0;
    while(s[index]!='\0')
    {
      count++; index++;
    }

    char *str = malloc(count);
    if(str == NULL) {free(newh); return false;}
    index = 0;
    while(s[index]!='\0')
    {
      str[index] = s[index];
      index++;
    }

    str[index] = '\0';
    newh->value = str;
    newh->next = NULL;

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if(q->tail==NULL) q->tail = newh;
    else {q->tail->next = newh; q->tail = newh;}
    q->size++;
    if(q->size == 1) q->head = newh;

    //printf("Current tail: %s\n", q->tail->value);
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q==NULL) return false;
    list_ele_t *h = q->head;
    if(h==NULL) return false;
    if(sp==NULL)
    {
      free(h->value);
      q->head = q->head->next;
      free(h);
      q->size--;
      return true;
    }

    int index = 0;
    while(index<bufsize-1)
    {
      if(h->value[index]=='\0') break;
      sp[index] = h->value[index];
      index++;
    }
    sp[index] = '\0';
    free(h->value);

    q->head = q->head->next;
    free(h);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q==NULL) return 0;
    if(q->head==NULL) return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */

void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(q==NULL) return;
    if(q->head==NULL) return;

    list_ele_t *h0 = NULL; //list element before head
    list_ele_t *h1 = q->head; //head
    list_ele_t *h2 = q->head->next; //list element after head

    q->tail = h1;
    while(h2!=NULL) // for(int i=0; i<q->size; i++)
    {
      h1->next = h0;
      h0 = h1;
      h1 = h2;
      h2 = h2->next;
    }
    //for final element
    h1->next = h0;
    q->head = h1;
}
