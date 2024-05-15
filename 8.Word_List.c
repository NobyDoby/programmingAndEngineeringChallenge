#include <stdio.h>
#include <string.h>
#include <libpynq.h>
#include "predefined.h"

void printWordList (char *wordList[MAXWORDS]);
void insertWord (char *wordList[MAXWORDS], char *word);
void findWord (char **wordList, char *word, int *index);
void swapWords (char *wordList[MAXWORDS], char *word1, char *word2);
void longestWord (char *wordList[MAXWORDS], char **word);
void changeVowels (char *wordList[MAXWORDS]);
void appendWords (char *wordList[MAXWORDS], char *word1, char *word2);
void shareWord (char *wordList[MAXWORDS], char *word);
void deleteWord (char *wordList[MAXWORDS], char *word);

int main(){
    char* wordList[MAXWORDS]= {NULL, };
    char cmd;
    char word[100] = {'\0'};
    char word1[100] = {'\0'};
    char word2[100] = {'\0'};
    int index = -1;
    int index1 = -1;
    int index2 = -1;
    while(1){
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            
            case 'D':
            break;
            case 'd':
            printf("Word? ");
            scanf("%s", word);
            index = -1;
            findWord(wordList, word, &index);
            if(index == -1){
                printf("Word not found\n");
            }else{
                deleteWord(wordList, word);
            }
            break;
            case 's':
            printf("Word? ");
            scanf(" %s", word);
            if(wordList[MAXWORDS-1] != NULL){
                printf("List is full\n");
            }else{
                shareWord(wordList, word);
            }
            break;
            case 'a':
            printf("Words? ");
            scanf("%s %s", word1, word2);
            index1 = -1;
            index2 = -1;
            findWord(wordList, word1, &index1);
            findWord(wordList, word2, &index2);
           
            if(index1 ==-1 || index2 == -1){
                printf("Word(s) not in list\n");
            }else{
                appendWords(wordList, word1, word2);
            }
            break;
            case 'v':
            changeVowels(wordList);
            break;
            case 'l':
            char* longWord = {NULL};
            if(wordList[0] == NULL){
                printf("No words\n");
            }else{
                longestWord(wordList, &longWord);
                printf("The longest word is %s\n", longWord);
            }
            break;
            case 'w':
            printf("Words? ");
            scanf("%s %s", word1, word2);
            index1 = -1;
            index2 = -1;
            findWord(wordList, word1, &index1);
            findWord(wordList, word2, &index2);
            //printf("%d %d ", index1, index2);
            if(index1 ==-1 || index2 == -1){
                printf("Word(s) not in list\n");
            }else{
                swapWords(wordList, word1, word2);
            }
            break;
            case 'f':
            printf("Word? ");
            scanf(" %s", word);
            findWord(wordList, word, &index);
            printf("The index is %d\n", index);
            break;
            case 'i':
            printf("Word? ");
            scanf(" %s", word);
            if(wordList[MAXWORDS-1] != NULL){
                printf("List is full\n");
            }else{
                insertWord(wordList, word);
            }
            break;
            case 'p':
            printWordList(wordList);
            break;
            case 'q':
            printf("Bye!\n");
            while(wordList[0] != NULL) {
            predefined_deleteWord(wordList, wordList[0]);
            }
            return 0;
            break;
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    }
}


void printWordList (char *wordList[MAXWORDS]){
   
  for(int i = 0; i < MAXWORDS; i++)
    {
        if(wordList[i] != NULL){
        char * curr_p = wordList[i];
       
        printf("\"%s\" is referenced from entries", wordList[i]);
        for(int j = 0; j < MAXWORDS; j++)
        {
            if(wordList[j] != NULL){
            if(wordList[j] == curr_p)
            printf(" %d", j);
        }
        }
        printf("\n");
    }
    }
}



