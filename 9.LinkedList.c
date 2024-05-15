#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "predefined.h" /* Do not delete this line. Do not define predefined types and functions yourself. */

void printList (node_t *head);
node_t * insertHead (node_t *head, float re, float im);
node_t *insertTail (node_t *head, float re, float im);
node_t *removeFirst (node_t *head);
node_t *removeLast (node_t *head);
float distance (float re1, float im1, float re2, float im2);
node_t *findClosest (node_t *head, float re, float im);
node_t *insertAfterClosest (node_t *head, float re, float im);
node_t *insertBeforeClosest (node_t *head, float re, float im);
void printListReverse (node_t *head);
node_t *removeClosest (node_t *head, float re, float im);
 
int main (void)
{
  char cmd;
  node_t* list = {NULL};
 float re = 0, im = 0;
 node_t* pointer = NULL;
  while(1){
      printf("Command? ");
      scanf(" %c", &cmd);
      switch(cmd){
          case 'r':
           printf("re, im? ");
          scanf(" %f %f", &re, &im);
          if(list != NULL){
             list = removeClosest(list, re, im);
          }
          break;
          case 'v':
          printf("[");
          printListReverse(list);
          printf("]\n");
          break;
          case 'b':
           printf("re, im? ");
          scanf(" %f %f", &re, &im);
          if(list == NULL){
             list = insertHead(list, re, im);
          }else{
             list =  insertBeforeClosest(list, re, im);
          }
          break;
          case 'a':
          printf("re, im? ");
          scanf(" %f %f", &re, &im);
          if(list == NULL){
             list = insertHead(list, re, im);
          }else{
             list =  insertAfterClosest(list, re, im);
          }
          break;
          case 'c':
           printf("re, im? ");
          scanf(" %f %f", &re, &im);
             pointer = findClosest(list, re, im);
            if(pointer == NULL){
                printf("No closest number found\n");
            }else{
                printf("Closest number is ");
                printf("%.2f", pointer->re);
                if(pointer->im >= 0) printf("+");
                printf("%.2fi\n", pointer->im);
            }
          break;
          case 'l':
          list = removeLast(list);
          break;
          case 'f':
          list = removeFirst(list);
          break;
          case 't':
         printf("re, im? ");
          scanf(" %f %f", &re, &im);
         list = insertTail(list, re, im);
          break;
          case 'h':
          printf("re, im? ");
          scanf(" %f %f", &re, &im);
         list = insertHead(list, re, im);
          break;
          case 'p':
          printList(list);
          break;
          case 'q':
          printf("Bye!\n");
          while (list != NULL) list = removeFirst(list);
          return 0;
          break;
          default:
          printf("Unknown command '%c'\n", cmd);
          break;
      }
  }
}


void printList (node_t *head){
    printf("[");
    node_t* mark = head;
    while(mark != NULL){
        printf("%.2f", mark->re);
        if(mark->im >= 0){
            printf("+");
        }
        printf("%.2fi", mark->im);
        if(mark->next == NULL){
            break;
        }
        printf(",");
        mark = mark->next;
    }
    printf("]\n");
}

node_t * insertHead (node_t *head, float re, float im){
    node_t* newHead = (node_t *)malloc(sizeof(node_t));
   newHead->re = re;
   newHead->im = im;
   newHead->next = head;
   return newHead;
}


node_t *insertTail (node_t *head, float re, float im){
   node_t* new_node = (node_t *)malloc(sizeof(node_t));
   node_t* last = head;
   new_node->re = re;
   new_node->im = im;
   new_node->next = NULL;
   if(head == NULL){
       head = new_node;
   }else{
   while(last->next != NULL){
       last = last->next;
   }
   last->next = new_node;
    
}
    return head;
}


node_t *removeFirst (node_t *head){
    if(head == NULL){
        return head;
    }
    node_t* new_node = head->next;
    free(head);
    return new_node;
}

node_t *removeLast (node_t *head){
   node_t* curr = head;

   if(head == NULL){
      return head;
   }else if(head->next == NULL){
        free(head);
        head = NULL;
        return head;
   }else{
   while(curr->next->next!= NULL){
    
       curr = curr->next;
   }
   
        free(curr->next);
        curr->next = NULL;
   } 

    return head;
}



float distance (float re1, float im1, float re2, float im2){
    float distance = sqrt(powf(re1-re2, 2) +powf(im1-im2, 2));
    return distance;
}

node_t *findClosest (node_t *head, float re, float im){

    float minim = 100000;
    node_t* min = NULL;
    while(head != NULL){
        float dist = distance(re, im, head->re, head->im);
        if(dist < minim){
            minim = dist;
            min = head;
        }
        head = head->next;
    }
    return min;
}


node_t *insertAfterClosest (node_t *head, float re, float im){
    node_t* closest = findClosest(head, re, im);
    
    if(closest->next == NULL){
        head = insertTail(head, re, im);
    }else{
        // we replace the next number with the new one that points at the old one
        closest->next = insertHead(closest->next, re, im);
    }
    return head;
}


node_t *insertBeforeClosest (node_t *head, float re, float im){
        node_t* closest = findClosest(head, re, im);
        node_t* head_ref = head;
        if(head == closest){ // if th closest is in first position
            head = insertHead(head, re, im);
        }else {
            while(head_ref != NULL){
                // we search for the closest number
                if(head_ref->next == closest){
                    closest = insertHead(closest, re, im);
                    head_ref->next = closest;
                    // we add it before the closest number and break
                    break;
                }
                head_ref = head_ref -> next;
            }
        }
        return head;
}


void printListReverse (node_t *head){
   if (head == NULL)
       return;
    
    // the function prints the elemtents from last to first
    printListReverse(head->next);
    if(head->next != NULL){
        printf(",");
    } 
    // we print a number if the number is not the last thus the new first number
    // we get here if we get to a NULL element and start printing from last to first
   
    printf("%.2f", head->re);
    if(head->im >= 0){
        printf("+");
    }
    printf("%.2fi", head->im);
    // because we print the comma before a number we don't have a comma after last number
}


node_t* removeClosest(node_t* head, float re, float im) {
    node_t* closest = findClosest(head, re, im);

    if (closest == head) {
        head = removeFirst(head);
        return head;
    } else if (closest->next == NULL) {
        head = removeLast(head);
        return head;
    } else {
        node_t* head_ref = head;
        while (head_ref != NULL) {
            if (head_ref->next == closest) {
                node_t* closest_ref = closest->next;
                head_ref->next = closest_ref;
                free(closest); // Free memory of the removed node
                break; // No need to continue searching
            }
            head_ref = head_ref->next;
        }
    }

    return head;
}

