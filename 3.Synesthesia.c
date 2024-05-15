#include <libpynq.h>
#include <ctype.h>
#include <string.h>

void printString(char s[]);
void printChar(char c);
void printArray(char a[], int length);
void readLine(char str[], int length);
void insertChar(char str[], char aChar, int index);
void replaceChars(char str[], char fromString[], char toChar);

int isconsonant(char c);
int isvowel(char c);
int is0to9(char c);
int findFirstOccurence(char str[], char c);
int readInt(char str[], int length);

#define LENGTH 30
int main() {
  int x = -1;

  pynq_init();
  leds_init_onoff();
  
  char inputString[LENGTH] = {'\0'};
  char currString[LENGTH] = {'\0'};
      while(1){
        printf("Command? ");
        readLine(inputString, 30);
      switch(inputString[0]){
          case 'r':
          printf("Replace which characters? ");
        char fromString[30];
        readLine(fromString, 30);
        printf("with which character? ");
        char toChar[2];
        readLine(toChar, 2);
        replaceChars(currString, fromString, toChar[0]);
        break;
       case 'i':
                printf("Insert which character? ");
                char targetChar[2];
                readLine(targetChar, 2);
                printf("At what index? ");
                char targetIndex[3];
                readLine(targetIndex, 3);
               int y = readInt(targetIndex, 3);
                insertChar(currString, targetChar[0], y);
                break;

        
        case 'o':
        printf("Find first occurrence of which character? ");
            char target[2];
            readLine(target, 2);
         x = findFirstOccurence(currString, target[0]);
        printf("The first occurrence of '%c' is at index %d\n", target[0], x);

        break;

          case 's':
          printf("Please enter a string? ");
          readLine(currString, LENGTH);

          break;

        case 'q':
          printf("Bye!\n");
          return 0;
          break;
        case  'p':
        printString(currString);
        break;
        case 'a':
          printArray(currString, LENGTH);
          break;
        default:
        printf("Unknown command '%c'\n", inputString[0]);
        break;
      }
      }



  // your code here
   leds_destroy();     
  pynq_destroy();
  return EXIT_SUCCESS;
}

void printChar (char c) {
    int x= isconsonant(c);
    int y = isvowel(c);
    int z = is0to9(c);
    if(x == 1){
        color_led_red_onoff(LED_ON);
         sleep_msec(100);
        color_led_red_onoff(LED_OFF);
         sleep_msec(100);
    }else if(y == 1){
      color_led_blue_onoff(LED_ON);
         sleep_msec(100);
        color_led_blue_onoff(LED_OFF);
         sleep_msec(100);
    }else if(z == 1){
      color_led_green_onoff(LED_ON);
         sleep_msec(100);
        color_led_green_onoff(LED_OFF);
         sleep_msec(100);
    }else if(x == 0 && y == 0 && z == 0){
      color_led_onoff(LED_OFF, LED_OFF, LED_OFF);
    }
putchar(c);
fflush(NULL);
sleep_msec(200);
}

void printString (char s[]) {
  printf("The current string is: ");
  printf("\"");

    int i= 0;
    while(s[i] != '\0'){

      printChar(s[i]);
      i++;
    }
    if(s[i] == '\0'){
      
      color_led_onoff(LED_ON,LED_ON,LED_ON);
       sleep_msec(200);
      color_led_onoff(LED_OFF,LED_OFF,LED_OFF);
       sleep_msec(200);
    }
    printf( "\"\n");
}

int isconsonant(char c){
  c = tolower(c);
  if(c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' || c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z')
  return 1;
  else
  return 0;
}

int isvowel(char c){
  c = tolower(c);
  if(c == 'a' || c == 'e'|| c == 'i' || c == 'o' || c == 'u')
  return 1;
  else
  return 0;
}

int is0to9(char c){
  if(c == '0' || c == '1' || c == '2' || c == '3'|| c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
  return 1;
    else
    return 0;
}

void printArray(char a[], int length){
 printf("The current array is: ");
 printf("[");
 int i = 0 ;
 for (i=0; i < length; i++){
          if(a[i] == '\0'){
            printf("\\0");
          }else {
            putchar(a[i]);
          }
          fflush(NULL);
          if(i == length-1){
            printf("]\n");
          }else {
            printf(",");
          }
 }
     
 
    
 
}


void readLine(char str[], int length) {
    int i = 0;
        int x;
    do {
        x = getchar();
        if(x != '\n' && i <length-1){
            str[i] = x;
        }else if(x == '\n' && i < length-1){
            str[i] = '\0';
        }else if(i >= length-1 && x == '\n'){
            str[length-1] = '\0';
        }else if(x == ' '){
          str[i] = ' ';
        }
        i++;
        
    } while (x != '\n');


}
   

int findFirstOccurence(char str[], char c){
    
    int i;
    for(i = 0; str[i] != '\0' ; i++){
       if(str[i]== c){
        return i;
      }
    }
        return -1;
      
}

int readInt(char str[], int length) {
    int result = 0;
    int i = 0;
    while (i < length && (str[i] == ' ' || str[i] == '\n')) {
        return -1;
    }
    if (i >= length || (str[i] < '0' || str[i] > '9')) {
        return -1;
    }
    while (i < length && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}



void insertChar(char str[], char aChar, int index) {
    int length = strlen(str);
    
    if (index >= 0 && index <= length) {
        for (int i = length; i > index; i--) {
            str[i] = str[i - 1];
        }
        str[index] = aChar;
    }
}

void replaceChars(char str[], char fromString[], char toChar){
    int i = 0;
    int j = 0;
     int length = strlen(str);
        int fromStringLength = strlen(fromString);
    
        for (i = 0; i < length; i++) {
        for (j = 0; j < fromStringLength; j++) {
            if (str[i] == fromString[j]) {
                str[i] = toChar;
                break; // Exit the inner loop if a replacement is made
            }
        }
    }
}







