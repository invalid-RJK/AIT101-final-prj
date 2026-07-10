#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Admin.h"
#include "Students.h"
#include "Lecturer.h"

void wait_for_keypress(){
    printf("\nEnter any character to return to the menu: ");
    char pause;
    scanf(" %c", &pause);
}

int main(){
    char role;

    while(1){
        system("clear");
        printf("Welcome to the Student Attendance Management System!\n");
        printf("1. Admin\n2. Lecturer\n3. Student\n4. Exit\nEnter your status: ");
        scanf(" %c", &role);

        if(role == '1'){
            system("clear");
            admin_main();
        }
        else if(role == '2'){
            system("clear");
            lecturer_main();
        }
        else if(role == '3'){
            system("clear");
            students_main();
        }
        else if(role == '4'){
            return 0;
        }
        else{
            printf("Invalid input! Such a role does not exist!\n");
        }
    }
}
