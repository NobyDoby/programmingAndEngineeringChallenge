#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 120
void printArray(char array[], int length);
void insertName(char *startPos[], int *nrNames, char newName[]);
int spaceUsed(char *startPos[], int nrNames);
void printNames(char names[], char *startPos[], int nrNames);
int lookupName(char names[], char *startPos[], int nrNames, char name[]);
void removeName(char *startPos[], int *nrNames, char name[]);
void swapNames(char *startPos[], int i, int j);
void mergeNames(char names[], char *startPos[], int *nrNames, int startPosIndex);

int main(){
    char names[LENGTH] = "\0";
    char cmd;
    char * startPos[LENGTH] = {names};
    char newName[LENGTH];
    int nrNames = 0, space = 0, lookup = -1, i, j, index;
    while(1){
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'm':
            printf("StartPos index? ");
            scanf(" %d", &index);
            mergeNames(names, startPos, &nrNames, index);
            break;
            case 's':
            printf("Indices? ");
            scanf(" %d %d", &i, &j);
            swapNames(startPos, i, j);
            break;
            case 'r':
            printf("Name? ");
            scanf(" %s", newName);
            lookup = lookupName(names, startPos, nrNames, newName);
            if(lookup == -1){
                printf("Did not find \"%s\"\n", newName);
            }else{
                removeName(startPos, &nrNames, newName);
            }
            break;
            
            case 'l':
            printf("Name? ");
            scanf(" %s", newName);
             lookup = lookupName(names, startPos, nrNames, newName);
            printf("\"%s\" has index %d\n", newName, lookup);
            break;
            case 'n':
            printNames(names, startPos, nrNames);
            break;
            case 'u':
            space = spaceUsed(startPos, nrNames);
            printf("Space used is %d\n", space);
            break;
            case 'i':
            printf("Name? ");
            scanf(" %s", newName);
            insertName(startPos, &nrNames, newName);
            break;
            case 'p':
            printArray(names, LENGTH);
            break;
            case 'q':
            printf("Bye!\n");
            return 0;
            break;
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    }
}

void printArray(char array[], int length){
    for(int i = 0; i < length; i++){
        if(array[i] == '\0'){
            printf("\\0");
        }else{
            printf("%c", array[i]);
        }
    }
    printf("\n");
}


void insertName(char *startPos[], int *nrNames, char newName[]){
   int space = spaceUsed(startPos, *nrNames);
   if(LENGTH-space < strlen(newName)){
       printf("Not enough space left\n");
       return;
   }
    strcpy(startPos[*nrNames], newName);
    (*nrNames)++;
    startPos[*nrNames] = startPos[(*nrNames)-1] + strlen(newName)+1;
}


int spaceUsed(char *startPos[], int nrNames){
    int x = startPos[nrNames] - startPos[0];
    return x;
}


void printNames(char names[], char *startPos[], int nrNames)
{
    int i;
    for (i = 0; i < nrNames; i++)
    {
        int charCount = strlen(startPos[i]) + 1;
        int currentPosIndex = startPos[i] - names;
       
        printf("startPos[%d]=%03d #chars=%03d string=\"%s\"\n", i, currentPosIndex, charCount, startPos[i]);
    }
}


int lookupName(char names[], char *startPos[], int nrNames, char name[]){
   
   int index = -1;
    for(int i = 0; i < nrNames; i++){
        if(strcmp(startPos[i], name) == 0){
            index = spaceUsed(startPos, i);
        }
    }
    return index;
}




void removeName(char *startPos[], int *nrNames, char name[]){
   for(int i = 0; i < *nrNames; i++){
       if(strcmp(startPos[i], name) == 0){
          startPos[i] = startPos[*nrNames-1];
           startPos[*nrNames-1] = startPos[*nrNames];
           (*nrNames)--;
           return;
       }
   }
}




void swapNames(char *startPos[], int i, int j){
    char *tmp = startPos[i];
    startPos[i] = startPos[j];
    startPos[j] = tmp;
}


void mergeNames(char names[], char *startPos[], int *nrNames, int startPosIndex){
    char* ptr_start = startPos[startPosIndex];
  char* ptr_center = ptr_start + strlen(ptr_start); //get terminating null char
  //Link names:
  *ptr_center = '+';

  //Is the found next removed -> we are done
  if(lookupName(names, startPos, *nrNames, startPos[startPosIndex+1])!= -1){
        removeName(startPos, nrNames, startPos[startPosIndex+1]);
  }

}
