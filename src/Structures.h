#ifndef STRUCTURES.H 
#define STRUCTURES.H 
#define MAX_STRING 50
#define MAX_CODE 10

struct Subject {
    char subject_code[MAX_CODE];
    char subject_name[MAX_STRING];
    char assigned_lecturer_id[MAX_STRING];
};

struct Lecturer {
    char lecturer_id[MAX_STRING];
    char lecturer_name[MAX_STRING];
};

struct Student {
    char student_id[MAX_STRING];
    char student_name[MAX_STRING];
};

struct Attendance {
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
    char date[12];             
    char status;              
};

struct Warning {
    char student_id[MAX_STRING];
    char subject_code[MAX_CODE];
    float attendance_percentage;
    char date_issued[12];
};
#endif