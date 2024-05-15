#include <stdio.h>

int power,i, j, val_re, val_im;
char cmd, v[1000][1000];
float curr_re = 0, curr_im = 0;
double temp_re, temp_im, k, c;

int main(){
    printf("** Complex Calculator **\n");
    while(1){
    printf("Operation [0+-*crpq]? ");
    scanf(" %c", &cmd); 
switch(cmd){
    case 'p':
    val_re = (int)curr_re;
    val_im = (int)curr_im;
    for(i = 10; i > -11; i--){
        for( j = -10; j <= 10; j++){
          if(i== 0 && j != 0){
               printf("-");
           }else if(i != 0 && j == 0){
               printf("|");
           }
           else if(i == val_im && j == val_re){
            printf("*");   
           }
           else if(i == 0 && j == 0){
               printf("+");
           }else{
            printf(".");
           }
           }
        printf("\n");
    }
    
    break;
    case 'r':
    printf("Natural operand? ");
        scanf(" %d", &power);
         temp_re = curr_re;
            temp_im = curr_im;
         if(power == 0){
                curr_im = 0;
                curr_re = 1;
            }else{
        while(power-1){
           
            k = curr_re * temp_re - curr_im *   temp_im;
            c = curr_re * temp_im + curr_im * temp_re;
            curr_re = k;
            curr_im = c;
            power--;
        }
            }
        break;
    case '*':
    printf("Complex operand? ");
    scanf(" %lf  %lf", &temp_re, &temp_im);
    k = curr_re * temp_re - curr_im * temp_im;
    c = curr_re * temp_im + curr_im * temp_re;
    curr_re = k;
    curr_im = c;
    break;
    case 'c':
    curr_im = -curr_im;
    break;
    case '0':
        curr_re = 0.00;
        curr_im = 0.00;
        break;
    case '-':
    printf("Complex operand? ");
        scanf(" %lf  %lf", &temp_re, &temp_im);
        curr_re = curr_re - temp_re;
        curr_im = curr_im - temp_im;
        break;
    case '+':
        printf("Complex operand? ");
        scanf(" %lf  %lf", &temp_re, &temp_im);
        curr_re = curr_re + temp_re;
        curr_im = curr_im + temp_im;
        break;
    case 'q':
        if(curr_im < 0){
            printf("Current value is %lf%lfi\n", curr_re, curr_im);
        }else
        printf("Current value is %lf+%lfi\n", curr_re, curr_im);
            printf("Bye!\n");
            return 0;
            break;

default:
    printf("Invalid command '%c'\n", cmd);
}       
        if(curr_im < 0){
            printf("Current value is %lf%lfi\n", curr_re, curr_im);
        }else
        printf("Current value is %lf+%lfi\n", curr_re, curr_im);
}
}