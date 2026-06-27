#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Structures.h"

void attendance_percentage(){

}

void students_reminders(){

}

int students_main(){
    char studentID[MAX_STRING];
    char choice;
    printf("Enter your student ID: ");
    scanf(" %[^\n]", studentID);

    while(1){
        system("clear");
        printf("Welcome, %s\n1. View attendance percentage by subject\n2. View reminders\n", studentID);
        printf("Enter an option: ");
        scanf("%c", &choice);

        if(choice == '1'){
            printf("adsf");
        }
        else if(choice == '2'){
            printf("aaaa");
        }
    }
}