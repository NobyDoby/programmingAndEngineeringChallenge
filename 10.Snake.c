#include <stdio.h>
#include <libpynq.h>

typedef struct _pos_t{
    int x, y;
    struct _pos_t * next;
}pos_t;

typedef struct _ttl_t {
int x;
int y;
int startTTL; // duration that the pop-ups show up on the screen
int ttl; // remaining time to be displayed
struct _ttl_t *next;
} ttl_t;

void insertPos (pos_t **list, int x, int y);
void printPos (pos_t *list);
pos_t removeFirstPos (pos_t **list);
pos_t *lookupPos (pos_t *list, int x, int y);
void printTTL (ttl_t *list);
ttl_t *insertTTL (ttl_t *list, int x, int y, int startTTL);
ttl_t *lookupTTL (ttl_t *list, int x, int y);
int updateTTL (ttl_t *list);
int removeTTL (ttl_t **list);
void removeMiddleTTL (ttl_t **list, int x, int y);

int main(void)
{   pos_t* snake = {NULL};
    ttl_t* bonus = {NULL};
    pos_t removed;
    pos_t *position = {NULL};
    char cmd;
    int x, y;
    int k = 0;
    int start_ttl;
    while(1){
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'm':
             printf("Position (x y)? ");
            scanf(" %d %d", &x, &y);
            removeMiddleTTL(&bonus, x, y);
            break;
            case 'r':
            k = removeTTL(&bonus);
            printf("Removed %d nodes\n", k);
            break;
            case 'u':
            updateTTL(bonus);
            break;
            case 'i':
            printf("Position (x y ttl)? ");
            scanf(" %d %d %d", &x, &y, &start_ttl);
            bonus = insertTTL(bonus, x, y, start_ttl);
            break;
            case 'b':
            printf("[");
            printTTL(bonus);
            printf("]\n");
            break;
            case 'l':
             printf("Position (x y)? ");
            scanf(" %d %d", &x, &y);
            position = lookupPos(snake, x, y);
            if(position == NULL){
                printf("Position (%d,%d) is not in the list\n", x, y);
            }else{
                printf("Position (%d,%d) is in the list\n", x, y);
            }
            break;
            case 'f':
           removed = removeFirstPos(&snake);
           
           printf("Removed (%d,%d)\n", removed.x, removed.y);
               
           break;
            case 's':
            printPos (snake);
            break;
            case 'e':
            printf("Position (x y)? ");
            scanf(" %d %d", &x, &y);
            insertPos(&snake, x, y);
            break;
            case 'q':
            printf("Bye!\n"); 
            while(snake!= NULL) removeFirstPos(&snake);
            while(bonus != NULL){
                updateTTL(bonus);
                removeTTL(&bonus);
               
            }
            
            return 0;
            break;
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
        
    }
}



void insertPos (pos_t **list, int x, int y){
  pos_t* new_node = NULL;
  new_node = (pos_t*)malloc(sizeof(pos_t));
  new_node->x = x;
  new_node->y = y;
  new_node->next = NULL;
  
  if(*list == NULL){
      *list = new_node;
  }else {
      pos_t* snake = *list;
    while (snake != NULL) {
        if (snake->x == x && snake->y == y) {
            // Duplicate data, print an error message and return
            printf("Position (%d,%d) is already in the list\n", x, y);
            free(new_node);
            return;
        }
        snake = snake->next;
    }

    //reset the loop and now insert 
    // it didnt work before because if u insert in second position it will skip the above loop
    snake = *list;
    while (snake->next != NULL) {
        snake = snake->next;
    }
    snake->next = new_node;
}
}

void printPos (pos_t *list){
     printf("[");
    while(list != NULL){
        printf("(%d,%d)", list->x, list->y);
        
        if(list->next != NULL){
            printf(",");
        }
        list = list->next;
    }
            printf("]\n");

}


pos_t removeFirstPos (pos_t **list){
    pos_t * snake = *list;
     pos_t removed;
     removed.x = -1;
     removed.y = -1;
    if(snake == NULL){
        return removed;
    }else{
        removed = *snake;
        *list = snake->next;
        free(snake);
    
    }
    return removed;
}


pos_t *lookupPos (pos_t *list, int x, int y){
    pos_t* snake = list;
    pos_t* poz = NULL;
    while(snake != NULL){
        if(snake->x == x && snake->y == y){
            poz = snake;
            return poz;
        }
        snake = snake->next;
    }
    return poz;
}


void printTTL (ttl_t *list){
    while(list != NULL){
        printf("(%d,%d,%d,%d)", list->x, list->y, list->startTTL, list->ttl);
        if(list ->next != NULL){
            printf(",");
        }
        list = list->next;
        
    }
}


ttl_t *insertTTL(ttl_t *list, int x, int y, int startTTL) {
    ttl_t *insert = (ttl_t *)malloc(sizeof(ttl_t));
    insert->x = x;
    insert->y = y;
    insert->startTTL = startTTL;
    insert->ttl = startTTL;
    insert->next = NULL;
    
    ttl_t *print = lookupTTL(list, x, y);
    if(print != NULL){
        printf("Position (%d,%d) is already in the list\n", print->x, print->y);
        free(insert);
        return list;
    }
    if(list == NULL){
        list = insert;
        return list;
    }
    if(startTTL <= list->ttl){
        insert->next = list;
        return insert;
    }
    ttl_t* tmp = list;
    while(tmp->next != NULL && startTTL > tmp->next->ttl){
        tmp = tmp->next;
    }
    insert->next = tmp->next;
    tmp->next = insert;
    
    return list;
}


ttl_t *lookupTTL (ttl_t *list, int x, int y){
    ttl_t* tmp = list;
    
    while(tmp != NULL){
        if(tmp->x == x && tmp->y == y){
           
           return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

int updateTTL (ttl_t *list){
    while(list != NULL){
        list->ttl--;
        list = list->next;
    }
    return 0;
}


int removeTTL (ttl_t **list){
    ttl_t * tmp = *list;
    ttl_t * removed = NULL;
    int k = 0;
   while(tmp != NULL){
       if(tmp->ttl < 1){
           removed = tmp;
           *list = tmp->next;
           tmp = *list;
           free(removed);
           k++;
       }else{
           tmp =  tmp->next;
       }
   }
    return k;
}


void removeMiddleTTL (ttl_t **list, int x, int y){
    ttl_t * print = lookupTTL(*list, x, y);
    ttl_t * removed = NULL;
    if(print == NULL){
        printf("Position (%d,%d) not in list\n", x,y);
        return;
    }
     ttl_t * tmp = *list;
    if(tmp->x == x && tmp->y == y){
        *list = tmp->next;
        removed = tmp;
        free(removed);
        
        return;
    }
   
    tmp = *list;
    while(tmp->next != NULL){
        if(tmp->next->x == x && tmp->next->y == y){
            removed = tmp->next;
            tmp->next = tmp->next->next;
            free(removed);
            return;
        }
        tmp = tmp -> next;
    
    }
    
}