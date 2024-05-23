#ifndef EOP_COURSE_CONTENT_H
#define EOP_COURSE_CONTENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>

typedef struct {
    long id;
    long student_id;
    long subject_id;
    int course;
    bool is_visit;
    const char *date;
} EOP_Attendance;

#ifdef __cplusplus
}
#endif

#endif