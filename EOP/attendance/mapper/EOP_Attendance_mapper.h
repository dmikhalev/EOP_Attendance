#ifndef EOP_EOP_ATTENDANCE_MAPPER_H
#define EOP_EOP_ATTENDANCE_MAPPER_H

#include <EOP/attendance/entities/EOP_Attendance.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

EOP_Attendance to_model(struct mg_str json) {
    EOP_Attendance attendance;
    attendance.student_id = mg_json_get_long(json, "$.student_id", -1);
    attendance.subject_id = mg_json_get_long(json, "$.subject_id", -1);
    attendance.course = mg_json_get_long(json, "$.course", -1);
    bool b = NULL;
    mg_json_get_bool(json, "$.is_visit", &b);
    attendance.is_visit = b;
    attendance.date = mg_json_get_str(json, "$.date");
    return attendance;
}

char *to_json(EOP_Attendance *attendance) {
    char obj[256]; // todo fix
    sprintf(obj, "{\n"
                 "    \"id\": %ld,\n"
                 "    \"student_id\": %ld,\n"
                 "    \"subject_id\": %ld, \n"
                 "    \"course\": %d,\n"
                 "    \"is_visit\": %b,\n"
                 "    \"date\": \"%s\"\n"
                 "}",
            attendance->id,
            attendance->student_id,
            attendance->subject_id,
            attendance->course,
            attendance->is_visit,
            attendance->date
    );
    return obj;
}


#endif //EOP_EOP_ATTENDANCE_MAPPER_H
