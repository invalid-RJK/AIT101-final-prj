#define MAX_STRING 50
#define MAX_CODE 10

// 1. Subject Information
struct Subject {
    char subject_code[MAX_CODE];
    char subject_name[MAX_STRING];
    char assigned_lecturer_id[MAX_STRING];
};

// 2. Lecturer Information
struct Lecturer {
    char lecturer_id[MAX_STRING];
    char lecturer_name[MAX_STRING];
};

// 3. Student Information
struct Student {
    char student_id[MAX_STRING];
    char student_name[MAX_STRING];
};

// 4. Attendance Records
struct Attendance {
    char subject_code[MAX_CODE];
    char student_id[MAX_STRING];
    char date[12];             
    char status;              
};

// 5. Reminder / Warning History
struct Warning {
    char student_id[MAX_STRING];
    char subject_code[MAX_CODE];
    float attendance_percentage;
    char date_issued[12];
};