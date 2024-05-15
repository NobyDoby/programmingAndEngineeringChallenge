#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct node{
    char * name;
    int height;
    struct node * next;
};
struct node *insertTail (struct node *ring, char *name, int height);
void printRing (struct node *ring);
void insertHead (struct node **ring, char *name, int height);
void swap (struct node **ring1, struct node **ring2);
void append (struct node **ring1, struct node **ring2);
int sumProduct (struct node *ring1, struct node *ring2);
int length (struct node *ring);
struct node *delete (struct node *ring, char *name, int height);
struct node * find_ring(struct node *ring,char *name, int height);
struct node *sort (struct node *ring);
struct node *max (struct node *ring);
struct node *rotateLeft (struct node *ring);
struct node *rotateRight(struct node *ring);
void reverse (struct node **ring);
int main (void)
{   
    struct node * ring1 = NULL;
    struct node *ring2 = NULL;
    struct node *maxim = NULL;
    char cmd ='\0';
    char  name[100] = "\0";
    int height;
    while(1){
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'v':
            reverse(&ring1);
            break;
            case 'm':
            maxim = max(ring1);
            if(maxim != NULL){
                printf("cel mai mare este %s %d\n", maxim->name, maxim->height);
            }
            break;
            case 'R':
            ring1 = rotateRight(ring1);
            break;
            case 'r':
            ring1 = rotateLeft(ring1);
            break;
            case 'o':
            ring1 = sort(ring1);
            break;
            case 'd':
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %d", &height);
            if(ring1 == NULL){
                printf("%s %d not in ring\n", name, height);
            }else{
            ring1 = delete(ring1, name, height);
            } 
            break;
            case 'l':
            int r1_len = length(ring1);
            int r2_len = length(ring2);
            printf("Ring 1 contains %d nodes\n", r1_len);
            printf("Ring 2 contains %d nodes\n", r2_len);
            break;
            case 'p':
            int product = sumProduct(ring1, ring2);
            printf("The product is %d\n", product);
            break;
            case 'a':
            append(&ring1, &ring2);
            break;
            case 's':
            swap(&ring1, &ring2);
            break;
            case 'h':
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %d", &height);
            insertHead(&ring1, name, height);
            break;
            case '2':
            if(ring2 != NULL){
            printRing(ring2);
            }
            break;
            case '1':
            if(ring1 != NULL){
            printRing(ring1);
            }
            break;
            case 't':
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %d", &height);
            ring1 = insertTail(ring1, name, height);
            break;
            case 'q':
            printf("Bye!\n");
           while(ring1 != NULL){
            ring1 = delete(ring1, ring1->name, ring1->height);
           }
              while(ring2 != NULL){
            ring2 = delete(ring2, ring2->name, ring2->height);
           }
          
            return 0;
            break;
            default:
            printf("Unknown command \'%c\'\n", cmd);
            break;
        }
    }
}



struct node *insertTail (struct node *ring, char *name, int height){
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
    new_node->name = (char*)malloc(sizeof(char)*1000);
    strcpy(new_node->name, name);
    new_node->height = height;
    new_node->next = new_node;
    if(ring == NULL){
        ring = new_node;
        return ring;
    }else{
       
        new_node->next = ring->next;
        ring->next = new_node;
        return new_node;
    }
    
   
}


void printRing (struct node *ring){
  struct node* tmp = ring->next;
    while(tmp != ring){
        if(tmp == NULL){
            continue;
        }
        printf("%s %d\n", tmp->name, tmp->height);
        tmp = tmp->next;
    }
    printf("%s %d\n", tmp->name, tmp->height);
   return;
}


void insertHead (struct node **ring, char *name, int height){
    struct node * head = (struct node *)malloc(sizeof(struct node));
    head->name = (char*)malloc(sizeof(char)*1000);
    strcpy(head->name, name);
    head->height = height;
    head->next = head;
    struct node * tmp = *ring;
    if(tmp == NULL){
        tmp = head;
        *ring = tmp;
        return;
    }else{
        head->next = tmp->next;
        tmp->next = head;
        *ring = tmp;
        return;
    }
}


void swap (struct node **ring1, struct node **ring2){
    struct node * tmp = *ring1;
    *ring1 = *ring2;
    *ring2 = tmp;
}