void insertWord (char *wordList[MAXWORDS], char *word){
    for(int i = 0; i < MAXWORDS; i++){
        if(wordList[i] == NULL){
            wordList[i] = (char*)malloc(sizeof(char)*MAXLEN);
           strcpy(wordList[i], word);
            break;
        }else if(strcmp(word, wordList[i])<0){
            for(int j = MAXWORDS-1; j > i; j--){
                wordList[j] = wordList[j-1];
            }
            wordList[i] = (char*)malloc(sizeof(char)*MAXLEN);
           strcpy(wordList[i], word);
           break;
        }else if(strcmp(word,wordList[i]) == 0){
            for(int j = MAXWORDS-1; j > i; j--){
                wordList[j] = wordList[j-1];
            }
            wordList[i] = (char*)malloc(sizeof(char)*MAXLEN);
           strcpy(wordList[i], word);
           break;
        }
        
    }
}



void findWord (char **wordList, char *word, int *index){
    
    for(int i = 0; i < MAXWORDS;i++){
        if(wordList[i] != NULL){
        if(strcmp(wordList[i], word) == 0){
            *index = i;
        }
    }
    }      
}


void swapWords (char *wordList[MAXWORDS], char *word1, char *word2){
    int index1 = 0;
    int index2 = 0;
    findWord(wordList, word1, &index1);
    findWord(wordList, word2, &index2);
    char* tmp = wordList[index1];
    wordList[index1] = wordList[index2];
    wordList[index2] = tmp;
}


void longestWord (char *wordList[MAXWORDS], char **word){
   int maxim = -1;
   int index = -1;
    for(int i = 0; i < MAXWORDS; i++){
        if(wordList[i] != NULL){
            int len = strlen(wordList[i])+1;
        if(len > maxim){
            maxim = len;
            index = i;
        }else if(len == maxim ){
            index = i;
        }
    }
    }
    if(index != -1){
    
    *word = wordList[index];
    }
   // printf("%s", *word);
}


void changeVowels (char *wordList[MAXWORDS]){
    for(int i = 0; i < MAXWORDS;i++){
        if(wordList[i] != NULL){
            int len = strlen(wordList[i]);
            for(int j = 0; j < len;j++){
                if(wordList[i][j] == 'a'){
                    wordList[i][j] = 'e';
                }else if(wordList[i][j] == 'e'){
                    wordList[i][j] = 'a';
            }else if(wordList[i][j] == 'o'){
                    wordList[i][j] = 'u';
            }else if(wordList[i][j] == 'u'){
                    wordList[i][j] = 'o';
            }
        }
    }
}
}

 void appendWords (char *wordList[MAXWORDS], char *word1, char *word2){
 
     int index1 = -1;
     int index2 = -1;
     char* tmp = {NULL};
    findWord(wordList, word1, &index1);
    findWord(wordList, word2, &index2);
    
        tmp = word1;
     strcat(tmp, "+");
     strcat(tmp, word2);
   
    // printf("%s", word1);
    free(wordList[index1]);
    wordList[index1] = (char*)malloc(strlen(tmp)+1);
   strcpy(wordList[index1], tmp);
   
 predefined_deleteWord(wordList, wordList[index2]);
 }
 
 
void shareWord (char *wordList[MAXWORDS], char *word){
    int index = -1;
    
    findWord(wordList, word, &index);
    if(index == -1){
        insertWord(wordList, word);
    }else{
        for(int i  = 0; i < MAXWORDS;i++){
            if(wordList[i] != NULL){
                if(strcmp(wordList[i], word) == 0){
                for(int j = MAXWORDS-1; j > i; j--){
                wordList[j] = wordList[j-1];
            }
            }if(strcmp(wordList[i], word) == 0){
            wordList[i] = wordList[i+1];
            break;
            }
        }
        }
    }
}


void deleteWord (char *wordList[MAXWORDS], char *word){
    int index = -1;
    findWord(wordList, word, &index);
    if(index != -1){
    if(index == 0 || wordList[index] != wordList[index - 1]) // if it's only one word and not the same multiple times
    {
        if(wordList[index] != NULL) // for the  not shared
            free(wordList[index]);
    }
    

    for(int j = index; j < MAXWORDS; j++){
        if(wordList[j] != NULL){  
        wordList[j] = wordList[j+1];
    }
    }
}
}