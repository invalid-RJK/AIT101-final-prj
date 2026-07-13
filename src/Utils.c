#include <stdio.h>

void wait_for_keypress(){
    printf("\nEnter any character to return to the menu: ");
    char pause;
    scanf(" %c", &pause);
}