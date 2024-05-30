#ifndef EOP_COURSE_CONTENT_H
#define EOP_COURSE_CONTENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

typedef short EOP_Attendance_err_code;

typedef long EOP_Attendance_id;
typedef long EOP_Attendance_student_id;
typedef long EOP_Attendance_subject_id;
typedef int EOP_Attendance_course;
typedef bool EOP_Attendance_is_visit;
typedef const char *EOP_Attendance_date;

typedef struct {
    EOP_Attendance_id id;
    EOP_Attendance_student_id student_id;
    EOP_Attendance_subject_id subject_id;
    EOP_Attendance_course course;
    EOP_Attendance_is_visit is_visit;
    EOP_Attendance_date date;
} EOP_Attendance;

typedef struct {
    EOP_Attendance_student_id student_id;
    EOP_Attendance_subject_id subject_id;
    EOP_Attendance_course course;
} EOP_Attendance_Count_request;

typedef struct {
    EOP_Attendance_id id;
} EOP_Attendance_Delete_attendance_request;

typedef struct {
    EOP_Attendance_id student_id;
} EOP_Attendance_Delete_student_attendance_request;

typedef struct {
    EOP_Attendance_subject_id subject_id;
} EOP_Attendance_Delete_subject_attendance_request;


void EOP_Attendance_api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage);

EOP_Attendance_err_code EOP_Attendance_create_attendance_db(sqlite3 *db, char **err_msg);

#ifdef __cplusplus
}
#endif

#endif