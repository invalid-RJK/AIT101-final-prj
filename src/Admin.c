#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Structures.h"

int reg_new_Lecturers(){
    FILE *file_lecturer = fopen("../data_field/lecturer_info.txt", "a");
    struct Lecturer lect;

    if (file_lecturer == NULL){
        printf("Error: lecturer_info.txt not found!");
        return 1;
    }
    
    printf("Enter a name of new lecturer(at fist, put 'L'): ");
    scanf(" %[^\n]", lect.lecturer_name);

    printf("\nEnter corresponding ID: ");
    scanf("%s", lect.lecturer_id);

    fprintf(file_lecturer, "%s: %s\n", lect.lecturer_name, lect.lecturer_id);

    fclose(file_lecturer);

    return 0;
}

int reg_new_subjects(){
    FILE *file_subjects = fopen("../data_field/subject_info.txt", "a");
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
    
    return 0;
}

int attendance_reports(){
    FILE *file_attendance;
    FILE *file_subjects;
    struct Attendance att;
    char choice;
    char search_id[MAX_STRING];

    system("clear");
    printf("--- View Attendance Reports ---\n1. By Lecturer\n2. By Subject\n3. Student's attendance percentage\nEnter a choice number: ");
    scanf(" %c", &choice);

    if(choice == '1'){
        system("clear");
        printf("Enter Lecturer's ID: ");
        scanf("%s", search_id);

        file_subjects = fopen("../data_field/subject_info.txt", "r");

        if(file_subjects == NULL){
            printf("Error: subjecgt_info.txt not found!\n");
            return 1;
        }

        char assigned_subjects[10][MAX_CODE];
        int subject_count = 0;
        char line[150];

        while(fgets(line, sizeof(line), file_subjects) != NULL){
            char temp_name[MAX_STRING], temp_code[MAX_CODE], temp_lect_id[MAX_STRING];
            if(sscanf(line, "%[^:]: %[^,], %s", temp_name, temp_code, temp_lect_id) == 3){
                if(strcmp(temp_lect_id, search_id) == 0){
                    strcpy(assigned_subjects[subject_count], temp_code);
                    subject_count++;
                }
            }
        }
        fclose(file_subjects);

        if(subject_count == 0){
            system("clear");
            printf("No subjects assigned to Lecturer ID: %s\n", search_id);
            return 0;
        }

        file_attendance = fopen("../data_field/attendance_reports.txt", "r");

        if(file_attendance == NULL){
            printf("Error: attendance_reports.txt not found!\n");
            return 1;
        }

        system("clear");

        printf("--- Attendance Report for Lecturer: %s ---\n", search_id);
        printf("%-15s %-15s %-15s %-10s\n", "Subject Code", "Student ID", "Date", "Status");
        printf("-------------------------------------------------------\n");\

        int found_records = 0;

        while(fscanf(file_attendance, "%s %s %s %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
            for(int i = 0; i < subject_count; i++){
                if(strcmp(att.subject_code, assigned_subjects[i]) == 0){
                    printf("%-15s %-15s %-15s %-10c\n", att.subject_code, att.student_id, att.date, att.status);
                    found_records++;
                    break;
                }
            }
        }
        fclose(file_attendance);

        if(found_records == 0){
            printf("No attendance records found for this lecturer's subjects\n");
        }
    
    }
    else if(choice == '2'){
        system("clear");
        printf("Enter Subject's ID: ");
        scanf("%s", search_id);

        file_attendance = fopen("../data_field/attendance_reports.txt", "r");

        if(file_attendance == NULL){
            printf("Error: attendance_reports.txt not found!\n");
            return 1;
        }

        system("clear");

        printf("--- Attendance Report for Subject: %s ---\n", search_id);
        printf("%-15s %-15s %-15s %-10s\n", "Subject Code", "Student ID", "Date", "Status");
        printf("-------------------------------------------------------\n");

        int found_records = 0;

        while(fscanf(file_attendance, "%s %s %s %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
            if(strcmp(att.subject_code, search_id) == 0){
                printf("%-15s %-15s %-15s %-10c\n", att.subject_code, att.student_id, att.date, att.status);
                found_records++;
            }
        }
        fclose(file_attendance);

        if(found_records == 0){
            system("clear");
            printf("No attendance records found for Subject ID: %s\n", search_id);
        }
    }
    else if(choice == '3'){
        struct Warning wrn;
        char temp_id[MAX_STRING];
        char temp_subject_code[MAX_STRING];

        system("clear");
        printf("Enter student's ID: ");
        scanf(" %s", temp_id);
        printf("Enter course code: ");
        scanf(" %s", temp_subject_code);

        FILE *file_warnings = fopen("../data_field/warnings_history.txt", "r");

        if(file_warnings == NULL){
            printf("Error: warnings_history.txt not found!\n");
            return 1;
        }

        while(fscanf(file_warnings, " %[^:]: %[^,], %[^,], %f", wrn.student_id, wrn.subject_code, wrn.date_issued, &wrn.attendance_percentage) == 4){
            if(strcmp(temp_id, wrn.student_id) == 0 && strcmp(temp_subject_code, wrn.subject_code) == 0){
                system("clear");
                printf("%s: %.2f\n", wrn.subject_code, wrn.attendance_percentage);
            }
            else{
                printf("Error: Such data not exist!\n");
                return 1;
            }
        }
        fclose(file_warnings);

        return 0;
    }
    else{
        printf("Error! Invalid choice! Try again!\n");
        return 1;
    }

    printf("\nEnter any character to return to the menu: ");
    char pause;
    scanf(" %c", &pause);

    system("clear");
    return 0;
}

int issue_warnings(){
    struct Student std;
    struct Subject subj;
    struct Attendance att;
    struct Warning wrn;

    FILE *file_students = fopen("../data_field/student_info.txt", "r");
    FILE *file_subjects = fopen("../data_field/subject_info.txt", "r");
    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");
    FILE *file_warnings = fopen("../data_field/warnings_history.txt", "a");

    if(file_students == NULL || file_subjects == NULL || file_attendance == NULL || file_warnings == NULL){
        printf("Error: attendance_reports not found!");
        return 1;
    }

    while(fscanf(file_students, " %[^:]: %s", std.student_name, std.student_id) == 2){
        while(fscanf(file_subjects, " %[^:]: %[^,], %s", subj.subject_name, subj.subject_code, subj.assigned_lecturer_id) == 3){
            int attended_classes = 0;
            int total_classes = 0;

            while(fscanf(file_attendance, "%s %s %s %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
                if(strcmp(att.subject_code, subj.subject_code) == 0 && strcmp(att.student_id, std.student_id) == 0){
                    total_classes++;

                    if(att.status == 'P'){
                        attended_classes++;
                    }
                }
            }
            rewind(file_attendance);

            if(total_classes > 0){
                wrn.attendance_percentage = ((float) attended_classes / total_classes) * 100;

                if(wrn.attendance_percentage < 80.00){
                    fprintf(file_warnings, "%s: %s, %s, %.2f\n", std.student_id, subj.subject_code, att.date, wrn.attendance_percentage);
                }
            }
        }
        rewind(file_subjects);
    }
    fclose(file_students);
    fclose(file_subjects);
    fclose(file_attendance);
    fclose(file_warnings);

    return 0;
}

int view_warnings(){
    char line[MAX_STRING * 3];
    FILE *file_warnings = fopen("../data_field/warnings_history.txt", "r");

    if(file_warnings == NULL){
        printf("Error: warnings_history.txt not found!");
        return 1;
    }

    printf("\tWarnings history\n");
    printf("----------------------------------------\n");
    while(fgets(line, sizeof(line), file_warnings) != NULL){
        printf("%s", line);
    }

    fclose(file_warnings);

    printf("----------------------------------------\n");
    printf("\nEnter any character to return to the menu: ");
    char pause;
    scanf(" %c", &pause);

    system("clear");
    return 0;
}

int admin_main(){
    char choice;

    while(1){
        printf("What function to do?\n");
        printf("1. Register new Lecturers\n2. Register new subjects\n3. View attendance report\n4. Issue warnings\n5. View warnings history\n6. Exit\nEnter a choice number: ");
        scanf(" %c", &choice);

        if(choice == '1'){
            system("clear");
            reg_new_Lecturers();
        }
        else if(choice == '2'){
            system("clear");
            reg_new_subjects();
        }
        else if(choice == '3'){
            system("clear");
            attendance_reports();
        }
        else if(choice == '4'){
            system("clear");
            issue_warnings();
        }
        else if(choice == '5'){
            system("clear");
            view_warnings();
        }
        else if(choice == '6'){
            return 0;
        }

        else{
            printf("Invalid input! Such a choice does not exist!");
        }
    }
}