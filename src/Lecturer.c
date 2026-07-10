#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structures.h"

struct Enrollment {
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
};

int get_lecturer_subjects(char *lecturer_id, char subjects[][MAX_CODE], int max_subjects){
    FILE *file_subjects = fopen("../data_field/subject_info.txt", "r");
    int count = 0;
    char line[150];

    if(file_subjects == NULL){
        printf("Error: subject_info.txt not found!\n");
        return 0;
    }

    while(fgets(line, sizeof(line), file_subjects) != NULL && count < max_subjects){
        char temp_name[MAX_STRING], temp_code[MAX_CODE], temp_lect_id[MAX_STRING];
        if(sscanf(line, "%[^:]: %[^,], %s", temp_name, temp_code, temp_lect_id) == 3){
            if(strcmp(temp_lect_id, lecturer_id) == 0){
                strcpy(subjects[count], temp_code);
                count++;
            }
        }
    }
    fclose(file_subjects);
    return count;
}

bool is_valid_subject_for_lecturer(char *subject_code, char subjects[][MAX_CODE], int count){
    for(int i = 0; i < count; i++){
        if(strcmp(subjects[i], subject_code) == 0){
            return true;
        }
    }
    return false;
}

bool student_exists(char *student_id){
    FILE *file_students = fopen("../data_field/student_info.txt", "r");
    struct Student std;
    bool found = false;

    if(file_students == NULL){
        printf("Error: student_info.txt not found!\n");
        return false;
    }

    while(fscanf(file_students, " %[^:]: %s", std.student_name, std.student_id) == 2){
        if(strcmp(std.student_id, student_id) == 0){
            found = true;
            break;
        }
    }
    fclose(file_students);
    return found;
}

bool lecturer_exists(char *lecturer_id){
    FILE *file_lecturers = fopen("../data_field/lecturer_info.txt", "r");
    struct Lecturer lect;
    bool found = false;

    if(file_lecturers == NULL){
        printf("Error: lecturer_info.txt not found!\n");
        return false;
    }

    while(fscanf(file_lecturers, " %[^:]: %s", lect.lecturer_name, lect.lecturer_id) == 2){
        if(strcmp(lect.lecturer_id, lecturer_id) == 0){
            found = true;
            break;
        }
    }
    fclose(file_lecturers);
    return found;
}

bool is_enrolled(char *subject_code, char *student_id){
    FILE *file_enroll = fopen("../data_field/subject_students.txt", "r");
    struct Enrollment enr;
    bool found = false;

    if(file_enroll == NULL){
        return false;
    }

    while(fscanf(file_enroll, "%s %s", enr.subject_code, enr.student_id) == 2){
        if(strcmp(enr.subject_code, subject_code) == 0 && strcmp(enr.student_id, student_id) == 0){
            found = true;
            break;
        }
    }
    fclose(file_enroll);
    return found;
}

int register_student_to_subject(char *lecturer_id){
    char subjects[10][MAX_CODE];
    int subject_count = get_lecturer_subjects(lecturer_id, subjects, 10);
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
    char student_name[MAX_STRING];

    if(subject_count == 0){
        printf("No subjects assigned to Lecturer ID: %s\n", lecturer_id);
        return 1;
    }

    system("clear");
    printf("Your subjects: ");
    for(int i = 0; i < subject_count; i++){
        printf("%s ", subjects[i]);
    }
    printf("\n\nEnter subject code to register student into: ");
    scanf(" %9s", subject_code);

    if(!is_valid_subject_for_lecturer(subject_code, subjects, subject_count)){
        printf("Error: This subject is not assigned to you!\n");
        return 1;
    }

    printf("Enter student ID: ");
    scanf(" %49s", student_id);

    if(!student_exists(student_id)){
        printf("Student ID not found in student_info.txt.\n");
        printf("Enter student's name to register as a new student: ");
        scanf(" %[^\n]", student_name);

        FILE *file_students = fopen("../data_field/student_info.txt", "a");
        if(file_students == NULL){
            printf("Error: student_info.txt not found!\n");
            return 1;
        }
        fprintf(file_students, "%s: %s\n", student_name, student_id);
        fclose(file_students);
    }

    system("clear");
    if(is_enrolled(subject_code, student_id)){
        printf("Student %s is already registered under subject %s.\n", student_id, subject_code);
    }
    else{
        FILE *file_enroll = fopen("../data_field/subject_students.txt", "a");
        if(file_enroll == NULL){
            printf("Error: could not open subject_students.txt!\n");
            return 1;
        }
        fprintf(file_enroll, "%s %s\n", subject_code, student_id);
        fclose(file_enroll);

        printf("Student %s registered under subject %s successfully.\n", student_id, subject_code);
    }

    wait_for_keypress();
    return 0;
}

