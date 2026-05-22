# --finalProject
---------------------
All variables will be contained in the structures.c file and each file can access it 

Structures.c {

   #define MAX_STRING 50
   
   #define MAX_CODE 10

   // 1. Subject Information
   
   struct Subject {
   
       char subject_code[MAX_CODE];
       
       char subject_name[MAX_STRING];
       
       char assigned_lecturer_id[MAX_STRING]; // Links Subject to a Lecturer
       
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
       char date[12];              // Format: YYYY-MM-DD
       char status;                [span_12](start_span)// 'P' for Present, 'A' for Absent[span_12](end_span)
   };

   // 5. Reminder / Warning History
   struct Warning {
       char student_id[MAX_STRING];
       char subject_code[MAX_CODE];
       float attendance_percentage; [span_13](start_span)// To verify it fell below 80.0%[span_13](end_span)
       char date_issued[12];
   };
}
