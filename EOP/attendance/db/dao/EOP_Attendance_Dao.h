#include <stdio.h>
#include <third_party/sqlite3.h>
#include <EOP/attendance/db/tables/EOP_Attendance_Table.h>
#include <EOP/attendance/EOP_Attendance.h>
#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

#ifndef EOP_EOP_ATTENDANCE_DAO_H
#define EOP_EOP_ATTENDANCE_DAO_H


int EOP_Attendance_Dao_create(sqlite3 *db, char **err_msg);

int EOP_Save_attendance(EOP_Attendance attendance);

int EOP_Save_attendance_list(struct mg_str attendanceList);

char *EOP_Get_attendance_list(EOP_Attendance filter);

int EOP_Update_attendance(EOP_Attendance attendance);

int EOP_Delete_attendance(long attendance_id);

int EOP_Delete_student_attendance(long student_id);

int EOP_Delete_subject_attendance(long subject_id);

int EOP_Get_visit_count(Count_request request);

int EOP_Get_absence_count(Count_request request);

#endif //EOP_EOP_ATTENDANCE_DAO_H