void append (struct node **ring1, struct node **ring2){
    if(*ring1 == NULL){
        swap(ring1, ring2);
        return;
    }else if(*ring2 == NULL){
        return;
    }
    struct node * inel1 = *ring1;
    struct node * inel2 = *ring2;
    struct node* tmp = inel1->next;
    inel1->next = inel2->next;
    inel2->next = tmp;
    *ring1 = inel2;
    *ring2 = NULL;
}

int length (struct node *ring){
    if(ring == NULL){
        return 0;
    }
    struct node * tmp = ring;
    int k = 0;
    while(tmp->next != ring){
        k++;
        tmp = tmp->next;
    }
    k++;
    return k;
}

int sumProduct (struct node *ring1, struct node *ring2){
    if(ring1 == NULL || ring2 == NULL){
        return 0;
    }
    int r1_len = length(ring1);
    int r2_len = length(ring2);
    int len = 0;
   if(r1_len - r2_len <= 0){
       len = r1_len;
   }else{
       len = r2_len;
   }
   int nr = 0;
   while(len){
        nr = nr + ring1->next->height*ring2->next->height;
       ring1 = ring1->next;
       ring2 = ring2->next;
       len--;
   }
   return nr;
    return 0;
}

struct node *delete (struct node *ring, char *name, int height){
    struct node* tmp = ring->next;
    if(tmp == ring && strcmp(tmp->name, name) == 0 && tmp->height == height){
       free(ring->name);
        free(ring);
        ring = NULL;
        return ring;
    }
    if(strcmp(tmp->name, name) == 0 && tmp->height == height){
        struct node * removed = tmp;
         ring->next = tmp->next;
            free(removed->name);
            free(removed);
            return ring;
    }
    while(tmp->next != ring){
        if(strcmp(tmp->next->name, name) == 0 && tmp->next->height == height){
           struct node * removed = tmp->next;
            tmp ->next = tmp->next->next;
            free(removed->name);
            free(removed);
            return ring;
        }
        tmp = tmp->next;
    }
    if(strcmp(tmp->next->name, name) == 0 && tmp->next->height == height){
            struct node *removed = tmp->next;
            tmp->next = tmp->next->next;
            free(removed->name);
            free(removed);
            return tmp;
        }
    printf("%s %d not in ring\n", name, height);
    return ring;
}
struct node *sort (struct node *ring){
    struct node * new_ring = NULL;
    struct node * tmp = new_ring;
    struct node * max_ring =  NULL;
    struct node * last = NULL;
    if(ring == NULL){
        return ring;
    }
    if(ring->next == ring){
        return ring;
    }
    while(ring != NULL){
        max_ring = max(ring);
        if(max_ring == NULL){
            return last;
        }
        if(new_ring == NULL){
            insertHead(&new_ring,max_ring->name, max_ring->height);
            last = new_ring;
        }else{
        insertHead(&new_ring, max_ring->name, max_ring->height);
        }
        ring = delete(ring, max_ring->name, max_ring->height);
        tmp = tmp->next;
    }
    
    return last;
}


struct node *max (struct node *ring){
    struct node * tmp = ring;
    
    if(ring == NULL){
        return NULL;
    }
    struct node * maxim = tmp->next;
    
    while(tmp->next != ring){
        if(maxim->height < tmp->next->height){
            maxim = tmp->next;
        }
        if(maxim->height == tmp->next->height && strcmp(maxim->name, tmp->next->name) < 0){
            maxim = tmp->next;
        }
        tmp = tmp->next;
    }
     if(maxim->height < tmp->next->height){
            maxim = tmp->next;
        }
        if(maxim->height == tmp->next->height && strcmp(maxim->name, tmp->next->name) < 0){
            maxim = tmp->next;
        }
        return maxim;
}

struct node *rotateLeft (struct node *ring){
    if(ring == NULL){
        return ring;
    }
    return ring->next;
}

struct node *rotateRight (struct node *ring){
    if(ring == NULL){
        return ring;
    }
        struct node * tmp = ring->next;
    if(tmp == ring){
        return ring;
    }
    while(tmp->next != ring){
        tmp = tmp->next;
    }
    return tmp;
}

void reverse(struct node **ring){
    struct node * new_node = NULL;
    struct node *removed = *ring;
    // struct node *tmp = new_node;
    if(removed == NULL){
        return;
    }
    if(removed->next == removed){
        return;
    }
    while(removed != NULL){
    insertHead(&new_node, removed->name, removed->height);
    removed = delete(removed, removed->name, removed->height);
    new_node = new_node->next;
    }
    swap(ring, &new_node);
}