int record_daily_attendance(char *lecturer_id){
    char subjects[10][MAX_CODE];
    int subject_count = get_lecturer_subjects(lecturer_id, subjects, 10);
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
    char date[12];
    char status;

    if(subject_count == 0){
        printf("No subjects assigned to Lecturer ID: %s\n", lecturer_id);
        return 1;
    }

    system("clear");
    printf("Your subjects: ");
    for(int i = 0; i < subject_count; i++){
        printf("%s ", subjects[i]);
    }
    printf("\n\nEnter subject code: ");
    scanf(" %9s", subject_code);

    if(!is_valid_subject_for_lecturer(subject_code, subjects, subject_count)){
        printf("Error: This subject is not assigned to you!\n");
        return 1;
    }

    printf("Enter student ID: ");
    scanf(" %49s", student_id);

    if(!is_enrolled(subject_code, student_id)){
        printf("Error: Student %s is not registered under subject %s.\n", student_id, subject_code);
        printf("Please register the student first (Option 1).\n");
        return 1;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf(" %10s", date);

    printf("Enter status (P for Present / A for Absent): ");
    scanf(" %c", &status);

    if(status != 'P' && status != 'A'){
        printf("Error: Invalid status! Use P or A.\n");
        return 1;
    }

    system("clear");
    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "a");
    if(file_attendance == NULL){
        printf("Error: attendance_reports.txt not found!\n");
        return 1;
    }
    fprintf(file_attendance, "%s: %s, %s, %c\n", subject_code, student_id, date, status);
    fclose(file_attendance);

    printf("Attendance recorded successfully.\n");

    wait_for_keypress();
    return 0;
}

int update_attendance_record(char *lecturer_id){
    char subjects[10][MAX_CODE];
    int subject_count = get_lecturer_subjects(lecturer_id, subjects, 10);
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
    char date[12];
    char new_status;
    struct Attendance att;
    bool record_found = false;

    if(subject_count == 0){
        printf("No subjects assigned to Lecturer ID: %s\n", lecturer_id);
        return 1;
    }

    system("clear");
    printf("Your subjects: ");
    for(int i = 0; i < subject_count; i++){
        printf("%s ", subjects[i]);
    }
    printf("\n\nEnter subject code: ");
    scanf(" %9s", subject_code);

    if(!is_valid_subject_for_lecturer(subject_code, subjects, subject_count)){
        printf("Error: This subject is not assigned to you!\n");
        return 1;
    }

    printf("Enter student ID: ");
    scanf(" %9s", student_id);
    printf("Enter date of the record to update (YYYY-MM-DD): ");
    scanf(" %10s", date);
    printf("Enter new status (P for Present / A for Absent): ");
    scanf(" %c", &new_status);

    if(new_status != 'P' && new_status != 'A'){
        printf("Error: Invalid status! Use P or A.\n");
        return 1;
    }

    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");
    FILE *file_temp = fopen("../data_field/attendance_reports_temp.txt", "w");

    if(file_attendance == NULL || file_temp == NULL){
        printf("Error: attendance_reports.txt not found!\n");
        return 1;
    }

    system("clear");
    while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
        if(strcmp(att.subject_code, subject_code) == 0 && strcmp(att.student_id, student_id) == 0 && strcmp(att.date, date) == 0){
            fprintf(file_temp, "%s: %s, %s, %c\n", att.subject_code, att.student_id, att.date, new_status);
            record_found = true;
        }
        else{
            fprintf(file_temp, "%s: %s, %s, %c\n", att.subject_code, att.student_id, att.date, att.status);
        }
    }
    fclose(file_attendance);
    fclose(file_temp);

    remove("../data_field/attendance_reports.txt");
    rename("../data_field/attendance_reports_temp.txt", "../data_field/attendance_reports.txt");

    if(record_found){
        printf("Attendance record updated successfully.\n");
    }
    else{
        printf("Error: No matching attendance record found for %s, %s, %s.\n", subject_code, student_id, date);
    }

    wait_for_keypress();
    return 0;
}

