#include <stdio.h>
#include "Structures.h"

// Initialize reg_new_Lecturers to register new lecturers
void reg_new_Lecturers(){
    struct Lecturer lect;
    printf("%s", lect.lecturer_name);
}

void reg_new_subjects(){
    struct Subject sbjct;

}

int list_of_actions(){
    char choice;
    printf("What function to do?\n");
    printf("1. Register new Lecturers\n2. Register new subjects\n3.View attendance report\n");
    printf("4. View student attendance percentage\n5. Exit\n");
    printf("Enter a choice number");

    scanf("%c", &choice);

    if (choice == '1'){
        reg_new_Lecturers();
    }
    else if (choice == '2'){

    }
    else if (choice == '3'){

    }
    else if (choice == '4'){

    }
    else if (choice == '5'){

    }

    else{
        printf("Invalid input! Such a choice does not exist!");
        // Return to the beginning of input
    }
}

int admin_main(){
    list_of_actions();

}