#include <stdio.h>
#include <EOP/attendance/EOP_Attendance.h>

#ifndef EOP_EOP_ATTENDANCE_SERVICE_H
#define EOP_EOP_ATTENDANCE_SERVICE_H


int save_attendance(EOP_Attendance attendance);

int save_attendance_list(struct mg_str attendanceList);

char *get_attendance_list(EOP_Attendance filter);

int update_attendance(EOP_Attendance attendance);

int delete_attendance(long attendance_id);

#endif //EOP_EOP_ATTENDANCE_SERVICE_H
