#include <stdio.h>
#include <stdbool.h>
#include "Structures.h"

int reg_new_Lecturers(){
    FILE *file_lecturer = fopen("../data_field/lecturer_info.txt", "a");
    struct Lecturer lect;

    if (file_lecturer == NULL){
        printf("No data found!");
        return 1;
    }
    
    printf("Enter a name of new lecturer: ");
    scanf(" %[^\n]", lect.lecturer_name);

    printf("\nEnter corresponding ID: ");
    scanf("%s", lect.lecturer_id);

    fprintf(file_lecturer, "%s: %s\n", lect.lecturer_name, lect.lecturer_id);

    fclose(file_lecturer);
}

int reg_new_subjects(){
    FILE *file_subjects = fopen("../data_field/subject_info_txt", "a");
    struct Subject subj;
    
    if(file_subjects == NULL){
        printf("No data found!");
        return 1;
    }

    printf("Enter a name of subject: ");
    scanf(" %[^\n]", subj.subject_name);

    printf("\nEnter ID: ");
    scanf("%s", subj.subject_code);

    printf("\nEnter lecturer's ID assigned to subject: ");
    scanf("%s", subj.assigned_lecturer_id);

    fprintf(file_subjects, "%s: %s, %s\n", subj.subject_name, subj.subject_code, subj.assigned_lecturer_id);

    fclose(file_subjects);

}

int attendance_reports(){
    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");
    struct Attendance report;
    char choice;

    if (file_attendance == NULL){
        printf("No data found!");
        return 1;
    }

    system("clear");
    printf("Attendance by\n1. Lecturer\n2. Subject\nEnter a choice number: ");
    scanf(" %c", &choice);

    if (choice == '1'){
        system("clear");
        printf("Enter lecturer's ID: ");
        scanf(" %[^\n]", report.student_id);

        while (fgets(report.student_id, sizeof(report.student_id), file_attendance) != NULL){
            // Add condition to check if ID exists in file
            printf("%s", report.student_id);
        }

        fclose(file_attendance);
    }
    else if (choice == '2'){
        system("clear");
        printf("Enter subject's ID: ");
        scanf(" %[^\n]", report.subject_code);

        while(fgets(report.subject_code, sizeof(report.subject_code), file_attendance) != NULL){
            // Add conditino to check if ID exists in file
            printf("%s", report.subject_code);
        }

        fclose(file_attendance);
    }
    else{
        printf("Error! Invalid role choice! Try again!");
        return 1;
    }
}

int admin_main(){
    bool is_True = true;
    char choice;

    while(is_True){
        printf("What function to do?\n");
        printf("1. Register new Lecturers\n2. Register new subjects\n3. View attendance report\n");
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
            system("clear");
            attendance_reports();
        }
        else if (choice == '4'){

        }
        else if (choice == '5'){
            is_True = false;
        }

        else{
            printf("Invalid input! Such a choice does not exist!");
        }
    }
}