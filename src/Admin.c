#include <stdio.h>
#include <stdbool.h>
#include "Structures.h"

int reg_new_Lecturers(){
    struct Lecturer lect;
    FILE *fptr = fopen("../data_field/lecturer_info.txt", "a");

    if(fptr == NULL){
        printf("lecturer_info.txt does not exist!\n");
        return 1;
    }
    
    printf("Enter a name of new lecturer: ");
    scanf(" %[^\n]", lect.lecturer_name);

    printf("\nEnter corresponding ID: ");
    scanf("%s", lect.lecturer_id);

    fprintf(fptr, "%s: %s\n", lect.lecturer_name, lect.lecturer_id);

    fclose(fptr);
    printf("Done!\n");
}

int reg_new_subjects(){
    struct Subject subj;
    FILE *fptr = fopen("../data_field/subject_info_txt", "a");

    if(fptr == NULL){
        printf("subject.txt does not exist!\n");
        return 1;
    }

    printf("Enter a name of subject: ");
    scanf(" %[^\n]", subj.subject_name);

    printf("\nEnter ID");
    scanf("%s", subj.subject_code);

    printf("\nEnter lecturer's ID assigned to subject: ");
    scanf("%s", subj.assigned_lecturer_id);

    fprintf(fptr, "%s: %s, %s", subj.subject_name, subj.subject_code, subj.assigned_lecturer_id);

    fclose(fptr);
    system("clear");

}

int list_of_actions(){
    char choice;
    printf("What function to do?\n");
    printf("1. Register new Lecturers\n2. Register new subjects\n3.View attendance report\n");
    printf("4. View student attendance percentage\n5. Exit\n");
    printf("Enter a choice number: ");

    scanf(" %c", &choice);

    if (choice == '1'){
        system("clear");
        reg_new_Lecturers();
    }
    else if (choice == '2'){
        system("clear");
        reg_new_subjects();
    }
    else if (choice == '3'){

    }
    else if (choice == '4'){

    }
    else if (choice == '5'){
        return 1;
    }

    else{
        printf("Invalid input! Such a choice does not exist!");
    }
}

int admin_main(){
    bool is_True = true;

    while(is_True){
        list_of_actions();
    }
}