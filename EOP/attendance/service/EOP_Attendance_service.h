#include <stdio.h>
#include <EOP/attendance/EOP_Attendance.h>

#ifndef EOP_EOP_ATTENDANCE_SERVICE_H
#define EOP_EOP_ATTENDANCE_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

int EOP_Attendance_Service_save_attendance(EOP_Attendance attendance);

int EOP_Attendance_Service_save_attendance_list(struct mg_str attendanceList);

char *EOP_Attendance_Service_get_attendance_list(EOP_Attendance filter);

int EOP_Attendance_Service_update_attendance(EOP_Attendance attendance);

int EOP_Attendance_Service_delete_attendance(Delete_attendance_request request);

int EOP_Attendance_Service_delete_student_attendance(Delete_student_attendance_request request);

int EOP_Attendance_Service_delete_subject_attendance(Delete_subject_attendance_request request);

int EOP_Attendance_Service_get_count_visit(Count_request request);

int EOP_Attendance_Service_get_count_absence(Count_request request);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_ATTENDANCE_SERVICE_H
