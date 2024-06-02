#include <stdio.h>
#include <third_party/sqlite3.h>
#include <EOP/attendance/EOP_Attendance.h>
#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

#define ATTENDANCE "attendance"

#ifndef EOP_EOP_ATTENDANCE_DAO_H
#define EOP_EOP_ATTENDANCE_DAO_H

#ifdef __cplusplus
extern "C" {
#endif

EOP_Attendance_err_code EOP_Attendance_Dao_create(sqlite3 *db, char **err_msg);

EOP_Attendance_err_code EOP_Attendance_Dao_save_attendance(EOP_Attendance attendance);

EOP_Attendance_err_code EOP_Attendance_Dao_save_attendance_list(struct mg_str attendanceList);

char *EOP_Attendance_Dao_get_attendance_list(EOP_Attendance filter);

EOP_Attendance_err_code EOP_Attendance_Dao_update_attendance(EOP_Attendance attendance);

EOP_Attendance_err_code EOP_Attendance_Dao_delete_attendance(long attendance_id);

EOP_Attendance_err_code EOP_Attendance_Dao_delete_student_attendance(long student_id);

EOP_Attendance_err_code EOP_Attendance_Dao_delete_subject_attendance(long subject_id);

int EOP_Attendance_Dao_get_visit_count(EOP_Attendance_Count_request request);

int EOP_Attendance_Dao_get_absence_count(EOP_Attendance_Count_request request);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_ATTENDANCE_DAO_H
