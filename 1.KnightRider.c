#include <libpynq.h>
#include <stdio.h>

int k;
int main(void) {
  int num = 4;
  int i = 0;
  int n = 20;
  pynq_init();
  leds_init_onoff(); 
///// begin of new code that you have type in (or copy):
  printf("Wait for how many miliseconds? ");
  scanf("%d", &k);
  if(k < 0){
    printf("The number of miliseconds should be at least 0 ");
  }else{
    while (n){
      for(i = 0; i < num-1; i++){
             green_led_onoff(i,LED_ON);  
             sleep_msec(k);
              green_led_onoff(i,LED_OFF); 
               sleep_msec(k);
          }
    for(i = num-1; i > 0; i--){
             green_led_onoff(i,LED_ON);  
              sleep_msec(k);
              green_led_onoff(i,LED_OFF); 
               sleep_msec(k);
    }
       n--; 
      }
              green_led_onoff(0,LED_ON);  
              sleep_msec(k);
              green_led_onoff(0,LED_OFF); 
              sleep_msec(k);
      // Your code goes here
    }
  leds_destroy();              
///// end of new code
  pynq_destroy();
  return EXIT_SUCCESS;
}