int view_subject_attendance(char *lecturer_id){
    char subjects[10][MAX_CODE];
    int subject_count = get_lecturer_subjects(lecturer_id, subjects, 10);
    char subject_code[MAX_CODE];
    struct Attendance att;
    int found_records = 0;

    if(subject_count == 0){
        printf("No subjects assigned to Lecturer ID: %s\n", lecturer_id);
        return 1;
    }

    system("clear");
    printf("Your subjects: ");
    for(int i = 0; i < subject_count; i++){
        printf("%s ", subjects[i]);
    }
    printf("\n\nEnter subject code to view: ");
    scanf(" %9s", subject_code);

    if(!is_valid_subject_for_lecturer(subject_code, subjects, subject_count)){
        printf("Error: This subject is not assigned to you!\n");
        return 1;
    }

    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");
    if(file_attendance == NULL){
        printf("Error: attendance_reports.txt not found!\n");
        return 1;
    }

    system("clear");
    printf("--- Attendance List for Subject: %s ---\n", subject_code);
    printf("%-15s %-15s %-15s %-10s\n", "Subject Code", "Student ID", "Date", "Status");
    printf("-------------------------------------------------------\n");

    while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
        if(strcmp(att.subject_code, subject_code) == 0){
            printf("%-15s %-15s %-15s %-10c\n", att.subject_code, att.student_id, att.date, att.status);
            found_records++;
        }
    }
    fclose(file_attendance);

    if(found_records == 0){
        printf("No attendance records found for this subject.\n");
    }

    wait_for_keypress();
    return 0;
}

int lecturer_main(){
    char lecturer_id[MAX_STRING];
    char choice;

    system("clear");
    printf("Enter your Lecturer ID: ");
    scanf(" %49s", lecturer_id);

    if(!lecturer_exists(lecturer_id)){
        printf("Error: Lecturer ID '%s' not found in lecturer_info.txt.\n", lecturer_id);
        printf("Please check with the Academic (Admin) to register your ID first.\n");
        wait_for_keypress();
        return 1;
    }

    while(1){
        system("clear");
        printf("Welcome, Lecturer %s\n", lecturer_id);
        printf("1. Register student under my subject\n2. Record daily attendance\n3. Update attendance record\n4. View attendance list for my subject\n5. Exit\n");
        printf("Enter a choice number: ");
        scanf(" %c", &choice);

        if(choice == '1'){
            register_student_to_subject(lecturer_id);
        }
        else if(choice == '2'){
            record_daily_attendance(lecturer_id);
        }
        else if(choice == '3'){
            update_attendance_record(lecturer_id);
        }
        else if(choice == '4'){
            view_subject_attendance(lecturer_id);
        }
        else if(choice == '5'){
            return 0;
        }
        else{
            printf("Invalid input! Such a choice does not exist!\n");
        }
    }
}
