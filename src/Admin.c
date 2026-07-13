#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Structures.h"

int reg_new_Lecturers(){
    struct Lecturer lect;
    char temp_lect_name[MAX_STRING];
    char temp_lect_id[MAX_STRING];
    int is_duplicate = 0;

    FILE *file_lecturer = fopen("../data_field/lecturer_info.txt", "a+");

    if (file_lecturer == NULL){
        printf("Error: lecturer_info.txt not found!");
        return 1;
    }
    
    printf("Enter a name of new lecturer: ");
    scanf(" %49[^\n]", temp_lect_name);

    printf("Enter corresponding ID(at fist, put 'L'): ");
    scanf(" %49s", temp_lect_id);

    rewind(file_lecturer);
    while(fscanf(file_lecturer, " %[^:]: %s", lect.lecturer_name, lect.lecturer_id) == 2){
        if(strcmp(temp_lect_name, lect.lecturer_name) == 0 && strcmp(temp_lect_id, lect.lecturer_id) == 0){
            is_duplicate = 1;
            break;
        }
    }

    system("clear");
    if(is_duplicate == 1){
        printf("Error: Lecturer ID '%s' aldready exist!\n", temp_lect_id);
    }
    else{
        if(temp_lect_id[0] == 'L'){
            fprintf(file_lecturer, "%s: %s\n", temp_lect_name, temp_lect_id);
            printf("Successfully added new lecturer info!\n");
        }
        else{
            printf("Error: start ID with 'L' letter!\n");
        }
    }
    fclose(file_lecturer);
    wait_for_keypress();
    return 0;
}

int reg_new_subjects(){
    struct Subject subj;
    char temp_subject_name[MAX_STRING];
    char temp_subject_code[MAX_STRING];
    char temp_assigned_lecturer_id[MAX_STRING];
    int is_duplicate = 0;

    FILE *file_subjects = fopen("../data_field/subject_info.txt", "a+");
    
    if(file_subjects == NULL){
        printf("No data found!");
        wait_for_keypress();
        return 0;
    }

    printf("Enter a name of subject: ");
    scanf(" %49[^\n]", temp_subject_name);

    printf("Enter ID: ");
    scanf("%49s", temp_subject_code);

    printf("Enter lecturer's ID assigned to subject: ");
    scanf("%49s", temp_assigned_lecturer_id);

    rewind(file_subjects);
    while(fscanf(file_subjects, " %[^:]: %[^,], %s", subj.subject_name, subj.subject_code, subj.assigned_lecturer_id) == 3){
        if(strcmp(temp_subject_code, subj.subject_code) == 0 && strcmp(temp_assigned_lecturer_id, subj.assigned_lecturer_id) == 0){
            is_duplicate = 1;
            break;
        }
    }

    system("clear");
    if(is_duplicate == 1){
        printf("Error: Subject '%s' already exist!\n", temp_subject_code);
    }
    else{
        fprintf(file_subjects, "%s: %s, %s\n", temp_subject_name, temp_subject_code, temp_assigned_lecturer_id);
        printf("Successfully added the new subject!\n");
    }
    fclose(file_subjects);
    wait_for_keypress();
    return 0;
}

int attendance_reports(){
    struct Attendance att;
    struct Subject subj;
    char choice;
    char search_id[MAX_STRING];
    char assigned_subjects[10][MAX_CODE];
    int subject_count = 0;

    system("clear");
    printf("--- Attendance Reports ---\n1. By Lecturer\n2. By Subject\n3. Student's attendance percentage\n4. Exit\nEnter a choice number: ");
    scanf(" %c", &choice);

    if(choice == '1'){
        char line[MAX_STRING * 3];

        system("clear");
        printf("Enter Lecturer's ID: ");
        scanf("%49s", search_id);

        FILE *file_subjects = fopen("../data_field/subject_info.txt", "r");

        if(file_subjects == NULL){
            printf("Error: subject_info.txt not found\n");
            wait_for_keypress();
            return 1;
        }

        while(fgets(line, sizeof(line), file_subjects) != NULL){
            char temp_name[MAX_STRING], temp_code[MAX_CODE], temp_lect_id[MAX_STRING];
            if(sscanf(line, "%[^:]: %[^,], %s", temp_name, temp_code, temp_lect_id) == 3){
                if(strcmp(temp_lect_id, search_id) == 0){
                    if(subject_count < 10){
                        strcpy(assigned_subjects[subject_count], temp_code);
                        subject_count++;
                    }
                }
            }
        }
        fclose(file_subjects);

        FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");

        if(file_attendance == NULL){
            printf("Error: attendance_reports.txt not found!\n");
            wait_for_keypress();
            return 1;
        }

        system("clear");
        printf("--- Attendance Report for Lecturer: %s ---\n", search_id);
        printf("%-15s %-15s %-15s %-10s\n", "Subject Code", "Student ID", "Date", "Status");
        printf("-------------------------------------------------------\n");\

        int found_records = 0;
        while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
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
        scanf("%49s", search_id);

        FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");

        if(file_attendance == NULL){
            printf("Error: attendance_reports.txt not found!\n");
            wait_for_keypress();
            return 1;
        }

        system("clear");
        printf("--- Attendance Report for Subject: %s ---\n", search_id);
        printf("%-15s %-15s %-15s %-10s\n", "Subject Code", "Student ID", "Date", "Status");
        printf("-------------------------------------------------------\n");

        int found_records = 0;
        while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
            if(strcmp(search_id, att.subject_code) == 0){
                printf("%-15s %-15s %-15s %-10c\n", att.subject_code, att.student_id, att.date, att.status);
                found_records++;
            }
        }

        if(found_records == 0){
            printf("No attendance records found for this subject\n");
        }

        fclose(file_attendance);
        wait_for_keypress();
        return 0;
    }
    else if(choice == '3'){
        char temp_id[MAX_STRING];
        char temp_subject_code[MAX_STRING];
        int total_classes = 0;
        int attended_classes = 0;

        system("clear");
        printf("Enter student's ID: ");
        scanf(" %10s", temp_id);
        printf("Enter course code: ");
        scanf(" %49s", temp_subject_code);

        FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");

        while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
            if(strcmp(att.subject_code, temp_subject_code) == 0){
                if(strcmp(att.student_id, temp_id) == 0){
                    total_classes++;
                
                    if(att.status == 'P'){
                        attended_classes++;
                    }
                }
            }
        }
        fclose(file_attendance);

        system("clear");
        if(total_classes == 0){
            printf("No attendance records found for this student in this subject\n");
            wait_for_keypress();
            return 0;
        }
        else{
            double percentage = ((double)attended_classes / total_classes) * 100;
            printf("Total Classes Conducted: %d\n", total_classes);
            printf("Total Classes Attended: %d\n", attended_classes);
            printf("Total Classes Absent: %d\n", total_classes - attended_classes);
            printf("Attendance Percentage: %.2f%%\n", percentage);
        }
    }
    else if(choice == '4'){
        return 0;
    }
    else{
        printf("Error! Invalid choice! Try again!\n");
    }

    wait_for_keypress();
    return 0;
}

