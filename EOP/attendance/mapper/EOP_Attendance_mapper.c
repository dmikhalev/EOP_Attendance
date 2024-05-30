#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

long get_student_id(struct mg_str json) {
    return mg_json_get_long(json, "$.student_id", -1);
}

long get_subject_id(struct mg_str json) {
    return mg_json_get_long(json, "$.subject_id", -1);
}

int get_course(struct mg_str json) {
    return mg_json_get_long(json, "$.course", -1);
}

bool get_is_visit(struct mg_str json) {
    bool b = NULL;
    return mg_json_get_bool(json, "$.is_visit", &b);
}

long get_id(struct mg_str json) {
    return mg_json_get_long(json, "$.id", -1);
}

char *get_date(struct mg_str json) {
    return mg_json_get_str(json, "$.date");
}

EOP_Attendance to_model(struct mg_str json) {
    EOP_Attendance attendance;
    attendance.student_id = get_student_id(json);
    attendance.subject_id = get_subject_id(json);
    attendance.course = get_course(json);
    attendance.is_visit = get_is_visit(json);
    attendance.date = get_date(json);
    return attendance;
}

Count_request to_count_request(struct mg_str json) {
    Count_request request;
    request.student_id = get_student_id(json);
    request.subject_id = get_subject_id(json);
    request.course = get_course(json);
    return request;
}

Delete_attendance_request to_delete_attendance_request(struct mg_str json) {
    Delete_attendance_request request;
    request.id = get_id(json);
    return request;
}

Delete_student_attendance_request to_delete_student_attendance_request(struct mg_str json) {
    Delete_student_attendance_request request;
    request.student_id = get_student_id(json);
    return request;
}

Delete_subject_attendance_request to_delete_subject_attendance_request(struct mg_str json) {
    Delete_subject_attendance_request request;
    request.subject_id = get_subject_id(json);
    return request;
}

char *to_json(EOP_Attendance *attendance) {
    char obj[256];
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