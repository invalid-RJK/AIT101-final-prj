#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Structures.h"

int view_my_attendance(const char *student_id){
    struct Subject subj;
    struct Attendance att;
    int found_any = 0;
    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");
    FILE *file_subjects = fopen("../data_field/subject_info.txt", "r");

    if(file_attendance == NULL || file_subjects == NULL){
        printf("Error: attendance_reports.txt/subject_info.txt not found!\n");
        return 1;
    }

    printf("%-15s %-28s %-15s\n", "Subject Code", "Subject Name", "Percentage");
    printf("---------------------------------------------------------\n");

    while(fscanf(file_subjects, " %[^:]: %[^,], %s", subj.subject_name, subj.subject_code, subj.assigned_lecturer_id) == 3){
        int total_classes = 0;
        int attended_classes = 0;

        rewind(file_attendance);
        
        while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
            if(strcmp(att.student_id, student_id) == 0 && strcmp(att.subject_code, subj.subject_code) == 0){
                total_classes++;
                if(att.status == 'P'){
                    attended_classes++;
                }
            }
        }
        
        rewind(file_attendance);

        if(total_classes > 0){
            found_any = 1;
            float percentage = ((float)attended_classes / total_classes) * 100;
            printf("%-15s %-28s %.2f%%\n", subj.subject_code, subj.subject_name, percentage);
        }
    }

    if(found_any == 0){
        printf("No attendance records found for your ID\n");
    }

    fclose(file_attendance);
    fclose(file_subjects);

    wait_for_keypress();
    return 0;
}

int view_my_warnings(const char *student_id){
    struct Warning wrn;
    int found_any = 0;
    FILE *file_warnings = fopen("../data_field/warnings_history.txt", "r");

    if(file_warnings == NULL){
        printf("Error: warnings_history.txt not found!\n");
        return 1;
    }

    printf("%-15s %-15s %-15s\n", "Subject Code", "Date Issued", "Percentage");
    printf("---------------------------------------------------\n");

    while(fscanf(file_warnings, " %[^:]: %[^,], %[^,], %f", wrn.student_id, wrn.subject_code, wrn.date_issued, &wrn.attendance_percentage) == 4){
        if(strcmp(wrn.student_id, student_id) == 0){
            found_any = 1;
            printf("%-15s %-15s %.2f%%\n", wrn.subject_code, wrn.date_issued, wrn.attendance_percentage);
        }
    }

    if(found_any == 0){
        printf("No warnings found for your ID. Keep up the good work!\n");
    }

    fclose(file_warnings);

    wait_for_keypress();
    return 0;
}

int students_main(){
    struct Student std;
    char current_student_id[MAX_STRING];
    char choice;
    int student_found = 0;
    FILE *file_students = fopen("../data_field/student_info.txt", "r");

    if(file_students == NULL){
        printf("Error: student_info.txt not found!\n");
        return 1;
    }

    printf("Enter your Student ID: ");
    scanf(" %49s", current_student_id);

    while(fscanf(file_students, " %[^:]: %s", std.student_name, std.student_id) == 2){
        if(strcmp(current_student_id, std.student_id) == 0){
            student_found = 1;
            break;
        }
    }

    if(student_found == 0){
        printf("No such StudentID exist!\n");
        fclose(file_students);

        wait_for_keypress();
        return 0;
    }

    fclose(file_students);

    while(1){
        system("clear");
        printf("--- Student Menu (ID: %s) ---\n", current_student_id);
        printf("1. View my attendance\n2. View my wanrings\n3. Exit\nEnter a choice: ");
        scanf(" %c", &choice);

        if(choice == '1'){
            system("clear");
            view_my_attendance(current_student_id);
        }
        else if(choice == '2'){
            system("clear");
            view_my_warnings(current_student_id);
        }
        else if(choice == '3'){
            return 0;
        }
        else{
            printf("Invalid choice! Please try again!\n");
        }
    }
    return 0;
}
