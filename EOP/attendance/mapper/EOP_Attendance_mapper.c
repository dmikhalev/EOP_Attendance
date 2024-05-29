#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

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

Count_request to_count_request(struct mg_str json) {
    Count_request request;
    request.student_id = mg_json_get_long(json, "$.student_id", -1);
    request.subject_id = mg_json_get_long(json, "$.subject_id", -1);
    request.course = mg_json_get_long(json, "$.course", -1);
    return request;
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