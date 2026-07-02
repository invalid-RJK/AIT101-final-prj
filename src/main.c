#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structures.h"
#include "Admin.c"
#include "Students.c"

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
            break;
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
