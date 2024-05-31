#ifndef EOP_EOP_ATTENDANCE_MAPPER_H
#define EOP_EOP_ATTENDANCE_MAPPER_H

#include <EOP/attendance/EOP_Attendance.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

EOP_Attendance EOP_Attendance_Mapper_to_attendance(struct mg_str json);

EOP_Attendance_Count_request EOP_Attendance_Mapper_to_count_request(struct mg_str json);

EOP_Attendance_Delete_attendance_request EOP_Attendance_Mapper_to_delete_attendance_request(struct mg_str json);

EOP_Attendance_Delete_student_attendance_request EOP_Attendance_Mapper_to_delete_student_attendance_request(struct mg_str json);

EOP_Attendance_Delete_subject_attendance_request EOP_Attendance_Mapper_to_delete_subject_attendance_request(struct mg_str json);

char *EOP_Attendance_Mapper_to_json(EOP_Attendance attendance);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_ATTENDANCE_MAPPER_H