int issue_warnings(){
    struct Attendance att;
    struct Warning wrn;
    struct{
        char student_id[MAX_STRING];
        char subject_code[MAX_STRING];
        char latest_date[12];
        int attended;
        int total;
    }records[500];
    int record_count = 0;
    int new_warnings = 0;

    FILE *file_attendance = fopen("../data_field/attendance_reports.txt", "r");

    if(file_attendance == NULL){
        printf("Error: files not found!");
        wait_for_keypress();
        return 1;
    }

    while(fscanf(file_attendance, " %[^:]: %[^,], %[^,], %c", att.subject_code, att.student_id, att.date, &att.status) == 4){
        int found = 0;

        for(int i = 0; i < record_count; i++){
            if(strcmp(records[i].student_id, att.student_id) == 0 && strcmp(records[i].subject_code, att.subject_code) == 0){
                records[i].total++;
                if(att.status == 'P'){
                    records[i].attended++;
                }
                strcpy(records[i].latest_date, att.date);
                found = 1;
                break;
            }
        }

        if(found == 0 && record_count < 500){
            strcpy(records[record_count].student_id, att.student_id);
            strcpy(records[record_count].subject_code, att.subject_code);
            strcpy(records[record_count].latest_date, att.date);
            records[record_count].total = 1;
            records[record_count].attended = (att.status == 'P') ? 1: 0;
            record_count++;
        }
    }
    fclose(file_attendance);

    FILE *file_warnings = fopen("../data_field/warnings_history.txt", "a+");

    if(file_warnings == NULL){
        printf("Error: warnings_history.txt not found!\n");
        wait_for_keypress();
        return 1;
    }

    for(int i = 0; i < record_count; i++){
        float percentage = ((float)records[i].attended / records[i].total) * 100;
        if(percentage < 80.0){
            int is_duplicate = 0;

            rewind(file_warnings);
            while(fscanf(file_warnings, " %[^:]: %[^,], %[^,], %f", wrn.student_id, wrn.subject_code, wrn.date_issued, &wrn.attendance_percentage) == 4){
                if(strcmp(wrn.student_id, records[i].student_id) == 0 && strcmp(wrn.subject_code, records[i].subject_code) == 0 && strcmp(wrn.date_issued, records[i].latest_date) == 0){
                    is_duplicate = 1;
                    break;
                }
            }

            if(is_duplicate == 0){
                fprintf(file_warnings, "%s: %s, %s, %.2f\n", records[i].student_id, records[i].subject_code, records[i].latest_date, percentage);
                new_warnings++;
            }
        }
    }
    fclose(file_warnings);

    system("clear");
    printf("Warning generation completed. %d new warnings issued\n", new_warnings);
    wait_for_keypress();
    return 0;
}

int view_warnings(){
    char line[MAX_STRING * 3];
    FILE *file_warnings = fopen("../data_field/warnings_history.txt", "r");

    if(file_warnings == NULL){
        printf("Error: warnings_history.txt not found!");
        wait_for_keypress();
        return 1;
    }

    printf("Warnings history\n");
    printf("----------------------------------------\n");
    while(fgets(line, sizeof(line), file_warnings) != NULL){
        printf("%s", line);
    }

    fclose(file_warnings);

    wait_for_keypress();
    return 0;
}

int admin_main(){
    char choice;

    while(1){
        system("clear");
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