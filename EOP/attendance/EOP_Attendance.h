#ifndef EOP_COURSE_CONTENT_H
#define EOP_COURSE_CONTENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

typedef struct {
    long id;
    long student_id;
    long subject_id;
    int course;
    bool is_visit;
    const char *date;
} EOP_Attendance;

typedef struct {
    long student_id;
    long subject_id;
    int course;
} Count_request;

typedef struct {
    long id;
} Delete_attendance_request;

typedef struct {
    long student_id;
} Delete_student_attendance_request;

typedef struct {
    long subject_id;
} Delete_subject_attendance_request;


void api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage);

int create_attendance_db(sqlite3 *db, char **err_msg);

#ifdef __cplusplus
}
#endif

#endif