#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/service//EOP_Attendance_service.h>

int validate_id(long id) {
    if (id < 1) {
        printf("incorrect id");
        return 1;
    }
    return 0;
}

int validate_student_id(long student_id) {
    if (student_id < 1) {
        printf("incorrect student_id");
        return 1;
    }
    return 0;
}

int validate_subject_id(long subject_id) {
    if (subject_id < 1) {
        printf("incorrect subject_id");
        return 1;
    }
    return 0;
}

int validate_course(int course) {
    if (course < 1) {
        printf("incorrect course");
        return 1;
    }
    return 0;
}

int validate_date(const char *date) {
    if (strlen(date) < 8 || strlen(date) > 10) {
        printf("incorrect date");
        return 1;
    }
    return 0;
}

int validate_attendance(EOP_Attendance attendance) {
    if (validate_student_id(attendance.student_id) == 1) return 1;
    if (validate_subject_id(attendance.subject_id) == 1) return 1;
    if (validate_course(attendance.course) == 1) return 1;
    if (validate_date(attendance.date) == 1) return 1;
    return 0;
}

int validate_count_request(Count_request request) {
    if (validate_student_id(request.student_id) == 1) return 1;
    if (validate_subject_id(request.subject_id) == 1) return 1;
    if (validate_course(request.course) == 1) return 1;
    return 0;
}

int save_attendance(EOP_Attendance attendance) {
    if (validate_attendance(attendance) == 1) return 1;
    int result = EOP_Save_attendance(attendance);
    printf("Attendance saved");
    return result;
}

int save_attendance_list(struct mg_str attendanceList) {
    int result = EOP_Save_attendance_list(attendanceList);
    printf("Attendance list saved");
    return result;
}

char *get_attendance_list(EOP_Attendance filter) {
    printf("Getting attendance list");
    return EOP_Get_attendance_list(filter);
}

int update_attendance(EOP_Attendance attendance) {
    if (validate_attendance(attendance) == 1) return 1;
    if (validate_id(attendance.id) == 1) return 1;
    int result = EOP_Update_attendance(attendance);
    printf("Attendance updated");
    return result;
}

int delete_attendance(long attendance_id) {
    if (validate_id(attendance_id) == 1) return 1;
    int result = EOP_Delete_attendance(attendance_id);
    printf("Attendance deleted");
    return result;
}

int get_count_visit(Count_request request) {
    if (validate_count_request(request) == 1) return 1;
    int result = EOP_Get_visit_count(request);
    printf("Visit count calculated");
    return result;
}

int get_count_absence(Count_request request) {
    if (validate_count_request(request) == 1) return 1;
    int result = EOP_Get_absence_count(request);
    printf("Absence count calculated");
    return result;
}